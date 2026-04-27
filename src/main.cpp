#include <iostream>
#include "FileHandler.hpp"
#include "Storage.hpp"
#include "Patient.hpp"
#include "Doctor.hpp"
#include "Admin.hpp"
#include "Appointment.hpp"
#include "Bill.hpp"
#include "Prescription.hpp"

int main() {
    std::cout << "=== MediCore Hospital Management System ===\n\n";

    std::cout << "Testing Patient creation and storage...\n";
    Storage<Patient> patients;
    Patient p1(1, "John Doe", "pass123", 30, "Male", "03001234567", 5000.0);
    Patient p2(2, "Jane Smith", "pass456", 28, "Female", "03009876543", 3500.0);
    patients.add(p1);
    patients.add(p2);
    std::cout << "Added " << patients.size() << " patients.\n";
    std::cout << p1 << "\n";
    std::cout << p2 << "\n\n";

    std::cout << "Testing Doctor creation and storage...\n";
    Storage<Doctor> doctors;
    Doctor d1(1, "Dr. Ahmed", "doc123", "Cardiology", "03001111111", 1500.0);
    Doctor d2(2, "Dr. Fatima", "doc456", "Pediatrics", "03002222222", 1200.0);
    doctors.add(d1);
    doctors.add(d2);
    std::cout << "Added " << doctors.size() << " doctors.\n";
    std::cout << d1 << "\n";
    std::cout << d2 << "\n\n";

    std::cout << "Testing Appointment creation and storage...\n";
    Storage<Appointment> appointments;
    Appointment a1(1, 1, 1, "27-04-2026", "09:00", "pending");
    Appointment a2(2, 2, 2, "27-04-2026", "10:00", "pending");
    appointments.add(a1);
    appointments.add(a2);
    std::cout << "Added " << appointments.size() << " appointments.\n";
    std::cout << a1 << "\n";
    std::cout << a2 << "\n\n";

    std::cout << "Testing Bill creation and storage...\n";
    Storage<Bill> bills;
    Bill b1(1, 1, 1, 1500.0, "unpaid", "27-04-2026");
    Bill b2(2, 2, 2, 1200.0, "unpaid", "27-04-2026");
    bills.add(b1);
    bills.add(b2);
    std::cout << "Added " << bills.size() << " bills.\n";
    std::cout << b1 << "\n";
    std::cout << b2 << "\n\n";

    std::cout << "Testing Prescription creation and storage...\n";
    Storage<Prescription> prescriptions;
    Prescription rx1(1, 1, 1, 1, "27-04-2026", "Aspirin 500mg", "Take twice daily");
    Prescription rx2(2, 2, 2, 2, "27-04-2026", "Amoxicillin 250mg", "Take thrice daily");
    prescriptions.add(rx1);
    prescriptions.add(rx2);
    std::cout << "Added " << prescriptions.size() << " prescriptions.\n";
    std::cout << rx1 << "\n";
    std::cout << rx2 << "\n\n";

    std::cout << "Testing Storage find and remove...\n";
    Patient* foundPatient = patients.findByID(1);
    if (foundPatient != nullptr) {
        std::cout << "Found patient: " << *foundPatient << "\n";
    }

    std::cout << "\nTesting Patient balance operations...\n";
    std::cout << "Original balance: " << p1.getBalance() << "\n";
    p1 += 1000.0;
    std::cout << "After adding 1000: " << p1.getBalance() << "\n";
    p1 -= 500.0;
    std::cout << "After deducting 500: " << p1.getBalance() << "\n\n";

    std::cout << "Testing Appointment conflict check (operator==)...\n";
    Appointment a3(3, 1, 1, "27-04-2026", "09:00", "pending");
    if (a1 == a3) {
        std::cout << "Appointments a1 and a3 conflict (same doctor, date, time)!\n";
    } else {
        std::cout << "No conflict detected.\n";
    }

    Appointment a4(4, 1, 1, "27-04-2026", "09:00", "cancelled");
    if (a1 == a4) {
        std::cout << "Appointments a1 and a4 conflict!\n";
    } else {
        std::cout << "No conflict (one is cancelled).\n";
    }

    std::cout << "\n=== All backend tests completed successfully! ===\n";

    return 0;
}