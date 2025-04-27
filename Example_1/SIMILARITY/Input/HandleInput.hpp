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

/// INPUT ~ HANDLE INPUT

#ifndef HANDLEINPUT_HPP_INCLUDED
#define HANDLEINPUT_HPP_INCLUDED

#include "KeyStates.hpp"
#include "InputBoolean.hpp"
#include "InputLists.hpp"

namespace SIM {

    namespace Input {

        /// GETHOLD (KEY)
        /*
            >! @brief Decides which input boolean to use from the mapping boolean that is in the keyboard input list.
            -
            >! @param Key - the key, Condition - the condition.
            -
            >! @return Reference to the input boolean.
        */

        Input_Boolean& getHold (sf::Keyboard::Key Key, Key_States::Activation_Type Condition) {

            Mapping_Boolean& Position = Keyboard_Input_List[KeyGroup(Key, Condition)];

            switch (Condition) {

                case Key_States::Press:

                    return Position.Press;
                break;

                case Key_States::Press_Hold:

                    return Position.Press_Hold;
                break;

                case Key_States::Release:

                    return Position.Release;
                break;

                case Key_States::Release_Hold:

                    return Position.Release_Hold;

            }
        }

        /// GETHOLD (MOUSE BUTTON)
        /*
            >! @brief Decides which input boolean to use from the mapping boolean that is in the mouse input list.
            -
            >! @param Button - the mouse button, Condition - the condition.
            -
            >! @return Reference to the input boolean.
        */

        Input_Boolean& getHold (sf::Mouse::Button Button, Key_States::Activation_Type Condition) {

            Mapping_Boolean& Position = Mouse_Input_List[ButtonGroup(Button, Condition)];

            switch (Condition) {

                case Key_States::Press:

                    return Position.Press;
                break;

                case Key_States::Press_Hold:

                    return Position.Press_Hold;
                break;

                case Key_States::Release:

                    return Position.Release;
                break;

                case Key_States::Release_Hold:

                    return Position.Release_Hold;

            }
        }

        /// HANDLE_INPUT (KEY)
        /*
            >! @brief Handles input based on key and condition.
            -
            >! @param Key - the key, Condition - the condition.
            -
            >! @return Output of the boolean operation.
        */

        bool Handle_Input (sf::Keyboard::Key Key, Key_States::Activation_Type Condition) {

            Input_Boolean& Handle = getHold (Key, Condition);

            switch (Condition) {

                case Key_States::Press:

                    if (!Handle.Output && sf::Keyboard::isKeyPressed(Key) && sf::Keyboard::isKeyPressed(Key) != Handle.Last_State) {
                        Handle.Output = true;
                    }
                    else if (Handle.Output) {
                        Handle.Output = false;
                    }
                break;

                case Key_States::Press_Hold:

                    Handle.Output = sf::Keyboard::isKeyPressed(Key);
                break;

                case Key_States::Release:

                    if (!Handle.Output && !sf::Keyboard::isKeyPressed(Key) && sf::Keyboard::isKeyPressed(Key) != Handle.Last_State) {
                        Handle.Output = true;
                    }
                    else if (Handle.Output){
                        Handle.Output = false;
                    }
                break;

                case Key_States::Release_Hold:

                    Handle.Output = !(sf::Keyboard::isKeyPressed(Key));
            }

            if (Handle.Last_State != sf::Keyboard::isKeyPressed(Key)) {
                Handle.Last_State = sf::Keyboard::isKeyPressed(Key);
            }

            return Handle.Output;
        }

        /// HANDLE_INPUT (MOUSE BUTTON)
        /*
            >! @brief Handles input based on mouse button and condition.
            -
            >! @param Button - the button, Condition - the condition.
            -
            >! @return Output of the boolean operation.
        */

        bool Handle_Input (sf::Mouse::Button Button, Key_States::Activation_Type Condition) {

            Input_Boolean& Handle = getHold (Button, Condition);

            switch (Condition) {

                case Key_States::Activation_Type::Press:

                    if (sf::Mouse::isButtonPressed(Button) && sf::Mouse::isButtonPressed(Button) != Handle.Last_State && !Handle.Output) {
                        Handle.Output = true;
                    }
                    else if (Handle.Output){
                        Handle.Output = false;
                    }
                break;

                case Key_States::Activation_Type::Press_Hold:

                    Handle.Output = sf::Mouse::isButtonPressed(Button);
                break;

                case Key_States::Activation_Type::Release:

                    if (!Handle.Output && !sf::Mouse::isButtonPressed(Button) && sf::Mouse::isButtonPressed(Button) != Handle.Last_State) {
                        Handle.Output = true;
                    }
                    else if (Handle.Output){
                        Handle.Output = false;
                    }
                break;

                case Key_States::Activation_Type::Release_Hold:

                    Handle.Output = !(sf::Mouse::isButtonPressed(Button));
                break;
            }

            if (Handle.Last_State != sf::Mouse::isButtonPressed(Button)) {
                Handle.Last_State = sf::Mouse::isButtonPressed(Button);
            }
            return Handle.Output;
        }

    }

}

#endif
