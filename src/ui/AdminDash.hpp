#pragma once

#include <SFML/Graphics.hpp>
#include "UIButton.hpp"
#include "UITextBox.hpp"
#include "../entities/Storage.hpp"
#include "../entities/Doctor.hpp"
#include "../entities/Patient.hpp"
#include "../entities/Appointment.hpp"
#include "../entities/Bill.hpp"

class AdminDash
{
private:
    enum
    {
        PAGED_LIST_MAX_ITEMS = 100,
        PAGED_LIST_MAX_LINE_LENGTH = 260,
        PAGED_LIST_MAX_VISIBLE_ROWS = 14
    };

    enum PagedListViewType
    {
        PAGED_LIST_NONE,
        PAGED_LIST_REMOVE_DOCTOR,
        PAGED_LIST_PATIENTS,
        PAGED_LIST_DOCTORS,
        PAGED_LIST_APPOINTMENTS,
        PAGED_LIST_UNPAID_BILLS
    };

    sf::Font regularFont;
    sf::Font boldFont;

    sf::RectangleShape dashboardCard;
    sf::Text *titleText;
    sf::Text *welcomeText;
    sf::Text *statusText;

    bool addDoctorMode;
    sf::RectangleShape addDoctorPanel;
    sf::Text *addDoctorTitleText;
    sf::Text *addDoctorStatusText;
    sf::Text *addDoctorNameLabelText;
    sf::Text *addDoctorSpecializationLabelText;
    sf::Text *addDoctorContactLabelText;
    sf::Text *addDoctorPasswordLabelText;
    sf::Text *addDoctorFeeLabelText;
    UITextBox addDoctorNameInput;
    UITextBox addDoctorSpecializationInput;
    UITextBox addDoctorContactInput;
    UITextBox addDoctorPasswordInput;
    UITextBox addDoctorFeeInput;
    UIButton confirmAddDoctorBtn;
    UIButton backFromAddDoctorBtn;
    bool addDoctorSubmitRequested;

    bool removeDoctorMode;
    sf::RectangleShape removeDoctorPanel;
    PagedListViewType pagedListViewType;
    sf::Text *removeDoctorTitleText;
    sf::Text *removeDoctorStatusText;
    sf::Text *removeDoctorLabelText;
    sf::Text *removeDoctorIdLabelText;
    sf::Text *removeDoctorListText[30];
    int removeDoctorCount;
    UIButton removeDoctorPrevBtn;
    UIButton removeDoctorNextBtn;
    sf::Text *removeDoctorPageInfoText;
    UITextBox removeDoctorIdInput;
    UIButton confirmRemoveDoctorBtn;
    UIButton backFromRemoveDoctorBtn;
    bool removeDoctorSubmitRequested;

    char pagedListItems[PAGED_LIST_MAX_ITEMS][PAGED_LIST_MAX_LINE_LENGTH];
    int pagedListTotalItems;
    int pagedListCurrentPage;
    int pagedListPageSize;

    void clearPagedListItems();
    void appendPagedListItem(const char *line);
    int getPagedListTotalPages() const;
    void updateRemoveDoctorVisiblePage();
    void startPagedListMode(PagedListViewType viewType);
    void closePagedListMode();
    void setPagedListHeader(const char *title, const char *header, const char *prompt);

    UIButton addDoctorBtn;
    UIButton removeDoctorBtn;
    UIButton viewAllPatientsBtn;
    UIButton viewAllDoctorsBtn;
    UIButton viewAllAppointmentsBtn;
    UIButton viewUnpaidBillsBtn;
    UIButton dischargePatientBtn;
    UIButton viewSecurityLogBtn;
    UIButton generateDailyReportBtn;

    bool addDoctorClicked;
    bool removeDoctorClicked;
    bool viewAllPatientsClicked;
    bool viewAllDoctorsClicked;
    bool viewAllAppointmentsClicked;
    bool viewUnpaidBillsClicked;
    bool dischargePatientClicked;
    bool viewSecurityLogClicked;
    bool generateDailyReportClicked;

public:
    AdminDash();
    ~AdminDash();

    bool initialize(const sf::Font &regularFontParam, const sf::Font &boldFontParam);
    void draw(sf::RenderWindow &window) const;
    void handleMouseClick(sf::RenderWindow &window);
    void handleTextEntered(char32_t unicode);

    bool consumeAddDoctorRequest();
    bool consumeAddDoctorSubmitRequest();
    bool consumeRemoveDoctorRequest();
    bool consumeRemoveDoctorSubmitRequest();
    bool consumeViewAllPatientsRequest();
    bool consumeViewAllDoctorsRequest();
    bool consumeViewAllAppointmentsRequest();
    bool consumeViewUnpaidBillsRequest();
    bool consumeDischargePatientRequest();
    bool consumeViewSecurityLogRequest();
    bool consumeGenerateDailyReportRequest();

    void clearClickStates();
    void setStatus(const char *message);
    void setWelcome(const char *name);
    void startAddDoctorMode();
    void closeAddDoctorMode();
    void setDoctorsForRemoval(Storage<Doctor> *doctors);
    void setDoctorsForView(Storage<Doctor> *doctors);
    void setPatientsForView(Storage<Patient> *patients, Storage<Bill> *bills);
    void setAppointmentsForView(Storage<Appointment> *appointments, Storage<Patient> *patients, Storage<Doctor> *doctors);
    void setUnpaidBillsForView(Storage<Bill> *bills, Storage<Patient> *patients);
    void startRemoveDoctorMode();
    void closeRemoveDoctorMode();

    const char *getAddDoctorNameText() const;
    const char *getAddDoctorSpecializationText() const;
    const char *getAddDoctorContactText() const;
    const char *getAddDoctorPasswordText() const;
    const char *getAddDoctorFeeText() const;
    const char *getRemoveDoctorIDText() const;
};
