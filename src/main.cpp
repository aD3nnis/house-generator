#include <iostream>

#include "../include/models/LayoutRequest.h"
#include "../include/systems/LayoutGenerator.h"
#include "../include/systems/LayoutOutput.h"
#include "../include/systems/RuleValidator.h"

namespace {

int readInt(const std::string& label) {
    int value = 0;
    std::cout << label;
    std::cin >> value;
    return value;
}

} // namespace

int main() {
    LayoutRequest request;

    std::cout << "\n=== House Layout Generator ===\n\n";
    request.bedrooms = readInt("Enter number of bedrooms  (0-6): ");
    request.bathrooms = readInt("Enter number of bathrooms (0-4): ");
    request.totalSqft = readInt("Enter total square footage (500-5000): ");

    if (request.bedrooms < 0 || request.bedrooms > 6 ||
        request.bathrooms < 0 || request.bathrooms > 4 ||
        request.totalSqft < 500 || request.totalSqft > 5000) {
        std::cout << "\nInput out of supported range.\n";
        return 1;
    }

    LayoutGenerator generator;
    RuleValidator validator;

    const HouseLayout layout = generator.generateLayout(request);
    const ValidationReport report = validator.validate(layout);

    printLayoutReport(layout, report);

    return 0;
}
