#include "LoginScreen.hpp"
#include "../helpers/UIThemeHelper.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"

void LoginScreen::updateRoleLabel()
{
    // Deprecated - role label is now shown via nameLabel as ID field
}

bool LoginScreen::validateSignupInputs(char *errorMessage)
{
    const char *name;
    const char *ageStr;
    const char *contact;
    const char *password;
    int age;

    name = nameInput.getText();
    ageStr = ageInput.getText();
    contact = contactInput.getText();
    password = signupPasswordInput.getText();

    if (StringHelper::stringLength(name) < 2)
    {
        StringHelper::stringCopy(errorMessage, "Name must be at least 2 characters", 200);
        return false;
    }

    age = ConversionHelper::toInt(ageStr);
    if (age < 18 || age > 120)
    {
        StringHelper::stringCopy(errorMessage, "Age must be between 18 and 120", 200);
        return false;
    }

    if (StringHelper::stringLength(selectedGender) < 1)
    {
        StringHelper::stringCopy(errorMessage, "Please select a gender", 200);
        return false;
    }

    if (!Validator::isValidContact(contact))
    {
        StringHelper::stringCopy(errorMessage, "Contact must be 11 digits", 200);
        return false;
    }

    if (!Validator::isValidPassword(password))
    {
        StringHelper::stringCopy(errorMessage, "Password must be at least 6 characters", 200);
        return false;
    }

    return true;
}

LoginScreen::LoginScreen()
{
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
    selectedGender[0] = '\0';
}

LoginScreen::~LoginScreen()
{
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

LoginScreen::LoginScreen(const LoginScreen &other)
{
    int index;

    patientRoleButton = other.patientRoleButton;
    doctorRoleButton = other.doctorRoleButton;
    adminRoleButton = other.adminRoleButton;
    loginButton = other.loginButton;
    toggleModeButton = other.toggleModeButton;
    signupButton = other.signupButton;
    genderMButton = other.genderMButton;
    genderFButton = other.genderFButton;
    genderNAButton = other.genderNAButton;
    nameInput = other.nameInput;
    contactInput = other.contactInput;
    passwordInput = other.passwordInput;
    ageInput = other.ageInput;
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
    while (other.statusMessage[index] != '\0' && index < 199)
    {
        statusMessage[index] = other.statusMessage[index];
        index++;
    }
    statusMessage[index] = '\0';

    index = 0;
    while (other.selectedGender[index] != '\0' && index < 2)
    {
        selectedGender[index] = other.selectedGender[index];
        index++;
    }
    selectedGender[index] = '\0';
}

LoginScreen &LoginScreen::operator=(const LoginScreen &other)
{
    int index;

    if (this != &other)
    {
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
        genderMButton = other.genderMButton;
        genderFButton = other.genderFButton;
        genderNAButton = other.genderNAButton;
        nameInput = other.nameInput;
        contactInput = other.contactInput;
        passwordInput = other.passwordInput;
        ageInput = other.ageInput;
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
        while (other.statusMessage[index] != '\0' && index < 199)
        {
            statusMessage[index] = other.statusMessage[index];
            index++;
        }
        statusMessage[index] = '\0';

        index = 0;
        while (other.selectedGender[index] != '\0' && index < 2)
        {
            selectedGender[index] = other.selectedGender[index];
            index++;
        }
        selectedGender[index] = '\0';
    }

    return *this;
}

bool LoginScreen::initialize(const sf::Font &regularFont, const sf::Font &boldFont)
{
    // Card background setup
    // Center card: say 640x540. Center it at 1280/2 = 640, 720/2 = 360.
    // Top-left of card = (640-320, 360-270) = (320, 90)
    float startX = 320.f;
    float startY = 90.f;

    cardBackground.setSize(sf::Vector2f(640.f, 540.f));
    cardBackground.setPosition(sf::Vector2f(startX, startY));
    UIThemeHelper::styleDashboardCard(cardBackground);

    // Login UI setup
    // Base layout coordinates derived from the card's startX and startY.
    // Inner padding of 40px left/right
    float innerX = startX + 40.f;
    float row1Y = startY + 120.f;

    patientRoleButton = UIButton(regularFont, "Patient", sf::Vector2f(innerX, row1Y), sf::Vector2f(173.f, 46.f));
    doctorRoleButton = UIButton(regularFont, "Doctor", sf::Vector2f(innerX + 193.f, row1Y), sf::Vector2f(173.f, 46.f));
    adminRoleButton = UIButton(regularFont, "Admin", sf::Vector2f(innerX + 386.f, row1Y), sf::Vector2f(174.f, 46.f));
    UIThemeHelper::setButtonSizeSecondary(patientRoleButton);
    UIThemeHelper::setButtonSizeSecondary(doctorRoleButton);
    UIThemeHelper::setButtonSizeSecondary(adminRoleButton);

    float loginBtnY = startY + 360.f;
    loginButton = UIButton(boldFont, "Login", sf::Vector2f(innerX, loginBtnY), sf::Vector2f(560.f, 50.f));
    UIThemeHelper::setButtonSizeWide(loginButton);

    // Toggle Mode / Back button (will be moved Top-Left inside card)
    toggleModeButton = UIButton(regularFont, "Sign Up", sf::Vector2f(innerX, startY + 430.f), sf::Vector2f(560.f, 50.f));
    UIThemeHelper::setButtonSizeWide(toggleModeButton);

    // Patient is selected by default, so use darker gray
    UIThemeHelper::styleSelectedButton(patientRoleButton);
    UIThemeHelper::styleNeutralButton(doctorRoleButton);
    UIThemeHelper::styleNeutralButton(adminRoleButton);
    UIThemeHelper::stylePrimaryButton(loginButton);
    UIThemeHelper::styleNeutralButton(toggleModeButton);

    // Login form: ID and Password (Contact field reused for signup)
    nameInput = UITextBox(regularFont, sf::Vector2f(innerX, startY + 210.f), sf::Vector2f(560.f, 40.f), 50);
    passwordInput = UITextBox(regularFont, sf::Vector2f(innerX, startY + 280.f), sf::Vector2f(560.f, 40.f), 30);
    contactInput = UITextBox(regularFont, sf::Vector2f(innerX, startY + 280.f), sf::Vector2f(270.f, 40.f), 11);

    UIThemeHelper::styleInput(nameInput);
    UIThemeHelper::styleInput(passwordInput);
    UIThemeHelper::styleInput(contactInput);

    // Signup UI setup
    ageInput = UITextBox(regularFont, sf::Vector2f(innerX, startY + 280.f), sf::Vector2f(120.f, 40.f), 3);

    genderMButton = UIButton(regularFont, "M", sf::Vector2f(innerX + 140.f, startY + 280.f), sf::Vector2f(35.f, 40.f));
    genderFButton = UIButton(regularFont, "F", sf::Vector2f(innerX + 180.f, startY + 280.f), sf::Vector2f(35.f, 40.f));
    genderNAButton = UIButton(regularFont, "N/A", sf::Vector2f(innerX + 220.f, startY + 280.f), sf::Vector2f(50.f, 40.f));

    UIThemeHelper::styleNeutralButton(genderMButton);
    UIThemeHelper::styleNeutralButton(genderFButton);
    UIThemeHelper::styleNeutralButton(genderNAButton);

    signupPasswordInput = UITextBox(regularFont, sf::Vector2f(innerX + 290.f, startY + 280.f), sf::Vector2f(270.f, 40.f), 30);

    UIThemeHelper::styleInput(ageInput);
    UIThemeHelper::styleInput(signupPasswordInput);

    signupButton = UIButton(boldFont, "Create Account", sf::Vector2f(innerX, startY + 360.f), sf::Vector2f(560.f, 50.f));
    UIThemeHelper::setButtonSizeWide(signupButton);
    UIThemeHelper::styleSuccessButton(signupButton);

    // Text labels setup (grouped: creation + position + style)
    titleText = new sf::Text(boldFont, "MediCore", 40);
    UIThemeHelper::setTextSizeMainTitle(titleText);
    {
        sf::FloatRect titleBounds = titleText->getLocalBounds();
        float centeredTitleX = startX + (cardBackground.getSize().x * 0.5f) - (titleBounds.size.x * 0.5f) - titleBounds.position.x;
        titleText->setPosition(sf::Vector2f(centeredTitleX, startY + 30.f));
    }
    UIThemeHelper::styleTitleText(titleText);

    roleText = new sf::Text(regularFont, "Role: Patient", 20);
    UIThemeHelper::setTextSizeBody(roleText);
    roleText->setPosition(sf::Vector2f(startX + 40.f, startY + 90.f));
    UIThemeHelper::styleLabelText(roleText);

    nameLabel = new sf::Text(regularFont, "Patient ID", 16);
    UIThemeHelper::setTextSizeLabel(nameLabel);
    nameLabel->setPosition(sf::Vector2f(startX + 40.f, startY + 190.f));
    UIThemeHelper::styleLabelText(nameLabel);

    contactLabel = new sf::Text(regularFont, "Contact Number", 16);
    UIThemeHelper::setTextSizeLabel(contactLabel);
    contactLabel->setPosition(sf::Vector2f(startX + 40.f, startY + 260.f));
    UIThemeHelper::styleLabelText(contactLabel);

    passwordLabel = new sf::Text(regularFont, "Password", 16);
    UIThemeHelper::setTextSizeLabel(passwordLabel);
    passwordLabel->setPosition(sf::Vector2f(startX + 40.f, startY + 260.f));
    UIThemeHelper::styleLabelText(passwordLabel);

    statusText = new sf::Text(regularFont, "", 16);
    UIThemeHelper::setTextSizeSmall(statusText);
    statusText->setPosition(sf::Vector2f(startX + 40.f, startY + 500.f));
    UIThemeHelper::styleStatusText(statusText);

    // Signup UI labels
    ageLabel = new sf::Text(regularFont, "Age", 14);
    UIThemeHelper::setTextSizeBody(ageLabel);
    ageLabel->setPosition(sf::Vector2f(innerX, startY + 260.f));
    UIThemeHelper::styleLabelText(ageLabel);

    genderLabel = new sf::Text(regularFont, "Gender", 14);
    UIThemeHelper::setTextSizeBody(genderLabel);
    genderLabel->setPosition(sf::Vector2f(innerX + 140.f, startY + 260.f));
    UIThemeHelper::styleLabelText(genderLabel);

    signupPasswordLabel = new sf::Text(regularFont, "Password", 14);
    UIThemeHelper::setTextSizeBody(signupPasswordLabel);
    UIThemeHelper::styleLabelText(signupPasswordLabel);

    selectedRole = ROLE_PATIENT;
    loginRequested = false;
    isSignupMode = false;
    signupRequested = false;
    setStatus("");

    return true;
}

void LoginScreen::handleMouseClick(sf::RenderWindow &window)
{
    sf::Vector2f mouseWorldPosition;
    char errorBuffer[200];

    mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (isSignupMode)
    {
        // Signup mode: handle signup-specific inputs and buttons
        nameInput.handleMousePress(window);
        ageInput.handleMousePress(window);
        contactInput.handleMousePress(window);
        signupPasswordInput.handleMousePress(window);

        if (genderMButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            selectedGender[0] = 'M';
            selectedGender[1] = '\0';
            UIThemeHelper::styleSelectedButton(genderMButton);
            UIThemeHelper::styleNeutralButton(genderFButton);
            UIThemeHelper::styleNeutralButton(genderNAButton);
        }
        if (genderFButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            selectedGender[0] = 'F';
            selectedGender[1] = '\0';
            UIThemeHelper::styleNeutralButton(genderMButton);
            UIThemeHelper::styleSelectedButton(genderFButton);
            UIThemeHelper::styleNeutralButton(genderNAButton);
        }
        if (genderNAButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            selectedGender[0] = 'N';
            selectedGender[1] = '/';
            selectedGender[2] = 'A';
            selectedGender[3] = '\0';
            UIThemeHelper::styleNeutralButton(genderMButton);
            UIThemeHelper::styleNeutralButton(genderFButton);
            UIThemeHelper::styleSelectedButton(genderNAButton);
        }

        if (signupButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            if (validateSignupInputs(errorBuffer))
            {
                signupRequested = true;
            }
            else
            {
                setStatus(errorBuffer);
            }
        }

        if (toggleModeButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            isSignupMode = false;
            clearInputs();
            setStatus("Back to login");
            selectedGender[0] = '\0';

            float startX = 320.f;
            float startY = 90.f;
            float innerX = startX + 40.f;

            // Reset role buttons
            patientRoleButton.setPosition(sf::Vector2f(innerX, startY + 120.f));
            UIThemeHelper::setButtonSizeSecondary(patientRoleButton);
            doctorRoleButton.setPosition(sf::Vector2f(innerX + 190.f, startY + 120.f));
            UIThemeHelper::setButtonSizeSecondary(doctorRoleButton);
            adminRoleButton.setPosition(sf::Vector2f(innerX + 380.f, startY + 120.f));
            UIThemeHelper::setButtonSizeSecondary(adminRoleButton);

            // Reset Patient role as default
            selectedRole = ROLE_PATIENT;
            UIThemeHelper::styleSelectedButton(patientRoleButton);
            UIThemeHelper::styleNeutralButton(doctorRoleButton);
            UIThemeHelper::styleNeutralButton(adminRoleButton);

            // Reset login form labels and inputs
            nameLabel->setPosition(sf::Vector2f(innerX, startY + 190.f));
            nameLabel->setString("Patient ID");
            contactLabel->setPosition(sf::Vector2f(innerX, startY + 260.f));
            nameInput.setPosition(sf::Vector2f(innerX, startY + 210.f));
            contactInput.setPosition(sf::Vector2f(innerX, startY + 280.f));
            contactInput.setSize(sf::Vector2f(270.f, 40.f));
            passwordInput.setPosition(sf::Vector2f(innerX, startY + 280.f));
            passwordInput.setSize(sf::Vector2f(560.f, 40.f));

            toggleModeButton.setText("Sign Up");
            toggleModeButton.setPosition(sf::Vector2f(innerX, startY + 430.f));
            UIThemeHelper::setButtonSizeWide(toggleModeButton);
        }
    }
    else
    {
        // Login mode: handle login-specific inputs and buttons
        nameInput.handleMousePress(window);
        passwordInput.handleMousePress(window);

        if (patientRoleButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            selectedRole = ROLE_PATIENT;
            UIThemeHelper::styleSelectedButton(patientRoleButton);
            UIThemeHelper::styleNeutralButton(doctorRoleButton);
            UIThemeHelper::styleNeutralButton(adminRoleButton);
            nameLabel->setString("Patient ID");
            setStatus("Selected role: Patient");
        }
        if (doctorRoleButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            selectedRole = ROLE_DOCTOR;
            UIThemeHelper::styleNeutralButton(patientRoleButton);
            UIThemeHelper::styleSelectedButton(doctorRoleButton);
            UIThemeHelper::styleNeutralButton(adminRoleButton);
            nameLabel->setString("Doctor ID");
            setStatus("Selected role: Doctor");
        }
        if (adminRoleButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            selectedRole = ROLE_ADMIN;
            UIThemeHelper::styleNeutralButton(patientRoleButton);
            UIThemeHelper::styleNeutralButton(doctorRoleButton);
            UIThemeHelper::styleSelectedButton(adminRoleButton);
            nameLabel->setString("Admin ID");
            setStatus("Selected role: Admin");
        }

        if (loginButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            loginRequested = true;
        }

        if (toggleModeButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            isSignupMode = true;
            clearInputs();
            setStatus("Create a new patient account");

            float startX = 320.f;
            float startY = 90.f;
            float innerX = startX + 40.f;

            nameLabel->setString("Name");
            nameLabel->setPosition(sf::Vector2f(innerX, startY + 120.f));
            nameInput.setPosition(sf::Vector2f(innerX, startY + 140.f));

            ageLabel->setPosition(sf::Vector2f(innerX, startY + 200.f));
            ageInput.setPosition(sf::Vector2f(innerX, startY + 220.f));

            genderLabel->setPosition(sf::Vector2f(innerX + 140.f, startY + 200.f));
            genderMButton.setPosition(sf::Vector2f(innerX + 140.f, startY + 220.f));
            genderFButton.setPosition(sf::Vector2f(innerX + 180.f, startY + 220.f));
            genderNAButton.setPosition(sf::Vector2f(innerX + 220.f, startY + 220.f));

            contactLabel->setPosition(sf::Vector2f(innerX + 290.f, startY + 200.f));
            contactInput.setPosition(sf::Vector2f(innerX + 290.f, startY + 220.f));
            contactInput.setSize(sf::Vector2f(270.f, 40.f));

            signupPasswordLabel->setPosition(sf::Vector2f(innerX, startY + 280.f));
            signupPasswordInput.setPosition(sf::Vector2f(innerX, startY + 300.f));
            signupPasswordInput.setSize(sf::Vector2f(560.f, 40.f));

            toggleModeButton.setText("Back");
            toggleModeButton.setPosition(sf::Vector2f(innerX, startY + 30.f));
            UIThemeHelper::setButtonSizeTertiary(toggleModeButton);
        }
    }
}

void LoginScreen::handleTextEntered(char32_t unicode)
{
    if (isSignupMode)
    {
        nameInput.handleTextEntered(unicode);
        ageInput.handleTextEntered(unicode);
        contactInput.handleTextEntered(unicode);
        signupPasswordInput.handleTextEntered(unicode);
    }
    else
    {
        nameInput.handleTextEntered(unicode);
        passwordInput.handleTextEntered(unicode);
    }
}

void LoginScreen::draw(sf::RenderWindow &window) const
{
    window.draw(cardBackground);

    if (titleText != nullptr)
    {
        window.draw(*titleText);
    }
    if (statusText != nullptr)
    {
        window.draw(*statusText);
    }

    if (isSignupMode)
    {
        // Draw signup form
        if (nameLabel != nullptr)
        {
            window.draw(*nameLabel);
        }
        if (ageLabel != nullptr)
        {
            window.draw(*ageLabel);
        }
        if (genderLabel != nullptr)
        {
            window.draw(*genderLabel);
        }
        if (contactLabel != nullptr)
        {
            window.draw(*contactLabel);
        }
        if (signupPasswordLabel != nullptr)
        {
            window.draw(*signupPasswordLabel);
        }

        nameInput.draw(window);
        ageInput.draw(window);
        genderMButton.draw(window);
        genderFButton.draw(window);
        genderNAButton.draw(window);
        contactInput.draw(window);
        signupPasswordInput.draw(window);
        signupButton.draw(window);
        toggleModeButton.draw(window);
    }
    else
    {
        // Draw login form
        if (nameLabel != nullptr)
        {
            window.draw(*nameLabel);
        }
        if (passwordLabel != nullptr)
        {
            window.draw(*passwordLabel);
        }

        patientRoleButton.draw(window);
        doctorRoleButton.draw(window);
        adminRoleButton.draw(window);
        nameInput.draw(window);
        passwordInput.draw(window);
        loginButton.draw(window);
        if (selectedRole == ROLE_PATIENT)
        {
            toggleModeButton.draw(window);
        }
    }
}

Role LoginScreen::getSelectedRole() const
{
    return selectedRole;
}

const char *LoginScreen::getEnteredName() const
{
    return nameInput.getText();
}

const char *LoginScreen::getEnteredContact() const
{
    return contactInput.getText();
}

const char *LoginScreen::getEnteredPassword() const
{
    return passwordInput.getText();
}

bool LoginScreen::consumeLoginRequest()
{
    bool result;

    result = loginRequested;
    loginRequested = false;
    return result;
}

void LoginScreen::clearInputs()
{
    nameInput.clear();
    contactInput.clear();
    passwordInput.clear();
    ageInput.clear();
    selectedGender[0] = '\0';
    signupPasswordInput.clear();
}

void LoginScreen::setStatus(const char *message)
{
    int index;

    if (message == nullptr)
    {
        statusMessage[0] = '\0';
    }
    else
    {
        index = 0;
        while (message[index] != '\0' && index < 199)
        {
            statusMessage[index] = message[index];
            index++;
        }
        statusMessage[index] = '\0';
    }

    if (statusText != nullptr)
    {
        statusText->setString(statusMessage);
    }
}

int LoginScreen::getEnteredAge() const
{
    return ConversionHelper::toInt(ageInput.getText());
}

const char *LoginScreen::getEnteredGender() const
{
    return selectedGender;
}

const char *LoginScreen::getEnteredSignupPassword() const
{
    return signupPasswordInput.getText();
}

bool LoginScreen::consumeSignupRequest()
{
    bool result;

    result = signupRequested;
    signupRequested = false;
    return result;
}

void LoginScreen::setSignupMode(bool signupMode)
{
    isSignupMode = signupMode;
    clearInputs();

    if (signupMode)
    {
        setStatus("Create a new patient account");
    }
    else
    {
        // Transitioning back to login mode - reset all UI positions and states
        // Don't clear status here - let the caller set the appropriate message
        selectedGender[0] = '\0';

        float startX = 320.f;
        float startY = 90.f;
        float innerX = startX + 40.f;

        // Reset role buttons
        patientRoleButton.setPosition(sf::Vector2f(innerX, startY + 120.f));
        UIThemeHelper::setButtonSizeSecondary(patientRoleButton);
        doctorRoleButton.setPosition(sf::Vector2f(innerX + 190.f, startY + 120.f));
        UIThemeHelper::setButtonSizeSecondary(doctorRoleButton);
        adminRoleButton.setPosition(sf::Vector2f(innerX + 380.f, startY + 120.f));
        UIThemeHelper::setButtonSizeSecondary(adminRoleButton);

        // Reset Patient role as default
        selectedRole = ROLE_PATIENT;
        UIThemeHelper::styleSelectedButton(patientRoleButton);
        UIThemeHelper::styleNeutralButton(doctorRoleButton);
        UIThemeHelper::styleNeutralButton(adminRoleButton);

        // Reset login form labels and inputs
        nameLabel->setPosition(sf::Vector2f(innerX, startY + 190.f));
        nameLabel->setString("Patient ID");
        contactLabel->setPosition(sf::Vector2f(innerX, startY + 260.f));
        nameInput.setPosition(sf::Vector2f(innerX, startY + 210.f));
        contactInput.setPosition(sf::Vector2f(innerX, startY + 280.f));
        contactInput.setSize(sf::Vector2f(270.f, 40.f));
        passwordInput.setPosition(sf::Vector2f(innerX, startY + 280.f));
        passwordInput.setSize(sf::Vector2f(560.f, 40.f));

        toggleModeButton.setText("Sign Up");
        toggleModeButton.setPosition(sf::Vector2f(innerX, startY + 430.f));
        UIThemeHelper::setButtonSizeWide(toggleModeButton);
    }
}

bool LoginScreen::getIsSignupMode() const
{
    return isSignupMode;
}
