#ifndef LAYOUT_OUTPUT_H
#define LAYOUT_OUTPUT_H

#include "../models/House.h"
#include "RuleValidator.h"

void printRoom(const Room& room);
void printLayoutReport(const HouseLayout& layout, const ValidationReport& report);

#endif
