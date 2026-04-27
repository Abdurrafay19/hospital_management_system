#include "Doctor.hpp"

#include "Validator.hpp"

Doctor::Doctor() : Person() {
    specialization = nullptr;
    contact = nullptr;
    fee = 0.0;
}

Doctor::Doctor(int doctorID,
               const char* doctorName,
               const char* doctorPassword,
               const char* doctorSpecialization,
               const char* doctorContact,
               double doctorFee)
    : Person(doctorID, doctorName, doctorPassword) {
    specialization = nullptr;
    contact = nullptr;
    fee = 0.0;

    setSpecialization(doctorSpecialization);
    setContact(doctorContact);
    setFee(doctorFee);
}

Doctor::Doctor(const Doctor& other) : Person(other) {
    specialization = nullptr;
    contact = nullptr;
    fee = other.fee;

    copyText(specialization, other.specialization);
    copyText(contact, other.contact);
}

Doctor::~Doctor() {
    delete[] specialization;
    delete[] contact;
    specialization = nullptr;
    contact = nullptr;
}

Doctor& Doctor::operator=(const Doctor& other) {
    if (this != &other) {
        Person::operator=(other);
        fee = other.fee;
        copyText(specialization, other.specialization);
        copyText(contact, other.contact);
    }

    return *this;
}

void Doctor::displayDashboard() {
    std::cout << "Doctor Dashboard - ID: " << id << "\n";
}

void Doctor::showProfile() const {
    std::cout << *this << "\n";
}

const char* Doctor::getSpecialization() const {
    return specialization;
}

const char* Doctor::getContact() const {
    return contact;
}

double Doctor::getFee() const {
    return fee;
}

void Doctor::setSpecialization(const char* doctorSpecialization) {
    copyText(specialization, doctorSpecialization);
}

bool Doctor::setContact(const char* doctorContact) {
    if (!Validator::isValidContact(doctorContact)) {
        return false;
    }

    copyText(contact, doctorContact);
    return true;
}

void Doctor::setFee(double doctorFee) {
    if (doctorFee > 0.0) {
        fee = doctorFee;
    }
}

bool Doctor::operator==(const Doctor& other) const {
    return id == other.id;
}

std::ostream& operator<<(std::ostream& out, const Doctor& doctor) {
    const char* safeName;
    const char* safeSpecialization;
    const char* safeContact;

    safeName = doctor.name != nullptr ? doctor.name : "";
    safeSpecialization = doctor.specialization != nullptr ? doctor.specialization : "";
    safeContact = doctor.contact != nullptr ? doctor.contact : "";

    out << "Doctor[ID=" << doctor.id
        << ", Name=" << safeName
        << ", Specialization=" << safeSpecialization
        << ", Contact=" << safeContact
        << ", Fee=" << doctor.fee
        << "]";

    return out;
}
