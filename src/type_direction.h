#ifndef TYPE_DIRECTION_H
#define TYPE_DIRECTION_H

#include <QDebug>

#include "iostream"

enum TYPE_DIRECTION : int { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

//поворот по часовой стрелке
inline TYPE_DIRECTION &operator++(TYPE_DIRECTION &x_dir)
{
    switch (x_dir) {
        case TYPE_DIRECTION::UP: {
            x_dir = TYPE_DIRECTION::RIGHT;
            break;
        }
        case TYPE_DIRECTION::RIGHT: {
            x_dir = TYPE_DIRECTION::DOWN;
            break;
        }
        case TYPE_DIRECTION::DOWN: {
            x_dir = TYPE_DIRECTION::LEFT;
            break;
        }
        case TYPE_DIRECTION::LEFT: {
            x_dir = TYPE_DIRECTION::UP;
            break;
        }
    }
    return x_dir;
}

inline TYPE_DIRECTION &operator--(TYPE_DIRECTION &x_dir)
{
    switch (x_dir) {
        case TYPE_DIRECTION::UP: {
            x_dir = TYPE_DIRECTION::LEFT;
            break;
        }
        case TYPE_DIRECTION::LEFT: {
            x_dir = TYPE_DIRECTION::DOWN;
            break;
        }
        case TYPE_DIRECTION::DOWN: {
            x_dir = TYPE_DIRECTION::RIGHT;
            break;
        }
        case TYPE_DIRECTION::RIGHT: {
            x_dir = TYPE_DIRECTION::UP;
            break;
        }
    }
    return x_dir;
}

inline std::ostream &operator<<(std::ostream &out, const TYPE_DIRECTION &x_dir)
{
    switch (x_dir) {
        case TYPE_DIRECTION::UP: {
            out << "Direction UP" << std::endl;
            break;
        }
        case TYPE_DIRECTION::LEFT: {
            out << "Direction LEFT" << std::endl;
            break;
        }
        case TYPE_DIRECTION::DOWN: {
            out << "Direction DOWN" << std::endl;
            break;
        }
        case TYPE_DIRECTION::RIGHT: {
            out << "Direction RIGHT" << std::endl;
            break;
        }
    }
    return out;
}

#endif // TYPE_DIRECTION_H
