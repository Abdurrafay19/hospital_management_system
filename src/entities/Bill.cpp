#include "Bill.hpp"

#include "../core/Validator.hpp"
#include "../helpers/StringHelper.hpp"

Bill::Bill()
{
    billID = 0;
    patientID = 0;
    appointmentID = 0;
    amount = 0.0;
    status = nullptr;
    date = nullptr;
}

Bill::Bill(int newBillID,
           int newPatientID,
           int newAppointmentID,
           double newAmount,
           const char *newStatus,
           const char *newDate)
{
    billID = 0;
    patientID = 0;
    appointmentID = 0;
    amount = 0.0;
    status = nullptr;
    date = nullptr;

    setID(newBillID);
    setPatientID(newPatientID);
    setAppointmentID(newAppointmentID);
    setAmount(newAmount);
    setStatus(newStatus);
    setDate(newDate);
}

Bill::Bill(const Bill &other)
{
    billID = 0;
    patientID = 0;
    appointmentID = 0;
    amount = 0.0;
    status = nullptr;
    date = nullptr;

    billID = other.billID;
    patientID = other.patientID;
    appointmentID = other.appointmentID;
    amount = other.amount;
    StringHelper::copyTextDynamic(status, other.status);
    StringHelper::copyTextDynamic(date, other.date);
}

Bill::~Bill()
{
    delete[] status;
    delete[] date;

    status = nullptr;
    date = nullptr;
}

Bill &Bill::operator=(const Bill &other)
{
    if (this != &other)
    {
        billID = other.billID;
        patientID = other.patientID;
        appointmentID = other.appointmentID;
        amount = other.amount;
        StringHelper::copyTextDynamic(status, other.status);
        StringHelper::copyTextDynamic(date, other.date);
    }

    return *this;
}

int Bill::getID() const
{
    return billID;
}

int Bill::getPatientID() const
{
    return patientID;
}

int Bill::getAppointmentID() const
{
    return appointmentID;
}

double Bill::getAmount() const
{
    return amount;
}

const char *Bill::getStatus() const
{
    return status;
}

const char *Bill::getDate() const
{
    return date;
}

void Bill::setID(int newBillID)
{
    if (Validator::isValidID(newBillID))
    {
        billID = newBillID;
    }
}

void Bill::setPatientID(int newPatientID)
{
    if (Validator::isValidID(newPatientID))
    {
        patientID = newPatientID;
    }
}

void Bill::setAppointmentID(int newAppointmentID)
{
    if (Validator::isValidID(newAppointmentID))
    {
        appointmentID = newAppointmentID;
    }
}

void Bill::setAmount(double newAmount)
{
    if (newAmount >= 0.0)
    {
        amount = newAmount;
    }
}

void Bill::setStatus(const char *newStatus)
{
    StringHelper::copyTextDynamic(status, newStatus);
}

void Bill::setDate(const char *newDate)
{
    if (!Validator::isValidDate(newDate))
    {
        return;
    }

    StringHelper::copyTextDynamic(date, newDate);
}

bool Bill::isPaid() const
{
    return StringHelper::textEquals(status, "paid");
}

bool Bill::operator==(const Bill &other) const
{
    return billID == other.billID;
}
