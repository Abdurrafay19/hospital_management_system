# MediCore

Graphical hospital management system demonstrating role-based access control, object-oriented programming principles, and persistent entity storage in C++17 using SFML.

## Architecture & Features

* Role-based dashboards (Admin, Doctor, Patient) built with custom SFML UI components (`UIButton`, `UITextBox`).
* Entity relationship management (`Patient`, `Doctor`, `Appointment`, `Bill`, `Prescription`) implementing inheritance from a `Person` base class.
* Text-based data persistence layer (`FileHandler`) managing state via comma-separated `.txt` files.
* Automated system access logging (`security_log.txt`) tracking failed authentication attempts.
* CMake `FetchContent` integration for automatic SFML 3.1.0 dependency resolution without manual linking.

## Prerequisites & Dependencies

* C++17 compatible compiler (GCC, Clang, or MSVC)
* CMake >= 3.28
* Git (required for CMake `FetchContent` to retrieve SFML)

## Installation & Getting Started

Clone the repository and compile via CMake:

```bash
git clone https://github.com/abdurrafay19/hospital_management_system.git
cd hospital_management_system
mkdir build
cd build
cmake ..
cmake --build .

```

Execute the compiled binary from the project root directory:

```bash
# Windows
./bin/Debug/MediCore.exe

# Linux / macOS
./bin/MediCore

```

## Data Persistence Schema

State is maintained locally in the `data/` directory using CSV-formatted text files.

| File | Schema Format | Description |
| --- | --- | --- |
| `patients.txt` | `id,name,age,gender,contact,password,balance` | Patient entity records and account balances. |
| `doctors.txt` | `id,name,specialization,contact,password,fee` | Doctor entity records and consultation fees. |
| `admin.txt` | `id,name,password` | Administrator credentials. |
| `appointments.txt` | `id,patient_id,doctor_id,date,time,status` | Appointment scheduling state (`pending`, `completed`, `cancelled`, `no-show`). |
| `bills.txt` | `id,patient_id,appointment_id,amount,status,date` | Financial transactions and billing status. |
| `prescriptions.txt` | `id,appointment_id,patient_id,doctor_id,date,medicines,notes` | Medical prescriptions linked to appointments. |
| `security_log.txt` | `timestamp,role,entered_id,result` | Security tracking for failed authentication events. |

## Project Structure

The source code is separated into domain-specific modules for rendering, business logic, and data handling:

```text
src/
├── app/         # Application lifecycle management
├── core/        # Core orchestrators, FileHandler, custom exception classes
├── entities/    # Data models (Person, Admin, Doctor, Patient, Bill, etc.)
├── helpers/     # Utility functions (TimeHelper, StringHelper, ConversionHelper)
└── ui/          # SFML rendering logic and custom UI components

```

## Academic Integrity Notice

This repository contains an academic term project for an Object-Oriented Programming (OOP) course. It is public for portfolio and demonstration purposes. Current students taking similar OOP courses must adhere to their institution's academic integrity policies and honor codes. Do not copy, mirror, or submit this codebase as your own academic work.
