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

/// INPUT ~ MOUSE MAP

#ifndef MOUSEMAP_HPP_INCLUDED
#define MOUSEMAP_HPP_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include "KeyStates.hpp"
#include "HandleInput.hpp"
#include "InputLists.hpp"
#include <unordered_map>

namespace SIM {

    namespace Input {

        /// MOUSEMAP
        /*
            >! @brief Associates a command to a ButtonGroup.
            > A MouseMap is a data structure used to link a ButtonGroup and a command (in the form of a hash table).
            -
            >! @details A MouseMap is used mainly in storing inputs of a specific category.
            > A notable use of MouseMaps is in videogames (example: moving), also in simulations and other softwares that depend on user mouse input.
        */

        class MouseMap {
        private:

            std::unordered_map <ButtonGroup, std::function<void()>, MouseHasher> Input_Map;

        public:

            /// SETINPUT
            /*
                >! @brief Adds / Changes an element to / in the input map.
                > setInput is a function that stores a condition and its result in the input map.
                -
                >! @param Button - the mouse button, ActivationType - the condition needed for the command to be executed, Function - the command.
            */

            void setInput (sf::Mouse::Button Button, Key_States::Activation_Type ActivationType, std::function<void()>& Function){

                ButtonGroup group;
                group.Button = Button;
                group.Activation = ActivationType;

                Input_Map[group] = Function;

            }

            /// TRY
            /*
                >! @brief Tries an input.
                > Try is a function that determines whether the condition for a command to be executed is met.
                > If the condition is met, the command is executed.
                -
                >! @param Button - the mouse button, ActivationType - the condition needed for the command to be executed.
            */

            bool Try (sf::Mouse::Button Button, Key_States::Activation_Type ActivationType) {

                ButtonGroup group;
                group.Button = Button;
                group.Activation = ActivationType;

                if (Input_Map.find(group) == Input_Map.end()) {
                    throw std::runtime_error("Button - Activation combination does not exist in input map.");
                }

                if (Handle_Input (Button, ActivationType) ) {
                    std::function<void()> button = Input_Map.find(group)->second;
                    button();
                    return true;
                }
                else {
                    return false;
                }

            }

            /// TRYALL
            /*
                >! @brief Tries every input.
                > TryAll is basically the function above, Try, but done for every element in the input map.
            */

            void TryAll () {
                std::unordered_map <ButtonGroup, std::function<void()>, MouseHasher>::iterator i;

                for(i = Input_Map.begin(); i != Input_Map.end(); ++i){
                    Try(i->first.Button, i->first.Activation);
                }
            }

            /// ACTIVECOUNT
            /*
                >! @brief Gets the number of active conditions.
                -
                >! @details ActiveCount is a function that iterates through the input map and checks whether each condition is met.
                -
                >! @return The count of active conditions.
            */

            uint16_t ActiveCount () {

                uint16_t Count = false;
                std::unordered_map <ButtonGroup, std::function<void()>, MouseHasher>::iterator i;

                for(i = Input_Map.begin(); i != Input_Map.end(); ++i){

                    ButtonGroup group = i->first;

                    if (Handle_Input (group.Button, group.Activation) ){
                        ++Count;
                    }

                }
                return Count;
            }

            /// ACTIVECOUNT (CONDITION-BASED)
            /*
                >! @brief Gets the number of active conditions that are of same type.
                -
                >! @details An overloaded function of ActiveCount that iterates through the input map and returns the count of common conditions that are met, based on the parameter.
                -
                >! @param Activation_Type - the common condition.
                -
                >! @return The count of active conditions.
            */

            uint16_t ActiveCount (Key_States::Activation_Type Activation_Type) {

                uint16_t Count = 0;
                std::unordered_map<ButtonGroup, std::function<void()>, MouseHasher>::iterator i;

                for(i = Input_Map.begin(); i != Input_Map.end(); ++i) {

                    ButtonGroup group = i->first;

                    if (group.Activation == Activation_Type && Handle_Input (group.Button, group.Activation) ){
                        ++Count;
                    }
                }
                return Count;
            }

        };

    }

}

#endif
