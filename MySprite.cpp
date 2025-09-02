#include "MySprite.hpp"
#include "PPU466.hpp"
#include <queue>
#include <iostream>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

MySprite::MySprite() {}
MySprite::~MySprite() {}

void MySprite::print_info() {
    /*
    std::string name;
    std::vector< Tile > tiles;
    std::vector< std::array< glm::u8vec4, 4 > > palettes;
    std::vector< std::vector< int16_t > > tile_offsets;
    */
    std::cout<<std::endl;
    std::cout<<"Name: " << name << std::endl;
    std::cout<<"Tiles: " << std::endl;
    uint16_t i = 0;
    for (auto& tile: tiles) {
        std::cout<<"Tile " << tile << std::endl;
        // std::cout<<"bit0: ";
        // for (auto& bit: tile.bit0) {
        //     std::cout<<bit;
        // }
        // std::cout<<std::endl;

        // std::cout<<"bit1: ";
        // for (auto& bit: tile.bit1) {
        //     std::cout<<bit;
        // }
        // std::cout<<std::endl;
    }
    
    std::cout<< "Palettes: " << std::endl;
    i = 0;
    for (auto& palette: palettes) {
        std::cout<<"Palette " << +palette << std::endl;
        // for (auto& color: palette) {
        //     std::cout<<"Color: " << glm::to_string(color) << std::endl;
        // }
    }

    std::cout<<"Tile offsets: " << std::endl;
    i = 0;
    for (auto& offset: tile_offsets) {
        std::cout<<"Tile " << i++ << ", offset x = " << offset[0] << ", y = " << offset[1] << std::endl;
    }
}

void MySprite::draw(uint32_t x, uint32_t y, PPU466* ppu, uint16_t& ppu_sprite_index) {
    // print_info();
    for (int i = 0; i < tile_offsets.size(); i++) {
        ppu->sprites[ppu_sprite_index].x = tile_offsets[i][0] + x;
        ppu->sprites[ppu_sprite_index].y = tile_offsets[i][1] + y;
        ppu->sprites[ppu_sprite_index].index = tiles[i];
        ppu->sprites[ppu_sprite_index].attributes = palettes[i];
        ppu_sprite_index++;
    }
}