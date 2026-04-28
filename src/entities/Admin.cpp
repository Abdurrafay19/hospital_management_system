#include "Admin.hpp"

#include <iostream>

Admin::Admin() : Person() {
}

Admin::Admin(int adminID, const char* adminName, const char* adminPassword)
    : Person(adminID, adminName, adminPassword) {
}

Admin::~Admin() {
}

void Admin::displayDashboard() {
    std::cout << "Admin Dashboard - ID: " << id << "\n";
}

void Admin::showProfile() const {
    const char* safeName;

    safeName = name != nullptr ? name : "";

    std::cout << "Admin[ID=" << id
              << ", Name=" << safeName
              << "]\n";
}
