#include "animations.h"
#include "genericStrip.h"

RandomSwitchColor::RandomSwitchColor(GenericStrip &s, RgbColor a, RgbColor b, uint concurrentLedsFlip) : s(s), ColorA(a), ColorB(b), animations(1)
{
    stripState.resize(s.PixelCount());
    currentFlipIndexes.resize(concurrentLedsFlip);

    // Init strip
    for (int i = 0; i < s.PixelCount(); i++)
    {
        if (rand() > (RAND_MAX / 2))
        {
            stripState[i] = true;
            s.SetPixelColor(i, ColorA);
        }
        else
        {
            stripState[i] = false;
            s.SetPixelColor(i, ColorB);
        }
    }

    // Register animation callback
    animations.StartAnimation(0, 500, [this](const AnimationParam &param) { UpdateLeds(param); });
}

void RandomSwitchColor::UpdateLeds(const AnimationParam &param)
{
    // Start of animation, pick random leds to flip
    if (param.state == AnimationState_Started)
    {
        for (int in = 0, im = 0; in < s.PixelCount() && im < currentFlipIndexes.size(); ++in)
        {
            int rn = s.PixelCount() - in;
            int rm = currentFlipIndexes.size() - im;
            if (rand() % rn < rm)
                currentFlipIndexes[im++] = in;
        }
    }

    // Apply the movement animation curve
    float progress = NeoEase::Linear(param.progress);

    // Compute the new color
    RgbColor updatedColorAToB = RgbColor::LinearBlend(ColorA, ColorB, param.progress);
    RgbColor updatedColorBToA = RgbColor::LinearBlend(ColorB, ColorA, param.progress);

    // Update colors
    for (int i = 0; i < currentFlipIndexes.size(); i++)
    {
        int index = currentFlipIndexes[i];
        if (stripState[index])
        {
            s.SetPixelColor(index, updatedColorAToB);
        }
        else
        {
            s.SetPixelColor(index, updatedColorBToA);
        }
    }

    // End of animation, update state array
    if (param.state == AnimationState_Completed)
    {
        for (int i = 0; i < currentFlipIndexes.size(); i++)
        {
            int index = currentFlipIndexes[i];
            stripState[index] = !stripState[index];
        }

        // Restart the animation
        animations.RestartAnimation(0);
    }
}