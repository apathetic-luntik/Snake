#include "table_model.h"

Table_model::Table_model(QString filePath)
{
    initColorMap();
    fileCard.setFileName(filePath);

    if (!fileCard.exists()) {
        qDebug() << " Файл не существует";
        return;
    }

    if (!fileCard.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << " Ошибка чтения файла";
        return;
    }
    //Подумать над вариантом, что там слишком много данных
    QByteArray data = fileCard.readAll();
    fileCard.close();
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << " Ошибка чтения Json " << error.errorString();
    }

    QJsonObject rootObject = jsonDoc.object();
    int rowCard = rootObject.value("row_card").toInt();
    int colCard = rootObject.value("col_card").toInt();
    resize(rowCard, colCard);

    QJsonArray wallArray = rootObject.value("wall").toArray();

    int rowWall = 0;
    int colWall = 0;
    for (auto wall : wallArray) {
        rowWall = wall.toObject().value("row").toInt();
        colWall = wall.toObject().value("col").toInt();
        setItemFiel(rowWall, colWall, TYPE_CELL::WALL);
    }

    startSnake();
    randomFood();
}
void Table_model::restart()
{

    snake.dead_snake();

    clearField();
    startSnake();
    randomFood();
}

Table_model::~Table_model()
{

    snake.dead_snake();
}
void Table_model::resize(int row, int col)
{
    this->clear();
    this->setRowCount(row);
    this->setColumnCount(col);

    for (int i = 0; i < col; i++)
        for (int j = 0; j < row; j++) {
            QStandardItem *item = new QStandardItem;
            QVariant newItem;

            TypeCell type;
            type.type = TYPE_CELL::EMPTY;
            newItem.setValue<TypeCell>(type);
            item->setData(newItem);
            this->setItem(i, j, item);
        }
}
void Table_model::setItemFiel(int row, int col, TYPE_CELL cell)
{

    auto item = this->item(row, col);
    if (item == nullptr) {
        qDebug() << " нет ячейки";
        return;
    }

    QVariant newItem;
    TypeCell type;
    type.type = cell;
    newItem.setValue<TypeCell>(type);
    item->setData(newItem);
    item->setBackground(colorCell.at(cell));
}

bool Table_model::typeInCell(int row, int col, TYPE_CELL type)
{
    auto item = this->item(row, col);
    auto data = item->data();
    auto typeHead = data.value<TypeCell>();
    if (typeHead.type == type) {
        //        qDebug() << " змея в клетке";
        return true;
    }
    return false;
}

void Table_model::randomFood()
{
    QRandomGenerator *generator = QRandomGenerator::global();
    bool flFood = true;
    int rowFood = 0;
    int colFood = 0;

    while (flFood) {
        rowFood = generator->bounded(0, this->rowCount() - 1);
        colFood = generator->bounded(0, this->columnCount() - 1);

        if (typeInCell(rowFood, colFood, TYPE_CELL::WALL) ||
            typeInCell(rowFood, colFood, TYPE_CELL::SNAKE) ||
            typeInCell(rowFood, colFood, TYPE_CELL::SNAKE_HEAD))
            continue;

        flFood = 0;
    }

    setItemFiel(rowFood, colFood, TYPE_CELL::FOOD);
}

void Table_model::startSnake()
{
    QRandomGenerator *generator = QRandomGenerator::global();
    bool flSnake = true;
    int rowHead = 0;
    int colHead = 0;
    TYPE_DIRECTION dir = TYPE_DIRECTION::UP;
    while (flSnake) {
        rowHead = generator->bounded(0, this->rowCount() - 1);
        colHead = generator->bounded(0, this->columnCount() - 1);

        int i = generator->bounded(0, 3);
        //        qDebug() << " i=" << i;
        dir = static_cast<TYPE_DIRECTION>(i);
        //        qDebug() << " i=" << i << " dir = " << static_cast<int>(dir);

        if (typeInCell(rowHead, colHead, TYPE_CELL::WALL))
            continue;
        switch (dir) {
            case TYPE_DIRECTION::UP: {
                if (rowHead == 0) {
                    qDebug() << " врезалась в конец поля";
                    continue;
                }
                if ((rowHead + 2) > (this->rowCount() - 1)) {
                    qDebug() << " сгенерировалась за полем";
                    continue;
                }
                if (typeInCell(rowHead - 1, colHead, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась перед стеной";
                    continue;
                }
                if (typeInCell(rowHead + 1, colHead, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась в стене";
                    continue;
                }
                if (typeInCell(rowHead + 2, colHead, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась в стене";
                    continue;
                }
                break;
            }
            case TYPE_DIRECTION::RIGHT: {
                if (colHead == (rowCount() - 1)) {
                    qDebug() << " врезалась в конец поля";
                    continue;
                }
                if ((colHead - 2) < 0) {
                    qDebug() << " сгенерировалась за полем";
                    continue;
                }
                if (typeInCell(rowHead, colHead + 1, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась перед стеной";
                    continue;
                }
                if (typeInCell(rowHead, colHead - 1, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась в стене";
                    continue;
                }
                if (typeInCell(rowHead, colHead - 2, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась в стене";
                    continue;
                }
                break;
            }
            case TYPE_DIRECTION::LEFT: {
                if (colHead == 0) {
                    qDebug() << " врезалась в конец поля";
                    continue;
                }
                if ((colHead + 2) > (this->rowCount() - 1)) {
                    qDebug() << " сгенерировалась за полем";
                    continue;
                }
                if (typeInCell(rowHead, colHead - 1, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась перед стеной";
                    continue;
                }
                if (typeInCell(rowHead, colHead + 1, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась в стене";
                    continue;
                }
                if (typeInCell(rowHead, colHead + 2, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась в стене";
                    continue;
                }
                break;
            }
            case TYPE_DIRECTION::DOWN: {
                if (rowHead == (this->rowCount() - 1)) {
                    qDebug() << " врезалась в конец поля";
                    continue;
                }
                if ((rowHead - 2) < 0) {
                    qDebug() << " сгенерировалась за полем";
                    continue;
                }
                if (typeInCell(rowHead + 1, colHead, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась перед стеной";
                    continue;
                }
                if (typeInCell(rowHead - 1, colHead, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась в стене";
                    continue;
                }
                if (typeInCell(rowHead - 2, colHead, TYPE_CELL::WALL)) {
                    qDebug() << " сгенерировалась в стене";
                    continue;
                }
                break;
            }
            default: break;
        }

        flSnake = 0;
    }

    snake.new_snake(rowHead, colHead, dir);

    int rowTail = snake.tail().first;
    int colTail = snake.tail().second;
    setItemFiel(rowHead, colHead, TYPE_CELL::SNAKE_HEAD);
    setItemFiel(rowTail, colTail, TYPE_CELL::SNAKE);

    if (rowHead != rowTail) {
        if (rowHead < rowTail) {
            setItemFiel(rowHead + 1, colTail, TYPE_CELL::SNAKE);

        } else {
            setItemFiel(rowTail + 1, colTail, TYPE_CELL::SNAKE);
        }
    } else {
        if (colHead < colTail) {
            setItemFiel(rowHead, colHead + 1, TYPE_CELL::SNAKE);

        } else {
            setItemFiel(rowHead, colTail + 1, TYPE_CELL::SNAKE);
        }
    }
}

void Table_model::turnSnake(TYPE_DIRECTION directionType)
{
    TYPE_DIRECTION incDir = directionType;
    ++incDir;
    TYPE_DIRECTION decDir = directionType;
    --decDir;

    int rowHead = snake.head().first;
    int colHead = snake.head().second;

    if (snake.dir() == incDir || snake.dir() == decDir || snake.dir() == directionType)
        snake.step(directionType);
    else {

        snake.step(snake.dir());
    }
    //проверка не вышла ли за поле
    if (snake.head().first < 0 || snake.head().first > (rowCount() - 1) ||
        snake.head().second < 0 || snake.head().second > (columnCount() - 1) ||
        typeInCell(snake.head().first, snake.head().second, TYPE_CELL::WALL) ||
        typeInCell(snake.head().first, snake.head().second, TYPE_CELL::SNAKE)) {

        emit deadSnake();
        return;
    }

    if (typeInCell(snake.head().first, snake.head().second, TYPE_CELL::FOOD)) {

        randomFood();
        emit eatSnake();

    } else {

        setItemFiel(snake.tail().first, snake.tail().second, TYPE_CELL::EMPTY);
        snake.not_eat();
    }
    setItemFiel(rowHead, colHead, TYPE_CELL::SNAKE);
    setItemFiel(snake.head().first, snake.head().second, TYPE_CELL::SNAKE_HEAD);
}

void Table_model::clearField()
{
    for (int i = 0; i < rowCount(); i++)
        for (int j = 0; j < columnCount(); j++) {

            if (typeInCell(i, j, TYPE_CELL::FOOD) || typeInCell(i, j, TYPE_CELL::SNAKE) ||
                typeInCell(i, j, TYPE_CELL::SNAKE_HEAD)) {
                setItemFiel(i, j, TYPE_CELL::EMPTY);
            }
        }
}

void Table_model::initColorMap()
{
    colorCell[TYPE_CELL::EMPTY] = Qt::white;
    colorCell[TYPE_CELL::WALL] = Qt::gray;
    colorCell[TYPE_CELL::SNAKE] = QColor(0, 155, 70);
    colorCell[TYPE_CELL::SNAKE_HEAD] = QColor(0, 100, 70);
    colorCell[TYPE_CELL::FOOD] = QColor(160, 0, 50);
}
