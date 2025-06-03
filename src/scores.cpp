#include "scores.h"

#include "ui_scores.h"

Scores::Scores(QWidget *parent) : QWidget(parent), ui(new Ui::Scores)
{

    ui->setupUi(this);
    ui->tableScorse->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableScorse->setEditTriggers(QAbstractItemView::NoEditTriggers);
    initList();
}

Scores::~Scores()
{
    delete ui;
}

void Scores::initList()
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
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(str_level);
        ui->listLevel->addItem(item);
    }
}

void Scores::initTable(QString nameFile)
{
    int rowcount = ui->tableScorse->rowCount();
    for (int i = 0; i < rowcount; i++)
        ui->tableScorse->removeRow(0);

    QDir dir = QDir::current();
    dir.cdUp();
    QString filePath = dir.path() + "/data/" + nameFile + ".json";
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
    QJsonArray playersArray = rootObject.value("players").toArray();
    int count = playersArray.count();
    ui->tableScorse->setRowCount(count);
    for (int i = 0; i < count; i++) {
        auto player = playersArray.at(i);
        QString score, name;
        score = score.number(player.toObject().value("score").toInt());
        name = player.toObject().value("name").toString();
        QTableWidgetItem *item = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item->setText(name);
        item2->setText(score);
        ui->tableScorse->setItem(i, 1, item);
        ui->tableScorse->setItem(i, 0, item2);
    }
}
void Scores::on_exit_clicked()
{
    int x = this->geometry().x();
    int y = this->geometry().y();
    emit exitScores(x, y);
    hide();
}

void Scores::on_listLevel_clicked()
{
    QString nameFile = "scores_";

    auto selected = ui->listLevel->selectedItems();
    nameFile += selected.at(0)->text();
    initTable(nameFile);
}
