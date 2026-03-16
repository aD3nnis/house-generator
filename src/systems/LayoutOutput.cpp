#include "../../include/systems/LayoutOutput.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {

const int HORIZONTAL_SCALE = 2;

enum Connection : unsigned char {
    Up = 1 << 0,
    Down = 1 << 1,
    Left = 1 << 2,
    Right = 1 << 3
};

struct StrokeGrid {
    int width;
    int height;
    std::vector<std::vector<unsigned char>> cells;

    StrokeGrid(int widthValue, int heightValue)
        : width(widthValue),
          height(heightValue),
          cells(heightValue, std::vector<unsigned char>(widthValue, 0)) {}

    bool inBounds(int x, int y) const {
        return x >= 0 && y >= 0 && x < width && y < height;
    }

    void addConnection(int x, int y, Connection direction) {
        if (inBounds(x, y)) {
            cells[y][x] |= direction;
        }
    }

    void connectHorizontal(int y, int startX, int endXExclusive) {
        for (int x = startX; x < endXExclusive; ++x) {
            addConnection(x, y, Right);
            addConnection(x + 1, y, Left);
        }
    }

    void connectVertical(int x, int startY, int endYExclusive) {
        for (int y = startY; y < endYExclusive; ++y) {
            addConnection(x, y, Down);
            addConnection(x, y + 1, Up);
        }
    }
};

std::string displayName(const Room& room) {
    std::string name = room.name;
    if (room.isMaster) {
        name += " M";
    }
    if (room.isEnsuite) {
        name += " E";
    }
    return name;
}

std::string roomSize(const Room& room) {
    return std::to_string(room.width) + "x" + std::to_string(room.height);
}

std::string fitText(const std::string& text, int width) {
    if (width <= 0) {
        return "";
    }
    if (static_cast<int>(text.size()) <= width) {
        return text;
    }
    if (width <= 3) {
        return text.substr(0, width);
    }
    return text.substr(0, width - 3) + "...";
}

std::string junctionGlyph(unsigned char mask) {
    switch (mask) {
        case Left | Right: return "─";
        case Up | Down: return "│";
        case Down | Right: return "┌";
        case Down | Left: return "┐";
        case Up | Right: return "└";
        case Up | Left: return "┘";
        case Up | Down | Right: return "├";
        case Up | Down | Left: return "┤";
        case Left | Right | Down: return "┬";
        case Left | Right | Up: return "┴";
        case Up | Down | Left | Right: return "┼";
        case Right:
        case Left:
            return "─";
        case Up:
        case Down:
            return "│";
        default:
            return " ";
    }
}

std::vector<std::string> buildLabelLines(const Room& room, int interiorWidth, int interiorHeight) {
    std::vector<std::string> lines;
    if (interiorWidth <= 0 || interiorHeight <= 0) {
        return lines;
    }

    const std::string name = fitText(displayName(room), interiorWidth);
    const std::string dimensions = fitText(roomSize(room), interiorWidth);

    if (interiorHeight >= 2 && !name.empty()) {
        lines.push_back(name);
        if (!dimensions.empty()) {
            lines.push_back(dimensions);
        }
        return lines;
    }

    const std::string combined = fitText(name + " (" + dimensions + ")", interiorWidth);
    if (!combined.empty()) {
        lines.push_back(combined);
    }
    return lines;
}

void placeCenteredText(
    std::vector<std::vector<std::string>>& canvas,
    int left,
    int right,
    int top,
    int bottom,
    const std::vector<std::string>& lines
) {
    if (lines.empty() || left > right || top > bottom) {
        return;
    }

    const int availableWidth = right - left + 1;
    const int availableHeight = bottom - top + 1;
    const int blockHeight = std::min(availableHeight, static_cast<int>(lines.size()));
    const int startY = top + std::max(0, (availableHeight - blockHeight) / 2);

    for (int i = 0; i < blockHeight; ++i) {
        const std::string text = fitText(lines[i], availableWidth);
        const int startX = left + std::max(0, (availableWidth - static_cast<int>(text.size())) / 2);
        for (std::size_t j = 0; j < text.size(); ++j) {
            canvas[startY + i][startX + static_cast<int>(j)] = std::string(1, text[j]);
        }
    }
}

std::string joinRow(const std::vector<std::string>& row) {
    std::string line;
    for (const std::string& cell : row) {
        line += cell;
    }
    return line;
}

void printValidationReport(const ValidationReport& report) {
    std::cout << "\n=== Validation ===\n";
    if (report.isValid) {
        std::cout << "Layout passed the core rule checks.\n";
        return;
    }

    for (const std::string& issue : report.issues) {
        std::cout << "- " << issue << "\n";
    }
}

void printAsciiFloorPlan(const HouseLayout& layout) {
    if (layout.rooms.empty()) {
        return;
    }

    const int planWidth = std::max(1, layout.width() * HORIZONTAL_SCALE);
    const int planHeight = std::max(1, layout.height());

    StrokeGrid strokes(planWidth + 1, planHeight + 1);

    for (const Room& room : layout.rooms) {
        const int left = room.position.x * HORIZONTAL_SCALE;
        const int right = room.right() * HORIZONTAL_SCALE;
        const int top = room.position.y;
        const int bottom = room.bottom();

        strokes.connectHorizontal(top, left, right);
        strokes.connectHorizontal(bottom, left, right);
        strokes.connectVertical(left, top, bottom);
        strokes.connectVertical(right, top, bottom);
    }

    std::vector<std::vector<std::string>> canvas(
        planHeight + 1,
        std::vector<std::string>(planWidth + 1, " ")
    );

    for (int y = 0; y <= planHeight; ++y) {
        for (int x = 0; x <= planWidth; ++x) {
            canvas[y][x] = junctionGlyph(strokes.cells[y][x]);
        }
    }

    for (const Room& room : layout.rooms) {
        const int left = room.position.x * HORIZONTAL_SCALE + 1;
        const int right = room.right() * HORIZONTAL_SCALE - 1;
        const int top = room.position.y + 1;
        const int bottom = room.bottom() - 1;

        placeCenteredText(
            canvas,
            left,
            right,
            top,
            bottom,
            buildLabelLines(room, right - left + 1, bottom - top + 1)
        );
    }

    const std::string topLeft = "(0,0)";
    const std::string topRight = "(" + std::to_string(layout.width()) + ",0)";
    const std::string bottomLeft = "(0," + std::to_string(layout.height()) + ")";
    const std::string bottomRight =
        "(" + std::to_string(layout.width()) + "," + std::to_string(layout.height()) + ")";
    const std::string leftPadding(topLeft.size(), ' ');

    std::cout << "\n=== Floor Plan ===\n";
    for (int y = 0; y <= planHeight; ++y) {
        const std::string row = joinRow(canvas[y]);
        if (y == 0) {
            std::cout << row << "\n";
        } else if (y == planHeight) {
            std::cout << row << "\n";
        } else {
            std::cout << row << "\n";
        }
    }
}

} // namespace

void printRoom(const Room& room) {
    std::cout << std::left << std::setw(28) << displayName(room)
              << std::right << std::setw(8) << std::fixed << std::setprecision(2) << room.percent << "%"
              << std::setw(12) << std::fixed << std::setprecision(1) << room.sqft << " sqft"
              << std::setw(14) << (std::to_string(room.width) + "x" + std::to_string(room.height))
              << std::setw(14) << ("(" + std::to_string(room.position.x) + "," + std::to_string(room.position.y) + ")")
              << "\n";
}

void printLayoutReport(const HouseLayout& layout, const ValidationReport& report) {
    std::cout << "\n=== Results ===\n";
    std::cout << std::string(82, '-') << "\n";
    std::cout << std::left << std::setw(28) << "Room"
              << std::right << std::setw(9) << "Percent"
              << std::setw(14) << "Sqft"
              << std::setw(14) << "Dimensions"
              << std::setw(17) << "Position"
              << "\n";
    std::cout << std::string(82, '-') << "\n";

    float totalPercent = 0.0f;
    float totalRoomSqft = 0.0f;

    if (!layout.hasHallway) {
        std::cout << "Hallway: NONE (front access routes through living room or kitchen)\n";
    }

    for (const Room& room : layout.rooms) {
        printRoom(room);
        totalPercent += room.percent;
        totalRoomSqft += room.sqft;
    }

    std::cout << std::string(82, '-') << "\n";
    std::cout << std::left << std::setw(28) << "TOTAL"
              << std::right << std::setw(8) << std::fixed << std::setprecision(2) << totalPercent << "%"
              << std::setw(12) << std::fixed << std::setprecision(1) << totalRoomSqft << " sqft"
              << "\n";
    std::cout << std::string(82, '-') << "\n";
    std::cout << "\nTarget sqft: " << layout.request.totalSqft
              << "  |  Planned room sqft: " << std::fixed << std::setprecision(1) << totalRoomSqft
              << "  |  Diff: " << std::fixed << std::setprecision(1) << (totalRoomSqft - layout.request.totalSqft)
              << " sqft\n";
    std::cout << "Bounding box: " << layout.width() << " ft x " << layout.height() << " ft\n";

    printValidationReport(report);
    printAsciiFloorPlan(layout);
    std::cout << "\n";
}
