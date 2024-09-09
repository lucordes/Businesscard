#include "IO.h"

// Constructor to initialize the pin
IO::IO(uint8_t p) : pin(p) {
    pinMode(pin, OUTPUT); // Default to OUTPUT mode
}

// Overloading the '=' operator to write to the pin
void IO::operator=(bool value) {
    if (value) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}

// Method to set the pin mode (optional)
void IO::setMode(uint8_t mode) {
    pinMode(pin, mode);
}

// Method to read the pin value
bool IO::read() const {
    return digitalRead(pin);
}

// Optional: Overloading the '==' operator to compare pin state
bool IO::operator==(bool value) const {
    return digitalRead(pin) == value;
}

// Optional: Overloading the '!=' operator to compare pin state
IO::operator int() const {
    return digitalRead(pin);
}
