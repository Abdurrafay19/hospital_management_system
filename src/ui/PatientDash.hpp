#pragma once

#include <SFML/Graphics.hpp>
#include "../entities/Patient.hpp"
#include "UIButton.hpp"
#include "UITextBox.hpp"

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
    sf::Text* bookingTitleText;
    sf::Text* bookingDoctorLabelText;
    sf::Text* bookingDateLabelText;
    sf::Text* bookingTimeLabelText;

    sf::RectangleShape bookingPanel;
    UITextBox doctorIdInput;
    UITextBox bookingDateInput;
    UITextBox bookingTimeInput;

    UIButton bookAppointmentBtn;
    UIButton cancelAppointmentBtn;
    UIButton viewAppointmentsBtn;
    UIButton viewMedicalRecordsBtn;
    UIButton viewBillsBtn;
    UIButton payBillBtn;
    UIButton topUpBalanceBtn;
    UIButton confirmBookingBtn;
    UIButton cancelBookingBtn;

    bool bookAppointmentClicked;
    bool cancelAppointmentClicked;
    bool viewAppointmentsClicked;
    bool viewMedicalRecordsClicked;
    bool viewBillsClicked;
    bool payBillClicked;
    bool topUpBalanceClicked;

    bool bookingMode;
    bool bookAppointmentRequested;
    int bookingFocusedField;

    void updateBookingFocus(int focusedField);
    
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
    bool isBookingMode() const;
    bool consumeBookAppointmentRequest();
    const char* getBookingDoctorIDText() const;
    const char* getBookingDateText() const;
    const char* getBookingTimeText() const;

    bool isBookAppointmentClicked() const;
    bool isCancelAppointmentClicked() const;
    bool isViewAppointmentsClicked() const;
    bool isViewMedicalRecordsClicked() const;
    bool isViewBillsClicked() const;
    bool isPayBillClicked() const;
    bool isTopUpBalanceClicked() const;
    
    void clearClickStates();
    void setStatus(const char* message);
};
