#include "App.hpp"

#include <fstream>
#include <optional>
#include "../core/Validator.hpp"
#include "../core/FileHandler.hpp"
#include "../helpers/ConversionHelper.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/TimeHelper.hpp"

static bool pathExists(const char *path)
{
    std::ifstream fileStream(path, std::ios::binary);

    return fileStream.good();
}

static bool loadFontWithFallback(sf::Font &font, const char *rootPath, const char *buildPath)
{
    if (pathExists(buildPath) && font.openFromFile(buildPath))
    {
        return true;
    }

    if (pathExists(rootPath) && font.openFromFile(rootPath))
    {
        return true;
    }

    return false;
}

static int compareText(const char *left, const char *right)
{
    int index;
    char leftChar;
    char rightChar;

    index = 0;
    while (left != nullptr && right != nullptr)
    {
        leftChar = left[index];
        rightChar = right[index];

        if (leftChar == '\0' && rightChar == '\0')
        {
            return 0;
        }
        if (leftChar == '\0')
        {
            return -1;
        }
        if (rightChar == '\0')
        {
            return 1;
        }
        if (leftChar < rightChar)
        {
            return -1;
        }
        if (leftChar > rightChar)
        {
            return 1;
        }

        index++;
    }

    if (left == nullptr && right == nullptr)
    {
        return 0;
    }
    if (left == nullptr)
    {
        return -1;
    }

    return 1;
}

static int parseDateComponent(const char *dateText, int startIndex, int endMarker)
{
    int value;
    int index;

    value = 0;
    index = startIndex;
    while (dateText != nullptr && dateText[index] != '\0' && dateText[index] != endMarker)
    {
        if (dateText[index] >= '0' && dateText[index] <= '9')
        {
            value = value * 10 + (dateText[index] - '0');
        }
        index++;
    }

    return value;
}

static void parseDateText(const char *dateText, int &day, int &month, int &year)
{
    int index;

    day = 0;
    month = 0;
    year = 0;

    if (dateText == nullptr)
    {
        return;
    }

    day = parseDateComponent(dateText, 0, '-');

    index = 0;
    while (dateText[index] != '\0' && dateText[index] != '-')
    {
        index++;
    }
    if (dateText[index] == '-')
    {
        index++;
    }

    month = parseDateComponent(dateText, index, '-');

    while (dateText[index] != '\0' && dateText[index] != '-')
    {
        index++;
    }
    if (dateText[index] == '-')
    {
        index++;
    }

    year = parseDateComponent(dateText, index, '\0');
}

static int compareAppointmentsByDateTime(const Appointment &left, const Appointment &right)
{
    int leftDay;
    int leftMonth;
    int leftYear;
    int rightDay;
    int rightMonth;
    int rightYear;
    int result;

    parseDateText(left.getDate(), leftDay, leftMonth, leftYear);
    parseDateText(right.getDate(), rightDay, rightMonth, rightYear);

    if (leftYear < rightYear)
    {
        return -1;
    }
    if (leftYear > rightYear)
    {
        return 1;
    }

    if (leftMonth < rightMonth)
    {
        return -1;
    }
    if (leftMonth > rightMonth)
    {
        return 1;
    }

    if (leftDay < rightDay)
    {
        return -1;
    }
    if (leftDay > rightDay)
    {
        return 1;
    }

    result = compareText(left.getTimeSlot(), right.getTimeSlot());
    return result;
}

static void sortAppointmentsByDate(Storage<Appointment> &appointments)
{
    Appointment *appointmentArray;
    int count;
    int pass;
    int index;
    Appointment temp;

    count = appointments.size();
    appointmentArray = appointments.getAll();

    for (pass = 0; pass < count - 1; pass++)
    {
        for (index = 0; index < count - 1 - pass; index++)
        {
            if (compareAppointmentsByDateTime(appointmentArray[index], appointmentArray[index + 1]) > 0)
            {
                temp = appointmentArray[index];
                appointmentArray[index] = appointmentArray[index + 1];
                appointmentArray[index + 1] = temp;
            }
        }
    }
}

static int comparePrescriptionsByDateDesc(const Prescription &left, const Prescription &right)
{
    int leftDay;
    int leftMonth;
    int leftYear;
    int rightDay;
    int rightMonth;
    int rightYear;

    parseDateText(left.getDate(), leftDay, leftMonth, leftYear);
    parseDateText(right.getDate(), rightDay, rightMonth, rightYear);

    if (leftYear > rightYear)
    {
        return -1;
    }
    if (leftYear < rightYear)
    {
        return 1;
    }

    if (leftMonth > rightMonth)
    {
        return -1;
    }
    if (leftMonth < rightMonth)
    {
        return 1;
    }

    if (leftDay > rightDay)
    {
        return -1;
    }
    if (leftDay < rightDay)
    {
        return 1;
    }

    return 0;
}

static void sortPrescriptionsByDateDesc(Storage<Prescription> &prescriptions)
{
    Prescription *prescriptionArray;
    int count;
    int pass;
    int index;
    Prescription temp;

    count = prescriptions.size();
    prescriptionArray = prescriptions.getAll();

    for (pass = 0; pass < count - 1; pass++)
    {
        for (index = 0; index < count - 1 - pass; index++)
        {
            if (comparePrescriptionsByDateDesc(prescriptionArray[index], prescriptionArray[index + 1]) > 0)
            {
                temp = prescriptionArray[index];
                prescriptionArray[index] = prescriptionArray[index + 1];
                prescriptionArray[index + 1] = temp;
            }
        }
    }
}

static Storage<Appointment> *collectTodaysDoctorAppointments(HospitalSystem &system, int doctorID, const char *todayDate, bool pendingOnly)
{
    Storage<Appointment> *result;
    Appointment *appointmentList;
    int i;

    result = new Storage<Appointment>();
    appointmentList = system.getAppointments().getAll();

    for (i = 0; i < system.getAppointments().size(); i++)
    {
        if (appointmentList[i].getDoctorID() != doctorID)
        {
            continue;
        }

        if (!StringHelper::textEquals(appointmentList[i].getDate(), todayDate))
        {
            continue;
        }

        if (pendingOnly && !StringHelper::textEquals(appointmentList[i].getStatus(), "pending"))
        {
            continue;
        }

        result->add(appointmentList[i]);
    }

    appointmentList = result->getAll();
    for (i = 0; i < result->size() - 1; i++)
    {
        int j;
        for (j = 0; j < result->size() - 1 - i; j++)
        {
            if (TimeHelper::compareTimeSlotsAscending(appointmentList[j].getTimeSlot(), appointmentList[j + 1].getTimeSlot()) > 0)
            {
                Appointment temp;
                temp = appointmentList[j];
                appointmentList[j] = appointmentList[j + 1];
                appointmentList[j + 1] = temp;
            }
        }
    }

    return result;
}

static Storage<Bill> *collectPatientBills(HospitalSystem &system, int patientID, bool unpaidOnly)
{
    Storage<Bill> *result;
    Bill *billList;
    int i;

    result = new Storage<Bill>();
    billList = system.getBills().getAll();

    for (i = 0; i < system.getBills().size(); i++)
    {
        if (billList[i].getPatientID() != patientID)
        {
            continue;
        }

        if (unpaidOnly && (StringHelper::textEquals(billList[i].getStatus(), "paid") || StringHelper::textEquals(billList[i].getStatus(), "cancelled")))
        {
            continue;
        }

        result->add(billList[i]);
    }

    return result;
}

static bool prescriptionExistsForAppointment(Storage<Prescription> &prescriptions, int appointmentID)
{
    Prescription *prescriptionList;
    int i;

    prescriptionList = prescriptions.getAll();

    for (i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptionList[i].getAppointmentID() == appointmentID)
        {
            return true;
        }
    }

    return false;
}

static int getNextPrescriptionID(Storage<Prescription> &prescriptions)
{
    int i;
    int maxID;

    maxID = 0;
    for (i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptions.getAll()[i].getPrescriptionID() > maxID)
        {
            maxID = prescriptions.getAll()[i].getPrescriptionID();
        }
    }

    return maxID + 1;
}

static void truncateText(char *destination, const char *source, int maxLength)
{
    StringHelper::stringCopy(destination, source, maxLength);
}

void App::setupUI()
{
    logoutButton = UIButton(regularFont, "Logout", sf::Vector2f(1100.f, 30.f), sf::Vector2f(130.f, 40.f));

    logoutButton.setFillColor(sf::Color(230, 80, 80));

    logoutButton.setOutlineColor(sf::Color(230, 80, 80));
    logoutButton.setTextColor(sf::Color::White);

    loginScreen.initialize(regularFont, boldFont);
    patientDash.initialize(regularFont, boldFont);
    doctorDash.initialize(regularFont, boldFont);
}

void App::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (event->is<sf::Event::MouseButtonPressed>())
        {
            handleMouseClick();
        }

        if (const sf::Event::TextEntered *textEvent = event->getIf<sf::Event::TextEntered>())
        {
            handleTextEntered(textEvent->unicode);
        }
    }
}

void App::handleMouseClick()
{
    if (state == LOGIN)
    {
        loginScreen.handleMouseClick(window);
        if (loginScreen.consumeLoginRequest())
        {
            attemptLogin();
        }
        if (loginScreen.consumeSignupRequest())
        {
            attemptSignup();
        }
    }
    else
    {
        sf::Vector2f mouseWorldPosition;

        mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (logoutButton.getShape().getGlobalBounds().contains(mouseWorldPosition))
        {
            logout();
            return;
        }

        if (state == PATIENT_MENU)
        {
            patientDash.handleMouseClick(window);

            if (patientDash.consumeSpecializationSearchRequest())
            {
                try
                {
                    Storage<Doctor> *foundDoctors;
                    foundDoctors = system.getDoctorsBySpecialization(patientDash.getSpecializationText());

                    if (foundDoctors == nullptr || foundDoctors->size() == 0)
                    {
                        patientDash.setDialogStatus("No doctors available for that specialization.");
                        if (foundDoctors != nullptr)
                        {
                            delete foundDoctors;
                        }
                    }
                    else
                    {
                        patientDash.setFilteredDoctors(foundDoctors);
                        patientDash.advanceBookingStep();
                    }
                }
                catch (const HospitalException &exception)
                {
                    patientDash.setDialogStatus(exception.what());
                }
            }

            if (patientDash.isCancelAppointmentClicked())
            {
                Patient *patient;
                Storage<Appointment> *pendingAppointments;
                Appointment *appointmentList;
                int i;

                patient = reinterpret_cast<Patient *>(currentUser);
                pendingAppointments = new Storage<Appointment>();
                appointmentList = system.getAppointments().getAll();

                for (i = 0; i < system.getAppointments().size(); i++)
                {
                    if (appointmentList[i].getPatientID() == patient->getID() && StringHelper::textEquals(appointmentList[i].getStatus(), "pending"))
                    {
                        pendingAppointments->add(appointmentList[i]);
                    }
                }

                if (pendingAppointments->size() == 0)
                {
                    delete pendingAppointments;
                    patientDash.setStatus("You have no pending appointments.");
                }
                else
                {
                    patientDash.setPendingAppointments(pendingAppointments, &system.getDoctors());
                    patientDash.startCancelAppointmentMode();
                }
            }

            if (patientDash.isViewAppointmentsClicked())
            {
                Patient *patient;
                Storage<Appointment> *patientAppointments;
                Appointment *appointmentList;
                int i;

                patient = reinterpret_cast<Patient *>(currentUser);
                patientAppointments = new Storage<Appointment>();
                appointmentList = system.getAppointments().getAll();

                for (i = 0; i < system.getAppointments().size(); i++)
                {
                    if (appointmentList[i].getPatientID() == patient->getID())
                    {
                        patientAppointments->add(appointmentList[i]);
                    }
                }

                if (patientAppointments->size() == 0)
                {
                    delete patientAppointments;
                    patientDash.setStatus("No appointments found.");
                }
                else
                {
                    sortAppointmentsByDate(*patientAppointments);
                    patientDash.setViewedAppointments(patientAppointments, &system.getDoctors());
                    patientDash.startViewAppointmentsMode();
                }
            }

            if (patientDash.isViewMedicalRecordsClicked())
            {
                Patient *patient;
                Storage<Prescription> *patientRecords;
                Prescription *recordList;
                int i;

                patient = reinterpret_cast<Patient *>(currentUser);
                patientRecords = new Storage<Prescription>();
                recordList = system.getPrescriptions().getAll();

                for (i = 0; i < system.getPrescriptions().size(); i++)
                {
                    if (recordList[i].getPatientID() == patient->getID())
                    {
                        patientRecords->add(recordList[i]);
                    }
                }

                if (patientRecords->size() == 0)
                {
                    delete patientRecords;
                    patientDash.setStatus("No medical records found.");
                }
                else
                {
                    sortPrescriptionsByDateDesc(*patientRecords);
                    patientDash.setViewedMedicalRecords(patientRecords, &system.getDoctors());
                    patientDash.startViewMedicalRecordsMode();
                }
            }

            if (patientDash.isViewBillsClicked())
            {
                Patient *patient;
                Storage<Bill> *patientBills;

                patient = reinterpret_cast<Patient *>(currentUser);
                patientBills = collectPatientBills(system, patient->getID(), false);

                if (patientBills->size() == 0)
                {
                    delete patientBills;
                    patientDash.setStatus("No bills found.");
                }
                else
                {
                    patientDash.setViewedBills(patientBills);
                    patientDash.startViewBillsMode();
                }
            }

            if (patientDash.isTopUpBalanceClicked())
            {
                patientDash.startTopUpMode();
            }

            if (patientDash.isPayBillClicked())
            {
                Patient *patient;
                Storage<Bill> *unpaidBills;

                patient = reinterpret_cast<Patient *>(currentUser);
                unpaidBills = collectPatientBills(system, patient->getID(), true);

                if (unpaidBills->size() == 0)
                {
                    delete unpaidBills;
                    patientDash.setStatus("No unpaid bills.");
                }
                else
                {
                    patientDash.setViewedBills(unpaidBills);
                    patientDash.startPayBillMode();
                }
            }

            if (patientDash.consumeCancelAppointmentRequest())
            {
                Patient *patient;
                int appointmentID;
                double refundedFee;
                char feeBuffer[32];
                char successMessage[200];
                int messageLength;

                patient = reinterpret_cast<Patient *>(currentUser);
                appointmentID = ConversionHelper::toInt(patientDash.getCancelAppointmentIDText());

                try
                {
                    refundedFee = system.cancelAppointment(patient, appointmentID);
                    patientDash.closeCancelAppointmentMode();
                    patientDash.setPatient(patient);
                    patientDash.setAllAppointments(&system.getAppointments());

                    successMessage[0] = '\0';
                    StringHelper::stringCopy(successMessage, "Appointment cancelled. PKR ", 200);
                    messageLength = StringHelper::stringLength(successMessage);
                    ConversionHelper::doubleToString(refundedFee, feeBuffer);
                    StringHelper::stringCopy(successMessage + messageLength, feeBuffer, 200 - messageLength);
                    messageLength = StringHelper::stringLength(successMessage);
                    StringHelper::stringCopy(successMessage + messageLength, " refunded to your balance.", 200 - messageLength);
                    patientDash.setStatus(successMessage);
                }
                catch (const HospitalException &exception)
                {
                    patientDash.closeCancelAppointmentMode();
                    patientDash.setStatus(exception.what());
                }
            }

            if (patientDash.consumePayBillRequest())
            {
                Patient *patient;
                int billID;
                char balanceBuffer[64];
                char successMessage[200];
                int msgLen;
                const char *billText;

                patient = reinterpret_cast<Patient *>(currentUser);
                billText = patientDash.getPayBillIDText();

                billID = ConversionHelper::toInt(billText);

                try
                {
                    system.payBill(patient, billID);
                    patientDash.closePayBillMode();
                    patientDash.setPatient(patient);
                    patientDash.setAllAppointments(&system.getAppointments());

                    successMessage[0] = '\0';
                    StringHelper::stringCopy(successMessage, "Bill paid successfully. Remaining balance: PKR ", 200);
                    msgLen = StringHelper::stringLength(successMessage);
                    ConversionHelper::doubleToString(patient->getBalance(), balanceBuffer);
                    StringHelper::stringCopy(successMessage + msgLen, balanceBuffer, 200 - msgLen);
                    patientDash.setStatus(successMessage);
                }
                catch (const InsufficientFundsException &ex)
                {
                    patientDash.closePayBillMode();
                    patientDash.setStatus(ex.what());
                }
                catch (const HospitalException &ex)
                {
                    patientDash.closePayBillMode();
                    patientDash.setStatus(ex.what());
                }
            }

            if (patientDash.consumeTopUpRequest())
            {
                Patient *patient;
                const char *amtText;
                double amount;
                char buf[128];
                char balStr[64];
                int len;

                patient = reinterpret_cast<Patient *>(currentUser);
                amtText = patientDash.getTopUpAmountText();

                try
                {
                    amount = ConversionHelper::stringToDouble(amtText);

                    system.topUpBalance(patient, amount);

                    buf[0] = '\0';
                    StringHelper::stringCopy(buf, "Balance updated. New balance: PKR ", 128);
                    ConversionHelper::doubleToString(patient->getBalance(), balStr);
                    len = StringHelper::stringLength(buf);
                    StringHelper::stringCopy(buf + len, balStr, 128 - len);

                    patientDash.closeTopUpMode();
                    patientDash.setPatient(patient);
                    patientDash.setAllAppointments(&system.getAppointments());
                    patientDash.setStatus(buf);
                }
                catch (const InvalidInputException &ex)
                {
                    patientDash.incrementTopUpAttempts();
                    if (patientDash.getTopUpAttempts() >= 3)
                    {
                        patientDash.closeTopUpMode();
                        patientDash.setStatus("Top up cancelled after 3 attempts.");
                    }
                    else
                    {
                        patientDash.setStatus(ex.what());
                    }
                }
                catch (const HospitalException &ex)
                {
                    patientDash.closeTopUpMode();
                    patientDash.setStatus(ex.what());
                }
            }

            if (patientDash.consumeBookAppointmentRequest())
            {
                Patient *patient;
                int doctorID;

                patient = reinterpret_cast<Patient *>(currentUser);
                doctorID = patientDash.getSelectedDoctorID();

                try
                {
                    if (doctorID < 1)
                    {
                        patientDash.setDialogStatus("Doctor ID is invalid.");
                    }
                    else if (StringHelper::stringLength(patientDash.getBookingDateText()) < 1)
                    {
                        patientDash.setDialogStatus("Date is required.");
                    }
                    else if (StringHelper::stringLength(patientDash.getBookingTimeText()) < 1)
                    {
                        patientDash.setDialogStatus("Time slot is required.");
                    }
                    else
                    {
                        system.bookAppointment(
                            patient,
                            doctorID,
                            patientDash.getBookingDateText(),
                            patientDash.getBookingTimeText());
                        patientDash.setDialogStatus("Appointment booked successfully!");
                        patientDash.cancelBookingMode();
                        patientDash.setPatient(patient);
                        patientDash.setAllAppointments(&system.getAppointments());
                    }
                }
                catch (const HospitalException &exception)
                {
                    patientDash.setDialogStatus(exception.what());
                }
            }

            patientDash.clearClickStates();
        }
        else if (state == DOCTOR_MENU)
        {
            doctorDash.handleMouseClick(window);

            if (doctorDash.consumeViewTodayAppointmentsRequest())
            {
                Doctor *doctor;
                Storage<Appointment> *todayAppointments;
                char todayDate[11];

                doctor = reinterpret_cast<Doctor *>(currentUser);
                TimeHelper::getTodayDate(todayDate, 11);
                todayAppointments = collectTodaysDoctorAppointments(system, doctor->getID(), todayDate, false);

                if (todayAppointments->size() == 0)
                {
                    delete todayAppointments;
                    doctorDash.closeTodayAppointmentsMode();
                    doctorDash.setStatus("No appointments scheduled for today.");
                }
                else
                {
                    doctorDash.setTodayAppointments(todayAppointments, &system.getPatients());
                    doctorDash.startTodayAppointmentsMode();
                }
            }

            if (doctorDash.consumeMarkAppointmentCompleteRequest())
            {
                Doctor *doctor;
                Storage<Appointment> *pendingAppointments;
                char todayDate[11];

                doctor = reinterpret_cast<Doctor *>(currentUser);
                TimeHelper::getTodayDate(todayDate, 11);
                pendingAppointments = collectTodaysDoctorAppointments(system, doctor->getID(), todayDate, true);

                if (pendingAppointments->size() == 0)
                {
                    delete pendingAppointments;
                    doctorDash.closeMarkCompleteMode();
                    doctorDash.setStatus("No pending appointments scheduled for today.");
                }
                else
                {
                    doctorDash.setTodayAppointments(pendingAppointments, &system.getPatients());
                    doctorDash.startMarkCompleteMode();
                }
            }

            if (doctorDash.consumeMarkAppointmentNoShowRequest())
            {
                Doctor *doctor;
                Storage<Appointment> *pendingAppointments;
                char todayDate[11];

                doctor = reinterpret_cast<Doctor *>(currentUser);
                TimeHelper::getTodayDate(todayDate, 11);
                pendingAppointments = collectTodaysDoctorAppointments(system, doctor->getID(), todayDate, true);

                if (pendingAppointments->size() == 0)
                {
                    delete pendingAppointments;
                    doctorDash.closeMarkNoShowMode();
                    doctorDash.setStatus("No pending appointments scheduled for today.");
                }
                else
                {
                    doctorDash.setTodayAppointments(pendingAppointments, &system.getPatients());
                    doctorDash.startMarkNoShowMode();
                }
            }

            if (doctorDash.consumeWritePrescriptionRequest())
            {
                doctorDash.startWritePrescriptionMode();
            }

            if (doctorDash.consumeMarkAppointmentCompleteSubmitRequest())
            {
                Doctor *doctor;
                Appointment *appointment;
                int appointmentID;
                char todayDate[11];
                char successMessage[200];

                doctor = reinterpret_cast<Doctor *>(currentUser);
                appointmentID = ConversionHelper::toInt(doctorDash.getMarkCompleteAppointmentIDText());
                TimeHelper::getTodayDate(todayDate, 11);

                appointment = system.getAppointments().findByID(appointmentID);
                if (appointment == nullptr)
                {
                    doctorDash.setStatus("Invalid appointment ID.");
                }
                else if (appointment->getDoctorID() != doctor->getID())
                {
                    doctorDash.setStatus("Invalid appointment ID.");
                }
                else if (!StringHelper::textEquals(appointment->getStatus(), "pending"))
                {
                    doctorDash.setStatus("Appointment must be pending.");
                }
                else if (!StringHelper::textEquals(appointment->getDate(), todayDate))
                {
                    doctorDash.setStatus("Appointment must be dated today.");
                }
                else
                {
                    appointment->setStatus("completed");
                    FileHandler::saveAllAppointments(system.getAppointments());
                    doctorDash.closeMarkCompleteMode();
                    successMessage[0] = '\0';
                    StringHelper::stringCopy(successMessage, "Appointment marked as completed.", 200);
                    doctorDash.setStatus(successMessage);
                }
            }

            if (doctorDash.consumeWritePrescriptionSubmitRequest())
            {
                Doctor *doctor;
                Appointment *appointment;
                Prescription prescription;
                int appointmentID;
                int prescriptionID;
                char todayDate[11];

                doctor = reinterpret_cast<Doctor *>(currentUser);
                appointmentID = ConversionHelper::toInt(doctorDash.getWritePrescriptionAppointmentIDText());
                TimeHelper::getTodayDate(todayDate, 11);

                appointment = system.getAppointments().findByID(appointmentID);
                if (appointment == nullptr)
                {
                    doctorDash.setStatus("Invalid appointment ID.");
                }
                else if (appointment->getDoctorID() != doctor->getID())
                {
                    doctorDash.setStatus("Invalid appointment ID.");
                }
                else if (!StringHelper::textEquals(appointment->getStatus(), "completed"))
                {
                    doctorDash.setStatus("Appointment must be completed.");
                }
                else if (prescriptionExistsForAppointment(system.getPrescriptions(), appointmentID))
                {
                    doctorDash.closeWritePrescriptionMode();
                    doctorDash.setStatus("Prescription already written for this appointment.");
                }
                else
                {
                    prescriptionID = getNextPrescriptionID(system.getPrescriptions());
                    prescription = Prescription(
                        prescriptionID,
                        appointmentID,
                        appointment->getPatientID(),
                        doctor->getID(),
                        todayDate,
                        doctorDash.getWritePrescriptionMedicinesText(),
                        doctorDash.getWritePrescriptionNotesText());

                    FileHandler::savePrescription(prescription, true);
                    system.getPrescriptions().add(prescription);
                    doctorDash.closeWritePrescriptionMode();
                    doctorDash.setStatus("Prescription saved.");
                }
            }

            if (doctorDash.consumeMarkAppointmentNoShowSubmitRequest())
            {
                Doctor *doctor;
                Appointment *appointment;
                Bill *bill;
                int appointmentID;
                char todayDate[11];
                char successMessage[200];

                doctor = reinterpret_cast<Doctor *>(currentUser);
                appointmentID = ConversionHelper::toInt(doctorDash.getMarkNoShowAppointmentIDText());
                TimeHelper::getTodayDate(todayDate, 11);

                appointment = system.getAppointments().findByID(appointmentID);
                if (appointment == nullptr)
                {
                    doctorDash.setStatus("Invalid appointment ID.");
                }
                else if (appointment->getDoctorID() != doctor->getID())
                {
                    doctorDash.setStatus("Invalid appointment ID.");
                }
                else if (!StringHelper::textEquals(appointment->getStatus(), "pending"))
                {
                    doctorDash.setStatus("Appointment must be pending.");
                }
                else if (!StringHelper::textEquals(appointment->getDate(), todayDate))
                {
                    doctorDash.setStatus("Appointment must be dated today.");
                }
                else
                {
                    bill = nullptr;
                    for (int i = 0; i < system.getBills().size(); i++)
                    {
                        if (system.getBills().getAll()[i].getPatientID() == appointment->getPatientID() && system.getBills().getAll()[i].getAppointmentID() == appointmentID)
                        {
                            bill = &system.getBills().getAll()[i];
                            break;
                        }
                    }

                    if (bill == nullptr)
                    {
                        doctorDash.setStatus("Invalid appointment ID.");
                    }
                    else
                    {
                        appointment->setStatus("no-show");
                        bill->setStatus("cancelled");
                        FileHandler::saveAllAppointments(system.getAppointments());
                        FileHandler::saveAllBills(system.getBills());
                        doctorDash.closeMarkNoShowMode();
                        successMessage[0] = '\0';
                        StringHelper::stringCopy(successMessage, "Appointment marked as no-show.", 200);
                        doctorDash.setStatus(successMessage);
                    }
                }
            }

            if (doctorDash.consumeViewPatientHistoryRequest())
            {
                Doctor *doctor;

                doctor = reinterpret_cast<Doctor *>(currentUser);
                doctorDash.setPatientListForMedicalHistory(&system.getPatients(), &system.getAppointments());
                doctorDash.startViewMedicalHistoryMode();
            }

            if (doctorDash.consumeViewMedicalHistorySubmitRequest())
            {
                Doctor *doctor;
                Patient *patient;
                int patientID;
                int i;
                bool hasCompletedAppointment;
                Appointment *appointmentArray;
                const char *inputText;

                doctor = reinterpret_cast<Doctor *>(currentUser);
                inputText = doctorDash.getViewMedicalHistoryPatientIDText();

                if (inputText == nullptr || inputText[0] == '\0')
                {
                    doctorDash.setStatus("Please enter a Patient ID.");
                }
                else
                {
                    patientID = ConversionHelper::toInt(inputText);
                    patient = system.getPatients().findByID(patientID);

                    if (patient == nullptr)
                    {
                        doctorDash.setStatus("Access denied. You can only view records of your own patients.");
                    }
                    else
                    {
                        hasCompletedAppointment = false;
                        appointmentArray = system.getAppointments().getAll();

                        for (i = 0; i < system.getAppointments().size(); i++)
                        {
                            if (appointmentArray[i].getPatientID() == patientID &&
                                appointmentArray[i].getDoctorID() == doctor->getID() &&
                                StringHelper::textEquals(appointmentArray[i].getStatus(), "completed"))
                            {
                                hasCompletedAppointment = true;
                                break;
                            }
                        }

                        if (!hasCompletedAppointment)
                        {
                            doctorDash.setStatus("Access denied. You can only view records of your own patients.");
                        }
                        else
                        {
                            doctorDash.setPrescriptionsForPatient(&system.getPrescriptions(), patientID, doctor->getID());
                            doctorDash.displayPrescriptionsForPatient();
                        }
                    }
                }
            }
        }
    }
}

void App::handleTextEntered(char32_t unicode)
{
    if (state != LOGIN)
    {
        if (state == PATIENT_MENU)
        {
            patientDash.handleTextEntered(unicode);
        }
        else if (state == DOCTOR_MENU)
        {
            doctorDash.handleTextEntered(unicode);
        }
        return;
    }

    loginScreen.handleTextEntered(unicode);
}

void App::attemptLogin()
{
    Person *user;
    Role selectedRole;

    selectedRole = loginScreen.getSelectedRole();
    user = system.login(loginScreen.getEnteredName(), loginScreen.getEnteredPassword(), "", selectedRole);

    if (user == nullptr)
    {
        loginScreen.setStatus("Login failed. Check ID or password.");
        return;
    }

    currentUser = user;
    if (selectedRole == ROLE_PATIENT)
    {
        state = PATIENT_MENU;
        patientDash.setPatient(reinterpret_cast<Patient *>(user));
        patientDash.setAllAppointments(&system.getAppointments());
        loginScreen.setStatus("Login successful. Welcome, patient.");
    }
    else if (selectedRole == ROLE_DOCTOR)
    {
        state = DOCTOR_MENU;
        doctorDash.setDoctor(reinterpret_cast<Doctor *>(user));
        doctorDash.closeTodayAppointmentsMode();
        doctorDash.closeMarkCompleteMode();
        doctorDash.closeMarkNoShowMode();
        doctorDash.closeWritePrescriptionMode();
        doctorDash.closeViewMedicalHistoryMode();
        loginScreen.setStatus("Login successful. Welcome, doctor.");
    }
    else
    {
        state = ADMIN_MENU;
        loginScreen.setStatus("Login successful. Welcome, admin.");
    }
}

void App::attemptSignup()
{
    const char *name;
    int age;
    const char *gender;
    const char *contact;
    const char *password;
    int newID;
    Patient newPatient;
    char successMsg[200];
    int i;

    name = loginScreen.getEnteredName();
    age = loginScreen.getEnteredAge();
    gender = loginScreen.getEnteredGender();
    contact = loginScreen.getEnteredContact();
    password = loginScreen.getEnteredSignupPassword();

    // Validate inputs
    if (StringHelper::stringLength(name) < 2)
    {
        loginScreen.setStatus("Name must be at least 2 characters");
        return;
    }
    if (age < 18 || age > 120)
    {
        loginScreen.setStatus("Age must be between 18 and 120");
        return;
    }
    if (StringHelper::stringLength(gender) < 1)
    {
        loginScreen.setStatus("Gender cannot be empty");
        return;
    }
    if (!Validator::isValidContact(contact))
    {
        loginScreen.setStatus("Contact must be 11 digits");
        return;
    }
    if (!Validator::isValidPassword(password))
    {
        loginScreen.setStatus("Password must be at least 6 characters");
        return;
    }

    // Generate new patient ID
    newID = system.getNextPatientID();

    // Create new patient with initial balance of 0
    newPatient = Patient(newID, name, password, age, gender, contact, 0.0);

    // Save to file
    FileHandler::savePatient(newPatient, true);

    // Add to system's patient storage
    system.getPatients().add(newPatient);

    // Show success message with new patient ID
    successMsg[0] = '\0';
    StringHelper::stringCopy(successMsg, "New account created with ID: ", 200);
    i = StringHelper::stringLength(successMsg);
    ConversionHelper::intToString(newID, successMsg + i);

    loginScreen.setSignupMode(false);
    loginScreen.clearInputs();
    loginScreen.setStatus(successMsg);
}

void App::logout()
{
    currentUser = nullptr;
    state = LOGIN;
    loginScreen.clearInputs();
    loginScreen.setStatus("Logged out.");
    patientDash.setPatient(nullptr);
    doctorDash.closeTodayAppointmentsMode();
    doctorDash.closeMarkCompleteMode();
    doctorDash.closeMarkNoShowMode();
    doctorDash.closeWritePrescriptionMode();
    doctorDash.closeViewMedicalHistoryMode();
}

void App::drawDashboard()
{
    if (state == PATIENT_MENU)
    {
        patientDash.draw(window);
    }
    else if (state == DOCTOR_MENU)
    {
        doctorDash.draw(window);
    }
    else
    {
        sf::Text title(boldFont, "", 30);
        title.setString("Admin Dashboard");
        title.setPosition(sf::Vector2f(80.f, 34.f));
        title.setFillColor(sf::Color(44, 62, 80));
        window.draw(title);
    }

    logoutButton.draw(window);
}

App::App()
    : window(sf::VideoMode({1280, 720}), "MediCore")
{
    fontLoaded = false;
    state = LOGIN;
    currentUser = nullptr;

    fontLoaded = loadFontWithFallback(regularFont,
                                      "assets/fonts/font.ttf",
                                      "../../../assets/fonts/font.ttf");

    if (fontLoaded)
    {
        fontLoaded = loadFontWithFallback(boldFont,
                                          "assets/fonts/font-bold.ttf",
                                          "../../../assets/fonts/font-bold.ttf");
    }

    if (fontLoaded)
    {
        setupUI();
    }
}

App::~App()
{
}

void App::run()
{
    while (window.isOpen())
    {
        processEvents();

        window.clear(sf::Color(245, 247, 248));

        if (!fontLoaded)
        {
            window.display();
            continue;
        }

        if (state == LOGIN)
        {
            loginScreen.draw(window);
        }
        else
        {
            drawDashboard();
        }

        window.display();
    }
}
