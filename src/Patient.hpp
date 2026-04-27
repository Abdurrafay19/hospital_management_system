#pragma once

#include <iostream>

#include "Person.hpp"

class Patient : public Person {
private:
    int age;
    char* gender;
    char* contact;
    double balance;

public:
    Patient();
    Patient(int patientID,
            const char* patientName,
            const char* patientPassword,
            int patientAge,
            const char* patientGender,
            const char* patientContact,
            double patientBalance);
    Patient(const Patient& other);
    ~Patient();

    Patient& operator=(const Patient& other);

    void displayDashboard();
    void showProfile() const;

    int getAge() const;
    const char* getGender() const;
    const char* getContact() const;
    double getBalance() const;

    void setAge(int patientAge);
    void setGender(const char* patientGender);
    bool setContact(const char* patientContact);

    Patient& operator+=(double amount);
    Patient& operator-=(double amount);
    bool operator==(const Patient& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Patient& patient);
};
