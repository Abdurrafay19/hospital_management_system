#include "Patient.hpp"

#include "Validator.hpp"

Patient::Patient() : Person() {
    age = 0;
    gender = 0;
    contact = 0;
    balance = 0;
}

Patient::Patient(int patientID,
                 const char* patientName,
                 const char* patientPassword,
                 int patientAge,
                 const char* patientGender,
                 const char* patientContact,
                 double patientBalance)
    : Person(patientID, patientName, patientPassword) {
    age = 0;
    gender = 0;
    contact = 0;
    balance = 0;

    setAge(patientAge);
    setGender(patientGender);
    setContact(patientContact);

    if (patientBalance > 0) {
        balance = patientBalance;
    }
}

Patient::~Patient() {
    delete[] gender;
    delete[] contact;
    gender = 0;
    contact = 0;
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

double Patient::getBalance() const {
    return balance;
}

void Patient::setAge(int patientAge) {
    if (patientAge > 0) {
        age = patientAge;
    }
}

void Patient::setGender(const char* patientGender) {
    copyText(gender, patientGender);
}

bool Patient::setContact(const char* patientContact) {
    if (!Validator::isValidContact(patientContact)) {
        return false;
    }

    copyText(contact, patientContact);
    return true;
}

Patient& Patient::operator+=(double amount) {
    if (amount > 0) {
        balance = balance + amount;
    }
    return *this;
}

Patient& Patient::operator-=(double amount) {
    if (amount > 0 && amount <= balance) {
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
