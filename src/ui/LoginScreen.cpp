#include "LoginScreen.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"

void LoginScreen::updateRoleLabel() {
    if (roleText == nullptr) {
        return;
    }

    if (selectedRole == ROLE_PATIENT) {
        roleText->setString("Role: Patient");
    } else if (selectedRole == ROLE_DOCTOR) {
        roleText->setString("Role: Doctor");
    } else {
        roleText->setString("Role: Admin");
    }
}

bool LoginScreen::validateSignupInputs(char* errorMessage) {
    const char* name;
    const char* ageStr;
    const char* gender;
    const char* contact;
    const char* password;
    int age;

    name = nameInput.getText();
    ageStr = ageInput.getText();
    gender = genderInput.getText();
    contact = contactInput.getText();
    password = signupPasswordInput.getText();

    if (StringHelper::stringLength(name) < 2) {
        StringHelper::stringCopy(errorMessage, "Name must be at least 2 characters", 200);
        return false;
    }

    age = ConversionHelper::toInt(ageStr);
    if (age < 18 || age > 120) {
        StringHelper::stringCopy(errorMessage, "Age must be between 18 and 120", 200);
        return false;
    }

    if (StringHelper::stringLength(gender) < 1) {
        StringHelper::stringCopy(errorMessage, "Gender cannot be empty", 200);
        return false;
    }

    if (!Validator::isValidContact(contact)) {
        StringHelper::stringCopy(errorMessage, "Contact must be 11 digits", 200);
        return false;
    }

    if (!Validator::isValidPassword(password)) {
        StringHelper::stringCopy(errorMessage, "Password must be at least 6 characters", 200);
        return false;
    }

    return true;
}

LoginScreen::LoginScreen() {
    titleText = nullptr;
    roleText = nullptr;
    nameLabel = nullptr;
    contactLabel = nullptr;
    passwordLabel = nullptr;
    statusText = nullptr;
    selectedRole = ROLE_PATIENT;
    loginRequested = false;
    isSignupMode = false;
    signupRequested = false;
    statusMessage[0] = '\0';
}

LoginScreen::~LoginScreen() {
    delete titleText;
    delete roleText;
    delete nameLabel;
    delete contactLabel;
    delete passwordLabel;
    delete statusText;
    delete ageLabel;
    delete genderLabel;
    delete signupPasswordLabel;
    titleText = nullptr;
    roleText = nullptr;
    nameLabel = nullptr;
    contactLabel = nullptr;
    passwordLabel = nullptr;
    statusText = nullptr;
    ageLabel = nullptr;
    genderLabel = nullptr;
    signupPasswordLabel = nullptr;
}

LoginScreen::LoginScreen(const LoginScreen& other) {
    int index;

    patientRoleButton = other.patientRoleButton;
    doctorRoleButton = other.doctorRoleButton;
    adminRoleButton = other.adminRoleButton;
    loginButton = other.loginButton;
    toggleModeButton = other.toggleModeButton;
    signupButton = other.signupButton;
    nameInput = other.nameInput;
    contactInput = other.contactInput;
    passwordInput = other.passwordInput;
    ageInput = other.ageInput;
    genderInput = other.genderInput;
    signupPasswordInput = other.signupPasswordInput;

    titleText = nullptr;
    roleText = nullptr;
    nameLabel = nullptr;
    contactLabel = nullptr;
    passwordLabel = nullptr;
    statusText = nullptr;
    ageLabel = nullptr;
    genderLabel = nullptr;
    signupPasswordLabel = nullptr;
    selectedRole = other.selectedRole;
    loginRequested = other.loginRequested;
    isSignupMode = other.isSignupMode;
    signupRequested = other.signupRequested;

    index = 0;
    while (other.statusMessage[index] != '\0' && index < 199) {
        statusMessage[index] = other.statusMessage[index];
        index++;
    }
    statusMessage[index] = '\0';
}

LoginScreen& LoginScreen::operator=(const LoginScreen& other) {
    int index;

    if (this != &other) {
        delete titleText;
        delete roleText;
        delete nameLabel;
        delete contactLabel;
        delete passwordLabel;
        delete statusText;
        delete ageLabel;
        delete genderLabel;
        delete signupPasswordLabel;

        patientRoleButton = other.patientRoleButton;
        doctorRoleButton = other.doctorRoleButton;
        adminRoleButton = other.adminRoleButton;
        loginButton = other.loginButton;
        toggleModeButton = other.toggleModeButton;
        signupButton = other.signupButton;
        nameInput = other.nameInput;
        contactInput = other.contactInput;
        passwordInput = other.passwordInput;
        ageInput = other.ageInput;
        genderInput = other.genderInput;
        signupPasswordInput = other.signupPasswordInput;

        titleText = nullptr;
        roleText = nullptr;
        nameLabel = nullptr;
        contactLabel = nullptr;
        passwordLabel = nullptr;
        statusText = nullptr;
        ageLabel = nullptr;
        genderLabel = nullptr;
        signupPasswordLabel = nullptr;
        selectedRole = other.selectedRole;
        loginRequested = other.loginRequested;
        isSignupMode = other.isSignupMode;
        signupRequested = other.signupRequested;

        index = 0;
        while (other.statusMessage[index] != '\0' && index < 199) {
            statusMessage[index] = other.statusMessage[index];
            index++;
        }
        statusMessage[index] = '\0';
    }

    return *this;
}

bool LoginScreen::initialize(const sf::Font& regularFont, const sf::Font& boldFont) {
    // Card background setup
    // Center card: say 640x540. Center it at 1280/2 = 640, 720/2 = 360.
    // Top-left of card = (640-320, 360-270) = (320, 90)
    float startX = 320.f;
    float startY = 90.f;
    
    cardBackground.setSize(sf::Vector2f(640.f, 540.f));
    cardBackground.setPosition(sf::Vector2f(startX, startY));
    cardBackground.setFillColor(sf::Color(255, 255, 255)); // Different white shade for the card itself
    cardBackground.setOutlineColor(sf::Color(220, 225, 230)); // Faint border
    cardBackground.setOutlineThickness(2.f);

    // Login UI setup
    // Base layout coordinates derived from the card's startX and startY.
    // Inner padding of 40px left/right
    float innerX = startX + 40.f;
    float row1Y = startY + 120.f;

    patientRoleButton = UIButton(regularFont, "Patient", sf::Vector2f(innerX, row1Y), sf::Vector2f(173.f, 46.f));
    doctorRoleButton = UIButton(regularFont, "Doctor", sf::Vector2f(innerX + 193.f, row1Y), sf::Vector2f(173.f, 46.f));
    adminRoleButton = UIButton(regularFont, "Admin", sf::Vector2f(innerX + 386.f, row1Y), sf::Vector2f(174.f, 46.f));
    
    float loginBtnY = startY + 360.f;
    loginButton = UIButton(boldFont, "Login", sf::Vector2f(innerX, loginBtnY), sf::Vector2f(560.f, 50.f));
    
    // Toggle Mode / Back button (will be moved Top-Left inside card)
    toggleModeButton = UIButton(regularFont, "Sign Up", sf::Vector2f(innerX, startY + 430.f), sf::Vector2f(560.f, 50.f));

    patientRoleButton.setFillColor(sf::Color(230, 235, 240));
    doctorRoleButton.setFillColor(sf::Color(230, 235, 240));
    adminRoleButton.setFillColor(sf::Color(230, 235, 240));
    loginButton.setFillColor(sf::Color(52, 152, 219));
    toggleModeButton.setFillColor(sf::Color(245, 247, 248)); // Subtle button style

    patientRoleButton.setOutlineColor(sf::Color(200, 205, 210));
    doctorRoleButton.setOutlineColor(sf::Color(200, 205, 210));
    adminRoleButton.setOutlineColor(sf::Color(200, 205, 210));
    loginButton.setOutlineColor(sf::Color(52, 152, 219));
    toggleModeButton.setOutlineColor(sf::Color(200, 205, 210));

    patientRoleButton.setTextColor(sf::Color(44, 62, 80));
    doctorRoleButton.setTextColor(sf::Color(44, 62, 80));
    adminRoleButton.setTextColor(sf::Color(44, 62, 80));
    loginButton.setTextColor(sf::Color::White);
    toggleModeButton.setTextColor(sf::Color(44, 62, 80));

    // Login form: Name, Contact, Password
    nameInput = UITextBox(regularFont, sf::Vector2f(innerX, startY + 210.f), sf::Vector2f(560.f, 40.f), 50);
    contactInput = UITextBox(regularFont, sf::Vector2f(innerX, startY + 280.f), sf::Vector2f(270.f, 40.f), 11);
    passwordInput = UITextBox(regularFont, sf::Vector2f(innerX + 290.f, startY + 280.f), sf::Vector2f(270.f, 40.f), 30);
    
    nameInput.setFillColor(sf::Color(250, 251, 252));
    contactInput.setFillColor(sf::Color(250, 251, 252));
    passwordInput.setFillColor(sf::Color(250, 251, 252));
    nameInput.setOutlineColor(sf::Color(200, 205, 210));
    contactInput.setOutlineColor(sf::Color(200, 205, 210));
    passwordInput.setOutlineColor(sf::Color(200, 205, 210));
    nameInput.setTextColor(sf::Color(44, 62, 80));
    contactInput.setTextColor(sf::Color(44, 62, 80));
    passwordInput.setTextColor(sf::Color(44, 62, 80));

    // Signup UI setup
    ageInput = UITextBox(regularFont, sf::Vector2f(innerX, startY + 280.f), sf::Vector2f(120.f, 40.f), 3);
    genderInput = UITextBox(regularFont, sf::Vector2f(innerX + 140.f, startY + 280.f), sf::Vector2f(120.f, 40.f), 10);
    signupPasswordInput = UITextBox(regularFont, sf::Vector2f(innerX + 290.f, startY + 280.f), sf::Vector2f(270.f, 40.f), 30);

    ageInput.setFillColor(sf::Color(250, 251, 252));
    genderInput.setFillColor(sf::Color(250, 251, 252));
    signupPasswordInput.setFillColor(sf::Color(250, 251, 252));

    ageInput.setOutlineColor(sf::Color(200, 205, 210));
    genderInput.setOutlineColor(sf::Color(200, 205, 210));
    signupPasswordInput.setOutlineColor(sf::Color(200, 205, 210));

    ageInput.setTextColor(sf::Color(44, 62, 80));
    genderInput.setTextColor(sf::Color(44, 62, 80));
    signupPasswordInput.setTextColor(sf::Color(44, 62, 80));

    signupButton = UIButton(boldFont, "Create Account", sf::Vector2f(innerX, startY + 360.f), sf::Vector2f(560.f, 50.f));
    signupButton.setFillColor(sf::Color(46, 204, 113));
    signupButton.setOutlineColor(sf::Color(46, 204, 113));
    signupButton.setTextColor(sf::Color::White);

    // Text labels setup
    titleText = new sf::Text(boldFont, "MediCore", 40);
    roleText = new sf::Text(regularFont, "Role: Patient", 20);
    nameLabel = new sf::Text(regularFont, "Full Name", 16);
    contactLabel = new sf::Text(regularFont, "Contact Number", 16);
    passwordLabel = new sf::Text(regularFont, "Password", 16);
    statusText = new sf::Text(regularFont, "", 16);
    ageLabel = new sf::Text(regularFont, "Age", 14);
    genderLabel = new sf::Text(regularFont, "Gender", 14);
    signupPasswordLabel = new sf::Text(regularFont, "Password", 14);

    // Login UI positions
    {
        sf::FloatRect titleBounds;
        float centeredTitleX;

        titleBounds = titleText->getLocalBounds();
        centeredTitleX = startX + (cardBackground.getSize().x * 0.5f) - (titleBounds.size.x * 0.5f) - titleBounds.position.x;
        titleText->setPosition(sf::Vector2f(centeredTitleX, startY + 30.f));
    }
    roleText->setPosition(sf::Vector2f(startX + 40.f, startY + 90.f));
    nameLabel->setPosition(sf::Vector2f(startX + 40.f, startY + 190.f));
    contactLabel->setPosition(sf::Vector2f(startX + 40.f, startY + 260.f));
    passwordLabel->setPosition(sf::Vector2f(startX + 330.f, startY + 260.f));
    statusText->setPosition(sf::Vector2f(startX + 40.f, startY + 500.f));

    // Signup UI positions
    ageLabel->setPosition(sf::Vector2f(innerX, startY + 260.f));
    genderLabel->setPosition(sf::Vector2f(innerX + 140.f, startY + 260.f));

    // Text colors
    titleText->setFillColor(sf::Color(44, 62, 80));
    roleText->setFillColor(sf::Color(127, 140, 141));
    nameLabel->setFillColor(sf::Color(127, 140, 141));
    contactLabel->setFillColor(sf::Color(127, 140, 141));
    passwordLabel->setFillColor(sf::Color(127, 140, 141));
    statusText->setFillColor(sf::Color(231, 76, 60)); // Red for errors typically
    ageLabel->setFillColor(sf::Color(127, 140, 141));
    genderLabel->setFillColor(sf::Color(127, 140, 141));
    signupPasswordLabel->setFillColor(sf::Color(127, 140, 141));

    selectedRole = ROLE_PATIENT;
    loginRequested = false;
    isSignupMode = false;
    signupRequested = false;
    setStatus("");

    return true;
}

void LoginScreen::handleMouseClick(sf::RenderWindow& window) {
    sf::Vector2f mouseWorldPosition;
    char errorBuffer[200];

    mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (isSignupMode) {
        // Signup mode: handle signup-specific inputs and buttons
        nameInput.handleMousePress(window);
        ageInput.handleMousePress(window);
        genderInput.handleMousePress(window);
        contactInput.handleMousePress(window);
        signupPasswordInput.handleMousePress(window);

        if (signupButton.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            if (validateSignupInputs(errorBuffer)) {
                signupRequested = true;
            } else {
                setStatus(errorBuffer);
            }
        }

        if (toggleModeButton.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            isSignupMode = false;
            clearInputs();
            setStatus("Back to login");
            
            float startX = 320.f;
            float startY = 90.f;
            float innerX = startX + 40.f;
            
            nameLabel->setPosition(sf::Vector2f(innerX, startY + 190.f));
            contactLabel->setPosition(sf::Vector2f(innerX, startY + 260.f));
            nameInput.setPosition(sf::Vector2f(innerX, startY + 210.f));
            contactInput.setPosition(sf::Vector2f(innerX, startY + 280.f));
            contactInput.setSize(sf::Vector2f(270.f, 40.f));
            
            toggleModeButton.setText("Sign Up");
            toggleModeButton.setPosition(sf::Vector2f(innerX, startY + 430.f));
            toggleModeButton.setSize(sf::Vector2f(560.f, 50.f));
        }
    } else {
        // Login mode: handle login-specific inputs and buttons
        nameInput.handleMousePress(window);
        contactInput.handleMousePress(window);
        passwordInput.handleMousePress(window);

        if (patientRoleButton.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            selectedRole = ROLE_PATIENT;
            setStatus("Selected role: Patient");
        }
        if (doctorRoleButton.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            selectedRole = ROLE_DOCTOR;
            setStatus("Selected role: Doctor");
        }
        if (adminRoleButton.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            selectedRole = ROLE_ADMIN;
            setStatus("Selected role: Admin");
        }

        if (loginButton.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            loginRequested = true;
        }

        if (toggleModeButton.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            isSignupMode = true;
            clearInputs();
            setStatus("Create a new patient account");

            float startX = 320.f;
            float startY = 90.f;
            float innerX = startX + 40.f;

            nameLabel->setPosition(sf::Vector2f(innerX, startY + 120.f));
            nameInput.setPosition(sf::Vector2f(innerX, startY + 140.f));
            
            ageLabel->setPosition(sf::Vector2f(innerX, startY + 200.f));
            ageInput.setPosition(sf::Vector2f(innerX, startY + 220.f));
            
            genderLabel->setPosition(sf::Vector2f(innerX + 140.f, startY + 200.f));
            genderInput.setPosition(sf::Vector2f(innerX + 140.f, startY + 220.f));
            
            contactLabel->setPosition(sf::Vector2f(innerX + 290.f, startY + 200.f));
            contactInput.setPosition(sf::Vector2f(innerX + 290.f, startY + 220.f));
            contactInput.setSize(sf::Vector2f(270.f, 40.f));

            signupPasswordLabel->setPosition(sf::Vector2f(innerX, startY + 280.f));
            signupPasswordInput.setPosition(sf::Vector2f(innerX, startY + 300.f));
            signupPasswordInput.setSize(sf::Vector2f(560.f, 40.f));
            
            toggleModeButton.setText("Back");
            toggleModeButton.setPosition(sf::Vector2f(innerX, startY + 30.f));
            toggleModeButton.setSize(sf::Vector2f(80.f, 40.f));
        }

        updateRoleLabel();
    }
}

void LoginScreen::handleTextEntered(char32_t unicode) {
    if (isSignupMode) {
        nameInput.handleTextEntered(unicode);
        ageInput.handleTextEntered(unicode);
        genderInput.handleTextEntered(unicode);
        contactInput.handleTextEntered(unicode);
        signupPasswordInput.handleTextEntered(unicode);
    } else {
        nameInput.handleTextEntered(unicode);
        contactInput.handleTextEntered(unicode);
        passwordInput.handleTextEntered(unicode);
    }
}

void LoginScreen::draw(sf::RenderWindow& window) const {
    window.draw(cardBackground);

    if (titleText != nullptr) {
        window.draw(*titleText);
    }
    if (statusText != nullptr) {
        window.draw(*statusText);
    }

    if (isSignupMode) {
        // Draw signup form
        if (nameLabel != nullptr) {
            window.draw(*nameLabel);
        }
        if (ageLabel != nullptr) {
            window.draw(*ageLabel);
        }
        if (genderLabel != nullptr) {
            window.draw(*genderLabel);
        }
        if (contactLabel != nullptr) {
            window.draw(*contactLabel);
        }
        if (signupPasswordLabel != nullptr) {
            window.draw(*signupPasswordLabel);
        }

        nameInput.draw(window);
        ageInput.draw(window);
        genderInput.draw(window);
        contactInput.draw(window);
        signupPasswordInput.draw(window);
        signupButton.draw(window);
        toggleModeButton.draw(window);
    } else {
        // Draw login form
        if (roleText != nullptr) {
            window.draw(*roleText);
        }
        if (nameLabel != nullptr) {
            window.draw(*nameLabel);
        }
        if (contactLabel != nullptr) {
            window.draw(*contactLabel);
        }
        if (passwordLabel != nullptr) {
            window.draw(*passwordLabel);
        }

        patientRoleButton.draw(window);
        doctorRoleButton.draw(window);
        adminRoleButton.draw(window);
        nameInput.draw(window);
        contactInput.draw(window);
        passwordInput.draw(window);
        loginButton.draw(window);
        toggleModeButton.draw(window);
    }
}

Role LoginScreen::getSelectedRole() const {
    return selectedRole;
}

const char* LoginScreen::getEnteredName() const {
    return nameInput.getText();
}

const char* LoginScreen::getEnteredContact() const {
    return contactInput.getText();
}

const char* LoginScreen::getEnteredPassword() const {
    return passwordInput.getText();
}

bool LoginScreen::consumeLoginRequest() {
    bool result;

    result = loginRequested;
    loginRequested = false;
    return result;
}

void LoginScreen::clearInputs() {
    nameInput.clear();
    contactInput.clear();
    passwordInput.clear();
    ageInput.clear();
    genderInput.clear();
    signupPasswordInput.clear();
}

void LoginScreen::setStatus(const char* message) {
    int index;

    if (message == nullptr) {
        statusMessage[0] = '\0';
    } else {
        index = 0;
        while (message[index] != '\0' && index < 199) {
            statusMessage[index] = message[index];
            index++;
        }
        statusMessage[index] = '\0';
    }

    if (statusText != nullptr) {
        statusText->setString(statusMessage);
    }
}

int LoginScreen::getEnteredAge() const {
    return ConversionHelper::toInt(ageInput.getText());
}

const char* LoginScreen::getEnteredGender() const {
    return genderInput.getText();
}

const char* LoginScreen::getEnteredSignupPassword() const {
    return signupPasswordInput.getText();
}

bool LoginScreen::consumeSignupRequest() {
    bool result;

    result = signupRequested;
    signupRequested = false;
    return result;
}

void LoginScreen::setSignupMode(bool signupMode) {
    isSignupMode = signupMode;
    clearInputs();
    if (signupMode) {
        setStatus("Create a new patient account");
    } else {
        setStatus("");
    }
}

bool LoginScreen::getIsSignupMode() const {
    return isSignupMode;
}
