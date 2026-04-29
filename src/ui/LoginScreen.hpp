#pragma once

#include <SFML/Graphics.hpp>

#include "../core/HospitalSystem.hpp"
#include "UIButton.hpp"
#include "UITextBox.hpp"
#include "../core/Validator.hpp"
#include "../core/FileHandler.hpp"

class LoginScreen {
private:
    // Login UI
    sf::RectangleShape cardBackground;
    UIButton patientRoleButton;
    UIButton doctorRoleButton;
    UIButton adminRoleButton;
    UIButton loginButton;
    UIButton toggleModeButton;

    UITextBox nameInput;
    UITextBox contactInput;
    UITextBox passwordInput;

    sf::Text* titleText;
    sf::Text* roleText;
    sf::Text* nameLabel;
    sf::Text* contactLabel;
    sf::Text* passwordLabel;
    sf::Text* statusText;

    // Signup UI
    UIButton signupButton;
    UIButton genderMButton;
    UIButton genderFButton;
    UIButton genderNAButton;
    UITextBox ageInput;
    UITextBox signupPasswordInput;

    sf::Text* ageLabel;
    sf::Text* genderLabel;
    sf::Text* signupPasswordLabel;

    char selectedGender[4];

    Role selectedRole;
    bool loginRequested;
    bool isSignupMode;
    bool signupRequested;

    char statusMessage[200];

    void updateRoleLabel();
    bool validateSignupInputs(char* errorMessage);

public:
    LoginScreen();
    ~LoginScreen();

    LoginScreen(const LoginScreen& other);
    LoginScreen& operator=(const LoginScreen& other);

    bool initialize(const sf::Font& regularFont, const sf::Font& boldFont);

    void handleMouseClick(sf::RenderWindow& window);
    void handleTextEntered(char32_t unicode);
    void draw(sf::RenderWindow& window) const;

    Role getSelectedRole() const;
    const char* getEnteredName() const;
    const char* getEnteredContact() const;
    const char* getEnteredPassword() const;
    bool consumeLoginRequest();

    int getEnteredAge() const;
    const char* getEnteredGender() const;
    const char* getEnteredSignupPassword() const;
    bool consumeSignupRequest();

    void clearInputs();
    void setStatus(const char* message);
    void setSignupMode(bool signupMode);
    bool getIsSignupMode() const;
};
