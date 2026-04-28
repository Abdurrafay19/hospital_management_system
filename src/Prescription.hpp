#pragma once

#include <iostream>

class Prescription {
private:
    int prescriptionID;
    int appointmentID;
    int patientID;
    int doctorID;
    char* date;
    char* medicines;
    char* notes;

public:
    Prescription();
    Prescription(int newPrescriptionID,
                 int newAppointmentID,
                 int newPatientID,
                 int newDoctorID,
                 const char* newDate,
                 const char* newMedicines,
                 const char* newNotes);
    Prescription(const Prescription& other);
    ~Prescription();

    Prescription& operator=(const Prescription& other);

    int getPrescriptionID() const;
    int getID() const;
    int getAppointmentID() const;
    int getPatientID() const;
    int getDoctorID() const;
    const char* getDate() const;
    const char* getMedicines() const;
    const char* getNotes() const;

    void setPrescriptionID(int newPrescriptionID);
    void setAppointmentID(int newAppointmentID);
    void setPatientID(int newPatientID);
    void setDoctorID(int newDoctorID);
    void setDate(const char* newDate);
    void setMedicines(const char* newMedicines);
    void setNotes(const char* newNotes);

    bool operator==(const Prescription& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Prescription& prescription);
};
