#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(this);
    QPoint center = rect.center();

    //    int x1 = center.x() - (this->geometry().width() / 2);
    //    int y1 = center.y() - (this->geometry().height() / 2);
    int x1 = center.x() - this->geometry().width() / 4;
    int y1 = center.y() - this->geometry().height() / 4;
    int x2 = x1 + this->geometry().width();
    int y2 = y1 + this->geometry().height();

    auto geom = this->geometry();
    geom.setCoords(x1, y1, x2, y2);

    setGeometry(geom);

    ui->setupUi(this);
    m_scorse = new Scores;
    m_level = new Levels;
    m_create_level = new Create_Level;

    connect(m_level, SIGNAL(exitLevels(int, int)), this, SLOT(showGeo(int, int)));
    connect(m_scorse, SIGNAL(exitScores(int, int)), this, SLOT(showGeo(int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_scorse;
    delete m_level;
    delete m_create_level;
}

void MainWindow::showGeo(int x, int y)
{
    int x2 = x + this->geometry().width();
    int y2 = y + this->geometry().height();
    auto geom = this->geometry();
    geom.setCoords(x, y, x2, y2);
    this->setGeometry(geom);
    this->show();
}
void MainWindow::on_exit_clicked()
{
    m_create_level->close();
    close();
}
void MainWindow::on_scores_clicked()
{
    int x1 = this->geometry().x();
    int y1 = this->geometry().y();
    int x2 = x1 + m_scorse->geometry().width();
    int y2 = y1 + m_scorse->geometry().height();

    auto geom = m_scorse->geometry();
    geom.setCoords(x1, y1, x2, y2);
    m_scorse->setGeometry(geom);
    m_scorse->show();
    hide();
}
void MainWindow::on_play_clicked()
{
    int x1 = this->geometry().x();
    int y1 = this->geometry().y();
    int x2 = x1 + m_level->geometry().width();
    int y2 = y1 + m_level->geometry().height();

    auto geom = m_level->geometry();
    geom.setCoords(x1, y1, x2, y2);
    m_level->setGeometry(geom);
    m_level->show();
    hide();
}
void MainWindow::on_creator_clicked()
{
    int x1 = this->geometry().x();
    int y1 = this->geometry().y();
    int x2 = x1 + m_create_level->geometry().width();
    int y2 = y1 + m_create_level->geometry().height();

    auto geom = m_create_level->geometry();
    geom.setCoords(x1, y1, x2, y2);
    m_create_level->setGeometry(geom);
    m_create_level->show();
}
