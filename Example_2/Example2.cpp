#include "SIMILARITY/SIMILARITY.hpp"
#include <SFML/Window/Event.hpp>

int main() {

    sf::RenderWindow window (sf::VideoMode(800, 600), "SIMILARITY", sf::Style::None);
    SIM::Window::Value_Resize (window, sf::Vector2u (800, 600));
    SIM::Window::Center_Window (window);
    window.setFramerateLimit (60);

    SIM::UI::TextUI text;
    text.TextAccess = SIM::UI::Poly;
    text.Font.loadFromFile ("AveriaSerifLibre-Regular.ttf");
    text.setAlignment (SIM::UI::Alignment_Types::Centered);
    text.setPosition (sf::Vector2f(400, 300));
    text.Background_Dependency = false;
    text.setString ("Front!    ");

    SIM::UI::SpriteUI Coin;
    Coin.Object.Sprite_Sheet.setType ("Idle", sf::Vector2u(0, 0), sf::Vector2u(20, 20), sf::Vector2u(20, 20));
    Coin.Object.Sprite_Sheet.setType ("Idle1", sf::Vector2u(120, 0), sf::Vector2u(20, 20), sf::Vector2u(20, 20));
    Coin.Object.Sprite_Sheet.setType ("Flip0", sf::Vector2u(0, 0), sf::Vector2u(140, 20), sf::Vector2u(20, 20));
    Coin.Object.Sprite_Sheet.setType ("Flip1", sf::Vector2u(0, 21), sf::Vector2u(140, 20), sf::Vector2u(20, 20));

    sf::Color f[6] = {
        sf::Color (170, 0, 255, 255),
        sf::Color (230, 0, 255, 255),
        sf::Color (255, 0, 191, 255),
        sf::Color (255, 0, 132, 255),
        sf::Color (255, 0, 76, 255),
        sf::Color (255, 0, 0, 255)
    };

    std::function<void()> Flip0 = [&Coin, &text, &window]() {
        if (SIM::UI::isMouseContained(window, Coin.Hitbox, true)) {
            Coin.Object.setAnimation("Flip0");

        }
    };

    std::function<void()> Flip1 = [&Coin, &text, &window]() {
        if (SIM::UI::isMouseContained(window, Coin.Hitbox, true)) {
            Coin.Object.setAnimation("Flip1");
        }
    };

    Coin.Mouse_Map.setInput (sf::Mouse::Left, SIM::Input::Key_States::Press, Flip0);
    Coin.Mouse_Map.setInput (sf::Mouse::Right, SIM::Input::Key_States::Press, Flip1);

    Coin.Object.Animation_Frequency = sf::milliseconds(50);
    Coin.Object.Sprite_Sheet.Texture.loadFromFile ("coin.png");
    Coin.Object.Sprite.setTexture (Coin.Object.Sprite_Sheet.Texture);
    Coin.Object.setAnimation("Idle");
    Coin.Object.Sprite.setScale (sf::Vector2f(10, 10));
    Coin.setPosition (sf::Vector2f (400, 300));

    for (uint8_t i  = 0; i < 6; ++i) {
        text.setFillColor(i, f[6-i-1]);
    }

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        SIM::Time::Compute_DeltaTime();
        window.clear (sf::Color::White);

        Coin.Mouse_Map.TryAll();

        if (Coin.Mouse_Map.ActiveCount() == 0 && Coin.Object.getAnimationPlays() == 1) {
            if (Coin.Object.getAnimation() == "Flip0") {
                Coin.Object.setAnimation("Idle1");
                text.setString ("Back!   ");
                for (uint8_t i  = 0; i < 5; ++i) {
                    text.setFillColor(i, f[i]);
                }
            }
            else if (Coin.Object.getAnimation() == "Flip1") {
                Coin.Object.setAnimation("Idle");
                text.setString ("Front!    ");
                for (uint8_t i  = 0; i < 6; ++i) {
                    text.setFillColor(i, f[6-i-1]);
                }
            }
        }

        Coin.Object.playAnimation();

        text.playAnimation(SIM::UI::Animation_Data(SIM::UI::Animation_Types::Circular, 0, 100, 1, 0, false));

        Coin.draw(window);
        text.draw(window);
        window.display();
    }

}
