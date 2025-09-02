#pragma once
#include "PPU466.hpp"
#include <vector>
#include <queue>
#include <string>
#include "DataTypes.hpp"

struct MySprite {
    MySprite();
    ~MySprite();
    
    std::string name;
    std::vector< uint16_t > tiles;
    std::vector< uint8_t > palettes;
    std::vector< std::vector< int16_t > > tile_offsets;
    void print_info();
    void draw(uint32_t x, uint32_t y, PPU466* ppu, uint16_t& ppu_sprite_index);
};