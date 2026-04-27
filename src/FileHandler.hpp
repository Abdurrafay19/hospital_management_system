#pragma once

#include "Storage.hpp"
#include "Patient.hpp"
#include "Doctor.hpp"
#include "Admin.hpp"
#include "Appointment.hpp"
#include "Bill.hpp"
#include "Prescription.hpp"

class FileHandler {
public:
    // Load methods
    static void loadPatients(Storage<Patient>& storage);
    static void loadDoctors(Storage<Doctor>& storage);
    static void loadAdmin(Storage<Admin>& storage);
    static void loadAppointments(Storage<Appointment>& storage);
    static void loadBills(Storage<Bill>& storage);
    static void loadPrescriptions(Storage<Prescription>& storage);

    // Save methods (append or overwrite)
    static void savePatient(const Patient& patient, bool append = true);
    static void saveDoctor(const Doctor& doctor, bool append = true);
    static void saveAdmin(const Admin& admin, bool append = true);
    static void saveAppointment(const Appointment& appointment, bool append = true);
    static void saveBill(const Bill& bill, bool append = true);
    static void savePrescription(const Prescription& prescription, bool append = true);

    // Utility methods
    static void splitByComma(const char* line, char** fields, int maxFields, int& fieldCount);

private:
    static int stringToInt(const char* str);
    static double stringToDouble(const char* str);
    static void intToString(int value, char* buffer);
    static void doubleToString(double value, char* buffer);
    static int stringLength(const char* str);
    static void stringCopy(char* destination, const char* source, int maxLength);
};
