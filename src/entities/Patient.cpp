#include "Patient.hpp"

#include "../core/Validator.hpp"
#include "../helpers/StringHelper.hpp"

Patient::Patient() : Person()
{
    age = 0;
    gender = 0;
    contact = 0;
    balance = 0;
}

Patient::Patient(int patientID,
                 const char *patientName,
                 const char *patientPassword,
                 int patientAge,
                 const char *patientGender,
                 const char *patientContact,
                 double patientBalance)
    : Person(patientID, patientName, patientPassword)
{
    age = 0;
    gender = 0;
    contact = 0;
    balance = 0;

    setAge(patientAge);
    setGender(patientGender);
    setContact(patientContact);

    if (patientBalance > 0)
    {
        balance = patientBalance;
    }
}

Patient::Patient(const Patient &other) : Person(other)
{
    age = other.age;
    gender = 0;
    contact = 0;
    balance = other.balance;

    StringHelper::copyTextDynamic(gender, other.gender);
    StringHelper::copyTextDynamic(contact, other.contact);
}

Patient::~Patient()
{
    delete[] gender;
    delete[] contact;
    gender = 0;
    contact = 0;
}

Patient &Patient::operator=(const Patient &other)
{
    if (this != &other)
    {
        Person::operator=(other);
        age = other.age;
        balance = other.balance;
        StringHelper::copyTextDynamic(gender, other.gender);
        StringHelper::copyTextDynamic(contact, other.contact);
    }

    return *this;
}

void Patient::displayDashboard()
{
    std::cout << "Patient Dashboard - ID: " << id << "\n";
}

void Patient::showProfile() const
{
    std::cout << *this << "\n";
}

int Patient::getAge() const
{
    return age;
}

const char *Patient::getGender() const
{
    return gender;
}

const char *Patient::getContact() const
{
    return contact;
}

double Patient::getBalance() const
{
    return balance;
}

void Patient::setAge(int patientAge)
{
    if (patientAge > 0)
    {
        age = patientAge;
    }
}

void Patient::setGender(const char *patientGender)
{
    StringHelper::copyTextDynamic(gender, patientGender);
}

bool Patient::setContact(const char *patientContact)
{
    if (!Validator::isValidContact(patientContact))
    {
        return false;
    }

    StringHelper::copyTextDynamic(contact, patientContact);
    return true;
}

Patient &Patient::operator+=(double amount)
{
    if (amount > 0)
    {
        balance = balance + amount;
    }
    return *this;
}

Patient &Patient::operator-=(double amount)
{
    if (amount > 0 && amount <= balance)
    {
        balance = balance - amount;
    }
    return *this;
}

bool Patient::operator==(const Patient &other) const
{
    return id == other.id;
}

std::ostream &operator<<(std::ostream &out, const Patient &patient)
{
    out << "Patient[ID=" << patient.id
        << ", Name=" << patient.name
        << ", Age=" << patient.age
        << ", Gender=" << patient.gender
        << ", Contact=" << patient.contact
        << ", Balance=" << patient.balance
        << "]";

    return out;
}
