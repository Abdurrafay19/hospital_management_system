# [MediCore — Comprehensive Hospital Management System](https://github.com/Abdurrafay19/hospital_management_system)

![Status: Production Ready](https://img.shields.io/badge/Status-Production%20Ready-brightgreen) ![C++ Standard: C++17](https://img.shields.io/badge/C%2B%2B-17-blue) ![License: Educational](https://img.shields.io/badge/License-Educational-yellow)

**MediCore** is a full-featured, file-persistent hospital management system built with modern C++17 and SFML 3.1.0. It provides a secure, role-based interface for managing patient appointments, medical records, prescriptions, billing, and administrative operations. Designed as a capstone Object-Oriented Programming (OOP) project emphasizing low-level memory management, custom data structures, and enterprise-grade software architecture.

---

## 📋 Table of Contents

- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [Technology Stack](#technology-stack)
- [Installation & Setup](#installation--setup)
- [Project Structure](#project-structure)
- [Architecture & Design Patterns](#architecture--design-patterns)
- [Entity Model & Class Hierarchy](#entity-model--class-hierarchy)
- [Core Components](#core-components)
- [File Format Specifications](#file-format-specifications)
- [User Workflows](#user-workflows)
- [Build & Compilation](#build--compilation)
- [Security Features](#security-features)
- [Known Limitations & Future Enhancements](#known-limitations--future-enhancements)

---

## 📚 Project Overview

**MediCore** is a production-ready hospital information system designed to streamline operations across three user roles:

- **Patients:** Book/cancel appointments, view medical records, manage billing, top up account balance
- **Doctors:** Manage daily appointments, write prescriptions, access patient medical history
- **Administrators:** Oversee system-wide operations, discharge patients, generate reports, monitor security logs

The system enforces strict object-oriented design principles: manual memory management, dynamic allocation for all data structures, and custom container implementation (`Storage<T>`). All data persists immediately to CSV files, ensuring system reliability across restarts.

---

## ✨ Key Features

### Authentication & Security
- **Role-Based Access Control:** Separate login paths for Patients, Doctors, and Admins
- **Account Lockout:** Automatic session lock after 3 consecutive failed login attempts
- **Security Logging:** Comprehensive audit trail of all login attempts and lockouts with timestamps
- **Password Validation:** Minimum 6-character passwords with persistent authentication

### Patient Management
- **Appointment Booking:** Search doctors by specialization (case-insensitive), select time slots (09:00–16:00), automatic balance validation
- **Appointment Cancellation:** Full refund on cancellation with bill status updates
- **Medical Records:** View prescriptions organized by appointment with date-based sorting
- **Billing System:** View all bills, filter by payment status, settle outstanding amounts
- **Account Management:** Top-up account balance with real-time updates and persistence

### Doctor Workflow
- **Appointment Management:** View today's appointments sorted by time slot
- **Status Updates:** Mark appointments as completed or no-show with automatic billing adjustments
- **Prescription Writing:** Generate prescriptions with medicine details and clinical notes
- **Patient History:** Access comprehensive medical history by patient ID with complete prescription records

### Administrative Operations
- **Doctor Management:** Add new doctors, remove doctors (with constraints), manage specializations and fees
- **Patient Oversight:** View all patients with count of unpaid bills, comprehensive statistics
- **Appointment Auditing:** View all appointments sorted by date (newest first)
- **Financial Management:** View unpaid bills with automatic overdue detection (>7 days past due date)
- **Patient Discharge:** Complete patient removal with archival to discharged records file
- **Security & Reporting:** View complete security audit log and generate daily operational reports

### Data Persistence
- **Immediate File Write:** All changes written to CSV files immediately upon action completion
- **State Recovery:** Complete system state restored on application startup
- **Transaction Integrity:** No data loss or corruption even on unexpected shutdown

---

## 🛠️ Technology Stack

| Component | Version/Details |
|-----------|-----------------|
| **Language** | C++17 (ISO/IEC 14882:2017) |
| **Graphics Framework** | SFML 3.1.0 (Simple and Fast Multimedia Library) |
| **Build System** | CMake 3.28+ |
| **Compiler** | MSVC (Visual Studio 2022) or GCC/Clang with C++17 support |
| **Storage** | CSV-based file persistence (no external database) |
| **Memory Model** | Manual allocation with RAII principles |

### SFML Modules
- **Graphics:** 2D rendering, sprite management, text rendering
- **Window:** Window management, event handling, input processing
- **System:** Cross-platform utilities, timing, threading

---

## 📥 Installation & Setup

### Prerequisites

- **Visual Studio 2022** (or equivalent C++17 compiler)
- **CMake 3.28+** ([download here](https://cmake.org/download/))
- **Git** ([download here](https://git-scm.com/))
- **Internet connection** (for SFML automatic download)

### Step 1: Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/SFML-OOP-Project.git
cd SFML-OOP-Project
```

### Step 2: Create Build Directory

```bash
mkdir build
cd build
```

### Step 3: Configure with CMake

```bash
cmake -G "Visual Studio 17 2022" ..
```

**Alternative for other compilers:**
```bash
# For Unix/Linux/macOS with GCC
cmake -G "Unix Makefiles" ..

# For Ninja
cmake -G Ninja ..
```

### Step 4: Build the Project

```bash
# Using Visual Studio
cmake --build . --config Debug

# Or using platform-specific commands
# For Visual Studio:
msbuild MediCore.sln /p:Configuration=Debug

# For Unix:
make
```

### Step 5: Run the Application

```bash
# From the build directory
cd bin/Debug
./MediCore.exe          # Windows
./MediCore              # Linux/macOS
```

### Troubleshooting

| Issue | Solution |
|-------|----------|
| CMake not found | Add CMake to system PATH or use full path: `"C:\Program Files\CMake\bin\cmake.exe"` |
| SFML compilation timeout | Increase internet timeout or pre-build SFML |
| Font loading errors | Ensure `assets/fonts/` directory exists with TTF font files |
| File permission errors | Run as administrator or check write permissions on `data/` directory |

---

## 📁 Project Structure

```
SFML-OOP-Project/
├── CMakeLists.txt
├── README.md
├── assets/
│   └── fonts/
│       ├── font.ttf
│       └── font-bold.ttf
├── data/
│   ├── patients.txt
│   ├── doctors.txt
│   ├── admin.txt
│   ├── appointments.txt
│   ├── bills.txt
│   ├── prescriptions.txt
│   ├── discharged.txt
│   └── security_log.txt
├── src/
│   ├── main.cpp
│   ├── entities/
│   │   ├── Person.hpp/cpp
│   │   ├── Patient.hpp/cpp
│   │   ├── Doctor.hpp/cpp
│   │   ├── Admin.hpp/cpp
│   │   ├── Appointment.hpp/cpp
│   │   ├── Bill.hpp/cpp
│   │   ├── Prescription.hpp/cpp
│   │   └── Storage.hpp/cpp
│   ├── core/
│   │   ├── HospitalSystem.hpp/cpp
│   │   ├── FileHandler.hpp/cpp
│   │   ├── HospitalException.hpp/cpp
│   │   ├── Validator.hpp/cpp
│   │   └── Constants.hpp
│   ├── helpers/
│   │   ├── StringHelper.hpp/cpp
│   │   ├── TimeHelper.hpp/cpp
│   │   ├── ConversionHelper.hpp/cpp
│   │   ├── DataHelper.hpp/cpp
│   │   ├── CharHelper.hpp/cpp
│   │   ├── FilePathHelper.hpp/cpp
│   │   ├── StorageHelper.hpp
│   │   └── UIThemeHelper.hpp/cpp
│   ├── ui/
│   │   ├── LoginScreen.hpp/cpp
│   │   ├── PatientDash.hpp/cpp
│   │   ├── DoctorDash.hpp/cpp
│   │   ├── AdminDash.hpp/cpp
│   │   ├── UIButton.hpp/cpp
│   │   └── UITextBox.hpp/cpp
│   └── app/
│       └── App.hpp/cpp
└── build/
    └── bin/Debug/MediCore.exe
```

---

## 🏗️ Architecture & Design Patterns

### Design Principles

**MediCore** adheres to SOLID principles:

1. **Single Responsibility:** Each class handles one concern
2. **Open/Closed:** Extensible via inheritance without modification
3. **Liskov Substitution:** Derived classes honor base contracts
4. **Interface Segregation:** Minimal, focused interfaces
5. **Dependency Inversion:** Depends on abstractions, not implementations

### Architectural Layers

```
┌─────────────────────────────────────┐
│  UI Layer (SFML Graphics)           │
│  LoginScreen, PatientDash, etc.     │
└────────────────┬────────────────────┘
                 │
┌────────────────▼────────────────────┐
│  Application Controller (App)       │
│  State machine, event routing       │
└────────────────┬────────────────────┘
                 │
┌────────────────▼────────────────────┐
│  Business Logic (HospitalSystem)    │
│  Rules, validations, relationships  │
└────────┬───────────────────┬────────┘
         │                   │
    ┌────▼──────┐      ┌────▼──────┐
    │ Entities  │      │ Helpers   │
    │ (Models)  │      │ (Utils)   │
    └───────────┘      └────┬──────┘
                            │
                 ┌──────────▼────────┐
                 │ FileHandler I/O   │
                 │ (CSV Persist)     │
                 └───────────────────┘
```

---

## 🎯 Entity Model & Class Hierarchy

### Core Classes

#### **Person (Abstract Base)**
- **Members:** `id`, `name`, `password`
- **Purpose:** Identity and authentication foundation
- **Inheritance:** Base for Patient, Doctor, Admin

#### **Patient (Inherits Person)**
- **Additional Members:** `age`, `gender`, `contact`, `balance`
- **Operators:** `+=` (credit), `-=` (debit), `==` (by ID), `<<` (output)
- **Throws:** `InsufficientFundsException` on `-=` if balance insufficient

#### **Doctor (Inherits Person)**
- **Additional Members:** `specialization`, `contact`, `fee`
- **Operators:** `==` (by ID), `<<` (output)

#### **Admin (Inherits Person)**
- **No additional members**
- **Purpose:** Administrative user with system-wide privileges

#### **Appointment**
- **Members:** `appointmentID`, `patientID`, `doctorID`, `date`, `timeSlot`, `status`
- **Operators:** `==` (conflict detection), `<<` (output)
- **Query:** `isCancelled()`

#### **Bill**
- **Members:** `billID`, `patientID`, `appointmentID`, `amount`, `status`, `date`
- **Query:** `isPaid()`
- **Operators:** `==` (by ID)

#### **Prescription**
- **Members:** `prescriptionID`, `appointmentID`, `patientID`, `doctorID`, `date`, `medicines`, `notes`

#### **Storage<T> (Template Container)**
- **Capacity:** Static array of 100 items
- **Operations:** `add()`, `removeByID()`, `findByID()`, `getAll()`, `size()`
- **Purpose:** Type-safe, size-bounded container replacing `std::vector`

---

## 🔧 Core Components

### HospitalSystem (Business Logic Hub)

**Responsibilities:**
- Manage all entity storage (6 Storage<T> containers)
- Authenticate users (Patient, Doctor, Admin)
- Enforce business rules (balance validation, slot availability, etc.)
- Track login attempts and enforce lockouts

**Key Methods:**
- `Person* login(id, contact, password, role)` — Authenticate user, return Person* or nullptr
- `bool isSessionLocked()` — Query lock status
- `void bookAppointment(patient, doctorID, date, timeSlot)` — Create appointment with validation
- `double cancelAppointment(patient, appointmentID)` — Cancel and refund
- `void payBill(patient, billID)` — Mark bill as paid
- `void topUpBalance(patient, amount)` — Credit account
- `void dischargePatient(patientID)` — Archive and remove patient

**Security Features:**
- 3-strike login lockout with audit logging
- Balance validation before debits
- Conflict detection for time slots

### FileHandler (Persistence Layer)

**Methods:**
- Load methods: `loadPatients()`, `loadDoctors()`, `loadAppointments()`, etc.
- Save methods: `savePatient()`, `saveAllPatients()`, etc.
- Security logging: `saveSecurityLogEntry()`, `loadSecurityLogLines()`

**Features:**
- CSV parsing with field validation
- Automatic ID preservation on load
- Append vs. overwrite modes

### Exception Hierarchy

```
std::exception
└── HospitalException
    ├── FileNotFoundException
    ├── InsufficientFundsException
    ├── InvalidInputException
    └── SlotUnavailableException
```

### Validator (Input Validation)

**Methods:**
- `isValidID()`, `isValidDate()`, `isValidContact()`, `isValidPassword()`
- `isValidPositiveIntegerText()`, `isValidPositiveNumberText()`

### Helper Utilities

| Helper | Purpose |
|--------|---------|
| StringHelper | String operations (copy, compare, case conversion) |
| TimeHelper | Date/time parsing and comparison |
| ConversionHelper | Type conversions (string ↔ int/double) |
| DataHelper | Data manipulation (splitting, sorting) |
| FilePathHelper | File system utilities |
| UIThemeHelper | UI styling and theming |

---

## 📄 File Format Specifications

### CSV Schema (all in `data/` directory)

**patients.txt**
```csv
patient_id,name,age,gender,contact,password,balance
```

**doctors.txt**
```csv
doctor_id,name,specialization,contact,password,fee
```

**appointments.txt**
```csv
appointment_id,patient_id,doctor_id,date,time,status
```

**bills.txt**
```csv
bill_id,patient_id,appointment_id,amount,status,date
```

**prescriptions.txt**
```csv
prescription_id,appointment_id,patient_id,doctor_id,date,medicines,notes
```

**security_log.txt**
```csv
timestamp,role,entered_id,result
```

---

## 🔨 Build & Compilation

### Quick Start (Windows)

```bash
mkdir build && cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Debug
cd bin\Debug
MediCore.exe
```

### Linux/macOS

```bash
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make -j4
./bin/Debug/MediCore
```

### Troubleshooting

| Error | Solution |
|-------|----------|
| `cmake: command not found` | Install CMake or add to PATH |
| `SFML download timeout` | Pre-build SFML or increase timeout |
| `C++17 not supported` | Update compiler (MSVC 2019+, GCC 7+) |

---

## 🔐 Security Features

- **Authentication:** Role-based login with password validation (min 6 chars)
- **Account Lockout:** 3 failed attempts → session lock
- **Audit Trail:** All login attempts logged to `security_log.txt`
- **Data Integrity:** Immediate file persistence, no buffering
- **Balance Validation:** Insufficient funds throws exception

---

## 📋 Known Limitations & Future Enhancements

### Current Limitations
1. Single-session support (no concurrent users)
2. Plaintext passwords (educational project)
3. Fixed capacity: 100 items per Storage<T>
4. CSV-based storage (slow for large datasets)
5. No automatic backups

### Recommended Enhancements
1. Migrate to SQLite/PostgreSQL database
2. Implement password encryption (bcrypt/Argon2)
3. Multi-user support with session management
4. Dynamic container with pagination
5. Export reports to PDF/Excel
6. Appointment reminders via SMS/Email
7. Mobile app (React Native/Flutter)
8. HIPAA compliance features

---
