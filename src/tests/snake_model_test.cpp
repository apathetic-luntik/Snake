#include <QtTest/QtTest>
#include "../snake_model.h"
#include "../type_direction.h"

class TestSnakeModel : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {
        // Инициализация перед всеми тестами
    }

    void cleanupTestCase() {
        // Очистка после всех тестов
    }

    void testNewSnake() {
        Snake_model &snake = Snake_model::instance();
        snake.new_snake(5, 5, TYPE_DIRECTION::RIGHT);
        QCOMPARE(snake.head(), std::make_pair(5, 5));
        QCOMPARE(snake.dir(), TYPE_DIRECTION::RIGHT);
    }

    void testStep() {
        Snake_model &snake = Snake_model::instance();
        snake.new_snake(5, 5, TYPE_DIRECTION::RIGHT);
        snake.step(TYPE_DIRECTION::RIGHT);
        auto head = snake.head();
        QCOMPARE(head.first, 5);
        QCOMPARE(head.second, 6); // сдвиг вправо
    }

    void testNotEat() {
        Snake_model &snake = Snake_model::instance();
        snake.new_snake(5, 5, TYPE_DIRECTION::RIGHT);
        snake.step(TYPE_DIRECTION::RIGHT);
        int oldTailRow = snake.tail().first;
        int oldTailCol = snake.tail().second;
        snake.not_eat();
        // Хвост должен сместиться вперед (удален старый хвост)
        auto newTail = snake.tail();
        QVERIFY(newTail != std::make_pair(oldTailRow, oldTailCol));
    }

    void testHeadTail() {
        Snake_model &snake = Snake_model::instance();
        snake.new_snake(3, 3, TYPE_DIRECTION::UP);
        QCOMPARE(snake.head(), std::make_pair(3, 3));
        QCOMPARE(snake.tail(), std::make_pair(3, 3));
    }

    void testDir() {
        Snake_model &snake = Snake_model::instance();
        snake.new_snake(1, 1, TYPE_DIRECTION::DOWN);
        QCOMPARE(snake.dir(), TYPE_DIRECTION::DOWN);
    }

    void testDeadSnake() {
        Snake_model &snake = Snake_model::instance();
        snake.new_snake(2, 2, TYPE_DIRECTION::LEFT);
        snake.dead_snake();
        // После dead_snake голова и хвост должны быть одинаковы и, возможно, пусты
        QCOMPARE(snake.head(), snake.tail());
    }
};

QTEST_MAIN(TestSnakeModel)
#include "snake_model_test.moc"


