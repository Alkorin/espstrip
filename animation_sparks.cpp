#include "animations.h"
#include "genericStrip.h"

Sparks::Sparks(GenericStrip &s, RgbColor color, uint concurrentLedsFlip) : s(s), Color(color), animations(1)
{
    stripState.resize(s.PixelCount());
    currentFlipIndexes.resize(concurrentLedsFlip);

    // Init strip
    for (int i = 0; i < s.PixelCount(); i++)
    {

        s.SetPixelColor(i, RgbColor(0, 0, 0));
    }

    // Register animation callback
    animations.StartAnimation(0, 500, [this](const AnimationParam &param) { UpdateLeds(param); });
}

void Sparks::UpdateLeds(const AnimationParam &param)
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
    float progress;
    if (param.progress < 0.5f)
    {
        progress = 2 * param.progress;
    }
    else
    {
        progress = 2 - 2 * param.progress;
    }

    progress = NeoEase::Linear(progress);

    // Compute the new color
    RgbColor updatedColor = Color.Dim(255 * progress);

    // Update colors
    for (int i = 0; i < currentFlipIndexes.size(); i++)
    {
        s.SetPixelColor(currentFlipIndexes[i], updatedColor);
    }

    // End of animation, update state array
    if (param.state == AnimationState_Completed)
    {
        // Restart the animation
        animations.RestartAnimation(0);
    }
}