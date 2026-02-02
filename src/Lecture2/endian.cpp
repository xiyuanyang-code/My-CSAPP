#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

/**
 * Display the binary representation of a single byte.
 *
 * @param byte The byte value to display
 */
void show_binary(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        cout << ((byte >> i) & 1);
    }
}

/**
 * Display bytes starting from a given pointer.
 *
 * @param start Pointer to the starting address
 * @param len Number of bytes to display
 * @param label Label for the display
 */
void show_bytes(uint8_t* start, size_t len, const string& label) {
    cout << label << ": ";
    for (size_t i = 0; i < len; i++) {
        cout << "0x" << setfill('0') << setw(2) << hex << (int)start[i] << " ";
    }
    cout << endl;
}

/**
 * Display bytes with binary representation.
 *
 * @param start Pointer to the starting address
 * @param len Number of bytes to display
 * @param label Label for the display
 */
void show_bytes_with_binary(uint8_t* start, size_t len, const string& label) {
    cout << label << ":" << endl;
    for (size_t i = 0; i < len; i++) {
        cout << "  Byte [" << i << "]: ";
        cout << "0x" << setfill('0') << setw(2) << hex << (int)start[i] << " (";
        show_binary(start[i]);
        cout << ")" << endl;
    }
    cout << endl;
}

/**
 * Check if the current system is little-endian.
 *
 * @return true if little-endian, false if big-endian
 */
bool is_little_endian() {
    uint32_t test = 0x12345678;
    uint8_t* byte_ptr = (uint8_t*)&test;
    return (*byte_ptr == 0x78);
}

/**
 * Demonstrate big-endian representation.
 *
 * @param value The value to demonstrate
 */
void show_big_endian(uint32_t value) {
    uint8_t bytes[4];
    bytes[0] = (value >> 24) & 0xFF;  // Most significant byte
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;          // Least significant byte

    cout << "Big-endian representation:" << endl;
    cout << "  Memory layout (low address -> high address):" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "    Address + " << i << ": ";
        cout << "0x" << setfill('0') << setw(2) << hex << (int)bytes[i] << " (";
        show_binary(bytes[i]);
        cout << ")" << endl;
    }
    cout << "  Byte sequence: ";
    for (int i = 0; i < 4; i++) {
        cout << "0x" << setfill('0') << setw(2) << hex << (int)bytes[i];
        if (i < 3) cout << " ";
    }
    cout << endl << endl;
}

/**
 * Demonstrate little-endian representation.
 *
 * @param value The value to demonstrate
 */
void show_little_endian(uint32_t value) {
    uint8_t bytes[4];
    bytes[0] = value & 0xFF;          // Least significant byte
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;  // Most significant byte

    cout << "Little-endian representation:" << endl;
    cout << "  Memory layout (low address -> high address):" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "    Address + " << i << ": ";
        cout << "0x" << setfill('0') << setw(2) << hex << (int)bytes[i] << " (";
        show_binary(bytes[i]);
        cout << ")" << endl;
    }
    cout << "  Byte sequence: ";
    for (int i = 0; i < 4; i++) {
        cout << "0x" << setfill('0') << setw(2) << hex << (int)bytes[i];
        if (i < 3) cout << " ";
    }
    cout << endl << endl;
}

int main() {
    uint32_t value;
    cout << "Enter a 32-bit hexadecimal number (e.g., 12345678): ";
    cin >> hex >> value;

    cout << "\n========================================" << endl;
    cout << "Input value: 0x" << setfill('0') << setw(8) << hex << value << endl;
    cout << "========================================\n" << endl;

    // Show binary encoding process
    cout << "Binary encoding process:" << endl;
    cout << "Hexadecimal: 0x" << setfill('0') << setw(8) << hex << value << endl;
    cout << "Binary:      ";
    for (int i = 31; i >= 0; i--) {
        cout << ((value >> i) & 1);
        if (i % 8 == 0 && i != 0) cout << " ";
    }
    cout << "\n" << endl;

    // Split into 4 bytes
    uint8_t byte0 = (value >> 24) & 0xFF;
    uint8_t byte1 = (value >> 16) & 0xFF;
    uint8_t byte2 = (value >> 8) & 0xFF;
    uint8_t byte3 = value & 0xFF;

    cout << "Split into 4 bytes:" << endl;
    cout << "  Byte 3 (most significant):  0x" << setfill('0') << setw(2) << hex << (int)byte0;
    cout << " ("; show_binary(byte0); cout << ")" << endl;
    cout << "  Byte 2:                     0x" << setfill('0') << setw(2) << hex << (int)byte1;
    cout << " ("; show_binary(byte1); cout << ")" << endl;
    cout << "  Byte 1:                     0x" << setfill('0') << setw(2) << hex << (int)byte2;
    cout << " ("; show_binary(byte2); cout << ")" << endl;
    cout << "  Byte 0 (least significant): 0x" << setfill('0') << setw(2) << hex << (int)byte3;
    cout << " ("; show_binary(byte3); cout << ")" << endl;
    cout << endl;

    // Show big-endian representation
    show_big_endian(value);

    // Show little-endian representation
    show_little_endian(value);

    // Show actual system representation
    cout << "========================================" << endl;
    cout << "Actual system representation:" << endl;
    cout << "System is: " << (is_little_endian() ? "Little-endian" : "Big-endian") << endl;
    cout << "========================================" << endl;

    uint8_t* ptr = (uint8_t*)&value;
    show_bytes_with_binary(ptr, 4, "Memory layout of 0x" + to_string(value));

    return 0;
}