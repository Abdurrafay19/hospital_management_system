#include "HospitalSystem.hpp"

bool HospitalSystem::textEquals(const char* left, const char* right) {
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

int HospitalSystem::nextIDFromPatients(Storage<Patient>& storage) {
    int i;
    int maxID;

    maxID = 0;
    for (i = 0; i < storage.size(); i++) {
        if (storage.getAll()[i].getID() > maxID) {
            maxID = storage.getAll()[i].getID();
        }
    }

    return maxID + 1;
}

int HospitalSystem::nextIDFromDoctors(Storage<Doctor>& storage) {
    int i;
    int maxID;

    maxID = 0;
    for (i = 0; i < storage.size(); i++) {
        if (storage.getAll()[i].getID() > maxID) {
            maxID = storage.getAll()[i].getID();
        }
    }

    return maxID + 1;
}

int HospitalSystem::nextIDFromAdmins(Storage<Admin>& storage) {
    int i;
    int maxID;

    maxID = 0;
    for (i = 0; i < storage.size(); i++) {
        if (storage.getAll()[i].getID() > maxID) {
            maxID = storage.getAll()[i].getID();
        }
    }

    return maxID + 1;
}

int HospitalSystem::nextIDFromAppointments(Storage<Appointment>& storage) {
    int i;
    int maxID;

    maxID = 0;
    for (i = 0; i < storage.size(); i++) {
        if (storage.getAll()[i].getAppointmentID() > maxID) {
            maxID = storage.getAll()[i].getAppointmentID();
        }
    }

    return maxID + 1;
}

int HospitalSystem::nextIDFromBills(Storage<Bill>& storage) {
    int i;
    int maxID;

    maxID = 0;
    for (i = 0; i < storage.size(); i++) {
        if (storage.getAll()[i].getBillID() > maxID) {
            maxID = storage.getAll()[i].getBillID();
        }
    }

    return maxID + 1;
}

int HospitalSystem::nextIDFromPrescriptions(Storage<Prescription>& storage) {
    int i;
    int maxID;

    maxID = 0;
    for (i = 0; i < storage.size(); i++) {
        if (storage.getAll()[i].getPrescriptionID() > maxID) {
            maxID = storage.getAll()[i].getPrescriptionID();
        }
    }

    return maxID + 1;
}

HospitalSystem::HospitalSystem() {
    failedLoginAttempts = 0;
    sessionLocked = false;

    FileHandler::loadPatients(patients);
    FileHandler::loadDoctors(doctors);
    FileHandler::loadAdmin(admins);
    FileHandler::loadAppointments(appointments);
    FileHandler::loadBills(bills);
    FileHandler::loadPrescriptions(prescriptions);
}

Person* HospitalSystem::login(int id, const char* password, Role role) {
    Patient* patient;
    Doctor* doctor;
    Admin* admin;

    if (sessionLocked) {
        std::cout << "Account locked. Contact admin.\n";
        return nullptr;
    }

    patient = nullptr;
    doctor = nullptr;
    admin = nullptr;

    if (role == ROLE_PATIENT) {
        patient = patients.findByID(id);
        if (patient != nullptr && textEquals(patient->getPassword(), password)) {
            failedLoginAttempts = 0;
            return patient;
        }
    } else if (role == ROLE_DOCTOR) {
        doctor = doctors.findByID(id);
        if (doctor != nullptr && textEquals(doctor->getPassword(), password)) {
            failedLoginAttempts = 0;
            return doctor;
        }
    } else if (role == ROLE_ADMIN) {
        admin = admins.findByID(id);
        if (admin != nullptr && textEquals(admin->getPassword(), password)) {
            failedLoginAttempts = 0;
            return admin;
        }
    }

    failedLoginAttempts++;
    if (failedLoginAttempts >= 3) {
        sessionLocked = true;
        std::cout << "Account locked. Contact admin.\n";
    }

    return nullptr;
}

void HospitalSystem::bookAppointment(Patient* patient, int doctorID, const char* date, const char* timeSlot) {
    Doctor* doctor;
    Appointment* appointmentsArray;
    Appointment candidate;
    Appointment newAppointment;
    Bill newBill;
    int newAppointmentID;
    int newBillID;
    int i;

    if (patient == nullptr || date == nullptr || timeSlot == nullptr) {
        throw InvalidInputException();
    }

    if (!Validator::isValidDate(date)) {
        throw InvalidInputException("Invalid appointment date.");
    }

    doctor = doctors.findByID(doctorID);
    if (doctor == nullptr) {
        throw InvalidInputException("Doctor not found.");
    }

    if (patient->getBalance() < doctor->getFee()) {
        throw InsufficientFundsException();
    }

    candidate = Appointment(1, patient->getID(), doctorID, date, timeSlot, "pending");
    appointmentsArray = appointments.getAll();
    for (i = 0; i < appointments.size(); i++) {
        if (appointmentsArray[i] == candidate) {
            throw SlotUnavailableException();
        }
    }

    newAppointmentID = nextIDFromAppointments(appointments);
    newBillID = nextIDFromBills(bills);

    *patient -= doctor->getFee();

    newAppointment = Appointment(newAppointmentID, patient->getID(), doctorID, date, timeSlot, "pending");
    appointments.add(newAppointment);

    newBill = Bill(newBillID, patient->getID(), newAppointmentID, doctor->getFee(), "unpaid", date);
    bills.add(newBill);

    FileHandler::saveAllPatients(patients);
    FileHandler::saveAllAppointments(appointments);
    FileHandler::saveAllBills(bills);
}

void HospitalSystem::payBill(Patient* patient, int billID) {
    Bill* bill;

    if (patient == nullptr) {
        throw InvalidInputException();
    }

    bill = bills.findByID(billID);
    if (bill == nullptr || bill->getPatientID() != patient->getID()) {
        throw InvalidInputException("Bill not found for this patient.");
    }

    if (textEquals(bill->getStatus(), "paid")) {
        throw InvalidInputException("Bill is already paid.");
    }

    if (patient->getBalance() < bill->getAmount()) {
        throw InsufficientFundsException();
    }

    *patient -= bill->getAmount();
    bill->setStatus("paid");

    FileHandler::saveAllPatients(patients);
    FileHandler::saveAllBills(bills);
}

void HospitalSystem::dischargePatient(int patientID) {
    Patient* patient;
    int appointmentIDs[100];
    int billIDs[100];
    int prescriptionIDs[100];
    int appointmentCount;
    int billCount;
    int prescriptionCount;
    int i;

    patient = patients.findByID(patientID);
    if (patient == nullptr) {
        throw InvalidInputException("Patient not found.");
    }

    appointmentCount = 0;
    billCount = 0;
    prescriptionCount = 0;

    for (i = 0; i < appointments.size(); i++) {
        if (appointments.getAll()[i].getPatientID() == patientID && textEquals(appointments.getAll()[i].getStatus(), "pending")) {
            throw InvalidInputException("Patient has pending appointments.");
        }
        if (appointments.getAll()[i].getPatientID() == patientID) {
            appointmentIDs[appointmentCount] = appointments.getAll()[i].getAppointmentID();
            appointmentCount++;
        }
    }

    for (i = 0; i < bills.size(); i++) {
        if (bills.getAll()[i].getPatientID() == patientID && !textEquals(bills.getAll()[i].getStatus(), "paid")) {
            throw InvalidInputException("Patient has unpaid bills.");
        }
        if (bills.getAll()[i].getPatientID() == patientID) {
            billIDs[billCount] = bills.getAll()[i].getBillID();
            billCount++;
        }
    }

    for (i = 0; i < prescriptions.size(); i++) {
        if (prescriptions.getAll()[i].getPatientID() == patientID) {
            prescriptionIDs[prescriptionCount] = prescriptions.getAll()[i].getPrescriptionID();
            prescriptionCount++;
        }
    }

    FileHandler::saveDischargedPatient(*patient, true);

    for (i = appointmentCount - 1; i >= 0; i--) {
        appointments.removeByID(appointmentIDs[i]);
    }

    for (i = billCount - 1; i >= 0; i--) {
        bills.removeByID(billIDs[i]);
    }

    for (i = prescriptionCount - 1; i >= 0; i--) {
        prescriptions.removeByID(prescriptionIDs[i]);
    }

    patients.removeByID(patientID);

    FileHandler::saveAllPatients(patients);
    FileHandler::saveAllAppointments(appointments);
    FileHandler::saveAllBills(bills);
    FileHandler::saveAllPrescriptions(prescriptions);
}

Storage<Patient>& HospitalSystem::getPatients() {
    return patients;
}

Storage<Doctor>& HospitalSystem::getDoctors() {
    return doctors;
}

Storage<Admin>& HospitalSystem::getAdmins() {
    return admins;
}

Storage<Appointment>& HospitalSystem::getAppointments() {
    return appointments;
}

Storage<Bill>& HospitalSystem::getBills() {
    return bills;
}

Storage<Prescription>& HospitalSystem::getPrescriptions() {
    return prescriptions;
}