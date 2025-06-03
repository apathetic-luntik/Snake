#ifndef RECORD_H
#define RECORD_H

#include <QCloseEvent>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWidget>
#include <QtCore/QDir>
#include <QtCore/QFile>

#include <algorithm>

namespace Ui {
class Record;
}

class Record : public QWidget {
    Q_OBJECT

public:
    explicit Record(QWidget *parent = 0);
    ~Record();
    void showRecord(QString nameLevel, int rez, int x, int y);

private:
    Ui::Record *ui;
    using QWidget::show;
    QJsonArray playersArray;
    int rowRez;

    QFile file;
    void closeEvent(QCloseEvent *event);

private slots:
    void on_exit_clicked();
    void on_save_clicked();
signals:
    void exitRecord();
};

#endif // RECORD_H
