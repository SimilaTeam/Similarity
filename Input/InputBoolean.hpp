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

/// INPUT ~ INPUT BOOLEAN

#ifndef INPUTBOOLEAN_HPP_INCLUDED
#define INPUTBOOLEAN_HPP_INCLUDED

namespace SIM {

    namespace Input {

        /// INPUT_BOOLEAN
        /*
            >! @brief Groups the last state and the output of a boolean operation.
            -
            >! @details An input boolean is used primarily in handling inputs where boolean operations that depend on last states are done.
        */

        struct Input_Boolean {
            bool Last_State, Output;
        };

        /// MAPPING_BOOLEAN
        /*
            >! @brief Groups booleans specialized for each activation type.
            -
            >! @details A mapping boolean is used primarily in handling inputs inside an input map.
        */

        struct Mapping_Boolean {
            Input_Boolean Press, Press_Hold, Release, Release_Hold;
        };

    }
}

#endif
