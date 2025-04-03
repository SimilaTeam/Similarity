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

/// UI ~ TEXT UI

#ifndef TEXTUI_HPP_INCLUDED
#define TEXTUI_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include "UIStructures.hpp"
#include "../Input.hpp"
#include "../Time.hpp"
#include <cmath>
#include <iostream>

namespace SIM {

    namespace UI {

        /// ANIMATION_DATA
        /*
            >! @brief Data of an animation.
            -
            >! @details Animation_Data is a structure that stores the information of an animation.
        */

        struct Animation_Data {

            SIM::UI::Animation_Types Animation_Type;
            float Speed = 0, Amplitude = 0, Frequency = 1, Angular_Offset = 0;
            bool isOriented = false;

            Animation_Data (SIM::UI::Animation_Types animation, float speed = 0, float amplitude = 0, float frequency = 1, float angular_offset = 0, bool isoriented = false) {
                Animation_Type = animation;
                Speed = speed;
                Amplitude = amplitude;
                Frequency = frequency;
                Angular_Offset = angular_offset;
                isOriented = isoriented;
            }

            bool operator== (const Animation_Data& data) const {
                return Animation_Type == data.Animation_Type && Speed == data.Speed && Amplitude == data.Amplitude && Frequency == data.Frequency && Angular_Offset == data.Angular_Offset && isOriented == data.isOriented;
            }

            bool operator!= (const Animation_Data& data) const {
                return Animation_Type != data.Animation_Type && Speed != data.Speed && Amplitude != data.Amplitude && Frequency != data.Frequency && Angular_Offset != data.Angular_Offset && isOriented != data.isOriented;
            }

            Animation_Data operator= (const Animation_Data& data) {
                if (this != &data) {
                    Animation_Type = data.Animation_Type;
                    Speed = data.Speed;
                    Amplitude = data.Amplitude;
                    Frequency = data.Frequency;
                    Angular_Offset = data.Angular_Offset;
                    isOriented = data.isOriented;
                }
                return *this;
            }

            Animation_Data(){}

        };

        /// TEXTUI
        /*
            >! @brief Advanced version of sf::Text.
            -
            >! @details A Text UI is an user interface specialized for diplaying text.
            >! The additions of this data type are: alignment types, animations, hitboxes, input handling and more.
        */

        class TextUI {

        private:

            std::vector <sf::Text> TextBox;

            sf::Vector2f Internal_Origin = sf::Vector2f (0, 0);
            sf::Vector2f Origin = sf::Vector2f (0, 0);

            sf::Vector2f Position = sf::Vector2f (0, 0);
            sf::Vector2f Internal_Background_Position = sf::Vector2f (0, 0);

            sf::Vector2f Size = sf::Vector2f (0, 0); // SIZE OF THE TEXTBOX

            unsigned int Character_Size = 20;

            Alignment_Types Alignment = Centered;

            std::vector <sf::Vector2f> Initial_Positions;

            bool inAnimation = false;

            float Rotation;

            Animation_Data AnimationData;

            /// TEXT_TEMPLATE
            /*
                >! @brief Generic template for text, unaltered by functions.
            */

            sf::Text Text_Template () {
                sf::Text text;
                text.setCharacterSize (Character_Size);
                text.setFont (Font);
                text.setFillColor (General_Color);
                if (Spacing == 0) {
                    Spacing = 20;
                }
                return text;
            }

            /// HITBOX_SETROTATION
            /*
                >! @brief Changes the rotation of the hitbox.
                -
                >! @details This function changes the rotation of the hitbox by using trigonometric functions and constants based on the alignment of the text.
                -
                >! @param angle - the angle (in degrees).
            */

            void Hitbox_setRotation (float angle) {

                Hitbox.width = cos(angle*M_PI/180) * Size.x + sin(angle*M_PI/180) * Size.y;
                Hitbox.height = cos(angle*M_PI/180) * Size.y + sin(angle*M_PI/180) * Size.x;

                switch (Alignment) {

                case Centered:
                    Hitbox.left = Position.x - Hitbox.width/2;
                    Hitbox.top = Position.y - Hitbox.height/2;
                break;

                case Right:
                    Hitbox.left = Position.x - Hitbox.width;
                    Hitbox.top = Position.y - Hitbox.height;
                break;

                case Left:
                    Hitbox.left = Position.x;
                    Hitbox.top = Position.y;

                }

            }

        public:

            Text_Access TextAccess = Mono;

            sf::Color General_Color = sf::Color::Black;

            sf::RectangleShape Background;

            bool Background_Dependency = true;

            std::string Text;
            sf::Font Font;

            float Spacing = 0;

            Input::MouseMap Mouse_Map;

            sf::FloatRect Hitbox;
            bool Hitbox_Dependency = true;

            /// SETORIGIN
            /*
                >! @brief Changes the origin of the text.
                -
                >! @param Origin - the new origin.
            */

            void setOrigin (const sf::Vector2f& origin) {

                Origin = origin;

                if (TextAccess == SIM::UI::Mono) {
                    TextBox[0].setOrigin (Origin);
                    TextBox[0].setPosition(Position);
                }

                if (Hitbox_Dependency) {
                    Hitbox.left = Position.x - Hitbox.width + Origin.x;
                    Hitbox.top = Position.y - Hitbox.height + Origin.y;
                }

                if (Background_Dependency) {
                    Background.setOrigin (Origin);
                    Background.setPosition (Internal_Background_Position);
                }

            }

            sf::Vector2f getOrigin () const {    return Origin;    }

            /// SETALIGNMENT
            /*
                >! @brief Changes the alignment of the text.
                -
                >! @details By changing the initial positions of the letters, the alignment is changed.
                -
                >! @param Alignment_Type - the type of alignment.
            */

            void setAlignment (Alignment_Types Alignment_Type) {

                if (Alignment != Alignment_Type) {
                    Alignment = Alignment_Type;
                }

                if (TextAccess == SIM::UI::Poly) {

                    size_t prev = Initial_Positions.size();
                    Initial_Positions.resize(TextBox.size());

                    if (TextBox.size() < prev) {
                        Initial_Positions.shrink_to_fit();
                    }

                    if (TextBox.size() > 0) {

                        switch (Alignment) {

                            case Left:

                                setOrigin (sf::Vector2f(0, Size.y/2) );

                                TextBox[0].setPosition (sf::Vector2f (Position.x, Position.y-(TextBox[0].getLocalBounds().height/2)) );
                                Initial_Positions[0] = TextBox[0].getPosition();

                                for (unsigned int i = 1; i < TextBox.size(); ++i) {
                                    TextBox[i].setPosition (sf::Vector2f (Initial_Positions[i-1].x + TextBox[i-1].getLocalBounds().width, Initial_Positions[0].y) );
                                    Initial_Positions[i] = TextBox[i].getPosition();
                                }

                            break;

                            case Right:

                                setOrigin (sf::Vector2f(Size.x, Size.y/2) );

                                TextBox[TextBox.size()-1].setPosition (sf::Vector2f (Position.x - TextBox[TextBox.size()-1].getLocalBounds().width, Position.y - (TextBox[TextBox.size()-1].getLocalBounds().height/2)) );
                                Initial_Positions[TextBox.size()-1] = TextBox[TextBox.size()-1].getPosition();

                                if (TextBox.size() > 1) {
                                    for (int i = TextBox.size()-2; i >= 0; --i) {
                                        TextBox[i].setPosition (sf::Vector2f (Initial_Positions[i+1].x - TextBox[i].getLocalBounds().width, Initial_Positions[TextBox.size()-1].y) );
                                        Initial_Positions[i] = TextBox[i].getPosition();
                                    }
                                }
                            break;

                            case Centered:

                                setOrigin (sf::Vector2f(Size.x/2, Size.y/2 ));

                                float Size_Count = TextBox[0].getLocalBounds().width;
                                TextBox[0].setPosition (sf::Vector2f (Position.x - Size.x/2, Initial_Positions[0].y));
                                Initial_Positions[0] = TextBox[0].getPosition();

                                for (unsigned int i = 1; i < TextBox.size(); ++i) {
                                    TextBox[i].setPosition (sf::Vector2f (Position.x - (Size.x/2) + Size_Count, Initial_Positions[0].y));
                                    Size_Count += TextBox[i].getLocalBounds().width;
                                    Initial_Positions[i] = TextBox[i].getPosition();
                                }

                            }
                    }

                }
                else {
                    switch (Alignment) {

                    case Left:

                        setOrigin (sf::Vector2f (0, Size.y/2) );
                    break;

                    case Right:

                        setOrigin (sf::Vector2f (Size.x, Size.y/2) );
                    break;

                    case Centered:

                        setOrigin (sf::Vector2f (Size.x/2, Size.y/2) );
                    break;

                    }
                }

                Internal_Origin = Origin;

                setPosition(Position);
                setRotation(Rotation);

                if (inAnimation) {
                    playAnimation (Animation_Data(AnimationData.Animation_Type, 0, AnimationData.Amplitude, AnimationData.Frequency, AnimationData.Angular_Offset, AnimationData.isOriented));
                }

            }

            Alignment_Types getAlignment() const {    return Alignment;   }

            /// SETCHARACTERSIZE
            /*
                >! @brief Changes the character size of the text.
                -
                >! @param CharacterSize - the desired size for the characters.
            */

            void setCharacterSize (unsigned int CharacterSize) {

                Character_Size = CharacterSize;

                if (TextBox.size() > 0) {

                    if (TextAccess == SIM::UI::Mono) {
                        TextBox[0].setCharacterSize (CharacterSize);
                        Size.x = TextBox[0].getLocalBounds().width;
                        Size.y = TextBox[0].getLocalBounds().height;
                    }
                    else {
                        Size = sf::Vector2f (0, 0);
                        for (unsigned int i = 0; i < TextBox.size(); ++i) {
                            TextBox[i].setCharacterSize (CharacterSize);
                            Size.x += TextBox[i].getLocalBounds().width;
                            if (TextBox[i].getLocalBounds().height > Size.y) {
                                Size.y = TextBox[i].getLocalBounds().height;
                            }
                        }
                    }

                    if (Background_Dependency) {
                        Background.setSize (Size);
                    }

                    if (Hitbox_Dependency) {
                        Hitbox.width = Size.x;
                        Hitbox.height = Size.y;
                    }

                    setAlignment(Alignment);

                }

            }

            unsigned int getCharacterSize () const {   return Character_Size;  }

            /// SETPOSITION
            /*
                >! @brief Changes the position of the text.
                -
                >! @details Changes the position based on the alignment, TextAccess and origin.
                -
                >! @param position - the position.
            */

            void setPosition (const sf::Vector2f& position) {

                Internal_Background_Position.x += position.x - Position.x;
                Internal_Background_Position.y += position.y - Position.y;

                Background.setPosition (Internal_Background_Position);

                if (TextBox.size() > 0) {

                    if (Hitbox_Dependency) {
                        Hitbox.left = position.x - Origin.x;
                        Hitbox.top = position.y - Origin.y;
                    }

                    if (TextAccess == Poly) {
                        for (unsigned int i = 0; i < TextBox.size(); ++i) {
                            TextBox[i].move (sf::Vector2f (position.x - Position.x, position.y - Position.y) );
                        }
                    }
                    else {
                        TextBox[0].setPosition (position);
                    }

                }

                Position = position;

            }

            /// MOVE
            /*
                >! @brief Moves the text.
                -
                >! @details This function moves the text based on an offset.
                -
                >! @param Offset - the position offset.
            */

            void move (const sf::Vector2f& Offset) {
                setPosition(sf::Vector2f (getPosition().x + SIM::Time::DeltaTime.asSeconds()*Offset.x, getPosition().y + SIM::Time::DeltaTime.asSeconds()*Offset.y) );
            }

            sf::Vector2f getPosition () const {    return Position;    }

            /// ADD
            /*
                >! @brief Adds a character to the text.
                -
                >! @param Character - the character.
            */

            void add (const char& Character) {

                sf::Text text = Text_Template();
                text.setString (Character);

                Size.x += text.getLocalBounds().width;
                if (text.getLocalBounds().height > Size.y) {
                    Size.y = text.getLocalBounds().height;
                }

                if (TextAccess == Poly) {

                    size_t prev = Initial_Positions.size();
                    Initial_Positions.resize(TextBox.size() + 1);

                    if (TextBox.size() + 1 < prev) {
                        Initial_Positions.shrink_to_fit();
                    }

                    if (TextBox.size() > 1) {

                        switch (Alignment) {

                            case Left:

                                text.setPosition (sf::Vector2f (Initial_Positions[TextBox.size()-1].x + TextBox[TextBox.size()-1].getLocalBounds().width, Initial_Positions[0].y) );
                            break;

                            case Right:

                                text.setPosition (sf::Vector2f (Initial_Positions[0].x - text.getLocalBounds().width, Initial_Positions[TextBox.size()-1].y) );
                            break;

                            case Centered:

                                float Size_Count = TextBox[0].getLocalBounds().width;
                                TextBox[0].setPosition (sf::Vector2f (Position.x - Size.x/2, TextBox[0].getPosition().y));
                                Initial_Positions[0] = TextBox[0].getPosition();

                                for (unsigned int i = 1; i < TextBox.size(); ++i) {
                                    TextBox[i].setPosition (sf::Vector2f (Position.x - Size.x/2 + Size_Count, Position.x - (TextBox[i].getLocalBounds().height/2) ));
                                    Size_Count += TextBox[i].getLocalBounds().width;
                                    Initial_Positions[i] = TextBox[i].getPosition();
                                }
                        }
                    }
                    else {

                        switch (Alignment) {

                            case Left:

                                text.setPosition (sf::Vector2f (Position.x, Position.y - (text.getLocalBounds().height/2)) );
                            break;

                            case Right:

                                text.setPosition (sf::Vector2f (Position.x-text.getLocalBounds().width, Position.y-(text.getLocalBounds().height/2)) );
                            break;

                            case Centered:

                                text.setPosition (sf::Vector2f (Position.x-(text.getLocalBounds().width/2), Position.y-(text.getLocalBounds().height/2)) );
                        }
                    }

                    TextBox.push_back (text);
                    if (TextBox.size() > 0) {
                        Initial_Positions.at(TextBox.size() - 1) = text.getPosition();
                    }

                }
                else {
                    if (TextBox.size() == 0) {
                        sf::Text text = Text_Template();
                        text.setString(Character);
                        TextBox.push_back (text);
                    }
                    else {
                        TextBox[0].setString(TextBox[0].getString() + Character);
                    }
                }

                if (Background_Dependency) {
                    Background.setSize(Size);
                }

                if (Hitbox_Dependency) {
                    Hitbox.width = Size.x;
                    Hitbox.height = Size.y;
                }

                setAlignment(Alignment);

            }

            /// SETSTRING
            /*
                >! @brief Changes the string of the text.
                -
                >! @details The most simple and direct approach is to add letters of the string until the string is obtained.
                -
                >! @param String - the string.
            */

            void setString (const std::string& String) {

                if (TextAccess == Poly) {
                    size_t Arr_Size = TextBox.size();
                    for (unsigned int i = 0; i < String.size(); ++i) {

                        if (i >= Arr_Size) {
                            add (String[i]);
                        }
                        else {
                            TextBox[i].setString (String[i]);
                        }

                    }

                    TextBox.resize(String.size());
                    TextBox.shrink_to_fit();
                }
                else {

                    if (TextBox.size() == 0) {
                        sf::Text Text = Text_Template();
                        Text.setString (String);
                        TextBox.push_back (Text);
                    }
                    else {
                        TextBox[0].setString (String);
                    }

                    Size = sf::Vector2f (TextBox[0].getLocalBounds().width, TextBox[0].getLocalBounds().height);

                    Internal_Origin = sf::Vector2f (Size.x/2, Size.y/2);

                    TextBox[0].setOrigin(Origin);

                    Internal_Origin.x = Size.x/2;
                    Internal_Origin.y = Size.y/2;

                    if (Background_Dependency) {
                        Background.setSize(Size);
                    }

                    if (Hitbox_Dependency) {
                        Hitbox.width = Size.x;
                        Hitbox.height = Size.y;
                    }

                    setOrigin(Internal_Origin);

                }

            }

            std::string getString () {

                std::string str;

                if (TextAccess == Poly) {
                    for (unsigned int i = 0; i < TextBox.size(); ++i) {

                        if (!TextBox[i].getString().isEmpty()) {
                            str += TextBox[i].getString();
                        }
                        else{
                            TextBox.resize(i+1);
                            TextBox.shrink_to_fit();
                            break;
                        }

                    }
                }
                else {
                    str = TextBox[0].getString();
                }
                return str;
            }

            /// SETROTATION
            /*
                >! @brief Changes the rotation of the text.
                -
                >! @param angle - the angle of rotation, isOriented - boolean that determines whether the letters should be rotated in sync (only for Poly TextAccess).
            */

            void setRotation (float angle, bool isOriented = true) {

                Rotation = angle;

                if (TextAccess == SIM::UI::Poly) {

                    stopAnimation();

                    for (int i = 0; i < TextBox.size(); ++i) {

                        float Delta =  (Position.x - Initial_Positions[i].x);

                        TextBox[i].setPosition (sf::Vector2f (Position.x - Delta * cos((Rotation * M_PI)/180), Position.y - Delta * sin((Rotation * M_PI)/180) - (Size.y/2) ) ) ;

                        if (isOriented) {
                            TextBox[i].setRotation (Rotation);
                        }

                    }
                }
                else {
                    TextBox[0].setRotation (Rotation);
                }

                if (Hitbox_Dependency) {
                    Hitbox_setRotation (angle);
                }

            }

            /// ROTATE
            /*
                >! @brief Rotates the text based on an offset.
                -
                >! @param angle - the rotational offset, isOriented - boolean that determines whether the letters should be rotated in sync (only for Poly TextAccess).
            */

            void rotate (float angle, bool isOriented = true) {
                Rotation += angle*SIM::Time::DeltaTime.asSeconds();
                setRotation (Rotation, isOriented);
            }

            float getRotation () const {   return Rotation;    }

            /// SETFILLCOLOR
            /*
                >! @brief Changes the fill color of a letter at an index.
                -
                >! @param Position - the index of the letter, Color - the new color.
            */

            void setFillColor(unsigned int Position, sf::Color Color) {
                if (TextBox.size() == 0) {
                    sf::Text Text = Text_Template();
                    Text.setFillColor (Color);
                    TextBox.push_back (Text);
                }
                else {
                    TextBox[Position].setFillColor(Color);
                }
            }

            /// SETFILLCOLOR (GENERIC)
            /*
                >! @brief Changes the generic fill color of the text.
                -
                >! @param Color - the new color.
            */

            void setFillColor(const sf::Color& Color) {

                for(unsigned int i = 0; i < TextBox.size(); ++i) {
                    if (TextBox.size() == 0) {
                        sf::Text Text = Text_Template();
                        Text.setFillColor (Color);
                        TextBox.push_back (Text);
                    }
                    else {
                        TextBox[i].setFillColor(Color);
                    }
                }
            }

            sf::Color getFillColor(unsigned int Position) {    return TextBox[Position].getFillColor();    }

            /// PLAYANIMATION
            /*
                >! @brief Plays an animation.
                -
                >! @details This function moves and rotates the text in an order that generates an animation, based on the animation data.
            */

            void playAnimation (const Animation_Data& Data) {

                static float Angle;

                if (AnimationData.Animation_Type != Data.Animation_Type) {
                    stopAnimation();
                    AnimationData.Animation_Type = Data.Animation_Type;
                }

                if (AnimationData != Data) {
                    AnimationData = Data;
                }

                if (!inAnimation) {
                    inAnimation = true;
                }

                float Amplitude = 0; //Declared for SIM::UI::Circular in Poly access

                if (TextAccess == SIM::UI::Poly) {

                    switch (Data.Animation_Type) {

                    /*  For the Sinusoidal, respectively Cosinusoidal animations,
                        The tangent line at x = 0 will be used to calculate the maximum angle, which is 45 degrees.
                        Using the derivative formula, the coefficient will be determined.
                    */

                    case SIM::UI::Sinusoidal:

                        if (Background_Dependency && Background.getSize() != sf::Vector2f (Size.x, 2*Data.Amplitude)) {
                            Background.setSize (sf::Vector2f(Size.x, 2*Data.Amplitude));
                            setOrigin (sf::Vector2f (Origin.x, Data.Amplitude) );
                        }

                        if (Hitbox_Dependency && (Hitbox.width != Size.x || Hitbox.height != 2*Data.Amplitude)) {
                            Hitbox.width = Size.x;
                            Hitbox.height = 2*Data.Amplitude;
                            setOrigin(sf::Vector2f (Origin.x, Data.Amplitude) );
                        }

                        for (unsigned int i = 0; i < TextBox.size(); ++i) {
                            float Int_Angle = fmod(Data.Frequency * (Angle + ((float)i / TextBox.size())*360), 360);
                            TextBox[i].setPosition (sf::Vector2f (Initial_Positions[i].x + sin(Int_Angle * M_PI/180) * (Size.y/2), Position.y - (Data.Amplitude - Size.y) * sin((Int_Angle * M_PI)/180) - (Size.y)/2 ) );
                            TextBox[i].setRotation(Data.Angular_Offset);
                            if (Data.isOriented) {
                                TextBox[i].rotate (-cos(Int_Angle * M_PI/180) * 45);
                            }
                        }

                        break;

                    case SIM::UI::Cosinusoidal:

                        if (Background_Dependency && Background.getSize() != sf::Vector2f (Size.x, 2*Data.Amplitude)) {
                            Background.setSize(sf::Vector2f(Size.x, 2*Data.Amplitude));
                            setOrigin (sf::Vector2f (Origin.x, Data.Amplitude) );
                        }

                        if (Hitbox_Dependency && (Hitbox.width != Size.x || Hitbox.height != 2*Data.Amplitude)) {
                            Hitbox.width = Size.x;
                            Hitbox.height = 2*Data.Amplitude;
                            setOrigin(sf::Vector2f (Origin.x, Data.Amplitude) );
                        }

                        for (unsigned int i = 0; i < TextBox.size(); ++i) {
                            float Int_Angle = fmod(Data.Frequency * (Angle + ((float)i / TextBox.size())*360), 360);
                            TextBox[i].setPosition(sf::Vector2f (Initial_Positions[i].x, Position.y - (Data.Amplitude - Size.y) * cos((Int_Angle * M_PI)/180) - (Size.y)/2 ) );
                            TextBox[i].setRotation(Data.Angular_Offset);
                            if (Data.isOriented) {
                                TextBox[i].rotate (sin((Int_Angle * M_PI)/180) * 45);
                            }
                        }

                        break;

                    case SIM::UI::Circular:

                        //Here, either a custom amplitude or one based on the text size (if the data amplitude is left as 0) will be used.

                        if (Data.Amplitude == 0) {
                            Amplitude = (Size.x / (2*M_PI));
                        }
                        else {
                            Amplitude = Data.Amplitude;
                        }

                        if (Background_Dependency && Background.getSize() != sf::Vector2f(2*Amplitude, 2*Amplitude)) {
                            Background.setSize(sf::Vector2f(2*Amplitude, 2*Amplitude));
                            setOrigin (sf::Vector2f (Amplitude, Amplitude) );
                        }

                        if (Hitbox_Dependency && (Hitbox.width != 2*Amplitude || Hitbox.height != 2*Amplitude)) {
                            Hitbox.width = 2*Amplitude;
                            Hitbox.height = 2*Amplitude;
                            setOrigin(sf::Vector2f (Amplitude, Amplitude) );
                        }

                        for (unsigned int i = 0; i < TextBox.size(); ++i) {
                            float Int_Angle = fmod((Angle + ((float)i / TextBox.size())*360) + Rotation, 360);

                            TextBox[i].setRotation(Data.Angular_Offset);

                            if (Data.isOriented) {
                                TextBox[i].setPosition(sf::Vector2f (Position.x - Amplitude * cos(Int_Angle * M_PI/180), Position.y - Amplitude * sin(Int_Angle * M_PI/180) ) );
                                TextBox[i].rotate (Int_Angle-90);
                            }
                            else {
                                sf::Text* t_ptr = &TextBox[i];
                                t_ptr->setRotation(0);

                                TextBox[i].setPosition(sf::Vector2f (Position.x - (Amplitude - t_ptr->getLocalBounds().width) * cos(Int_Angle * M_PI/180) - (t_ptr->getLocalBounds().width/2), Position.y - (Amplitude - Size.y/2) * sin(Int_Angle * M_PI/180) - (Size.y/2) ) );

                            }

                        }

                        break;

                    case SIM::UI::Rotational:

                        if (Background_Dependency) {
                            Background.setRotation (Angle);
                        }

                        rotate (Data.Speed, Data.isOriented);

                    }

                }

                else {

                    switch (Data.Animation_Type) {

                        case SIM::UI::Sinusoidal:

                            setRotation (Data.Angular_Offset - cos((Data.Frequency * Angle * M_PI)/180) * 45);

                            break;

                        case SIM::UI::Cosinusoidal:

                            setRotation (Data.Angular_Offset + sin((Data.Frequency * Angle * M_PI)/180) * 45);

                            break;

                        case SIM::UI::Rotational:

                            if (Background_Dependency) {
                                Background.setRotation (Rotation);
                            }

                            rotate (Data.Speed, Data.isOriented);

                    }

                }

                Angle += SIM::Time::DeltaTime.asSeconds()*Data.Speed;
                Angle = fmod(Angle, 360);

            }

            Animation_Data getAnimationData () const {    return AnimationData;   }

            /// STOPANIMATION
            /*
                >! @brief Stops the animation and refreshes.
            */

            void stopAnimation () {

                if (inAnimation) {
                    inAnimation = false;
                }

                setOrigin (Internal_Origin);

                if (TextAccess == SIM::UI::Mono) {
                    TextBox[0].setPosition(Position);
                    TextBox[0].setRotation(0);
                }
                else {
                    for (unsigned int i = 0; i < TextBox.size(); ++i) {
                        TextBox[i].setPosition(sf::Vector2f(Initial_Positions[i].x, Position.y-Size.y/2) );
                        TextBox[i].setRotation(0);
                    }
                }

                if (Background_Dependency) {
                    if (Background.getSize() != Size) {
                        Background.setSize (Size);
                    }
                    Background.setRotation (0);
                }

                if (Hitbox_Dependency && Hitbox.width != Size.x && Hitbox.height != Size.y) {
                    Hitbox.width = Size.x;
                    Hitbox.height = Size.y;
                }

            }

            /// GETSIZE
            /*
                >! @brief Gets the bounding size of the unaltered text.
                -
                >! @return The bounding size of the text.
            */

            sf::Vector2f getSize() const{  return Size;    }

            /// DRAW
            /*
                >! @brief Draws the text to a window.
                -
                >! @param Window - the window the text will be drawn to.
            */

            void draw (sf::RenderWindow& Window) {

                Window.draw(Background);

                if (TextAccess == Poly) {
                    for (unsigned int i = 0; i < TextBox.size(); ++i) {
                        Window.draw(TextBox[i]);
                    }
                }
                else {
                    Window.draw(TextBox[0]);
                }

            }

        };

    }

}

#endif
