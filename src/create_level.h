#ifndef CREATE_LEVEL_H
#define CREATE_LEVEL_H

#include <QCloseEvent>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QFile>

namespace Ui {
class Create_Level;
}

class Create_Level : public QMainWindow {
    Q_OBJECT

public:
    explicit Create_Level(QWidget *parent = 0);
    ~Create_Level();

private:
    Ui::Create_Level *ui;
    QBrush flag_filling;
    QFile fileCard;
    int sizeHeight = 0;
    int sizeWidth = 0;
    QString const defaultName = "безымянный";

    void updateTable();
    void checkSave();
    void closeEvent(QCloseEvent *event);

private slots:

    void row_spinBox_clicked();
    void col_spinBox_clicked();
    void filling();
    void slot_draw(bool checked);
    void slot_wash(bool checked);
    void slot_save();
    void slot_open();
    void slot_new_create();
};

#endif // CREATE_LEVEL_H
