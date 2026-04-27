#include "Bill.hpp"

#include "Validator.hpp"

static bool textEquals(const char* left, const char* right) {
    int i;

    if (left == nullptr || right == nullptr) {
        return left == right;
    }

    i = 0;
    while (left[i] != '\0' && right[i] != '\0') {
        if (left[i] != right[i]) {
            return false;
        }
        i++;
    }

    return left[i] == '\0' && right[i] == '\0';
}

Bill::Bill() {
    billID = 0;
    patientID = 0;
    appointmentID = 0;
    amount = 0.0;
    status = nullptr;
    date = nullptr;
}

Bill::Bill(int newBillID,
           int newPatientID,
           int newAppointmentID,
           double newAmount,
           const char* newStatus,
           const char* newDate) {
    billID = 0;
    patientID = 0;
    appointmentID = 0;
    amount = 0.0;
    status = nullptr;
    date = nullptr;

    setBillID(newBillID);
    setPatientID(newPatientID);
    setAppointmentID(newAppointmentID);
    setAmount(newAmount);
    setStatus(newStatus);
    setDate(newDate);
}

Bill::Bill(const Bill& other) {
    billID = 0;
    patientID = 0;
    appointmentID = 0;
    amount = 0.0;
    status = nullptr;
    date = nullptr;

    billID = other.billID;
    patientID = other.patientID;
    appointmentID = other.appointmentID;
    amount = other.amount;
    copyText(status, other.status);
    copyText(date, other.date);
}

Bill::~Bill() {
    delete[] status;
    delete[] date;

    status = nullptr;
    date = nullptr;
}

Bill& Bill::operator=(const Bill& other) {
    if (this != &other) {
        billID = other.billID;
        patientID = other.patientID;
        appointmentID = other.appointmentID;
        amount = other.amount;
        copyText(status, other.status);
        copyText(date, other.date);
    }

    return *this;
}

void Bill::copyText(char*& destination, const char* source) {
    int i;
    int length;

    delete[] destination;
    destination = nullptr;

    if (source == nullptr) {
        return;
    }

    length = 0;
    while (source[length] != '\0') {
        length++;
    }

    destination = new char[length + 1];

    i = 0;
    while (i < length) {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

int Bill::getBillID() const {
    return billID;
}

int Bill::getPatientID() const {
    return patientID;
}

int Bill::getAppointmentID() const {
    return appointmentID;
}

double Bill::getAmount() const {
    return amount;
}

const char* Bill::getStatus() const {
    return status;
}

const char* Bill::getDate() const {
    return date;
}

void Bill::setBillID(int newBillID) {
    if (Validator::isValidID(newBillID)) {
        billID = newBillID;
    }
}

void Bill::setPatientID(int newPatientID) {
    if (Validator::isValidID(newPatientID)) {
        patientID = newPatientID;
    }
}

void Bill::setAppointmentID(int newAppointmentID) {
    if (Validator::isValidID(newAppointmentID)) {
        appointmentID = newAppointmentID;
    }
}

void Bill::setAmount(double newAmount) {
    if (newAmount >= 0.0) {
        amount = newAmount;
    }
}

void Bill::setStatus(const char* newStatus) {
    copyText(status, newStatus);
}

void Bill::setDate(const char* newDate) {
    if (!Validator::isValidDate(newDate)) {
        return;
    }

    copyText(date, newDate);
}

bool Bill::isPaid() const {
    return textEquals(status, "paid");
}

bool Bill::operator==(const Bill& other) const {
    return billID == other.billID;
}

std::ostream& operator<<(std::ostream& out, const Bill& bill) {
    const char* safeStatus;
    const char* safeDate;

    safeStatus = bill.status != nullptr ? bill.status : "";
    safeDate = bill.date != nullptr ? bill.date : "";

    out << "Bill[ID=" << bill.billID
        << ", PatientID=" << bill.patientID
        << ", AppointmentID=" << bill.appointmentID
        << ", Amount=" << bill.amount
        << ", Status=" << safeStatus
        << ", Date=" << safeDate
        << "]";

    return out;
}
