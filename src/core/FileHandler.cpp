#include "FileHandler.hpp"
#include "../helpers/FilePathHelper.hpp"
#include "../helpers/DataHelper.hpp"
#include "../helpers/ConversionHelper.hpp"

#include <fstream>

void FileHandler::loadPatients(Storage<Patient>& storage) {
    std::ifstream file;
    char line[1024];
    char* fields[7];
    int fieldCount;
    int i;

    if (!FilePathHelper::openInputDataFile(file, "patients.txt")) {
        return;
    }

    for (i = 0; i < 7; i++) {
        fields[i] = new char[256];
    }

    file.getline(line, 1024);

    while (file.getline(line, 1024)) {
        DataHelper::splitByComma(line, fields, 7, fieldCount);

        if (fieldCount == 7) {
            Patient* patient = new Patient(
                ConversionHelper::stringToInt(fields[0]),
                fields[1],
                fields[5],
                ConversionHelper::stringToInt(fields[2]),
                fields[3],
                fields[4],
                ConversionHelper::stringToDouble(fields[6])
            );
            storage.add(*patient);
            delete patient;
        }
    }

    for (i = 0; i < 7; i++) {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadDoctors(Storage<Doctor>& storage) {
    std::ifstream file;
    char line[1024];
    char* fields[6];
    int fieldCount;
    int i;

    if (!FilePathHelper::openInputDataFile(file, "doctors.txt")) {
        return;
    }

    for (i = 0; i < 6; i++) {
        fields[i] = new char[256];
    }
    file.getline(line, 2048);
    while (file.getline(line, 1024)) {
        DataHelper::splitByComma(line, fields, 6, fieldCount);

        if (fieldCount == 6) {
            Doctor* doctor = new Doctor(
                ConversionHelper::stringToInt(fields[0]),
                fields[1],
                fields[4],
                fields[2],
                fields[3],
                ConversionHelper::stringToDouble(fields[5])
            );
            storage.add(*doctor);
            delete doctor;
        }
    }

    for (i = 0; i < 6; i++) {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadAdmin(Storage<Admin>& storage) {
    std::ifstream file;
    char line[1024];
    char* fields[3];
    int fieldCount;
    int i;

    if (!FilePathHelper::openInputDataFile(file, "admin.txt")) {
        return;
    }

    for (i = 0; i < 3; i++) {
        fields[i] = new char[256];
    }

    file.getline(line, 1024);

    while (file.getline(line, 1024)) {
        DataHelper::splitByComma(line, fields, 3, fieldCount);

        if (fieldCount == 3) {
            Admin* admin = new Admin(
                ConversionHelper::stringToInt(fields[0]),
                fields[1],
                fields[2]
            );
            storage.add(*admin);
            delete admin;
        }
    }

    for (i = 0; i < 3; i++) {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadAppointments(Storage<Appointment>& storage) {
    std::ifstream file;
    char line[1024];
    char* fields[6];
    int fieldCount;
    int i;

    if (!FilePathHelper::openInputDataFile(file, "appointments.txt")) {
        return;
    }

    for (i = 0; i < 6; i++) {
        fields[i] = new char[256];
    }
    // skip header line
    file.getline(line, 1024);

    while (file.getline(line, 1024)) {
        DataHelper::splitByComma(line, fields, 6, fieldCount);

        if (fieldCount == 6) {
            Appointment* appointment = new Appointment(
                ConversionHelper::stringToInt(fields[0]),
                ConversionHelper::stringToInt(fields[1]),
                ConversionHelper::stringToInt(fields[2]),
                fields[3],
                fields[4],
                fields[5]
            );
            storage.add(*appointment);
            delete appointment;
        }
    }

    for (i = 0; i < 6; i++) {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadBills(Storage<Bill>& storage) {
    std::ifstream file;
    char line[1024];
    char* fields[6];
    int fieldCount;
    int i;

    if (!FilePathHelper::openInputDataFile(file, "bills.txt")) {
        return;
    }

    for (i = 0; i < 6; i++) {
        fields[i] = new char[256];
    }
    // skip header line
    file.getline(line, 1024);

    while (file.getline(line, 1024)) {
        DataHelper::splitByComma(line, fields, 6, fieldCount);

        if (fieldCount == 6) {
            Bill* bill = new Bill(
                ConversionHelper::stringToInt(fields[0]),
                ConversionHelper::stringToInt(fields[1]),
                ConversionHelper::stringToInt(fields[2]),
                ConversionHelper::stringToDouble(fields[3]),
                fields[4],
                fields[5]
            );
            storage.add(*bill);
            delete bill;
        }
    }

    for (i = 0; i < 6; i++) {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadPrescriptions(Storage<Prescription>& storage) {
    std::ifstream file;
    char line[2048];
    char* fields[7];
    int fieldCount;
    int i;

    if (!FilePathHelper::openInputDataFile(file, "prescriptions.txt")) {
        return;
    }

    for (i = 0; i < 7; i++) {
        fields[i] = new char[512];
    }

    file.getline(line, 2048);

    while (file.getline(line, 2048)) {
        DataHelper::splitByComma(line, fields, 7, fieldCount);

        if (fieldCount == 7) {
            Prescription* prescription = new Prescription(
                ConversionHelper::stringToInt(fields[0]),
                ConversionHelper::stringToInt(fields[1]),
                ConversionHelper::stringToInt(fields[2]),
                ConversionHelper::stringToInt(fields[3]),
                fields[4],
                fields[5],
                fields[6]
            );
            storage.add(*prescription);
            delete prescription;
        }
    }

    for (i = 0; i < 7; i++) {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::savePatient(const Patient& patient, bool append) {
    std::ofstream file;
    char amountBuffer[32];

    if (append) {
        FilePathHelper::openOutputDataFile(file, "patients.txt", std::ios::app);
    } else {
        FilePathHelper::openOutputDataFile(file, "patients.txt", std::ios::out);
    }

    if (!file.is_open()) {
        return;
    }

    ConversionHelper::doubleToString(patient.getBalance(), amountBuffer);

    file << patient.getID() << ","
         << patient.getName() << ","
         << patient.getAge() << ","
         << patient.getGender() << ","
         << patient.getContact() << ","
         << patient.getPassword() << ","
         << amountBuffer << "\n";

    file.close();
}

void FileHandler::saveDoctor(const Doctor& doctor, bool append) {
    std::ofstream file;
    char feeBuffer[32];

    if (append) {
        FilePathHelper::openOutputDataFile(file, "doctors.txt", std::ios::app);
    } else {
        FilePathHelper::openOutputDataFile(file, "doctors.txt", std::ios::out);
    }

    if (!file.is_open()) {
        return;
    }

    ConversionHelper::doubleToString(doctor.getFee(), feeBuffer);

    file << doctor.getID() << ","
         << doctor.getName() << ","
         << doctor.getSpecialization() << ","
         << doctor.getContact() << ","
         << doctor.getPassword() << ","
         << feeBuffer << "\n";

    file.close();
}

void FileHandler::saveAdmin(const Admin& admin, bool append) {
    std::ofstream file;

    if (append) {
        FilePathHelper::openOutputDataFile(file, "admin.txt", std::ios::app);
    } else {
        FilePathHelper::openOutputDataFile(file, "admin.txt", std::ios::out);
    }

    if (!file.is_open()) {
        return;
    }

    file << admin.getID() << ","
         << admin.getName() << ","
         << admin.getPassword() << "\n";

    file.close();
}

void FileHandler::saveAppointment(const Appointment& appointment, bool append) {
    std::ofstream file;

    if (append) {
        FilePathHelper::openOutputDataFile(file, "appointments.txt", std::ios::app);
    } else {
        FilePathHelper::openOutputDataFile(file, "appointments.txt", std::ios::out);
    }

    if (!file.is_open()) {
        return;
    }

    file << appointment.getAppointmentID() << ","
         << appointment.getPatientID() << ","
         << appointment.getDoctorID() << ","
         << appointment.getDate() << ","
         << appointment.getTimeSlot() << ","
         << appointment.getStatus() << "\n";

    file.close();
}

void FileHandler::saveBill(const Bill& bill, bool append) {
    std::ofstream file;
    char amountBuffer[32];

    if (append) {
        FilePathHelper::openOutputDataFile(file, "bills.txt", std::ios::app);
    } else {
        FilePathHelper::openOutputDataFile(file, "bills.txt", std::ios::out);
    }

    if (!file.is_open()) {
        return;
    }

    ConversionHelper::doubleToString(bill.getAmount(), amountBuffer);

    file << bill.getBillID() << ","
         << bill.getPatientID() << ","
         << bill.getAppointmentID() << ","
         << amountBuffer << ","
         << bill.getStatus() << ","
         << bill.getDate() << "\n";

    file.close();
}

void FileHandler::savePrescription(const Prescription& prescription, bool append) {
    std::ofstream file;

    if (append) {
        FilePathHelper::openOutputDataFile(file, "prescriptions.txt", std::ios::app);
    } else {
        FilePathHelper::openOutputDataFile(file, "prescriptions.txt", std::ios::out);
    }

    if (!file.is_open()) {
        return;
    }

    file << prescription.getPrescriptionID() << ","
         << prescription.getAppointmentID() << ","
         << prescription.getPatientID() << ","
         << prescription.getDoctorID() << ","
         << prescription.getDate() << ","
         << prescription.getMedicines() << ","
         << prescription.getNotes() << "\n";

    file.close();
}

void FileHandler::saveDischargedPatient(const Patient& patient, bool append) {
    std::ofstream file;
    char amountBuffer[32];

    if (append) {
        FilePathHelper::openOutputDataFile(file, "discharged.txt", std::ios::app);
    } else {
        FilePathHelper::openOutputDataFile(file, "discharged.txt", std::ios::out);
    }

    if (!file.is_open()) {
        return;
    }

    ConversionHelper::doubleToString(patient.getBalance(), amountBuffer);

    file << patient.getID() << ","
         << patient.getName() << ","
         << patient.getAge() << ","
         << patient.getGender() << ","
         << patient.getContact() << ","
         << patient.getPassword() << ","
         << amountBuffer << "\n";

    file.close();
}

void FileHandler::saveAllPatients(Storage<Patient>& storage) {
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "patients.txt", std::ios::out)) {
        file << "patient_id,name,age,gender,contact,password,balance\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++) {
        savePatient(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllDoctors(Storage<Doctor>& storage) {
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "doctors.txt", std::ios::out)) {
        file << "doctor_id,name,specialization,contact,password,fee\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++) {
        saveDoctor(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllAdmins(Storage<Admin>& storage) {
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "admin.txt", std::ios::out)) {
        file << "admin_id,name,password\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++) {
        saveAdmin(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllAppointments(Storage<Appointment>& storage) {
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "appointments.txt", std::ios::out)) {
        file << "appointment_id,patient_id,doctor_id,date,time,status\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++) {
        saveAppointment(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllBills(Storage<Bill>& storage) {
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "bills.txt", std::ios::out)) {
        file << "bill_id,patient_id,appointment_id,amount,status,date\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++) {
        saveBill(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllPrescriptions(Storage<Prescription>& storage) {
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "prescriptions.txt", std::ios::out)) {
        file << "prescription_id,appointment_id,patient_id,doctor_id,date,medicines,notes\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++) {
        savePrescription(storage.getAll()[i], true);
    }
}
