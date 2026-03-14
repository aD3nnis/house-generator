#include <iostream>
using namespace std;

#pragma once
#ifndef ROOM_H
#define ROOM_H


class Room{
    private: 
        int length;
        int width;
        const int DOOR = 2;
    public:
    virtual float get_size() const = 0;
    virtual ~Room() = default;   
};
#endif