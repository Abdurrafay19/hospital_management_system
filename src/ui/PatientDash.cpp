#include "PatientDash.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"

PatientDash::PatientDash()
    : patient(nullptr),
      bookAppointmentClicked(false), cancelAppointmentClicked(false), 
      viewAppointmentsClicked(false), viewMedicalRecordsClicked(false),
      viewBillsClicked(false), payBillClicked(false),
            topUpBalanceClicked(false), bookingMode(false),
    bookAppointmentRequested(false), bookingFocusedField(0) {
    titleText = nullptr;
    patientNameText = nullptr;
    balanceText = nullptr;
    statusText = nullptr;
        bookingTitleText = nullptr;
        bookingDoctorLabelText = nullptr;
        bookingDateLabelText = nullptr;
        bookingTimeLabelText = nullptr;
}

PatientDash::~PatientDash() {
    delete titleText;
    delete patientNameText;
    delete balanceText;
    delete statusText;
        delete bookingTitleText;
        delete bookingDoctorLabelText;
        delete bookingDateLabelText;
        delete bookingTimeLabelText;
    titleText = nullptr;
    patientNameText = nullptr;
    balanceText = nullptr;
    statusText = nullptr;
        bookingTitleText = nullptr;
        bookingDoctorLabelText = nullptr;
        bookingDateLabelText = nullptr;
        bookingTimeLabelText = nullptr;
}

bool PatientDash::initialize(const sf::Font& regularFontParam, const sf::Font& boldFontParam) {
    regularFont = regularFontParam;
    boldFont = boldFontParam;

    dashboardCard.setSize(sf::Vector2f(1100.f, 650.f));
    dashboardCard.setPosition(sf::Vector2f(90.f, 80.f));
    dashboardCard.setFillColor(sf::Color(255, 255, 255));
    dashboardCard.setOutlineColor(sf::Color(220, 225, 230));
    dashboardCard.setOutlineThickness(2.f);

    titleText = new sf::Text(boldFont, "Patient Dashboard", 32);
    patientNameText = new sf::Text(regularFont, "", 18);
    balanceText = new sf::Text(regularFont, "", 18);
    statusText = new sf::Text(regularFont, "", 16);
    bookingTitleText = new sf::Text(boldFont, "Book Appointment", 24);
    bookingDoctorLabelText = new sf::Text(regularFont, "Doctor ID", 16);
    bookingDateLabelText = new sf::Text(regularFont, "Date (dd-mm-yyyy)", 16);
    bookingTimeLabelText = new sf::Text(regularFont, "Time Slot", 16);

    titleText->setPosition(sf::Vector2f(110.f, 100.f));
    titleText->setFillColor(sf::Color(44, 62, 80));

    patientNameText->setPosition(sf::Vector2f(110.f, 150.f));
    patientNameText->setFillColor(sf::Color(127, 140, 141));

    balanceText->setPosition(sf::Vector2f(110.f, 180.f));
    balanceText->setFillColor(sf::Color(127, 140, 141));

    statusText->setPosition(sf::Vector2f(110.f, 600.f));
    statusText->setFillColor(sf::Color(231, 76, 60));

    bookingPanel.setSize(sf::Vector2f(500.f, 420.f));
    bookingPanel.setPosition(sf::Vector2f(390.f, 180.f));
    bookingPanel.setFillColor(sf::Color(250, 251, 252));
    bookingPanel.setOutlineColor(sf::Color(220, 225, 230));
    bookingPanel.setOutlineThickness(2.f);

    bookingTitleText->setPosition(sf::Vector2f(410.f, 195.f));
    bookingTitleText->setFillColor(sf::Color(44, 62, 80));
    bookingDoctorLabelText->setPosition(sf::Vector2f(410.f, 245.f));
    bookingDoctorLabelText->setFillColor(sf::Color(127, 140, 141));
    bookingDateLabelText->setPosition(sf::Vector2f(410.f, 315.f));
    bookingDateLabelText->setFillColor(sf::Color(127, 140, 141));
    bookingTimeLabelText->setPosition(sf::Vector2f(410.f, 385.f));
    bookingTimeLabelText->setFillColor(sf::Color(127, 140, 141));

    doctorIdInput.setFont(regularFont);
    doctorIdInput.setCapacity(50);
    doctorIdInput.setPosition(sf::Vector2f(410.f, 268.f));
    doctorIdInput.setSize(sf::Vector2f(460.f, 36.f));
    doctorIdInput.setFillColor(sf::Color::White);
    doctorIdInput.setOutlineColor(sf::Color(189, 195, 199));
    doctorIdInput.setTextColor(sf::Color(44, 62, 80));

    bookingDateInput.setFont(regularFont);
    bookingDateInput.setCapacity(50);
    bookingDateInput.setPosition(sf::Vector2f(410.f, 338.f));
    bookingDateInput.setSize(sf::Vector2f(460.f, 36.f));
    bookingDateInput.setFillColor(sf::Color::White);
    bookingDateInput.setOutlineColor(sf::Color(189, 195, 199));
    bookingDateInput.setTextColor(sf::Color(44, 62, 80));

    bookingTimeInput.setFont(regularFont);
    bookingTimeInput.setCapacity(50);
    bookingTimeInput.setPosition(sf::Vector2f(410.f, 408.f));
    bookingTimeInput.setSize(sf::Vector2f(460.f, 36.f));
    bookingTimeInput.setFillColor(sf::Color::White);
    bookingTimeInput.setOutlineColor(sf::Color(189, 195, 199));
    bookingTimeInput.setTextColor(sf::Color(44, 62, 80));

    int startX = 130;
    int startY = 230;
    int btnWidth = 300;
    int btnHeight = 45;
    int spacingX = 20;
    int spacingY = 15;

    bookAppointmentBtn.setFont(regularFont);
    bookAppointmentBtn.setText("Book Appointment");
    bookAppointmentBtn.setPosition(sf::Vector2f(startX, startY));
    bookAppointmentBtn.setSize(sf::Vector2f(btnWidth, btnHeight));

    cancelAppointmentBtn.setFont(regularFont);
    cancelAppointmentBtn.setText("Cancel Appointment");
    cancelAppointmentBtn.setPosition(sf::Vector2f(startX + btnWidth + spacingX, startY));
    cancelAppointmentBtn.setSize(sf::Vector2f(btnWidth, btnHeight));

    viewAppointmentsBtn.setFont(regularFont);
    viewAppointmentsBtn.setText("View Appointments");
    viewAppointmentsBtn.setPosition(sf::Vector2f(startX + (btnWidth + spacingX) * 2, startY));
    viewAppointmentsBtn.setSize(sf::Vector2f(btnWidth, btnHeight));

    viewMedicalRecordsBtn.setFont(regularFont);
    viewMedicalRecordsBtn.setText("Medical Records");
    viewMedicalRecordsBtn.setPosition(sf::Vector2f(startX, startY + btnHeight + spacingY));
    viewMedicalRecordsBtn.setSize(sf::Vector2f(btnWidth, btnHeight));

    viewBillsBtn.setFont(regularFont);
    viewBillsBtn.setText("View Bills");
    viewBillsBtn.setPosition(sf::Vector2f(startX + btnWidth + spacingX, startY + btnHeight + spacingY));
    viewBillsBtn.setSize(sf::Vector2f(btnWidth, btnHeight));

    payBillBtn.setFont(regularFont);
    payBillBtn.setText("Pay Bill");
    payBillBtn.setPosition(sf::Vector2f(startX + (btnWidth + spacingX) * 2, startY + btnHeight + spacingY));
    payBillBtn.setSize(sf::Vector2f(btnWidth, btnHeight));

    topUpBalanceBtn.setFont(regularFont);
    topUpBalanceBtn.setText("Top Up Balance");
    topUpBalanceBtn.setPosition(sf::Vector2f(startX, startY + (btnHeight + spacingY) * 2));
    topUpBalanceBtn.setSize(sf::Vector2f(btnWidth, btnHeight));

    sf::Color btnFill(52, 152, 219);
    sf::Color btnOutline(52, 152, 219);

    bookAppointmentBtn.setFillColor(btnFill);
    bookAppointmentBtn.setOutlineColor(btnOutline);
    bookAppointmentBtn.setTextColor(sf::Color::White);

    cancelAppointmentBtn.setFillColor(btnFill);
    cancelAppointmentBtn.setOutlineColor(btnOutline);
    cancelAppointmentBtn.setTextColor(sf::Color::White);

    viewAppointmentsBtn.setFillColor(btnFill);
    viewAppointmentsBtn.setOutlineColor(btnOutline);
    viewAppointmentsBtn.setTextColor(sf::Color::White);

    viewMedicalRecordsBtn.setFillColor(btnFill);
    viewMedicalRecordsBtn.setOutlineColor(btnOutline);
    viewMedicalRecordsBtn.setTextColor(sf::Color::White);

    viewBillsBtn.setFillColor(btnFill);
    viewBillsBtn.setOutlineColor(btnOutline);
    viewBillsBtn.setTextColor(sf::Color::White);

    payBillBtn.setFillColor(btnFill);
    payBillBtn.setOutlineColor(btnOutline);
    payBillBtn.setTextColor(sf::Color::White);

    topUpBalanceBtn.setFillColor(btnFill);
    topUpBalanceBtn.setOutlineColor(btnOutline);
    topUpBalanceBtn.setTextColor(sf::Color::White);

    confirmBookingBtn.setFont(regularFont);
    confirmBookingBtn.setText("Confirm");
    confirmBookingBtn.setPosition(sf::Vector2f(410.f, 470.f));
    confirmBookingBtn.setSize(sf::Vector2f(155.f, 40.f));
    confirmBookingBtn.setFillColor(sf::Color(46, 204, 113));
    confirmBookingBtn.setOutlineColor(sf::Color(46, 204, 113));
    confirmBookingBtn.setTextColor(sf::Color::White);

    cancelBookingBtn.setFont(regularFont);
    cancelBookingBtn.setText("Cancel");
    cancelBookingBtn.setPosition(sf::Vector2f(715.f, 470.f));
    cancelBookingBtn.setSize(sf::Vector2f(155.f, 40.f));
    cancelBookingBtn.setFillColor(sf::Color(231, 76, 60));
    cancelBookingBtn.setOutlineColor(sf::Color(231, 76, 60));
    cancelBookingBtn.setTextColor(sf::Color::White);
    
    return true;
}

void PatientDash::updateBookingFocus(int focusedField) {
    bookingFocusedField = focusedField;
    doctorIdInput.setActive(focusedField == 1);
    bookingDateInput.setActive(focusedField == 2);
    bookingTimeInput.setActive(focusedField == 3);
}

void PatientDash::setPatient(Patient* patientPtr) {
    patient = patientPtr;

    if (patient == nullptr) {
        cancelBookingMode();
        if (patientNameText != nullptr) {
            patientNameText->setString("");
        }
        if (balanceText != nullptr) {
            balanceText->setString("");
        }
        return;
    }
    
    char nameBuffer[100];
    char balanceBuffer[200];
    char balanceStr[100];
    int i;
    int j;

    StringHelper::stringCopy(nameBuffer, "Patient: ", 100);
    int nameLen = StringHelper::stringLength(nameBuffer);
    StringHelper::stringCopy(nameBuffer + nameLen, patient->getName(), 100 - nameLen);

    StringHelper::stringCopy(balanceBuffer, "Balance: PKR ", 200);
    i = 0;
    while (balanceBuffer[i] != '\0') {
        i++;
    }

    ConversionHelper::doubleToString(patient->getBalance(), balanceStr);
    j = 0;
    while (balanceStr[j] != '\0' && i < 199) {
        balanceBuffer[i] = balanceStr[j];
        i++;
        j++;
    }
    balanceBuffer[i] = '\0';

    if (patientNameText != nullptr) {
        patientNameText->setString(nameBuffer);
    }
    if (balanceText != nullptr) {
        balanceText->setString(balanceBuffer);
    }
}

void PatientDash::draw(sf::RenderWindow& window) const {
    window.draw(dashboardCard);
    
    if (titleText != nullptr) {
        window.draw(*titleText);
    }
    if (patientNameText != nullptr) {
        window.draw(*patientNameText);
    }
    if (balanceText != nullptr) {
        window.draw(*balanceText);
    }
    if (statusText != nullptr) {
        window.draw(*statusText);
    }
    
    bookAppointmentBtn.draw(window);
    cancelAppointmentBtn.draw(window);
    viewAppointmentsBtn.draw(window);
    viewMedicalRecordsBtn.draw(window);
    viewBillsBtn.draw(window);
    payBillBtn.draw(window);
    topUpBalanceBtn.draw(window);

    if (bookingMode) {
        window.draw(bookingPanel);
        if (bookingTitleText != nullptr) {
            window.draw(*bookingTitleText);
        }
        if (bookingDoctorLabelText != nullptr) {
            window.draw(*bookingDoctorLabelText);
        }
        if (bookingDateLabelText != nullptr) {
            window.draw(*bookingDateLabelText);
        }
        if (bookingTimeLabelText != nullptr) {
            window.draw(*bookingTimeLabelText);
        }

        doctorIdInput.draw(window);
        bookingDateInput.draw(window);
        bookingTimeInput.draw(window);
        confirmBookingBtn.draw(window);
        cancelBookingBtn.draw(window);
    }
}

void PatientDash::handleMouseClick(sf::RenderWindow& window) {
    if (bookingMode) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (doctorIdInput.contains(mouseWorldPosition)) {
            updateBookingFocus(1);
            return;
        }

        if (bookingDateInput.contains(mouseWorldPosition)) {
            updateBookingFocus(2);
            return;
        }

        if (bookingTimeInput.contains(mouseWorldPosition)) {
            updateBookingFocus(3);
            return;
        }

        if (confirmBookingBtn.getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            if (StringHelper::stringLength(doctorIdInput.getText()) < 1 ||
                StringHelper::stringLength(bookingDateInput.getText()) < 1 ||
                StringHelper::stringLength(bookingTimeInput.getText()) < 1) {
                setStatus("Fill doctor ID, date, and time slot.");
                return;
            }

            bookAppointmentRequested = true;
            return;
        }

        if (cancelBookingBtn.getShape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            cancelBookingMode();
            return;
        }

        return;
    }

    sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    if (bookAppointmentBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
        bookAppointmentClicked = true;
        startBookingMode();
    }
    if (cancelAppointmentBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
        cancelAppointmentClicked = true;
    }
    if (viewAppointmentsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
        viewAppointmentsClicked = true;
    }
    if (viewMedicalRecordsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
        viewMedicalRecordsClicked = true;
    }
    if (viewBillsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
        viewBillsClicked = true;
    }
    if (payBillBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
        payBillClicked = true;
    }
    if (topUpBalanceBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
        topUpBalanceClicked = true;
    }
}

void PatientDash::handleTextEntered(char32_t unicode) {
    if (!bookingMode) {
        return;
    }

    if (bookingFocusedField == 1) {
        doctorIdInput.handleTextEntered(unicode);
    } else if (bookingFocusedField == 2) {
        bookingDateInput.handleTextEntered(unicode);
    } else if (bookingFocusedField == 3) {
        bookingTimeInput.handleTextEntered(unicode);
    }
}

void PatientDash::startBookingMode() {
    bookingMode = true;
    bookAppointmentRequested = false;
    statusText->setString("Enter booking details.");

    doctorIdInput.clear();
    bookingDateInput.clear();
    bookingTimeInput.clear();
    updateBookingFocus(1);
}

void PatientDash::cancelBookingMode() {
    bookingMode = false;
    bookAppointmentRequested = false;
    bookingFocusedField = 0;
    doctorIdInput.clear();
    bookingDateInput.clear();
    bookingTimeInput.clear();
    doctorIdInput.setActive(false);
    bookingDateInput.setActive(false);
    bookingTimeInput.setActive(false);
}

bool PatientDash::isBookingMode() const {
    return bookingMode;
}

bool PatientDash::consumeBookAppointmentRequest() {
    if (!bookAppointmentRequested) {
        return false;
    }

    bookAppointmentRequested = false;
    return true;
}

const char* PatientDash::getBookingDoctorIDText() const {
    return doctorIdInput.getText();
}

const char* PatientDash::getBookingDateText() const {
    return bookingDateInput.getText();
}

const char* PatientDash::getBookingTimeText() const {
    return bookingTimeInput.getText();
}

bool PatientDash::isBookAppointmentClicked() const {
    return bookAppointmentClicked;
}

bool PatientDash::isCancelAppointmentClicked() const {
    return cancelAppointmentClicked;
}

bool PatientDash::isViewAppointmentsClicked() const {
    return viewAppointmentsClicked;
}

bool PatientDash::isViewMedicalRecordsClicked() const {
    return viewMedicalRecordsClicked;
}

bool PatientDash::isViewBillsClicked() const {
    return viewBillsClicked;
}

bool PatientDash::isPayBillClicked() const {
    return payBillClicked;
}

bool PatientDash::isTopUpBalanceClicked() const {
    return topUpBalanceClicked;
}

void PatientDash::clearClickStates() {
    bookAppointmentClicked = false;
    cancelAppointmentClicked = false;
    viewAppointmentsClicked = false;
    viewMedicalRecordsClicked = false;
    viewBillsClicked = false;
    payBillClicked = false;
    topUpBalanceClicked = false;
}

void PatientDash::setStatus(const char* message) {
    if (message != nullptr && statusText != nullptr) {
        statusText->setString(message);
    }
}
