#pragma once
#include <algorithm>
#include "color.h"
#include "shape.h"
#include "image.h"

class camera {
    int image_height;                 // Rendered image height
    point3 camera_center = point3(0,0,0);
    point3 pixel00_loc;               // Location of pixel 0, 0
    vec3 delta_u;                     // Offset to pixel to the right
    vec3 delta_v;                     // Offset to pixel below
    double viewport_height;
    double viewport_width;
    double pitch = 0.0;
    double yaw = -M_PI / 2.0;
    double focal_length;
    vec3 forward;
    vec3 right;

    void setup();
    void update();
    static color ray_color(const ray& r, const shape& world);

public:
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 800;

    camera();

    void render(const shape& world, Image& image);

    void MoveForward();
    void MoveBackward();
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();

    void addYaw();
    void lowerYaw();
    void addPitch();
    void lowerPitch();
};
