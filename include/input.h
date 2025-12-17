#pragma once

struct Input {
    static bool keys[256];

    static bool IsKeyDown(int vk) {
        return keys[vk];
    }
};
