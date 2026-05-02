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
            cancelAppointmentMode(false), cancelAppointmentRequested(false),
            bookingFocusedField(0),
      currentBookingStep(STEP_SPECIALIZATION), doctorListCount(0),
      selectedDoctorIndex(-1), dateFailureCount(0), selectedTimeSlotIndex(-1),
            filteredDoctors(nullptr), pendingAppointments(nullptr),
        pendingAppointmentDoctors(nullptr), pendingAppointmentCount(0),
        viewAppointmentsMode(false), viewedAppointments(nullptr),
        viewedAppointmentDoctors(nullptr), viewedAppointmentCount(0),
        viewMedicalRecordsMode(false), viewedMedicalRecords(nullptr),
        viewedMedicalRecordDoctors(nullptr), viewedMedicalRecordCount(0),
        viewBillsMode(false), viewedBills(nullptr), viewedBillCount(0),
        outstandingUnpaidAmount(0.0) {
    payBillMode = false;
    payBillRequested = false;
    payBillIdLabelText = nullptr;
        topUpMode = false;
        topUpRequested = false;
        topUpAttempts = 0;
        topUpTitleText = nullptr;
        topUpLabelText = nullptr;
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
    cancelTitleText = nullptr;
    cancelDialogStatusText = nullptr;
    cancelAppointmentsLabelText = nullptr;
    cancelAppointmentIdLabelText = nullptr;
    viewAppointmentsTitleText = nullptr;
    viewAppointmentsStatusText = nullptr;
    viewAppointmentsLabelText = nullptr;
    viewMedicalRecordsTitleText = nullptr;
    viewMedicalRecordsStatusText = nullptr;
    viewMedicalRecordsLabelText = nullptr;
    viewBillsTitleText = nullptr;
    viewBillsStatusText = nullptr;
    viewBillsLabelText = nullptr;
    viewBillsTotalText = nullptr;
    payBillIdLabelText = nullptr;
    topUpLabelText = nullptr;
    
    int i;
    for (i = 0; i < 20; i++) {
        doctorListText[i] = nullptr;
        pendingAppointmentListText[i] = nullptr;
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
    delete cancelTitleText;
    delete cancelDialogStatusText;
    delete cancelAppointmentsLabelText;
    delete cancelAppointmentIdLabelText;
    delete viewAppointmentsTitleText;
    delete viewAppointmentsStatusText;
    delete viewAppointmentsLabelText;
    delete viewMedicalRecordsTitleText;
    delete viewMedicalRecordsStatusText;
    delete viewMedicalRecordsLabelText;
    delete viewBillsTitleText;
    delete viewBillsStatusText;
    delete viewBillsLabelText;
    delete viewBillsTotalText;
    delete payBillIdLabelText;
    delete topUpTitleText;
    delete topUpLabelText;
    
    int i;
    for (i = 0; i < 20; i++) {
        delete doctorListText[i];
        delete pendingAppointmentListText[i];
        doctorListText[i] = nullptr;
        pendingAppointmentListText[i] = nullptr;
    }
    
    if (filteredDoctors != nullptr) {
        delete filteredDoctors;
        filteredDoctors = nullptr;
    }
    if (pendingAppointments != nullptr) {
        delete pendingAppointments;
        pendingAppointments = nullptr;
    }
    if (viewedAppointments != nullptr) {
        delete viewedAppointments;
        viewedAppointments = nullptr;
    }
    if (viewedMedicalRecords != nullptr) {
        delete viewedMedicalRecords;
        viewedMedicalRecords = nullptr;
    }
    if (viewedBills != nullptr) {
        delete viewedBills;
        viewedBills = nullptr;
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
    cancelTitleText = nullptr;
    cancelDialogStatusText = nullptr;
    cancelAppointmentsLabelText = nullptr;
    cancelAppointmentIdLabelText = nullptr;
    viewAppointmentsTitleText = nullptr;
    viewAppointmentsStatusText = nullptr;
    viewAppointmentsLabelText = nullptr;
    viewMedicalRecordsTitleText = nullptr;
    viewMedicalRecordsStatusText = nullptr;
    viewMedicalRecordsLabelText = nullptr;
    viewBillsTitleText = nullptr;
    viewBillsStatusText = nullptr;
    viewBillsLabelText = nullptr;
    viewBillsTotalText = nullptr;
    topUpTitleText = nullptr;
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
    cancelTitleText = new sf::Text(boldFont, "Cancel Appointment", 24);
    cancelDialogStatusText = new sf::Text(regularFont, "", 13);
    cancelAppointmentsLabelText = new sf::Text(regularFont, "Pending Appointments:", 16);
    cancelAppointmentIdLabelText = new sf::Text(regularFont, "Enter Appointment ID to cancel:", 16);

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

    int i;

    cancelPanel.setSize(sf::Vector2f(900.f, 550.f));
    cancelPanel.setPosition(sf::Vector2f(200.f, 130.f));
    cancelPanel.setFillColor(sf::Color(250, 251, 252));
    cancelPanel.setOutlineColor(sf::Color(220, 225, 230));
    cancelPanel.setOutlineThickness(2.f);

    cancelTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    cancelTitleText->setFillColor(sf::Color(44, 62, 80));

    cancelDialogStatusText->setPosition(sf::Vector2f(220.f, 605.f));
    cancelDialogStatusText->setFillColor(sf::Color(192, 57, 43));

    cancelAppointmentsLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    cancelAppointmentsLabelText->setFillColor(sf::Color(127, 140, 141));

    cancelAppointmentIdLabelText->setPosition(sf::Vector2f(220.f, 490.f));
    cancelAppointmentIdLabelText->setFillColor(sf::Color(127, 140, 141));

    viewAppointmentsPanel.setSize(sf::Vector2f(900.f, 550.f));
    viewAppointmentsPanel.setPosition(sf::Vector2f(200.f, 130.f));
    viewAppointmentsPanel.setFillColor(sf::Color(250, 251, 252));
    viewAppointmentsPanel.setOutlineColor(sf::Color(220, 225, 230));
    viewAppointmentsPanel.setOutlineThickness(2.f);

    viewAppointmentsTitleText = new sf::Text(boldFont, "My Appointments", 24);
    viewAppointmentsStatusText = new sf::Text(regularFont, "", 13);
    viewAppointmentsLabelText = new sf::Text(regularFont, "Appointments:", 16);

    viewAppointmentsTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    viewAppointmentsTitleText->setFillColor(sf::Color(44, 62, 80));

    viewAppointmentsStatusText->setPosition(sf::Vector2f(220.f, 605.f));
    viewAppointmentsStatusText->setFillColor(sf::Color(192, 57, 43));

    viewAppointmentsLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    viewAppointmentsLabelText->setFillColor(sf::Color(127, 140, 141));

    viewMedicalRecordsPanel.setSize(sf::Vector2f(900.f, 550.f));
    viewMedicalRecordsPanel.setPosition(sf::Vector2f(200.f, 130.f));
    viewMedicalRecordsPanel.setFillColor(sf::Color(250, 251, 252));
    viewMedicalRecordsPanel.setOutlineColor(sf::Color(220, 225, 230));
    viewMedicalRecordsPanel.setOutlineThickness(2.f);

    viewMedicalRecordsTitleText = new sf::Text(boldFont, "My Medical Records", 24);
    viewMedicalRecordsStatusText = new sf::Text(regularFont, "", 13);
    viewMedicalRecordsLabelText = new sf::Text(regularFont, "Records:", 16);

    viewMedicalRecordsTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    viewMedicalRecordsTitleText->setFillColor(sf::Color(44, 62, 80));

    viewMedicalRecordsStatusText->setPosition(sf::Vector2f(220.f, 605.f));
    viewMedicalRecordsStatusText->setFillColor(sf::Color(192, 57, 43));

    viewMedicalRecordsLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    viewMedicalRecordsLabelText->setFillColor(sf::Color(127, 140, 141));

    viewBillsPanel.setSize(sf::Vector2f(900.f, 550.f));
    viewBillsPanel.setPosition(sf::Vector2f(200.f, 130.f));
    viewBillsPanel.setFillColor(sf::Color(250, 251, 252));
    viewBillsPanel.setOutlineColor(sf::Color(220, 225, 230));
    viewBillsPanel.setOutlineThickness(2.f);

    viewBillsTitleText = new sf::Text(boldFont, "My Bills", 24);
    viewBillsStatusText = new sf::Text(regularFont, "", 13);
    viewBillsLabelText = new sf::Text(regularFont, "Bills:", 16);
    viewBillsTotalText = new sf::Text(regularFont, "", 15);

    viewBillsTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    viewBillsTitleText->setFillColor(sf::Color(44, 62, 80));

    viewBillsStatusText->setPosition(sf::Vector2f(220.f, 605.f));
    viewBillsStatusText->setFillColor(sf::Color(192, 57, 43));

    viewBillsLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    viewBillsLabelText->setFillColor(sf::Color(127, 140, 141));

    viewBillsTotalText->setPosition(sf::Vector2f(220.f, 560.f));
    viewBillsTotalText->setFillColor(sf::Color(44, 62, 80));

    payBillIdLabelText = new sf::Text(regularFont, "Enter Bill ID to pay:", 16);
    payBillIdLabelText->setPosition(sf::Vector2f(220.f, 490.f));
    payBillIdLabelText->setFillColor(sf::Color(127, 140, 141));

    payBillIdInput.setFont(regularFont);
    payBillIdInput.setCapacity(20);
    payBillIdInput.setPosition(sf::Vector2f(220.f, 515.f));
    payBillIdInput.setSize(sf::Vector2f(360.f, 36.f));
    payBillIdInput.setFillColor(sf::Color::White);
    payBillIdInput.setOutlineColor(sf::Color(189, 195, 199));
    payBillIdInput.setTextColor(sf::Color(44, 62, 80));

    confirmPayBillBtn.setFont(regularFont);
    confirmPayBillBtn.setText("Pay Bill");
    confirmPayBillBtn.setPosition(sf::Vector2f(720.f, 560.f));
    confirmPayBillBtn.setSize(sf::Vector2f(160.f, 38.f));
    confirmPayBillBtn.setFillColor(sf::Color(46, 204, 113));
    confirmPayBillBtn.setOutlineColor(sf::Color(46, 204, 113));
    confirmPayBillBtn.setTextColor(sf::Color::White);

    backFromPayBillBtn.setFont(regularFont);
    backFromPayBillBtn.setText("Back");
    backFromPayBillBtn.setPosition(sf::Vector2f(890.f, 560.f));
    backFromPayBillBtn.setSize(sf::Vector2f(90.f, 38.f));
    backFromPayBillBtn.setFillColor(sf::Color(149, 165, 166));
    backFromPayBillBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromPayBillBtn.setTextColor(sf::Color::White);

    topUpPanel.setSize(sf::Vector2f(650.f, 260.f));
    topUpPanel.setPosition(sf::Vector2f(320.f, 220.f));
    topUpPanel.setFillColor(sf::Color(250, 251, 252));
    topUpPanel.setOutlineColor(sf::Color(220, 225, 230));
    topUpPanel.setOutlineThickness(2.f);

    topUpTitleText = new sf::Text(boldFont, "Top Up Balance", 24);
    topUpTitleText->setPosition(sf::Vector2f(340.f, 240.f));
    topUpTitleText->setFillColor(sf::Color(44, 62, 80));

    topUpLabelText = new sf::Text(regularFont, "Enter amount to add (PKR):", 16);
    topUpLabelText->setPosition(sf::Vector2f(340.f, 295.f));
    topUpLabelText->setFillColor(sf::Color(127, 140, 141));

    topUpAmountInput.setFont(regularFont);
    topUpAmountInput.setCapacity(20);
    topUpAmountInput.setPosition(sf::Vector2f(340.f, 320.f));
    topUpAmountInput.setSize(sf::Vector2f(380.f, 36.f));
    topUpAmountInput.setFillColor(sf::Color::White);
    topUpAmountInput.setOutlineColor(sf::Color(189, 195, 199));
    topUpAmountInput.setTextColor(sf::Color(44, 62, 80));

    confirmTopUpBtn.setFont(regularFont);
    confirmTopUpBtn.setText("Top Up");
    confirmTopUpBtn.setPosition(sf::Vector2f(560.f, 380.f));
    confirmTopUpBtn.setSize(sf::Vector2f(160.f, 38.f));
    confirmTopUpBtn.setFillColor(sf::Color(46, 204, 113));
    confirmTopUpBtn.setOutlineColor(sf::Color(46, 204, 113));
    confirmTopUpBtn.setTextColor(sf::Color::White);

    backFromTopUpBtn.setFont(regularFont);
    backFromTopUpBtn.setText("Back");
    backFromTopUpBtn.setPosition(sf::Vector2f(730.f, 380.f));
    backFromTopUpBtn.setSize(sf::Vector2f(90.f, 38.f));
    backFromTopUpBtn.setFillColor(sf::Color(149, 165, 166));
    backFromTopUpBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromTopUpBtn.setTextColor(sf::Color::White);

    cancelAppointmentIdInput.setFont(regularFont);
    cancelAppointmentIdInput.setCapacity(20);
    cancelAppointmentIdInput.setPosition(sf::Vector2f(220.f, 515.f));
    cancelAppointmentIdInput.setSize(sf::Vector2f(360.f, 36.f));
    cancelAppointmentIdInput.setFillColor(sf::Color::White);
    cancelAppointmentIdInput.setOutlineColor(sf::Color(189, 195, 199));
    cancelAppointmentIdInput.setTextColor(sf::Color(44, 62, 80));

    for (i = 0; i < 20; i++) {
        pendingAppointmentListText[i] = new sf::Text(regularFont, "", 12);
        pendingAppointmentListText[i]->setPosition(sf::Vector2f(220.f, 225.f + i * 14.f));
        pendingAppointmentListText[i]->setFillColor(sf::Color(44, 62, 80));
    }

    confirmCancelAppointmentBtn.setFont(regularFont);
    confirmCancelAppointmentBtn.setText("Cancel Appointment");
    confirmCancelAppointmentBtn.setPosition(sf::Vector2f(720.f, 560.f));
    confirmCancelAppointmentBtn.setSize(sf::Vector2f(160.f, 38.f));
    confirmCancelAppointmentBtn.setFillColor(sf::Color(231, 76, 60));
    confirmCancelAppointmentBtn.setOutlineColor(sf::Color(231, 76, 60));
    confirmCancelAppointmentBtn.setTextColor(sf::Color::White);

    backFromCancelAppointmentBtn.setFont(regularFont);
    backFromCancelAppointmentBtn.setText("Back");
    backFromCancelAppointmentBtn.setPosition(sf::Vector2f(890.f, 560.f));
    backFromCancelAppointmentBtn.setSize(sf::Vector2f(90.f, 38.f));
    backFromCancelAppointmentBtn.setFillColor(sf::Color(149, 165, 166));
    backFromCancelAppointmentBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromCancelAppointmentBtn.setTextColor(sf::Color::White);

    backFromViewAppointmentsBtn.setFont(regularFont);
    backFromViewAppointmentsBtn.setText("Back");
    backFromViewAppointmentsBtn.setPosition(sf::Vector2f(890.f, 560.f));
    backFromViewAppointmentsBtn.setSize(sf::Vector2f(90.f, 38.f));
    backFromViewAppointmentsBtn.setFillColor(sf::Color(149, 165, 166));
    backFromViewAppointmentsBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromViewAppointmentsBtn.setTextColor(sf::Color::White);

    backFromViewMedicalRecordsBtn.setFont(regularFont);
    backFromViewMedicalRecordsBtn.setText("Back");
    backFromViewMedicalRecordsBtn.setPosition(sf::Vector2f(890.f, 560.f));
    backFromViewMedicalRecordsBtn.setSize(sf::Vector2f(90.f, 38.f));
    backFromViewMedicalRecordsBtn.setFillColor(sf::Color(149, 165, 166));
    backFromViewMedicalRecordsBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromViewMedicalRecordsBtn.setTextColor(sf::Color::White);

    backFromViewBillsBtn.setFont(regularFont);
    backFromViewBillsBtn.setText("Back");
    backFromViewBillsBtn.setPosition(sf::Vector2f(890.f, 560.f));
    backFromViewBillsBtn.setSize(sf::Vector2f(90.f, 38.f));
    backFromViewBillsBtn.setFillColor(sf::Color(149, 165, 166));
    backFromViewBillsBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromViewBillsBtn.setTextColor(sf::Color::White);

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
        closeCancelAppointmentMode();
        closeViewAppointmentsMode();
        closeViewMedicalRecordsMode();
        closeViewBillsMode();
        closePayBillMode();
        closeTopUpMode();
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

    if (cancelAppointmentMode) {
        window.draw(cancelPanel);
        if (cancelTitleText != nullptr) {
            window.draw(*cancelTitleText);
        }
        if (cancelDialogStatusText != nullptr) {
            window.draw(*cancelDialogStatusText);
        }
        if (cancelAppointmentsLabelText != nullptr) {
            window.draw(*cancelAppointmentsLabelText);
        }
        if (cancelAppointmentIdLabelText != nullptr) {
            window.draw(*cancelAppointmentIdLabelText);
        }

        int i;
        for (i = 0; i < pendingAppointmentCount; i++) {
            if (pendingAppointmentListText[i] != nullptr) {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        cancelAppointmentIdInput.draw(window);
        confirmCancelAppointmentBtn.draw(window);
        backFromCancelAppointmentBtn.draw(window);
    } else if (viewAppointmentsMode) {
        window.draw(viewAppointmentsPanel);
        if (viewAppointmentsTitleText != nullptr) {
            window.draw(*viewAppointmentsTitleText);
        }
        if (viewAppointmentsStatusText != nullptr) {
            window.draw(*viewAppointmentsStatusText);
        }
        if (viewAppointmentsLabelText != nullptr) {
            window.draw(*viewAppointmentsLabelText);
        }

        int i;
        for (i = 0; i < viewedAppointmentCount; i++) {
            if (pendingAppointmentListText[i] != nullptr) {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        backFromViewAppointmentsBtn.draw(window);
    } else if (viewMedicalRecordsMode) {
        window.draw(viewMedicalRecordsPanel);
        if (viewMedicalRecordsTitleText != nullptr) {
            window.draw(*viewMedicalRecordsTitleText);
        }
        if (viewMedicalRecordsStatusText != nullptr) {
            window.draw(*viewMedicalRecordsStatusText);
        }
        if (viewMedicalRecordsLabelText != nullptr) {
            window.draw(*viewMedicalRecordsLabelText);
        }

        int i;
        for (i = 0; i < viewedMedicalRecordCount; i++) {
            if (pendingAppointmentListText[i] != nullptr) {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        backFromViewMedicalRecordsBtn.draw(window);
    } else if (viewBillsMode) {
        window.draw(viewBillsPanel);
        if (viewBillsTitleText != nullptr) {
            window.draw(*viewBillsTitleText);
        }
        if (viewBillsStatusText != nullptr) {
            window.draw(*viewBillsStatusText);
        }
        if (viewBillsLabelText != nullptr) {
            window.draw(*viewBillsLabelText);
        }
        if (viewBillsTotalText != nullptr) {
            window.draw(*viewBillsTotalText);
        }

        int i;
        for (i = 0; i < viewedBillCount; i++) {
            if (pendingAppointmentListText[i] != nullptr) {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        backFromViewBillsBtn.draw(window);
    } else if (payBillMode) {
        window.draw(viewBillsPanel);
        if (viewBillsTitleText != nullptr) {
            window.draw(*viewBillsTitleText);
        }
        if (viewBillsStatusText != nullptr) {
            window.draw(*viewBillsStatusText);
        }
        if (viewBillsLabelText != nullptr) {
            window.draw(*viewBillsLabelText);
        }
        if (viewBillsTotalText != nullptr) {
            window.draw(*viewBillsTotalText);
        }

        int i;
        for (i = 0; i < viewedBillCount; i++) {
            if (pendingAppointmentListText[i] != nullptr) {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        if (payBillIdLabelText != nullptr) {
            window.draw(*payBillIdLabelText);
        }
        payBillIdInput.draw(window);
        confirmPayBillBtn.draw(window);
        backFromPayBillBtn.draw(window);
    } else if (topUpMode) {
        window.draw(topUpPanel);

        if (topUpTitleText != nullptr) {
            window.draw(*topUpTitleText);
        }

        if (topUpLabelText != nullptr) {
            window.draw(*topUpLabelText);
        }
        topUpAmountInput.draw(window);
        confirmTopUpBtn.draw(window);
        backFromTopUpBtn.draw(window);
    } else if (bookingMode) {
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
    if (cancelAppointmentMode) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (cancelAppointmentIdInput.contains(mouseWorldPosition)) {
            cancelAppointmentIdInput.setActive(true);
            return;
        }

        if (confirmCancelAppointmentBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            cancelAppointmentRequested = true;
            return;
        }

        if (backFromCancelAppointmentBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            closeCancelAppointmentMode();
            return;
        }

        cancelAppointmentIdInput.setActive(false);
        return;
    }

    if (viewAppointmentsMode) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (backFromViewAppointmentsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            closeViewAppointmentsMode();
            return;
        }

        return;
    }

    if (viewMedicalRecordsMode) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (backFromViewMedicalRecordsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            closeViewMedicalRecordsMode();
            return;
        }

        return;
    }

    if (viewBillsMode) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (backFromViewBillsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            closeViewBillsMode();
            return;
        }

        return;
    }

    if (payBillMode) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (payBillIdInput.contains(mouseWorldPosition)) {
            payBillIdInput.setActive(true);
            return;
        }

        if (confirmPayBillBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            payBillRequested = true;
            return;
        }

        if (backFromPayBillBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            closePayBillMode();
            return;
        }

        payBillIdInput.setActive(false);
        return;
    }

    if (topUpMode) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (topUpAmountInput.contains(mouseWorldPosition)) {
            topUpAmountInput.setActive(true);
            return;
        }

        if (confirmTopUpBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            topUpRequested = true;
            return;
        }

        if (backFromTopUpBtn.getShape().getGlobalBounds().contains(mouseWorldPosition)) {
            closeTopUpMode();
            return;
        }

        topUpAmountInput.setActive(false);
        return;
    }

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
    if (cancelAppointmentMode) {
        cancelAppointmentIdInput.handleTextEntered(unicode);
        return;
    }

    if (viewAppointmentsMode) {
        return;
    }

    if (viewMedicalRecordsMode) {
        return;
    }

    if (viewBillsMode) {
        return;
    }

    if (payBillMode) {
        payBillIdInput.handleTextEntered(unicode);
        return;
    }

    if (topUpMode) {
        topUpAmountInput.handleTextEntered(unicode);
        return;
    }

    if (!bookingMode) {
        return;
    }
                                // Confirm booking logic here
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

void PatientDash::startCancelAppointmentMode() {
    cancelAppointmentMode = true;
    cancelAppointmentRequested = false;
    cancelAppointmentIdInput.clear();
    cancelAppointmentIdInput.setActive(false);

    if (pendingAppointments != nullptr) {
        updatePendingAppointmentList();
    }

    if (cancelDialogStatusText != nullptr) {
        cancelDialogStatusText->setString("Enter the appointment ID to cancel.");
    }
}

void PatientDash::closeCancelAppointmentMode() {
    cancelAppointmentMode = false;
    cancelAppointmentRequested = false;
    cancelAppointmentIdInput.clear();
    cancelAppointmentIdInput.setActive(false);
    pendingAppointmentCount = 0;

    if (pendingAppointments != nullptr) {
        delete pendingAppointments;
        pendingAppointments = nullptr;
    }

    pendingAppointmentDoctors = nullptr;
}

void PatientDash::startViewAppointmentsMode() {
    viewAppointmentsMode = true;

    if (viewAppointmentsStatusText != nullptr) {
        viewAppointmentsStatusText->setString("");
    }

    if (viewedAppointments != nullptr) {
        updatePendingAppointmentList();
    }
}

void PatientDash::closeViewAppointmentsMode() {
    viewAppointmentsMode = false;
    viewedAppointmentCount = 0;

    if (viewedAppointments != nullptr) {
        delete viewedAppointments;
        viewedAppointments = nullptr;
    }

    viewedAppointmentDoctors = nullptr;
}

void PatientDash::startViewMedicalRecordsMode() {
    viewMedicalRecordsMode = true;

    if (viewMedicalRecordsStatusText != nullptr) {
        viewMedicalRecordsStatusText->setString("");
    }

    if (viewedMedicalRecords != nullptr) {
        updatePendingAppointmentList();
    }
}

void PatientDash::closeViewMedicalRecordsMode() {
    viewMedicalRecordsMode = false;
    viewedMedicalRecordCount = 0;

    if (viewedMedicalRecords != nullptr) {
        delete viewedMedicalRecords;
        viewedMedicalRecords = nullptr;
    }

    viewedMedicalRecordDoctors = nullptr;
}

void PatientDash::startViewBillsMode() {
    viewBillsMode = true;

    if (viewBillsStatusText != nullptr) {
        viewBillsStatusText->setString("");
    }

    if (viewedBills != nullptr) {
        updatePendingAppointmentList();
    }
}

void PatientDash::startPayBillMode() {
    payBillMode = true;
    payBillRequested = false;
    payBillIdInput.clear();
    payBillIdInput.setActive(false);

    if (viewedBills != nullptr) {
        updatePendingAppointmentList();
    }

    if (viewBillsStatusText != nullptr) {
        viewBillsStatusText->setString("");
    }
}

void PatientDash::closePayBillMode() {
    payBillMode = false;
    payBillRequested = false;
    payBillIdInput.clear();
    payBillIdInput.setActive(false);
    viewedBillCount = 0;

    if (viewedBills != nullptr) {
        delete viewedBills;
        viewedBills = nullptr;
    }

    if (viewBillsTotalText != nullptr) {
        viewBillsTotalText->setString("");
    }
}

void PatientDash::startTopUpMode() {
    topUpMode = true;
    topUpRequested = false;
    topUpAttempts = 0;
    topUpAmountInput.clear();
    topUpAmountInput.setActive(false);

    if (viewedBills != nullptr) {
        updatePendingAppointmentList();
    }

    if (viewBillsStatusText != nullptr) {
        viewBillsStatusText->setString("");
    }
}

void PatientDash::closeTopUpMode() {
    topUpMode = false;
    topUpRequested = false;
    topUpAmountInput.clear();
    topUpAmountInput.setActive(false);
    topUpAttempts = 0;

    if (viewedBills != nullptr) {
        delete viewedBills;
        viewedBills = nullptr;
    }

    if (viewBillsTotalText != nullptr) {
        viewBillsTotalText->setString("");
    }
}

void PatientDash::closeViewBillsMode() {
    viewBillsMode = false;
    viewedBillCount = 0;
    outstandingUnpaidAmount = 0.0;

    if (viewedBills != nullptr) {
        delete viewedBills;
        viewedBills = nullptr;
    }

    if (viewBillsTotalText != nullptr) {
        viewBillsTotalText->setString("");
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

bool PatientDash::isCancelAppointmentMode() const {
    return cancelAppointmentMode;
}

bool PatientDash::consumeCancelAppointmentRequest() {
    if (!cancelAppointmentRequested) {
        return false;
    }

    cancelAppointmentRequested = false;
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

const char* PatientDash::getCancelAppointmentIDText() const {
    return cancelAppointmentIdInput.getText();
}

const char* PatientDash::getPayBillIDText() const {
    return payBillIdInput.getText();
}

const char* PatientDash::getTopUpAmountText() const {
    return topUpAmountInput.getText();
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

void PatientDash::setPendingAppointments(Storage<Appointment>* appointments, Storage<Doctor>* doctors) {
    if (pendingAppointments != nullptr) {
        delete pendingAppointments;
    }

    pendingAppointments = appointments;
    pendingAppointmentDoctors = doctors;

    if (appointments != nullptr) {
        updatePendingAppointmentList();
    } else {
        pendingAppointmentCount = 0;
    }
}

void PatientDash::setViewedAppointments(Storage<Appointment>* appointments, Storage<Doctor>* doctors) {
    if (viewedAppointments != nullptr) {
        delete viewedAppointments;
    }

    viewedAppointments = appointments;
    viewedAppointmentDoctors = doctors;

    if (appointments != nullptr) {
        updatePendingAppointmentList();
    } else {
        viewedAppointmentCount = 0;
    }
}

void PatientDash::setViewedMedicalRecords(Storage<Prescription>* records, Storage<Doctor>* doctors) {
    if (viewedMedicalRecords != nullptr) {
        delete viewedMedicalRecords;
    }

    viewedMedicalRecords = records;
    viewedMedicalRecordDoctors = doctors;

    if (records != nullptr) {
        updatePendingAppointmentList();
    } else {
        viewedMedicalRecordCount = 0;
    }
}

void PatientDash::setViewedBills(Storage<Bill>* bills) {
    if (viewedBills != nullptr) {
        delete viewedBills;
    }

    viewedBills = bills;

    if (bills != nullptr) {
        updatePendingAppointmentList();
    } else {
        viewedBillCount = 0;
        outstandingUnpaidAmount = 0.0;
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

bool PatientDash::consumeTopUpRequest() {
    if (!topUpRequested) {
        return false;
    }

    topUpRequested = false;
    return true;
}

void PatientDash::incrementTopUpAttempts() {
    topUpAttempts++;
}

int PatientDash::getTopUpAttempts() const {
    return topUpAttempts;
}

bool PatientDash::consumePayBillRequest() {
    if (!payBillRequested) {
        return false;
    }

    payBillRequested = false;
    return true;
}

void PatientDash::updatePendingAppointmentList() {
    int i;
    int j;
    Appointment* appointmentsArray;
    Appointment* appointment;
    Prescription* recordsArray;
    Prescription* record;
    Bill* billsArray;
    Bill* bill;
    Doctor* doctor;
    const char* doctorName;
    char row[400];
    char amountBuffer[32];
    char totalBuffer[400];
    int rowLen;

    if (cancelAppointmentMode) {
        if (pendingAppointments == nullptr) {
            pendingAppointmentCount = 0;
            return;
        }

        pendingAppointmentCount = pendingAppointments->size();
        if (pendingAppointmentCount > 20) {
            pendingAppointmentCount = 20;
        }

        appointmentsArray = pendingAppointments->getAll();
        for (i = 0; i < pendingAppointmentCount; i++) {
            appointment = &appointmentsArray[i];
            doctorName = "Unknown Doctor";

            if (pendingAppointmentDoctors != nullptr) {
                doctor = pendingAppointmentDoctors->findByID(appointment->getDoctorID());
                if (doctor != nullptr) {
                    doctorName = doctor->getName();
                }
            }

            row[0] = '\0';
            StringHelper::stringCopy(row, "Appointment ID: ", 400);
            rowLen = StringHelper::stringLength(row);
            ConversionHelper::intToString(appointment->getAppointmentID(), row + rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, doctorName, 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, appointment->getDate(), 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, appointment->getTimeSlot(), 400 - rowLen);

            if (pendingAppointmentListText[i] != nullptr) {
                pendingAppointmentListText[i]->setString(row);
            }
        }

        for (j = pendingAppointmentCount; j < 20; j++) {
            if (pendingAppointmentListText[j] != nullptr) {
                pendingAppointmentListText[j]->setString("");
            }
        }
        return;
    }

    if (viewAppointmentsMode) {
        if (viewedAppointments == nullptr) {
            viewedAppointmentCount = 0;
            return;
        }

        viewedAppointmentCount = viewedAppointments->size();
        if (viewedAppointmentCount > 20) {
            viewedAppointmentCount = 20;
        }

        appointmentsArray = viewedAppointments->getAll();
        for (i = 0; i < viewedAppointmentCount; i++) {
            appointment = &appointmentsArray[i];
            doctorName = "Unknown Doctor";

            if (viewedAppointmentDoctors != nullptr) {
                doctor = viewedAppointmentDoctors->findByID(appointment->getDoctorID());
                if (doctor != nullptr) {
                    doctorName = doctor->getName();
                }
            }

            row[0] = '\0';
            StringHelper::stringCopy(row, "ID: ", 400);
            rowLen = StringHelper::stringLength(row);
            ConversionHelper::intToString(appointment->getAppointmentID(), row + rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, doctorName, 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            if (doctor != nullptr) {
                StringHelper::stringCopy(row + rowLen, doctor->getSpecialization(), 400 - rowLen);
            } else {
                StringHelper::stringCopy(row + rowLen, "Unknown", 400 - rowLen);
            }

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, appointment->getDate(), 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, appointment->getTimeSlot(), 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, appointment->getStatus(), 400 - rowLen);

            if (pendingAppointmentListText[i] != nullptr) {
                pendingAppointmentListText[i]->setString(row);
            }
        }

        for (j = viewedAppointmentCount; j < 20; j++) {
            if (pendingAppointmentListText[j] != nullptr) {
                pendingAppointmentListText[j]->setString("");
            }
        }
        return;
    }

    if (viewMedicalRecordsMode) {
        if (viewedMedicalRecords == nullptr) {
            viewedMedicalRecordCount = 0;
            return;
        }

        viewedMedicalRecordCount = viewedMedicalRecords->size();
        if (viewedMedicalRecordCount > 20) {
            viewedMedicalRecordCount = 20;
        }

        recordsArray = viewedMedicalRecords->getAll();
        for (i = 0; i < viewedMedicalRecordCount; i++) {
            record = &recordsArray[i];
            doctorName = "Unknown Doctor";

            if (viewedMedicalRecordDoctors != nullptr) {
                doctor = viewedMedicalRecordDoctors->findByID(record->getDoctorID());
                if (doctor != nullptr) {
                    doctorName = doctor->getName();
                }
            }

            row[0] = '\0';
            StringHelper::stringCopy(row, record->getDate(), 400);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, doctorName, 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, record->getMedicines(), 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, record->getNotes(), 400 - rowLen);

            if (pendingAppointmentListText[i] != nullptr) {
                pendingAppointmentListText[i]->setString(row);
            }
        }

        for (j = viewedMedicalRecordCount; j < 20; j++) {
            if (pendingAppointmentListText[j] != nullptr) {
                pendingAppointmentListText[j]->setString("");
            }
        }
        return;
    }

    if (viewBillsMode || payBillMode) {
        if (viewedBills == nullptr) {
            viewedBillCount = 0;
            outstandingUnpaidAmount = 0.0;
            if (viewBillsTotalText != nullptr) {
                viewBillsTotalText->setString("");
            }
            return;
        }

        viewedBillCount = viewedBills->size();
        if (viewedBillCount > 20) {
            viewedBillCount = 20;
        }

        outstandingUnpaidAmount = 0.0;
        billsArray = viewedBills->getAll();
        for (i = 0; i < viewedBillCount; i++) {
            bill = &billsArray[i];

            row[0] = '\0';
            StringHelper::stringCopy(row, "Bill ID: ", 400);
            rowLen = StringHelper::stringLength(row);
            ConversionHelper::intToString(bill->getBillID(), row + rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | Appt ID: ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            ConversionHelper::intToString(bill->getAppointmentID(), row + rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | PKR ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            ConversionHelper::doubleToString(bill->getAmount(), amountBuffer);
            StringHelper::stringCopy(row + rowLen, amountBuffer, 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, bill->getStatus(), 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, bill->getDate(), 400 - rowLen);

            if (!StringHelper::textEquals(bill->getStatus(), "paid") && !StringHelper::textEquals(bill->getStatus(), "cancelled")) {
                outstandingUnpaidAmount = outstandingUnpaidAmount + bill->getAmount();
            }

            if (pendingAppointmentListText[i] != nullptr) {
                pendingAppointmentListText[i]->setString(row);
            }
        }

        for (j = viewedBillCount; j < 20; j++) {
            if (pendingAppointmentListText[j] != nullptr) {
                pendingAppointmentListText[j]->setString("");
            }
        }

        if (viewBillsTotalText != nullptr) {
            totalBuffer[0] = '\0';
            StringHelper::stringCopy(totalBuffer, "Total Outstanding Unpaid: PKR ", 400);
            rowLen = StringHelper::stringLength(totalBuffer);
            ConversionHelper::doubleToString(outstandingUnpaidAmount, amountBuffer);
            StringHelper::stringCopy(totalBuffer + rowLen, amountBuffer, 400 - rowLen);
            viewBillsTotalText->setString(totalBuffer);
        }
    }
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
