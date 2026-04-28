#pragma once

#include <SFML/Graphics.hpp>

class UIButton {
private:
    sf::RectangleShape box;
    sf::Text* label;
    const sf::Font* font;
    bool enabled;

    void updateLabelPosition();

public:
    UIButton();
    UIButton(const sf::Font& buttonFont,
             const char* text,
             sf::Vector2f position,
             sf::Vector2f size);
    UIButton(const UIButton& other);
    ~UIButton();

    UIButton& operator=(const UIButton& other);

    void setFont(const sf::Font& buttonFont);
    void setText(const char* text);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);
    void setEnabled(bool isEnabled);

    bool isClicked(sf::RenderWindow& window) const;
    void draw(sf::RenderWindow& window) const;

    const sf::RectangleShape& getShape() const;
    const sf::Text* getLabel() const;
};
