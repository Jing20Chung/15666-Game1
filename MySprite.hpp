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
    std::vector< Tile > tiles;
    std::vector< std::array< glm::u8vec4, 4 > > palettes;
    std::vector< std::vector< int16_t > > tile_offsets;
    void print_info();
    void draw(uint32_t x, uint32_t y, PPU466* ppu, std::queue< uint16_t >& available_sprite_index);
};