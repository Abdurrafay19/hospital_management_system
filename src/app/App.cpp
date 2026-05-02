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

static int compareText(const char* left, const char* right) {
    int index;
    char leftChar;
    char rightChar;

    index = 0;
    while (left != nullptr && right != nullptr) {
        leftChar = left[index];
        rightChar = right[index];

        if (leftChar == '\0' && rightChar == '\0') {
            return 0;
        }
        if (leftChar == '\0') {
            return -1;
        }
        if (rightChar == '\0') {
            return 1;
        }
        if (leftChar < rightChar) {
            return -1;
        }
        if (leftChar > rightChar) {
            return 1;
        }

        index++;
    }

    if (left == nullptr && right == nullptr) {
        return 0;
    }
    if (left == nullptr) {
        return -1;
    }

    return 1;
}

static int parseDateComponent(const char* dateText, int startIndex, int endMarker) {
    int value;
    int index;

    value = 0;
    index = startIndex;
    while (dateText != nullptr && dateText[index] != '\0' && dateText[index] != endMarker) {
        if (dateText[index] >= '0' && dateText[index] <= '9') {
            value = value * 10 + (dateText[index] - '0');
        }
        index++;
    }

    return value;
}

static void parseDateText(const char* dateText, int& day, int& month, int& year) {
    int index;

    day = 0;
    month = 0;
    year = 0;

    if (dateText == nullptr) {
        return;
    }

    day = parseDateComponent(dateText, 0, '-');

    index = 0;
    while (dateText[index] != '\0' && dateText[index] != '-') {
        index++;
    }
    if (dateText[index] == '-') {
        index++;
    }

    month = parseDateComponent(dateText, index, '-');

    while (dateText[index] != '\0' && dateText[index] != '-') {
        index++;
    }
    if (dateText[index] == '-') {
        index++;
    }

    year = parseDateComponent(dateText, index, '\0');
}

static int compareAppointmentsByDateTime(const Appointment& left, const Appointment& right) {
    int leftDay;
    int leftMonth;
    int leftYear;
    int rightDay;
    int rightMonth;
    int rightYear;
    int result;

    parseDateText(left.getDate(), leftDay, leftMonth, leftYear);
    parseDateText(right.getDate(), rightDay, rightMonth, rightYear);

    if (leftYear < rightYear) {
        return -1;
    }
    if (leftYear > rightYear) {
        return 1;
    }

    if (leftMonth < rightMonth) {
        return -1;
    }
    if (leftMonth > rightMonth) {
        return 1;
    }

    if (leftDay < rightDay) {
        return -1;
    }
    if (leftDay > rightDay) {
        return 1;
    }

    result = compareText(left.getTimeSlot(), right.getTimeSlot());
    return result;
}

static void sortAppointmentsByDate(Storage<Appointment>& appointments) {
    Appointment* appointmentArray;
    int count;
    int pass;
    int index;
    Appointment temp;

    count = appointments.size();
    appointmentArray = appointments.getAll();

    for (pass = 0; pass < count - 1; pass++) {
        for (index = 0; index < count - 1 - pass; index++) {
            if (compareAppointmentsByDateTime(appointmentArray[index], appointmentArray[index + 1]) > 0) {
                temp = appointmentArray[index];
                appointmentArray[index] = appointmentArray[index + 1];
                appointmentArray[index + 1] = temp;
            }
        }
    }
}

static int comparePrescriptionsByDateDesc(const Prescription& left, const Prescription& right) {
    int leftDay;
    int leftMonth;
    int leftYear;
    int rightDay;
    int rightMonth;
    int rightYear;

    parseDateText(left.getDate(), leftDay, leftMonth, leftYear);
    parseDateText(right.getDate(), rightDay, rightMonth, rightYear);

    if (leftYear > rightYear) {
        return -1;
    }
    if (leftYear < rightYear) {
        return 1;
    }

    if (leftMonth > rightMonth) {
        return -1;
    }
    if (leftMonth < rightMonth) {
        return 1;
    }

    if (leftDay > rightDay) {
        return -1;
    }
    if (leftDay < rightDay) {
        return 1;
    }

    return 0;
}

static void sortPrescriptionsByDateDesc(Storage<Prescription>& prescriptions) {
    Prescription* prescriptionArray;
    int count;
    int pass;
    int index;
    Prescription temp;

    count = prescriptions.size();
    prescriptionArray = prescriptions.getAll();

    for (pass = 0; pass < count - 1; pass++) {
        for (index = 0; index < count - 1 - pass; index++) {
            if (comparePrescriptionsByDateDesc(prescriptionArray[index], prescriptionArray[index + 1]) > 0) {
                temp = prescriptionArray[index];
                prescriptionArray[index] = prescriptionArray[index + 1];
                prescriptionArray[index + 1] = temp;
            }
        }
    }
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

            // Handle specialization search
            if (patientDash.consumeSpecializationSearchRequest()) {
                try {
                    Storage<Doctor>* foundDoctors;
                    foundDoctors = system.getDoctorsBySpecialization(patientDash.getSpecializationText());
                    
                    if (foundDoctors == nullptr || foundDoctors->size() == 0) {
                        patientDash.setDialogStatus("No doctors available for that specialization.");
                        if (foundDoctors != nullptr) {
                            delete foundDoctors;
                        }
                    } else {
                        patientDash.setFilteredDoctors(foundDoctors);
                        patientDash.advanceBookingStep();
                    }
                } catch (const HospitalException& exception) {
                    patientDash.setDialogStatus(exception.what());
                }
            }

            if (patientDash.isCancelAppointmentClicked()) {
                Patient* patient;
                Storage<Appointment>* pendingAppointments;
                Appointment* appointmentList;
                int i;

                patient = reinterpret_cast<Patient*>(currentUser);
                pendingAppointments = new Storage<Appointment>();
                appointmentList = system.getAppointments().getAll();

                for (i = 0; i < system.getAppointments().size(); i++) {
                    if (appointmentList[i].getPatientID() == patient->getID() && StringHelper::textEquals(appointmentList[i].getStatus(), "pending")) {
                        pendingAppointments->add(appointmentList[i]);
                    }
                }

                if (pendingAppointments->size() == 0) {
                    delete pendingAppointments;
                    patientDash.setStatus("You have no pending appointments.");
                } else {
                    patientDash.setPendingAppointments(pendingAppointments, &system.getDoctors());
                    patientDash.startCancelAppointmentMode();
                }
            }

            if (patientDash.isViewAppointmentsClicked()) {
                Patient* patient;
                Storage<Appointment>* patientAppointments;
                Appointment* appointmentList;
                int i;

                patient = reinterpret_cast<Patient*>(currentUser);
                patientAppointments = new Storage<Appointment>();
                appointmentList = system.getAppointments().getAll();

                for (i = 0; i < system.getAppointments().size(); i++) {
                    if (appointmentList[i].getPatientID() == patient->getID()) {
                        patientAppointments->add(appointmentList[i]);
                    }
                }

                if (patientAppointments->size() == 0) {
                    delete patientAppointments;
                    patientDash.setStatus("No appointments found.");
                } else {
                    sortAppointmentsByDate(*patientAppointments);
                    patientDash.setViewedAppointments(patientAppointments, &system.getDoctors());
                    patientDash.startViewAppointmentsMode();
                }
            }

            if (patientDash.isViewMedicalRecordsClicked()) {
                Patient* patient;
                Storage<Prescription>* patientRecords;
                Prescription* recordList;
                int i;

                patient = reinterpret_cast<Patient*>(currentUser);
                patientRecords = new Storage<Prescription>();
                recordList = system.getPrescriptions().getAll();

                for (i = 0; i < system.getPrescriptions().size(); i++) {
                    if (recordList[i].getPatientID() == patient->getID()) {
                        patientRecords->add(recordList[i]);
                    }
                }

                if (patientRecords->size() == 0) {
                    delete patientRecords;
                    patientDash.setStatus("No medical records found.");
                } else {
                    sortPrescriptionsByDateDesc(*patientRecords);
                    patientDash.setViewedMedicalRecords(patientRecords, &system.getDoctors());
                    patientDash.startViewMedicalRecordsMode();
                }
            }

            if (patientDash.isViewBillsClicked()) {
                Patient* patient;
                Storage<Bill>* patientBills;
                Bill* billList;
                int i;

                patient = reinterpret_cast<Patient*>(currentUser);
                patientBills = new Storage<Bill>();
                billList = system.getBills().getAll();

                for (i = 0; i < system.getBills().size(); i++) {
                    if (billList[i].getPatientID() == patient->getID()) {
                        patientBills->add(billList[i]);
                    }
                }

                if (patientBills->size() == 0) {
                    delete patientBills;
                    patientDash.setStatus("No bills found.");
                } else {
                    patientDash.setViewedBills(patientBills);
                    patientDash.startViewBillsMode();
                }
            }

            if (patientDash.consumeCancelAppointmentRequest()) {
                Patient* patient;
                int appointmentID;
                double refundedFee;
                char feeBuffer[32];
                char successMessage[200];
                int messageLength;

                patient = reinterpret_cast<Patient*>(currentUser);
                appointmentID = ConversionHelper::toInt(patientDash.getCancelAppointmentIDText());

                try {
                    refundedFee = system.cancelAppointment(patient, appointmentID);
                    patientDash.closeCancelAppointmentMode();
                    patientDash.setPatient(patient);

                    successMessage[0] = '\0';
                    StringHelper::stringCopy(successMessage, "Appointment cancelled. PKR ", 200);
                    messageLength = StringHelper::stringLength(successMessage);
                    ConversionHelper::doubleToString(refundedFee, feeBuffer);
                    StringHelper::stringCopy(successMessage + messageLength, feeBuffer, 200 - messageLength);
                    messageLength = StringHelper::stringLength(successMessage);
                    StringHelper::stringCopy(successMessage + messageLength, " refunded to your balance.", 200 - messageLength);
                    patientDash.setStatus(successMessage);
                } catch (const HospitalException& exception) {
                    patientDash.closeCancelAppointmentMode();
                    patientDash.setStatus(exception.what());
                }
            }

            // Handle booking confirmation
            if (patientDash.consumeBookAppointmentRequest()) {
                Patient* patient;
                int doctorID;

                patient = reinterpret_cast<Patient*>(currentUser);
                doctorID = patientDash.getSelectedDoctorID();

                try {
                    if (doctorID < 1) {
                        patientDash.setDialogStatus("Doctor ID is invalid.");
                    } else if (StringHelper::stringLength(patientDash.getBookingDateText()) < 1) {
                        patientDash.setDialogStatus("Date is required.");
                    } else if (StringHelper::stringLength(patientDash.getBookingTimeText()) < 1) {
                        patientDash.setDialogStatus("Time slot is required.");
                    } else {
                        system.bookAppointment(
                            patient,
                            doctorID,
                            patientDash.getBookingDateText(),
                            patientDash.getBookingTimeText()
                        );
                        patientDash.setDialogStatus("Appointment booked successfully!");
                        patientDash.cancelBookingMode();
                        patientDash.setPatient(patient);
                    }
                } catch (const HospitalException& exception) {
                    patientDash.setDialogStatus(exception.what());
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
