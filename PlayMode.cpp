#include "PlayMode.hpp"

//for the GL_ERRORS() macro:
#include "gl_errors.hpp"

//for glm::value_ptr() :
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <array>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include "Load.hpp"
#include "Sprites.hpp"
#include "DataTypes.hpp"
#include "Player.hpp"

static MySprite* player_sprite = nullptr;
static Player* player_ref = nullptr;
// static MySprite* ground_sprite = nullptr;

Load< Sprites > sprites (LoadTagDefault, []() -> Sprites const* {
	static Sprites ret = Sprites::load("game.asset");
	(void) player_sprite;
	player_sprite = ret.lookup("player2");
	return &ret;
});


PlayMode::PlayMode() {
	//TODO:
	// you *must* use an asset pipeline of some sort to generate tiles.
	// don't hardcode them like this!
	// or, at least, if you do hardcode them like this,
	//  make yourself a script that spits out the code that you paste in here
	//   and check that script into your repository.

	//Also, *don't* use these tiles in your game:
	player_ref = new Player();
	player_ref->set_init_pos(glm::vec2(120, 0));
	
	uint16_t i = 0;
	for (auto tile: sprites->all_tile) {
		ppu.tile_table[i].bit0 = tile.bit0;
		ppu.tile_table[i].bit1 = tile.bit1;
		i++;
	}

	i = 0;
	for (auto palette: sprites->all_palette) {
		ppu.palette_table[i] = palette;
		i++;
	}
	ppu.background_color = glm::u8vec4(0xff, 0xff, 0xff, 0xff);
	ppu.background = sprites->background; 
	ppu.background_position.x = 0;
	ppu.background_position.y = 0;
}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_EVENT_KEY_DOWN) {
		if (evt.key.key == SDLK_LEFT) {
			left.downs += 1;
			left.pressed = true;
			return true;
		} else if (evt.key.key == SDLK_RIGHT) {
			right.downs += 1;
			right.pressed = true;
			return true;
		} else if (evt.key.key == SDLK_UP) {
			up.downs += 1;
			up.pressed = true;
			return true;
		} else if (evt.key.key == SDLK_DOWN) {
			down.downs += 1;
			down.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_EVENT_KEY_UP) {
		if (evt.key.key == SDLK_LEFT) {
			left.pressed = false;
			return true;
		} else if (evt.key.key == SDLK_RIGHT) {
			right.pressed = false;
			return true;
		} else if (evt.key.key == SDLK_UP) {
			up.pressed = false;
			return true;
		} else if (evt.key.key == SDLK_DOWN) {
			down.pressed = false;
			return true;
		}
	}

	return false;
}


void PlayMode::update(float elapsed) {
	//slowly rotates through [0,1):
	// (will be used to set background color)
	// background_fade += elapsed / 10.0f;
	// background_fade -= std::floor(background_fade);
	
	player_ref->update_input(left.pressed, right.pressed, down.pressed, up.pressed);
	player_at = player_ref->move(elapsed);

	//reset button press counters:
	left.downs = 0;
	right.downs = 0;
	up.downs = 0;
	down.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//--- set ppu state based on game state ---

	// Disable scroll for now.
	//background scroll:
	// ppu.background_position.x = int32_t(-0.5f * player_at.x);
	// ppu.background_position.y = int32_t(-0.5f * player_at.y);

	uint16_t ppu_sprite_index = 0;
	//player sprite:
	player_sprite->draw(int8_t(player_at.x), int8_t(player_at.y), &ppu, ppu_sprite_index);
	//--- actually draw ---
	ppu.draw(drawable_size);
}
