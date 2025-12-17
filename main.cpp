//
// Created by marco on 10/10/2025.
//
#include "camera.h"
#include "input.h"
#include "shape.h"
#include "shape_list.h"
#include "sphere.h"
#include "window2.h"

int main() {
    shape_list world;
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 800;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    std::cout << "Creating Window\n";
    Window* pWindow = new Window(cam.image_width, cam.image_width/cam.aspect_ratio);

    cam.render(world, pWindow->image);
    InvalidateRect(pWindow->m_hWnd, nullptr, FALSE);

    bool running = true;
    while (running) {

        if (!pWindow->ProcessMessages()) {
            std::cout << "Closing Window\n";
            running = false;
        }
        bool moved = false;

        if (Input::IsKeyDown('W')) {cam.MoveForward(); moved = true;}
        if (Input::IsKeyDown('S')) {cam.MoveBackward(); moved = true;}
        if (Input::IsKeyDown('A')) {cam.MoveLeft(); moved = true;}
        if (Input::IsKeyDown('D')) {cam.MoveRight(); moved = true;}
        if (Input::IsKeyDown(VK_SPACE)) {cam.MoveUp(); moved = true;}
        if (Input::IsKeyDown(VK_CONTROL)) {cam.MoveDown(); moved = true;}
        if (Input::IsKeyDown(VK_LEFT)) {cam.addYaw(); moved = true;}
        if (Input::IsKeyDown(VK_RIGHT)) {cam.lowerYaw(); moved = true;}
        if (Input::IsKeyDown(VK_UP)) {cam.addPitch(); moved = true;}
        if (Input::IsKeyDown(VK_DOWN)) {cam.lowerPitch(); moved = true;}

        if (moved) {
            cam.render(world, pWindow->image);
            InvalidateRect(pWindow->m_hWnd, nullptr, FALSE);
        }

        Sleep(10);
    }
    delete pWindow;

    return 0;
}
