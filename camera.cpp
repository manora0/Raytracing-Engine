#include "camera.h"

#include <fstream>
#include <iostream>

void camera::setup() {
    image_height = int(image_width / aspect_ratio);

    viewport_height = 2.0;
    viewport_width = viewport_height * (double(image_width) / image_height);

    delta_u = vec3(viewport_width, 0, 0) / image_width;
    delta_v = vec3(0, -viewport_height, 0) / image_height;
    focal_length = 1.0;
}

void camera::update() {
    forward = vec3(
        cos(pitch) * cos(yaw),
        sin(pitch),
        cos(pitch) * sin(yaw)
    );
    forward = unit_vector(forward);

    vec3 world_up(0,1,0);
    right = unit_vector(cross(world_up, forward));
    const vec3 up = cross(forward, right);

    vec3 viewport_u = right * viewport_width;
    vec3 viewport_v = -up * viewport_height;

    delta_u = viewport_u / image_width;
    delta_v = viewport_v / image_height;

    const auto viewport_upperLeft =
        camera_center + forward * focal_length
        - viewport_u / 2
        - viewport_v / 2;

    pixel00_loc = viewport_upperLeft + 0.5 * (delta_u + delta_v);
}

color camera::ray_color(const ray& r, const shape& world) {
    shape_record rec;
    if (world.hit(r, 0, 20, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0)
         + a * color(0.5, 0.7, 1.0);
}

camera::camera() {
    setup();
    update();
}

void camera::render(const shape& world, Image& image) {
    for (int y = 0; y < image_height; y++) {
        for (int x = 0; x < image_width; x++) {
            auto pixel_center =
                pixel00_loc + (x * delta_u) + (y * delta_v);

            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);

            image.setColor(
                Pixel(pixel_color.x(), pixel_color.y(), pixel_color.z()),
                x, y
            );
        }
    }
}

void camera::MoveForward() {
    camera_center += forward * 0.1;
    update();
}

void camera::MoveBackward() {
    camera_center += -forward * 0.1;
    update();
}

void camera::MoveRight() {
    camera_center += right * 0.1;
    update();
}

void camera::MoveLeft() {
    camera_center += -right * 0.1;
    update();
}

void camera::MoveUp() {
    camera_center += vec3(0,1,0) * 0.1;
    update();
}

void camera::MoveDown() {
    if (camera_center.y() > -0.5) {
        camera_center += -vec3(0,1,0) * 0.1;
        update();
    }
    std::cout << camera_center.y();
}

void camera::addYaw() {
    yaw += 0.1;
    update();
}

void camera::lowerYaw() {
    yaw -= 0.1;
    update();
}

void camera::addPitch() {
    pitch += 0.1;
    pitch = std::clamp(pitch, -1.55, 1.55);
    update();
}

void camera::lowerPitch() {
    pitch -= 0.1;
    pitch = std::clamp(pitch, -1.55, 1.55);
    update();
}
