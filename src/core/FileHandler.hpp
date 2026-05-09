#pragma once

#include "../entities/Storage.hpp"
#include "../entities/Patient.hpp"
#include "../entities/Doctor.hpp"
#include "../entities/Admin.hpp"
#include "../entities/Appointment.hpp"
#include "../entities/Bill.hpp"
#include "../entities/Prescription.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"
#include "../helpers/FilePathHelper.hpp"
#include "../helpers/DataHelper.hpp"
#include "Constants.hpp"

class FileHandler
{
public:
    // Load methods
    static void loadPatients(Storage<Patient> &storage);
    static void loadDoctors(Storage<Doctor> &storage);
    static void loadAdmin(Storage<Admin> &storage);
    static void loadAppointments(Storage<Appointment> &storage);
    static void loadBills(Storage<Bill> &storage);
    static void loadPrescriptions(Storage<Prescription> &storage);
    static int loadSecurityLogLines(char *lines, int maxItems, int lineLength);
    static void saveSecurityLogEntry(const char *timestamp, const char *role, const char *enteredID, const char *result);

    // Save methods (append or overwrite)
    static void savePatient(const Patient &patient, bool append = true);
    static void saveDoctor(const Doctor &doctor, bool append = true);
    static void saveAdmin(const Admin &admin, bool append = true);
    static void saveAppointment(const Appointment &appointment, bool append = true);
    static void saveBill(const Bill &bill, bool append = true);
    static void savePrescription(const Prescription &prescription, bool append = true);
    static void saveDischargedPatient(const Patient &patient, bool append = true);

    static void saveAllPatients(Storage<Patient> &storage);
    static void saveAllDoctors(Storage<Doctor> &storage);
    static void saveAllAdmins(Storage<Admin> &storage);
    static void saveAllAppointments(Storage<Appointment> &storage);
    static void saveAllBills(Storage<Bill> &storage);
    static void saveAllPrescriptions(Storage<Prescription> &storage);
};
