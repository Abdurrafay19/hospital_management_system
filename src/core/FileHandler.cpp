#include "FileHandler.hpp"
#include "../helpers/FilePathHelper.hpp"
#include "../helpers/DataHelper.hpp"
#include "../helpers/ConversionHelper.hpp"

#include <fstream>
#include <ctime>

void FileHandler::loadPatients(Storage<Patient> &storage)
{
    std::ifstream file;
    char line[MAX_LINE_BUFFER];
    char *fields[MAX_PATIENT_FIELDS];
    int fieldCount;

    if (!FilePathHelper::openInputDataFile(file, "patients.txt"))
    {
        return;
    }

    for (int i = 0; i < MAX_PATIENT_FIELDS; i++)
    {
        fields[i] = new char[MAX_FIELD_BUFFER];
    }

    file.getline(line, MAX_LINE_BUFFER);

    while (file.getline(line, MAX_LINE_BUFFER))
    {
        DataHelper::splitByComma(line, fields, MAX_PATIENT_FIELDS, fieldCount);

        if (fieldCount == MAX_PATIENT_FIELDS)
        {
            Patient *patient = new Patient(
                ConversionHelper::stringToInt(fields[0]),
                fields[1],
                fields[5],
                ConversionHelper::stringToInt(fields[2]),
                fields[3],
                fields[4],
                ConversionHelper::stringToDouble(fields[6]));
            storage.add(*patient);
            delete patient;
        }
    }

    for (int i = 0; i < MAX_PATIENT_FIELDS; i++)
    {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadDoctors(Storage<Doctor> &storage)
{
    std::ifstream file;
    char line[MAX_LINE_BUFFER];
    char *fields[MAX_DOCTOR_FIELDS];
    int fieldCount;

    if (!FilePathHelper::openInputDataFile(file, "doctors.txt"))
    {
        return;
    }

    for (int i = 0; i < MAX_DOCTOR_FIELDS; i++)
    {
        fields[i] = new char[MAX_FIELD_BUFFER];
    }
    file.getline(line, MAX_LARGE_LINE_BUFFER);
    while (file.getline(line, MAX_LINE_BUFFER))
    {
        DataHelper::splitByComma(line, fields, MAX_DOCTOR_FIELDS, fieldCount);

        if (fieldCount == MAX_DOCTOR_FIELDS)
        {
            Doctor *doctor = new Doctor(
                ConversionHelper::stringToInt(fields[0]),
                fields[1],
                fields[4],
                fields[2],
                fields[3],
                ConversionHelper::stringToDouble(fields[5]));
            storage.add(*doctor);
            delete doctor;
        }
    }

    for (int i = 0; i < MAX_DOCTOR_FIELDS; i++)
    {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadAdmin(Storage<Admin> &storage)
{
    std::ifstream file;
    char line[MAX_LINE_BUFFER];
    char *fields[MAX_ADMIN_FIELDS];
    int fieldCount;

    if (!FilePathHelper::openInputDataFile(file, "admin.txt"))
    {
        return;
    }

    for (int i = 0; i < MAX_ADMIN_FIELDS; i++)
    {
        fields[i] = new char[MAX_FIELD_BUFFER];
    }

    file.getline(line, MAX_LINE_BUFFER);

    while (file.getline(line, MAX_LINE_BUFFER))
    {
        DataHelper::splitByComma(line, fields, MAX_ADMIN_FIELDS, fieldCount);

        if (fieldCount == MAX_ADMIN_FIELDS)
        {
            Admin *admin = new Admin(
                ConversionHelper::stringToInt(fields[0]),
                fields[1],
                fields[2]);
            storage.add(*admin);
            delete admin;
        }
    }

    for (int i = 0; i < MAX_ADMIN_FIELDS; i++)
    {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadAppointments(Storage<Appointment> &storage)
{
    std::ifstream file;
    char line[MAX_LINE_BUFFER];
    char *fields[MAX_APPOINTMENT_FIELDS];
    int fieldCount;

    if (!FilePathHelper::openInputDataFile(file, "appointments.txt"))
    {
        return;
    }

    for (int i = 0; i < MAX_APPOINTMENT_FIELDS; i++)
    {
        fields[i] = new char[MAX_FIELD_BUFFER];
    }
    // skip header line
    file.getline(line, MAX_LINE_BUFFER);

    while (file.getline(line, MAX_LINE_BUFFER))
    {
        DataHelper::splitByComma(line, fields, MAX_APPOINTMENT_FIELDS, fieldCount);

        if (fieldCount == MAX_APPOINTMENT_FIELDS)
        {
            Appointment *appointment = new Appointment(
                ConversionHelper::stringToInt(fields[0]),
                ConversionHelper::stringToInt(fields[1]),
                ConversionHelper::stringToInt(fields[2]),
                fields[3],
                fields[4],
                fields[5]);
            storage.add(*appointment);
            delete appointment;
        }
    }

    for (int i = 0; i < MAX_APPOINTMENT_FIELDS; i++)
    {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadBills(Storage<Bill> &storage)
{
    std::ifstream file;
    char line[MAX_LINE_BUFFER];
    char *fields[MAX_BILL_FIELDS];
    int fieldCount;

    if (!FilePathHelper::openInputDataFile(file, "bills.txt"))
    {
        return;
    }

    for (int i = 0; i < MAX_BILL_FIELDS; i++)
    {
        fields[i] = new char[MAX_FIELD_BUFFER];
    }
    // skip header line
    file.getline(line, MAX_LINE_BUFFER);

    while (file.getline(line, MAX_LINE_BUFFER))
    {
        DataHelper::splitByComma(line, fields, MAX_BILL_FIELDS, fieldCount);

        if (fieldCount == MAX_BILL_FIELDS)
        {
            Bill *bill = new Bill(
                ConversionHelper::stringToInt(fields[0]),
                ConversionHelper::stringToInt(fields[1]),
                ConversionHelper::stringToInt(fields[2]),
                ConversionHelper::stringToDouble(fields[3]),
                fields[4],
                fields[5]);
            storage.add(*bill);
            delete bill;
        }
    }

    for (int i = 0; i < MAX_BILL_FIELDS; i++)
    {
        delete[] fields[i];
    }

    file.close();
}

void FileHandler::loadPrescriptions(Storage<Prescription> &storage)
{
    std::ifstream file;
    char line[MAX_LARGE_LINE_BUFFER];
    char *fields[MAX_PRESCRIPTION_FIELDS];
    int fieldCount;

    if (!FilePathHelper::openInputDataFile(file, "prescriptions.txt"))
    {
        return;
    }

    for (int i = 0; i < MAX_PRESCRIPTION_FIELDS; i++)
    {
        fields[i] = new char[MAX_LARGE_FIELD_BUFFER];
    }

    file.getline(line, MAX_LARGE_LINE_BUFFER);

    while (file.getline(line, MAX_LARGE_LINE_BUFFER))
    {
        DataHelper::splitByComma(line, fields, MAX_PRESCRIPTION_FIELDS, fieldCount);

        if (fieldCount == MAX_PRESCRIPTION_FIELDS)
        {
            Prescription *prescription = new Prescription(
                ConversionHelper::stringToInt(fields[0]),
                ConversionHelper::stringToInt(fields[1]),
                ConversionHelper::stringToInt(fields[2]),
                ConversionHelper::stringToInt(fields[3]),
                fields[4],
                fields[5],
                fields[6]);
            storage.add(*prescription);
            delete prescription;
        }
    }

    for (int i = 0; i < MAX_PRESCRIPTION_FIELDS; i++)
    {
        delete[] fields[i];
    }

    file.close();
}

int FileHandler::loadSecurityLogLines(char *lines, int maxItems, int lineLength)
{
    std::ifstream file;
    char line[MAX_LINE_BUFFER];
    int count;
    int sourceIndex;
    int destinationIndex;
    char *destination;

    if (lines == nullptr || maxItems <= 0 || lineLength <= 1)
    {
        return 0;
    }

    if (!FilePathHelper::openInputDataFile(file, "security_log.txt"))
    {
        return 0;
    }

    count = 0;
    while (file.getline(line, MAX_LINE_BUFFER) && count < maxItems)
    {
        if (line[0] == '\0' || StringHelper::textEquals(line, "timestamp,role,entered_id,result"))
        {
            continue;
        }

        destination = lines + (count * lineLength);
        sourceIndex = 0;
        destinationIndex = 0;
        while (line[sourceIndex] != '\0' && destinationIndex < lineLength - 1)
        {
            if (line[sourceIndex] == ',')
            {
                if (destinationIndex >= lineLength - 3)
                {
                    break;
                }
                destination[destinationIndex] = ' ';
                destination[destinationIndex + 1] = '|';
                destination[destinationIndex + 2] = ' ';
                destinationIndex += 3;
            }
            else
            {
                destination[destinationIndex] = line[sourceIndex];
                destinationIndex++;
            }
            sourceIndex++;
        }
        destination[destinationIndex] = '\0';
        count++;
    }

    file.close();
    return count;
}

void FileHandler::saveSecurityLogEntry(const char *timestamp, const char *role, const char *enteredID, const char *result)
{
    std::ofstream file;

    if (timestamp == nullptr || role == nullptr || enteredID == nullptr || result == nullptr)
    {
        return;
    }

    if (!FilePathHelper::openOutputDataFile(file, "security_log.txt", std::ios::app))
    {
        return;
    }

    file << timestamp << "," << role << "," << enteredID << "," << result << "\n";
    file.close();
}

void FileHandler::savePatient(const Patient &patient, bool append)
{
    std::ofstream file;
    char amountBuffer[32];

    if (append)
    {
        FilePathHelper::openOutputDataFile(file, "patients.txt", std::ios::app);
    }
    else
    {
        FilePathHelper::openOutputDataFile(file, "patients.txt", std::ios::out);
    }

    if (!file.is_open())
    {
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

void FileHandler::saveDoctor(const Doctor &doctor, bool append)
{
    std::ofstream file;
    char feeBuffer[32];
    const char *safeName;
    const char *safeSpecialization;
    const char *safeContact;
    const char *safePassword;

    if (append)
    {
        FilePathHelper::openOutputDataFile(file, "doctors.txt", std::ios::app);
    }
    else
    {
        FilePathHelper::openOutputDataFile(file, "doctors.txt", std::ios::out);
    }

    if (!file.is_open())
    {
        return;
    }

    ConversionHelper::doubleToString(doctor.getFee(), feeBuffer);

    safeName = doctor.getName() != nullptr ? doctor.getName() : "";
    safeSpecialization = doctor.getSpecialization() != nullptr ? doctor.getSpecialization() : "";
    safeContact = doctor.getContact() != nullptr ? doctor.getContact() : "";
    safePassword = doctor.getPassword() != nullptr ? doctor.getPassword() : "";

    file << doctor.getID() << ","
         << safeName << ","
         << safeSpecialization << ","
         << safeContact << ","
         << safePassword << ","
         << feeBuffer << "\n";

    file.close();
}

void FileHandler::saveAdmin(const Admin &admin, bool append)
{
    std::ofstream file;

    if (append)
    {
        FilePathHelper::openOutputDataFile(file, "admin.txt", std::ios::app);
    }
    else
    {
        FilePathHelper::openOutputDataFile(file, "admin.txt", std::ios::out);
    }

    if (!file.is_open())
    {
        return;
    }

    file << admin.getID() << ","
         << admin.getName() << ","
         << admin.getPassword() << "\n";

    file.close();
}

void FileHandler::saveAppointment(const Appointment &appointment, bool append)
{
    std::ofstream file;

    if (append)
    {
        FilePathHelper::openOutputDataFile(file, "appointments.txt", std::ios::app);
    }
    else
    {
        FilePathHelper::openOutputDataFile(file, "appointments.txt", std::ios::out);
    }

    if (!file.is_open())
    {
        return;
    }

    file << appointment.getID() << ","
         << appointment.getPatientID() << ","
         << appointment.getDoctorID() << ","
         << appointment.getDate() << ","
         << appointment.getTimeSlot() << ","
         << appointment.getStatus() << "\n";

    file.close();
}

void FileHandler::saveBill(const Bill &bill, bool append)
{
    std::ofstream file;
    char amountBuffer[32];

    if (append)
    {
        FilePathHelper::openOutputDataFile(file, "bills.txt", std::ios::app);
    }
    else
    {
        FilePathHelper::openOutputDataFile(file, "bills.txt", std::ios::out);
    }

    if (!file.is_open())
    {
        return;
    }

    ConversionHelper::doubleToString(bill.getAmount(), amountBuffer);

    file << bill.getID() << ","
         << bill.getPatientID() << ","
         << bill.getAppointmentID() << ","
         << amountBuffer << ","
         << bill.getStatus() << ","
         << bill.getDate() << "\n";

    file.close();
}

void FileHandler::savePrescription(const Prescription &prescription, bool append)
{
    std::ofstream file;

    if (append)
    {
        FilePathHelper::openOutputDataFile(file, "prescriptions.txt", std::ios::app);
    }
    else
    {
        FilePathHelper::openOutputDataFile(file, "prescriptions.txt", std::ios::out);
    }

    if (!file.is_open())
    {
        return;
    }

    file << prescription.getID() << ","
         << prescription.getAppointmentID() << ","
         << prescription.getPatientID() << ","
         << prescription.getDoctorID() << ","
         << prescription.getDate() << ","
         << prescription.getMedicines() << ","
         << prescription.getNotes() << "\n";

    file.close();
}

void FileHandler::saveDischargedPatient(const Patient &patient, bool append)
{
    std::ofstream file;
    char amountBuffer[32];

    if (append)
    {
        FilePathHelper::openOutputDataFile(file, "discharged.txt", std::ios::app);
    }
    else
    {
        FilePathHelper::openOutputDataFile(file, "discharged.txt", std::ios::out);
    }

    if (!file.is_open())
    {
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

void FileHandler::saveAllPatients(Storage<Patient> &storage)
{
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "patients.txt", std::ios::out))
    {
        file << "patient_id,name,age,gender,contact,password,balance\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++)
    {
        savePatient(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllDoctors(Storage<Doctor> &storage)
{
    std::ofstream file;
    int i;
    char feeBuffer[32];
    const char *safeName;
    const char *safeSpecialization;
    const char *safeContact;
    const char *safePassword;

    if (FilePathHelper::openOutputDataFile(file, "doctors.txt", std::ios::out))
    {
        file << "doctor_id,name,specialization,contact,password,fee\n";
        for (i = 0; i < storage.size(); i++)
        {
            ConversionHelper::doubleToString(storage.getAll()[i].getFee(), feeBuffer);
            safeName = storage.getAll()[i].getName() != nullptr ? storage.getAll()[i].getName() : "";
            safeSpecialization = storage.getAll()[i].getSpecialization() != nullptr ? storage.getAll()[i].getSpecialization() : "";
            safeContact = storage.getAll()[i].getContact() != nullptr ? storage.getAll()[i].getContact() : "";
            safePassword = storage.getAll()[i].getPassword() != nullptr ? storage.getAll()[i].getPassword() : "";

            file << storage.getAll()[i].getID() << ","
                 << safeName << ","
                 << safeSpecialization << ","
                 << safeContact << ","
                 << safePassword << ","
                 << feeBuffer << "\n";
        }
        file.close();
    }
}

void FileHandler::saveAllAdmins(Storage<Admin> &storage)
{
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "admin.txt", std::ios::out))
    {
        file << "admin_id,name,password\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++)
    {
        saveAdmin(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllAppointments(Storage<Appointment> &storage)
{
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "appointments.txt", std::ios::out))
    {
        file << "appointment_id,patient_id,doctor_id,date,time,status\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++)
    {
        saveAppointment(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllBills(Storage<Bill> &storage)
{
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "bills.txt", std::ios::out))
    {
        file << "bill_id,patient_id,appointment_id,amount,status,date\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++)
    {
        saveBill(storage.getAll()[i], true);
    }
}

void FileHandler::saveAllPrescriptions(Storage<Prescription> &storage)
{
    std::ofstream file;
    int i;

    // Truncate and write header
    if (FilePathHelper::openOutputDataFile(file, "prescriptions.txt", std::ios::out))
    {
        file << "prescription_id,appointment_id,patient_id,doctor_id,date,medicines,notes\n";
        file.close();
    }

    for (i = 0; i < storage.size(); i++)
    {
        savePrescription(storage.getAll()[i], true);
    }
}
