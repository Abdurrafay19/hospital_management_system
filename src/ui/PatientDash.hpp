#pragma once

#include <SFML/Graphics.hpp>
#include "../entities/Patient.hpp"
#include "../entities/Appointment.hpp"
#include "../entities/Prescription.hpp"
#include "../entities/Bill.hpp"
#include "../entities/Storage.hpp"
#include "../entities/Doctor.hpp"
#include "UIButton.hpp"
#include "UITextBox.hpp"

// Booking steps
enum BookingStep
{
    STEP_SPECIALIZATION = 0,
    STEP_DOCTOR_SELECTION = 1,
    STEP_DATE_INPUT = 2,
    STEP_TIME_SLOT = 3,
    STEP_CONFIRM = 4
};

class PatientDash
{
private:
    Patient *patient;
    sf::Font regularFont;
    sf::Font boldFont;

    sf::RectangleShape dashboardCard;
    sf::Text *titleText;
    sf::Text *patientNameText;
    sf::Text *balanceText;
    sf::Text *statusText;

    // Large booking panel for multi-step
    sf::RectangleShape bookingPanel;
    sf::Text *bookingTitleText;
    sf::Text *bookingStepIndicatorText;
    sf::Text *bookingDialogStatusText;
    sf::RectangleShape selectedDoctorHighlight;

    // Step 1: Specialization
    sf::Text *specializationLabelText;
    UITextBox specializationInput;
    UIButton searchDoctorsBtn;

    // Step 2: Doctor Selection
    sf::Text *doctorListLabelText;
    sf::Text *doctorListText[20]; // Display up to 20 doctors
    int doctorListCount;
    int selectedDoctorIndex;
    UIButton selectDoctorBtn;

    // Step 3: Date Input
    sf::Text *dateInputLabelText;
    UITextBox dateInput;
    UIButton confirmDateBtn;
    int dateFailureCount;

    // Step 4: Time Slot
    sf::Text *timeSlotsLabelText;
    sf::Text *timeSlotDisplayText;
    UIButton timeSlotButtons[8];
    int selectedTimeSlotIndex;
    Storage<Appointment> *allAppointments;

    // Step 5: Confirm
    UIButton confirmBookingBtn;
    UIButton cancelBookingBtn;

    // Cancel appointment mode
    bool cancelAppointmentMode;
    bool cancelAppointmentRequested;
    sf::RectangleShape cancelPanel;
    sf::Text *cancelTitleText;
    sf::Text *cancelDialogStatusText;
    sf::Text *cancelAppointmentsLabelText;
    sf::Text *cancelAppointmentIdLabelText;
    sf::Text *pendingAppointmentListText[20];
    int pendingAppointmentCount;
    UITextBox cancelAppointmentIdInput;
    UIButton confirmCancelAppointmentBtn;
    UIButton backFromCancelAppointmentBtn;
    Storage<Appointment> *pendingAppointments;
    Storage<Doctor> *pendingAppointmentDoctors;

    // View appointments mode
    bool viewAppointmentsMode;
    sf::RectangleShape viewAppointmentsPanel;
    sf::Text *viewAppointmentsTitleText;
    sf::Text *viewAppointmentsStatusText;
    sf::Text *viewAppointmentsLabelText;
    UIButton backFromViewAppointmentsBtn;
    Storage<Appointment> *viewedAppointments;
    Storage<Doctor> *viewedAppointmentDoctors;
    int viewedAppointmentCount;

    // View medical records mode
    bool viewMedicalRecordsMode;
    sf::RectangleShape viewMedicalRecordsPanel;
    sf::Text *viewMedicalRecordsTitleText;
    sf::Text *viewMedicalRecordsStatusText;
    sf::Text *viewMedicalRecordsLabelText;
    UIButton backFromViewMedicalRecordsBtn;
    Storage<Prescription> *viewedMedicalRecords;
    Storage<Doctor> *viewedMedicalRecordDoctors;
    int viewedMedicalRecordCount;

    // View bills mode
    bool viewBillsMode;
    sf::RectangleShape viewBillsPanel;
    sf::Text *viewBillsTitleText;
    sf::Text *viewBillsStatusText;
    sf::Text *viewBillsLabelText;
    sf::Text *viewBillsTotalText;
    UIButton backFromViewBillsBtn;
    Storage<Bill> *viewedBills;
    int viewedBillCount;
    double outstandingUnpaidAmount;
    // Pay bill mode
    bool payBillMode;
    bool payBillRequested;
    sf::RectangleShape payBillPanel;
    sf::Text *payBillTitleText;
    sf::Text *payBillLabelText;
    sf::Text *payBillIdLabelText;
    UITextBox payBillIdInput;
    UIButton confirmPayBillBtn;
    UIButton backFromPayBillBtn;
    // Top up balance mode
    bool topUpMode;
    bool topUpRequested;
    int topUpAttempts;
    sf::RectangleShape topUpPanel;
    sf::Text *topUpTitleText;
    sf::Text *topUpLabelText;
    UITextBox topUpAmountInput;
    UIButton confirmTopUpBtn;
    UIButton backFromTopUpBtn;

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
    Storage<Doctor> *filteredDoctors;

    void updateBookingFocus(int focusedField);
    void updateDoctorList();
    void updateTimeSlotDisplay();
    void updatePendingAppointmentList();
    void resetBillModeStatus();
    void clearViewedBillsState();
    void showStep(BookingStep step);

public:
    PatientDash();
    ~PatientDash();

    bool initialize(const sf::Font &regularFont, const sf::Font &boldFont);
    void setPatient(Patient *patient);
    void draw(sf::RenderWindow &window) const;
    void handleMouseClick(sf::RenderWindow &window);
    void handleTextEntered(char32_t unicode);
    void startBookingMode();
    void cancelBookingMode();
    void startCancelAppointmentMode();
    void closeCancelAppointmentMode();
    void startViewAppointmentsMode();
    void closeViewAppointmentsMode();
    void startViewMedicalRecordsMode();
    void closeViewMedicalRecordsMode();
    void startViewBillsMode();
    void closeViewBillsMode();
    void startPayBillMode();
    void closePayBillMode();
    void startTopUpMode();
    void closeTopUpMode();
    void advanceBookingStep();
    void regressBookingStep();
    bool isBookingMode() const;
    bool consumeBookAppointmentRequest();
    bool consumeSpecializationSearchRequest();
    bool isCancelAppointmentMode() const;
    bool consumeCancelAppointmentRequest();

    // Getters for booking data
    const char *getSpecializationText() const;
    int getSelectedDoctorID() const;
    const char *getBookingDateText() const;
    const char *getBookingTimeText() const;
    Storage<Doctor> *getFilteredDoctors() const;
    void setFilteredDoctors(Storage<Doctor> *doctors);
    void setPendingAppointments(Storage<Appointment> *appointments, Storage<Doctor> *doctors);
    void setViewedAppointments(Storage<Appointment> *appointments, Storage<Doctor> *doctors);
    void setViewedMedicalRecords(Storage<Prescription> *records, Storage<Doctor> *doctors);
    void setViewedBills(Storage<Bill> *bills);
    void setAllAppointments(Storage<Appointment> *appointments);
    BookingStep getCurrentBookingStep() const;
    const char *getCancelAppointmentIDText() const;
    const char *getPayBillIDText() const;
    const char *getTopUpAmountText() const;

    bool isBookAppointmentClicked() const;
    bool isCancelAppointmentClicked() const;
    bool isViewAppointmentsClicked() const;
    bool isViewMedicalRecordsClicked() const;
    bool isViewBillsClicked() const;
    bool isPayBillClicked() const;
    bool isTopUpBalanceClicked() const;
    bool consumePayBillRequest();
    bool consumeTopUpRequest();
    void incrementTopUpAttempts();
    int getTopUpAttempts() const;

    void clearClickStates();
    void setStatus(const char *message);
    void setDialogStatus(const char *message);
    void updateStepIndicator();
};
