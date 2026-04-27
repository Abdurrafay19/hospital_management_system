#include "FileHandler.hpp"

#include <fstream>
#include <cstdio>

int FileHandler::stringLength(const char* str) {
    int length;

    if (str == nullptr) {
        return 0;
    }

    length = 0;
    while (str[length] != '\0') {
        length++;
    }

    return length;
}

void FileHandler::stringCopy(char* destination, const char* source, int maxLength) {
    int i;

    if (destination == nullptr || source == nullptr) {
        return;
    }

    i = 0;
    while (i < maxLength && source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

int FileHandler::stringToInt(const char* str) {
    int result;
    int i;
    int isNegative;

    if (str == nullptr) {
        return 0;
    }

    result = 0;
    isNegative = 0;
    i = 0;

    if (str[0] == '-') {
        isNegative = 1;
        i = 1;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return isNegative ? -result : result;
}

double FileHandler::stringToDouble(const char* str) {
    double result;
    double decimalPlace;
    int i;
    int isNegative;
    int foundDot;

    if (str == nullptr) {
        return 0.0;
    }

    result = 0.0;
    isNegative = 0;
    foundDot = 0;
    decimalPlace = 1.0;
    i = 0;

    if (str[0] == '-') {
        isNegative = 1;
        i = 1;
    }

    while (str[i] != '\0') {
        if (str[i] == '.' && !foundDot) {
            foundDot = 1;
            decimalPlace = 0.1;
        } else if (str[i] >= '0' && str[i] <= '9') {
            if (foundDot) {
                result = result + (double)(str[i] - '0') * decimalPlace;
                decimalPlace = decimalPlace * 0.1;
            } else {
                result = result * 10.0 + (double)(str[i] - '0');
            }
        }
        i++;
    }

    return isNegative ? -result : result;
}

void FileHandler::intToString(int value, char* buffer) {
    int i;
    int length;
    int temp;

    if (buffer == nullptr) {
        return;
    }

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0) {
        buffer[0] = '-';
        value = -value;
        i = 1;
    } else {
        i = 0;
    }

    length = 0;
    temp = value;
    while (temp > 0) {
        length++;
        temp = temp / 10;
    }

    temp = value;
    while (temp > 0) {
        buffer[i + length - 1] = static_cast<char>('0' + (temp % 10));
        temp = temp / 10;
        length--;
    }

    if (value < 0) {
        buffer[i + length] = '\0';
    } else {
        buffer[i] = '\0';
    }
}

void FileHandler::doubleToString(double value, char* buffer) {
    int intPart;
    double decPart;
    int i;
    int digits;

    if (buffer == nullptr) {
        return;
    }

    if (value < 0.0) {
        buffer[0] = '-';
        value = -value;
        i = 1;
    } else {
        i = 0;
    }

    intPart = static_cast<int>(value);
    decPart = value - intPart;

    intToString(intPart, buffer + i);

    i = 0;
    while (buffer[i] != '\0') {
        i++;
    }

    buffer[i] = '.';
    i++;

    digits = 0;
    while (digits < 2 && decPart > 0.0) {
        decPart = decPart * 10.0;
        buffer[i] = static_cast<char>('0' + static_cast<int>(decPart));
        decPart = decPart - static_cast<int>(decPart);
        i++;
        digits++;
    }

    buffer[i] = '\0';
}

void FileHandler::splitByComma(const char* line, char** fields, int maxFields, int& fieldCount) {
    int i;
    int j;
    int fieldIndex;

    if (line == nullptr || fields == nullptr) {
        fieldCount = 0;
        return;
    }

    fieldIndex = 0;
    i = 0;
    j = 0;

    while (fieldIndex < maxFields && line[i] != '\0') {
        if (line[i] == ',') {
            fields[fieldIndex][j] = '\0';
            fieldIndex++;
            j = 0;
            i++;
        } else if (line[i] == '\n' || line[i] == '\r') {
            fields[fieldIndex][j] = '\0';
            fieldIndex++;
            break;
        } else {
            fields[fieldIndex][j] = line[i];
            j++;
            i++;
        }
    }

    if (fieldIndex < maxFields && line[i] == '\0') {
        fields[fieldIndex][j] = '\0';
        fieldIndex++;
    }

    fieldCount = fieldIndex;
}

void FileHandler::loadPatients(Storage<Patient>& storage) {
    std::ifstream file("patients.txt");
    char line[1024];
    char* fields[7];
    int fieldCount;
    int i;

    if (!file.is_open()) {
        return;
    }

    for (i = 0; i < 7; i++) {
        fields[i] = new char[256];
    }

    while (file.getline(line, 1024)) {
        splitByComma(line, fields, 7, fieldCount);

        if (fieldCount == 7) {
            Patient* patient = new Patient(
                stringToInt(fields[0]),
                fields[1],
                fields[5],
                stringToInt(fields[2]),
                fields[3],
                fields[4],
                stringToDouble(fields[6])
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
    std::ifstream file("doctors.txt");
    char line[1024];
    char* fields[6];
    int fieldCount;
    int i;

    if (!file.is_open()) {
        return;
    }

    for (i = 0; i < 6; i++) {
        fields[i] = new char[256];
    }

    while (file.getline(line, 1024)) {
        splitByComma(line, fields, 6, fieldCount);

        if (fieldCount == 6) {
            Doctor* doctor = new Doctor(
                stringToInt(fields[0]),
                fields[1],
                fields[4],
                fields[2],
                fields[3],
                stringToDouble(fields[5])
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
    std::ifstream file("admin.txt");
    char line[1024];
    char* fields[3];
    int fieldCount;
    int i;

    if (!file.is_open()) {
        return;
    }

    for (i = 0; i < 3; i++) {
        fields[i] = new char[256];
    }

    while (file.getline(line, 1024)) {
        splitByComma(line, fields, 3, fieldCount);

        if (fieldCount == 3) {
            Admin* admin = new Admin(
                stringToInt(fields[0]),
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
    std::ifstream file("appointments.txt");
    char line[1024];
    char* fields[6];
    int fieldCount;
    int i;

    if (!file.is_open()) {
        return;
    }

    for (i = 0; i < 6; i++) {
        fields[i] = new char[256];
    }

    while (file.getline(line, 1024)) {
        splitByComma(line, fields, 6, fieldCount);

        if (fieldCount == 6) {
            Appointment* appointment = new Appointment(
                stringToInt(fields[0]),
                stringToInt(fields[1]),
                stringToInt(fields[2]),
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
    std::ifstream file("bills.txt");
    char line[1024];
    char* fields[6];
    int fieldCount;
    int i;

    if (!file.is_open()) {
        return;
    }

    for (i = 0; i < 6; i++) {
        fields[i] = new char[256];
    }

    while (file.getline(line, 1024)) {
        splitByComma(line, fields, 6, fieldCount);

        if (fieldCount == 6) {
            Bill* bill = new Bill(
                stringToInt(fields[0]),
                stringToInt(fields[1]),
                stringToInt(fields[2]),
                stringToDouble(fields[3]),
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
    std::ifstream file("prescriptions.txt");
    char line[2048];
    char* fields[7];
    int fieldCount;
    int i;

    if (!file.is_open()) {
        return;
    }

    for (i = 0; i < 7; i++) {
        fields[i] = new char[512];
    }

    while (file.getline(line, 2048)) {
        splitByComma(line, fields, 7, fieldCount);

        if (fieldCount == 7) {
            Prescription* prescription = new Prescription(
                stringToInt(fields[0]),
                stringToInt(fields[1]),
                stringToInt(fields[2]),
                stringToInt(fields[3]),
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
        file.open("patients.txt", std::ios::app);
    } else {
        file.open("patients.txt");
    }

    if (!file.is_open()) {
        return;
    }

    doubleToString(patient.getBalance(), amountBuffer);

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
        file.open("doctors.txt", std::ios::app);
    } else {
        file.open("doctors.txt");
    }

    if (!file.is_open()) {
        return;
    }

    doubleToString(doctor.getFee(), feeBuffer);

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
        file.open("admin.txt", std::ios::app);
    } else {
        file.open("admin.txt");
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
        file.open("appointments.txt", std::ios::app);
    } else {
        file.open("appointments.txt");
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
        file.open("bills.txt", std::ios::app);
    } else {
        file.open("bills.txt");
    }

    if (!file.is_open()) {
        return;
    }

    doubleToString(bill.getAmount(), amountBuffer);

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
        file.open("prescriptions.txt", std::ios::app);
    } else {
        file.open("prescriptions.txt");
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
