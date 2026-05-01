#pragma once

#include <SFML/Graphics.hpp>
#include "../entities/Patient.hpp"
#include "../entities/Storage.hpp"
#include "../entities/Doctor.hpp"
#include "UIButton.hpp"
#include "UITextBox.hpp"

// Booking steps
enum BookingStep {
    STEP_SPECIALIZATION = 0,
    STEP_DOCTOR_SELECTION = 1,
    STEP_DATE_INPUT = 2,
    STEP_TIME_SLOT = 3,
    STEP_CONFIRM = 4
};

class PatientDash {
private:
    Patient* patient;
    sf::Font regularFont;
    sf::Font boldFont;

    sf::RectangleShape dashboardCard;
    sf::Text* titleText;
    sf::Text* patientNameText;
    sf::Text* balanceText;
    sf::Text* statusText;
    
    // Large booking panel for multi-step
    sf::RectangleShape bookingPanel;
    sf::Text* bookingTitleText;
    sf::Text* bookingStepIndicatorText;
    sf::Text* bookingDialogStatusText;
    sf::RectangleShape selectedDoctorHighlight;

    // Step 1: Specialization
    sf::Text* specializationLabelText;
    UITextBox specializationInput;
    UIButton searchDoctorsBtn;

    // Step 2: Doctor Selection
    sf::Text* doctorListLabelText;
    sf::Text* doctorListText[20];  // Display up to 20 doctors
    int doctorListCount;
    int selectedDoctorIndex;
    UIButton selectDoctorBtn;

    // Step 3: Date Input
    sf::Text* dateInputLabelText;
    UITextBox dateInput;
    UIButton confirmDateBtn;
    int dateFailureCount;

    // Step 4: Time Slot
    sf::Text* timeSlotsLabelText;
    sf::Text* timeSlotDisplayText;
    UIButton timeSlotButtons[8];
    int selectedTimeSlotIndex;

    // Step 5: Confirm
    UIButton confirmBookingBtn;
    UIButton cancelBookingBtn;

    // Navigation buttons between steps
    UIButton previousStepBtn;
    UIButton nextStepBtn;

    // Dashboard buttons
    UIButton bookAppointmentBtn;
    UIButton cancelAppointmentBtn;
    UIButton viewAppointmentsBtn;
    UIButton viewMedicalRecordsBtn;
    UIButton viewBillsBtn;
    UIButton payBillBtn;
    UIButton topUpBalanceBtn;

    // Click state tracking
    bool bookAppointmentClicked;
    bool cancelAppointmentClicked;
    bool viewAppointmentsClicked;
    bool viewMedicalRecordsClicked;
    bool viewBillsClicked;
    bool payBillClicked;
    bool topUpBalanceClicked;

    // Booking state tracking
    BookingStep currentBookingStep;
    bool bookingMode;
    bool bookAppointmentRequested;
    bool specializationSearchRequested;
    int bookingFocusedField;
    
    // Temporary storage during booking
    char selectedSpecialization[100];
    int selectedDoctorID;
    char selectedDate[20];
    char selectedTimeSlot[10];
    Storage<Doctor>* filteredDoctors;

    void updateBookingFocus(int focusedField);
    void updateDoctorList();
    void updateTimeSlotDisplay();
    void showStep(BookingStep step);
    
public:
    PatientDash();
    ~PatientDash();
    
    bool initialize(const sf::Font& regularFont, const sf::Font& boldFont);
    void setPatient(Patient* patient);
    void draw(sf::RenderWindow& window) const;
    void handleMouseClick(sf::RenderWindow& window);
    void handleTextEntered(char32_t unicode);
    void startBookingMode();
    void cancelBookingMode();
    void advanceBookingStep();
    void regressBookingStep();
    bool isBookingMode() const;
    bool consumeBookAppointmentRequest();
    bool consumeSpecializationSearchRequest();
    
    // Getters for booking data
    const char* getSpecializationText() const;
    int getSelectedDoctorID() const;
    const char* getBookingDateText() const;
    const char* getBookingTimeText() const;
    Storage<Doctor>* getFilteredDoctors() const;
    void setFilteredDoctors(Storage<Doctor>* doctors);
    BookingStep getCurrentBookingStep() const;

    bool isBookAppointmentClicked() const;
    bool isCancelAppointmentClicked() const;
    bool isViewAppointmentsClicked() const;
    bool isViewMedicalRecordsClicked() const;
    bool isViewBillsClicked() const;
    bool isPayBillClicked() const;
    bool isTopUpBalanceClicked() const;
    
    void clearClickStates();
    void setStatus(const char* message);
    void setDialogStatus(const char* message);
    void updateStepIndicator();
};

