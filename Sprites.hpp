#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>
#include "MySprite.hpp"
#include "DataTypes.hpp"
#include "PPU466.hpp"

struct Sprites {
    Sprites();
    ~Sprites();

    static std::vector< Tile > all_tile; // all found sprite, sprite contains: tile number, palette table number, and name.
    static std::vector< std::array<glm::u8vec4, 4> > all_palette; // all found sprite, sprite contains: tile number, palette table number, and name.
	static std::unordered_map< std::string, MySprite > all_sprite;
    static std::array< uint16_t, BackgroundWidth * BackgroundHeight > background;

    static Sprites load(std::string const &filename);
    static MySprite lookup(std::string const &sprite_name);
};