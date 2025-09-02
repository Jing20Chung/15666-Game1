#pragma once

#include <glm/glm.hpp>

struct GameObject {
    glm::vec2 position;
    glm::vec2 velocity;
    virtual glm::vec2 move(float elapsed);
};