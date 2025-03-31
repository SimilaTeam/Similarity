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

/// OBJECT

#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "SpriteSheet.hpp"
#include "Physics.hpp"
#include "Time.hpp"

namespace SIM {

    /// OBJECT
    /*
        >! @brief Extension to sf::Sprite.
        -
        >! @details An Object can be considered an extension to sf::Sprite, composed of other variables.
        > The main addition is spritesheet support, which eases handling animations.
    */

    class Object {

    private:

        std::string Animation;

        sf::Vector2f Velocity;

    public:

        SpriteSheet Sprite_Sheet;
        sf::Sprite Sprite;

        bool isGeoCentered = true;

        sf::Time Animation_Frequency;

        void setAnimation (const std::string& Address) {
            Animation = Address;
        }

        std::string getAnimation () const {  return Animation;    }

        /// PLAYANIMATION
        /*
            >! @brief Plays the animation based on the spritesheet category.
            -
            >! @details This function iterates through the frames of the spritesheet category specified by the Animation variable and attributes the sprite the current frame.
        */

        void playAnimation () {

            if (Sprite.getTexture() != &Sprite_Sheet.Texture){
                Sprite.setTexture (Sprite_Sheet.Texture);
            }

            if (Sprite_Sheet.Sheet.find(Animation) == Sprite_Sheet.Sheet.end()){
                throw std::runtime_error("Animation \""+Animation+"\" does not exist in sheet.");
            }

            static sf::Clock Animation_Time;
            static std::string PreviousAnimation = Animation;
            static bool LoadFrame = true;
            static unsigned int phase = 0;

            if (PreviousAnimation != Animation) {
                phase = 0;
                Animation_Time.restart();
                LoadFrame = true;
            }
            else {
                if (LoadFrame) {
                    Sprite.setTextureRect (Sprite_Sheet.Sheet[Animation].at(phase));

                    if (phase == Sprite_Sheet.Sheet[Animation].size()-1) {
                        phase = 0;
                    }
                    else {
                        ++phase;
                    }

                    LoadFrame = false;
                }
                if (Animation_Time.getElapsedTime().asMilliseconds() >= Animation_Frequency.asMilliseconds()) {
                    Animation_Time.restart();
                    LoadFrame = true;
                }
            }

            if (PreviousAnimation != Animation) {
                PreviousAnimation = Animation;
            }

            if (isGeoCentered) {
                Sprite.setOrigin (sf::Vector2f(Sprite.getTextureRect().width/2, Sprite.getTextureRect().height/2));
            }
        }

        sf::Vector2f getVelocity () const {    return Velocity;    }

        void setVelocity (const sf::Vector2f& velocity) {
            Velocity = velocity;
        }

        void move () {
            Sprite.move (Velocity.x*SIM::Time::DeltaTime.asSeconds(), Velocity.y*SIM::Time::DeltaTime.asSeconds());
        }

        void move (const sf::Vector2f& velocity) {
            Velocity = velocity;
            Sprite.move (velocity.x*Time::DeltaTime.asSeconds(), velocity.y*Time::DeltaTime.asSeconds());
        }

    };

}

#endif
