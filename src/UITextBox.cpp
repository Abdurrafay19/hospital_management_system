#include "UITextBox.hpp"

UITextBox::UITextBox() {
    font = 0;
    text = 0;
    buffer = 0;
    capacity = 0;
    length = 0;
    active = false;
    box.setSize(sf::Vector2f(0.f, 0.f));
}

UITextBox::UITextBox(const sf::Font& boxFont, sf::Vector2f position, sf::Vector2f size, int maxCharacters) {
    font = 0;
    text = 0;
    buffer = 0;
    capacity = 0;
    length = 0;
    active = false;
    box.setSize(sf::Vector2f(0.f, 0.f));

    setFont(boxFont);
    setPosition(position);
    setSize(size);
    capacity = maxCharacters;
    buffer = new char[capacity + 1];
    buffer[0] = '\0';
}

UITextBox::~UITextBox() {
    delete text;
    delete[] buffer;
    text = 0;
    buffer = 0;
}

UITextBox::UITextBox(const UITextBox& other) {
    font = 0;
    text = 0;
    buffer = 0;
    capacity = 0;
    length = 0;
    active = other.active;
    box = other.box;

    if (other.font != 0) {
        font = other.font;
        text = new sf::Text(*font, "", 20);
    }

    capacity = other.capacity;
    if (capacity > 0) {
        buffer = new char[capacity + 1];
        copyBuffer(other.buffer);
    }

    length = other.length;
    if (text != 0 && other.text != 0) {
        *text = *other.text;
    } else {
        refreshText();
    }
}

UITextBox& UITextBox::operator=(const UITextBox& other) {
    if (this != &other) {
        delete text;
        delete[] buffer;
        text = 0;
        buffer = 0;
        font = 0;
        capacity = 0;
        length = 0;
        active = other.active;
        box = other.box;

        if (other.font != 0) {
            font = other.font;
            text = new sf::Text(*font, "", 20);
        }

        capacity = other.capacity;
        if (capacity > 0) {
            buffer = new char[capacity + 1];
            copyBuffer(other.buffer);
        }

        length = other.length;
        if (text != 0 && other.text != 0) {
            *text = *other.text;
        } else {
            refreshText();
        }
    }

    return *this;
}

void UITextBox::refreshText() {
    if (text == 0) {
        return;
    }

    if (buffer == 0) {
        text->setString("");
    } else {
        text->setString(buffer);
    }
}

void UITextBox::copyBuffer(const char* source) {
    int i;

    if (buffer == 0 || source == 0) {
        if (buffer != 0) {
            buffer[0] = '\0';
        }
        return;
    }

    i = 0;
    while (i < capacity && source[i] != '\0') {
        buffer[i] = source[i];
        i++;
    }
    buffer[i] = '\0';
    length = i;
}

void UITextBox::setFont(const sf::Font& boxFont) {
    font = &boxFont;

    if (text == 0) {
        text = new sf::Text(boxFont, "", 20);
    } else {
        *text = sf::Text(boxFont, getText(), 20);
    }

    refreshText();
}

void UITextBox::setPosition(sf::Vector2f position) {
    box.setPosition(position);
    if (text != 0) {
        text->setPosition(sf::Vector2f(position.x + 10.f, position.y + 8.f));
    }
}

void UITextBox::setSize(sf::Vector2f size) {
    box.setSize(size);
}

void UITextBox::setFillColor(const sf::Color& color) {
    box.setFillColor(color);
}

void UITextBox::setOutlineColor(const sf::Color& color) {
    box.setOutlineColor(color);
}

void UITextBox::setTextColor(const sf::Color& color) {
    if (text != 0) {
        text->setFillColor(color);
    }
}

void UITextBox::setActive(bool isActive) {
    active = isActive;
}

bool UITextBox::isActive() const {
    return active;
}

void UITextBox::clear() {
    if (buffer != 0) {
        buffer[0] = '\0';
    }
    length = 0;
    refreshText();
}

void UITextBox::handleTextEntered(char32_t unicode) {
    if (!active || buffer == 0) {
        return;
    }

    if (unicode == U'\b') {
        if (length > 0) {
            length--;
            buffer[length] = '\0';
            refreshText();
        }
        return;
    }

    if (unicode < 32 || unicode > 126) {
        return;
    }

    if (length >= capacity) {
        return;
    }

    buffer[length] = static_cast<char>(unicode);
    length++;
    buffer[length] = '\0';
    refreshText();
}

void UITextBox::handleMousePress(sf::RenderWindow& window) {
    sf::Vector2i mousePosition;
    sf::Vector2f mouseWorldPosition;

    mousePosition = sf::Mouse::getPosition(window);
    mouseWorldPosition = window.mapPixelToCoords(mousePosition);
    active = box.getGlobalBounds().contains(mouseWorldPosition);
}

const char* UITextBox::getText() const {
    if (buffer == 0) {
        return "";
    }

    return buffer;
}

void UITextBox::setText(const char* value) {
    int i;

    if (buffer == 0 || value == 0) {
        return;
    }

    i = 0;
    while (i < capacity && value[i] != '\0') {
        buffer[i] = value[i];
        i++;
    }
    buffer[i] = '\0';
    length = i;
    refreshText();
}

bool UITextBox::contains(sf::Vector2f point) const {
    return box.getGlobalBounds().contains(point);
}

void UITextBox::draw(sf::RenderWindow& window) const {
    window.draw(box);
    if (text != 0) {
        window.draw(*text);
    }
}
