#pragma once

#include <iostream>

class Appointment
{
private:
    int appointmentID;
    int patientID;
    int doctorID;
    char *date;
    char *timeSlot;
    char *status;

public:
    Appointment();
    Appointment(int newAppointmentID,
                int newPatientID,
                int newDoctorID,
                const char *newDate,
                const char *newTimeSlot,
                const char *newStatus);
    Appointment(const Appointment &other);
    ~Appointment();

    Appointment &operator=(const Appointment &other);

    int getAppointmentID() const;
    int getID() const;
    int getPatientID() const;
    int getDoctorID() const;
    const char *getDate() const;
    const char *getTimeSlot() const;
    const char *getStatus() const;

    void setAppointmentID(int newAppointmentID);
    void setPatientID(int newPatientID);
    void setDoctorID(int newDoctorID);
    void setDate(const char *newDate);
    void setTimeSlot(const char *newTimeSlot);
    void setStatus(const char *newStatus);

    bool isCancelled() const;
    bool operator==(const Appointment &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Appointment &appointment);
};
