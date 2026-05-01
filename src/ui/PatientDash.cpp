#include "PatientDash.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"

PatientDash::PatientDash()
    : patient(nullptr),
      bookAppointmentClicked(false), cancelAppointmentClicked(false), 
      viewAppointmentsClicked(false), viewMedicalRecordsClicked(false),
      viewBillsClicked(false), payBillClicked(false),
      topUpBalanceClicked(false), bookingMode(false),
      bookAppointmentRequested(false), specializationSearchRequested(false),
      bookingFocusedField(0),
      currentBookingStep(STEP_SPECIALIZATION), doctorListCount(0),
      selectedDoctorIndex(-1), dateFailureCount(0), selectedTimeSlotIndex(-1),
      filteredDoctors(nullptr) {
    titleText = nullptr;
    patientNameText = nullptr;
    balanceText = nullptr;
    statusText = nullptr;
    bookingTitleText = nullptr;
    bookingStepIndicatorText = nullptr;
    bookingDialogStatusText = nullptr;
    specializationLabelText = nullptr;
    doctorListLabelText = nullptr;
    dateInputLabelText = nullptr;
    timeSlotsLabelText = nullptr;
    timeSlotDisplayText = nullptr;
    
    int i;
    for (i = 0; i < 20; i++) {
        doctorListText[i] = nullptr;
    }
    
    selectedSpecialization[0] = '\0';
    selectedDoctorID = -1;
    selectedDate[0] = '\0';
    selectedTimeSlot[0] = '\0';
}

PatientDash::~PatientDash() {
    delete titleText;
    delete patientNameText;
    delete balanceText;
    delete statusText;
    delete bookingTitleText;
    delete bookingStepIndicatorText;
    delete bookingDialogStatusText;
    delete specializationLabelText;
    delete doctorListLabelText;
    delete dateInputLabelText;
    delete timeSlotsLabelText;
    delete timeSlotDisplayText;
    
    int i;
    for (i = 0; i < 20; i++) {
        delete doctorListText[i];
        doctorListText[i] = nullptr;
    }
    
    if (filteredDoctors != nullptr) {
        delete filteredDoctors;
        filteredDoctors = nullptr;
    }
    
    titleText = nullptr;
    patientNameText = nullptr;
    balanceText = nullptr;
    statusText = nullptr;
    bookingTitleText = nullptr;
    bookingStepIndicatorText = nullptr;
    bookingDialogStatusText = nullptr;
    specializationLabelText = nullptr;
    doctorListLabelText = nullptr;
    dateInputLabelText = nullptr;
    timeSlotsLabelText = nullptr;
    timeSlotDisplayText = nullptr;
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
    specializationLabelText = new sf::Text(regularFont, "Specialization:", 16);
    doctorListLabelText = new sf::Text(regularFont, "Available Doctors:", 16);
    dateInputLabelText = new sf::Text(regularFont, "Date (DD-MM-YYYY):", 16);
    timeSlotsLabelText = new sf::Text(regularFont, "Available Time Slots:", 16);
    timeSlotDisplayText = new sf::Text(regularFont, "", 14);
    bookingStepIndicatorText = new sf::Text(regularFont, "Step 1 of 5", 14);
    bookingDialogStatusText = new sf::Text(regularFont, "", 13);

    titleText->setPosition(sf::Vector2f(110.f, 100.f));
    titleText->setFillColor(sf::Color(44, 62, 80));

    patientNameText->setPosition(sf::Vector2f(110.f, 150.f));
    patientNameText->setFillColor(sf::Color(127, 140, 141));

    balanceText->setPosition(sf::Vector2f(110.f, 180.f));
    balanceText->setFillColor(sf::Color(127, 140, 141));

    statusText->setPosition(sf::Vector2f(110.f, 600.f));
    statusText->setFillColor(sf::Color(231, 76, 60));

    // Expand booking panel to 900x550 for multi-step booking
    bookingPanel.setSize(sf::Vector2f(900.f, 550.f));
    bookingPanel.setPosition(sf::Vector2f(200.f, 130.f));
    bookingPanel.setFillColor(sf::Color(250, 251, 252));
    bookingPanel.setOutlineColor(sf::Color(220, 225, 230));
    bookingPanel.setOutlineThickness(2.f);

    bookingTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    bookingTitleText->setFillColor(sf::Color(44, 62, 80));

    bookingStepIndicatorText->setPosition(sf::Vector2f(820.f, 153.f));
    bookingStepIndicatorText->setFillColor(sf::Color(149, 165, 166));

    bookingDialogStatusText->setPosition(sf::Vector2f(220.f, 467.f));
    bookingDialogStatusText->setFillColor(sf::Color(192, 57, 43));

    // Step 1: Specialization
    specializationLabelText->setPosition(sf::Vector2f(220.f, 210.f));
    specializationLabelText->setFillColor(sf::Color(127, 140, 141));
    
    specializationInput.setFont(regularFont);
    specializationInput.setCapacity(50);
    specializationInput.setPosition(sf::Vector2f(220.f, 235.f));
    specializationInput.setSize(sf::Vector2f(400.f, 36.f));
    specializationInput.setFillColor(sf::Color::White);
    specializationInput.setOutlineColor(sf::Color(189, 195, 199));
    specializationInput.setTextColor(sf::Color(44, 62, 80));

    searchDoctorsBtn.setFont(regularFont);
    searchDoctorsBtn.setText("Search");
    searchDoctorsBtn.setPosition(sf::Vector2f(640.f, 235.f));
    searchDoctorsBtn.setSize(sf::Vector2f(120.f, 36.f));
    searchDoctorsBtn.setFillColor(sf::Color(52, 152, 219));
    searchDoctorsBtn.setOutlineColor(sf::Color(52, 152, 219));
    searchDoctorsBtn.setTextColor(sf::Color::White);

    // Step 2: Doctor Selection
    doctorListLabelText->setPosition(sf::Vector2f(220.f, 280.f));
    doctorListLabelText->setFillColor(sf::Color(127, 140, 141));

    int i;
    for (i = 0; i < 20; i++) {
        doctorListText[i] = new sf::Text(regularFont, "", 14);
        doctorListText[i]->setPosition(sf::Vector2f(220.f, 305.f + i * 22.f));
        doctorListText[i]->setFillColor(sf::Color(44, 62, 80));
    }

    selectDoctorBtn.setFont(regularFont);
    selectDoctorBtn.setText("Select Doctor");
    selectDoctorBtn.setPosition(sf::Vector2f(220.f, 300.f));
    selectDoctorBtn.setSize(sf::Vector2f(150.f, 36.f));
    selectDoctorBtn.setFillColor(sf::Color(52, 152, 219));
    selectDoctorBtn.setOutlineColor(sf::Color(52, 152, 219));
    selectDoctorBtn.setTextColor(sf::Color::White);

    // Step 3: Date Input
    dateInputLabelText->setPosition(sf::Vector2f(220.f, 280.f));
    dateInputLabelText->setFillColor(sf::Color(127, 140, 141));

    dateInput.setFont(regularFont);
    dateInput.setCapacity(20);
    dateInput.setPosition(sf::Vector2f(220.f, 305.f));
    dateInput.setSize(sf::Vector2f(300.f, 36.f));
    dateInput.setFillColor(sf::Color::White);
    dateInput.setOutlineColor(sf::Color(189, 195, 199));
    dateInput.setTextColor(sf::Color(44, 62, 80));

    confirmDateBtn.setFont(regularFont);
    confirmDateBtn.setText("Confirm Date");
    confirmDateBtn.setPosition(sf::Vector2f(540.f, 305.f));
    confirmDateBtn.setSize(sf::Vector2f(120.f, 36.f));
    confirmDateBtn.setFillColor(sf::Color(52, 152, 219));
    confirmDateBtn.setOutlineColor(sf::Color(52, 152, 219));
    confirmDateBtn.setTextColor(sf::Color::White);

    // Step 4: Time Slots
    timeSlotsLabelText->setPosition(sf::Vector2f(220.f, 280.f));
    timeSlotsLabelText->setFillColor(sf::Color(127, 140, 141));

    timeSlotDisplayText->setPosition(sf::Vector2f(220.f, 305.f));
    timeSlotDisplayText->setFillColor(sf::Color(44, 62, 80));

    const char* timeSlots[] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};
    int j;
    for (i = 0; i < 8; i++) {
        timeSlotButtons[i].setFont(regularFont);
        timeSlotButtons[i].setText(timeSlots[i]);
        j = i % 4;
        int row = i / 4;
        timeSlotButtons[i].setPosition(sf::Vector2f(220.f + j * 150.f, 305.f + row * 50.f));
        timeSlotButtons[i].setSize(sf::Vector2f(130.f, 40.f));
        timeSlotButtons[i].setFillColor(sf::Color(189, 195, 199));
        timeSlotButtons[i].setOutlineColor(sf::Color(189, 195, 199));
        timeSlotButtons[i].setTextColor(sf::Color::White);
    }

    // Step 5: Confirm
    confirmBookingBtn.setFont(regularFont);
    confirmBookingBtn.setText("Confirm Booking");
    confirmBookingBtn.setPosition(sf::Vector2f(720.f, 510.f));
    confirmBookingBtn.setSize(sf::Vector2f(160.f, 38.f));
    confirmBookingBtn.setFillColor(sf::Color(46, 204, 113));
    confirmBookingBtn.setOutlineColor(sf::Color(46, 204, 113));
    confirmBookingBtn.setTextColor(sf::Color::White);

    cancelBookingBtn.setFont(regularFont);
    cancelBookingBtn.setText("Cancel");
    cancelBookingBtn.setPosition(sf::Vector2f(890.f, 510.f));
    cancelBookingBtn.setSize(sf::Vector2f(90.f, 38.f));
    cancelBookingBtn.setFillColor(sf::Color(231, 76, 60));
    cancelBookingBtn.setOutlineColor(sf::Color(231, 76, 60));
    cancelBookingBtn.setTextColor(sf::Color::White);

    // Previous/Next buttons
    previousStepBtn.setFont(regularFont);
    previousStepBtn.setText("< Previous");
    previousStepBtn.setPosition(sf::Vector2f(220.f, 510.f));
    previousStepBtn.setSize(sf::Vector2f(90.f, 38.f));
    previousStepBtn.setFillColor(sf::Color(149, 165, 166));
    previousStepBtn.setOutlineColor(sf::Color(149, 165, 166));
    previousStepBtn.setTextColor(sf::Color::White);

    nextStepBtn.setFont(regularFont);
    nextStepBtn.setText("Next >");
    nextStepBtn.setPosition(sf::Vector2f(320.f, 510.f));
    nextStepBtn.setSize(sf::Vector2f(90.f, 38.f));
    nextStepBtn.setFillColor(sf::Color(149, 165, 166));
    nextStepBtn.setOutlineColor(sf::Color(149, 165, 166));
    nextStepBtn.setTextColor(sf::Color::White);

    // Dashboard buttons
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
    bookAppointmentBtn.setFillColor(sf::Color(52, 152, 219));
    bookAppointmentBtn.setOutlineColor(sf::Color(52, 152, 219));
    bookAppointmentBtn.setTextColor(sf::Color::White);

    cancelAppointmentBtn.setFont(regularFont);
    cancelAppointmentBtn.setText("Cancel Appointment");
    cancelAppointmentBtn.setPosition(sf::Vector2f(startX + btnWidth + spacingX, startY));
    cancelAppointmentBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    cancelAppointmentBtn.setFillColor(sf::Color(52, 152, 219));
    cancelAppointmentBtn.setOutlineColor(sf::Color(52, 152, 219));
    cancelAppointmentBtn.setTextColor(sf::Color::White);

    viewAppointmentsBtn.setFont(regularFont);
    viewAppointmentsBtn.setText("View Appointments");
    viewAppointmentsBtn.setPosition(sf::Vector2f(startX + (btnWidth + spacingX) * 2, startY));
    viewAppointmentsBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    viewAppointmentsBtn.setFillColor(sf::Color(52, 152, 219));
    viewAppointmentsBtn.setOutlineColor(sf::Color(52, 152, 219));
    viewAppointmentsBtn.setTextColor(sf::Color::White);

    viewMedicalRecordsBtn.setFont(regularFont);
    viewMedicalRecordsBtn.setText("Medical Records");
    viewMedicalRecordsBtn.setPosition(sf::Vector2f(startX, startY + btnHeight + spacingY));
    viewMedicalRecordsBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    viewMedicalRecordsBtn.setFillColor(sf::Color(52, 152, 219));
    viewMedicalRecordsBtn.setOutlineColor(sf::Color(52, 152, 219));
    viewMedicalRecordsBtn.setTextColor(sf::Color::White);

    viewBillsBtn.setFont(regularFont);
    viewBillsBtn.setText("View Bills");
    viewBillsBtn.setPosition(sf::Vector2f(startX + btnWidth + spacingX, startY + btnHeight + spacingY));
    viewBillsBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    viewBillsBtn.setFillColor(sf::Color(52, 152, 219));
    viewBillsBtn.setOutlineColor(sf::Color(52, 152, 219));
    viewBillsBtn.setTextColor(sf::Color::White);

    payBillBtn.setFont(regularFont);
    payBillBtn.setText("Pay Bill");
    payBillBtn.setPosition(sf::Vector2f(startX + (btnWidth + spacingX) * 2, startY + btnHeight + spacingY));
    payBillBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    payBillBtn.setFillColor(sf::Color(52, 152, 219));
    payBillBtn.setOutlineColor(sf::Color(52, 152, 219));
    payBillBtn.setTextColor(sf::Color::White);

    topUpBalanceBtn.setFont(regularFont);
    topUpBalanceBtn.setText("Top Up Balance");
    topUpBalanceBtn.setPosition(sf::Vector2f(startX, startY + (btnHeight + spacingY) * 2));
    topUpBalanceBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    topUpBalanceBtn.setFillColor(sf::Color(52, 152, 219));
    topUpBalanceBtn.setOutlineColor(sf::Color(52, 152, 219));
    topUpBalanceBtn.setTextColor(sf::Color::White);
    
    return true;
}

void PatientDash::updateDoctorList() {
    int i;
    int dispIdx;
    Doctor* doctors;
    char docStr[100];
    int docIdx;
    int charIdx;
    
    if (filteredDoctors == nullptr) {
        doctorListCount = 0;
        return;
    }
    
    doctorListCount = filteredDoctors->size();
    if (doctorListCount > 20) {
        doctorListCount = 20;
    }
    
    doctors = filteredDoctors->getAll();
    for (i = 0; i < doctorListCount; i++) {
        StringHelper::stringCopy(docStr, "ID: ", 100);
        docIdx = 0;
        while (docStr[docIdx] != '\0') {
            docIdx++;
        }
        ConversionHelper::intToString(doctors[i].getID(), docStr + docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0') {
            docIdx++;
        }
        
        StringHelper::stringCopy(docStr + docIdx, " | ", 100 - docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0') {
            docIdx++;
        }
        StringHelper::stringCopy(docStr + docIdx, doctors[i].getName(), 100 - docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0') {
            docIdx++;
        }
        
        StringHelper::stringCopy(docStr + docIdx, " | Fee: ", 100 - docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0') {
            docIdx++;
        }
        ConversionHelper::doubleToString(doctors[i].getFee(), docStr + docIdx);
        
        if (doctorListText[i] != nullptr) {
            doctorListText[i]->setString(docStr);
        }
    }
}

void PatientDash::updateTimeSlotDisplay() {
    char buffer[500];
    int i;
    
    StringHelper::stringCopy(buffer, "Select a time slot: ", 500);
    int len = StringHelper::stringLength(buffer);
    
    for (i = 0; i < 8; i++) {
        if (i > 0) {
            StringHelper::stringCopy(buffer + len, " | ", 500 - len);
            len = StringHelper::stringLength(buffer);
        }
        StringHelper::stringCopy(buffer + len, "09:00 10:00 11:00 12:00 13:00 14:00 15:00 16:00", 500 - len);
        break;
    }
    
    if (timeSlotDisplayText != nullptr) {
        timeSlotDisplayText->setString("Click on a time slot below to select:");
    }
}

void PatientDash::showStep(BookingStep step) {
    currentBookingStep = step;
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
        if (bookingStepIndicatorText != nullptr) {
            window.draw(*bookingStepIndicatorText);
        }
        if (bookingDialogStatusText != nullptr) {
            window.draw(*bookingDialogStatusText);
        }

        // Step 1: Specialization
        if (currentBookingStep == STEP_SPECIALIZATION) {
            if (specializationLabelText != nullptr) {
                window.draw(*specializationLabelText);
            }
            specializationInput.draw(window);
            searchDoctorsBtn.draw(window);
        }
        // Step 2: Doctor Selection
        else if (currentBookingStep == STEP_DOCTOR_SELECTION) {
            if (doctorListLabelText != nullptr) {
                window.draw(*doctorListLabelText);
            }
            int i;
            for (i = 0; i < doctorListCount; i++) {
                if (doctorListText[i] != nullptr) {
                    if (selectedDoctorIndex == i) {
                        sf::RectangleShape highlight(sf::Vector2f(650.f, 20.f));
                        highlight.setPosition(sf::Vector2f(215.f, 302.f + i * 22.f));
                        highlight.setFillColor(sf::Color(174, 235, 216));
                        window.draw(highlight);
                    }
                    window.draw(*doctorListText[i]);
                }
            }
        }
        // Step 3: Date Input
        else if (currentBookingStep == STEP_DATE_INPUT) {
            if (dateInputLabelText != nullptr) {
                window.draw(*dateInputLabelText);
            }
            dateInput.draw(window);
            confirmDateBtn.draw(window);
        }
        // Step 4: Time Slot Selection
        else if (currentBookingStep == STEP_TIME_SLOT) {
            if (timeSlotsLabelText != nullptr) {
                window.draw(*timeSlotsLabelText);
            }
            if (timeSlotDisplayText != nullptr) {
                window.draw(*timeSlotDisplayText);
            }
            int i;
            for (i = 0; i < 8; i++) {
                timeSlotButtons[i].draw(window);
            }
        }
        // Step 5: Confirm
        else if (currentBookingStep == STEP_CONFIRM) {
            sf::Text summaryLabel(regularFont, "Booking Summary:", 16);
            summaryLabel.setPosition(sf::Vector2f(220.f, 200.f));
            summaryLabel.setFillColor(sf::Color(44, 62, 80));
            window.draw(summaryLabel);
            
            sf::Text summaryText(regularFont, "", 13);
            summaryText.setFillColor(sf::Color(52, 73, 94));
            
            char summary[500];
            int y = 235;
            
            // Specialization
            StringHelper::stringCopy(summary, "Specialization: ", 500);
            int len = StringHelper::stringLength(summary);
            StringHelper::stringCopy(summary + len, selectedSpecialization, 500 - len);
            summaryText.setString(summary);
            summaryText.setPosition(sf::Vector2f(220.f, y));
            window.draw(summaryText);
            y += 25;
            
            // Doctor ID
            StringHelper::stringCopy(summary, "Doctor ID: ", 500);
            len = StringHelper::stringLength(summary);
            ConversionHelper::intToString(selectedDoctorID, summary + len);
            summaryText.setString(summary);
            summaryText.setPosition(sf::Vector2f(220.f, y));
            window.draw(summaryText);
            y += 25;
            
            // Date
            StringHelper::stringCopy(summary, "Date: ", 500);
            len = StringHelper::stringLength(summary);
            StringHelper::stringCopy(summary + len, selectedDate, 500 - len);
            summaryText.setString(summary);
            summaryText.setPosition(sf::Vector2f(220.f, y));
            window.draw(summaryText);
            y += 25;
            
            // Time
            StringHelper::stringCopy(summary, "Time: ", 500);
            len = StringHelper::stringLength(summary);
            StringHelper::stringCopy(summary + len, selectedTimeSlot, 500 - len);
            summaryText.setString(summary);
            summaryText.setPosition(sf::Vector2f(220.f, y));
            window.draw(summaryText);
        }

        // Navigation buttons
        if (currentBookingStep > STEP_SPECIALIZATION) {
            previousStepBtn.draw(window);
        }
        if (currentBookingStep < STEP_CONFIRM) {
            nextStepBtn.draw(window);
        }

        confirmBookingBtn.draw(window);
        cancelBookingBtn.draw(window);
    }
}

void PatientDash::handleMouseClick(sf::RenderWindow& window) {
    if (bookingMode) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (currentBookingStep == STEP_SPECIALIZATION) {
            if (specializationInput.contains(mouseWorldPosition)) {
                specializationInput.setActive(true);
                return;
            }
            if (searchDoctorsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
                if (StringHelper::stringLength(specializationInput.getText()) > 0) {
                    StringHelper::stringCopy(selectedSpecialization, specializationInput.getText(), 100);
                    specializationSearchRequested = true;
                    setDialogStatus("Searching for doctors...");
                } else {
                    setDialogStatus("Please enter a specialization.");
                }
                return;
            }
        } else if (currentBookingStep == STEP_DOCTOR_SELECTION) {
            int i;
            for (i = 0; i < doctorListCount; i++) {
                sf::Text& docText = *doctorListText[i];
                if (docText.getGlobalBounds().contains(mouseWorldPosition)) {
                    selectedDoctorIndex = i;
                    if (filteredDoctors != nullptr) {
                        selectedDoctorID = filteredDoctors->getAll()[i].getID();
                    }
                    advanceBookingStep();
                    return;
                }
            }
        } else if (currentBookingStep == STEP_DATE_INPUT) {
            if (dateInput.contains(mouseWorldPosition)) {
                dateInput.setActive(true);
                return;
            }
            if (confirmDateBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
                StringHelper::stringCopy(selectedDate, dateInput.getText(), 20);
                advanceBookingStep();
                return;
            }
        } else if (currentBookingStep == STEP_TIME_SLOT) {
            int i;
            for (i = 0; i < 8; i++) {
                if (timeSlotButtons[i].getShape().getGlobalBounds().contains(mouseWorldPosition)) {
                    // Reset all button colors to gray
                    int j;
                    for (j = 0; j < 8; j++) {
                        timeSlotButtons[j].setFillColor(sf::Color(189, 195, 199));
                        timeSlotButtons[j].setOutlineColor(sf::Color(189, 195, 199));
                    }
                    // Highlight selected button in green
                    selectedTimeSlotIndex = i;
                    timeSlotButtons[i].setFillColor(sf::Color(46, 204, 113));
                    timeSlotButtons[i].setOutlineColor(sf::Color(39, 174, 96));
                    const char* slots[] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};
                    StringHelper::stringCopy(selectedTimeSlot, slots[i], 10);
                    advanceBookingStep();
                    return;
                }
            }
        } else if (currentBookingStep == STEP_CONFIRM) {
            if (confirmBookingBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
                bookAppointmentRequested = true;
                return;
            }
        }

        if (previousStepBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            if (currentBookingStep > STEP_SPECIALIZATION) {
                regressBookingStep();
            }
            return;
        }

        if (nextStepBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            if (currentBookingStep < STEP_CONFIRM) {
                advanceBookingStep();
            }
            return;
        }

        if (cancelBookingBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
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

    if (currentBookingStep == STEP_SPECIALIZATION) {
        specializationInput.handleTextEntered(unicode);
    } else if (currentBookingStep == STEP_DATE_INPUT) {
        dateInput.handleTextEntered(unicode);
    }
}

void PatientDash::startBookingMode() {
    bookingMode = true;
    bookAppointmentRequested = false;
    specializationSearchRequested = false;
    currentBookingStep = STEP_SPECIALIZATION;
    dateFailureCount = 0;
    updateStepIndicator();
    setDialogStatus("Enter a specialization to search for doctors.");

    specializationInput.clear();
    specializationInput.setActive(false);
    dateInput.clear();
    dateInput.setActive(false);
    
    selectedSpecialization[0] = '\0';
    selectedDoctorID = -1;
    selectedDate[0] = '\0';
    selectedTimeSlot[0] = '\0';
    selectedDoctorIndex = -1;
    selectedTimeSlotIndex = -1;
    
    if (filteredDoctors != nullptr) {
        delete filteredDoctors;
        filteredDoctors = nullptr;
    }
}

void PatientDash::cancelBookingMode() {
    bookingMode = false;
    bookAppointmentRequested = false;
    bookingFocusedField = 0;
    currentBookingStep = STEP_SPECIALIZATION;
    
    specializationInput.clear();
    specializationInput.setActive(false);
    dateInput.clear();
    dateInput.setActive(false);
    
    if (filteredDoctors != nullptr) {
        delete filteredDoctors;
        filteredDoctors = nullptr;
    }
}

void PatientDash::advanceBookingStep() {
    if (currentBookingStep == STEP_SPECIALIZATION) {
        currentBookingStep = STEP_DOCTOR_SELECTION;
        updateStepIndicator();
        updateDoctorList();
        setDialogStatus("Select a doctor from the list below.");
    } else if (currentBookingStep == STEP_DOCTOR_SELECTION) {
        currentBookingStep = STEP_DATE_INPUT;
        updateStepIndicator();
        setDialogStatus("Enter appointment date in DD-MM-YYYY format (current year or later).");
        dateInput.setActive(true);
    } else if (currentBookingStep == STEP_DATE_INPUT) {
        currentBookingStep = STEP_TIME_SLOT;
        updateStepIndicator();
        updateTimeSlotDisplay();
        setDialogStatus("Select an available time slot.");
    } else if (currentBookingStep == STEP_TIME_SLOT) {
        currentBookingStep = STEP_CONFIRM;
        updateStepIndicator();
        setDialogStatus("Review your booking details and click Confirm to proceed.");
    }
}

void PatientDash::regressBookingStep() {
    if (currentBookingStep == STEP_CONFIRM) {
        currentBookingStep = STEP_TIME_SLOT;
        updateStepIndicator();
        setDialogStatus("Select an available time slot.");
    } else if (currentBookingStep == STEP_TIME_SLOT) {
        currentBookingStep = STEP_DATE_INPUT;
        updateStepIndicator();
        setDialogStatus("Enter appointment date in DD-MM-YYYY format.");
    } else if (currentBookingStep == STEP_DATE_INPUT) {
        currentBookingStep = STEP_DOCTOR_SELECTION;
        updateStepIndicator();
        setDialogStatus("Select a doctor from the list.");
    } else if (currentBookingStep == STEP_DOCTOR_SELECTION) {
        currentBookingStep = STEP_SPECIALIZATION;
        updateStepIndicator();
        setDialogStatus("Enter a specialization to search for doctors.");
    }
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

bool PatientDash::consumeSpecializationSearchRequest() {
    if (!specializationSearchRequested) {
        return false;
    }

    specializationSearchRequested = false;
    return true;
}

const char* PatientDash::getSpecializationText() const {
    return selectedSpecialization;
}

int PatientDash::getSelectedDoctorID() const {
    return selectedDoctorID;
}

const char* PatientDash::getBookingDateText() const {
    return selectedDate;
}

const char* PatientDash::getBookingTimeText() const {
    return selectedTimeSlot;
}

Storage<Doctor>* PatientDash::getFilteredDoctors() const {
    return filteredDoctors;
}

bool PatientDash::isBookAppointmentClicked() const {
    return bookAppointmentClicked;
}

void PatientDash::setFilteredDoctors(Storage<Doctor>* doctors) {
    if (filteredDoctors != nullptr) {
        delete filteredDoctors;
    }
    filteredDoctors = doctors;
    if (doctors != nullptr) {
        updateDoctorList();
    }
}

BookingStep PatientDash::getCurrentBookingStep() const {
    return currentBookingStep;
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

void PatientDash::setDialogStatus(const char* message) {
    if (message != nullptr && bookingDialogStatusText != nullptr) {
        bookingDialogStatusText->setString(message);
    }
}

void PatientDash::updateStepIndicator() {
    if (bookingStepIndicatorText == nullptr) {
        return;
    }
    
    char stepStr[50];
    int step = currentBookingStep + 1;
    StringHelper::stringCopy(stepStr, "Step ", 50);
    int len = StringHelper::stringLength(stepStr);
    ConversionHelper::intToString(step, stepStr + len);
    len = StringHelper::stringLength(stepStr);
    StringHelper::stringCopy(stepStr + len, " of 5", 50 - len);
    
    bookingStepIndicatorText->setString(stepStr);
}
