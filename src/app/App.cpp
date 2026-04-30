#include "App.hpp"

#include <fstream>
#include <optional>
#include "../core/Validator.hpp"
#include "../core/FileHandler.hpp"
#include "../helpers/ConversionHelper.hpp"
#include "../helpers/StringHelper.hpp"

static bool pathExists(const char* path) {
    std::ifstream fileStream(path, std::ios::binary);

    return fileStream.good();
}

static bool loadFontWithFallback(sf::Font& font, const char* rootPath, const char* buildPath) {
    if (pathExists(buildPath) && font.openFromFile(buildPath)) {
        return true;
    }

    if (pathExists(rootPath) && font.openFromFile(rootPath)) {
        return true;
    }

    return false;
}

void App::setupUI() {
    logoutButton = UIButton(regularFont, "Logout", sf::Vector2f(1100.f, 30.f), sf::Vector2f(130.f, 40.f));

    logoutButton.setFillColor(sf::Color(230, 80, 80));

    logoutButton.setOutlineColor(sf::Color(230, 80, 80));
    logoutButton.setTextColor(sf::Color::White);

    loginScreen.initialize(regularFont, boldFont);
    patientDash.initialize(regularFont, boldFont);
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
            return;
        }
        
        if (state == PATIENT_MENU) {
            patientDash.handleMouseClick(window);

            if (patientDash.consumeBookAppointmentRequest()) {
                Patient* patient;
                int doctorID;

                patient = reinterpret_cast<Patient*>(currentUser);
                doctorID = ConversionHelper::stringToInt(patientDash.getBookingDoctorIDText());

                try {
                    if (StringHelper::stringLength(patientDash.getBookingDoctorIDText()) < 1) {
                        patientDash.setStatus("Doctor ID is required.");
                    } else if (StringHelper::stringLength(patientDash.getBookingDateText()) < 1) {
                        patientDash.setStatus("Date is required.");
                    } else if (StringHelper::stringLength(patientDash.getBookingTimeText()) < 1) {
                        patientDash.setStatus("Time slot is required.");
                    } else {
                        system.bookAppointment(
                            patient,
                            doctorID,
                            patientDash.getBookingDateText(),
                            patientDash.getBookingTimeText()
                        );
                        patientDash.cancelBookingMode();
                        patientDash.setPatient(patient);
                        patientDash.setStatus("Appointment booked successfully.");
                    }
                } catch (const HospitalException& exception) {
                    patientDash.setStatus(exception.what());
                }
            }

            patientDash.clearClickStates();
        }
    }
}

void App::handleTextEntered(char32_t unicode) {
    if (state != LOGIN) {
        if (state == PATIENT_MENU) {
            patientDash.handleTextEntered(unicode);
        }
        return;
    }

    loginScreen.handleTextEntered(unicode);
}

void App::attemptLogin() {
    Person* user;
    Role selectedRole;

    selectedRole = loginScreen.getSelectedRole();
    user = system.login(loginScreen.getEnteredName(), loginScreen.getEnteredPassword(), "", selectedRole);

    if (user == nullptr) {
        loginScreen.setStatus("Login failed. Check ID or password.");
        return;
    }

    currentUser = user;
    if (selectedRole == ROLE_PATIENT) {
        state = PATIENT_MENU;
        patientDash.setPatient(reinterpret_cast<Patient*>(user));
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
    char successMsg[200];
    int i;

    name = loginScreen.getEnteredName();
    age = loginScreen.getEnteredAge();
    gender = loginScreen.getEnteredGender();
    contact = loginScreen.getEnteredContact();
    password = loginScreen.getEnteredSignupPassword();

    // Validate inputs
    if (StringHelper::stringLength(name) < 2) {
        loginScreen.setStatus("Name must be at least 2 characters");
        return;
    }
    if (age < 18 || age > 120) {
        loginScreen.setStatus("Age must be between 18 and 120");
        return;
    }
    if (StringHelper::stringLength(gender) < 1) {
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

    // Show success message with new patient ID
    successMsg[0] = '\0';
    StringHelper::stringCopy(successMsg, "New account created with ID: ", 200);
    i = StringHelper::stringLength(successMsg);
    ConversionHelper::intToString(newID, successMsg + i);
    
    loginScreen.setSignupMode(false);
    loginScreen.clearInputs();
    loginScreen.setStatus(successMsg);
}

void App::logout() {
    currentUser = nullptr;
    state = LOGIN;
    loginScreen.clearInputs();
    loginScreen.setStatus("Logged out.");
    patientDash.setPatient(nullptr);
}

void App::drawDashboard() {
    if (state == PATIENT_MENU) {
        patientDash.draw(window);
    } else {
        sf::Text title(boldFont, "", 30);

        if (state == DOCTOR_MENU) {
            title.setString("Doctor Dashboard");
        } else {
            title.setString("Admin Dashboard");
        }

        title.setPosition(sf::Vector2f(80.f, 34.f));
        title.setFillColor(sf::Color(44, 62, 80));

        window.draw(title);
    }
    
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
