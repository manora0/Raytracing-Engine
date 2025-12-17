//
// Created by marco on 12/16/2025.
//

#include "image.h"
#include <iostream>
#include <fstream>

Pixel::Pixel() :r(0), g(0), b(0){}

Pixel::Pixel(float r, float g, float b) : r(r), g(g), b(b) {
}

Image::Image(int width, int height)
    : m_width(width), m_height(height), m_colors(std::vector<Pixel>(width * height)){}

Pixel Image::getColor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void Image::setColor(const Pixel &color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void Image::DrawToHDC(HDC hdc) const {
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = m_width;
    bmi.bmiHeader.biHeight = -m_height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    std::vector<unsigned char> buffer(m_width * m_height * 3);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {

            int i = (y * m_width + x) * 3;
            buffer[i + 0] = static_cast<unsigned char>(getColor(x, y).b * 255.0f);
            buffer[i + 1] = static_cast<unsigned char>(getColor(x, y).g * 255.0f);
            buffer[i + 2] = static_cast<unsigned char>(getColor(x, y).r * 255.0f);
        }
    }

    StretchDIBits(
        hdc,
        0, 0, m_width, m_height,
        0, 0, m_width, m_height,
        buffer.data(),
        &bmi,
        DIB_RGB_COLORS,
        SRCCOPY
        );
}

void Image::Export(const char *path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File can not be opened\n";
        return;
    }

    // REQUIRED PARTS
    // HEADER - General Information
    // DIB HEADER - Detailed Information
    // PIXEL ARRAY

    unsigned char bmppad[3] = {0, 0, 0}; // PADDING REQURED PER PIXEL COLOR
    const int paddingAmmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmmount * m_height;

    unsigned char fileHeader[fileHeaderSize];

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    // File size (little endian)
    fileHeader[2] = (fileSize);
    fileHeader[3] = (fileSize >> 8);
    fileHeader[4] = (fileSize >> 16);
    fileHeader[5] = (fileSize >> 24);

    // Reserved (must be zero)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    fileHeader[8] = 0;
    fileHeader[9] = 0;

    // Pixel data offset
    fileHeader[10] = (fileHeaderSize + informationHeaderSize);
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Image width
    informationHeader[4]  = (m_width);
    informationHeader[5]  = (m_width >> 8);
    informationHeader[6]  = (m_width >> 16);
    informationHeader[7]  = (m_width >> 24);

    // Image height
    informationHeader[8]  = (m_height);
    informationHeader[9]  = (m_height >> 8);
    informationHeader[10] = (m_height >> 16);
    informationHeader[11] = (m_height >> 24);

    // Planes (must be 1)
    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // Bits per pixel (24-bit)
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    // Compression (0 = BI_RGB)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    // Image size (can be 0 for BI_RGB)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    // X pixels per meter (optional)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    // Y pixels per meter (optional)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    // Colors in color table
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    // Important colors
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char *>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char *>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned char r = static_cast<unsigned char>(getColor(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(getColor(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(getColor(x, y).b * 255.0f);

            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char*>(color), 3);
        }

        f.write(reinterpret_cast<char*>(bmppad), paddingAmmount);
    }

    f.close();

    std::cout << "Image Created\n";
}
