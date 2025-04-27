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

/// UI ~ MOUSE CONTAINED

#ifndef MOUSECONTAINED_HPP_INCLUDED
#define MOUSECONTAINED_HPP_INCLUDED

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace SIM {

    namespace UI {

        /// ISMOUSECONTAINED (WITH WINDOW)
        /*
            >! @brief Checks whether the mouse is contained in a surface.
            -
            >! @details isMouseContained is a function that checks whether the position of the mouse is contained in the specified surface.
            >! This function is used when the positions are relative to the window.
            -
            >! @param Window - the window the mouse is in, Surface - the surface the mouse must be on, Map - whether pixels should be mapped to coords.
            -
            >! @return Boolean representing if the mouse is contained in the surface.
        */

        bool isMouseContained (sf::RenderWindow& Window, const sf::FloatRect& Surface, const bool& Map = true) {
            sf::Vector2i MousePos = (sf::Mouse::getPosition(Window));
            if (Map) {
                return Surface.contains (Window.mapPixelToCoords(MousePos));
            }
            else {
                return Surface.contains ((sf::Vector2f)MousePos);
            }
        };

        /// ISMOUSECONTAINED (WITHOUT WINDOW)
        /*
            >! @brief Checks whether the mouse is contained in a surface.
            -
            >! @details isMouseContained is a function that checks whether the position of the mouse is contained in the specified surface.
            >! This function is used when the positions are NOT relative to the window.
            -
            >! @param Surface - the surface the mouse must be on.
            -
            >! @return Boolean representing if the mouse is contained in the surface.
        */

        bool isMouseContained (const sf::FloatRect& Surface) {
            sf::Vector2f MousePos = (sf::Vector2f) (sf::Mouse::getPosition());
            return Surface.contains (MousePos);
        };

    }

}

#endif
