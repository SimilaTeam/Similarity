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

/// INPUT ~ INPUT LISTS

#ifndef INPUTLISTS_HPP_INCLUDED
#define INPUTLISTS_HPP_INCLUDED

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "KeyStates.hpp"
#include "InputBoolean.hpp"
#include <unordered_map>

namespace SIM {

    namespace Input {


        /// KEYGROUP
        /*
            >! @brief Stores a key and an activation type inside a data structure.
            > A KeyGroup is a data structure used to link a key and an activation type, much like an associative container.
            -
            >! @details A KeyGroup is used mainly in handling inputs.
            > A notable use of KeyGroups is in maps that associate inputs to commands.
        */

        struct KeyGroup {
            sf::Keyboard::Key Key;
            Key_States::Activation_Type Activation;

            KeyGroup operator= (const KeyGroup& x) {
                Key = x.Key;
                Activation = x.Activation;
                return *this;
            }

            bool operator== (const KeyGroup& x) const {
                return (Key == x.Key && Activation == x.Activation);
            }

            KeyGroup (sf::Keyboard::Key key, Key_States::Activation_Type Activation_Type) {
                Key = key;
                Activation = Activation_Type;
            }

            KeyGroup(){}
        };

        struct KeyboardHasher {
            size_t operator()(const KeyGroup& g) const{
                return std::hash<sf::Keyboard::Key>()(g.Key) ^ (std::hash<Key_States::Activation_Type>()(g.Activation) << 1);
            }
        };

        /// KEYBOARD_INPUT_LIST
        // >! @details An associative container used to link a KeyGroup to a Mapping_Boolean.

        std::unordered_map <KeyGroup, Mapping_Boolean, KeyboardHasher> Keyboard_Input_List;

        /// BUTTONGROUP
        /*
            >! @brief Stores a mouse button and an activation type inside a data structure.
            > A MouseGroup is a data structure used to link a mouse button and an activation type, much like an associative container.
            -
            >! @details A MouseGroup is used mainly in handling inputs.
            > A notable use of MouseGroups is in maps that associate inputs to commands.
        */

        struct ButtonGroup {
            sf::Mouse::Button Button;
            Key_States::Activation_Type Activation;

            ButtonGroup operator= (const ButtonGroup& x) {
                Button = x.Button;
                Activation = x.Activation;
                return *this;
            }

            bool operator== (const ButtonGroup& x) const {
                return (Button == x.Button && Activation == x.Activation);
            }

            ButtonGroup (sf::Mouse::Button button, Key_States::Activation_Type Activation_Type) {
                Button = button;
                Activation = Activation_Type;
            }

            ButtonGroup(){}
        };

        struct MouseHasher {
            size_t operator()(const ButtonGroup& g) const {
                return std::hash<sf::Mouse::Button>()(g.Button) ^ (std::hash<Key_States::Activation_Type>()(g.Activation) << 1);
            }
        };

        /// MOUSE_INPUT_LIST
        // >! @details An associative container used to link a ButtonGroup to a Mapping_Boolean.

        std::unordered_map <ButtonGroup, Mapping_Boolean, MouseHasher> Mouse_Input_List;

    }
}

#endif
