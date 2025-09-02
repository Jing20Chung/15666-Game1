#include "AssetDeserializer.hpp"
#include "DataTypes.hpp"
#include "Sprites.hpp"
#include "load_save_png.hpp"
#include "data_path.hpp"
#include "read_write_chunk.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <algorithm>

// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/hash.hpp"

Sprites::Sprites(){}
Sprites::~Sprites(){}

std::vector< Tile > Sprites::all_tile; // all found sprite, sprite contains: tile number, palette table number, and name.
std::vector< std::array<glm::u8vec4, 4 > > Sprites::all_palette; // all found sprite, sprite contains: tile number, palette table number, and name.
std::vector< Sprite > Sprites::all_sprite; // all found sprite, sprite contains: tile number, palette table number, and name.
std::array< uint16_t, PPU466::BackgroundWidth * PPU466::BackgroundHeight > Sprites::background;

Sprites Sprites::load(std::string const &filename) {
    AssetDeserializer::load(data_path("game.asset"));
    Sprites sprites;
    // Build all tile from flat bits
    for (uint16_t i = 0; i < AssetDeserializer::flat_tile_bit0.size(); i+=8) {
        Tile tile;
        for (uint16_t j = 0; j < 8; j++) {
            tile.bit0[j] = AssetDeserializer::flat_tile_bit0[i + j];
            tile.bit1[j] = AssetDeserializer::flat_tile_bit1[i + j];
        }
        all_tile.push_back(tile);
    }

    // Build all palette from flat palette
    std::array< glm::u8vec4, 4 > palette_set;
    for (uint16_t i = 0; i < AssetDeserializer::flat_palette.size(); i++) {
        palette_set[i % 4] = AssetDeserializer::flat_palette[i];
        if (i % 4 == 3) {
            all_palette.push_back(palette_set);
        }
    }

    // Build all sprite
    char* ptr = &AssetDeserializer::all_name[0];
    for(auto& data: AssetDeserializer::sprite_refs) {
        std::string name(data.name_size, ' ');
        memcpy(&name, ptr + data.name_index_start, (sizeof(char)) * data.name_size);
        Sprite sprite;
        sprite.tile_index = data.tile_index;
        sprite.palette_index = data.palette_index;
        sprite.name = name;
        all_sprite.push_back(sprite);

        // std::cout<<"data.tile_index = " << data.tile_index << std::endl;
        // std::cout<<"data.palette_index = " << data.palette_index << std::endl;
        // std::cout<<"data.name_start = " << data.name_index_start << std::endl;
        // std::cout<<"data.name_size = " << data.name_size << std::endl;
        // std::cout<<"name = " << name << std::endl;
    }

    // Build background
    std::cout << "background W = " << PPU466::BackgroundWidth << ", H = " << PPU466::BackgroundHeight << std::endl;
    std::cout << "background tile count = " << AssetDeserializer::background.size() << std::endl;
    for (uint32_t i = 0; i < AssetDeserializer::background.size(); i++) {
        background[i] = AssetDeserializer::background[i];
        // background[i + AssetDeserializer::background.size()] = AssetDeserializer::background[i];
        std::cout << "background is " << background[i] << std::endl;
    }

    std::cout << "all_sprite size = " << all_sprite.size() << std::endl;
    return sprites;
}

Sprite Sprites::lookup(std::string const &sprite_name) {
    return Sprite();
}