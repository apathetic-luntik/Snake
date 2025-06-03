#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QStandardItemModel>
#include <QWidget>
#include <QtCore/QDir>
#include <QtCore/QFile>
//#include<QMap>

#include "snake_model.h"
#include "unordered_map"

enum class TYPE_CELL { EMPTY = 0, WALL = 1, SNAKE = 2, SNAKE_HEAD = 3, FOOD = 4 };

class TypeCell {
public:
    TYPE_CELL type;
};

Q_DECLARE_METATYPE(TypeCell)

class Table_model : public QStandardItemModel {
    Q_OBJECT
public:
    Table_model(QString filePath);
    ~Table_model();

    void turnSnake(TYPE_DIRECTION directionType);
    TYPE_DIRECTION snakeDir() const { return snake.dir(); }
    void restart();

private:
    QFile fileCard;
    Snake_model snake = Snake_model::instance();
    std::unordered_map<TYPE_CELL, QBrush> colorCell;

    void resize(int row, int col);
    void setWall(int row, int col);
    void startSnake();
    void randomFood();
    void setItemFiel(int row, int col, TYPE_CELL cell);
    void initColorMap();

    void clearField();

    ///Проверка типа клетки
    bool typeInCell(int row, int col, TYPE_CELL type);

signals:
    void deadSnake();
    void eatSnake();
};

#endif // TABLE_MODEL_H
