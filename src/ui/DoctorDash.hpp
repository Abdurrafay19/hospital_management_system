#pragma once

#include <SFML/Graphics.hpp>
#include "UIButton.hpp"
#include "UITextBox.hpp"
#include "../entities/Doctor.hpp"
#include "../entities/Appointment.hpp"
#include "../entities/Patient.hpp"
#include "../entities/Prescription.hpp"
#include "../entities/Storage.hpp"

class DoctorDash
{
private:
    Doctor *doctor;
    sf::Font regularFont;
    sf::Font boldFont;

    sf::RectangleShape dashboardCard;
    sf::Text *titleText;
    sf::Text *welcomeText;
    sf::Text *specializationText;
    sf::Text *statusText;

    bool todayAppointmentsMode;
    sf::RectangleShape todayAppointmentsPanel;
    sf::Text *todayAppointmentsTitleText;
    sf::Text *todayAppointmentsStatusText;
    sf::Text *todayAppointmentsLabelText;
    sf::Text *todayAppointmentListText[20];
    int todayAppointmentCount;
    Storage<Appointment> *todayAppointments;
    Storage<Patient> *todayAppointmentPatients;
    UIButton backFromTodayAppointmentsBtn;

    bool markCompleteMode;
    sf::RectangleShape markCompletePanel;
    sf::Text *markCompleteTitleText;
    sf::Text *markCompleteStatusText;
    sf::Text *markCompleteLabelText;
    sf::Text *markCompleteIdLabelText;
    UITextBox markCompleteIdInput;
    UIButton confirmMarkCompleteBtn;
    UIButton backFromMarkCompleteBtn;
    bool markCompleteRequested;

    bool markNoShowMode;
    sf::RectangleShape markNoShowPanel;
    sf::Text *markNoShowTitleText;
    sf::Text *markNoShowStatusText;
    sf::Text *markNoShowLabelText;
    sf::Text *markNoShowIdLabelText;
    UITextBox markNoShowIdInput;
    UIButton confirmMarkNoShowBtn;
    UIButton backFromMarkNoShowBtn;
    bool markNoShowRequested;

    bool writePrescriptionMode;
    sf::RectangleShape writePrescriptionPanel;
    sf::Text *writePrescriptionTitleText;
    sf::Text *writePrescriptionStatusText;
    sf::Text *writePrescriptionLabelText;
    sf::Text *writePrescriptionAppointmentIdLabelText;
    sf::Text *writePrescriptionMedicinesLabelText;
    sf::Text *writePrescriptionNotesLabelText;
    UITextBox writePrescriptionAppointmentIdInput;
    UITextBox writePrescriptionMedicinesInput;
    UITextBox writePrescriptionNotesInput;
    UIButton confirmWritePrescriptionBtn;
    UIButton backFromWritePrescriptionBtn;
    bool writePrescriptionRequested;

    bool viewMedicalHistoryMode;
    sf::RectangleShape viewMedicalHistoryPanel;
    sf::Text *viewMedicalHistoryTitleText;
    sf::Text *viewMedicalHistoryStatusText;
    sf::Text *viewMedicalHistoryLabelText;
    UITextBox viewMedicalHistoryPatientIdInput;
    UIButton confirmViewMedicalHistoryBtn;
    UIButton backFromViewMedicalHistoryBtn;
    bool viewMedicalHistoryRequested;
    bool viewingPrescriptionHistory;
    sf::Text *medicalHistoryPatientListText[30];
    int medicalHistoryPatientCount;
    sf::Text *prescriptionHistoryListText[30];
    int prescriptionHistoryCount;
    UIButton backFromPrescriptionsBtn;

    UIButton viewTodayAppointmentsBtn;
    UIButton markAppointmentCompleteBtn;
    UIButton markAppointmentNoShowBtn;
    UIButton writePrescriptionBtn;
    UIButton viewPatientHistoryBtn;

    bool viewTodayClicked;
    bool markCompleteClicked;
    bool markNoShowClicked;
    bool writePrescriptionClicked;
    bool viewHistoryClicked;

    void updateTodayAppointmentList();
    void clearTodayAppointmentsState();

public:
    DoctorDash();
    ~DoctorDash();

    bool initialize(const sf::Font &regularFontParam, const sf::Font &boldFontParam);
    void setDoctor(Doctor *doc);
    void draw(sf::RenderWindow &window) const;
    void handleMouseClick(sf::RenderWindow &window);

    bool consumeViewTodayAppointmentsRequest();
    bool consumeMarkAppointmentCompleteRequest();
    bool consumeMarkAppointmentCompleteSubmitRequest();
    bool consumeMarkAppointmentNoShowRequest();
    bool consumeMarkAppointmentNoShowSubmitRequest();
    bool consumeWritePrescriptionRequest();
    bool consumeWritePrescriptionSubmitRequest();
    bool consumeViewPatientHistoryRequest();
    bool consumeViewMedicalHistorySubmitRequest();

    void handleTextEntered(char32_t unicode);

    void setTodayAppointments(Storage<Appointment> *appointments, Storage<Patient> *patients);
    void startTodayAppointmentsMode();
    void closeTodayAppointmentsMode();
    void startMarkCompleteMode();
    void closeMarkCompleteMode();
    void startMarkNoShowMode();
    void closeMarkNoShowMode();
    void startWritePrescriptionMode();
    void closeWritePrescriptionMode();
    void startViewMedicalHistoryMode();
    void closeViewMedicalHistoryMode();
    void setPatientListForMedicalHistory(Storage<Patient> *patients, Storage<Appointment> *appointments);
    void setPrescriptionsForPatient(Storage<Prescription> *prescriptions, int patientID, int doctorID);
    void displayPrescriptionsForPatient();

    const char *getMarkCompleteAppointmentIDText() const;
    const char *getMarkNoShowAppointmentIDText() const;
    const char *getWritePrescriptionAppointmentIDText() const;
    const char *getWritePrescriptionMedicinesText() const;
    const char *getWritePrescriptionNotesText() const;
    const char *getViewMedicalHistoryPatientIDText() const;

    void clearClickStates();
    void setStatus(const char *message);
};
