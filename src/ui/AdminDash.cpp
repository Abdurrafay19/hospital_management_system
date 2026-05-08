#include "AdminDash.hpp"
#include "UIThemeHelper.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"
#include "../helpers/TimeHelper.hpp"
#include "../helpers/DataHelper.hpp"
#include "../core/FileHandler.hpp"

#include <ctime>

AdminDash::AdminDash()
      : titleText(nullptr), welcomeText(nullptr), statusText(nullptr),
        addDoctorMode(false), addDoctorTitleText(nullptr), addDoctorStatusText(nullptr),
        addDoctorNameLabelText(nullptr), addDoctorSpecializationLabelText(nullptr), addDoctorContactLabelText(nullptr),
        addDoctorPasswordLabelText(nullptr), addDoctorFeeLabelText(nullptr), addDoctorSubmitRequested(false),
        removeDoctorMode(false), pagedListViewType(PAGED_LIST_NONE), removeDoctorTitleText(nullptr), removeDoctorStatusText(nullptr),
        removeDoctorLabelText(nullptr), removeDoctorIdLabelText(nullptr), removeDoctorCount(0),
        removeDoctorPageInfoText(nullptr), removeDoctorSubmitRequested(false),
        pagedListTotalItems(0), pagedListCurrentPage(0), pagedListPageSize(PAGED_LIST_MAX_VISIBLE_ROWS),
        dischargePatientMode(false), dischargePatientTitleText(nullptr), dischargePatientStatusText(nullptr), dischargePatientIdLabelText(nullptr), dischargePatientSubmitRequested(false),
    addDoctorClicked(false), removeDoctorClicked(false), viewAllPatientsClicked(false), viewAllDoctorsClicked(false),
    viewAllAppointmentsClicked(false), viewUnpaidBillsClicked(false), dischargePatientClicked(false),
    viewSecurityLogClicked(false), generateDailyReportClicked(false)
{
    int i;
    for (i = 0; i < 30; i++)
    {
        removeDoctorListText[i] = nullptr;
    }

    for (i = 0; i < PAGED_LIST_MAX_ITEMS; i++)
    {
        pagedListItems[i][0] = '\0';
    }
}

AdminDash::~AdminDash()
{
    delete titleText;
    delete welcomeText;
    delete statusText;
    delete addDoctorTitleText;
    delete addDoctorStatusText;
    delete addDoctorNameLabelText;
    delete addDoctorSpecializationLabelText;
    delete addDoctorContactLabelText;
    delete addDoctorPasswordLabelText;
    delete addDoctorFeeLabelText;
    delete removeDoctorTitleText;
    delete removeDoctorStatusText;
    delete removeDoctorLabelText;
    delete removeDoctorIdLabelText;
    delete removeDoctorPageInfoText;
    delete dischargePatientTitleText;
    delete dischargePatientStatusText;
    delete dischargePatientIdLabelText;
    titleText = nullptr;
    welcomeText = nullptr;
    statusText = nullptr;
    addDoctorTitleText = nullptr;
    addDoctorStatusText = nullptr;
    addDoctorNameLabelText = nullptr;
    addDoctorSpecializationLabelText = nullptr;
    addDoctorContactLabelText = nullptr;
    addDoctorPasswordLabelText = nullptr;
    addDoctorFeeLabelText = nullptr;
    removeDoctorTitleText = nullptr;
    removeDoctorStatusText = nullptr;
    removeDoctorLabelText = nullptr;
    removeDoctorIdLabelText = nullptr;
    removeDoctorPageInfoText = nullptr;
    dischargePatientTitleText = nullptr;
    dischargePatientStatusText = nullptr;
    dischargePatientIdLabelText = nullptr;

    int i;
    for (i = 0; i < 30; i++)
    {
        delete removeDoctorListText[i];
        removeDoctorListText[i] = nullptr;
    }
}

bool AdminDash::initialize(const sf::Font &regularFontParam, const sf::Font &boldFontParam)
{
    regularFont = regularFontParam;
    boldFont = boldFontParam;

    // Fit within 1280x720 window (leave some margin at bottom)
    dashboardCard.setSize(sf::Vector2f(1100.f, 560.f));
    dashboardCard.setPosition(sf::Vector2f(90.f, 80.f));
    UIThemeHelper::styleDashboardCard(dashboardCard);

    titleText = new sf::Text(boldFont, "Admin Dashboard", 32);
    welcomeText = new sf::Text(regularFont, "", 18);
    statusText = new sf::Text(regularFont, "", 16);

    titleText->setPosition(sf::Vector2f(110.f, 100.f));
    UIThemeHelper::styleTitleText(titleText);

    // Welcome text just below title
    welcomeText->setPosition(sf::Vector2f(110.f, 140.f));
    UIThemeHelper::styleLabelText(welcomeText);

    statusText->setPosition(sf::Vector2f(110.f, 600.f));
    UIThemeHelper::styleStatusText(statusText);

    addDoctorPanel.setSize(sf::Vector2f(880.f, 500.f));
    addDoctorPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(addDoctorPanel);

    addDoctorTitleText = new sf::Text(boldFont, "Add Doctor", 24);
    addDoctorStatusText = new sf::Text(regularFont, "", 14);
    addDoctorNameLabelText = new sf::Text(regularFont, "Name (max 50):", 16);
    addDoctorSpecializationLabelText = new sf::Text(regularFont, "Specialization (max 50):", 16);
    addDoctorContactLabelText = new sf::Text(regularFont, "Contact (11 digits):", 16);
    addDoctorPasswordLabelText = new sf::Text(regularFont, "Password (min 6):", 16);
    addDoctorFeeLabelText = new sf::Text(regularFont, "Consultation Fee:", 16);

    addDoctorTitleText->setPosition(sf::Vector2f(230.f, 155.f));
    UIThemeHelper::styleTitleText(addDoctorTitleText);
    addDoctorStatusText->setPosition(sf::Vector2f(230.f, 588.f));
    UIThemeHelper::styleStatusText(addDoctorStatusText);

    addDoctorNameLabelText->setPosition(sf::Vector2f(230.f, 205.f));
    addDoctorSpecializationLabelText->setPosition(sf::Vector2f(230.f, 275.f));
    addDoctorContactLabelText->setPosition(sf::Vector2f(230.f, 345.f));
    addDoctorPasswordLabelText->setPosition(sf::Vector2f(230.f, 415.f));
    addDoctorFeeLabelText->setPosition(sf::Vector2f(230.f, 485.f));

    UIThemeHelper::styleLabelText(addDoctorNameLabelText);
    UIThemeHelper::styleLabelText(addDoctorSpecializationLabelText);
    UIThemeHelper::styleLabelText(addDoctorContactLabelText);
    UIThemeHelper::styleLabelText(addDoctorPasswordLabelText);
    UIThemeHelper::styleLabelText(addDoctorFeeLabelText);

    addDoctorNameInput = UITextBox(regularFont, sf::Vector2f(230.f, 230.f), sf::Vector2f(820.f, 38.f), 50);
    addDoctorSpecializationInput = UITextBox(regularFont, sf::Vector2f(230.f, 300.f), sf::Vector2f(820.f, 38.f), 50);
    addDoctorContactInput = UITextBox(regularFont, sf::Vector2f(230.f, 370.f), sf::Vector2f(820.f, 38.f), 11);
    addDoctorPasswordInput = UITextBox(regularFont, sf::Vector2f(230.f, 440.f), sf::Vector2f(820.f, 38.f), 50);
    addDoctorFeeInput = UITextBox(regularFont, sf::Vector2f(230.f, 510.f), sf::Vector2f(820.f, 38.f), 20);

    UIThemeHelper::styleInput(addDoctorNameInput);
    UIThemeHelper::styleInput(addDoctorSpecializationInput);
    UIThemeHelper::styleInput(addDoctorContactInput);
    UIThemeHelper::styleInput(addDoctorPasswordInput);
    UIThemeHelper::styleInput(addDoctorFeeInput);

    confirmAddDoctorBtn = UIButton(regularFont, "Add Doctor", sf::Vector2f(850.f, 560.f), sf::Vector2f(200.f, 40.f));
    confirmAddDoctorBtn.setFillColor(sf::Color(39, 174, 96));
    confirmAddDoctorBtn.setOutlineColor(sf::Color(39, 174, 96));
    confirmAddDoctorBtn.setTextColor(sf::Color::White);

    backFromAddDoctorBtn = UIButton(regularFont, "Back", sf::Vector2f(740.f, 560.f), sf::Vector2f(90.f, 40.f));
    UIThemeHelper::styleSecondaryButton(backFromAddDoctorBtn);

    removeDoctorPanel.setSize(sf::Vector2f(880.f, 500.f));
    removeDoctorPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(removeDoctorPanel);

    removeDoctorTitleText = new sf::Text(boldFont, "Remove Doctor", 24);
    removeDoctorStatusText = new sf::Text(regularFont, "", 14);
    removeDoctorLabelText = new sf::Text(regularFont, "ID | Name | Specialization | Fee", 15);
    removeDoctorIdLabelText = new sf::Text(regularFont, "Enter Doctor ID to remove:", 16);
    removeDoctorPageInfoText = new sf::Text(regularFont, "", 14);

    removeDoctorTitleText->setPosition(sf::Vector2f(230.f, 155.f));
    UIThemeHelper::styleTitleText(removeDoctorTitleText);
    removeDoctorStatusText->setPosition(sf::Vector2f(230.f, 588.f));
    UIThemeHelper::styleStatusText(removeDoctorStatusText);
    removeDoctorLabelText->setPosition(sf::Vector2f(230.f, 215.f));
    UIThemeHelper::styleLabelText(removeDoctorLabelText);
    removeDoctorIdLabelText->setPosition(sf::Vector2f(230.f, 520.f));
    UIThemeHelper::styleLabelText(removeDoctorIdLabelText);
    removeDoctorPageInfoText->setPosition(sf::Vector2f(470.f, 570.f));
    UIThemeHelper::styleLabelText(removeDoctorPageInfoText);

    removeDoctorIdInput = UITextBox(regularFont, sf::Vector2f(470.f, 513.f), sf::Vector2f(140.f, 36.f), 10);
    UIThemeHelper::styleInput(removeDoctorIdInput);

    confirmRemoveDoctorBtn = UIButton(regularFont, "Remove", sf::Vector2f(850.f, 560.f), sf::Vector2f(200.f, 40.f));
    UIThemeHelper::styleCriticalButton(confirmRemoveDoctorBtn);

    backFromRemoveDoctorBtn = UIButton(regularFont, "Back", sf::Vector2f(740.f, 560.f), sf::Vector2f(90.f, 40.f));
    UIThemeHelper::styleSecondaryButton(backFromRemoveDoctorBtn);

    removeDoctorPrevBtn = UIButton(regularFont, "Prev", sf::Vector2f(230.f, 560.f), sf::Vector2f(100.f, 40.f));
    UIThemeHelper::stylePrimaryButton(removeDoctorPrevBtn);

    removeDoctorNextBtn = UIButton(regularFont, "Next", sf::Vector2f(345.f, 560.f), sf::Vector2f(100.f, 40.f));
    UIThemeHelper::stylePrimaryButton(removeDoctorNextBtn);

    dischargePatientPanel.setSize(sf::Vector2f(880.f, 500.f));
    dischargePatientPanel.setPosition(sf::Vector2f(200.f, 130.f));
    UIThemeHelper::stylePanel(dischargePatientPanel);

    dischargePatientTitleText = new sf::Text(boldFont, "Discharge Patient", 24);
    dischargePatientStatusText = new sf::Text(regularFont, "", 14);
    dischargePatientIdLabelText = new sf::Text(regularFont, "Enter Patient ID:", 16);

    dischargePatientTitleText->setPosition(sf::Vector2f(230.f, 155.f));
    UIThemeHelper::styleTitleText(dischargePatientTitleText);
    dischargePatientStatusText->setPosition(sf::Vector2f(230.f, 588.f));
    UIThemeHelper::styleStatusText(dischargePatientStatusText);
    dischargePatientIdLabelText->setPosition(sf::Vector2f(230.f, 215.f));
    UIThemeHelper::styleLabelText(dischargePatientIdLabelText);

    dischargePatientIdInput = UITextBox(regularFont, sf::Vector2f(470.f, 208.f), sf::Vector2f(140.f, 36.f), 10);
    UIThemeHelper::styleInput(dischargePatientIdInput);

    confirmDischargePatientBtn = UIButton(regularFont, "Discharge", sf::Vector2f(850.f, 560.f), sf::Vector2f(200.f, 40.f));
    UIThemeHelper::styleCriticalButton(confirmDischargePatientBtn);

    backFromDischargePatientBtn = UIButton(regularFont, "Back", sf::Vector2f(740.f, 560.f), sf::Vector2f(90.f, 40.f));
    UIThemeHelper::styleSecondaryButton(backFromDischargePatientBtn);

    int removeIndex;
    for (removeIndex = 0; removeIndex < 30; removeIndex++)
    {
        removeDoctorListText[removeIndex] = new sf::Text(regularFont, "", 14);
        removeDoctorListText[removeIndex]->setPosition(sf::Vector2f(230.f, 240.f + (removeIndex * 18.f)));
        UIThemeHelper::styleBodyText(removeDoctorListText[removeIndex]);
    }

    sf::Vector2f btnSize(320.f, 48.f);
    float startX = 120.f;
    float startY = 190.f;
    float hGap = 20.f;
    float vGap = 24.f;

    // Create and style buttons (positioned in a 3-column grid)
    addDoctorBtn = UIButton(regularFont, "Add Doctor", sf::Vector2f(startX, startY), btnSize);
    removeDoctorBtn = UIButton(regularFont, "Remove Doctor", sf::Vector2f(startX + (btnSize.x + hGap), startY), btnSize);
    viewAllPatientsBtn = UIButton(regularFont, "View All Patients", sf::Vector2f(startX + 2 * (btnSize.x + hGap), startY), btnSize);

    viewAllDoctorsBtn = UIButton(regularFont, "View All Doctors", sf::Vector2f(startX, startY + (btnSize.y + vGap)), btnSize);
    viewAllAppointmentsBtn = UIButton(regularFont, "View All Appointments", sf::Vector2f(startX + (btnSize.x + hGap), startY + (btnSize.y + vGap)), btnSize);
    viewUnpaidBillsBtn = UIButton(regularFont, "View Unpaid Bills", sf::Vector2f(startX + 2 * (btnSize.x + hGap), startY + (btnSize.y + vGap)), btnSize);

    dischargePatientBtn = UIButton(regularFont, "Discharge Patient", sf::Vector2f(startX, startY + 2 * (btnSize.y + vGap)), btnSize);
    viewSecurityLogBtn = UIButton(regularFont, "View Security Log", sf::Vector2f(startX + (btnSize.x + hGap), startY + 2 * (btnSize.y + vGap)), btnSize);
    generateDailyReportBtn = UIButton(regularFont, "Generate Daily Report", sf::Vector2f(startX + 2 * (btnSize.x + hGap), startY + 2 * (btnSize.y + vGap)), btnSize);

    // Style buttons to match DoctorDash appearance
    UIButton *btns[9] = {&addDoctorBtn, &removeDoctorBtn, &viewAllPatientsBtn, &viewAllDoctorsBtn, &viewAllAppointmentsBtn, &viewUnpaidBillsBtn, &dischargePatientBtn, &viewSecurityLogBtn, &generateDailyReportBtn};
    for (int i = 0; i < 9; i++)
    {
        btns[i]->setFont(regularFont);
        UIThemeHelper::stylePrimaryButton(*btns[i]);
    }

    return true;
}

void AdminDash::draw(sf::RenderWindow &window) const
{
    window.draw(dashboardCard);
    if (titleText != nullptr)
    {
        window.draw(*titleText);
    }
    if (statusText != nullptr)
    {
        window.draw(*statusText);
    }

    if (welcomeText != nullptr && welcomeText->getString() != "")
    {
        window.draw(*welcomeText);
    }

    if (addDoctorMode)
    {
        window.draw(addDoctorPanel);
        if (addDoctorTitleText != nullptr)
        {
            window.draw(*addDoctorTitleText);
        }
        if (addDoctorStatusText != nullptr)
        {
            window.draw(*addDoctorStatusText);
        }
        if (addDoctorNameLabelText != nullptr)
        {
            window.draw(*addDoctorNameLabelText);
        }
        if (addDoctorSpecializationLabelText != nullptr)
        {
            window.draw(*addDoctorSpecializationLabelText);
        }
        if (addDoctorContactLabelText != nullptr)
        {
            window.draw(*addDoctorContactLabelText);
        }
        if (addDoctorPasswordLabelText != nullptr)
        {
            window.draw(*addDoctorPasswordLabelText);
        }
        if (addDoctorFeeLabelText != nullptr)
        {
            window.draw(*addDoctorFeeLabelText);
        }

        addDoctorNameInput.draw(window);
        addDoctorSpecializationInput.draw(window);
        addDoctorContactInput.draw(window);
        addDoctorPasswordInput.draw(window);
        addDoctorFeeInput.draw(window);
        confirmAddDoctorBtn.draw(window);
        backFromAddDoctorBtn.draw(window);
        return;
    }

    if (removeDoctorMode)
    {
        int i;

        window.draw(removeDoctorPanel);
        if (removeDoctorTitleText != nullptr)
        {
            window.draw(*removeDoctorTitleText);
        }
        if (removeDoctorStatusText != nullptr)
        {
            window.draw(*removeDoctorStatusText);
        }
        if (removeDoctorLabelText != nullptr)
        {
            window.draw(*removeDoctorLabelText);
        }
        if (pagedListViewType == PAGED_LIST_REMOVE_DOCTOR && removeDoctorIdLabelText != nullptr)
        {
            window.draw(*removeDoctorIdLabelText);
        }
        if (removeDoctorPageInfoText != nullptr)
        {
            window.draw(*removeDoctorPageInfoText);
        }

        for (i = 0; i < removeDoctorCount; i++)
        {
            if (removeDoctorListText[i] != nullptr)
            {
                window.draw(*removeDoctorListText[i]);
            }
        }

        removeDoctorPrevBtn.draw(window);
        removeDoctorNextBtn.draw(window);
        if (pagedListViewType == PAGED_LIST_REMOVE_DOCTOR)
        {
            removeDoctorIdInput.draw(window);
            confirmRemoveDoctorBtn.draw(window);
        }
        backFromRemoveDoctorBtn.draw(window);
        return;
    }

    if (dischargePatientMode)
    {
        window.draw(dischargePatientPanel);
        if (dischargePatientTitleText != nullptr)
        {
            window.draw(*dischargePatientTitleText);
        }
        if (dischargePatientStatusText != nullptr)
        {
            window.draw(*dischargePatientStatusText);
        }
        if (dischargePatientIdLabelText != nullptr)
        {
            window.draw(*dischargePatientIdLabelText);
        }
        dischargePatientIdInput.draw(window);
        confirmDischargePatientBtn.draw(window);
        backFromDischargePatientBtn.draw(window);
        // If a paged patients view is active, render its list inside this panel
        if (pagedListViewType == PAGED_LIST_PATIENTS)
        {
            int i;
            for (i = 0; i < removeDoctorCount; i++)
            {
                if (removeDoctorListText[i] != nullptr)
                {
                    window.draw(*removeDoctorListText[i]);
                }
            }

            if (removeDoctorPageInfoText != nullptr)
            {
                window.draw(*removeDoctorPageInfoText);
            }

            removeDoctorPrevBtn.draw(window);
            removeDoctorNextBtn.draw(window);
        }
        return;
    }

    addDoctorBtn.draw(window);
    removeDoctorBtn.draw(window);
    viewAllPatientsBtn.draw(window);
    viewAllDoctorsBtn.draw(window);
    viewAllAppointmentsBtn.draw(window);
    viewUnpaidBillsBtn.draw(window);
    dischargePatientBtn.draw(window);
    viewSecurityLogBtn.draw(window);
    generateDailyReportBtn.draw(window);
}

void AdminDash::handleMouseClick(sf::RenderWindow &window)
{
    sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (addDoctorMode)
    {
        if (addDoctorNameInput.contains(mouseWorldPosition))
        {
            addDoctorNameInput.setActive(true);
            addDoctorSpecializationInput.setActive(false);
            addDoctorContactInput.setActive(false);
            addDoctorPasswordInput.setActive(false);
            addDoctorFeeInput.setActive(false);
            return;
        }

        if (addDoctorSpecializationInput.contains(mouseWorldPosition))
        {
            addDoctorNameInput.setActive(false);
            addDoctorSpecializationInput.setActive(true);
            addDoctorContactInput.setActive(false);
            addDoctorPasswordInput.setActive(false);
            addDoctorFeeInput.setActive(false);
            return;
        }

        if (addDoctorContactInput.contains(mouseWorldPosition))
        {
            addDoctorNameInput.setActive(false);
            addDoctorSpecializationInput.setActive(false);
            addDoctorContactInput.setActive(true);
            addDoctorPasswordInput.setActive(false);
            addDoctorFeeInput.setActive(false);
            return;
        }

        if (addDoctorPasswordInput.contains(mouseWorldPosition))
        {
            addDoctorNameInput.setActive(false);
            addDoctorSpecializationInput.setActive(false);
            addDoctorContactInput.setActive(false);
            addDoctorPasswordInput.setActive(true);
            addDoctorFeeInput.setActive(false);
            return;
        }

        if (addDoctorFeeInput.contains(mouseWorldPosition))
        {
            addDoctorNameInput.setActive(false);
            addDoctorSpecializationInput.setActive(false);
            addDoctorContactInput.setActive(false);
            addDoctorPasswordInput.setActive(false);
            addDoctorFeeInput.setActive(true);
            return;
        }

        if (confirmAddDoctorBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            addDoctorSubmitRequested = true;
            return;
        }

        if (backFromAddDoctorBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeAddDoctorMode();
            return;
        }

        addDoctorNameInput.setActive(false);
        addDoctorSpecializationInput.setActive(false);
        addDoctorContactInput.setActive(false);
        addDoctorPasswordInput.setActive(false);
        addDoctorFeeInput.setActive(false);
        return;
    }

    if (removeDoctorMode)
    {
        if (removeDoctorPrevBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            if (pagedListCurrentPage > 0)
            {
                pagedListCurrentPage--;
                updateRemoveDoctorVisiblePage();
            }
            return;
        }

        if (removeDoctorNextBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            if (pagedListCurrentPage < getPagedListTotalPages() - 1)
            {
                pagedListCurrentPage++;
                updateRemoveDoctorVisiblePage();
            }
            return;
        }

        if (pagedListViewType == PAGED_LIST_REMOVE_DOCTOR && removeDoctorIdInput.contains(mouseWorldPosition))
        {
            removeDoctorIdInput.setActive(true);
            return;
        }

        if (pagedListViewType == PAGED_LIST_REMOVE_DOCTOR && confirmRemoveDoctorBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            removeDoctorSubmitRequested = true;
            return;
        }

        if (backFromRemoveDoctorBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeRemoveDoctorMode();
            return;
        }

        removeDoctorIdInput.setActive(false);
        return;
    }

    if (dischargePatientMode)
    {
        if (removeDoctorPrevBtn.getShape().getGlobalBounds().contains(mouseWorldPosition) && pagedListViewType == PAGED_LIST_PATIENTS)
        {
            if (pagedListCurrentPage > 0)
            {
                pagedListCurrentPage--;
                updateRemoveDoctorVisiblePage();
            }
            return;
        }

        if (removeDoctorNextBtn.getShape().getGlobalBounds().contains(mouseWorldPosition) && pagedListViewType == PAGED_LIST_PATIENTS)
        {
            if (pagedListCurrentPage < getPagedListTotalPages() - 1)
            {
                pagedListCurrentPage++;
                updateRemoveDoctorVisiblePage();
            }
            return;
        }

        if (dischargePatientIdInput.contains(mouseWorldPosition))
        {
            dischargePatientIdInput.setActive(true);
            return;
        }

        if (confirmDischargePatientBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            dischargePatientSubmitRequested = true;
            return;
        }

        if (backFromDischargePatientBtn.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            closeDischargePatientMode();
            return;
        }

        dischargePatientIdInput.setActive(false);
        return;
    }

    if (addDoctorBtn.isClicked(window))
    {
        addDoctorClicked = true;
    }
    if (removeDoctorBtn.isClicked(window))
    {
        removeDoctorClicked = true;
    }
    if (viewAllPatientsBtn.isClicked(window))
    {
        viewAllPatientsClicked = true;
    }
    if (viewAllDoctorsBtn.isClicked(window))
    {
        viewAllDoctorsClicked = true;
    }
    if (viewAllAppointmentsBtn.isClicked(window))
    {
        viewAllAppointmentsClicked = true;
    }
    if (viewUnpaidBillsBtn.isClicked(window))
    {
        viewUnpaidBillsClicked = true;
    }
    if (dischargePatientBtn.isClicked(window))
    {
        dischargePatientClicked = true;
    }
    if (viewSecurityLogBtn.isClicked(window))
    {
        viewSecurityLogClicked = true;
    }
    if (generateDailyReportBtn.isClicked(window))
    {
        generateDailyReportClicked = true;
    }
}

void AdminDash::handleTextEntered(char32_t unicode)
{
    if (addDoctorMode)
    {
        if (addDoctorNameInput.isActive())
        {
            addDoctorNameInput.handleTextEntered(unicode);
        }
        else if (addDoctorSpecializationInput.isActive())
        {
            addDoctorSpecializationInput.handleTextEntered(unicode);
        }
        else if (addDoctorContactInput.isActive())
        {
            addDoctorContactInput.handleTextEntered(unicode);
        }
        else if (addDoctorPasswordInput.isActive())
        {
            addDoctorPasswordInput.handleTextEntered(unicode);
        }
        else if (addDoctorFeeInput.isActive())
        {
            addDoctorFeeInput.handleTextEntered(unicode);
        }
        return;
    }

    if (removeDoctorMode && pagedListViewType == PAGED_LIST_REMOVE_DOCTOR && removeDoctorIdInput.isActive())
    {
        removeDoctorIdInput.handleTextEntered(unicode);
    }

    if (dischargePatientMode && dischargePatientIdInput.isActive())
    {
        dischargePatientIdInput.handleTextEntered(unicode);
    }
}

void AdminDash::setWelcome(const char *name)
{
    char message[220];
    int length;

    if (welcomeText == nullptr)
    {
        return;
    }

    if (StringHelper::isNullOrEmpty(name))
    {
        welcomeText->setString("");
        return;
    }

    message[0] = '\0';
    StringHelper::stringCopy(message, "Welcome back, ", 220);
    length = StringHelper::stringLength(message);
    StringHelper::stringCopy(message + length, name, 220 - length);
    welcomeText->setString(message);
}

bool AdminDash::consumeAddDoctorRequest()
{
    if (addDoctorClicked)
    {
        addDoctorClicked = false;
        return true;
    }
    return false;
}

bool AdminDash::consumeAddDoctorSubmitRequest()
{
    bool value;

    value = addDoctorSubmitRequested;
    addDoctorSubmitRequested = false;
    return value;
}

bool AdminDash::consumeRemoveDoctorRequest()
{
    if (removeDoctorClicked)
    {
        removeDoctorClicked = false;
        return true;
    }
    return false;
}

bool AdminDash::consumeRemoveDoctorSubmitRequest()
{
    bool value;

    value = removeDoctorSubmitRequested;
    removeDoctorSubmitRequested = false;
    return value;
}

bool AdminDash::consumeViewAllPatientsRequest()
{
    if (viewAllPatientsClicked)
    {
        viewAllPatientsClicked = false;
        return true;
    }
    return false;
}

bool AdminDash::consumeViewAllDoctorsRequest()
{
    if (viewAllDoctorsClicked)
    {
        viewAllDoctorsClicked = false;
        return true;
    }
    return false;
}

bool AdminDash::consumeViewAllAppointmentsRequest()
{
    if (viewAllAppointmentsClicked)
    {
        viewAllAppointmentsClicked = false;
        return true;
    }
    return false;
}

bool AdminDash::consumeViewUnpaidBillsRequest()
{
    if (viewUnpaidBillsClicked)
    {
        viewUnpaidBillsClicked = false;
        return true;
    }
    return false;
}

bool AdminDash::consumeDischargePatientRequest()
{
    if (dischargePatientClicked)
    {
        dischargePatientClicked = false;
        return true;
    }
    return false;
}

bool AdminDash::consumeDischargePatientSubmitRequest()
{
    bool value;

    value = dischargePatientSubmitRequested;
    dischargePatientSubmitRequested = false;
    return value;
}

bool AdminDash::consumeViewSecurityLogRequest()
{
    if (viewSecurityLogClicked)
    {
        viewSecurityLogClicked = false;
        return true;
    }
    return false;
}

bool AdminDash::consumeGenerateDailyReportRequest()
{
    if (generateDailyReportClicked)
    {
        generateDailyReportClicked = false;
        return true;
    }
    return false;
}

void AdminDash::clearClickStates()
{
    addDoctorClicked = false;
    removeDoctorClicked = false;
    viewAllPatientsClicked = false;
    viewAllDoctorsClicked = false;
    viewAllAppointmentsClicked = false;
    viewUnpaidBillsClicked = false;
    dischargePatientClicked = false;
    viewSecurityLogClicked = false;
    generateDailyReportClicked = false;
}

void AdminDash::setStatus(const char *message)
{
    if (statusText != nullptr && message != nullptr)
    {
        statusText->setString(message);
    }

    if (addDoctorStatusText != nullptr && message != nullptr)
    {
        addDoctorStatusText->setString(message);
    }

    if (removeDoctorStatusText != nullptr && message != nullptr)
    {
        removeDoctorStatusText->setString(message);
    }
    
    if (dischargePatientStatusText != nullptr && message != nullptr)
    {
        dischargePatientStatusText->setString(message);
    }
}

void AdminDash::startAddDoctorMode()
{
    addDoctorMode = true;
    addDoctorSubmitRequested = false;
    addDoctorNameInput.clear();
    addDoctorSpecializationInput.clear();
    addDoctorContactInput.clear();
    addDoctorPasswordInput.clear();
    addDoctorFeeInput.clear();
    addDoctorNameInput.setActive(false);
    addDoctorSpecializationInput.setActive(false);
    addDoctorContactInput.setActive(false);
    addDoctorPasswordInput.setActive(false);
    addDoctorFeeInput.setActive(false);
    if (addDoctorStatusText != nullptr)
    {
        addDoctorStatusText->setString("");
    }
}

void AdminDash::closeAddDoctorMode()
{
    addDoctorMode = false;
    addDoctorSubmitRequested = false;
    addDoctorNameInput.setActive(false);
    addDoctorSpecializationInput.setActive(false);
    addDoctorContactInput.setActive(false);
    addDoctorPasswordInput.setActive(false);
    addDoctorFeeInput.setActive(false);
    addDoctorNameInput.clear();
    addDoctorSpecializationInput.clear();
    addDoctorContactInput.clear();
    addDoctorPasswordInput.clear();
    addDoctorFeeInput.clear();
}

const char *AdminDash::getAddDoctorNameText() const
{
    return addDoctorNameInput.getText();
}

const char *AdminDash::getAddDoctorSpecializationText() const
{
    return addDoctorSpecializationInput.getText();
}

const char *AdminDash::getAddDoctorContactText() const
{
    return addDoctorContactInput.getText();
}

const char *AdminDash::getAddDoctorPasswordText() const
{
    return addDoctorPasswordInput.getText();
}

const char *AdminDash::getAddDoctorFeeText() const
{
    return addDoctorFeeInput.getText();
}

const char *AdminDash::getDischargePatientIDText() const
{
    return dischargePatientIdInput.getText();
}

void AdminDash::startDischargePatientMode()
{
    dischargePatientMode = true;
    dischargePatientSubmitRequested = false;
    dischargePatientIdInput.clear();
    dischargePatientIdInput.setActive(false);
}

void AdminDash::closeDischargePatientMode()
{
    dischargePatientMode = false;
    dischargePatientSubmitRequested = false;
    dischargePatientIdInput.clear();
    dischargePatientIdInput.setActive(false);
}

void AdminDash::setDischargePatientStatus(const char *message)
{
    if (dischargePatientStatusText != nullptr && message != nullptr)
    {
        dischargePatientStatusText->setString(message);
    }
}

void AdminDash::setDoctorsForRemoval(Storage<Doctor> *doctors)
{
    int i;

    clearPagedListItems();

    if (doctors == nullptr)
    {
        updateRemoveDoctorVisiblePage();
        return;
    }

    for (i = 0; i < doctors->size(); i++)
    {
        char line[260];
        char namePreview[64];
        char specializationPreview[64];
        char idBuffer[32];
        char feeBuffer[32];
        int len;

        line[0] = '\0';
        ConversionHelper::intToString(doctors->getAll()[i].getID(), idBuffer);
        ConversionHelper::doubleToString(doctors->getAll()[i].getFee(), feeBuffer);
        StringHelper::copyPreviewText(namePreview, 64, doctors->getAll()[i].getName(), 18);
        StringHelper::copyPreviewText(specializationPreview, 64, doctors->getAll()[i].getSpecialization(), 16);

        StringHelper::stringCopy(line, idBuffer, 260);
        len = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + len, " | ", 260 - len);
        len = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + len, namePreview, 260 - len);
        len = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + len, " | ", 260 - len);
        len = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + len, specializationPreview, 260 - len);
        len = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + len, " | ", 260 - len);
        len = StringHelper::stringLength(line);
        StringHelper::stringCopy(line + len, feeBuffer, 260 - len);

        appendPagedListItem(line);
    }

    updateRemoveDoctorVisiblePage();
}

void AdminDash::startRemoveDoctorMode()
{
    setPagedListHeader("Remove Doctor", "ID | Name | Specialization | Fee", "Enter Doctor ID to remove:");
    startPagedListMode(PAGED_LIST_REMOVE_DOCTOR);
    if (removeDoctorStatusText != nullptr)
    {
        removeDoctorStatusText->setString("");
    }
}

void AdminDash::closeRemoveDoctorMode()
{
    closePagedListMode();
}

const char *AdminDash::getRemoveDoctorIDText() const
{
    return removeDoctorIdInput.getText();
}

void AdminDash::startPagedListMode(PagedListViewType viewType)
{
    pagedListViewType = viewType;
    pagedListCurrentPage = 0;
    removeDoctorSubmitRequested = false;
    removeDoctorIdInput.clear();
    removeDoctorIdInput.setActive(false);

    // If we're opening the patients paged view inside discharge mode, do not switch to the
    // standalone removeDoctorMode panel. This keeps the patients list embedded in the
    // discharge patient panel when that mode is active.
    if (viewType == PAGED_LIST_PATIENTS && dischargePatientMode)
    {
        // clear any text-only id input used for remove-doctor flow
        removeDoctorIdInput.setText("");
    }
    else
    {
        removeDoctorMode = true;
        if (viewType != PAGED_LIST_REMOVE_DOCTOR)
        {
            removeDoctorIdInput.setText("");
        }
    }

    updateRemoveDoctorVisiblePage();
}

void AdminDash::closePagedListMode()
{
    // Close the paged-list view while preserving any active discharge panel state.
    removeDoctorMode = false;
    pagedListViewType = PAGED_LIST_NONE;
    removeDoctorSubmitRequested = false;
    removeDoctorIdInput.clear();
    removeDoctorIdInput.setActive(false);
}

void AdminDash::setPagedListHeader(const char *title, const char *header, const char *prompt)
{
    if (removeDoctorTitleText != nullptr)
    {
        removeDoctorTitleText->setString(title != nullptr ? title : "");
    }
    if (removeDoctorLabelText != nullptr)
    {
        removeDoctorLabelText->setString(header != nullptr ? header : "");
    }
    if (removeDoctorIdLabelText != nullptr)
    {
        removeDoctorIdLabelText->setString(prompt != nullptr ? prompt : "");
    }
}

// Helper implementations moved to src/helpers/* (StringHelper, DataHelper, TimeHelper)

void AdminDash::setDoctorsForView(Storage<Doctor> *doctors)
{
    int i;
    char line[260];
    char idBuffer[32];
    char feeBuffer[32];
    char namePreview[64];
    char specializationPreview[64];
    int len;

    clearPagedListItems();
    setPagedListHeader("View All Doctors", "ID | Name | Specialization | Contact | Fee", "");

    if (doctors != nullptr)
    {
        for (i = 0; i < doctors->size(); i++)
        {
            line[0] = '\0';
            ConversionHelper::intToString(doctors->getAll()[i].getID(), idBuffer);
            ConversionHelper::doubleToString(doctors->getAll()[i].getFee(), feeBuffer);
            StringHelper::copyPreviewText(namePreview, 64, doctors->getAll()[i].getName(), 18);
            StringHelper::copyPreviewText(specializationPreview, 64, doctors->getAll()[i].getSpecialization(), 18);

            StringHelper::appendTextField(line, 260, idBuffer);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, namePreview);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, specializationPreview);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, doctors->getAll()[i].getContact() != nullptr ? doctors->getAll()[i].getContact() : "");
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, feeBuffer);

            appendPagedListItem(line);
        }
    }

    startPagedListMode(PAGED_LIST_DOCTORS);
    setStatus("");
}

void AdminDash::setPatientsForView(Storage<Patient> *patients, Storage<Bill> *bills)
{
    int i;
    char line[260];
    char idBuffer[32];
    char ageBuffer[32];
    char balanceBuffer[32];
    char unpaidBuffer[32];
    char namePreview[64];
    char genderPreview[32];
    char contactPreview[32];

    clearPagedListItems();
    setPagedListHeader("View All Patients", "ID | Name | Age | Gender | Contact | Balance | Unpaid Bills", "");

    if (patients != nullptr)
    {
        for (i = 0; i < patients->size(); i++)
        {
            line[0] = '\0';
            ConversionHelper::intToString(patients->getAll()[i].getID(), idBuffer);
            ConversionHelper::intToString(patients->getAll()[i].getAge(), ageBuffer);
            ConversionHelper::doubleToString(patients->getAll()[i].getBalance(), balanceBuffer);
            ConversionHelper::intToString(DataHelper::countUnpaidBillsForPatient(bills, patients->getAll()[i].getID()), unpaidBuffer);
            StringHelper::copyPreviewText(namePreview, 64, patients->getAll()[i].getName(), 18);
            StringHelper::copyPreviewText(genderPreview, 32, patients->getAll()[i].getGender(), 8);
            StringHelper::copyPreviewText(contactPreview, 32, patients->getAll()[i].getContact(), 11);

            StringHelper::appendTextField(line, 260, idBuffer);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, namePreview);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, ageBuffer);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, genderPreview);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, contactPreview);
            StringHelper::appendTextField(line, 260, " | PKR ");
            StringHelper::appendTextField(line, 260, balanceBuffer);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, unpaidBuffer);

            appendPagedListItem(line);
        }
    }

    startPagedListMode(PAGED_LIST_PATIENTS);
    setStatus("");
}

void AdminDash::setAppointmentsForView(Storage<Appointment> *appointments, Storage<Patient> *patients, Storage<Doctor> *doctors)
{
    int i;
    Appointment *sortedAppointments[100];
    int sortedCount;
    char line[260];
    char idBuffer[32];
    char namePreview[64];
    char doctorPreview[64];
    int len;

    clearPagedListItems();
    setPagedListHeader("View All Appointments", "ID | Patient Name | Doctor Name | Date | Time Slot | Status", "");

    sortedCount = 0;
    if (appointments != nullptr)
    {
        for (i = 0; i < appointments->size() && i < 100; i++)
        {
            sortedAppointments[sortedCount] = &appointments->getAll()[i];
            sortedCount++;
        }

        DataHelper::sortAppointmentPointersByDateDesc(sortedAppointments, sortedCount);

        for (i = 0; i < sortedCount; i++)
        {
            line[0] = '\0';
            ConversionHelper::intToString(sortedAppointments[i]->getID(), idBuffer);
            StringHelper::copyPreviewText(namePreview, 64, DataHelper::findPatientName(patients, sortedAppointments[i]->getPatientID()), 18);
            StringHelper::copyPreviewText(doctorPreview, 64, DataHelper::findDoctorName(doctors, sortedAppointments[i]->getDoctorID()), 18);

            StringHelper::appendTextField(line, 260, idBuffer);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, namePreview);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, doctorPreview);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, sortedAppointments[i]->getDate() != nullptr ? sortedAppointments[i]->getDate() : "");
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, sortedAppointments[i]->getTimeSlot() != nullptr ? sortedAppointments[i]->getTimeSlot() : "");
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, sortedAppointments[i]->getStatus() != nullptr ? sortedAppointments[i]->getStatus() : "");

            appendPagedListItem(line);
        }
    }

    startPagedListMode(PAGED_LIST_APPOINTMENTS);
    setStatus("");
}

void AdminDash::setUnpaidBillsForView(Storage<Bill> *bills, Storage<Patient> *patients)
{
    int i;
    char line[260];
    char idBuffer[32];
    char amountBuffer[32];
    char patientPreview[64];
    char dateBuffer[40];
    int len;

    clearPagedListItems();
    setPagedListHeader("View Unpaid Bills", "Bill ID | Patient Name | Amount (PKR) | Date", "");

    if (bills != nullptr)
    {
        for (i = 0; i < bills->size(); i++)
        {
            if (!StringHelper::textEquals(bills->getAll()[i].getStatus(), "unpaid"))
            {
                continue;
            }

            line[0] = '\0';
            ConversionHelper::intToString(bills->getAll()[i].getID(), idBuffer);
            ConversionHelper::doubleToString(bills->getAll()[i].getAmount(), amountBuffer);
            StringHelper::copyPreviewText(patientPreview, 64, DataHelper::findPatientName(patients, bills->getAll()[i].getPatientID()), 18);

            StringHelper::appendTextField(line, 260, idBuffer);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, patientPreview);
            StringHelper::appendTextField(line, 260, " | PKR ");
            StringHelper::appendTextField(line, 260, amountBuffer);
            StringHelper::appendTextField(line, 260, " | ");
            StringHelper::appendTextField(line, 260, bills->getAll()[i].getDate() != nullptr ? bills->getAll()[i].getDate() : "");

            if (TimeHelper::isBillOverdueByMoreThan7Days(bills->getAll()[i].getDate()))
            {
                StringHelper::appendTextField(line, 260, " [OVERDUE]");
            }

            appendPagedListItem(line);
        }
    }

    startPagedListMode(PAGED_LIST_UNPAID_BILLS);
    setStatus("");
}

void AdminDash::setSecurityLogForView()
{
    int loadedCount;

    clearPagedListItems();
    setPagedListHeader("View Security Log", "Timestamp | Role | Entered ID | Result", "");

    loadedCount = FileHandler::loadSecurityLogLines(&pagedListItems[0][0], PAGED_LIST_MAX_ITEMS, PAGED_LIST_MAX_LINE_LENGTH);
    pagedListTotalItems = loadedCount;

    if (pagedListTotalItems == 0)
    {
        appendPagedListItem("No security events logged.");
    }

    startPagedListMode(PAGED_LIST_SECURITY_LOG);
    setStatus("");
}

void AdminDash::setDailyReportForView(Storage<Appointment> *appointments, Storage<Bill> *bills, Storage<Patient> *patients, Storage<Doctor> *doctors)
{
    int i;
    int j;
    int totalAppointments;
    int pendingCount;
    int completedCount;
    int noShowCount;
    int cancelledCount;
    double revenueCollected;
    char todayDate[16];
    char line[260];
    char numberBuffer[32];
    char amountBuffer[32];
    char namePreview[64];
    bool hasOutstandingPatients;
    bool hasDoctorSummaryRows;

    clearPagedListItems();
    setPagedListHeader("Generate Daily Report", "Daily Report", "");
    TimeHelper::getTodayDate(todayDate, 16);

    totalAppointments = 0;
    pendingCount = 0;
    completedCount = 0;
    noShowCount = 0;
    cancelledCount = 0;
    revenueCollected = 0.0;

    if (appointments != nullptr)
    {
        for (i = 0; i < appointments->size(); i++)
        {
            if (!StringHelper::textEquals(appointments->getAll()[i].getDate(), todayDate))
            {
                continue;
            }

            totalAppointments++;
            if (StringHelper::textEquals(appointments->getAll()[i].getStatus(), "pending"))
            {
                pendingCount++;
            }
            else if (StringHelper::textEquals(appointments->getAll()[i].getStatus(), "completed"))
            {
                completedCount++;
            }
            else if (StringHelper::textEquals(appointments->getAll()[i].getStatus(), "no-show"))
            {
                noShowCount++;
            }
            else if (StringHelper::textEquals(appointments->getAll()[i].getStatus(), "cancelled"))
            {
                cancelledCount++;
            }
        }
    }

    if (bills != nullptr)
    {
        for (i = 0; i < bills->size(); i++)
        {
            if (StringHelper::textEquals(bills->getAll()[i].getDate(), todayDate) &&
                StringHelper::textEquals(bills->getAll()[i].getStatus(), "paid"))
            {
                revenueCollected = revenueCollected + bills->getAll()[i].getAmount();
            }
        }
    }

    line[0] = '\0';
    StringHelper::appendTextField(line, 260, "Date: ");
    StringHelper::appendTextField(line, 260, todayDate);
    appendPagedListItem(line);

    line[0] = '\0';
    StringHelper::appendTextField(line, 260, "Total appointments today: ");
    ConversionHelper::intToString(totalAppointments, numberBuffer);
    StringHelper::appendTextField(line, 260, numberBuffer);
    StringHelper::appendTextField(line, 260, " (Pending: ");
    ConversionHelper::intToString(pendingCount, numberBuffer);
    StringHelper::appendTextField(line, 260, numberBuffer);
    StringHelper::appendTextField(line, 260, " Completed: ");
    ConversionHelper::intToString(completedCount, numberBuffer);
    StringHelper::appendTextField(line, 260, numberBuffer);
    StringHelper::appendTextField(line, 260, " No-show: ");
    ConversionHelper::intToString(noShowCount, numberBuffer);
    StringHelper::appendTextField(line, 260, numberBuffer);
    StringHelper::appendTextField(line, 260, " Cancelled: ");
    ConversionHelper::intToString(cancelledCount, numberBuffer);
    StringHelper::appendTextField(line, 260, numberBuffer);
    StringHelper::appendTextField(line, 260, ")");
    appendPagedListItem(line);

    line[0] = '\0';
    ConversionHelper::doubleToString(revenueCollected, amountBuffer);
    StringHelper::appendTextField(line, 260, "Revenue collected today (paid bills): PKR ");
    StringHelper::appendTextField(line, 260, amountBuffer);
    appendPagedListItem(line);

    appendPagedListItem("");
    appendPagedListItem("Patients with outstanding unpaid bills:");
    appendPagedListItem("Patient Name | Total Owed");

    hasOutstandingPatients = false;
    if (patients != nullptr && bills != nullptr)
    {
        for (i = 0; i < patients->size(); i++)
        {
            double totalOwed;

            totalOwed = 0.0;
            for (j = 0; j < bills->size(); j++)
            {
                if (bills->getAll()[j].getPatientID() == patients->getAll()[i].getID() &&
                    StringHelper::textEquals(bills->getAll()[j].getStatus(), "unpaid"))
                {
                    totalOwed = totalOwed + bills->getAll()[j].getAmount();
                }
            }

            if (totalOwed > 0.0)
            {
                line[0] = '\0';
                StringHelper::copyPreviewText(namePreview, 64, patients->getAll()[i].getName(), 28);
                ConversionHelper::doubleToString(totalOwed, amountBuffer);
                StringHelper::appendTextField(line, 260, namePreview);
                StringHelper::appendTextField(line, 260, " | PKR ");
                StringHelper::appendTextField(line, 260, amountBuffer);
                appendPagedListItem(line);
                hasOutstandingPatients = true;
            }
        }
    }

    if (!hasOutstandingPatients)
    {
        appendPagedListItem("No patients with outstanding unpaid bills.");
    }

    appendPagedListItem("");
    appendPagedListItem("Doctor-wise summary for today:");
    appendPagedListItem("Doctor Name | Completed | Pending | No-show");

    hasDoctorSummaryRows = false;
    if (doctors != nullptr && appointments != nullptr)
    {
        for (i = 0; i < doctors->size(); i++)
        {
            int doctorCompleted;
            int doctorPending;
            int doctorNoShow;

            doctorCompleted = 0;
            doctorPending = 0;
            doctorNoShow = 0;

            for (j = 0; j < appointments->size(); j++)
            {
                if (appointments->getAll()[j].getDoctorID() != doctors->getAll()[i].getID() ||
                    !StringHelper::textEquals(appointments->getAll()[j].getDate(), todayDate))
                {
                    continue;
                }

                if (StringHelper::textEquals(appointments->getAll()[j].getStatus(), "completed"))
                {
                    doctorCompleted++;
                }
                else if (StringHelper::textEquals(appointments->getAll()[j].getStatus(), "pending"))
                {
                    doctorPending++;
                }
                else if (StringHelper::textEquals(appointments->getAll()[j].getStatus(), "no-show"))
                {
                    doctorNoShow++;
                }
            }

            if (doctorCompleted > 0 || doctorPending > 0 || doctorNoShow > 0)
            {
                line[0] = '\0';
                StringHelper::copyPreviewText(namePreview, 64, doctors->getAll()[i].getName(), 28);
                StringHelper::appendTextField(line, 260, namePreview);
                StringHelper::appendTextField(line, 260, " | ");
                ConversionHelper::intToString(doctorCompleted, numberBuffer);
                StringHelper::appendTextField(line, 260, numberBuffer);
                StringHelper::appendTextField(line, 260, " | ");
                ConversionHelper::intToString(doctorPending, numberBuffer);
                StringHelper::appendTextField(line, 260, numberBuffer);
                StringHelper::appendTextField(line, 260, " | ");
                ConversionHelper::intToString(doctorNoShow, numberBuffer);
                StringHelper::appendTextField(line, 260, numberBuffer);
                appendPagedListItem(line);
                hasDoctorSummaryRows = true;
            }
        }
    }

    if (!hasDoctorSummaryRows)
    {
        appendPagedListItem("No doctor activity today.");
    }

    startPagedListMode(PAGED_LIST_DAILY_REPORT);
    setStatus("");
}

void AdminDash::clearPagedListItems()
{
    int i;

    pagedListTotalItems = 0;
    pagedListCurrentPage = 0;
    for (i = 0; i < PAGED_LIST_MAX_ITEMS; i++)
    {
        pagedListItems[i][0] = '\0';
    }
}

void AdminDash::appendPagedListItem(const char *line)
{
    if (line == nullptr || pagedListTotalItems >= PAGED_LIST_MAX_ITEMS)
    {
        return;
    }

    StringHelper::stringCopy(pagedListItems[pagedListTotalItems], line, PAGED_LIST_MAX_LINE_LENGTH);
    pagedListTotalItems++;
}

int AdminDash::getPagedListTotalPages() const
{
    int pages;

    if (pagedListPageSize <= 0)
    {
        return 1;
    }

    pages = (pagedListTotalItems + pagedListPageSize - 1) / pagedListPageSize;
    if (pages < 1)
    {
        pages = 1;
    }
    return pages;
}

void AdminDash::updateRemoveDoctorVisiblePage()
{
    int i;
    int totalPages;
    int startIndex;
    int endIndex;
    int row;
    char pageText[64];
    char pageNumBuffer[16];
    char totalPagesBuffer[16];
    int len;

    removeDoctorCount = 0;
    for (i = 0; i < 30; i++)
    {
        if (removeDoctorListText[i] != nullptr)
        {
            removeDoctorListText[i]->setString("");
        }
    }

    totalPages = getPagedListTotalPages();
    if (pagedListCurrentPage < 0)
    {
        pagedListCurrentPage = 0;
    }
    if (pagedListCurrentPage > totalPages - 1)
    {
        pagedListCurrentPage = totalPages - 1;
    }

    startIndex = pagedListCurrentPage * pagedListPageSize;
    endIndex = startIndex + pagedListPageSize;
    if (endIndex > pagedListTotalItems)
    {
        endIndex = pagedListTotalItems;
    }

    row = 0;
    for (i = startIndex; i < endIndex && row < 30; i++)
    {
        if (removeDoctorListText[row] != nullptr)
        {
            removeDoctorListText[row]->setString(pagedListItems[i]);
        }
        row++;
        removeDoctorCount++;
    }

    pageText[0] = '\0';
    StringHelper::stringCopy(pageText, "Page ", 64);
    len = StringHelper::stringLength(pageText);
    ConversionHelper::intToString(pagedListCurrentPage + 1, pageNumBuffer);
    StringHelper::stringCopy(pageText + len, pageNumBuffer, 64 - len);
    len = StringHelper::stringLength(pageText);
    StringHelper::stringCopy(pageText + len, " / ", 64 - len);
    len = StringHelper::stringLength(pageText);
    ConversionHelper::intToString(totalPages, totalPagesBuffer);
    StringHelper::stringCopy(pageText + len, totalPagesBuffer, 64 - len);

    if (removeDoctorPageInfoText != nullptr)
    {
        removeDoctorPageInfoText->setString(pageText);
    }

    removeDoctorPrevBtn.setEnabled(pagedListCurrentPage > 0);
    removeDoctorNextBtn.setEnabled(pagedListCurrentPage < totalPages - 1);
}
