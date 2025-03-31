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

/// TIME

#ifndef TIME_HPP_INCLUDED
#define TIME_HPP_INCLUDED

#include<SFML/Graphics.hpp>

namespace SIM {

    namespace Time {

        sf::Clock Program_Time;

        float FPS;

        sf::Time DeltaTime = sf::seconds(1);

        void Compute_DeltaTime() {
            static float Start = 0;
            float End = Program_Time.getElapsedTime().asSeconds();
            DeltaTime = sf::seconds(End-Start);
            Start = Program_Time.getElapsedTime().asSeconds();
            FPS = 1/DeltaTime.asSeconds();
        }
    }

}

#endif
