#include "PatientDash.hpp"
#include "../helpers/UIThemeHelper.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"
#include "../core/Validator.hpp"
#include "../helpers/TimeHelper.hpp"

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
      filteredDoctors(nullptr), allAppointments(nullptr), pendingAppointments(nullptr),
      pendingAppointmentDoctors(nullptr), pendingAppointmentCount(0),
      viewAppointmentsMode(false), viewedAppointments(nullptr),
      viewedAppointmentDoctors(nullptr), viewedAppointmentCount(0),
      viewMedicalRecordsMode(false), viewedMedicalRecords(nullptr),
      viewedMedicalRecordDoctors(nullptr), viewedMedicalRecordCount(0),
      viewBillsMode(false), viewedBills(nullptr), viewedBillCount(0),
      outstandingUnpaidAmount(0.0)
{
    payBillMode = false;
    payBillRequested = false;
    payBillTitleText = nullptr;
    payBillLabelText = nullptr;
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
    payBillTitleText = nullptr;
    payBillLabelText = nullptr;
    payBillIdLabelText = nullptr;
    topUpLabelText = nullptr;

    int i;
    for (i = 0; i < 20; i++)
    {
        doctorListText[i] = nullptr;
        pendingAppointmentListText[i] = nullptr;
    }

    selectedSpecialization[0] = '\0';
    selectedDoctorID = -1;
    selectedDate[0] = '\0';
    selectedTimeSlot[0] = '\0';
}

PatientDash::~PatientDash()
{
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
    delete payBillTitleText;
    delete payBillLabelText;
    delete payBillIdLabelText;
    delete topUpTitleText;
    delete topUpLabelText;

    int i;
    for (i = 0; i < 20; i++)
    {
        delete doctorListText[i];
        delete pendingAppointmentListText[i];
        doctorListText[i] = nullptr;
        pendingAppointmentListText[i] = nullptr;
    }

    if (filteredDoctors != nullptr)
    {
        delete filteredDoctors;
        filteredDoctors = nullptr;
    }
    if (pendingAppointments != nullptr)
    {
        delete pendingAppointments;
        pendingAppointments = nullptr;
    }
    if (viewedAppointments != nullptr)
    {
        delete viewedAppointments;
        viewedAppointments = nullptr;
    }
    if (viewedMedicalRecords != nullptr)
    {
        delete viewedMedicalRecords;
        viewedMedicalRecords = nullptr;
    }
    if (viewedBills != nullptr)
    {
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
    payBillTitleText = nullptr;
    payBillLabelText = nullptr;
    topUpTitleText = nullptr;
}

bool PatientDash::initialize(const sf::Font &regularFontParam, const sf::Font &boldFontParam)
{
    regularFont = regularFontParam;
    boldFont = boldFontParam;

    dashboardCard.setSize(sf::Vector2f(1100.f, 650.f));
    dashboardCard.setPosition(sf::Vector2f(90.f, 80.f));
    UIThemeHelper::styleDashboardCard(dashboardCard);

    // Header texts (creation + position + style)
    titleText = new sf::Text(boldFont, "Patient Dashboard", 32);
    UIThemeHelper::setTextSizeMainTitle(titleText);
    titleText->setPosition(sf::Vector2f(110.f, 100.f));
    UIThemeHelper::styleTitleText(titleText);

    patientNameText = new sf::Text(regularFont, "", 18);
    UIThemeHelper::setTextSizeBody(patientNameText);
    patientNameText->setPosition(sf::Vector2f(110.f, 150.f));
    UIThemeHelper::styleLabelText(patientNameText);

    balanceText = new sf::Text(regularFont, "", 18);
    UIThemeHelper::setTextSizeBody(balanceText);
    balanceText->setPosition(sf::Vector2f(110.f, 180.f));
    UIThemeHelper::styleLabelText(balanceText);

    statusText = new sf::Text(regularFont, "", 16);
    UIThemeHelper::setTextSizeSmall(statusText);
    statusText->setPosition(sf::Vector2f(110.f, 600.f));
    statusText->setFillColor(sf::Color(231, 76, 60));

    // Booking panel and texts
    bookingPanel.setSize(sf::Vector2f(900.f, 550.f));
    bookingPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(bookingPanel);

    bookingTitleText = new sf::Text(boldFont, "Book Appointment", 24);
    UIThemeHelper::setTextSizeTitle(bookingTitleText);
    bookingTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    UIThemeHelper::styleTitleText(bookingTitleText);

    bookingStepIndicatorText = new sf::Text(regularFont, "Step 1 of 5", 14);
    UIThemeHelper::setTextSizeBody(bookingStepIndicatorText);
    bookingStepIndicatorText->setPosition(sf::Vector2f(820.f, 153.f));
    bookingStepIndicatorText->setFillColor(sf::Color(149, 165, 166));

    bookingDialogStatusText = new sf::Text(regularFont, "", 13);
    UIThemeHelper::setTextSizeSmall(bookingDialogStatusText);
    bookingDialogStatusText->setPosition(sf::Vector2f(220.f, 467.f));
    UIThemeHelper::styleStatusText(bookingDialogStatusText);

    // Cancel panel and texts
    cancelPanel.setSize(sf::Vector2f(900.f, 550.f));
    cancelPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(cancelPanel);

    cancelTitleText = new sf::Text(boldFont, "Cancel Appointment", 24);
    UIThemeHelper::setTextSizeTitle(cancelTitleText);
    cancelTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    UIThemeHelper::styleTitleText(cancelTitleText);

    cancelDialogStatusText = new sf::Text(regularFont, "", 13);
    UIThemeHelper::setTextSizeSmall(cancelDialogStatusText);
    cancelDialogStatusText->setPosition(sf::Vector2f(220.f, 605.f));
    UIThemeHelper::styleStatusText(cancelDialogStatusText);

    cancelAppointmentsLabelText = new sf::Text(regularFont, "Pending Appointments:", 16);
    UIThemeHelper::setTextSizeLabel(cancelAppointmentsLabelText);
    cancelAppointmentsLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    UIThemeHelper::styleLabelText(cancelAppointmentsLabelText);

    cancelAppointmentIdLabelText = new sf::Text(regularFont, "Enter Appointment ID to cancel:", 16);
    UIThemeHelper::setTextSizeLabel(cancelAppointmentIdLabelText);
    cancelAppointmentIdLabelText->setPosition(sf::Vector2f(220.f, 490.f));
    UIThemeHelper::styleLabelText(cancelAppointmentIdLabelText);

    // View Appointments panel and texts
    viewAppointmentsPanel.setSize(sf::Vector2f(900.f, 550.f));
    viewAppointmentsPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(viewAppointmentsPanel);

    viewAppointmentsTitleText = new sf::Text(boldFont, "My Appointments", 24);
    UIThemeHelper::setTextSizeTitle(viewAppointmentsTitleText);
    viewAppointmentsTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    UIThemeHelper::styleTitleText(viewAppointmentsTitleText);

    viewAppointmentsStatusText = new sf::Text(regularFont, "", 13);
    UIThemeHelper::setTextSizeSmall(viewAppointmentsStatusText);
    viewAppointmentsStatusText->setPosition(sf::Vector2f(220.f, 605.f));
    UIThemeHelper::styleStatusText(viewAppointmentsStatusText);

    viewAppointmentsLabelText = new sf::Text(regularFont, "Appointments:", 16);
    UIThemeHelper::setTextSizeLabel(viewAppointmentsLabelText);
    viewAppointmentsLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    UIThemeHelper::styleLabelText(viewAppointmentsLabelText);

    // View Medical Records panel and texts
    viewMedicalRecordsPanel.setSize(sf::Vector2f(900.f, 550.f));
    viewMedicalRecordsPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(viewMedicalRecordsPanel);

    viewMedicalRecordsTitleText = new sf::Text(boldFont, "My Medical Records", 24);
    UIThemeHelper::setTextSizeTitle(viewMedicalRecordsTitleText);
    viewMedicalRecordsTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    UIThemeHelper::styleTitleText(viewMedicalRecordsTitleText);

    viewMedicalRecordsStatusText = new sf::Text(regularFont, "", 13);
    UIThemeHelper::setTextSizeSmall(viewMedicalRecordsStatusText);
    viewMedicalRecordsStatusText->setPosition(sf::Vector2f(220.f, 605.f));
    UIThemeHelper::styleStatusText(viewMedicalRecordsStatusText);

    viewMedicalRecordsLabelText = new sf::Text(regularFont, "Records:", 16);
    UIThemeHelper::setTextSizeLabel(viewMedicalRecordsLabelText);
    viewMedicalRecordsLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    UIThemeHelper::styleLabelText(viewMedicalRecordsLabelText);

    // View Bills panel and texts
    viewBillsPanel.setSize(sf::Vector2f(900.f, 550.f));
    viewBillsPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(viewBillsPanel);

    viewBillsTitleText = new sf::Text(boldFont, "My Bills", 24);
    UIThemeHelper::setTextSizeTitle(viewBillsTitleText);
    viewBillsTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    UIThemeHelper::styleTitleText(viewBillsTitleText);

    viewBillsStatusText = new sf::Text(regularFont, "", 13);
    UIThemeHelper::setTextSizeSmall(viewBillsStatusText);
    viewBillsStatusText->setPosition(sf::Vector2f(220.f, 605.f));
    UIThemeHelper::styleStatusText(viewBillsStatusText);

    viewBillsLabelText = new sf::Text(regularFont, "Bills:", 16);
    UIThemeHelper::setTextSizeLabel(viewBillsLabelText);
    viewBillsLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    UIThemeHelper::styleLabelText(viewBillsLabelText);

    viewBillsTotalText = new sf::Text(regularFont, "", 15);
    UIThemeHelper::setTextSizeBody(viewBillsTotalText);
    viewBillsTotalText->setPosition(sf::Vector2f(220.f, 560.f));
    UIThemeHelper::styleBodyText(viewBillsTotalText);

    // Pay Bill panel and texts
    payBillPanel.setSize(sf::Vector2f(900.f, 550.f));
    payBillPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(payBillPanel);

    payBillTitleText = new sf::Text(boldFont, "Pay Bill", 24);
    UIThemeHelper::setTextSizeTitle(payBillTitleText);
    payBillTitleText->setPosition(sf::Vector2f(220.f, 150.f));
    UIThemeHelper::styleTitleText(payBillTitleText);

    payBillLabelText = new sf::Text(regularFont, "Unpaid Bills:", 16);
    UIThemeHelper::setTextSizeLabel(payBillLabelText);
    payBillLabelText->setPosition(sf::Vector2f(220.f, 200.f));
    UIThemeHelper::styleLabelText(payBillLabelText);

    payBillIdLabelText = new sf::Text(regularFont, "Enter Bill ID to pay:", 16);
    UIThemeHelper::setTextSizeLabel(payBillIdLabelText);
    payBillIdLabelText->setPosition(sf::Vector2f(220.f, 490.f));
    UIThemeHelper::styleLabelText(payBillIdLabelText);

    // Top Up panel and texts
    topUpPanel.setSize(sf::Vector2f(650.f, 260.f));
    topUpPanel.setPosition(sf::Vector2f(320.f, 220.f));
    UIThemeHelper::stylePanel(topUpPanel);

    topUpTitleText = new sf::Text(boldFont, "Top Up Balance", 24);
    UIThemeHelper::setTextSizeTitle(topUpTitleText);
    topUpTitleText->setPosition(sf::Vector2f(340.f, 240.f));
    UIThemeHelper::styleTitleText(topUpTitleText);

    topUpLabelText = new sf::Text(regularFont, "Enter amount to add (PKR):", 16);
    UIThemeHelper::setTextSizeLabel(topUpLabelText);
    topUpLabelText->setPosition(sf::Vector2f(340.f, 295.f));
    UIThemeHelper::styleLabelText(topUpLabelText);

    // Booking step labels
    specializationLabelText = new sf::Text(regularFont, "Specialization:", 16);
    UIThemeHelper::setTextSizeLabel(specializationLabelText);
    specializationLabelText->setPosition(sf::Vector2f(220.f, 210.f));
    UIThemeHelper::styleLabelText(specializationLabelText);

    doctorListLabelText = new sf::Text(regularFont, "Available Doctors:", 16);
    UIThemeHelper::setTextSizeLabel(doctorListLabelText);
    doctorListLabelText->setPosition(sf::Vector2f(220.f, 190.f));
    UIThemeHelper::styleLabelText(doctorListLabelText);

    dateInputLabelText = new sf::Text(regularFont, "Date (DD-MM-YYYY):", 16);
    UIThemeHelper::setTextSizeLabel(dateInputLabelText);
    dateInputLabelText->setPosition(sf::Vector2f(220.f, 280.f));
    UIThemeHelper::styleLabelText(dateInputLabelText);

    timeSlotsLabelText = new sf::Text(regularFont, "Available Time Slots:", 16);
    UIThemeHelper::setTextSizeLabel(timeSlotsLabelText);
    timeSlotsLabelText->setPosition(sf::Vector2f(220.f, 255.f));
    UIThemeHelper::styleLabelText(timeSlotsLabelText);

    timeSlotDisplayText = new sf::Text(regularFont, "", 14);
    UIThemeHelper::setTextSizeBody(timeSlotDisplayText);
    timeSlotDisplayText->setPosition(sf::Vector2f(220.f, 280.f));
    UIThemeHelper::styleBodyText(timeSlotDisplayText);

    payBillIdInput.setFont(regularFont);
    payBillIdInput.setCapacity(20);
    payBillIdInput.setPosition(sf::Vector2f(220.f, 515.f));
    payBillIdInput.setSize(sf::Vector2f(360.f, 36.f));
    UIThemeHelper::styleInput(payBillIdInput);

    confirmPayBillBtn.setFont(regularFont);
    confirmPayBillBtn.setText("Pay Bill");
    confirmPayBillBtn.setPosition(sf::Vector2f(700.f, 560.f));
    UIThemeHelper::setButtonSizeSecondary(confirmPayBillBtn);
    UIThemeHelper::styleSuccessButton(confirmPayBillBtn);

    backFromPayBillBtn.setFont(regularFont);
    backFromPayBillBtn.setText("Back");
    backFromPayBillBtn.setPosition(sf::Vector2f(890.f, 560.f));
    UIThemeHelper::setButtonSizeTertiary(backFromPayBillBtn);
    UIThemeHelper::styleNeutralButton(backFromPayBillBtn);

    // Top Up inputs and buttons
    topUpAmountInput.setFont(regularFont);
    topUpAmountInput.setCapacity(20);
    topUpAmountInput.setPosition(sf::Vector2f(340.f, 320.f));
    topUpAmountInput.setSize(sf::Vector2f(380.f, 36.f));
    UIThemeHelper::styleInput(topUpAmountInput);

    confirmTopUpBtn.setFont(regularFont);
    confirmTopUpBtn.setText("Top Up");
    confirmTopUpBtn.setPosition(sf::Vector2f(540.f, 380.f));
    UIThemeHelper::setButtonSizeSecondary(confirmTopUpBtn);
    UIThemeHelper::styleSuccessButton(confirmTopUpBtn);

    backFromTopUpBtn.setFont(regularFont);
    backFromTopUpBtn.setText("Back");
    backFromTopUpBtn.setPosition(sf::Vector2f(730.f, 380.f));
    UIThemeHelper::setButtonSizeTertiary(backFromTopUpBtn);
    UIThemeHelper::styleNeutralButton(backFromTopUpBtn);

    // Cancel Appointment inputs and buttons
    cancelAppointmentIdInput.setFont(regularFont);
    cancelAppointmentIdInput.setCapacity(20);
    cancelAppointmentIdInput.setPosition(sf::Vector2f(220.f, 515.f));
    cancelAppointmentIdInput.setSize(sf::Vector2f(360.f, 36.f));
    UIThemeHelper::styleInput(cancelAppointmentIdInput);

    confirmCancelAppointmentBtn.setFont(regularFont);
    confirmCancelAppointmentBtn.setText("Cancel Appointment");
    confirmCancelAppointmentBtn.setPosition(sf::Vector2f(690.f, 560.f));
    UIThemeHelper::setButtonSizeMedium(confirmCancelAppointmentBtn);
    UIThemeHelper::styleDangerButton(confirmCancelAppointmentBtn);

    backFromCancelAppointmentBtn.setFont(regularFont);
    backFromCancelAppointmentBtn.setText("Back");
    backFromCancelAppointmentBtn.setPosition(sf::Vector2f(890.f, 560.f));
    UIThemeHelper::setButtonSizeTertiary(backFromCancelAppointmentBtn);
    UIThemeHelper::styleNeutralButton(backFromCancelAppointmentBtn);

    // Back buttons for view panels
    backFromViewAppointmentsBtn.setFont(regularFont);
    backFromViewAppointmentsBtn.setText("Back");
    backFromViewAppointmentsBtn.setPosition(sf::Vector2f(890.f, 560.f));
    UIThemeHelper::setButtonSizeTertiary(backFromViewAppointmentsBtn);
    UIThemeHelper::styleNeutralButton(backFromViewAppointmentsBtn);

    backFromViewMedicalRecordsBtn.setFont(regularFont);
    backFromViewMedicalRecordsBtn.setText("Back");
    backFromViewMedicalRecordsBtn.setPosition(sf::Vector2f(890.f, 560.f));
    UIThemeHelper::setButtonSizeTertiary(backFromViewMedicalRecordsBtn);
    UIThemeHelper::styleNeutralButton(backFromViewMedicalRecordsBtn);

    backFromViewBillsBtn.setFont(regularFont);
    backFromViewBillsBtn.setText("Back");
    backFromViewBillsBtn.setPosition(sf::Vector2f(890.f, 560.f));
    UIThemeHelper::setButtonSizeTertiary(backFromViewBillsBtn);
    UIThemeHelper::styleNeutralButton(backFromViewBillsBtn);

    // Step 1: Specialization input
    specializationInput.setFont(regularFont);
    specializationInput.setCapacity(50);
    specializationInput.setPosition(sf::Vector2f(220.f, 235.f));
    specializationInput.setSize(sf::Vector2f(400.f, 36.f));
    UIThemeHelper::styleInput(specializationInput);

    searchDoctorsBtn.setFont(regularFont);
    searchDoctorsBtn.setText("Search");
    searchDoctorsBtn.setPosition(sf::Vector2f(640.f, 235.f));
    UIThemeHelper::setButtonSizeSmall(searchDoctorsBtn);
    UIThemeHelper::stylePrimaryButton(searchDoctorsBtn);

    // Step 2: Doctor Selection - create doctor list texts and select button
    for (int i = 0; i < 20; i++)
    {
        doctorListText[i] = new sf::Text(regularFont, "", 14);
        doctorListText[i]->setPosition(sf::Vector2f(220.f, 215.f + i * 22.f));
        UIThemeHelper::styleBodyText(doctorListText[i]);
    }

    selectDoctorBtn.setFont(regularFont);
    selectDoctorBtn.setText("Select Doctor");
    selectDoctorBtn.setPosition(sf::Vector2f(220.f, 300.f));
    UIThemeHelper::setButtonSizeSmall(selectDoctorBtn);
    UIThemeHelper::stylePrimaryButton(selectDoctorBtn);

    // Step 3: Date Input
    dateInput.setFont(regularFont);
    dateInput.setCapacity(20);
    dateInput.setPosition(sf::Vector2f(220.f, 305.f));
    dateInput.setSize(sf::Vector2f(300.f, 36.f));
    UIThemeHelper::styleInput(dateInput);

    confirmDateBtn.setFont(regularFont);
    confirmDateBtn.setText("Confirm Date");
    confirmDateBtn.setPosition(sf::Vector2f(550.f, 305.f));
    UIThemeHelper::setButtonSizeSmall(confirmDateBtn);
    UIThemeHelper::stylePrimaryButton(confirmDateBtn);

    // Step 4: Time Slots
    for (int i = 0; i < 8; i++)
    {
        timeSlotButtons[i].setFont(regularFont);
        const char *timeSlots[] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};
        timeSlotButtons[i].setText(timeSlots[i]);
        int j = i % 4;
        int row = i / 4;
        timeSlotButtons[i].setPosition(sf::Vector2f(220.f + j * 150.f, 305.f + row * 50.f));
        UIThemeHelper::setButtonSizeSmall(timeSlotButtons[i]);
        UIThemeHelper::styleNeutralButton(timeSlotButtons[i]);
    }

    // Step 5: Confirm Booking
    confirmBookingBtn.setFont(regularFont);
    confirmBookingBtn.setText("Confirm Booking");
    confirmBookingBtn.setPosition(sf::Vector2f(700.f, 510.f));
    UIThemeHelper::setButtonSizeSecondary(confirmBookingBtn);
    UIThemeHelper::styleSuccessButton(confirmBookingBtn);

    cancelBookingBtn.setFont(regularFont);
    cancelBookingBtn.setText("Cancel");
    cancelBookingBtn.setPosition(sf::Vector2f(890.f, 510.f));
    UIThemeHelper::setButtonSizeTertiary(cancelBookingBtn);
    UIThemeHelper::styleDangerButton(cancelBookingBtn);

    // Previous/Next step buttons
    previousStepBtn.setFont(regularFont);
    previousStepBtn.setText("< Previous");
    previousStepBtn.setPosition(sf::Vector2f(220.f, 510.f));
    UIThemeHelper::setButtonSizeTertiary(previousStepBtn);
    UIThemeHelper::styleNeutralButton(previousStepBtn);

    nextStepBtn.setFont(regularFont);
    nextStepBtn.setText("Next >");
    nextStepBtn.setPosition(sf::Vector2f(340.f, 510.f));
    UIThemeHelper::setButtonSizeTertiary(nextStepBtn);
    UIThemeHelper::styleNeutralButton(nextStepBtn);

    // Pending appointment list for cancel dialog
    int i;
    for (i = 0; i < 20; i++)
    {
        pendingAppointmentListText[i] = new sf::Text(regularFont, "", 12);
        pendingAppointmentListText[i]->setPosition(sf::Vector2f(220.f, 225.f + i * 14.f));
        UIThemeHelper::styleBodyText(pendingAppointmentListText[i]);
    }

    // Dashboard buttons
    int startX = 130;
    int startY = 230;
    int btnWidth = 310;
    int btnHeight = 45;
    int spacingX = 30;
    int spacingY = 15;

    bookAppointmentBtn.setFont(regularFont);
    bookAppointmentBtn.setText("Book Appointment");
    bookAppointmentBtn.setPosition(sf::Vector2f(startX, startY));
    UIThemeHelper::setButtonSizePrimary(bookAppointmentBtn);
    UIThemeHelper::stylePrimaryButton(bookAppointmentBtn);

    cancelAppointmentBtn.setFont(regularFont);
    cancelAppointmentBtn.setText("Cancel Appointment");
    cancelAppointmentBtn.setPosition(sf::Vector2f(startX + btnWidth + spacingX, startY));
    UIThemeHelper::setButtonSizePrimary(cancelAppointmentBtn);
    UIThemeHelper::stylePrimaryButton(cancelAppointmentBtn);

    viewAppointmentsBtn.setFont(regularFont);
    viewAppointmentsBtn.setText("View Appointments");
    viewAppointmentsBtn.setPosition(sf::Vector2f(startX + (btnWidth + spacingX) * 2, startY));
    UIThemeHelper::setButtonSizePrimary(viewAppointmentsBtn);
    UIThemeHelper::stylePrimaryButton(viewAppointmentsBtn);

    viewMedicalRecordsBtn.setFont(regularFont);
    viewMedicalRecordsBtn.setText("Medical Records");
    viewMedicalRecordsBtn.setPosition(sf::Vector2f(startX, startY + btnHeight + spacingY));
    UIThemeHelper::setButtonSizePrimary(viewMedicalRecordsBtn);
    UIThemeHelper::stylePrimaryButton(viewMedicalRecordsBtn);

    viewBillsBtn.setFont(regularFont);
    viewBillsBtn.setText("View Bills");
    viewBillsBtn.setPosition(sf::Vector2f(startX + btnWidth + spacingX, startY + btnHeight + spacingY));
    UIThemeHelper::setButtonSizePrimary(viewBillsBtn);
    UIThemeHelper::stylePrimaryButton(viewBillsBtn);

    payBillBtn.setFont(regularFont);
    payBillBtn.setText("Pay Bill");
    payBillBtn.setPosition(sf::Vector2f(startX + (btnWidth + spacingX) * 2, startY + btnHeight + spacingY));
    UIThemeHelper::setButtonSizePrimary(payBillBtn);
    UIThemeHelper::stylePrimaryButton(payBillBtn);

    topUpBalanceBtn.setFont(regularFont);
    topUpBalanceBtn.setText("Top Up Balance");
    topUpBalanceBtn.setPosition(sf::Vector2f(startX, startY + (btnHeight + spacingY) * 2));
    UIThemeHelper::setButtonSizePrimary(topUpBalanceBtn);
    UIThemeHelper::stylePrimaryButton(topUpBalanceBtn);

    return true;
}

void PatientDash::updateDoctorList()
{
    int i;
    int dispIdx;
    Doctor *doctors;
    char docStr[100];
    int docIdx;
    int charIdx;
    const char *specialization;

    if (filteredDoctors == nullptr)
    {
        doctorListCount = 0;
        return;
    }

    doctorListCount = filteredDoctors->size();
    if (doctorListCount > 20)
    {
        doctorListCount = 20;
    }

    doctors = filteredDoctors->getAll();
    for (i = 0; i < doctorListCount; i++)
    {
        StringHelper::stringCopy(docStr, "ID: ", 100);
        docIdx = 0;
        while (docStr[docIdx] != '\0')
        {
            docIdx++;
        }
        ConversionHelper::intToString(doctors[i].getID(), docStr + docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0')
        {
            docIdx++;
        }

        StringHelper::stringCopy(docStr + docIdx, " | ", 100 - docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0')
        {
            docIdx++;
        }
        StringHelper::stringCopy(docStr + docIdx, doctors[i].getName(), 100 - docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0')
        {
            docIdx++;
        }

        specialization = doctors[i].getSpecialization();
        if (specialization == nullptr)
        {
            specialization = "";
        }

        StringHelper::stringCopy(docStr + docIdx, " | Spec: ", 100 - docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0')
        {
            docIdx++;
        }
        StringHelper::stringCopy(docStr + docIdx, specialization, 100 - docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0')
        {
            docIdx++;
        }

        StringHelper::stringCopy(docStr + docIdx, " | Fee: ", 100 - docIdx);
        docIdx = 0;
        while (docStr[docIdx] != '\0')
        {
            docIdx++;
        }
        ConversionHelper::doubleToString(doctors[i].getFee(), docStr + docIdx);

        if (doctorListText[i] != nullptr)
        {
            doctorListText[i]->setString(docStr);
        }
    }
}

void PatientDash::updateTimeSlotDisplay()
{
    char buffer[500];
    int i;

    StringHelper::stringCopy(buffer, "Select a time slot: ", 500);
    int len = StringHelper::stringLength(buffer);

    for (i = 0; i < 8; i++)
    {
        if (i > 0)
        {
            StringHelper::stringCopy(buffer + len, " | ", 500 - len);
            len = StringHelper::stringLength(buffer);
        }
        StringHelper::stringCopy(buffer + len, "09:00 10:00 11:00 12:00 13:00 14:00 15:00 16:00", 500 - len);
        break;
    }

    if (timeSlotDisplayText != nullptr)
    {
        timeSlotDisplayText->setString("Click on a time slot below to select:");
    }

    // Update timeslot button colors based on availability
    const char *timeSlots[] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};

    for (i = 0; i < 8; i++)
    {
        bool isBooked = false;

        if (allAppointments != nullptr)
        {
            int j;
            Appointment *appointmentsArray;
            appointmentsArray = allAppointments->getAll();

            for (j = 0; j < allAppointments->size(); j++)
            {
                if (StringHelper::textEquals(appointmentsArray[j].getDate(), selectedDate) &&
                    StringHelper::textEquals(appointmentsArray[j].getTimeSlot(), timeSlots[i]) &&
                    appointmentsArray[j].getDoctorID() == selectedDoctorID &&
                    StringHelper::textEquals(appointmentsArray[j].getStatus(), "pending"))
                {
                    isBooked = true;
                    break;
                }
            }
        }

        if (isBooked)
        {
            timeSlotButtons[i].setFillColor(sf::Color(231, 76, 60));
        }
        else
        {
            timeSlotButtons[i].setFillColor(sf::Color(189, 195, 199));
        }
    }
}

void PatientDash::showStep(BookingStep step)
{
    currentBookingStep = step;
}

void PatientDash::setPatient(Patient *patientPtr)
{
    patient = patientPtr;

    if (patient == nullptr)
    {
        cancelBookingMode();
        closeCancelAppointmentMode();
        closeViewAppointmentsMode();
        closeViewMedicalRecordsMode();
        closeViewBillsMode();
        closePayBillMode();
        closeTopUpMode();
        if (patientNameText != nullptr)
        {
            patientNameText->setString("");
        }
        if (balanceText != nullptr)
        {
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
    while (balanceBuffer[i] != '\0')
    {
        i++;
    }

    ConversionHelper::doubleToString(patient->getBalance(), balanceStr);
    j = 0;
    while (balanceStr[j] != '\0' && i < 199)
    {
        balanceBuffer[i] = balanceStr[j];
        i++;
        j++;
    }
    balanceBuffer[i] = '\0';

    if (patientNameText != nullptr)
    {
        patientNameText->setString(nameBuffer);
    }
    if (balanceText != nullptr)
    {
        balanceText->setString(balanceBuffer);
    }
}

void PatientDash::draw(sf::RenderWindow &window) const
{
    window.draw(dashboardCard);

    if (titleText != nullptr)
    {
        window.draw(*titleText);
    }
    if (patientNameText != nullptr)
    {
        window.draw(*patientNameText);
    }
    if (balanceText != nullptr)
    {
        window.draw(*balanceText);
    }
    if (statusText != nullptr)
    {
        window.draw(*statusText);
    }

    bookAppointmentBtn.draw(window);
    cancelAppointmentBtn.draw(window);
    viewAppointmentsBtn.draw(window);
    viewMedicalRecordsBtn.draw(window);
    viewBillsBtn.draw(window);
    payBillBtn.draw(window);
    topUpBalanceBtn.draw(window);

    if (cancelAppointmentMode)
    {
        window.draw(cancelPanel);
        if (cancelTitleText != nullptr)
        {
            window.draw(*cancelTitleText);
        }
        if (cancelDialogStatusText != nullptr)
        {
            window.draw(*cancelDialogStatusText);
        }
        if (cancelAppointmentsLabelText != nullptr)
        {
            window.draw(*cancelAppointmentsLabelText);
        }
        if (cancelAppointmentIdLabelText != nullptr)
        {
            window.draw(*cancelAppointmentIdLabelText);
        }

        int i;
        for (i = 0; i < pendingAppointmentCount; i++)
        {
            if (pendingAppointmentListText[i] != nullptr)
            {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        cancelAppointmentIdInput.draw(window);
        confirmCancelAppointmentBtn.draw(window);
        backFromCancelAppointmentBtn.draw(window);
    }
    else if (viewAppointmentsMode)
    {
        window.draw(viewAppointmentsPanel);
        if (viewAppointmentsTitleText != nullptr)
        {
            window.draw(*viewAppointmentsTitleText);
        }
        if (viewAppointmentsStatusText != nullptr)
        {
            window.draw(*viewAppointmentsStatusText);
        }
        if (viewAppointmentsLabelText != nullptr)
        {
            window.draw(*viewAppointmentsLabelText);
        }

        int i;
        for (i = 0; i < viewedAppointmentCount; i++)
        {
            if (pendingAppointmentListText[i] != nullptr)
            {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        backFromViewAppointmentsBtn.draw(window);
    }
    else if (viewMedicalRecordsMode)
    {
        window.draw(viewMedicalRecordsPanel);
        if (viewMedicalRecordsTitleText != nullptr)
        {
            window.draw(*viewMedicalRecordsTitleText);
        }
        if (viewMedicalRecordsStatusText != nullptr)
        {
            window.draw(*viewMedicalRecordsStatusText);
        }
        if (viewMedicalRecordsLabelText != nullptr)
        {
            window.draw(*viewMedicalRecordsLabelText);
        }

        int i;
        for (i = 0; i < viewedMedicalRecordCount; i++)
        {
            if (pendingAppointmentListText[i] != nullptr)
            {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        backFromViewMedicalRecordsBtn.draw(window);
    }
    else if (viewBillsMode)
    {
        window.draw(viewBillsPanel);
        if (viewBillsTitleText != nullptr)
        {
            window.draw(*viewBillsTitleText);
        }
        if (viewBillsStatusText != nullptr)
        {
            window.draw(*viewBillsStatusText);
        }
        if (viewBillsLabelText != nullptr)
        {
            window.draw(*viewBillsLabelText);
        }
        if (viewBillsTotalText != nullptr)
        {
            window.draw(*viewBillsTotalText);
        }

        int i;
        for (i = 0; i < viewedBillCount; i++)
        {
            if (pendingAppointmentListText[i] != nullptr)
            {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        backFromViewBillsBtn.draw(window);
    }
    else if (payBillMode)
    {
        window.draw(payBillPanel);
        if (payBillTitleText != nullptr)
        {
            window.draw(*payBillTitleText);
        }
        if (viewBillsStatusText != nullptr)
        {
            window.draw(*viewBillsStatusText);
        }
        if (payBillLabelText != nullptr)
        {
            window.draw(*payBillLabelText);
        }
        if (viewBillsTotalText != nullptr)
        {
            window.draw(*viewBillsTotalText);
        }

        int i;
        for (i = 0; i < viewedBillCount; i++)
        {
            if (pendingAppointmentListText[i] != nullptr)
            {
                window.draw(*pendingAppointmentListText[i]);
            }
        }

        if (payBillIdLabelText != nullptr)
        {
            window.draw(*payBillIdLabelText);
        }
        payBillIdInput.draw(window);
        confirmPayBillBtn.draw(window);
        backFromPayBillBtn.draw(window);
    }
    else if (topUpMode)
    {
        window.draw(topUpPanel);

        if (topUpTitleText != nullptr)
        {
            window.draw(*topUpTitleText);
        }

        if (topUpLabelText != nullptr)
        {
            window.draw(*topUpLabelText);
        }
        topUpAmountInput.draw(window);
        confirmTopUpBtn.draw(window);
        backFromTopUpBtn.draw(window);
    }
    else if (bookingMode)
    {
        window.draw(bookingPanel);
        if (bookingTitleText != nullptr)
        {
            window.draw(*bookingTitleText);
        }
        if (bookingStepIndicatorText != nullptr)
        {
            window.draw(*bookingStepIndicatorText);
        }
        if (bookingDialogStatusText != nullptr)
        {
            window.draw(*bookingDialogStatusText);
        }

        // Step 1: Specialization
        if (currentBookingStep == STEP_SPECIALIZATION)
        {
            if (specializationLabelText != nullptr)
            {
                window.draw(*specializationLabelText);
            }
            specializationInput.draw(window);
            searchDoctorsBtn.draw(window);
        }
        // Step 2: Doctor Selection
        else if (currentBookingStep == STEP_DOCTOR_SELECTION)
        {
            if (doctorListLabelText != nullptr)
            {
                window.draw(*doctorListLabelText);
            }
            int i;
            for (i = 0; i < doctorListCount; i++)
            {
                if (doctorListText[i] != nullptr)
                {
                    if (selectedDoctorIndex == i)
                    {
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
        else if (currentBookingStep == STEP_DATE_INPUT)
        {
            if (dateInputLabelText != nullptr)
            {
                window.draw(*dateInputLabelText);
            }
            dateInput.draw(window);
            confirmDateBtn.draw(window);
        }
        // Step 4: Time Slot Selection
        else if (currentBookingStep == STEP_TIME_SLOT)
        {
            if (timeSlotsLabelText != nullptr)
            {
                window.draw(*timeSlotsLabelText);
            }
            if (timeSlotDisplayText != nullptr)
            {
                window.draw(*timeSlotDisplayText);
            }
            int i;
            for (i = 0; i < 8; i++)
            {
                timeSlotButtons[i].draw(window);
            }
        }
        // Step 5: Confirm
        else if (currentBookingStep == STEP_CONFIRM)
        {
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
        if (currentBookingStep > STEP_SPECIALIZATION)
        {
            previousStepBtn.draw(window);
        }
        if (currentBookingStep < STEP_CONFIRM)
        {
            nextStepBtn.draw(window);
        }

        confirmBookingBtn.draw(window);
        cancelBookingBtn.draw(window);
    }
}

void PatientDash::handleMouseClick(sf::RenderWindow &window)
{
    sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (cancelAppointmentMode)
    {
        if (cancelAppointmentIdInput.contains(mouseWorldPosition))
        {
            cancelAppointmentIdInput.setActive(true);
            return;
        }

        if (confirmCancelAppointmentBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            cancelAppointmentRequested = true;
            return;
        }

        if (backFromCancelAppointmentBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeCancelAppointmentMode();
            return;
        }

        cancelAppointmentIdInput.setActive(false);
        return;
    }

    if (viewAppointmentsMode)
    {
        if (backFromViewAppointmentsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeViewAppointmentsMode();
            return;
        }

        return;
    }

    if (viewMedicalRecordsMode)
    {
        if (backFromViewMedicalRecordsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeViewMedicalRecordsMode();
            return;
        }

        return;
    }

    if (viewBillsMode)
    {
        if (backFromViewBillsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeViewBillsMode();
            return;
        }

        return;
    }

    if (payBillMode)
    {
        if (payBillIdInput.contains(mouseWorldPosition))
        {
            payBillIdInput.setActive(true);
            return;
        }

        if (confirmPayBillBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            payBillRequested = true;
            return;
        }

        if (backFromPayBillBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closePayBillMode();
            return;
        }

        payBillIdInput.setActive(false);
        return;
    }

    if (topUpMode)
    {
        if (topUpAmountInput.contains(mouseWorldPosition))
        {
            topUpAmountInput.setActive(true);
            return;
        }

        if (confirmTopUpBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            topUpRequested = true;
            return;
        }

        if (backFromTopUpBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeTopUpMode();
            return;
        }

        topUpAmountInput.setActive(false);
        return;
    }

    if (bookingMode)
    {
        if (currentBookingStep == STEP_SPECIALIZATION)
        {
            if (specializationInput.contains(mouseWorldPosition))
            {
                specializationInput.setActive(true);
                return;
            }
            if (searchDoctorsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
            {
                if (StringHelper::stringLength(specializationInput.getText()) > 0)
                {
                    StringHelper::stringCopy(selectedSpecialization, specializationInput.getText(), 100);
                    specializationSearchRequested = true;
                    setDialogStatus("Searching for doctors...");
                }
                else
                {
                    setDialogStatus("Please enter a specialization.");
                }
                return;
            }
        }
        else if (currentBookingStep == STEP_DOCTOR_SELECTION)
        {
            int i;
            for (i = 0; i < doctorListCount; i++)
            {
                sf::Text &docText = *doctorListText[i];
                if (docText.getGlobalBounds().contains(mouseWorldPosition))
                {
                    selectedDoctorIndex = i;
                    if (filteredDoctors != nullptr)
                    {
                        selectedDoctorID = filteredDoctors->getAll()[i].getID();
                    }
                    advanceBookingStep();
                    return;
                }
            }
        }
        else if (currentBookingStep == STEP_DATE_INPUT)
        {
            if (dateInput.contains(mouseWorldPosition))
            {
                dateInput.setActive(true);
                return;
            }
            if (confirmDateBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
            {
                const char *inputDate = dateInput.getText();
                // Normalize and validate format (accept loose forms like D-M-YYYY or D/M/YYYY)
                char normalized[11];
                if (!TimeHelper::normalizeToYMD(inputDate, normalized, sizeof(normalized)))
                {
                    setDialogStatus("Invalid appointment date format.");
                    return;
                }

                // Validate date is after today
                if (!TimeHelper::isDateAfterToday(normalized))
                {
                    setDialogStatus("Appointment date must be after today.");
                    return;
                }

                StringHelper::stringCopy(selectedDate, normalized, 20);
                dateInput.setText(normalized);
                advanceBookingStep();
                return;
            }
        }
        else if (currentBookingStep == STEP_TIME_SLOT)
        {
            int i;
            for (i = 0; i < 8; i++)
            {
                if (timeSlotButtons[i].getShape().getGlobalBounds().contains(mouseWorldPosition))
                {
                    // Check availability first
                    const char *slots[] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};
                    bool isBooked = false;
                    if (allAppointments != nullptr)
                    {
                        int j;
                        Appointment *appointmentsArray = allAppointments->getAll();
                        for (j = 0; j < allAppointments->size(); j++)
                        {
                            if (StringHelper::textEquals(appointmentsArray[j].getDate(), selectedDate) &&
                                StringHelper::textEquals(appointmentsArray[j].getTimeSlot(), slots[i]) &&
                                appointmentsArray[j].getDoctorID() == selectedDoctorID &&
                                StringHelper::textEquals(appointmentsArray[j].getStatus(), "pending"))
                            {
                                isBooked = true;
                                break;
                            }
                        }
                    }

                    if (isBooked)
                    {
                        setDialogStatus("Selected time slot is unavailable.");
                        return;
                    }

                    // Reset all button colors to gray
                    int j;
                    for (j = 0; j < 8; j++)
                    {
                        timeSlotButtons[j].setFillColor(sf::Color(189, 195, 199));
                        timeSlotButtons[j].setOutlineColor(sf::Color(189, 195, 199));
                    }
                    // Highlight selected button in green
                    selectedTimeSlotIndex = i;
                    timeSlotButtons[i].setFillColor(sf::Color(46, 204, 113));
                    timeSlotButtons[i].setOutlineColor(sf::Color(39, 174, 96));
                    StringHelper::stringCopy(selectedTimeSlot, slots[i], 10);
                    advanceBookingStep();
                    return;
                }
            }
        }
        else if (currentBookingStep == STEP_CONFIRM)
        {
            if (confirmBookingBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
            {
                bookAppointmentRequested = true;
                return;
            }
        }

        if (previousStepBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            if (currentBookingStep > STEP_SPECIALIZATION)
            {
                regressBookingStep();
            }
            return;
        }

        if (nextStepBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            if (currentBookingStep < STEP_CONFIRM)
            {
                advanceBookingStep();
            }
            return;
        }

        if (cancelBookingBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            cancelBookingMode();
            return;
        }

        return;
    }

    if (bookAppointmentBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        bookAppointmentClicked = true;
        startBookingMode();
    }
    if (cancelAppointmentBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        cancelAppointmentClicked = true;
    }
    if (viewAppointmentsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        viewAppointmentsClicked = true;
    }
    if (viewMedicalRecordsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        viewMedicalRecordsClicked = true;
    }
    if (viewBillsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        viewBillsClicked = true;
    }
    if (payBillBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        payBillClicked = true;
    }
    if (topUpBalanceBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        topUpBalanceClicked = true;
    }
}

void PatientDash::handleTextEntered(char32_t unicode)
{
    if (cancelAppointmentMode)
    {
        cancelAppointmentIdInput.handleTextEntered(unicode);
        return;
    }

    if (viewAppointmentsMode)
    {
        return;
    }

    if (viewMedicalRecordsMode)
    {
        return;
    }

    if (viewBillsMode)
    {
        return;
    }

    if (payBillMode)
    {
        payBillIdInput.handleTextEntered(unicode);
        return;
    }

    if (topUpMode)
    {
        topUpAmountInput.handleTextEntered(unicode);
        return;
    }

    if (!bookingMode)
    {
        return;
    }
    // Confirm booking logic
    if (currentBookingStep == STEP_SPECIALIZATION)
    {
        specializationInput.handleTextEntered(unicode);
    }
    else if (currentBookingStep == STEP_DATE_INPUT)
    {
        dateInput.handleTextEntered(unicode);
    }
}

void PatientDash::startBookingMode()
{
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

    if (filteredDoctors != nullptr)
    {
        delete filteredDoctors;
        filteredDoctors = nullptr;
    }
}

void PatientDash::startCancelAppointmentMode()
{
    cancelAppointmentMode = true;
    cancelAppointmentRequested = false;
    cancelAppointmentIdInput.clear();
    cancelAppointmentIdInput.setActive(false);

    if (pendingAppointments != nullptr)
    {
        updatePendingAppointmentList();
    }

    if (cancelDialogStatusText != nullptr)
    {
        cancelDialogStatusText->setString("Enter the appointment ID to cancel.");
    }
}

void PatientDash::closeCancelAppointmentMode()
{
    cancelAppointmentMode = false;
    cancelAppointmentRequested = false;
    cancelAppointmentIdInput.clear();
    cancelAppointmentIdInput.setActive(false);
    pendingAppointmentCount = 0;

    if (pendingAppointments != nullptr)
    {
        delete pendingAppointments;
        pendingAppointments = nullptr;
    }

    pendingAppointmentDoctors = nullptr;
}

void PatientDash::startViewAppointmentsMode()
{
    viewAppointmentsMode = true;

    if (viewAppointmentsStatusText != nullptr)
    {
        viewAppointmentsStatusText->setString("");
    }

    if (viewedAppointments != nullptr)
    {
        updatePendingAppointmentList();
    }
}

void PatientDash::closeViewAppointmentsMode()
{
    viewAppointmentsMode = false;
    viewedAppointmentCount = 0;

    if (viewedAppointments != nullptr)
    {
        delete viewedAppointments;
        viewedAppointments = nullptr;
    }

    viewedAppointmentDoctors = nullptr;
}

void PatientDash::startViewMedicalRecordsMode()
{
    viewMedicalRecordsMode = true;

    if (viewMedicalRecordsStatusText != nullptr)
    {
        viewMedicalRecordsStatusText->setString("");
    }

    if (viewedMedicalRecords != nullptr)
    {
        updatePendingAppointmentList();
    }
}

void PatientDash::closeViewMedicalRecordsMode()
{
    viewMedicalRecordsMode = false;
    viewedMedicalRecordCount = 0;

    if (viewedMedicalRecords != nullptr)
    {
        delete viewedMedicalRecords;
        viewedMedicalRecords = nullptr;
    }

    viewedMedicalRecordDoctors = nullptr;
}

void PatientDash::startViewBillsMode()
{
    viewBillsMode = true;

    resetBillModeStatus();

    if (viewedBills != nullptr)
    {
        updatePendingAppointmentList();
    }
}

void PatientDash::startPayBillMode()
{
    payBillMode = true;
    payBillRequested = false;
    payBillIdInput.clear();
    payBillIdInput.setActive(false);

    resetBillModeStatus();

    if (viewedBills != nullptr)
    {
        updatePendingAppointmentList();
    }
}

void PatientDash::closePayBillMode()
{
    payBillMode = false;
    payBillRequested = false;
    payBillIdInput.clear();
    payBillIdInput.setActive(false);

    clearViewedBillsState();
}

void PatientDash::startTopUpMode()
{
    topUpMode = true;
    topUpRequested = false;
    topUpAttempts = 0;
    topUpAmountInput.clear();
    topUpAmountInput.setActive(false);
}

void PatientDash::closeTopUpMode()
{
    topUpMode = false;
    topUpRequested = false;
    topUpAmountInput.clear();
    topUpAmountInput.setActive(false);
    topUpAttempts = 0;
}

void PatientDash::resetBillModeStatus()
{
    if (viewBillsStatusText != nullptr)
    {
        viewBillsStatusText->setString("");
    }
}

void PatientDash::clearViewedBillsState()
{
    viewedBillCount = 0;
    outstandingUnpaidAmount = 0.0;

    if (viewedBills != nullptr)
    {
        delete viewedBills;
        viewedBills = nullptr;
    }

    if (viewBillsTotalText != nullptr)
    {
        viewBillsTotalText->setString("");
    }
}

void PatientDash::closeViewBillsMode()
{
    viewBillsMode = false;

    clearViewedBillsState();
}

void PatientDash::cancelBookingMode()
{
    bookingMode = false;
    bookAppointmentRequested = false;
    bookingFocusedField = 0;
    currentBookingStep = STEP_SPECIALIZATION;

    specializationInput.clear();
    specializationInput.setActive(false);
    dateInput.clear();
    dateInput.setActive(false);

    if (filteredDoctors != nullptr)
    {
        delete filteredDoctors;
        filteredDoctors = nullptr;
    }
}

void PatientDash::advanceBookingStep()
{
    if (currentBookingStep == STEP_SPECIALIZATION)
    {
        currentBookingStep = STEP_DOCTOR_SELECTION;
        updateStepIndicator();
        updateDoctorList();
        setDialogStatus("Select a doctor from the list below.");
    }
    else if (currentBookingStep == STEP_DOCTOR_SELECTION)
    {
        currentBookingStep = STEP_DATE_INPUT;
        updateStepIndicator();
        setDialogStatus("Enter appointment date in DD-MM-YYYY format (current year or later).");
        dateInput.setActive(true);
    }
    else if (currentBookingStep == STEP_DATE_INPUT)
    {
        currentBookingStep = STEP_TIME_SLOT;
        updateStepIndicator();
        updateTimeSlotDisplay();
        setDialogStatus("Select an available time slot.");
    }
    else if (currentBookingStep == STEP_TIME_SLOT)
    {
        currentBookingStep = STEP_CONFIRM;
        updateStepIndicator();
        setDialogStatus("Review your booking details and click Confirm to proceed.");
    }
}

void PatientDash::regressBookingStep()
{
    if (currentBookingStep == STEP_CONFIRM)
    {
        currentBookingStep = STEP_TIME_SLOT;
        updateStepIndicator();
        setDialogStatus("Select an available time slot.");
    }
    else if (currentBookingStep == STEP_TIME_SLOT)
    {
        currentBookingStep = STEP_DATE_INPUT;
        updateStepIndicator();
        setDialogStatus("Enter appointment date in DD-MM-YYYY format.");
    }
    else if (currentBookingStep == STEP_DATE_INPUT)
    {
        currentBookingStep = STEP_DOCTOR_SELECTION;
        updateStepIndicator();
        setDialogStatus("Select a doctor from the list.");
    }
    else if (currentBookingStep == STEP_DOCTOR_SELECTION)
    {
        currentBookingStep = STEP_SPECIALIZATION;
        updateStepIndicator();
        setDialogStatus("Enter a specialization to search for doctors.");
    }
}

bool PatientDash::isBookingMode() const
{
    return bookingMode;
}

bool PatientDash::consumeBookAppointmentRequest()
{
    if (!bookAppointmentRequested)
    {
        return false;
    }

    bookAppointmentRequested = false;
    return true;
}

bool PatientDash::consumeSpecializationSearchRequest()
{
    if (!specializationSearchRequested)
    {
        return false;
    }

    specializationSearchRequested = false;
    return true;
}

bool PatientDash::isCancelAppointmentMode() const
{
    return cancelAppointmentMode;
}

bool PatientDash::consumeCancelAppointmentRequest()
{
    if (!cancelAppointmentRequested)
    {
        return false;
    }

    cancelAppointmentRequested = false;
    return true;
}

const char *PatientDash::getSpecializationText() const
{
    return selectedSpecialization;
}

int PatientDash::getSelectedDoctorID() const
{
    return selectedDoctorID;
}

const char *PatientDash::getBookingDateText() const
{
    return selectedDate;
}

const char *PatientDash::getBookingTimeText() const
{
    return selectedTimeSlot;
}

Storage<Doctor> *PatientDash::getFilteredDoctors() const
{
    return filteredDoctors;
}

const char *PatientDash::getCancelAppointmentIDText() const
{
    return cancelAppointmentIdInput.getText();
}

const char *PatientDash::getPayBillIDText() const
{
    return payBillIdInput.getText();
}

const char *PatientDash::getTopUpAmountText() const
{
    return topUpAmountInput.getText();
}

bool PatientDash::isBookAppointmentClicked() const
{
    return bookAppointmentClicked;
}

void PatientDash::setFilteredDoctors(Storage<Doctor> *doctors)
{
    if (filteredDoctors != nullptr)
    {
        delete filteredDoctors;
    }
    filteredDoctors = doctors;
    if (doctors != nullptr)
    {
        updateDoctorList();
    }
}

void PatientDash::setPendingAppointments(Storage<Appointment> *appointments, Storage<Doctor> *doctors)
{
    if (pendingAppointments != nullptr)
    {
        delete pendingAppointments;
    }

    pendingAppointments = appointments;
    pendingAppointmentDoctors = doctors;

    if (appointments != nullptr)
    {
        updatePendingAppointmentList();
    }
    else
    {
        pendingAppointmentCount = 0;
    }
}

void PatientDash::setViewedAppointments(Storage<Appointment> *appointments, Storage<Doctor> *doctors)
{
    if (viewedAppointments != nullptr)
    {
        delete viewedAppointments;
    }

    viewedAppointments = appointments;
    viewedAppointmentDoctors = doctors;

    if (appointments != nullptr)
    {
        updatePendingAppointmentList();
    }
    else
    {
        viewedAppointmentCount = 0;
    }
}

void PatientDash::setViewedMedicalRecords(Storage<Prescription> *records, Storage<Doctor> *doctors)
{
    if (viewedMedicalRecords != nullptr)
    {
        delete viewedMedicalRecords;
    }

    viewedMedicalRecords = records;
    viewedMedicalRecordDoctors = doctors;

    if (records != nullptr)
    {
        updatePendingAppointmentList();
    }
    else
    {
        viewedMedicalRecordCount = 0;
    }
}

void PatientDash::setViewedBills(Storage<Bill> *bills)
{
    if (viewedBills != nullptr)
    {
        delete viewedBills;
    }

    viewedBills = bills;

    if (bills != nullptr)
    {
        updatePendingAppointmentList();
    }
    else
    {
        viewedBillCount = 0;
        outstandingUnpaidAmount = 0.0;
    }
}

void PatientDash::setAllAppointments(Storage<Appointment> *appointments)
{
    allAppointments = appointments;
}

BookingStep PatientDash::getCurrentBookingStep() const
{
    return currentBookingStep;
}

bool PatientDash::isCancelAppointmentClicked() const
{
    return cancelAppointmentClicked;
}

bool PatientDash::isViewAppointmentsClicked() const
{
    return viewAppointmentsClicked;
}

bool PatientDash::isViewMedicalRecordsClicked() const
{
    return viewMedicalRecordsClicked;
}

bool PatientDash::isViewBillsClicked() const
{
    return viewBillsClicked;
}

bool PatientDash::isPayBillClicked() const
{
    return payBillClicked;
}

bool PatientDash::isTopUpBalanceClicked() const
{
    return topUpBalanceClicked;
}

bool PatientDash::consumeTopUpRequest()
{
    if (!topUpRequested)
    {
        return false;
    }

    topUpRequested = false;
    return true;
}

void PatientDash::incrementTopUpAttempts()
{
    topUpAttempts++;
}

int PatientDash::getTopUpAttempts() const
{
    return topUpAttempts;
}

bool PatientDash::consumePayBillRequest()
{
    if (!payBillRequested)
    {
        return false;
    }

    payBillRequested = false;
    return true;
}

void PatientDash::updatePendingAppointmentList()
{
    int i;
    int j;
    Appointment *appointmentsArray;
    Appointment *appointment;
    Prescription *recordsArray;
    Prescription *record;
    Bill *billsArray;
    Bill *bill;
    Doctor *doctor;
    const char *doctorName;
    char row[400];
    char amountBuffer[32];
    char totalBuffer[400];
    int rowLen;

    if (cancelAppointmentMode)
    {
        if (pendingAppointments == nullptr)
        {
            pendingAppointmentCount = 0;
            return;
        }

        pendingAppointmentCount = pendingAppointments->size();
        if (pendingAppointmentCount > 20)
        {
            pendingAppointmentCount = 20;
        }

        appointmentsArray = pendingAppointments->getAll();
        for (i = 0; i < pendingAppointmentCount; i++)
        {
            appointment = &appointmentsArray[i];
            doctorName = "Unknown Doctor";

            if (pendingAppointmentDoctors != nullptr)
            {
                doctor = pendingAppointmentDoctors->findByID(appointment->getDoctorID());
                if (doctor != nullptr)
                {
                    doctorName = doctor->getName();
                }
            }

            row[0] = '\0';
            StringHelper::stringCopy(row, "Appointment ID: ", 400);
            rowLen = StringHelper::stringLength(row);
            ConversionHelper::intToString(appointment->getID(), row + rowLen);

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

            if (pendingAppointmentListText[i] != nullptr)
            {
                pendingAppointmentListText[i]->setString(row);
            }
        }

        for (j = pendingAppointmentCount; j < 20; j++)
        {
            if (pendingAppointmentListText[j] != nullptr)
            {
                pendingAppointmentListText[j]->setString("");
            }
        }
        return;
    }

    if (viewAppointmentsMode)
    {
        if (viewedAppointments == nullptr)
        {
            viewedAppointmentCount = 0;
            return;
        }

        viewedAppointmentCount = viewedAppointments->size();
        if (viewedAppointmentCount > 20)
        {
            viewedAppointmentCount = 20;
        }

        appointmentsArray = viewedAppointments->getAll();
        for (i = 0; i < viewedAppointmentCount; i++)
        {
            appointment = &appointmentsArray[i];
            doctorName = "Unknown Doctor";

            if (viewedAppointmentDoctors != nullptr)
            {
                doctor = viewedAppointmentDoctors->findByID(appointment->getDoctorID());
                if (doctor != nullptr)
                {
                    doctorName = doctor->getName();
                }
            }

            row[0] = '\0';
            StringHelper::stringCopy(row, "ID: ", 400);
            rowLen = StringHelper::stringLength(row);
            ConversionHelper::intToString(appointment->getID(), row + rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, doctorName, 400 - rowLen);

            rowLen = StringHelper::stringLength(row);
            StringHelper::stringCopy(row + rowLen, " | ", 400 - rowLen);
            rowLen = StringHelper::stringLength(row);
            if (doctor != nullptr)
            {
                StringHelper::stringCopy(row + rowLen, doctor->getSpecialization(), 400 - rowLen);
            }
            else
            {
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

            if (pendingAppointmentListText[i] != nullptr)
            {
                pendingAppointmentListText[i]->setString(row);
            }
        }

        for (j = viewedAppointmentCount; j < 20; j++)
        {
            if (pendingAppointmentListText[j] != nullptr)
            {
                pendingAppointmentListText[j]->setString("");
            }
        }
        return;
    }

    if (viewMedicalRecordsMode)
    {
        if (viewedMedicalRecords == nullptr)
        {
            viewedMedicalRecordCount = 0;
            return;
        }

        viewedMedicalRecordCount = viewedMedicalRecords->size();
        if (viewedMedicalRecordCount > 20)
        {
            viewedMedicalRecordCount = 20;
        }

        recordsArray = viewedMedicalRecords->getAll();
        for (i = 0; i < viewedMedicalRecordCount; i++)
        {
            record = &recordsArray[i];
            doctorName = "Unknown Doctor";

            if (viewedMedicalRecordDoctors != nullptr)
            {
                doctor = viewedMedicalRecordDoctors->findByID(record->getDoctorID());
                if (doctor != nullptr)
                {
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

            if (pendingAppointmentListText[i] != nullptr)
            {
                pendingAppointmentListText[i]->setString(row);
            }
        }

        for (j = viewedMedicalRecordCount; j < 20; j++)
        {
            if (pendingAppointmentListText[j] != nullptr)
            {
                pendingAppointmentListText[j]->setString("");
            }
        }
        return;
    }

    if (viewBillsMode || payBillMode)
    {
        if (viewedBills == nullptr)
        {
            viewedBillCount = 0;
            outstandingUnpaidAmount = 0.0;
            if (viewBillsTotalText != nullptr)
            {
                viewBillsTotalText->setString("");
            }
            return;
        }

        viewedBillCount = viewedBills->size();
        if (viewedBillCount > 20)
        {
            viewedBillCount = 20;
        }

        outstandingUnpaidAmount = 0.0;
        billsArray = viewedBills->getAll();
        for (i = 0; i < viewedBillCount; i++)
        {
            bill = &billsArray[i];

            row[0] = '\0';
            StringHelper::stringCopy(row, "Bill ID: ", 400);
            rowLen = StringHelper::stringLength(row);
            ConversionHelper::intToString(bill->getID(), row + rowLen);

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

            if (!StringHelper::textEquals(bill->getStatus(), "paid") && !StringHelper::textEquals(bill->getStatus(), "cancelled"))
            {
                outstandingUnpaidAmount = outstandingUnpaidAmount + bill->getAmount();
            }

            if (pendingAppointmentListText[i] != nullptr)
            {
                pendingAppointmentListText[i]->setString(row);
            }
        }

        for (j = viewedBillCount; j < 20; j++)
        {
            if (pendingAppointmentListText[j] != nullptr)
            {
                pendingAppointmentListText[j]->setString("");
            }
        }

        if (viewBillsTotalText != nullptr)
        {
            totalBuffer[0] = '\0';
            StringHelper::stringCopy(totalBuffer, "Total Outstanding Unpaid: PKR ", 400);
            rowLen = StringHelper::stringLength(totalBuffer);
            ConversionHelper::doubleToString(outstandingUnpaidAmount, amountBuffer);
            StringHelper::stringCopy(totalBuffer + rowLen, amountBuffer, 400 - rowLen);
            viewBillsTotalText->setString(totalBuffer);
        }
    }
}

void PatientDash::clearClickStates()
{
    bookAppointmentClicked = false;
    cancelAppointmentClicked = false;
    viewAppointmentsClicked = false;
    viewMedicalRecordsClicked = false;
    viewBillsClicked = false;
    payBillClicked = false;
    topUpBalanceClicked = false;
}

void PatientDash::setStatus(const char *message)
{
    if (message != nullptr && statusText != nullptr)
    {
        statusText->setString(message);
    }
}

void PatientDash::setDialogStatus(const char *message)
{
    if (message != nullptr && bookingDialogStatusText != nullptr)
    {
        bookingDialogStatusText->setString(message);
    }
}

void PatientDash::updateStepIndicator()
{
    if (bookingStepIndicatorText == nullptr)
    {
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
