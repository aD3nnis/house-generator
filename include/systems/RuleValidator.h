#ifndef RULE_VALIDATOR_H
#define RULE_VALIDATOR_H

#include <string>
#include <vector>

#include "../models/House.h"

struct ValidationReport {
    bool isValid = true;
    std::vector<std::string> issues;
};

class RuleValidator {
public:
    ValidationReport validate(const HouseLayout& layout) const;
};

#endif
