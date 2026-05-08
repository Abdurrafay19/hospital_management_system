#include "HospitalSystem.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/TimeHelper.hpp"

HospitalSystem::HospitalSystem()
{
    failedLoginAttempts = 0;
    sessionLocked = false;

    FileHandler::loadPatients(patients);
    FileHandler::loadDoctors(doctors);
    FileHandler::loadAdmin(admins);
    FileHandler::loadAppointments(appointments);
    FileHandler::loadBills(bills);
    FileHandler::loadPrescriptions(prescriptions);
}

Person *HospitalSystem::login(const char *id, const char *password, const char *unused, Role role)
{
    Patient *patient;
    Doctor *doctor;
    Admin *admin;
    int userID;

    if (sessionLocked)
    {
        std::cout << "Account locked. Contact admin.\n";
        return nullptr;
    }

    patient = nullptr;
    doctor = nullptr;
    admin = nullptr;

    userID = ConversionHelper::toInt(id);

    if (role == ROLE_PATIENT)
    {
        patient = patients.findByID(userID);
        if (patient != nullptr && StringHelper::textEquals(patient->getPassword(), password))
        {
            failedLoginAttempts = 0;
            return patient;
        }
    }
    else if (role == ROLE_DOCTOR)
    {
        doctor = doctors.findByID(userID);
        if (doctor != nullptr && StringHelper::textEquals(doctor->getPassword(), password))
        {
            failedLoginAttempts = 0;
            return doctor;
        }
    }
    else if (role == ROLE_ADMIN)
    {
        admin = admins.findByID(userID);
        if (admin != nullptr && StringHelper::textEquals(admin->getPassword(), password))
        {
            failedLoginAttempts = 0;
            return admin;
        }
    }

    failedLoginAttempts++;
    if (failedLoginAttempts >= 3)
    {
        sessionLocked = true;
        std::cout << "Account locked. Contact admin.\n";
    }

    return nullptr;
}

void HospitalSystem::bookAppointment(Patient *patient, int doctorID, const char *date, const char *timeSlot)
{
    Doctor *doctor;
    Appointment *appointmentsArray;
    Appointment candidate;
    Appointment newAppointment;
    Bill newBill;
    int newAppointmentID;
    int newBillID;
    int i;

    if (patient == nullptr || date == nullptr || timeSlot == nullptr)
    {
        throw InvalidInputException();
    }

    if (!Validator::isValidDate(date))
    {
        throw InvalidInputException("Invalid appointment date.");
    }

    if (!TimeHelper::isDateAfterToday(date))
    {
        throw InvalidInputException("Appointment date must be after today.");
    }

    doctor = doctors.findByID(doctorID);
    if (doctor == nullptr)
    {
        throw InvalidInputException("Doctor not found.");
    }

    if (patient->getBalance() < doctor->getFee())
    {
        throw InsufficientFundsException();
    }

    candidate = Appointment(1, patient->getID(), doctorID, date, timeSlot, "pending");
    appointmentsArray = appointments.getAll();
    for (i = 0; i < appointments.size(); i++)
    {
        if (appointmentsArray[i] == candidate)
        {
            throw SlotUnavailableException();
        }
    }

    newAppointmentID = StorageHelper::nextIDFromStorage(appointments);
    newBillID = StorageHelper::nextIDFromStorage(bills);

    newAppointment = Appointment(newAppointmentID, patient->getID(), doctorID, date, timeSlot, "pending");
    appointments.add(newAppointment);

    newBill = Bill(newBillID, patient->getID(), newAppointmentID, doctor->getFee(), "unpaid", date);
    bills.add(newBill);

    FileHandler::saveAllPatients(patients);
    FileHandler::saveAllAppointments(appointments);
    FileHandler::saveAllBills(bills);
}

double HospitalSystem::cancelAppointment(Patient *patient, int appointmentID)
{
    Appointment *appointment;
    Doctor *doctor;
    Bill *bill;
    int i;
    double fee;

    if (patient == nullptr)
    {
        throw InvalidInputException();
    }

    appointment = appointments.findByID(appointmentID);
    if (appointment == nullptr || appointment->getPatientID() != patient->getID() || !StringHelper::textEquals(appointment->getStatus(), "pending"))
    {
        throw InvalidInputException("Invalid appointment ID.");
    }

    doctor = doctors.findByID(appointment->getDoctorID());
    if (doctor == nullptr)
    {
        throw InvalidInputException("Invalid appointment ID.");
    }

    bill = nullptr;
    for (i = 0; i < bills.size(); i++)
    {
        if (bills.getAll()[i].getPatientID() == patient->getID() && bills.getAll()[i].getAppointmentID() == appointmentID)
        {
            bill = &bills.getAll()[i];
            break;
        }
    }

    if (bill == nullptr)
    {
        throw InvalidInputException("Invalid appointment ID.");
    }

    fee = doctor->getFee();
    if (StringHelper::textEquals(bill->getStatus(), "paid"))
    {
        *patient += fee;
    }
    else
    {
        fee = 0;
    }
    appointment->setStatus("cancelled");
    bill->setStatus("cancelled");

    FileHandler::saveAllPatients(patients);
    FileHandler::saveAllAppointments(appointments);
    FileHandler::saveAllBills(bills);

    return fee;
}

void HospitalSystem::payBill(Patient *patient, int billID)
{
    Bill *bill;

    if (patient == nullptr)
    {
        throw InvalidInputException();
    }

    bill = bills.findByID(billID);
    if (bill == nullptr || bill->getPatientID() != patient->getID())
    {
        throw InvalidInputException("Bill not found for this patient.");
    }

    if (!StringHelper::textEquals(bill->getStatus(), "unpaid"))
    {
        throw InvalidInputException("Bill is not unpaid.");
    }

    if (patient->getBalance() < bill->getAmount())
    {
        throw InsufficientFundsException();
    }

    *patient -= bill->getAmount();
    bill->setStatus("paid");

    FileHandler::saveAllPatients(patients);
    FileHandler::saveAllBills(bills);
}

void HospitalSystem::topUpBalance(Patient *patient, double amount)
{
    if (patient == nullptr)
    {
        throw InvalidInputException();
    }

    if (amount <= 0.0)
    {
        throw InvalidInputException("Amount must be greater than 0.");
    }

    *patient += amount;
    FileHandler::saveAllPatients(patients);
}

void HospitalSystem::dischargePatient(int patientID)
{
    Patient *patient;
    int appointmentIDs[100];
    int billIDs[100];
    int prescriptionIDs[100];
    int appointmentCount;
    int billCount;
    int prescriptionCount;
    int i;

    patient = patients.findByID(patientID);
    if (patient == nullptr)
    {
        throw InvalidInputException("Patient not found.");
    }

    appointmentCount = 0;
    billCount = 0;
    prescriptionCount = 0;

    for (i = 0; i < appointments.size(); i++)
    {
        if (appointments.getAll()[i].getPatientID() == patientID && StringHelper::textEquals(appointments.getAll()[i].getStatus(), "pending"))
        {
            throw InvalidInputException("Patient has pending appointments.");
        }
        if (appointments.getAll()[i].getPatientID() == patientID)
        {
            appointmentIDs[appointmentCount] = appointments.getAll()[i].getID();
            appointmentCount++;
        }
    }

    for (i = 0; i < bills.size(); i++)
    {
        if (bills.getAll()[i].getPatientID() == patientID && !StringHelper::textEquals(bills.getAll()[i].getStatus(), "paid"))
        {
            throw InvalidInputException("Patient has unpaid bills.");
        }
        if (bills.getAll()[i].getPatientID() == patientID)
        {
            billIDs[billCount] = bills.getAll()[i].getID();
            billCount++;
        }
    }

    for (i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptions.getAll()[i].getPatientID() == patientID)
        {
            prescriptionIDs[prescriptionCount] = prescriptions.getAll()[i].getID();
            prescriptionCount++;
        }
    }

    FileHandler::saveDischargedPatient(*patient, true);

    for (i = appointmentCount - 1; i >= 0; i--)
    {
        appointments.removeByID(appointmentIDs[i]);
    }

    for (i = billCount - 1; i >= 0; i--)
    {
        bills.removeByID(billIDs[i]);
    }

    for (i = prescriptionCount - 1; i >= 0; i--)
    {
        prescriptions.removeByID(prescriptionIDs[i]);
    }

    patients.removeByID(patientID);

    FileHandler::saveAllPatients(patients);
    FileHandler::saveAllAppointments(appointments);
    FileHandler::saveAllBills(bills);
    FileHandler::saveAllPrescriptions(prescriptions);
}

int HospitalSystem::getNextPatientID()
{
    return StorageHelper::nextIDFromStorage(patients);
}

Storage<Doctor> *HospitalSystem::getDoctorsBySpecialization(const char *specialization)
{
    Storage<Doctor> *result;
    Doctor *allDoctors;
    int i;

    if (specialization == nullptr || StringHelper::stringLength(specialization) == 0)
    {
        return nullptr;
    }

    result = new Storage<Doctor>();
    allDoctors = doctors.getAll();

    for (i = 0; i < doctors.size(); i++)
    {
        if (StringHelper::textEqualsIgnoreCase(allDoctors[i].getSpecialization(), specialization))
        {
            result->add(allDoctors[i]);
        }
    }

    return result;
}

Storage<Patient> &HospitalSystem::getPatients()
{
    return patients;
}

Storage<Doctor> &HospitalSystem::getDoctors()
{
    return doctors;
}

Storage<Admin> &HospitalSystem::getAdmins()
{
    return admins;
}

Storage<Appointment> &HospitalSystem::getAppointments()
{
    return appointments;
}

Storage<Bill> &HospitalSystem::getBills()
{
    return bills;
}

Storage<Prescription> &HospitalSystem::getPrescriptions()
{
    return prescriptions;
}
