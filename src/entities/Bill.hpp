#pragma once

#include <iostream>

class Bill
{
private:
    int billID;
    int patientID;
    int appointmentID;
    double amount;
    char *status;
    char *date;

public:
    Bill();
    Bill(int newBillID,
         int newPatientID,
         int newAppointmentID,
         double newAmount,
         const char *newStatus,
         const char *newDate);
    Bill(const Bill &other);
    ~Bill();

    Bill &operator=(const Bill &other);

    int getID() const;
    int getPatientID() const;
    int getAppointmentID() const;
    double getAmount() const;
    const char *getStatus() const;
    const char *getDate() const;

    void setID(int newBillID);
    void setPatientID(int newPatientID);
    void setAppointmentID(int newAppointmentID);
    void setAmount(double newAmount);
    void setStatus(const char *newStatus);
    void setDate(const char *newDate);

    bool isPaid() const;
    bool operator==(const Bill &other) const;
};
