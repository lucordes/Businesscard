#ifndef IO_H
#define IO_H

#include <Arduino.h>

class IO
{
private:
public:
    // Constructor to initialize the pin
    IO(uint8_t p);

    // current pin
    uint8_t pin;

    // Overloading the '=' operator to write to the pin
    void operator=(bool value);

    // Method to set the pin mode (optional)
    void setMode(uint8_t mode);

    // Method to read the pin value
    bool read() const;

    // Optional: Overloading the '==' operator to compare pin state
    bool operator==(bool value) const;

    // Optional: Overloading the '!=' operator to compare pin state
    operator int() const;
};

#endif
