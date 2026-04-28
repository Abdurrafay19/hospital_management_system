#include "Appointment.hpp"

#include "../core/Validator.hpp"
#include "../helpers/StringHelper.hpp"

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
    StringHelper::copyTextDynamic(date, other.date);
    StringHelper::copyTextDynamic(timeSlot, other.timeSlot);
    StringHelper::copyTextDynamic(status, other.status);
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
        StringHelper::copyTextDynamic(date, other.date);
        StringHelper::copyTextDynamic(timeSlot, other.timeSlot);
        StringHelper::copyTextDynamic(status, other.status);
    }

    return *this;
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

    StringHelper::copyTextDynamic(date, newDate);
}

void Appointment::setTimeSlot(const char* newTimeSlot) {
    StringHelper::copyTextDynamic(timeSlot, newTimeSlot);
}

void Appointment::setStatus(const char* newStatus) {
    StringHelper::copyTextDynamic(status, newStatus);
}

bool Appointment::isCancelled() const {
    return StringHelper::textEqualsIgnoreCase(status, "cancelled");
}

bool Appointment::operator==(const Appointment& other) const {
    if (doctorID != other.doctorID) {
        return false;
    }

    if (!StringHelper::textEquals(date, other.date)) {
        return false;
    }

    if (!StringHelper::textEquals(timeSlot, other.timeSlot)) {
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
