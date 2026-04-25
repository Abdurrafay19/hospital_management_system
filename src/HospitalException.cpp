#include "HospitalException.hpp"

HospitalException::HospitalException(const char* msg) {
	if (msg == 0) {
		message[0] = '\0';
		return;
	}

	int i = 0;
	while (msg[i] != '\0' && i < 199) {
		message[i] = msg[i];
		i++;
	}
	message[i] = '\0';
}

const char* HospitalException::what() const throw() {
	return message;
}

FileNotFoundException::FileNotFoundException(const char* msg)
	: HospitalException(msg) {
}

InsufficientFundsException::InsufficientFundsException(const char* msg)
	: HospitalException(msg) {
}

InvalidInputException::InvalidInputException(const char* msg)
	: HospitalException(msg) {
}

SlotUnavailableException::SlotUnavailableException(const char* msg)
	: HospitalException(msg) {
}
