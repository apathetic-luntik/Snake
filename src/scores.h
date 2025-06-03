#ifndef SCORES_H
#define SCORES_H

#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWidget>
#include <QtCore/QDir>
#include <QtCore/QFile>

namespace Ui {
class Scores;
}

class Scores : public QWidget {
    Q_OBJECT

public:
    explicit Scores(QWidget *parent = 0);
    ~Scores();

private:
    Ui::Scores *ui;
    void initTable(QString nameFile);
    void initList();

private slots:
    void on_exit_clicked();
    void on_listLevel_clicked();
signals:
    void exitScores(int x, int y);
};

#endif // SCORES_H
