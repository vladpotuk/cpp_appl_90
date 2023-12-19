#include "var.h"

int main() {
    var a = 15;
    var b = "Hello";
    var c = 7.8;
    var d = "50";

    std::cout << "Initial b: ";
    b.Show(); 
    std::cout << std::endl;

    b = a + d;
    std::cout << "After adding a and d to b: ";
    b.Show(); 
    std::cout << std::endl;

    if (a == b) {
        std::cout << "a is equal to b\n";
    }
    else {
        std::cout << "a is not equal to b\n";
    }

    if (c > a) {
        std::cout << "c is greater than a\n";
    }
    else {
        std::cout << "c is not greater than a\n";
    }

    var e = a * c;
    std::cout << "Multiplication of a and c: ";
    e.Show(); 
    std::cout << std::endl;

    var f = b / c;
    std::cout << "Division of b by c: ";
    f.Show(); 
    std::cout << std::endl;

    int sum = static_cast<int>(a) + static_cast<int>(c);
    std::cout << "Sum of a and c (cast to int): " << sum << std::endl;

    double doubleB = static_cast<double>(b);
    std::cout << "b cast to double: " << doubleB << std::endl;

    const char* charB = static_cast<const char*>(b);
    std::cout << "b cast to const char*: " << charB << std::endl;

    return 0;
}