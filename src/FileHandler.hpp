#pragma once

#include "Storage.hpp"
#include "Patient.hpp"
#include "Doctor.hpp"
#include "Admin.hpp"
#include "Appointment.hpp"
#include "Bill.hpp"
#include "Prescription.hpp"
#include "helpers/StringHelper.hpp"
#include "helpers/ConversionHelper.hpp"
#include "helpers/FilePathHelper.hpp"
#include "helpers/DataHelper.hpp"

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
    static void saveDischargedPatient(const Patient& patient, bool append = true);

    static void saveAllPatients(Storage<Patient>& storage);
    static void saveAllDoctors(Storage<Doctor>& storage);
    static void saveAllAdmins(Storage<Admin>& storage);
    static void saveAllAppointments(Storage<Appointment>& storage);
    static void saveAllBills(Storage<Bill>& storage);
    static void saveAllPrescriptions(Storage<Prescription>& storage);
};
