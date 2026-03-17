#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <map> // for dict
#include <tuple> // for make_tuple member function
#include <random>
using namespace std;
#include "../systems/LayoutGenerator.h"

class Room; 

// can be catagorize rooms by any type
enum class RoomType {Bedroom, Kitchen, Livingroom, Bathroom};

struct AnchorChoiceContext {
    const vector<Room*>& placed;
    vector<Room*> kitchens;
    vector<Room*> Livingrooms;
    vector<Room*> bedrooms;
    vector<Room*> bathrooms;
    function<bool(Room*)> has_free_side;
};

class Room
{
private:
    int width{}; // inner loop but also y
    int height{}; // outer loop but also x
    float room_sqft{};
    string name = "Room";
    char name_symbol = 'R';
    map<tuple<int,int>,char> walls;
    int anchorXOnGrid;
    int anchorYOnGrid;

public:
public:
    static constexpr char N = '_';
    static constexpr char S = '-';
    static constexpr char E = '!';
    static constexpr char W = '|';
    static mt19937& rng(); //mt19937 is a random number generator
    Room(){width = 0; height = 0; room_sqft= 0;}
    Room(string n, char n_s){ name = n; name_symbol = n_s; }

    void set_anchor(int x, int y) { anchorXOnGrid = x; anchorYOnGrid = y; }
    int get_anchor_x() const { return anchorXOnGrid; }
    int get_anchor_y() const { return anchorYOnGrid; }


    int get_width() { return width; }
    int get_height() { return height; }
    void set_width(int w) { width = w; }
    void set_height(int h) { height = h; }

    void set_room_sqft(float percent, float totalSqft);
    float get_room_sqft();

    void update_dimensions(LayoutGenerator &layout_gen);

    void display_w_h(Room& r);
    void make_walls_of_room();
    void display_room_grid();
    void place_name_in_room();
    map<tuple<int,int>,char> get_room(){return walls;}


    virtual RoomType get_type() const = 0;
    virtual Room* pick_anchor(const AnchorChoiceContext& ctx) const = 0;
    virtual float get_default_size_ratio() = 0;
    virtual ~Room() = default;
    
};
#endif