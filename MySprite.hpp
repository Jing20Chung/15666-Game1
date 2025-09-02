#pragma once
#include "PPU466.hpp"
#include <vector>
#include <queue>
#include "DataTypes.hpp"

struct MySprite {
    MySprite();
    ~MySprite();

    std::vector< PPU466::Sprite* > ppu_sprites;
    SpriteInfo info;
    void set_info(SpriteInfo info_);
    void draw(uint32_t x, uint32_t y, PPU466* ppu, std::queue< uint16_t >& available_sprite_index);
};