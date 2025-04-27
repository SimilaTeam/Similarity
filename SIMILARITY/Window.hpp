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

/// WINDOW

#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>

namespace SIM {

    namespace Window {

        /// VALUE_RESIZE
        /*
            >! @brief Stabilizes the window size.
            -
            >! @details By stabilizing the window size, it takes in consideration the original size and resizes the window to a multiple of that.
        */

        void Value_Resize (sf::RenderWindow& Window, const sf::Vector2u& Original_Size, const sf::Vector2u& Desired_Size) {
            Window.setSize (sf::Vector2u( ((float)Desired_Size.y/(float)Original_Size.y) * Original_Size.x, ((float)Desired_Size.y/(float)Original_Size.y) * Original_Size.y) );
        }

        /// VALUE_RESIZE (MONITOR DEPENDENT)
        /*
            >! @brief Stabilizes the window size based on the monitor resolution.
            -
            >! @details By stabilizing the window size, it takes in consideration the resolution of the user's screen and resizes the window to a multiple of that.
        */

        void Value_Resize (sf::RenderWindow& Window, const sf::Vector2u& Original_Size) {
            Window.setSize (sf::Vector2u( ((float)sf::VideoMode().getDesktopMode().height/(float)Original_Size.y) * Original_Size.x, ((float)sf::VideoMode().getDesktopMode().height/(float)Original_Size.y) * Original_Size.y) );
        }

        /// VALUE_RESIZE (MONITOR DEPENDENT)
        /*
            >! @brief Centers the window based on the screen size.
        */

        void Center_Window (sf::RenderWindow& Window) {
            Window.setPosition (sf::Vector2i (sf::VideoMode().getDesktopMode().width/2 - Window.getSize().x/2, sf::VideoMode().getDesktopMode().height/2 - Window.getSize().y/2) );
        }
    }

}

#endif
