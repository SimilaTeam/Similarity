#include "SIMILARITY/SIMILARITY.hpp"
#include <SFML/Window/Event.hpp>

int main() {

    sf::RenderWindow window (sf::VideoMode(800, 600), "SIMILARITY", sf::Style::None);
    SIM::Window::Value_Resize (window, sf::Vector2u (800, 600));
    SIM::Window::Center_Window (window);
    window.setFramerateLimit (60);
    window.setMouseCursorVisible (false);

    SIM::Object obj;

    sf::View Camera;
    Camera.setSize(sf::Vector2f(800,600));

    window.setView(Camera);

    obj.isGeoCentered = true;

    obj.Sprite_Sheet.Texture.loadFromFile ("dude.png");
    obj.Sprite_Sheet.setType ("Walk_R", sf::Vector2u(0, 0), sf::Vector2u(640, 64), sf::Vector2u(64,64));
    obj.Sprite_Sheet.setType ("Walk_L", sf::Vector2u(0, 65), sf::Vector2u(640, 64), sf::Vector2u(64,64));
    obj.Sprite_Sheet.setType ("Idle_R", sf::Vector2u(0, 130), sf::Vector2u(320, 64), sf::Vector2u(64,64));
    obj.Sprite_Sheet.setType ("Idle_L", sf::Vector2u(320, 130), sf::Vector2u(320, 64), sf::Vector2u(64,64));
    obj.setAnimation("Idle_R");
    obj.Animation_Frequency = sf::milliseconds(200);

    obj.Sprite.setPosition (sf::Vector2f(600,400-16));

    SIM::Input::KeyboardMap K_Input;

    std::function<void()> Move_Left = [&obj]() {
        obj.move (sf::Vector2f(-64, 0) );
        if (obj.getAnimation() != "Walk_L") {
            obj.setAnimation ("Walk_L");
        }
    };

    std::function<void()> Move_Right = [&obj]() {
        obj.move (sf::Vector2f(64, 0) );
        if (obj.getAnimation() != "Walk_R") {
            obj.setAnimation ("Walk_R");
        }
    };

    K_Input.setInput (sf::Keyboard::Left, SIM::Input::Key_States::Press_Hold, Move_Left);
    K_Input.setInput (sf::Keyboard::Right, SIM::Input::Key_States::Press_Hold, Move_Right);

    sf::Texture Background_Texture;
    Background_Texture.loadFromFile ("background.png");

    sf::Sprite Background (Background_Texture);
    Background.setOrigin(sf::Vector2f(400,300));

    sf::Texture Ground_Texture;
    Ground_Texture.loadFromFile ("ground.png");

    sf::Sprite Ground (Ground_Texture);
    Ground.setPosition(sf::Vector2f(0,400));

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        SIM::Time::Compute_DeltaTime();
        window.clear (sf::Color::Black);

        window.draw (Background);

        window.draw (Ground);

        K_Input.TryAll();

        if (K_Input.ActiveCount() == 0 || (SIM::Input::Handle_Input(sf::Keyboard::Left, SIM::Input::Key_States::Press_Hold) == true && SIM::Input::Handle_Input(sf::Keyboard::Right, SIM::Input::Key_States::Press_Hold) == true) ) {

            if (obj.getAnimation() == "Walk_R") {
                obj.setAnimation("Idle_R");
            }
            else if (obj.getAnimation() == "Walk_L") {
                obj.setAnimation ("Idle_L");
            }

            if (obj.Animation_Frequency.asMilliseconds() != 200) {
                obj.Animation_Frequency = sf::milliseconds(200);
            }
        }
        else if (obj.Animation_Frequency.asMilliseconds() != 25) {
            obj.Animation_Frequency = sf::milliseconds(25);
        }
        obj.playAnimation();

        window.draw(obj.Sprite);

        if (obj.Sprite.getPosition().x >= 400 && obj.Sprite.getPosition().x <= 1400) {
            Camera.setCenter (sf::Vector2f(obj.Sprite.getPosition().x, 300));
            Background.setPosition (sf::Vector2f (obj.Sprite.getPosition().x, 300));
            window.setView(Camera);
        }
        else if (obj.Sprite.getPosition().x < 32) {
            obj.Sprite.setPosition (32, obj.Sprite.getPosition().y);
        }
        else if (obj.Sprite.getPosition().x > 1800-32) {
            obj.Sprite.setPosition (1800-32, obj.Sprite.getPosition().y);
        }

        window.display();
    }

}
