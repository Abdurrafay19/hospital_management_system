#pragma once

#include <SFML/Graphics.hpp>
#include "../ui/UIButton.hpp"
#include "../ui/UITextBox.hpp"

class UIThemeHelper
{
public:
    static void styleDashboardCard(sf::RectangleShape &shape);
    static void stylePanel(sf::RectangleShape &shape);
    static void styleTitleText(sf::Text *text);
    static void styleBodyText(sf::Text *text);
    static void styleLabelText(sf::Text *text);
    static void styleStatusText(sf::Text *text);
    static void styleInput(UITextBox &input);
    static void stylePrimaryButton(UIButton &button);
    static void styleSuccessButton(UIButton &button);
    static void styleDangerButton(UIButton &button);
    static void styleNeutralButton(UIButton &button);
    static void styleSelectedButton(UIButton &button);

    static void setButtonSizePrimary(UIButton &button);
    static void setButtonSizeSecondary(UIButton &button);
    static void setButtonSizeTertiary(UIButton &button);
    static void setButtonSizeSmall(UIButton &button);
    static void setButtonSizeMedium(UIButton &button);
    static void setButtonSizeWide(UIButton &button);

    static void setTextSizeMainTitle(sf::Text *text);
    static void setTextSizeTitle(sf::Text *text);
    static void setTextSizeLabel(sf::Text *text);
    static void setTextSizeBody(sf::Text *text);
    static void setTextSizeSmall(sf::Text *text);
};