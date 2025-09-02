#include "GameObject.hpp"
#include <glm/glm.hpp>

struct Player: GameObject {
    Player();
    ~Player();
    bool left_pressed, right_pressed, up_pressed, down_pressed;
    void set_init_pos(glm::vec2 init_pos);
    void update_input(bool left_, bool right_, bool down_, bool up_);
    virtual glm::vec2 move (float elapsed);
};