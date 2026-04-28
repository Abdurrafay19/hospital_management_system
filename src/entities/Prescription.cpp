#include "Prescription.hpp"
#include "../helpers/StringHelper.hpp"

#include "../core/Validator.hpp"

Prescription::Prescription() {
    prescriptionID = 0;
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;
    date = nullptr;
    medicines = nullptr;
    notes = nullptr;
}

Prescription::Prescription(int newPrescriptionID,
                           int newAppointmentID,
                           int newPatientID,
                           int newDoctorID,
                           const char* newDate,
                           const char* newMedicines,
                           const char* newNotes) {
    prescriptionID = 0;
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;
    date = nullptr;
    medicines = nullptr;
    notes = nullptr;

    setPrescriptionID(newPrescriptionID);
    setAppointmentID(newAppointmentID);
    setPatientID(newPatientID);
    setDoctorID(newDoctorID);
    setDate(newDate);
    setMedicines(newMedicines);
    setNotes(newNotes);
}

Prescription::Prescription(const Prescription& other) {
    prescriptionID = 0;
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;
    date = nullptr;
    medicines = nullptr;
    notes = nullptr;

    prescriptionID = other.prescriptionID;
    appointmentID = other.appointmentID;
    patientID = other.patientID;
    doctorID = other.doctorID;
    StringHelper::copyTextDynamic(date, other.date);
    setMedicines(other.medicines);
    setNotes(other.notes);
}

Prescription::~Prescription() {
    delete[] date;
    delete[] medicines;
    delete[] notes;

    date = nullptr;
    medicines = nullptr;
    notes = nullptr;
}

Prescription& Prescription::operator=(const Prescription& other) {
    if (this != &other) {
        prescriptionID = other.prescriptionID;
        appointmentID = other.appointmentID;
        patientID = other.patientID;
        doctorID = other.doctorID;
        StringHelper::copyTextDynamic(date, other.date);
        setMedicines(other.medicines);
        setNotes(other.notes);
    }

    return *this;
}


int Prescription::getPrescriptionID() const {
    return prescriptionID;
}

int Prescription::getID() const {
    return prescriptionID;
}

int Prescription::getAppointmentID() const {
    return appointmentID;
}

int Prescription::getPatientID() const {
    return patientID;
}

int Prescription::getDoctorID() const {
    return doctorID;
}

const char* Prescription::getDate() const {
    return date;
}

const char* Prescription::getMedicines() const {
    return medicines;
}

const char* Prescription::getNotes() const {
    return notes;
}

void Prescription::setPrescriptionID(int newPrescriptionID) {
    if (Validator::isValidID(newPrescriptionID)) {
        prescriptionID = newPrescriptionID;
    }
}

void Prescription::setAppointmentID(int newAppointmentID) {
    if (Validator::isValidID(newAppointmentID)) {
        appointmentID = newAppointmentID;
    }
}

void Prescription::setPatientID(int newPatientID) {
    if (Validator::isValidID(newPatientID)) {
        patientID = newPatientID;
    }
}

void Prescription::setDoctorID(int newDoctorID) {
    if (Validator::isValidID(newDoctorID)) {
        doctorID = newDoctorID;
    }
}

void Prescription::setDate(const char* newDate) {
    if (!Validator::isValidDate(newDate)) {
        return;
    }

    StringHelper::copyTextDynamic(date, newDate);
}

void Prescription::setMedicines(const char* newMedicines) {
    int i;
    int length;

    delete[] medicines;
    medicines = nullptr;

    if (newMedicines == nullptr) {
        return;
    }

    length = 0;
    while (newMedicines[length] != '\0' && length < 499) {
        length++;
    }

    medicines = new char[length + 1];

    i = 0;
    while (i < length) {
        medicines[i] = newMedicines[i];
        i++;
    }
    medicines[i] = '\0';
}

void Prescription::setNotes(const char* newNotes) {
    int i;
    int length;

    delete[] notes;
    notes = nullptr;

    if (newNotes == nullptr) {
        return;
    }

    length = 0;
    while (newNotes[length] != '\0' && length < 299) {
        length++;
    }

    notes = new char[length + 1];

    i = 0;
    while (i < length) {
        notes[i] = newNotes[i];
        i++;
    }
    notes[i] = '\0';
}

bool Prescription::operator==(const Prescription& other) const {
    return prescriptionID == other.prescriptionID;
}

std::ostream& operator<<(std::ostream& out, const Prescription& prescription) {
    const char* safeDate;
    const char* safeMedicines;
    const char* safeNotes;

    safeDate = prescription.date != nullptr ? prescription.date : "";
    safeMedicines = prescription.medicines != nullptr ? prescription.medicines : "";
    safeNotes = prescription.notes != nullptr ? prescription.notes : "";

    out << "Prescription[ID=" << prescription.prescriptionID
        << ", AppointmentID=" << prescription.appointmentID
        << ", PatientID=" << prescription.patientID
        << ", DoctorID=" << prescription.doctorID
        << ", Date=" << safeDate
        << ", Medicines=" << safeMedicines
        << ", Notes=" << safeNotes
        << "]";

    return out;
}
