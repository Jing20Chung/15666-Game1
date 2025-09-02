#include "AssetDeserializer.hpp"
#include "DataTypes.hpp"
#include "MySprite.hpp"
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
std::unordered_map< std::string, MySprite > Sprites::all_sprite;
std::array< uint16_t, PPU466::BackgroundWidth * PPU466::BackgroundHeight > Sprites::background;

Sprites Sprites::load(std::string const &filename) {
    AssetDeserializer::load(data_path(filename));
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

    // // Build all sprite info
    char* ptr = &AssetDeserializer::all_name[0];
    uint16_t* tile_idx_ptr = &AssetDeserializer::all_tile_index[0];
    uint16_t* palette_idx_ptr = &AssetDeserializer::all_palette_index[0];
    int16_t* offset_x_ptr = &AssetDeserializer::all_offset_x[0];
    int16_t* offset_y_ptr = &AssetDeserializer::all_offset_y[0];

    for(auto& data: AssetDeserializer::sprite_refs) {
        MySprite sprite;
        std::string name(data.name_size, ' ');
        memcpy(&name, ptr + data.name_index_start, (sizeof(char)) * data.name_size);

        // get tile index
        
        for (uint16_t i = data.tile_index_start; i <= data.tile_index_end; i++) {
            sprite.tiles.push_back(*(tile_idx_ptr + i));
        }
        // get palette index
        // std::cout<< "palette_index_start: " << data.palette_index_start << std::endl;
        // std::cout<< "palette_index_end: " << data.palette_index_end << std::endl;
        // std::cout<<std::endl;
        for (uint16_t i = data.palette_index_start; i <= data.palette_index_end; i++) {
            sprite.palettes.push_back(*(palette_idx_ptr + i));
        }
        // build offsets
        for (int16_t i = data.offset_index_start; i <= data.offset_index_end; i++) {
            sprite.tile_offsets.push_back({*(offset_x_ptr + i), *(offset_y_ptr + i)});
        }
        
        // set name
        sprite.name = name;
        sprite.print_info();
        
        all_sprite[name] = sprite;
    }

    // Build background
    for (uint32_t i = 0; i < AssetDeserializer::background.size(); i++) {
        background[i] = AssetDeserializer::background[i];
    }

    std::cout << "all_sprite size = " << all_sprite.size() << std::endl;
    return sprites;
}

MySprite* Sprites::lookup(std::string const &sprite_name) {
    if (all_sprite.find(sprite_name) == all_sprite.end()) {
        throw ("sprite not found");
    }
    else {
        std::cout << "sprite found" << std::endl;
        return &all_sprite[sprite_name];
    }
}