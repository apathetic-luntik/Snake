#include "levels.h"

#include "ui_levels.h"

Levels::Levels(QWidget *parent) : QWidget(parent), ui(new Ui::Levels)
{
    ui->setupUi(this);
    m_gameScreen = new GameScreen;
    initList();

    ui->play->setEnabled(false);

    connect(m_gameScreen, SIGNAL(exitGames(int, int)), this, SLOT(showGeo(int, int)));
    connect(m_gameScreen, SIGNAL(exitGamesMain(int, int)), this, SLOT(exitMain(int, int)));
}

Levels::~Levels()
{
    delete ui;
    delete m_gameScreen;
}
void Levels::initList()
{
    QDir dir = QDir::current();
    dir.cdUp();
    QString filePath = dir.path() + "/data/levels.json";
    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << " Файл не существует";
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << " Ошибка чтения файла";
        return;
    }
    //Подумать над вариантом, что там слишком много данных
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << " Ошибка чтения Json " << error.errorString();
    }

    QJsonObject rootObject = jsonDoc.object();
    QJsonArray levelArray = rootObject.value("level").toArray();
    QString str_level;

    for (auto level : levelArray) {
        str_level = "level" + level.toString();

        filePath = dir.path() + "/data/card_" + str_level + ".json";
        file.setFileName(filePath);
        if (file.exists()) {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(str_level);
            ui->listLevel->addItem(item);
        }
    }
}
void Levels::showGeo(int x, int y)
{
    int x2 = x + this->geometry().width();
    int y2 = y + this->geometry().height();
    auto geom = this->geometry();
    geom.setCoords(x, y, x2, y2);
    this->setGeometry(geom);
    this->show();
    m_gameScreen->hide();
}

void Levels::exitMain(int x, int y)
{
    emit exitLevels(x, y);
}

void Levels::on_exit_clicked()
{
    int x = this->geometry().x();
    int y = this->geometry().y();

    emit exitLevels(x, y);
    hide();
}
void Levels::on_play_clicked()

{
    auto selected = ui->listLevel->selectedItems();
    QString nameLavel = selected.at(0)->text();

    int x1 = this->geometry().x();
    int y1 = this->geometry().y();
    int x2 = x1 + m_gameScreen->geometry().width();
    int y2 = y1 + m_gameScreen->geometry().height();

    auto geom = m_gameScreen->geometry();
    geom.setCoords(x1, y1, x2, y2);
    m_gameScreen->setGeometry(geom);
    m_gameScreen->showLevel(nameLavel);

    hide();
}

void Levels::on_listLevel_clicked()
{
    ui->play->setEnabled(true);
}
