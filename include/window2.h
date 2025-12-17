//
// Created by marco on 12/16/2025.
//

#pragma once
#define UNICODE
#define _UNICODE
#include <Windows.h>
#include "image.h"

LRESULT CALLBACK WindowsProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

class Window {
    HINSTANCE m_hInstance; // application instance
public:
        HWND m_hWnd; // window instance
    Image image;
    Window(int height, int width);
    Window(const Window&);
    Window& operator =(const Window&);
    ~Window();

    bool ProcessMessages();
};
