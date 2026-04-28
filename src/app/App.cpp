#include "App.hpp"

#include <optional>
#include "../core/Validator.hpp"
#include "../core/FileHandler.hpp"

static bool loadFontWithFallback(sf::Font& font, const char* rootPath, const char* buildPath) {
    if (font.openFromFile(rootPath)) {
        return true;
    }

    return font.openFromFile(buildPath);
}

void App::setupUI() {
    logoutButton = UIButton(regularFont, "Logout", sf::Vector2f(1100.f, 30.f), sf::Vector2f(130.f, 40.f));

    logoutButton.setFillColor(sf::Color(230, 80, 80));

    logoutButton.setOutlineColor(sf::Color(230, 80, 80));
    logoutButton.setTextColor(sf::Color::White);

    loginScreen.initialize(regularFont, boldFont);
}

void App::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (event->is<sf::Event::MouseButtonPressed>()) {
            handleMouseClick();
        }

        if (const sf::Event::TextEntered* textEvent = event->getIf<sf::Event::TextEntered>()) {
            handleTextEntered(textEvent->unicode);
        }
    }
}

void App::handleMouseClick() {
    if (state == LOGIN) {
        loginScreen.handleMouseClick(window);
        if (loginScreen.consumeLoginRequest()) {
            attemptLogin();
        }
        if (loginScreen.consumeSignupRequest()) {
            attemptSignup();
        }
    } else {
        sf::Vector2f mouseWorldPosition;

        mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (logoutButton.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            logout();
        }
    }
}

void App::handleTextEntered(char32_t unicode) {
    if (state != LOGIN) {
        return;
    }

    loginScreen.handleTextEntered(unicode);
}

void App::attemptLogin() {
    Person* user;
    Role selectedRole;

    selectedRole = loginScreen.getSelectedRole();
    user = system.login(loginScreen.getEnteredName(), loginScreen.getEnteredContact(), loginScreen.getEnteredPassword(), selectedRole);

    if (user == nullptr) {
        loginScreen.setStatus("Login failed. Check name/contact/password.");
        return;
    }

    currentUser = user;
    if (selectedRole == ROLE_PATIENT) {
        state = PATIENT_MENU;
        loginScreen.setStatus("Login successful. Welcome, patient.");
    } else if (selectedRole == ROLE_DOCTOR) {
        state = DOCTOR_MENU;
        loginScreen.setStatus("Login successful. Welcome, doctor.");
    } else {
        state = ADMIN_MENU;
        loginScreen.setStatus("Login successful. Welcome, admin.");
    }
}

void App::attemptSignup() {
    const char* name;
    int age;
    const char* gender;
    const char* contact;
    const char* password;
    int newID;
    Patient newPatient;
    char errorMsg[200];
    int nameLen;
    int genderLen;
    int contactLen;
    int passwordLen;

    name = loginScreen.getEnteredName();
    age = loginScreen.getEnteredAge();
    gender = loginScreen.getEnteredGender();
    contact = loginScreen.getEnteredContact();
    password = loginScreen.getEnteredSignupPassword();

    // Calculate string lengths
    nameLen = 0;
    while (name[nameLen] != '\0') nameLen++;
    genderLen = 0;
    while (gender[genderLen] != '\0') genderLen++;
    contactLen = 0;
    while (contact[contactLen] != '\0') contactLen++;
    passwordLen = 0;
    while (password[passwordLen] != '\0') passwordLen++;

    // Validate inputs
    if (nameLen < 2) {
        loginScreen.setStatus("Name must be at least 2 characters");
        return;
    }
    if (age < 18 || age > 120) {
        loginScreen.setStatus("Age must be between 18 and 120");
        return;
    }
    if (genderLen < 1) {
        loginScreen.setStatus("Gender cannot be empty");
        return;
    }
    if (!Validator::isValidContact(contact)) {
        loginScreen.setStatus("Contact must be 11 digits");
        return;
    }
    if (!Validator::isValidPassword(password)) {
        loginScreen.setStatus("Password must be at least 6 characters");
        return;
    }

    // Generate new patient ID
    newID = system.getNextPatientID();

    // Create new patient with initial balance of 0
    newPatient = Patient(newID, name, password, age, gender, contact, 0.0);

    // Save to file
    FileHandler::savePatient(newPatient, true);

    // Add to system's patient storage
    system.getPatients().add(newPatient);

    // Show success message and return to login
    loginScreen.setStatus("Account created successfully! Please login.");
    loginScreen.setSignupMode(false);
    loginScreen.clearInputs();
}

void App::logout() {
    currentUser = nullptr;
    state = LOGIN;
    loginScreen.clearInputs();
    loginScreen.setStatus("Logged out.");
}

void App::drawDashboard() {
    sf::Text title(boldFont, "", 30);

    if (state == PATIENT_MENU) {
        title.setString("Patient Dashboard");
    } else if (state == DOCTOR_MENU) {
        title.setString("Doctor Dashboard");
    } else {
        title.setString("Admin Dashboard");
    }

    title.setPosition(sf::Vector2f(80.f, 34.f));
    title.setFillColor(sf::Color(44, 62, 80));

    window.draw(title);
    logoutButton.draw(window);
}

App::App()
    : window(sf::VideoMode({1280, 720}), "MediCore") {
    fontLoaded = false;
    state = LOGIN;
    currentUser = nullptr;

    fontLoaded = loadFontWithFallback(regularFont,
                                      "assets/fonts/font.ttf",
                                      "../../../assets/fonts/font.ttf");

    if (fontLoaded) {
        fontLoaded = loadFontWithFallback(boldFont,
                                          "assets/fonts/font-bold.ttf",
                                          "../../../assets/fonts/font-bold.ttf");
    }

    if (fontLoaded) {
        setupUI();
    }
}

App::~App() {
}

void App::run() {
    while (window.isOpen()) {
        processEvents();

        window.clear(sf::Color(245, 247, 248));

        if (!fontLoaded) {
            window.display();
            continue;
        }

        if (state == LOGIN) {
            loginScreen.draw(window);
        } else {
            drawDashboard();
        }

        window.display();
    }
}
