#pragma once

#include <iostream>

#include "Admin.hpp"
#include "Appointment.hpp"
#include "Bill.hpp"
#include "Doctor.hpp"
#include "FileHandler.hpp"
#include "HospitalException.hpp"
#include "Patient.hpp"
#include "Prescription.hpp"
#include "Person.hpp"
#include "Storage.hpp"
#include "Validator.hpp"
#include "helpers/StringHelper.hpp"
#include "helpers/ConversionHelper.hpp"

enum Role {
    ROLE_PATIENT,
    ROLE_DOCTOR,
    ROLE_ADMIN
};

class HospitalSystem {
private:
    Storage<Patient> patients;
    Storage<Doctor> doctors;
    Storage<Admin> admins;
    Storage<Appointment> appointments;
    Storage<Bill> bills;
    Storage<Prescription> prescriptions;
    int failedLoginAttempts;
    bool sessionLocked;

    static int nextIDFromPatients(Storage<Patient>& storage);
    static int nextIDFromDoctors(Storage<Doctor>& storage);
    static int nextIDFromAdmins(Storage<Admin>& storage);
    static int nextIDFromAppointments(Storage<Appointment>& storage);
    static int nextIDFromBills(Storage<Bill>& storage);
    static int nextIDFromPrescriptions(Storage<Prescription>& storage);

public:
    HospitalSystem();

    Person* login(const char* name, const char* contact, const char* password, Role role);
    void bookAppointment(Patient* patient, int doctorID, const char* date, const char* timeSlot);
    void payBill(Patient* patient, int billID);
    void dischargePatient(int patientID);

    int getNextPatientID();

    Storage<Patient>& getPatients();
    Storage<Doctor>& getDoctors();
    Storage<Admin>& getAdmins();
    Storage<Appointment>& getAppointments();
    Storage<Bill>& getBills();
    Storage<Prescription>& getPrescriptions();
};