#include "UIButton.hpp"

UIButton::UIButton() {
    font = 0;
    label = 0;
    enabled = true;
    box.setSize(sf::Vector2f(0.f, 0.f));
}

UIButton::UIButton(const sf::Font& buttonFont,
                   const char* text,
                   sf::Vector2f position,
                   sf::Vector2f size) {
    font = 0;
    label = 0;
    enabled = true;
    box.setSize(sf::Vector2f(0.f, 0.f));

    setFont(buttonFont);
    setText(text);
    setPosition(position);
    setSize(size);
}

UIButton::UIButton(const UIButton& other) {
    font = 0;
    label = 0;
    enabled = other.enabled;
    box = other.box;

    if (other.font != 0) {
        font = other.font;
        label = new sf::Text(*font, "", 20);
    }

    if (label != 0 && other.label != 0) {
        *label = *other.label;
    }
}

UIButton::~UIButton() {
    delete label;
    label = 0;
}

UIButton& UIButton::operator=(const UIButton& other) {
    if (this != &other) {
        delete label;
        label = 0;
        font = 0;
        enabled = other.enabled;
        box = other.box;

        if (other.font != 0) {
            font = other.font;
            label = new sf::Text(*font, "", 20);
        }

        if (label != 0 && other.label != 0) {
            *label = *other.label;
        }
    }

    return *this;
}

void UIButton::updateLabelPosition() {
    if (label == 0) {
        return;
    }

    sf::FloatRect labelBounds;
    float targetX;
    float targetY;

    labelBounds = label->getLocalBounds();
    targetX = box.getPosition().x + (box.getSize().x * 0.5f) - (labelBounds.size.x * 0.5f) - labelBounds.position.x;
    targetY = box.getPosition().y + (box.getSize().y * 0.5f) - (labelBounds.size.y * 0.5f) - labelBounds.position.y;
    label->setPosition(sf::Vector2f(targetX, targetY));
}

void UIButton::setFont(const sf::Font& buttonFont) {
    font = &buttonFont;

    if (label == 0) {
        label = new sf::Text(buttonFont, "", 20);
    } else {
        *label = sf::Text(buttonFont, label->getString(), label->getCharacterSize());
    }

    updateLabelPosition();
}

void UIButton::setText(const char* text) {
    if (label == 0) {
        return;
    }

    if (text == 0) {
        label->setString("");
    } else {
        label->setString(text);
    }

    updateLabelPosition();
}

void UIButton::setPosition(sf::Vector2f position) {
    box.setPosition(position);
    updateLabelPosition();
}

void UIButton::setSize(sf::Vector2f size) {
    box.setSize(size);
    box.setOutlineThickness(1.f);
    updateLabelPosition();
}

void UIButton::setFillColor(const sf::Color& color) {
    box.setFillColor(color);
}

void UIButton::setOutlineColor(const sf::Color& color) {
    box.setOutlineColor(color);
}

void UIButton::setTextColor(const sf::Color& color) {
    if (label != 0) {
        label->setFillColor(color);
    }
}

void UIButton::setEnabled(bool isEnabled) {
    enabled = isEnabled;
}

bool UIButton::isClicked(sf::RenderWindow& window) const {
    sf::Vector2i mousePosition;
    sf::Vector2f mouseWorldPosition;

    if (!enabled) {
        return false;
    }

    mousePosition = sf::Mouse::getPosition(window);
    mouseWorldPosition = window.mapPixelToCoords(mousePosition);

    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && box.getGlobalBounds().contains(mouseWorldPosition);
}

void UIButton::draw(sf::RenderWindow& window) const {
    window.draw(box);
    if (label != 0) {
        window.draw(*label);
    }
}

const sf::RectangleShape& UIButton::getShape() const {
    return box;
}

const sf::Text* UIButton::getLabel() const {
    return label;
}
