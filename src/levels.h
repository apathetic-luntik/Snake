#ifndef LEVELS_H
#define LEVELS_H

#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWidget>
#include <QtCore/QDir>
#include <QtCore/QFile>

#include <gamescreen.h>

namespace Ui {
class Levels;
}

class Levels : public QWidget {
    Q_OBJECT

public:
    explicit Levels(QWidget *parent = 0);
    ~Levels();

private:
    Ui::Levels *ui;
    GameScreen *m_gameScreen;
    void initList();
private slots:
    void on_play_clicked();
    void on_exit_clicked();
    void exitMain(int x, int y);
    void showGeo(int x, int y);
    void on_listLevel_clicked();

signals:
    void exitLevels(int x, int y);
};

#endif // LEVELS_H
