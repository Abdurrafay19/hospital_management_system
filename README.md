<div align="center">
  <h1>🏥 MediCore</h1>

  <p><strong>A robust, graphical Hospital Management System built in C++ to demonstrate advanced Object-Oriented Programming principles.</strong></p>

  <p>
    <img alt="C++17" src="https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white" />
    <img alt="SFML" src="https://img.shields.io/badge/SFML-3.1.0-8CC445?logo=c%2B%2B&logoColor=white" />
    <img alt="CMake" src="https://img.shields.io/badge/CMake-3.28-064F8C?logo=cmake&logoColor=white" />
    <img alt="Academic" src="https://img.shields.io/badge/Course-OOP_Term_Project-blue" />
  </p>
</div>

---

## 📖 Table of Contents
- [About the Project](#-about-the-project)
- [OOP Concepts Demonstrated](#-oop-concepts-demonstrated)
- [Key Features](#-key-features)
- [Tech Stack](#-tech-stack)
- [Project Architecture](#-project-architecture)
- [Getting Started](#-getting-started)
- [Academic Integrity Notice](#-academic-integrity-notice)

---

## 🚀 About the Project

**MediCore** was developed as a comprehensive term project for the Object-Oriented Programming (OOP) course at FAST NUCES. 

Moving beyond standard console-based assignments, this project features a full Graphical User Interface (GUI) built from scratch using SFML. It simulates a complete hospital ecosystem with role-based access control, allowing Administrators, Doctors, and Patients to interact with the system securely. All data is managed through a custom text-based local storage engine, ensuring data persistence across sessions.

### 🧠 OOP Concepts Demonstrated
This project serves as a practical implementation of core OOP pillars:
* **Inheritance & Polymorphism:** A base `Person` entity extended by `Admin`, `Doctor`, and `Patient` classes, allowing for scalable role management.
* **Encapsulation:** Strict separation of data and logic, with all entity attributes protected and accessed via secure getter/setter methods.
* **Exception Handling:** A custom `HospitalException` class to gracefully manage runtime errors (e.g., invalid logins, missing data files) without crashing the application.
* **Modularity:** Clear separation of concerns between Core Logic (`src/core`), Data Entities (`src/entities`), Helper Utilities (`src/helpers`), and the GUI (`src/ui`).

---

### 🎯 Key Features
* **Custom SFML GUI:** Features custom-built UI components (`UIButton`, `UITextBox`) with dynamic rendering and event polling.
* **Role-Based Dashboards:** Unique, isolated views and permissions for `AdminDash`, `DoctorDash`, and `PatientDash`.
* **Persistent Storage:** A robust `FileHandler` system that reads/writes appointments, bills, and user records to the `data/` directory using `.txt` files.
* **Comprehensive Operations:** Supports booking appointments, issuing prescriptions, processing patient discharges, and generating medical bills.
* **Security Logging:** Automated tracking of system access and critical actions via `security_log.txt`.

---

## 🛠 Tech Stack

* **Language:** C++17
* **Graphics & Windowing:** SFML (Simple and Fast Multimedia Library) 3.1.0
* **Build System:** CMake (Minimum v3.28)
* **Data Persistence:** Standard C++ File I/O (`<fstream>`)

---

## 🏗 Project Architecture

The repository is structured to maintain clean code practices:

```text
├── assets/          # Static assets (Custom UI Fonts)
├── data/            # Text-based database files (patients.txt, doctors.txt, etc.)
├── src/
│   ├── app/         # Application lifecycle management (App.cpp/hpp)
│   ├── core/        # System orchestrators, File Handlers, and custom Exceptions
│   ├── entities/    # OOP Data Models (Person, Doctor, Patient, Bill, etc.)
│   ├── helpers/     # Pure utility functions (TimeHelper, StringHelper)
│   ├── ui/          # SFML rendering logic and custom UI components
│   └── main.cpp     # Application entry point
└── CMakeLists.txt   # Build configuration

```

---

## ⚙️ Getting Started

The project is configured with CMake to provide a frictionless build process. **You do not need to install SFML manually**—the CMake script is configured to automatically fetch and link SFML 3.1.0 from GitHub.

### Prerequisites

* A C++17 compatible compiler (GCC, Clang, or MSVC)
* CMake (v3.28 or higher)
* Git (Required for CMake's `FetchContent` to pull SFML)

### Build Instructions

**1. Clone the repository:**

```bash
git clone https://github.com/abdurrafay19/hospital_management_system.git
cd hospital_management_system

```

**2. Generate the build files:**

```bash
# Create a build directory and run CMake
mkdir build
cd build
cmake ..

```

**3. Compile the project:**

```bash
cmake --build .

```

**4. Run the application:**
The executable will be generated in the `bin/` directory as specified in the `CMakeLists.txt`.

```bash
# On Windows
./bin/Debug/MediCore.exe

# On Linux/macOS
./bin/MediCore

```

---

## ⚠️ Academic Integrity Notice

This repository is public to showcase my personal academic progress and software architecture skills. If you are a current student taking an Object-Oriented Programming course, please respect your university's academic integrity and honor code policies. **Do not copy or plagiarize this code for your own academic assignments.**