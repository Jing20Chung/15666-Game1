#include "MySprite.hpp"
#include "PPU466.hpp"
#include <queue>

MySprite::MySprite() {}
MySprite::~MySprite() {}

void MySprite::set_info(SpriteInfo info_) {
    assert(info.tile_indexes.size() > 0 && "Error empty SpriteInfo!");
    info = info_;
}

void MySprite::draw(uint32_t x, uint32_t y, PPU466* ppu, std::queue< uint16_t >& available_sprite_index) {
    
    // while (!available_sprite_index.empty()) {

    // }
}