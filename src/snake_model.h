#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <QDebug>
#include <QQueue>
#include <QRandomGenerator>

#include "type_direction.h"

class Snake_model {
public:
    static Snake_model &instance()
    {
        static Snake_model inst;
        return inst;
    }

    void step(TYPE_DIRECTION dirTurn);
    void not_eat() { _snake.pop_front(); }
    std::pair<int, int> head() const { return _snake.back(); }
    std::pair<int, int> tail() const { return _snake.front(); }
    TYPE_DIRECTION dir() const { return _dir; }
    void new_snake(int rowHead, int colHead, TYPE_DIRECTION dirType);
    void dead_snake();

private:
    Snake_model();
    TYPE_DIRECTION _dir;
    QQueue<std::pair<int, int>> _snake; // row/col
};

#endif // SNAKE_MODEL_H
