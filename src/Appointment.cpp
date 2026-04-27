#include "Appointment.hpp"

#include "Validator.hpp"

static char toLowerASCII(char c) {
    if (c >= 'A' && c <= 'Z') {
        return static_cast<char>(c + ('a' - 'A'));
    }

    return c;
}

static bool textEquals(const char* left, const char* right) {
    int i;

    if (left == nullptr || right == nullptr) {
        return left == right;
    }

    i = 0;
    while (left[i] != '\0' && right[i] != '\0') {
        if (left[i] != right[i]) {
            return false;
        }
        i++;
    }

    return left[i] == '\0' && right[i] == '\0';
}

static bool textEqualsIgnoreCase(const char* left, const char* right) {
    int i;

    if (left == nullptr || right == nullptr) {
        return left == right;
    }

    i = 0;
    while (left[i] != '\0' && right[i] != '\0') {
        if (toLowerASCII(left[i]) != toLowerASCII(right[i])) {
            return false;
        }
        i++;
    }

    return left[i] == '\0' && right[i] == '\0';
}

Appointment::Appointment() {
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;
    date = nullptr;
    timeSlot = nullptr;
    status = nullptr;
}

Appointment::Appointment(int newAppointmentID,
                         int newPatientID,
                         int newDoctorID,
                         const char* newDate,
                         const char* newTimeSlot,
                         const char* newStatus) {
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;
    date = nullptr;
    timeSlot = nullptr;
    status = nullptr;

    setAppointmentID(newAppointmentID);
    setPatientID(newPatientID);
    setDoctorID(newDoctorID);
    setDate(newDate);
    setTimeSlot(newTimeSlot);
    setStatus(newStatus);
}

Appointment::Appointment(const Appointment& other) {
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;
    date = nullptr;
    timeSlot = nullptr;
    status = nullptr;

    appointmentID = other.appointmentID;
    patientID = other.patientID;
    doctorID = other.doctorID;
    copyText(date, other.date);
    copyText(timeSlot, other.timeSlot);
    copyText(status, other.status);
}

Appointment::~Appointment() {
    delete[] date;
    delete[] timeSlot;
    delete[] status;

    date = nullptr;
    timeSlot = nullptr;
    status = nullptr;
}

Appointment& Appointment::operator=(const Appointment& other) {
    if (this != &other) {
        appointmentID = other.appointmentID;
        patientID = other.patientID;
        doctorID = other.doctorID;
        copyText(date, other.date);
        copyText(timeSlot, other.timeSlot);
        copyText(status, other.status);
    }

    return *this;
}

void Appointment::copyText(char*& destination, const char* source) {
    int i;
    int length;

    delete[] destination;
    destination = nullptr;

    if (source == nullptr) {
        return;
    }

    length = 0;
    while (source[length] != '\0') {
        length++;
    }

    destination = new char[length + 1];

    i = 0;
    while (i < length) {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

int Appointment::getAppointmentID() const {
    return appointmentID;
}

int Appointment::getID() const {
    return appointmentID;
}

int Appointment::getPatientID() const {
    return patientID;
}

int Appointment::getDoctorID() const {
    return doctorID;
}

const char* Appointment::getDate() const {
    return date;
}

const char* Appointment::getTimeSlot() const {
    return timeSlot;
}

const char* Appointment::getStatus() const {
    return status;
}

void Appointment::setAppointmentID(int newAppointmentID) {
    if (Validator::isValidID(newAppointmentID)) {
        appointmentID = newAppointmentID;
    }
}

void Appointment::setPatientID(int newPatientID) {
    if (Validator::isValidID(newPatientID)) {
        patientID = newPatientID;
    }
}

void Appointment::setDoctorID(int newDoctorID) {
    if (Validator::isValidID(newDoctorID)) {
        doctorID = newDoctorID;
    }
}

void Appointment::setDate(const char* newDate) {
    if (!Validator::isValidDate(newDate)) {
        return;
    }

    copyText(date, newDate);
}

void Appointment::setTimeSlot(const char* newTimeSlot) {
    copyText(timeSlot, newTimeSlot);
}

void Appointment::setStatus(const char* newStatus) {
    copyText(status, newStatus);
}

bool Appointment::isCancelled() const {
    return textEqualsIgnoreCase(status, "cancelled");
}

bool Appointment::operator==(const Appointment& other) const {
    if (doctorID != other.doctorID) {
        return false;
    }

    if (!textEquals(date, other.date)) {
        return false;
    }

    if (!textEquals(timeSlot, other.timeSlot)) {
        return false;
    }

    if (isCancelled() || other.isCancelled()) {
        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const Appointment& appointment) {
    const char* safeDate;
    const char* safeTimeSlot;
    const char* safeStatus;

    safeDate = appointment.date != nullptr ? appointment.date : "";
    safeTimeSlot = appointment.timeSlot != nullptr ? appointment.timeSlot : "";
    safeStatus = appointment.status != nullptr ? appointment.status : "";

    out << "Appointment[ID=" << appointment.appointmentID
        << ", PatientID=" << appointment.patientID
        << ", DoctorID=" << appointment.doctorID
        << ", Date=" << safeDate
        << ", TimeSlot=" << safeTimeSlot
        << ", Status=" << safeStatus
        << "]";

    return out;
}
