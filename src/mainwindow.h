#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>

#include <create_level.h>
#include <levels.h>
#include <scores.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Levels *m_level;
    Scores *m_scorse;
    Create_Level *m_create_level;

private slots:
    void on_exit_clicked();
    void on_play_clicked();
    void on_scores_clicked();
    void on_creator_clicked();

    void showGeo(int x, int y);
};

#endif // MAINWINDOW_H
