#ifndef GRID_H
#define GRID_H

#include <vector>

#include "House.h"

class Grid {
public:
    Grid(int width, int height)
        : m_width(width), m_height(height), m_cells(width * height, -1) {}

    int width() const { return m_width; }
    int height() const { return m_height; }

    bool inBounds(int x, int y) const {
        return x >= 0 && y >= 0 && x < m_width && y < m_height;
    }

    int get(int x, int y) const {
        if (!inBounds(x, y)) {
            return -1;
        }

        return m_cells[(y * m_width) + x];
    }

    bool canPlace(const Room& room) const {
        for (int y = room.position.y; y < room.bottom(); ++y) {
            for (int x = room.position.x; x < room.right(); ++x) {
                if (!inBounds(x, y) || get(x, y) != -1) {
                    return false;
                }
            }
        }

        return true;
    }

    void place(const Room& room) {
        for (int y = room.position.y; y < room.bottom(); ++y) {
            for (int x = room.position.x; x < room.right(); ++x) {
                if (inBounds(x, y)) {
                    m_cells[(y * m_width) + x] = room.id;
                }
            }
        }
    }

    static Grid fromLayout(const HouseLayout& layout) {
        Grid grid(layout.width(), layout.height());

        for (const Room& room : layout.rooms) {
            grid.place(room);
        }

        return grid;
    }

private:
    int m_width;
    int m_height;
    std::vector<int> m_cells;
};

#endif
