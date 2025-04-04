/// SIMILARITY - alpha
//
//  Copyright (C) 2025 - SimilaTeam
//  Contact: SimilaTeam@gmail.com
//
//  Similarity is an open-source project aiming towards the creation of tools that ease the usage of the C++ library SFML - Simple and Fast Multimedia Library.
//
//  Similarity is free to download and use for any purpose, including commercial purposes.
//
//  This software may not be distributed as an altered version without a notice specifying so.
//  This software may also not be claimed as another's.

/// SPRITE SHEET

#ifndef SPRITESHEET_HPP_INCLUDED
#define SPRITESHEET_HPP_INCLUDED

#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

namespace SIM {

    /// SPRITESHEET
    /*
        >! @brief Associates groups of frames to categories.
        -
        >! @details A SpriteSheet stores sizes for frames in a vector. That vector is later associated with a name (string) that determines its category.
    */

    class SpriteSheet {
    private:


        /// SHEETLINE (REGULAR)
        /*
            >! @brief Group of frames.
            -
            >! @details A SheetLine creates a vector of sf::IntRect in order to save the SpriteSheet data, potential sprite data.
            -
            >! @param Start_Position - the starting point in the texture, Line_Size - size of the whole line of sprites, Sprite_Size - size of the sprite.
            -
            >! @return Vector containing SpriteSheet data.
        */

        std::vector<sf::IntRect> SheetLine (const sf::Vector2u& Start_Position, const sf::Vector2u& Line_Size, const sf::Vector2u& Sprite_Size) {

            std::vector<sf::IntRect> Output;

            if (Line_Size.x > Line_Size.y) {
                for (unsigned int p = 0; p < Line_Size.x/Sprite_Size.x; ++p) {
                    Output.push_back(sf::IntRect(p*Sprite_Size.x, Start_Position.y, Sprite_Size.x, Sprite_Size.y));
                }
            }
            else {
                for (unsigned int p = 0; p < Line_Size.y/Sprite_Size.y; ++p) {
                    Output.push_back(sf::IntRect(Start_Position.x, p*Sprite_Size.y, Sprite_Size.x, Sprite_Size.y));
                }
            }

            return Output;
        }

        /// SHEETLINE (IRREGULAR)
        /*
            >! @brief Group of frames.
            -
            >! @details A SheetLine creates a vector of sf::IntRect in order to save the SpriteSheet data, potential sprite data.
            -
            >! @param Start_Position - the starting point in the texture, Line_Size - size of the whole line of sprites, Sprite_Size[] - size of each sprite.
            -
            >! @return Vector containing SpriteSheet data.
        */

        std::vector<sf::IntRect> SheetLine (const sf::Vector2u& Start_Position, const sf::Vector2u& Line_Size, sf::Vector2u Sprite_Size[]){

            std::vector<sf::IntRect> Output;
            unsigned int p = 0, position = 0;

            if (Line_Size.x >= Line_Size.y) {
                while (position < Line_Size.x) {
                    Output.push_back (sf::IntRect(Start_Position.x + position, Start_Position.y, Sprite_Size[p].x, Sprite_Size[p].y));
                    position += Sprite_Size[p].x;
                    ++p;
                }
            }
            else {
                while (position < Line_Size.y) {
                    Output.push_back (sf::IntRect(Start_Position.x, Start_Position.y + position, Sprite_Size[p].x, Sprite_Size[p].y));
                    position += Sprite_Size[p].y;
                    ++p;
                }
            }

            return Output;
        }

        std::unordered_map<std::string, std::vector<sf::IntRect>> Sheet;

    public:

        sf::Texture Texture;

        /// SETTYPE (REGULAR)
        /*
            >! @brief Adds / Modifies a category to / from the sheet.
            -
            >! @param Name - category name, Start_Position - the starting point in the texture, Line_Size - size of the whole line of frames, Sprite_Size - size of the frame.
        */

        void setType (const std::string& Name, sf::Vector2u Start_Position, sf::Vector2u Line_Size, sf::Vector2u Sprite_Size) {
            Sheet[Name] = SheetLine(Start_Position, Line_Size, Sprite_Size);
        }

        /// SETTYPE (IRREGULAR)
        /*
            >! @brief Adds / Modifies a category to / from the sheet.
            -
            >! @param Name - category name, Start_Position - the starting point in the texture, Line_Size - size of the whole line of frames, Sprite_Size[] - size of each frame.
        */

        void setType (const std::string& Name, sf::Vector2u Start_Position, sf::Vector2u Line_Size, sf::Vector2u Sprite_Size[]) {
            Sheet[Name] = SheetLine(Start_Position, Line_Size, Sprite_Size);
        }

        /// GETFRAME
        /*
            >! @brief Gets the bounds of a frame.
            -
            >! @param Name - the category name, position - the index of the frame.
            -
            >! @return Bounds of the selected frame.
        */

        sf::IntRect GetFrame (const std::string& Name, const unsigned int& position) {

            if (Sheet.find(Name) == Sheet.end()) {
                throw std::runtime_error("Animation \""+Name+"\" does not exist in sheet.");
            }
            return Sheet[Name].at(position);
        }

        /// REMOVETYPE
        /*
            >! @brief Removes a category from the sheet.
            -
            >! @param Name - the category name.
        */

        void removeType (const std::string& Name) {

            if (Sheet.find(Name) == Sheet.end()) {
                throw std::runtime_error("Animation \""+Name+"\" does not exist in sheet.");
            }
            else if (Sheet.size() > 1) {
                Sheet.erase(Name);
            }

        }

        friend class Object;
        friend class SpriteUI;
    };

}

#endif
