#pragma once

enum SystemConstants
{
    // Buffer Sizes
    MAX_LINE_BUFFER = 1024,
    MAX_LARGE_LINE_BUFFER = 2048,
    MAX_FIELD_BUFFER = 256,
    MAX_LARGE_FIELD_BUFFER = 512,
    
    MAX_PATH_BUFFER = 300,
    MAX_SMALL_BUFFER = 32,
    MAX_MEDIUM_BUFFER = 64,

    // Storage and Pagination Limits
    STORAGE_MAX_SIZE = 100,
    PAGED_LIST_MAX_ITEMS = 100,

    // CSV Field Counts
    MAX_PATIENT_FIELDS = 7,
    MAX_DOCTOR_FIELDS = 6,
    MAX_ADMIN_FIELDS = 3,
    MAX_APPOINTMENT_FIELDS = 6,
    MAX_BILL_FIELDS = 6,
    MAX_PRESCRIPTION_FIELDS = 7
};