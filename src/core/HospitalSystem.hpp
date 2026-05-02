#pragma once

#include <iostream>

#include "../entities/Admin.hpp"
#include "../entities/Appointment.hpp"
#include "../entities/Bill.hpp"
#include "../entities/Doctor.hpp"
#include "FileHandler.hpp"
#include "HospitalException.hpp"
#include "../entities/Patient.hpp"
#include "../entities/Prescription.hpp"
#include "../entities/Person.hpp"
#include "../entities/Storage.hpp"
#include "Validator.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/ConversionHelper.hpp"

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
    double cancelAppointment(Patient* patient, int appointmentID);
    void payBill(Patient* patient, int billID);
    void dischargePatient(int patientID);

    int getNextPatientID();
    Storage<Doctor>* getDoctorsBySpecialization(const char* specialization);

    Storage<Patient>& getPatients();
    Storage<Doctor>& getDoctors();
    Storage<Admin>& getAdmins();
    Storage<Appointment>& getAppointments();
    Storage<Bill>& getBills();
    Storage<Prescription>& getPrescriptions();
};