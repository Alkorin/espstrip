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
    virtual bool CanShow() const = 0;

    virtual bool IsDirty() const = 0;
    virtual void Dirty() = 0;
    virtual void ResetDirty() = 0;

    virtual uint8_t *Pixels() = 0;
    virtual size_t PixelsSize() const = 0;
    virtual size_t PixelSize() const = 0;
    virtual uint16_t PixelCount() const = 0;

    virtual void SetPixelColor(uint16_t indexPixel, RgbColor const &color) = 0;
    virtual void SetPixelColor(uint16_t indexPixel, RgbwColor const &color) = 0;
    virtual RgbColor GetPixelRgbColor(uint16_t indexPixel) const = 0;
    virtual RgbwColor GetPixelRgbwColor(uint16_t indexPixel) const = 0;

    virtual void ClearTo(RgbColor const &color) = 0;
    virtual void ClearTo(RgbwColor const &color) = 0;
    virtual void ClearTo(RgbColor const &color, uint16_t first, uint16_t last) = 0;
    virtual void ClearTo(RgbwColor const &color, uint16_t first, uint16_t last) = 0;

    virtual void RotateLeft(uint16_t rotationCount) = 0;
    virtual void RotateLeft(uint16_t rotationCount, uint16_t first, uint16_t last) = 0;

    virtual void ShiftLeft(uint16_t shiftCount) = 0;
    virtual void ShiftLeft(uint16_t shiftCount, uint16_t first, uint16_t last) = 0;

    virtual void RotateRight(uint16_t rotationCount) = 0;
    virtual void RotateRight(uint16_t rotationCount, uint16_t first, uint16_t last) = 0;

    virtual void ShiftRight(uint16_t shiftCount) = 0;
    virtual void ShiftRight(uint16_t shiftCount, uint16_t first, uint16_t last) = 0;

    virtual void SwapPixelColor(uint16_t indexPixelOne, uint16_t indexPixelTwo) = 0;
};

template <typename T_COLOR_FEATURE, typename T_METHOD>
class Strip : public GenericStrip
{
public:
    Strip(int count) : _strip(count){};

    void Begin()
    {
        _strip.Begin();
    };

    void Show()
    {
        _strip.Show();
    };

    bool CanShow() const
    {
        return _strip.CanShow();
    };

    bool IsDirty() const
    {
        return _strip.IsDirty();
    };

    void Dirty()
    {
        _strip.Dirty();
    };

    void ResetDirty()
    {
        _strip.ResetDirty();
    };

    uint8_t *Pixels()
    {
        return _strip.Pixels();
    }

    size_t PixelsSize() const
    {
        return _strip.PixelsSize();
    };

    size_t PixelSize() const
    {
        return _strip.PixelSize();
    };

    uint16_t PixelCount() const
    {
        return _strip.PixelCount();
    };

    void SetPixelColor(uint16_t indexPixel, RgbColor const &color)
    {
        _strip.SetPixelColor(indexPixel, convertColor<typename T_COLOR_FEATURE::ColorObject>(color));
    }

    void SetPixelColor(uint16_t indexPixel, RgbwColor const &color)
    {
        _strip.SetPixelColor(indexPixel, convertColor<typename T_COLOR_FEATURE::ColorObject>(color));
    };

    RgbColor GetPixelRgbColor(uint16_t indexPixel) const
    {
        return convertColor<RgbColor>(_strip.GetPixelColor(indexPixel));
    };

    RgbwColor GetPixelRgbwColor(uint16_t indexPixel) const
    {
        return convertColor<RgbwColor>(_strip.GetPixelColor(indexPixel));
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

    void RotateLeft(uint16_t rotationCount)
    {
        _strip.RotateLeft(rotationCount);
    };

    void RotateLeft(uint16_t rotationCount, uint16_t first, uint16_t last)
    {
        _strip.RotateLeft(rotationCount, first, last);
    };

    void ShiftLeft(uint16_t shiftCount)
    {
        _strip.ShiftLeft(shiftCount);
    };

    void ShiftLeft(uint16_t shiftCount, uint16_t first, uint16_t last)
    {
        _strip.ShiftLeft(shiftCount, first, last);
    };

    void RotateRight(uint16_t rotationCount)
    {
        _strip.RotateRight(rotationCount);
    };

    void RotateRight(uint16_t rotationCount, uint16_t first, uint16_t last)
    {
        _strip.RotateRight(rotationCount, first, last);
    };

    void ShiftRight(uint16_t shiftCount)
    {
        _strip.ShiftRight(shiftCount);
    };

    void ShiftRight(uint16_t shiftCount, uint16_t first, uint16_t last)
    {
        _strip.ShiftRight(shiftCount, first, last);
    };

    void SwapPixelColor(uint16_t indexPixelOne, uint16_t indexPixelTwo)
    {
        _strip.SwapPixelColor(indexPixelOne, indexPixelTwo);
    };

private:
    NeoPixelBus<T_COLOR_FEATURE, T_METHOD> _strip;
};
