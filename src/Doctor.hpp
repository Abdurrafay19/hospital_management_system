#pragma once

#include <iostream>

#include "Person.hpp"

class Doctor : public Person {
private:
    char* specialization;
    char* contact;
    double fee;

public:
    Doctor();
    Doctor(int doctorID,
           const char* doctorName,
           const char* doctorPassword,
           const char* doctorSpecialization,
           const char* doctorContact,
           double doctorFee);
    ~Doctor();

    void displayDashboard();
    void showProfile() const;

    const char* getSpecialization() const;
    const char* getContact() const;
    double getFee() const;

    void setSpecialization(const char* doctorSpecialization);
    bool setContact(const char* doctorContact);
    void setFee(double doctorFee);

    bool operator==(const Doctor& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);
};
