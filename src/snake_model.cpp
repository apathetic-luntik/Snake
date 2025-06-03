#include "snake_model.h"

Snake_model::Snake_model()
{
    dead_snake();
}

void Snake_model::new_snake(int rowHead, int colHead, TYPE_DIRECTION dirType)
{
    std::pair<int, int> _mid;
    std::pair<int, int> _head;
    std::pair<int, int> _tail;

    _snake.clear();
    _head.first = rowHead;
    _head.second = colHead;
    _dir = dirType;

    switch (_dir) {
        case TYPE_DIRECTION::UP: {
            _tail.first = rowHead + 2;
            _tail.second = colHead;
            _mid.first = rowHead + 1;
            _mid.second = colHead;
            break;
        }
        case TYPE_DIRECTION::DOWN: {
            _tail.first = rowHead - 2;
            _tail.second = colHead;
            _mid.first = rowHead - 1;
            _mid.second = colHead;
            break;
        }
        case TYPE_DIRECTION::LEFT: {
            _tail.first = rowHead;
            _tail.second = colHead + 2;
            _mid.first = rowHead;
            _mid.second = colHead + 1;
            break;
        }
        case TYPE_DIRECTION::RIGHT: {
            _tail.first = rowHead;
            _tail.second = colHead - 2;
            _mid.first = rowHead;
            _mid.second = colHead - 1;
            break;
        }
        default: {
            qDebug() << "ОШИБКА Snake_model::Snake_model";
            break;
        }
    }
    _snake.push_back(_tail);
    _snake.push_back(_mid);
    _snake.push_back(_head);
}

void Snake_model::dead_snake()
{
    _snake.clear();
    std::pair<int, int> _head;
    _head.first = 8;
    _head.second = 8;
    _snake.push_back(_head);
    _dir = TYPE_DIRECTION::DOWN;
}

///
void Snake_model::step(TYPE_DIRECTION dirTurn)
{

    std::pair<int, int> _head = _snake.back();
    _dir = dirTurn;
    switch (_dir) {
        case TYPE_DIRECTION::UP: {
            _head.first--;

            break;
        }
        case TYPE_DIRECTION::DOWN: {
            _head.first++;

            break;
        }
        case TYPE_DIRECTION::LEFT: {
            _head.second--;

            break;
        }
        case TYPE_DIRECTION::RIGHT: {
            _head.second++;

            break;
        }
    }
    _snake.push_back(_head);
}
