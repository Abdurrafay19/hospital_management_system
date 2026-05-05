#include "DataHelper.hpp"
#include "../entities/Appointment.hpp"
#include "../entities/Patient.hpp"
#include "../entities/Doctor.hpp"
#include "../entities/Bill.hpp"
#include "../entities/Storage.hpp"
#include "TimeHelper.hpp"
#include "StringHelper.hpp"

#include <stddef.h>

void DataHelper::splitByComma(const char *line, char **fields, int maxFields, int &fieldCount)
{
    int currentField;
    int charIndex;
    int fieldCharIndex;
    char currentBuffer[300];

    if (line == nullptr)
    {
        fieldCount = 0;
        return;
    }

    currentField = 0;
    charIndex = 0;
    fieldCharIndex = 0;

    while (line[charIndex] != '\0' && currentField < maxFields)
    {
        if (line[charIndex] == ',')
        {
            currentBuffer[fieldCharIndex] = '\0';
            fields[currentField] = new char[fieldCharIndex + 1];
            int i = 0;
            while (currentBuffer[i] != '\0')
            {
                fields[currentField][i] = currentBuffer[i];
                i++;
            }
            fields[currentField][i] = '\0';

            currentField++;
            fieldCharIndex = 0;
        }
        else
        {
            currentBuffer[fieldCharIndex] = line[charIndex];
            fieldCharIndex++;
        }
        charIndex++;
    }

    if (currentField < maxFields && fieldCharIndex > 0)
    {
        currentBuffer[fieldCharIndex] = '\0';
        fields[currentField] = new char[fieldCharIndex + 1];
        int i = 0;
        while (currentBuffer[i] != '\0')
        {
            fields[currentField][i] = currentBuffer[i];
            i++;
        }
        fields[currentField][i] = '\0';
        currentField++;
    }

    fieldCount = currentField;
}

bool DataHelper::isLeapYear(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }

    if (year % 100 == 0)
    {
        return false;
    }

    if (year % 4 == 0)
    {
        return true;
    }

    return false;
}

int DataHelper::countUnpaidBillsForPatient(Storage<Bill> *bills, int patientID)
{
    int i;
    int count;

    count = 0;
    if (bills == nullptr)
    {
        return 0;
    }

    for (i = 0; i < bills->size(); i++)
    {
        if (bills->getAll()[i].getPatientID() == patientID && StringHelper::textEquals(bills->getAll()[i].getStatus(), "unpaid"))
        {
            count++;
        }
    }

    return count;
}

const char *DataHelper::findPatientName(Storage<Patient> *patients, int patientID)
{
    Patient *patient;

    if (patients == nullptr)
    {
        return "";
    }

    patient = patients->findByID(patientID);
    if (patient == nullptr)
    {
        return "";
    }

    return patient->getName();
}

const char *DataHelper::findDoctorName(Storage<Doctor> *doctors, int doctorID)
{
    Doctor *doctor;

    if (doctors == nullptr)
    {
        return "";
    }

    doctor = doctors->findByID(doctorID);
    if (doctor == nullptr)
    {
        return "";
    }

    return doctor->getName();
}

int DataHelper::compareAppointmentPointersByDateDesc(const Appointment *left, const Appointment *right)
{
    int dateCompare;

    if (left == nullptr && right == nullptr)
    {
        return 0;
    }
    if (left == nullptr)
    {
        return 1;
    }
    if (right == nullptr)
    {
        return -1;
    }

    dateCompare = TimeHelper::compareDates(left->getDate(), right->getDate());
    if (dateCompare != 0)
    {
        return -dateCompare;
    }

    return TimeHelper::compareTimeSlotsAscending(left->getTimeSlot(), right->getTimeSlot());
}

void DataHelper::sortAppointmentPointersByDateDesc(Appointment *items[], int count)
{
    int pass;
    int index;
    Appointment *temp;

    for (pass = 0; pass < count - 1; pass++)
    {
        for (index = 0; index < count - 1 - pass; index++)
        {
            if (compareAppointmentPointersByDateDesc(items[index], items[index + 1]) > 0)
            {
                temp = items[index];
                items[index] = items[index + 1];
                items[index + 1] = temp;
            }
        }
    }
}
