#pragma once

#include <SFML/Graphics.hpp>
#include "UIButton.hpp"
#include "UITextBox.hpp"

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
    static void styleSoftInput(UITextBox &input);
    static void stylePrimaryButton(UIButton &button);
    static void styleSuccessButton(UIButton &button);
    static void styleDangerButton(UIButton &button);
    static void styleCriticalButton(UIButton &button);
    static void styleSecondaryButton(UIButton &button);
    static void styleNeutralButton(UIButton &button);
    static void styleSelectedOptionButton(UIButton &button);
    static void styleMutedTimeSlotButton(UIButton &button);
};
