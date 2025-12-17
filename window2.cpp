//
// Created by marco on 12/16/2025.
//
#include "window2.h"

#include <cstdint>

#include "input.h"

LRESULT CALLBACK WindowsProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {

    switch (umsg) {
        case WM_NCCREATE: {
            CREATESTRUCT* cs = (CREATESTRUCT*)lparam;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
            return TRUE;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            Image* image = reinterpret_cast<Image *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            if (image) {
                image->DrawToHDC(hdc);
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        case WM_KEYDOWN: {
            if (wparam < 256) {
                Input::keys[wparam] = true;
            }
            return 0;
        }
        case WM_KEYUP: {
            if (wparam < 256) {
                Input::keys[wparam] = false;
            }
            return 0;
        }
    }
    return DefWindowProc(hwnd, umsg, wparam, lparam);
}

Window::Window(int width, int height) : m_hInstance(GetModuleHandle(nullptr)), image(width, height) {
    const wchar_t *CLASS_NAME = L"Window Class";

    WNDCLASS wndclass = {};
    wndclass.lpszClassName = CLASS_NAME;
    wndclass.hInstance = m_hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpfnWndProc = WindowsProc;

    RegisterClass(&wndclass);

    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false);

    m_hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Title",
        style,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        m_hInstance,
        &image
        );

    ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window() {
    const wchar_t *CLASS_NAME = L"Window Class";
    UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages() {
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {

        if (msg.message == WM_QUIT) {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}
