#pragma once

#include <NeoPixelBus.h>

template <typename T_COLOR_FEATURE>
T_COLOR_FEATURE convertColor(RgbColor const &color);

template <typename T_COLOR_FEATURE>
T_COLOR_FEATURE convertColor(RgbwColor const &color);

template <>
inline RgbColor convertColor<RgbColor>(RgbColor const &x) { return x; }

template <>
inline RgbColor convertColor<RgbColor>(RgbwColor const &x) { return RgbColor(x.R, x.G, x.B); }

template <>
inline RgbwColor convertColor<RgbwColor>(RgbColor const &x) { return RgbwColor(x.R, x.G, x.B, 0); }

template <>
inline RgbwColor convertColor<RgbwColor>(RgbwColor const &x) { return x; }

class GenericStrip
{
public:
    virtual void Begin() = 0;
    virtual void Show() = 0;
    virtual void SetPixelColor(uint16_t indexPixel, RgbColor const &color) = 0;
    virtual void SetPixelColor(uint16_t indexPixel, RgbwColor const &color) = 0;

    virtual void ClearTo(RgbColor const &color) = 0;
    virtual void ClearTo(RgbwColor const &color) = 0;
    virtual void ClearTo(RgbColor const &color, uint16_t first, uint16_t last) = 0;
    virtual void ClearTo(RgbwColor const &color, uint16_t first, uint16_t last) = 0;

    virtual uint16_t PixelCount() const = 0;
};

template <typename T_COLOR_FEATURE, typename T_METHOD>
class Strip : public GenericStrip
{
public:
    Strip(int count) : _strip(count){};

    void Begin() { _strip.Begin(); };
    void Show() { _strip.Show(); };

    void SetPixelColor(uint16_t indexPixel, RgbColor const &color)
    {
        _strip.SetPixelColor(indexPixel, convertColor<typename T_COLOR_FEATURE::ColorObject>(color));
    }
    void SetPixelColor(uint16_t indexPixel, RgbwColor const &color)
    {
        _strip.SetPixelColor(indexPixel, convertColor<typename T_COLOR_FEATURE::ColorObject>(color));
    };

    void ClearTo(RgbColor const &color)
    {
        _strip.ClearTo(convertColor<typename T_COLOR_FEATURE::ColorObject>(color));
    }
    void ClearTo(RgbwColor const &color)
    {
        _strip.ClearTo(convertColor<typename T_COLOR_FEATURE::ColorObject>(color));
    };

    void ClearTo(RgbColor const &color, uint16_t first, uint16_t last)
    {
        _strip.ClearTo(convertColor<typename T_COLOR_FEATURE::ColorObject>(color), first, last);
    }
    void ClearTo(RgbwColor const &color, uint16_t first, uint16_t last)
    {
        _strip.ClearTo(convertColor<typename T_COLOR_FEATURE::ColorObject>(color), first, last);
    };

    uint16_t PixelCount() const
    {
        return _strip.PixelCount();
    }

private:
    NeoPixelBus<T_COLOR_FEATURE, T_METHOD> _strip;
};
