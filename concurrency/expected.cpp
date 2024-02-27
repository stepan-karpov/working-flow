#include <iostream>
#include <expected>

std::expected<int, std::string> divide(int numerator, int denominator) {
    if (denominator == 0) {
        return std::make_unexpected(std::string("Division by zero"));
    }
    return numerator / denominator;
}

int main() {
    auto result = divide(10, 5);
    if (result.has_value()) {
        std::cout << "Result: " << result.value() << std::endl;
    } else {
        std::cout << "Error: " << result.error() << std::endl;
    }
    return 0;
}
