#include "DoctorDash.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"
#include "../entities/Prescription.hpp"
#include "../helpers/TimeHelper.hpp"

DoctorDash::DoctorDash()
    : doctor(nullptr), titleText(nullptr), welcomeText(nullptr), specializationText(nullptr), statusText(nullptr),
      todayAppointmentsMode(false), todayAppointmentsTitleText(nullptr), todayAppointmentsStatusText(nullptr),
      todayAppointmentsLabelText(nullptr), todayAppointmentCount(0), todayAppointments(nullptr),
    todayAppointmentPatients(nullptr), markCompleteMode(false), markCompleteTitleText(nullptr),
    markCompleteStatusText(nullptr), markCompleteLabelText(nullptr), markCompleteIdLabelText(nullptr),
        markCompleteRequested(false), markNoShowMode(false), markNoShowTitleText(nullptr), markNoShowStatusText(nullptr),
        markNoShowLabelText(nullptr), markNoShowIdLabelText(nullptr), markNoShowRequested(false), viewTodayClicked(false), markCompleteClicked(false), markNoShowClicked(false),
        writePrescriptionMode(false), writePrescriptionTitleText(nullptr), writePrescriptionStatusText(nullptr),
        writePrescriptionLabelText(nullptr), writePrescriptionAppointmentIdLabelText(nullptr),
        writePrescriptionMedicinesLabelText(nullptr), writePrescriptionNotesLabelText(nullptr),
        writePrescriptionRequested(false), writePrescriptionClicked(false), viewHistoryClicked(false),
        viewMedicalHistoryMode(false), viewMedicalHistoryTitleText(nullptr), viewMedicalHistoryStatusText(nullptr),
        viewMedicalHistoryLabelText(nullptr), viewMedicalHistoryRequested(false),
                viewingPrescriptionHistory(false), medicalHistoryPatientCount(0), prescriptionHistoryCount(0)
{
    int i;

    for (i = 0; i < 20; i++)
    {
        todayAppointmentListText[i] = nullptr;
    }
    for (i = 0; i < 30; i++)
    {
        prescriptionHistoryListText[i] = nullptr;
        medicalHistoryPatientListText[i] = nullptr;
    }
}

DoctorDash::~DoctorDash()
{
    delete titleText;
    delete welcomeText;
    delete specializationText;
    delete statusText;
    delete todayAppointmentsTitleText;
    delete todayAppointmentsStatusText;
    delete todayAppointmentsLabelText;
    delete markCompleteTitleText;
    delete markCompleteStatusText;
    delete markCompleteLabelText;
    delete markCompleteIdLabelText;
    delete markNoShowTitleText;
    delete markNoShowStatusText;
    delete markNoShowLabelText;
    delete markNoShowIdLabelText;
    delete writePrescriptionTitleText;
    delete writePrescriptionStatusText;
    delete writePrescriptionLabelText;
    delete writePrescriptionAppointmentIdLabelText;
    delete writePrescriptionMedicinesLabelText;
    delete writePrescriptionNotesLabelText;
    delete viewMedicalHistoryTitleText;
    delete viewMedicalHistoryStatusText;
    delete viewMedicalHistoryLabelText;
    titleText = nullptr;
    welcomeText = nullptr;
    specializationText = nullptr;
    statusText = nullptr;

    int i;
    for (i = 0; i < 20; i++)
    {
        delete todayAppointmentListText[i];
        todayAppointmentListText[i] = nullptr;
    }
    for (i = 0; i < 30; i++)
    {
        delete prescriptionHistoryListText[i];
        prescriptionHistoryListText[i] = nullptr;
        delete medicalHistoryPatientListText[i];
        medicalHistoryPatientListText[i] = nullptr;
    }

    clearTodayAppointmentsState();
}

bool DoctorDash::initialize(const sf::Font &regularFontParam, const sf::Font &boldFontParam)
{
    regularFont = regularFontParam;
    boldFont = boldFontParam;

    dashboardCard.setSize(sf::Vector2f(1100.f, 650.f));
    dashboardCard.setPosition(sf::Vector2f(90.f, 80.f));
    dashboardCard.setFillColor(sf::Color(255, 255, 255));
    dashboardCard.setOutlineColor(sf::Color(220, 225, 230));
    dashboardCard.setOutlineThickness(2.f);

    titleText = new sf::Text(boldFont, "Doctor Dashboard", 32);
    welcomeText = new sf::Text(regularFont, "", 18);
    specializationText = new sf::Text(regularFont, "", 18);
    statusText = new sf::Text(regularFont, "", 16);

    titleText->setPosition(sf::Vector2f(110.f, 100.f));
    titleText->setFillColor(sf::Color(44, 62, 80));

    welcomeText->setPosition(sf::Vector2f(110.f, 150.f));
    welcomeText->setFillColor(sf::Color(127, 140, 141));

    specializationText->setPosition(sf::Vector2f(110.f, 180.f));
    specializationText->setFillColor(sf::Color(127, 140, 141));

    statusText->setPosition(sf::Vector2f(110.f, 600.f));
    statusText->setFillColor(sf::Color(192, 57, 43));

    todayAppointmentsPanel.setSize(sf::Vector2f(900.f, 500.f));
    todayAppointmentsPanel.setPosition(sf::Vector2f(200.f, 150.f));
    todayAppointmentsPanel.setFillColor(sf::Color(250, 251, 252));
    todayAppointmentsPanel.setOutlineColor(sf::Color(220, 225, 230));
    todayAppointmentsPanel.setOutlineThickness(2.f);

    todayAppointmentsTitleText = new sf::Text(boldFont, "Today's Appointments", 24);
    todayAppointmentsStatusText = new sf::Text(regularFont, "", 13);
    todayAppointmentsLabelText = new sf::Text(regularFont, "Appointment ID | Patient Name | Time Slot | Status", 16);
    markCompleteTitleText = new sf::Text(boldFont, "Mark Appointment Complete", 24);
    markCompleteStatusText = new sf::Text(regularFont, "", 13);
    markCompleteLabelText = new sf::Text(regularFont, "Appointment ID | Patient Name | Time Slot | Status", 16);
    markCompleteIdLabelText = new sf::Text(regularFont, "Enter Appointment ID:", 16);
    markNoShowTitleText = new sf::Text(boldFont, "Mark Appointment No-Show", 24);
    markNoShowStatusText = new sf::Text(regularFont, "", 13);
    markNoShowLabelText = new sf::Text(regularFont, "Appointment ID | Patient Name | Time Slot | Status", 16);
    markNoShowIdLabelText = new sf::Text(regularFont, "Enter Appointment ID:", 16);
    writePrescriptionTitleText = new sf::Text(boldFont, "Write Prescription", 24);
    writePrescriptionStatusText = new sf::Text(regularFont, "", 13);
    writePrescriptionLabelText = new sf::Text(regularFont, "Fill in the prescription details below.", 16);
    writePrescriptionAppointmentIdLabelText = new sf::Text(regularFont, "Enter Appointment ID:", 16);
    writePrescriptionMedicinesLabelText = new sf::Text(regularFont, "Enter medicines:", 16);
    writePrescriptionNotesLabelText = new sf::Text(regularFont, "Enter notes:", 16);

    viewMedicalHistoryTitleText = new sf::Text(boldFont, "Patient Medical History", 24);
    viewMedicalHistoryStatusText = new sf::Text(regularFont, "", 13);
    viewMedicalHistoryLabelText = new sf::Text(regularFont, "Enter the Patient ID to view their medical history:", 16);

    todayAppointmentsTitleText->setPosition(sf::Vector2f(220.f, 170.f));
    todayAppointmentsTitleText->setFillColor(sf::Color(44, 62, 80));

    todayAppointmentsStatusText->setPosition(sf::Vector2f(220.f, 600.f));
    todayAppointmentsStatusText->setFillColor(sf::Color(192, 57, 43));

    todayAppointmentsLabelText->setPosition(sf::Vector2f(220.f, 220.f));
    todayAppointmentsLabelText->setFillColor(sf::Color(127, 140, 141));

    markCompletePanel.setSize(sf::Vector2f(900.f, 500.f));
    markCompletePanel.setPosition(sf::Vector2f(200.f, 150.f));
    markCompletePanel.setFillColor(sf::Color(250, 251, 252));
    markCompletePanel.setOutlineColor(sf::Color(220, 225, 230));
    markCompletePanel.setOutlineThickness(2.f);

    markCompleteTitleText->setPosition(sf::Vector2f(220.f, 170.f));
    markCompleteTitleText->setFillColor(sf::Color(44, 62, 80));

    markCompleteStatusText->setPosition(sf::Vector2f(220.f, 600.f));
    markCompleteStatusText->setFillColor(sf::Color(192, 57, 43));

    markCompleteLabelText->setPosition(sf::Vector2f(220.f, 220.f));
    markCompleteLabelText->setFillColor(sf::Color(127, 140, 141));

    markCompleteIdLabelText->setPosition(sf::Vector2f(220.f, 525.f));
    markCompleteIdLabelText->setFillColor(sf::Color(127, 140, 141));

    markNoShowPanel.setSize(sf::Vector2f(900.f, 500.f));
    markNoShowPanel.setPosition(sf::Vector2f(200.f, 150.f));
    markNoShowPanel.setFillColor(sf::Color(250, 251, 252));
    markNoShowPanel.setOutlineColor(sf::Color(220, 225, 230));
    markNoShowPanel.setOutlineThickness(2.f);

    markNoShowTitleText->setPosition(sf::Vector2f(220.f, 170.f));
    markNoShowTitleText->setFillColor(sf::Color(44, 62, 80));

    markNoShowStatusText->setPosition(sf::Vector2f(220.f, 600.f));
    markNoShowStatusText->setFillColor(sf::Color(192, 57, 43));

    markNoShowLabelText->setPosition(sf::Vector2f(220.f, 220.f));
    markNoShowLabelText->setFillColor(sf::Color(127, 140, 141));

    markNoShowIdLabelText->setPosition(sf::Vector2f(220.f, 525.f));
    markNoShowIdLabelText->setFillColor(sf::Color(127, 140, 141));

    writePrescriptionPanel.setSize(sf::Vector2f(900.f, 500.f));
    writePrescriptionPanel.setPosition(sf::Vector2f(200.f, 150.f));
    writePrescriptionPanel.setFillColor(sf::Color(250, 251, 252));
    writePrescriptionPanel.setOutlineColor(sf::Color(220, 225, 230));
    writePrescriptionPanel.setOutlineThickness(2.f);

    writePrescriptionTitleText->setPosition(sf::Vector2f(220.f, 170.f));
    writePrescriptionTitleText->setFillColor(sf::Color(44, 62, 80));

    writePrescriptionStatusText->setPosition(sf::Vector2f(220.f, 600.f));
    writePrescriptionStatusText->setFillColor(sf::Color(192, 57, 43));

    writePrescriptionLabelText->setPosition(sf::Vector2f(220.f, 220.f));
    writePrescriptionLabelText->setFillColor(sf::Color(127, 140, 141));

    writePrescriptionAppointmentIdLabelText->setPosition(sf::Vector2f(220.f, 255.f));
    writePrescriptionAppointmentIdLabelText->setFillColor(sf::Color(127, 140, 141));

    writePrescriptionAppointmentIdInput.setFont(regularFont);
    writePrescriptionAppointmentIdInput.setCapacity(20);
    writePrescriptionAppointmentIdInput.setPosition(sf::Vector2f(220.f, 280.f));
    writePrescriptionAppointmentIdInput.setSize(sf::Vector2f(320.f, 36.f));
    writePrescriptionAppointmentIdInput.setFillColor(sf::Color::White);
    writePrescriptionAppointmentIdInput.setOutlineColor(sf::Color(189, 195, 199));
    writePrescriptionAppointmentIdInput.setTextColor(sf::Color(44, 62, 80));

    writePrescriptionMedicinesLabelText->setPosition(sf::Vector2f(220.f, 325.f));
    writePrescriptionMedicinesLabelText->setFillColor(sf::Color(127, 140, 141));

    writePrescriptionMedicinesInput.setFont(regularFont);
    writePrescriptionMedicinesInput.setCapacity(499);
    writePrescriptionMedicinesInput.setPosition(sf::Vector2f(220.f, 350.f));
    writePrescriptionMedicinesInput.setSize(sf::Vector2f(720.f, 36.f));
    writePrescriptionMedicinesInput.setFillColor(sf::Color::White);
    writePrescriptionMedicinesInput.setOutlineColor(sf::Color(189, 195, 199));
    writePrescriptionMedicinesInput.setTextColor(sf::Color(44, 62, 80));

    writePrescriptionNotesLabelText->setPosition(sf::Vector2f(220.f, 395.f));
    writePrescriptionNotesLabelText->setFillColor(sf::Color(127, 140, 141));

    writePrescriptionNotesInput.setFont(regularFont);
    writePrescriptionNotesInput.setCapacity(299);
    writePrescriptionNotesInput.setPosition(sf::Vector2f(220.f, 420.f));
    writePrescriptionNotesInput.setSize(sf::Vector2f(720.f, 36.f));
    writePrescriptionNotesInput.setFillColor(sf::Color::White);
    writePrescriptionNotesInput.setOutlineColor(sf::Color(189, 195, 199));
    writePrescriptionNotesInput.setTextColor(sf::Color(44, 62, 80));

    confirmWritePrescriptionBtn.setFont(regularFont);
    confirmWritePrescriptionBtn.setText("Save Prescription");
    confirmWritePrescriptionBtn.setPosition(sf::Vector2f(650.f, 550.f));
    confirmWritePrescriptionBtn.setSize(sf::Vector2f(180.f, 36.f));
    confirmWritePrescriptionBtn.setFillColor(sf::Color(46, 204, 113));
    confirmWritePrescriptionBtn.setOutlineColor(sf::Color(46, 204, 113));
    confirmWritePrescriptionBtn.setTextColor(sf::Color::White);

    backFromWritePrescriptionBtn.setFont(regularFont);
    backFromWritePrescriptionBtn.setText("Back");
    backFromWritePrescriptionBtn.setPosition(sf::Vector2f(840.f, 550.f));
    backFromWritePrescriptionBtn.setSize(sf::Vector2f(90.f, 36.f));
    backFromWritePrescriptionBtn.setFillColor(sf::Color(149, 165, 166));
    backFromWritePrescriptionBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromWritePrescriptionBtn.setTextColor(sf::Color::White);

    markNoShowIdInput.setFont(regularFont);
    markNoShowIdInput.setCapacity(20);
    markNoShowIdInput.setPosition(sf::Vector2f(220.f, 550.f));
    markNoShowIdInput.setSize(sf::Vector2f(320.f, 36.f));
    markNoShowIdInput.setFillColor(sf::Color::White);
    markNoShowIdInput.setOutlineColor(sf::Color(189, 195, 199));
    markNoShowIdInput.setTextColor(sf::Color(44, 62, 80));

    confirmMarkNoShowBtn.setFont(regularFont);
    confirmMarkNoShowBtn.setText("Mark No-Show");
    confirmMarkNoShowBtn.setPosition(sf::Vector2f(680.f, 550.f));
    confirmMarkNoShowBtn.setSize(sf::Vector2f(160.f, 36.f));
    confirmMarkNoShowBtn.setFillColor(sf::Color(231, 76, 60));
    confirmMarkNoShowBtn.setOutlineColor(sf::Color(231, 76, 60));
    confirmMarkNoShowBtn.setTextColor(sf::Color::White);

    backFromMarkNoShowBtn.setFont(regularFont);
    backFromMarkNoShowBtn.setText("Back");
    backFromMarkNoShowBtn.setPosition(sf::Vector2f(850.f, 550.f));
    backFromMarkNoShowBtn.setSize(sf::Vector2f(90.f, 36.f));
    backFromMarkNoShowBtn.setFillColor(sf::Color(149, 165, 166));
    backFromMarkNoShowBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromMarkNoShowBtn.setTextColor(sf::Color::White);

    markCompleteIdInput.setFont(regularFont);
    markCompleteIdInput.setCapacity(20);
    markCompleteIdInput.setPosition(sf::Vector2f(220.f, 550.f));
    markCompleteIdInput.setSize(sf::Vector2f(320.f, 36.f));
    markCompleteIdInput.setFillColor(sf::Color::White);
    markCompleteIdInput.setOutlineColor(sf::Color(189, 195, 199));
    markCompleteIdInput.setTextColor(sf::Color(44, 62, 80));

    confirmMarkCompleteBtn.setFont(regularFont);
    confirmMarkCompleteBtn.setText("Mark Completed");
    confirmMarkCompleteBtn.setPosition(sf::Vector2f(680.f, 550.f));
    confirmMarkCompleteBtn.setSize(sf::Vector2f(160.f, 36.f));
    confirmMarkCompleteBtn.setFillColor(sf::Color(46, 204, 113));
    confirmMarkCompleteBtn.setOutlineColor(sf::Color(46, 204, 113));
    confirmMarkCompleteBtn.setTextColor(sf::Color::White);

    backFromMarkCompleteBtn.setFont(regularFont);
    backFromMarkCompleteBtn.setText("Back");
    backFromMarkCompleteBtn.setPosition(sf::Vector2f(850.f, 550.f));
    backFromMarkCompleteBtn.setSize(sf::Vector2f(90.f, 36.f));
    backFromMarkCompleteBtn.setFillColor(sf::Color(149, 165, 166));
    backFromMarkCompleteBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromMarkCompleteBtn.setTextColor(sf::Color::White);

    int i;
    for (i = 0; i < 20; i++)
    {
        todayAppointmentListText[i] = new sf::Text(regularFont, "", 14);
        todayAppointmentListText[i]->setPosition(sf::Vector2f(220.f, 255.f + i * 18.f));
        todayAppointmentListText[i]->setFillColor(sf::Color(44, 62, 80));
    }

    // Buttons list
    int startX = 130;
    int startY = 240;
    int btnWidth = 420;
    int btnHeight = 52;
    int spacingY = 14;

    viewTodayAppointmentsBtn.setFont(regularFont);
    viewTodayAppointmentsBtn.setText("View Today's Appointments");
    viewTodayAppointmentsBtn.setPosition(sf::Vector2f(startX, startY));
    viewTodayAppointmentsBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    viewTodayAppointmentsBtn.setFillColor(sf::Color(52, 152, 219));
    viewTodayAppointmentsBtn.setOutlineColor(sf::Color(52, 152, 219));
    viewTodayAppointmentsBtn.setTextColor(sf::Color::White);

    markAppointmentCompleteBtn.setFont(regularFont);
    markAppointmentCompleteBtn.setText("Mark Appointment Complete");
    markAppointmentCompleteBtn.setPosition(sf::Vector2f(startX, startY + (btnHeight + spacingY) * 1));
    markAppointmentCompleteBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    markAppointmentCompleteBtn.setFillColor(sf::Color(52, 152, 219));
    markAppointmentCompleteBtn.setOutlineColor(sf::Color(52, 152, 219));
    markAppointmentCompleteBtn.setTextColor(sf::Color::White);

    markAppointmentNoShowBtn.setFont(regularFont);
    markAppointmentNoShowBtn.setText("Mark Appointment No-Show");
    markAppointmentNoShowBtn.setPosition(sf::Vector2f(startX, startY + (btnHeight + spacingY) * 2));
    markAppointmentNoShowBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    markAppointmentNoShowBtn.setFillColor(sf::Color(52, 152, 219));
    markAppointmentNoShowBtn.setOutlineColor(sf::Color(52, 152, 219));
    markAppointmentNoShowBtn.setTextColor(sf::Color::White);

    writePrescriptionBtn.setFont(regularFont);
    writePrescriptionBtn.setText("Write Prescription");
    writePrescriptionBtn.setPosition(sf::Vector2f(startX, startY + (btnHeight + spacingY) * 3));
    writePrescriptionBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    writePrescriptionBtn.setFillColor(sf::Color(52, 152, 219));
    writePrescriptionBtn.setOutlineColor(sf::Color(52, 152, 219));
    writePrescriptionBtn.setTextColor(sf::Color::White);

    viewPatientHistoryBtn.setFont(regularFont);
    viewPatientHistoryBtn.setText("View Patient Medical History");
    viewPatientHistoryBtn.setPosition(sf::Vector2f(startX, startY + (btnHeight + spacingY) * 4));
    viewPatientHistoryBtn.setSize(sf::Vector2f(btnWidth, btnHeight));
    viewPatientHistoryBtn.setFillColor(sf::Color(52, 152, 219));
    viewPatientHistoryBtn.setOutlineColor(sf::Color(52, 152, 219));
    viewPatientHistoryBtn.setTextColor(sf::Color::White);

    viewMedicalHistoryPanel.setSize(sf::Vector2f(900.f, 500.f));
    viewMedicalHistoryPanel.setPosition(sf::Vector2f(200.f, 150.f));
    viewMedicalHistoryPanel.setFillColor(sf::Color(250, 251, 252));
    viewMedicalHistoryPanel.setOutlineColor(sf::Color(220, 225, 230));
    viewMedicalHistoryPanel.setOutlineThickness(2.f);

    viewMedicalHistoryTitleText->setPosition(sf::Vector2f(220.f, 170.f));
    viewMedicalHistoryTitleText->setFillColor(sf::Color(44, 62, 80));

    viewMedicalHistoryStatusText->setPosition(sf::Vector2f(220.f, 600.f));
    viewMedicalHistoryStatusText->setFillColor(sf::Color(192, 57, 43));

    viewMedicalHistoryLabelText->setPosition(sf::Vector2f(220.f, 450.f));
    viewMedicalHistoryLabelText->setFillColor(sf::Color(127, 140, 141));

    viewMedicalHistoryPatientIdInput.setFont(regularFont);
    viewMedicalHistoryPatientIdInput.setCapacity(20);
    viewMedicalHistoryPatientIdInput.setPosition(sf::Vector2f(220.f, 475.f));
    viewMedicalHistoryPatientIdInput.setSize(sf::Vector2f(320.f, 36.f));
    viewMedicalHistoryPatientIdInput.setFillColor(sf::Color::White);
    viewMedicalHistoryPatientIdInput.setOutlineColor(sf::Color(189, 195, 199));
    viewMedicalHistoryPatientIdInput.setTextColor(sf::Color(44, 62, 80));

    confirmViewMedicalHistoryBtn.setFont(regularFont);
    confirmViewMedicalHistoryBtn.setText("View History");
    confirmViewMedicalHistoryBtn.setPosition(sf::Vector2f(650.f, 550.f));
    confirmViewMedicalHistoryBtn.setSize(sf::Vector2f(180.f, 36.f));
    confirmViewMedicalHistoryBtn.setFillColor(sf::Color(46, 204, 113));
    confirmViewMedicalHistoryBtn.setOutlineColor(sf::Color(46, 204, 113));
    confirmViewMedicalHistoryBtn.setTextColor(sf::Color::White);

    backFromViewMedicalHistoryBtn.setFont(regularFont);
    backFromViewMedicalHistoryBtn.setText("Back");
    backFromViewMedicalHistoryBtn.setPosition(sf::Vector2f(840.f, 550.f));
    backFromViewMedicalHistoryBtn.setSize(sf::Vector2f(90.f, 36.f));
    backFromViewMedicalHistoryBtn.setFillColor(sf::Color(149, 165, 166));
    backFromViewMedicalHistoryBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromViewMedicalHistoryBtn.setTextColor(sf::Color::White);

    backFromPrescriptionsBtn.setFont(regularFont);
    backFromPrescriptionsBtn.setText("Back to Patients");
    backFromPrescriptionsBtn.setPosition(sf::Vector2f(650.f, 550.f));
    backFromPrescriptionsBtn.setSize(sf::Vector2f(180.f, 36.f));
    backFromPrescriptionsBtn.setFillColor(sf::Color(149, 165, 166));
    backFromPrescriptionsBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromPrescriptionsBtn.setTextColor(sf::Color::White);

    backFromTodayAppointmentsBtn.setFont(regularFont);
    backFromTodayAppointmentsBtn.setText("Back");
    backFromTodayAppointmentsBtn.setPosition(sf::Vector2f(850.f, 550.f));
    backFromTodayAppointmentsBtn.setSize(sf::Vector2f(90.f, 36.f));
    backFromTodayAppointmentsBtn.setFillColor(sf::Color(149, 165, 166));
    backFromTodayAppointmentsBtn.setOutlineColor(sf::Color(149, 165, 166));
    backFromTodayAppointmentsBtn.setTextColor(sf::Color::White);

    return true;
}

void DoctorDash::setDoctor(Doctor *doc)
{
    doctor = doc;

    if (doctor == nullptr)
    {
        if (welcomeText != nullptr)
        {
            welcomeText->setString("");
        }
        if (specializationText != nullptr)
        {
            specializationText->setString("");
        }
        return;
    }

    char buf[200];
    StringHelper::stringCopy(buf, "Welcome, Dr. ", 200);
    int len = StringHelper::stringLength(buf);
    StringHelper::stringCopy(buf + len, doctor->getName(), 200 - len);
    if (welcomeText != nullptr)
    {
        welcomeText->setString(buf);
    }

    char specBuf[200];
    StringHelper::stringCopy(specBuf, "Specialization: ", 200);
    len = StringHelper::stringLength(specBuf);
    StringHelper::stringCopy(specBuf + len, doctor->getSpecialization(), 200 - len);
    if (specializationText != nullptr)
    {
        specializationText->setString(specBuf);
    }
}

void DoctorDash::setPatientListForMedicalHistory(Storage<Patient> *patients, Storage<Appointment> *appointments)
{
    int i;
    int j;
    int count;
    Patient *patientArray;
    Appointment *appointmentArray;
    int patientID;
    bool foundPatient;
    char buf[200];

    medicalHistoryPatientCount = 0;

    if (patients == nullptr || appointments == nullptr)
    {
        return;
    }

    for (i = 0; i < 30; i++)
    {
        if (medicalHistoryPatientListText[i] != nullptr)
        {
            delete medicalHistoryPatientListText[i];
            medicalHistoryPatientListText[i] = nullptr;
        }
    }

    patientArray = patients->getAll();
    appointmentArray = appointments->getAll();
    count = 0;

    for (i = 0; i < patients->size() && count < 30; i++)
    {
        patientID = patientArray[i].getID();
        foundPatient = false;

        for (j = 0; j < appointments->size(); j++)
        {
            if (appointmentArray[j].getPatientID() == patientID &&
                appointmentArray[j].getDoctorID() == doctor->getID() &&
                StringHelper::textEquals(appointmentArray[j].getStatus(), "completed"))
            {
                foundPatient = true;
                break;
            }
        }

        if (foundPatient)
        {
            if (medicalHistoryPatientListText[count] != nullptr)
            {
                delete medicalHistoryPatientListText[count];
            }

            buf[0] = '\0';
            StringHelper::stringCopy(buf, "ID: ", 200);
            int len = StringHelper::stringLength(buf);
            char patientIdStr[20];
            ConversionHelper::intToString(patientID, patientIdStr);
            StringHelper::stringCopy(buf + len, patientIdStr, 200 - len);
            len = StringHelper::stringLength(buf);
            StringHelper::stringCopy(buf + len, " | ", 200 - len);
            len = StringHelper::stringLength(buf);
            StringHelper::stringCopy(buf + len, patientArray[i].getName(), 200 - len);

            medicalHistoryPatientListText[count] = new sf::Text(regularFont, buf, 14);
            medicalHistoryPatientListText[count]->setFillColor(sf::Color(52, 73, 94));
            count++;
        }
    }

    medicalHistoryPatientCount = count;
}

void DoctorDash::setPrescriptionsForPatient(Storage<Prescription> *prescriptions, int patientID, int doctorID)
{
    int i;
    int j;
    int bestIndex;
    int count;
    int selectedIndices[30];
    Prescription *prescriptionArray;
    char buf[700];
    char idBuffer[20];
    char medicinesBuffer[120];
    char notesBuffer[120];
    int len;
    const char *medicinesText;
    const char *notesText;

    prescriptionHistoryCount = 0;

    if (prescriptions == nullptr)
    {
        return;
    }

    prescriptionArray = prescriptions->getAll();
    count = 0;

    for (i = 0; i < prescriptions->size() && count < 30; i++)
    {
        if (prescriptionArray[i].getPatientID() == patientID && prescriptionArray[i].getDoctorID() == doctorID)
        {
            selectedIndices[count] = i;
            count++;
        }
    }

    for (i = 0; i < count - 1; i++)
    {
        bestIndex = i;
        for (j = i + 1; j < count; j++)
        {
            if (TimeHelper::compareDates(prescriptionArray[selectedIndices[j]].getDate(), prescriptionArray[selectedIndices[bestIndex]].getDate()) > 0)
            {
                bestIndex = j;
            }
        }

        if (bestIndex != i)
        {
            int tempIndex;
            tempIndex = selectedIndices[i];
            selectedIndices[i] = selectedIndices[bestIndex];
            selectedIndices[bestIndex] = tempIndex;
        }
    }

    for (i = 0; i < 30; i++)
    {
        if (prescriptionHistoryListText[i] != nullptr)
        {
            delete prescriptionHistoryListText[i];
            prescriptionHistoryListText[i] = nullptr;
        }
    }

    for (i = 0; i < count; i++)
    {
        buf[0] = '\0';
        StringHelper::stringCopy(buf, "Rx: ", 700);
        len = StringHelper::stringLength(buf);
        ConversionHelper::intToString(prescriptionArray[selectedIndices[i]].getID(), idBuffer);
        StringHelper::stringCopy(buf + len, idBuffer, 700 - len);
        len = StringHelper::stringLength(buf);
        StringHelper::stringCopy(buf + len, " | Date: ", 700 - len);
        len = StringHelper::stringLength(buf);
        StringHelper::stringCopy(buf + len, prescriptionArray[selectedIndices[i]].getDate(), 700 - len);
        len = StringHelper::stringLength(buf);
        StringHelper::stringCopy(buf + len, "\nMedicines: ", 700 - len);

        medicinesText = prescriptionArray[selectedIndices[i]].getMedicines();
        StringHelper::copyPreviewText(medicinesBuffer, 120, medicinesText, 100);
        len = StringHelper::stringLength(buf);
        StringHelper::stringCopy(buf + len, medicinesBuffer, 700 - len);
        len = StringHelper::stringLength(buf);
        StringHelper::stringCopy(buf + len, "\nNotes: ", 700 - len);

        notesText = prescriptionArray[selectedIndices[i]].getNotes();
        StringHelper::copyPreviewText(notesBuffer, 120, notesText, 100);
        len = StringHelper::stringLength(buf);
        StringHelper::stringCopy(buf + len, notesBuffer, 700 - len);

        prescriptionHistoryListText[i] = new sf::Text(regularFont, buf, 12);
        prescriptionHistoryListText[i]->setFillColor(sf::Color(44, 62, 80));
    }

    prescriptionHistoryCount = count;

    if (viewMedicalHistoryStatusText != nullptr)
    {
        if (count == 0)
        {
            viewMedicalHistoryStatusText->setString("No prescriptions found for this patient.");
        }
        else
        {
            viewMedicalHistoryStatusText->setString("");
        }
    }
}

void DoctorDash::displayPrescriptionsForPatient()
{
    viewingPrescriptionHistory = true;
}

void DoctorDash::clearTodayAppointmentsState()
{
    todayAppointmentCount = 0;

    if (todayAppointments != nullptr)
    {
        delete todayAppointments;
        todayAppointments = nullptr;
    }

    todayAppointmentPatients = nullptr;

    if (todayAppointmentsStatusText != nullptr)
    {
        todayAppointmentsStatusText->setString("");
    }
}

void DoctorDash::startMarkCompleteMode()
{
    markCompleteMode = true;
    markCompleteRequested = false;
    markCompleteIdInput.clear();
    markCompleteIdInput.setActive(false);

    if (markCompleteStatusText != nullptr)
    {
        markCompleteStatusText->setString("");
    }
}

void DoctorDash::closeMarkCompleteMode()
{
    markCompleteMode = false;
    markCompleteRequested = false;
    markCompleteIdInput.clear();
    markCompleteIdInput.setActive(false);
    clearTodayAppointmentsState();
}

void DoctorDash::startMarkNoShowMode()
{
    markNoShowMode = true;
    markNoShowRequested = false;
    markNoShowIdInput.clear();
    markNoShowIdInput.setActive(false);

    if (markNoShowStatusText != nullptr)
    {
        markNoShowStatusText->setString("");
    }
}

void DoctorDash::closeMarkNoShowMode()
{
    markNoShowMode = false;
    markNoShowRequested = false;
    markNoShowIdInput.clear();
    markNoShowIdInput.setActive(false);
    clearTodayAppointmentsState();
}

void DoctorDash::startWritePrescriptionMode()
{
    writePrescriptionMode = true;
    writePrescriptionRequested = false;
    writePrescriptionAppointmentIdInput.clear();
    writePrescriptionMedicinesInput.clear();
    writePrescriptionNotesInput.clear();
    writePrescriptionAppointmentIdInput.setActive(false);
    writePrescriptionMedicinesInput.setActive(false);
    writePrescriptionNotesInput.setActive(false);

    if (writePrescriptionStatusText != nullptr)
    {
        writePrescriptionStatusText->setString("");
    }
}

void DoctorDash::closeWritePrescriptionMode()
{
    writePrescriptionMode = false;
    writePrescriptionRequested = false;
    writePrescriptionAppointmentIdInput.clear();
    writePrescriptionMedicinesInput.clear();
    writePrescriptionNotesInput.clear();
    writePrescriptionAppointmentIdInput.setActive(false);
    writePrescriptionMedicinesInput.setActive(false);
    writePrescriptionNotesInput.setActive(false);
}

void DoctorDash::startViewMedicalHistoryMode()
{
    viewMedicalHistoryMode = true;
    viewMedicalHistoryRequested = false;
    viewingPrescriptionHistory = false;
    viewMedicalHistoryPatientIdInput.clear();
    viewMedicalHistoryPatientIdInput.setActive(false);
    prescriptionHistoryCount = 0;

    if (viewMedicalHistoryStatusText != nullptr)
    {
        viewMedicalHistoryStatusText->setString("");
    }
}

void DoctorDash::closeViewMedicalHistoryMode()
{
    viewMedicalHistoryMode = false;
    viewMedicalHistoryRequested = false;
    viewMedicalHistoryPatientIdInput.clear();
    viewMedicalHistoryPatientIdInput.setActive(false);
    medicalHistoryPatientCount = 0;
}

void DoctorDash::updateTodayAppointmentList()
{
    Appointment *appointmentArray;
    Patient *patientArray;
    int i;
    int j;
    int bestIndex;
    int tempIndex;
    Appointment tempAppointment;

    if (todayAppointments == nullptr)
    {
        todayAppointmentCount = 0;
        if (todayAppointmentsStatusText != nullptr)
        {
            todayAppointmentsStatusText->setString("No appointments scheduled for today.");
        }
        return;
    }

    todayAppointmentCount = todayAppointments->size();
    if (todayAppointmentCount > 20)
    {
        todayAppointmentCount = 20;
    }

    appointmentArray = todayAppointments->getAll();
    for (i = 0; i < todayAppointmentCount - 1; i++)
    {
        bestIndex = i;
        for (j = i + 1; j < todayAppointmentCount; j++)
        {
            if (TimeHelper::compareTimeSlotsAscending(appointmentArray[j].getTimeSlot(), appointmentArray[bestIndex].getTimeSlot()) < 0)
            {
                bestIndex = j;
            }
        }

        if (bestIndex != i)
        {
            tempAppointment = appointmentArray[i];
            appointmentArray[i] = appointmentArray[bestIndex];
            appointmentArray[bestIndex] = tempAppointment;
        }
    }

    if (todayAppointmentCount == 0)
    {
        if (todayAppointmentsStatusText != nullptr)
        {
            todayAppointmentsStatusText->setString("No appointments scheduled for today.");
        }
        return;
    }

    patientArray = nullptr;
    if (todayAppointmentPatients != nullptr)
    {
        patientArray = todayAppointmentPatients->getAll();
    }

    for (i = 0; i < todayAppointmentCount; i++)
    {
        char line[300];
        char buffer[64];
        const char *patientName;
        int patientID;
        int patientIndex;
        int lineLen;

        line[0] = '\0';
        ConversionHelper::intToString(appointmentArray[i].getID(), line);
        lineLen = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + lineLen, " | ", 300 - lineLen);
        lineLen = StringHelper::stringLength(line);

        patientName = "Unknown";
        patientID = appointmentArray[i].getPatientID();
        if (patientArray != nullptr)
        {
            for (patientIndex = 0; patientIndex < todayAppointmentPatients->size(); patientIndex++)
            {
                if (patientArray[patientIndex].getID() == patientID)
                {
                    patientName = patientArray[patientIndex].getName();
                    break;
                }
            }
        }

        StringHelper::stringCopy(line + lineLen, patientName, 300 - lineLen);
        lineLen = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + lineLen, " | ", 300 - lineLen);
        lineLen = StringHelper::stringLength(line);

        StringHelper::stringCopy(line + lineLen, appointmentArray[i].getTimeSlot(), 300 - lineLen);
        lineLen = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + lineLen, " | ", 300 - lineLen);
        lineLen = StringHelper::stringLength(line);

        StringHelper::stringCopy(line + lineLen, appointmentArray[i].getStatus(), 300 - lineLen);

        if (todayAppointmentListText[i] != nullptr)
        {
            todayAppointmentListText[i]->setString(line);
        }
    }

    if (todayAppointmentsStatusText != nullptr)
    {
        todayAppointmentsStatusText->setString("");
    }
}

void DoctorDash::draw(sf::RenderWindow &window) const
{
    window.draw(dashboardCard);
    if (titleText != nullptr)
    {
        window.draw(*titleText);
    }
    if (welcomeText != nullptr)
    {
        window.draw(*welcomeText);
    }
    if (specializationText != nullptr)
    {
        window.draw(*specializationText);
    }
    if (statusText != nullptr)
    {
        window.draw(*statusText);
    }

    if (todayAppointmentsMode)
    {
        window.draw(todayAppointmentsPanel);
        if (todayAppointmentsTitleText != nullptr)
        {
            window.draw(*todayAppointmentsTitleText);
        }
        if (todayAppointmentsStatusText != nullptr)
        {
            window.draw(*todayAppointmentsStatusText);
        }
        if (todayAppointmentsLabelText != nullptr)
        {
            window.draw(*todayAppointmentsLabelText);
        }

        int i;
        for (i = 0; i < todayAppointmentCount; i++)
        {
            if (todayAppointmentListText[i] != nullptr)
            {
                window.draw(*todayAppointmentListText[i]);
            }
        }
        backFromTodayAppointmentsBtn.draw(window);
        return;
    }
    else if (markCompleteMode)
    {
        window.draw(markCompletePanel);
        if (markCompleteTitleText != nullptr)
        {
            window.draw(*markCompleteTitleText);
        }
        if (markCompleteStatusText != nullptr)
        {
            window.draw(*markCompleteStatusText);
        }
        if (markCompleteLabelText != nullptr)
        {
            window.draw(*markCompleteLabelText);
        }
        if (markCompleteIdLabelText != nullptr)
        {
            window.draw(*markCompleteIdLabelText);
        }

        int i;
        for (i = 0; i < todayAppointmentCount; i++)
        {
            if (todayAppointmentListText[i] != nullptr)
            {
                window.draw(*todayAppointmentListText[i]);
            }
        }

        markCompleteIdInput.draw(window);
        confirmMarkCompleteBtn.draw(window);
        backFromMarkCompleteBtn.draw(window);
        return;
    }
    else if (markNoShowMode)
    {
        window.draw(markNoShowPanel);
        if (markNoShowTitleText != nullptr)
        {
            window.draw(*markNoShowTitleText);
        }
        if (markNoShowStatusText != nullptr)
        {
            window.draw(*markNoShowStatusText);
        }
        if (markNoShowLabelText != nullptr)
        {
            window.draw(*markNoShowLabelText);
        }
        if (markNoShowIdLabelText != nullptr)
        {
            window.draw(*markNoShowIdLabelText);
        }

        int i;
        for (i = 0; i < todayAppointmentCount; i++)
        {
            if (todayAppointmentListText[i] != nullptr)
            {
                window.draw(*todayAppointmentListText[i]);
            }
        }

        markNoShowIdInput.draw(window);
        confirmMarkNoShowBtn.draw(window);
        backFromMarkNoShowBtn.draw(window);
        return;
    }
    else if (writePrescriptionMode)
    {
        window.draw(writePrescriptionPanel);
        if (writePrescriptionTitleText != nullptr)
        {
            window.draw(*writePrescriptionTitleText);
        }
        if (writePrescriptionStatusText != nullptr)
        {
            window.draw(*writePrescriptionStatusText);
        }
        if (writePrescriptionLabelText != nullptr)
        {
            window.draw(*writePrescriptionLabelText);
        }
        if (writePrescriptionAppointmentIdLabelText != nullptr)
        {
            window.draw(*writePrescriptionAppointmentIdLabelText);
        }
        if (writePrescriptionMedicinesLabelText != nullptr)
        {
            window.draw(*writePrescriptionMedicinesLabelText);
        }
        if (writePrescriptionNotesLabelText != nullptr)
        {
            window.draw(*writePrescriptionNotesLabelText);
        }

        writePrescriptionAppointmentIdInput.draw(window);
        writePrescriptionMedicinesInput.draw(window);
        writePrescriptionNotesInput.draw(window);
        confirmWritePrescriptionBtn.draw(window);
        backFromWritePrescriptionBtn.draw(window);
        return;
    }

    else if (viewMedicalHistoryMode)
    {
        window.draw(viewMedicalHistoryPanel);
        if (viewMedicalHistoryTitleText != nullptr)
        {
            window.draw(*viewMedicalHistoryTitleText);
        }
        if (viewMedicalHistoryStatusText != nullptr)
        {
            window.draw(*viewMedicalHistoryStatusText);
        }

        int i;

        if (viewingPrescriptionHistory)
        {
            sf::Text prescriptionHeaderText(regularFont, "Patient Prescriptions:", 14);
            prescriptionHeaderText.setPosition(sf::Vector2f(220.f, 220.f));
            prescriptionHeaderText.setFillColor(sf::Color(127, 140, 141));
            window.draw(prescriptionHeaderText);

            for (i = 0; i < prescriptionHistoryCount; i++)
            {
                if (prescriptionHistoryListText[i] != nullptr)
                {
                    prescriptionHistoryListText[i]->setPosition(sf::Vector2f(220.f, 245.f + (i * 70)));
                    window.draw(*prescriptionHistoryListText[i]);
                }
            }

            backFromPrescriptionsBtn.draw(window);
        }
        else
        {
            if (viewMedicalHistoryLabelText != nullptr)
            {
                window.draw(*viewMedicalHistoryLabelText);
            }

            sf::Text listHeaderText(regularFont, "Your Patients (click or enter ID below):", 14);
            listHeaderText.setPosition(sf::Vector2f(220.f, 245.f));
            listHeaderText.setFillColor(sf::Color(127, 140, 141));
            window.draw(listHeaderText);

            for (i = 0; i < medicalHistoryPatientCount; i++)
            {
                if (medicalHistoryPatientListText[i] != nullptr)
                {
                    medicalHistoryPatientListText[i]->setPosition(sf::Vector2f(220.f, 270.f + (i * 20)));
                    window.draw(*medicalHistoryPatientListText[i]);
                }
            }

            viewMedicalHistoryPatientIdInput.draw(window);
            confirmViewMedicalHistoryBtn.draw(window);
            backFromViewMedicalHistoryBtn.draw(window);
        }
        return;
    }

    viewTodayAppointmentsBtn.draw(window);
    markAppointmentCompleteBtn.draw(window);
    markAppointmentNoShowBtn.draw(window);
    writePrescriptionBtn.draw(window);
    viewPatientHistoryBtn.draw(window);
}

void DoctorDash::handleMouseClick(sf::RenderWindow &window)
{
    sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (todayAppointmentsMode)
    {
        if (backFromTodayAppointmentsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeTodayAppointmentsMode();
            return;
        }
        return;
    }

    if (markCompleteMode)
    {
        if (markCompleteIdInput.contains(mouseWorldPosition))
        {
            markCompleteIdInput.setActive(true);
            return;
        }

        if (confirmMarkCompleteBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            markCompleteRequested = true;
            return;
        }

        if (backFromMarkCompleteBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeMarkCompleteMode();
            return;
        }

        markCompleteIdInput.setActive(false);
        return;
    }

    if (markNoShowMode)
    {
        if (markNoShowIdInput.contains(mouseWorldPosition))
        {
            markNoShowIdInput.setActive(true);
            return;
        }

        if (confirmMarkNoShowBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            markNoShowRequested = true;
            return;
        }

        if (backFromMarkNoShowBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeMarkNoShowMode();
            return;
        }

        markNoShowIdInput.setActive(false);
        return;
    }

    if (writePrescriptionMode)
    {
        if (writePrescriptionAppointmentIdInput.contains(mouseWorldPosition))
        {
            writePrescriptionAppointmentIdInput.setActive(true);
            writePrescriptionMedicinesInput.setActive(false);
            writePrescriptionNotesInput.setActive(false);
            return;
        }

        if (writePrescriptionMedicinesInput.contains(mouseWorldPosition))
        {
            writePrescriptionAppointmentIdInput.setActive(false);
            writePrescriptionMedicinesInput.setActive(true);
            writePrescriptionNotesInput.setActive(false);
            return;
        }

        if (writePrescriptionNotesInput.contains(mouseWorldPosition))
        {
            writePrescriptionAppointmentIdInput.setActive(false);
            writePrescriptionMedicinesInput.setActive(false);
            writePrescriptionNotesInput.setActive(true);
            return;
        }

        if (confirmWritePrescriptionBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            writePrescriptionRequested = true;
            return;
        }

        if (backFromWritePrescriptionBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeWritePrescriptionMode();
            return;
        }

        writePrescriptionAppointmentIdInput.setActive(false);
        writePrescriptionMedicinesInput.setActive(false);
        writePrescriptionNotesInput.setActive(false);
        return;
    }

    if (viewMedicalHistoryMode)
    {
        if (viewingPrescriptionHistory)
        {
            if (backFromPrescriptionsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
            {
                viewingPrescriptionHistory = false;
                viewMedicalHistoryPatientIdInput.clear();
                if (viewMedicalHistoryStatusText != nullptr)
                {
                    viewMedicalHistoryStatusText->setString("");
                }
                return;
            }
        }
        else
        {
            if (viewMedicalHistoryPatientIdInput.contains(mouseWorldPosition))
            {
                viewMedicalHistoryPatientIdInput.setActive(true);
                return;
            }

            if (confirmViewMedicalHistoryBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
            {
                viewMedicalHistoryRequested = true;
                return;
            }

            if (backFromViewMedicalHistoryBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
            {
                closeViewMedicalHistoryMode();
                return;
            }

            viewMedicalHistoryPatientIdInput.setActive(false);
        }
        return;
    }

    if (viewTodayAppointmentsBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        viewTodayClicked = true;
        return;
    }

    if (markAppointmentCompleteBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        markCompleteClicked = true;
        return;
    }

    if (markAppointmentNoShowBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        markNoShowClicked = true;
        return;
    }

    if (writePrescriptionBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        writePrescriptionClicked = true;
        return;
    }

    if (viewPatientHistoryBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
    {
        viewHistoryClicked = true;
        return;
    }
}

bool DoctorDash::consumeViewTodayAppointmentsRequest()
{
    bool v = viewTodayClicked;
    viewTodayClicked = false;
    return v;
}

bool DoctorDash::consumeMarkAppointmentCompleteRequest()
{
    bool v = markCompleteClicked;
    markCompleteClicked = false;
    return v;
}

bool DoctorDash::consumeMarkAppointmentCompleteSubmitRequest()
{
    bool v = markCompleteRequested;
    markCompleteRequested = false;
    return v;
}

bool DoctorDash::consumeMarkAppointmentNoShowSubmitRequest()
{
    bool v = markNoShowRequested;
    markNoShowRequested = false;
    return v;
}

bool DoctorDash::consumeMarkAppointmentNoShowRequest()
{
    bool v = markNoShowClicked;
    markNoShowClicked = false;
    return v;
}

bool DoctorDash::consumeWritePrescriptionRequest()
{
    bool v = writePrescriptionClicked;
    writePrescriptionClicked = false;
    return v;
}

bool DoctorDash::consumeWritePrescriptionSubmitRequest()
{
    bool v = writePrescriptionRequested;
    writePrescriptionRequested = false;
    return v;
}

bool DoctorDash::consumeViewPatientHistoryRequest()
{
    bool v = viewHistoryClicked;
    viewHistoryClicked = false;
    return v;
}

bool DoctorDash::consumeViewMedicalHistorySubmitRequest()
{
    bool v = viewMedicalHistoryRequested;
    viewMedicalHistoryRequested = false;
    return v;
}

void DoctorDash::setTodayAppointments(Storage<Appointment> *appointments, Storage<Patient> *patients)
{
    if (todayAppointments != nullptr)
    {
        delete todayAppointments;
        todayAppointments = nullptr;
    }

    todayAppointments = appointments;
    todayAppointmentPatients = patients;
    updateTodayAppointmentList();
}

void DoctorDash::handleTextEntered(char32_t unicode)
{
    if (markCompleteMode)
    {
        markCompleteIdInput.handleTextEntered(unicode);
        return;
    }

    if (markNoShowMode)
    {
        markNoShowIdInput.handleTextEntered(unicode);
        return;
    }

    if (writePrescriptionMode)
    {
        if (writePrescriptionAppointmentIdInput.isActive())
        {
            writePrescriptionAppointmentIdInput.handleTextEntered(unicode);
        }
        else if (writePrescriptionMedicinesInput.isActive())
        {
            writePrescriptionMedicinesInput.handleTextEntered(unicode);
        }
        else if (writePrescriptionNotesInput.isActive())
        {
            writePrescriptionNotesInput.handleTextEntered(unicode);
        }
        return;
    }

    if (viewMedicalHistoryMode)
    {
        if (viewMedicalHistoryPatientIdInput.isActive())
        {
            viewMedicalHistoryPatientIdInput.handleTextEntered(unicode);
        }
        return;
    }
}

void DoctorDash::startTodayAppointmentsMode()
{
    todayAppointmentsMode = true;
    if (todayAppointments == nullptr || todayAppointments->size() == 0)
    {
        if (todayAppointmentsStatusText != nullptr)
        {
            todayAppointmentsStatusText->setString("No appointments scheduled for today.");
        }
    }
}

void DoctorDash::closeTodayAppointmentsMode()
{
    todayAppointmentsMode = false;
    clearTodayAppointmentsState();
}

const char *DoctorDash::getMarkCompleteAppointmentIDText() const
{
    return markCompleteIdInput.getText();
}

const char *DoctorDash::getMarkNoShowAppointmentIDText() const
{
    return markNoShowIdInput.getText();
}

const char *DoctorDash::getWritePrescriptionAppointmentIDText() const
{
    return writePrescriptionAppointmentIdInput.getText();
}

const char *DoctorDash::getWritePrescriptionMedicinesText() const
{
    return writePrescriptionMedicinesInput.getText();
}

const char *DoctorDash::getWritePrescriptionNotesText() const
{
    return writePrescriptionNotesInput.getText();
}

const char *DoctorDash::getViewMedicalHistoryPatientIDText() const
{
    return viewMedicalHistoryPatientIdInput.getText();
}

void DoctorDash::clearClickStates()
{
    viewTodayClicked = false;
    markCompleteClicked = false;
    markNoShowClicked = false;
    writePrescriptionClicked = false;
    viewHistoryClicked = false;
}

void DoctorDash::setStatus(const char *message)
{
    if (statusText != nullptr)
    {
        statusText->setString(message);
    }
}
