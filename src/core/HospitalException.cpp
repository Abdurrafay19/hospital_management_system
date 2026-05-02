#include "HospitalException.hpp"

HospitalException::HospitalException(const char *msg)
{
	int i = 0;
	int length = 0;

	// Calculate length if msg is not null
	if (msg != 0)
	{
		while (msg[i] != '\0')
		{
			length++;
			i++;
		}
	}

	// Allocate memory
	message = new char[length + 1];

	// Copy message
	if (msg == 0)
	{
		message[0] = '\0';
		return;
	}

	i = 0;
	while (msg[i] != '\0')
	{
		message[i] = msg[i];
		i++;
	}
	message[i] = '\0';
}

HospitalException::~HospitalException()
{
	delete[] message;
	message = 0;
}

const char *HospitalException::what() const throw()
{
	return message;
}

FileNotFoundException::FileNotFoundException(const char *msg)
	: HospitalException(msg)
{
}

InsufficientFundsException::InsufficientFundsException(const char *msg)
	: HospitalException(msg)
{
}

InvalidInputException::InvalidInputException(const char *msg)
	: HospitalException(msg)
{
}

SlotUnavailableException::SlotUnavailableException(const char *msg)
	: HospitalException(msg)
{
}
