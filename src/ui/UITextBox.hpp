#pragma once

#include <SFML/Graphics.hpp>

class UITextBox {
private:
    sf::RectangleShape box;
    sf::Text* text;
    const sf::Font* font;
    char* buffer;
    int capacity;
    int length;
    bool active;

    void refreshText();
    void copyBuffer(const char* source);

public:
    UITextBox();
    UITextBox(const sf::Font& boxFont, sf::Vector2f position, sf::Vector2f size, int maxCharacters);
    ~UITextBox();

    UITextBox(const UITextBox& other);
    UITextBox& operator=(const UITextBox& other);

    void setFont(const sf::Font& boxFont);
    void setCapacity(int maxCharacters);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);
    void setActive(bool isActive);
    bool isActive() const;

    void clear();
    void handleTextEntered(char32_t unicode);
    void handleMousePress(sf::RenderWindow& window);
    const char* getText() const;
    void setText(const char* value);

    bool contains(sf::Vector2f point) const;
    void draw(sf::RenderWindow& window) const;
};
