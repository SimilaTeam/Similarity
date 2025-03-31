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

/// UI ~ SPRITE UI

#ifndef SPRITEUI_HPP_INCLUDED
#define SPRITEUI_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include "UIStructures.hpp"


namespace SIM {

    namespace UI {

        /// SPRITEUI
        /*
            >! @brief UI Object consisting of a sprite.
            -
            >! @details A SpriteUI consists of an object, a hitbox and mouse input handling (So basically a SIM::Object with input handling and a hitbox).
            >! Also, a SpriteUI's origin is the geometric center of the sprite.
        */

        class SpriteUI {

        public:
            SIM::Object Object;

            Input::MouseMap Mouse_Map;

            sf::FloatRect Hitbox;
            bool Hitbox_Dependency = true;

            void setPosition (const sf::Vector2f& Position) {

                if (Object.isGeoCentered) {

                    if (Hitbox_Dependency) {
                        Hitbox.width = Object.Sprite.getLocalBounds().width;
                        Hitbox.height = Object.Sprite.getLocalBounds().height;
                    }

                    Hitbox.left = Object.Sprite.getPosition().x - (Hitbox.width/2);
                    Hitbox.top = Object.Sprite.getPosition().y - (Hitbox.height/2);

                }

                Object.Sprite.setPosition(Position);
            }

            void move (const sf::Vector2f& Offset) {
                setPosition (sf::Vector2f (Object.Sprite.getPosition().x + SIM::Time::DeltaTime.asSeconds()*Offset.x, Object.Sprite.getPosition().y + SIM::Time::DeltaTime.asSeconds()*Offset.y) );
            }

        };

    }

}

#endif
