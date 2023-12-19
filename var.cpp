#include "var.h"
#include <iostream>

var::var() : valueType(INTEGER), data({ 0 }) {}

var::var(int intValue) : valueType(INTEGER), data({ intValue }) {}

var::var(double doubleValue) : valueType(DOUBLE), data({ doubleValue }) {}

var::var(const char* stringValue) : valueType(STRING), data(stringValue) {}

var::var(const std::string& stringValue) : valueType(STRING), data(stringValue) {}

var::~var() {
    if (valueType == STRING) {
        delete data.stringValue;
    }
}

var& var::operator+=(const var& other) {
    if (valueType == STRING && other.valueType == STRING) {
        *data.stringValue += static_cast<const char*>(other);
    }
    else if (valueType == DOUBLE || other.valueType == DOUBLE) {
        if (valueType == INTEGER) {
            data.doubleValue = static_cast<double>(data.intValue);
            valueType = DOUBLE;
        }
        data.doubleValue += static_cast<double>(other);
        valueType = DOUBLE;
    }
    else if (valueType == INTEGER) {
        data.intValue += static_cast<int>(other);
    }

    return *this;
}

var& var::operator/=(const var& other) {
    if (valueType == DOUBLE || other.valueType == DOUBLE) {
        if (valueType == INTEGER) {
            data.doubleValue = static_cast<double>(data.intValue);
            valueType = DOUBLE;
        }

        double otherValue = static_cast<double>(other);
        if (otherValue != 0) {
            data.doubleValue /= otherValue;
        }
        else {
            std::cerr << "Error: Division by zero.\n";
        }
    }
    else if (valueType == INTEGER) {
        int otherValue = static_cast<int>(other);
        if (otherValue != 0) {
            data.intValue /= otherValue;
        }
        else {
            std::cerr << "Error: Division by zero.\n";
        }
    }
    else {
        std::cerr << "Error: Division operation is not supported for non-numeric types.\n";
    }

    return *this;
}

var& var::operator*=(const var& other) {
    if (valueType == DOUBLE || other.valueType == DOUBLE) {
        if (valueType == INTEGER) {
            data.doubleValue = static_cast<double>(data.intValue);
            valueType = DOUBLE;
        }

        data.doubleValue *= static_cast<double>(other);
        valueType = DOUBLE;
    }
    else if (valueType == INTEGER) {
        data.intValue *= static_cast<int>(other);
    }
    else {
        std::cerr << "Error: Multiplication operation is not supported for non-numeric types.\n";
    }

    return *this;
}

var var::operator+(const var& other) const {
    var result = *this;
    result += other;
    return result;
}

var var::operator*(const var& other) const {
    if (valueType == STRING && other.valueType == STRING) {
        std::cerr << "Error: String multiplication is not supported.\n";
        return *this;
    }

    var result = *this;
    result *= other;
    return result;
}

var var::operator/(const var& other) const {
    var result = *this;
    result /= other;
    return result;
}

bool var::operator==(const var& other) const {
    if (valueType != other.valueType) {
        return false;
    }

    switch (valueType) {
    case INTEGER:
        return data.intValue == other.data.intValue;
    case DOUBLE:
        return data.doubleValue == other.data.doubleValue;
    case STRING:
        return *data.stringValue == *other.data.stringValue;
    }

    return false;
}

bool var::operator!=(const var& other) const {
    return !(*this == other);
}

bool var::operator<(const var& other) const {
    if (valueType != other.valueType) {
        std::cerr << "Error: Comparison between different types is not supported.\n";
        return false;
    }

    switch (valueType) {
    case INTEGER:
        return data.intValue < other.data.intValue;
    case DOUBLE:
        return data.doubleValue < other.data.doubleValue;
    case STRING:
        return *data.stringValue < *other.data.stringValue;
    }

    return false;
}

bool var::operator>(const var& other) const {
    return other < *this;
}

bool var::operator<=(const var& other) const {
    return !(other < *this);
}

bool var::operator>=(const var& other) const {
    return !(*this < other);
}

var::operator int() const {
    if (valueType != INTEGER) {
        std::cerr << "Error: Conversion to int not possible for non-integer types.\n";
        return 0;
    }

    return data.intValue;
}

var::operator double() const {
    if (valueType == DOUBLE) {
        return data.doubleValue;
    }
    else if (valueType == INTEGER) {
        return static_cast<double>(data.intValue);
    }
    else {
        std::cerr << "Error: Conversion to double not possible for non-numeric types.\n";
        return 0.0;
    }
}

var::operator const char* () const {
    if (valueType == STRING) {
        return data.stringValue->c_str();
    }
    else if (valueType == INTEGER) {
        std::string result = std::to_string(data.intValue);
        return result.c_str();
    }
    else if (valueType == DOUBLE) {
        std::string result = std::to_string(data.doubleValue);
        return result.c_str();
    }
    else {
        return nullptr;
    }
}

void var::Show() const {
    switch (valueType) {
    case INTEGER:
        std::cout << data.intValue;
        break;
    case DOUBLE:
        std::cout << data.doubleValue;
        break;
    case STRING:
        std::cout << *data.stringValue;
        break;
    }
}
