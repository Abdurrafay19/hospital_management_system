#pragma once

#include <exception>

class HospitalException : public std::exception
{
protected:
    char message[200];

public:
    HospitalException(const char *msg);
    virtual const char *what() const throw();
};

class FileNotFoundException : public HospitalException
{
public:
    FileNotFoundException(const char *msg = "File not found.");
};

class InsufficientFundsException : public HospitalException
{
public:
    InsufficientFundsException(const char *msg = "Insufficient funds.");
};

class InvalidInputException : public HospitalException
{
public:
    InvalidInputException(const char *msg = "Invalid input.");
};

class SlotUnavailableException : public HospitalException
{
public:
    SlotUnavailableException(const char *msg = "Selected slot is unavailable.");
};
