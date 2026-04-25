#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

class Game {
public:
    Game() 
        : m_window(sf::VideoMode({800, 600}), "SFML 3.1 OOP Test")
        , m_player(50.f) // Radius of 50
    {
        m_player.setFillColor(sf::Color::Cyan);
        m_player.setOrigin({50.f, 50.f}); // Center origin for better rotation/movement
        m_player.setPosition({400.f, 300.f});
    }

    void run() {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // Target 60 FPS

        while (m_window.isOpen()) {
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > TimePerFrame) {
                timeSinceLastUpdate -= TimePerFrame;
                processEvents();
                update(TimePerFrame);
            }
            render();
        }
    }

private:
    void processEvents() {
        // SFML 3 uses std::optional for polling
        while (const std::optional event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
            }
        }
    }

    void update(sf::Time deltaTime) {
        float speed = 200.f; // Pixels per second
        sf::Vector2f movement(0.f, 0.f);

        // Modern SFML 3 input checking
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

        m_player.move(movement * speed * deltaTime.asSeconds());
    }

    void render() {
        m_window.clear(sf::Color(30, 30, 30)); // Dark grey background
        m_window.draw(m_player);
        m_window.display();
    }

    sf::RenderWindow m_window;
    sf::CircleShape m_player;
};

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}