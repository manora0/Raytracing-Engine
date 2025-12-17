#pragma once
#include <vector>
#include <Windows.h>

struct Pixel {
    float r, g, b;

    Pixel();
    Pixel(float r, float g, float b);
    ~Pixel() = default;
};

class Image {
    int m_width;
    int m_height;
    std::vector<Pixel> m_colors;

public:
    Image(int width, int height);
    ~Image() = default;

    Pixel getColor(int x, int y) const;

    void setColor(const Pixel &color, int x, int y);

    void Export(const char* path) const;

    void DrawToHDC(HDC hdc) const;
};
