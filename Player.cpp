#include "GameObject.hpp"
#include "Player.hpp"
#include <glm/glm.hpp>
#include <algorithm>

Player::Player() {}
Player::~Player() {}
void Player::set_init_pos(glm::vec2 init_pos) {
    position = init_pos;
    velocity = glm::vec2(0, 0);
}

void Player::update_input(bool left_, bool right_, bool down_, bool up_){
    left_pressed = left_;
    right_pressed = right_;
    down_pressed = down_;
    up_pressed = up_;
}

glm::vec2 Player::move(float elapsed) {
    constexpr float PlayerSpeed = 30.0f;
	constexpr float PlayerJumpSpeed = 200.0f;
	constexpr float Gravity = 20.0f;
	constexpr float PlayerSlowdownSpeed = 5.0f;
	constexpr float EPSILON = 0.1f;
	constexpr float PlayerMaxSpeed = 80.0f;

	float slowDownPerFrame = PlayerSlowdownSpeed * elapsed;
	velocity.x += velocity.x < 0? slowDownPerFrame: -slowDownPerFrame;
	velocity.y += velocity.y < 0? slowDownPerFrame: -slowDownPerFrame;
	
	if (std::abs(velocity.x) <= EPSILON) velocity.x = 0;
	if (std::abs(velocity.y) <= EPSILON) velocity.y = 0;

	if (left_pressed) velocity.x -= PlayerSpeed * elapsed;
	if (right_pressed) velocity.x += PlayerSpeed * elapsed;
	// if (down_pressed) player_vel.y -= PlayerSpeed * elapsed;
	if (up_pressed) velocity.y = PlayerJumpSpeed * elapsed;

	velocity.y -= Gravity * elapsed;

	velocity.x = velocity.x > 0? std::min(velocity.x, PlayerMaxSpeed * elapsed): std::max(velocity.x, -PlayerMaxSpeed * elapsed);

	position.x += velocity.x;
	position.y += velocity.y;

	// check boundary
	if (position.x + velocity.x > 240) {
		position.x = 240;
	}
	else if (position.x + velocity.x < 10) {
		position.x = 10;
	}

	if (position.y < 10) {
		position.y = 10;
	}
	else if (position.y > 100) {
		position.y = 100;
	}

    return position;
}