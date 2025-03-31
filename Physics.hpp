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

/// PHYSICS - ! UNDER WORK !

#ifndef PHYSICS_HPP_INCLUDED
#define PHYSICS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <cmath>

namespace SIM {

    namespace Physics {

        float Gravitational = 9.81;

        float Measure_Ratio; // 1 METRE / PIXELS CORRESPONDING TO 1 PIXEL

        bool getFallState (const float& Reference, const float Velocity, const float Lower_Limit) {
            return ((Velocity >= 0) && (Reference < Lower_Limit));
        }

        float Fall_Velocity (bool isFalling) {
            static sf::Clock time;
            static bool state = isFalling;

            if (isFalling && !state) {
                time.restart();
            }

            state = isFalling;

            return Gravitational*time.getElapsedTime().asSeconds()/Measure_Ratio;
        }

        sf::Vector2f Slide_Velocity (const sf::Vector2f Last_Speed, float Friction_Coefficient = 1) {
            static sf::Clock Time;
            sf::Vector2f Decrease;
            if (Decrease.x > 0) {
                Decrease.x = Last_Speed.x - (Friction_Coefficient * Time.getElapsedTime().asSeconds() * Last_Speed.x);
            }
            if (Decrease.y > 0) {
                Decrease.y = Last_Speed.y - (Friction_Coefficient * Time.getElapsedTime().asSeconds() * Last_Speed.y);
            }
            return Decrease;
        }

    }

}

#endif
