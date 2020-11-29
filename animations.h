#pragma once

#include "genericStrip.h"
#include <NeoPixelAnimator.h>

class GenericAnimation
{
public:
    virtual void Animate() = 0;
};

class RandomSwitchColor : public GenericAnimation
{
public:
    RandomSwitchColor(GenericStrip &s, RgbColor a, RgbColor b, uint concurrentLedsFlip);
    void Animate() { animations.UpdateAnimations(); }

private:
    void UpdateLeds(const AnimationParam &param);

    GenericStrip &s;
    NeoPixelAnimator animations;
    RgbColor ColorA;
    RgbColor ColorB;
    std::vector<bool> stripState;
    std::vector<uint> currentFlipIndexes;
};

class Sparks : public GenericAnimation
{
public:
    Sparks(GenericStrip &s, RgbColor a, uint concurrentLedsFlip);
    void Animate() { animations.UpdateAnimations(); }

private:
    void UpdateLeds(const AnimationParam &param);

    GenericStrip &s;
    NeoPixelAnimator animations;
    RgbColor Color;
    std::vector<bool> stripState;
    std::vector<uint> currentFlipIndexes;
};