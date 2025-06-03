#ifndef NEW_LEVEL_H
#define NEW_LEVEL_H

#include <QWidget>

namespace Ui {
class New_Level;
}

class New_Level : public QWidget
{
    Q_OBJECT

public:
    explicit New_Level(QWidget *parent = 0);
    ~New_Level();

private:
    Ui::New_Level *ui;
};

#endif // NEW_LEVEL_H
