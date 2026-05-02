#pragma once

#include <SFML/Graphics.hpp>

#include "../core/HospitalSystem.hpp"
#include "../ui/UIButton.hpp"
#include "../ui/LoginScreen.hpp"
#include "../ui/PatientDash.hpp"

class App
{
public:
    enum AppState
    {
        LOGIN,
        PATIENT_MENU,
        DOCTOR_MENU,
        ADMIN_MENU
    };

private:
    sf::RenderWindow window;
    HospitalSystem system;
    sf::Font regularFont;
    sf::Font boldFont;
    bool fontLoaded;

    AppState state;
    Person *currentUser;

    UIButton logoutButton;
    LoginScreen loginScreen;
    PatientDash patientDash;

    void setupUI();

    void processEvents();
    void handleMouseClick();
    void handleTextEntered(char32_t unicode);
    void attemptLogin();
    void attemptSignup();
    void logout();

    void drawDashboard();

public:
    App();
    ~App();

    void run();
};
