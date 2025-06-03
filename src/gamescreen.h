#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <QWidget>
#include <QtCore/QDir>
#include <QtCore/QFile>
//#include <qt_windows.h>

#include "iostream"
#include "record.h"
#include "snake_model.h"
#include "table_model.h"

namespace Ui {
class GameScreen;
}

class GameScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = 0);
    ~GameScreen();
    void showLevel(QString name);

protected:
    //решение для винды
    // bool winEvent(MSG *message, long *result);

private:
    Ui::GameScreen *ui;
    QTimer *timer;
    using QWidget::show;
    Table_model *model;
    TYPE_DIRECTION dirSnake;
    Record *w_record;
    QString nameLevel; //название уровня, который сейчас открыт
    QMessageBox *exitMessageNoSave;
    qreal m_scaleParamWtoH;

    const int speed = 200; //скорость работы тайлера мс

    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:
    void slotTimerAlarm();

    void on_exit_clicked();
    void on_zanovo_clicked();
    void on_level_clicked();
    void on_start_clicked();
    void gameOver();
    void eat();
    void restart();

signals:
    void exitGames(int x, int y);
    void exitGamesMain(int x, int y);
};

#endif // GAMESCREEN_H
