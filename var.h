#ifndef VAR_H
#define VAR_H

#include <iostream>
#include <string>

class var {
public:
    var();
    var(int intValue);
    var(double doubleValue);
    var(const char* stringValue);
    var(const std::string& stringValue);

    var& operator+=(const var& other);
    var& operator/=(const var& other);
    var& operator*=(const var& other);

    var operator+(const var& other) const;
    var operator*(const var& other) const;
    var operator/(const var& other) const;

    bool operator==(const var& other) const;
    bool operator!=(const var& other) const;
    bool operator<(const var& other) const;
    bool operator>(const var& other) const;
    bool operator<=(const var& other) const;
    bool operator>=(const var& other) const;

    operator int() const;
    operator double() const;
    operator const char* () const;

    void Show() const;

    ~var(); 

private:
    enum ValueType { INTEGER, DOUBLE, STRING };
    ValueType valueType;
    union Data {
        int intValue;
        double doubleValue;
        std::string* stringValue;

        Data(int intValue) : intValue(intValue) {}
        Data(double doubleValue) : doubleValue(doubleValue) {}
        Data(const char* stringValue) : stringValue(new std::string(stringValue)) {}
        Data(const std::string& stringValue) : stringValue(new std::string(stringValue)) {}

        
    } data;

    void ConvertToString();
};

#endif 
