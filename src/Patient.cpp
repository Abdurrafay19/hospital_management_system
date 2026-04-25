#include "Patient.hpp"

#include "Validator.hpp"

Patient::Patient() : Person() {
    age = 0;
    gender[0] = '\0';
    contact[0] = '\0';
    balance = 0.0f;
}

Patient::Patient(int patientID,
                 const char* patientName,
                 const char* patientPassword,
                 int patientAge,
                 const char* patientGender,
                 const char* patientContact,
                 float patientBalance)
    : Person(patientID, patientName, patientPassword) {
    age = 0;
    gender[0] = '\0';
    contact[0] = '\0';
    balance = 0.0f;

    setAge(patientAge);
    setGender(patientGender);
    setContact(patientContact);

    if (patientBalance > 0.0f) {
        balance = patientBalance;
    }
}

void Patient::displayDashboard() {
    std::cout << "Patient Dashboard - ID: " << id << "\n";
}

void Patient::showProfile() const {
    std::cout << *this << "\n";
}

int Patient::getAge() const {
    return age;
}

const char* Patient::getGender() const {
    return gender;
}

const char* Patient::getContact() const {
    return contact;
}

float Patient::getBalance() const {
    return balance;
}

void Patient::setAge(int patientAge) {
    if (patientAge > 0) {
        age = patientAge;
    }
}

void Patient::setGender(const char* patientGender) {
    copyText(gender, patientGender, 10);
}

bool Patient::setContact(const char* patientContact) {
    if (!Validator::isValidContact(patientContact)) {
        return false;
    }

    copyText(contact, patientContact, 12);
    return true;
}

Patient& Patient::operator+=(float amount) {
    if (amount > 0.0f) {
        balance = balance + amount;
    }
    return *this;
}

Patient& Patient::operator-=(float amount) {
    if (amount > 0.0f && amount <= balance) {
        balance = balance - amount;
    }
    return *this;
}

bool Patient::operator==(const Patient& other) const {
    return id == other.id;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient) {
    out << "Patient[ID=" << patient.id
        << ", Name=" << patient.name
        << ", Age=" << patient.age
        << ", Gender=" << patient.gender
        << ", Contact=" << patient.contact
        << ", Balance=" << patient.balance
        << "]";

    return out;
}
