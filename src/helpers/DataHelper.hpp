#pragma once

#include "../entities/Storage.hpp"
#include "../entities/Patient.hpp"
#include "../entities/Doctor.hpp"
#include "../entities/Appointment.hpp"
#include "../entities/Bill.hpp"

class DataHelper
{
public:
    static void splitByComma(const char *line, char **fields, int maxFields, int &fieldCount);
    static bool isLeapYear(int year);
    static int countUnpaidBillsForPatient(Storage<Bill> *bills, int patientID);
    static const char *findPatientName(Storage<Patient> *patients, int patientID);
    static const char *findDoctorName(Storage<Doctor> *doctors, int doctorID);
    static int compareAppointmentPointersByDateDesc(const Appointment *left, const Appointment *right);
    static void sortAppointmentPointersByDateDesc(Appointment *items[], int count);
};
