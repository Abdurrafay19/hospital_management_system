#include "UIThemeHelper.hpp"

void UIThemeHelper::styleDashboardCard(sf::RectangleShape &shape)
{
    shape.setFillColor(sf::Color(255, 255, 255));
    shape.setOutlineColor(sf::Color(220, 225, 230));
    shape.setOutlineThickness(2.f);
}

void UIThemeHelper::stylePanel(sf::RectangleShape &shape)
{
    shape.setFillColor(sf::Color(250, 251, 252));
    shape.setOutlineColor(sf::Color(220, 225, 230));
    shape.setOutlineThickness(2.f);
}

void UIThemeHelper::styleTitleText(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setFillColor(sf::Color(44, 62, 80));
    }
}

void UIThemeHelper::styleBodyText(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setFillColor(sf::Color(44, 62, 80));
    }
}

void UIThemeHelper::styleLabelText(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setFillColor(sf::Color(127, 140, 141));
    }
}

void UIThemeHelper::styleStatusText(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setFillColor(sf::Color(192, 57, 43));
    }
}

void UIThemeHelper::styleInput(UITextBox &input)
{
    input.setFillColor(sf::Color::White);
    input.setOutlineColor(sf::Color(189, 195, 199));
    input.setTextColor(sf::Color(44, 62, 80));
}

void UIThemeHelper::stylePrimaryButton(UIButton &button)
{
    button.setFillColor(sf::Color(52, 152, 219));
    button.setOutlineColor(sf::Color(52, 152, 219));
    button.setTextColor(sf::Color::White);
}

void UIThemeHelper::styleSuccessButton(UIButton &button)
{
    button.setFillColor(sf::Color(46, 204, 113));
    button.setOutlineColor(sf::Color(46, 204, 113));
    button.setTextColor(sf::Color::White);
}

void UIThemeHelper::styleDangerButton(UIButton &button)
{
    button.setFillColor(sf::Color(231, 76, 60));
    button.setOutlineColor(sf::Color(231, 76, 60));
    button.setTextColor(sf::Color::White);
}

void UIThemeHelper::styleNeutralButton(UIButton &button)
{
    button.setFillColor(sf::Color(230, 235, 240));
    button.setOutlineColor(sf::Color(200, 205, 210));
    button.setTextColor(sf::Color(44, 62, 80));
}

void UIThemeHelper::styleSelectedButton(UIButton &button)
{
    button.setFillColor(sf::Color(200, 200, 200));
    button.setOutlineColor(sf::Color(170, 170, 170));
    button.setTextColor(sf::Color(44, 62, 80));
}

void UIThemeHelper::setButtonSizePrimary(UIButton &button)
{
    button.setSize(sf::Vector2f(300.f, 45.f));
}

void UIThemeHelper::setButtonSizeSecondary(UIButton &button)
{
    button.setSize(sf::Vector2f(180.f, 38.f));
}

void UIThemeHelper::setButtonSizeTertiary(UIButton &button)
{
    button.setSize(sf::Vector2f(90.f, 38.f));
}

void UIThemeHelper::setButtonSizeSmall(UIButton &button)
{
    button.setSize(sf::Vector2f(120.f, 36.f));
}

void UIThemeHelper::setButtonSizeMedium(UIButton &button)
{
    button.setSize(sf::Vector2f(180.f, 38.f));
}

void UIThemeHelper::setButtonSizeWide(UIButton &button)
{
    button.setSize(sf::Vector2f(560.f, 50.f));
}

void UIThemeHelper::setTextSizeMainTitle(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setCharacterSize(28);
    }
}

void UIThemeHelper::setTextSizeTitle(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setCharacterSize(24);
    }
}

void UIThemeHelper::setTextSizeLabel(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setCharacterSize(16);
    }
}

void UIThemeHelper::setTextSizeBody(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setCharacterSize(14);
    }
}

void UIThemeHelper::setTextSizeSmall(sf::Text *text)
{
    if (text != nullptr)
    {
        text->setCharacterSize(12);
    }
}