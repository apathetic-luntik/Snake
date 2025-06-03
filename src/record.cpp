#include "record.h"

#include "ui_record.h"

Record::Record(QWidget *parent) : QWidget(parent, Qt::WindowSystemMenuHint), ui(new Ui::Record)
{
    ui->setupUi(this);
    ui->tableScorse->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Record::~Record()
{
    delete ui;
}

void Record::showRecord(QString nameLevel, int rez, int x, int y)
{

    qDebug() << "nameLevel " << nameLevel;
    int x1 = x - this->geometry().width() / 2;
    int y1 = y - this->geometry().height() / 2;
    int x2 = x1 + this->geometry().width();
    int y2 = y1 + this->geometry().height();
    auto geom = this->geometry();
    geom.setCoords(x1, y1, x2, y2);

    setGeometry(geom);
    show();

    QDir dir = QDir::current();
    dir.cdUp();
    QString filePath = dir.path() + "/data/scores_" + nameLevel + ".json";
    file.setFileName(filePath);

    if (!file.exists()) {
        qDebug() << " Новый файл ";

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
            qDebug() << " Ошибка чтения файла";
            return;
        }
        QJsonObject rootObject;
        QJsonDocument jsonDoc;
        QJsonArray array;
        rootObject.insert("players", array);
        jsonDoc.setObject(rootObject);
        QTextStream stream(&file);
        stream << jsonDoc.toJson(QJsonDocument::Indented);

    } else

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

    QJsonObject objValue;
    objValue.insert("name", "");
    objValue.insert("score", rez);

    playersArray = rootObject.value("players").toArray();

    int count = playersArray.count();
    ui->tableScorse->setRowCount(count + 1);

    if (count == 0) {
        QTableWidgetItem *item = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item->setText("");
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        item->setSelected(true);
        item2->setText(QString::number(rez));
        item2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->tableScorse->setItem(0, 1, item);
        ui->tableScorse->setItem(0, 0, item2);

        ui->tableScorse->scrollToItem(item);
        ui->tableScorse->scrollToItem(item2);
        rowRez = 0;
        return;
    }
    rowRez = -1;

    int j = 0;
    for (int i = 0; i < count; i++) {

        auto player = playersArray.at(i);
        QString score, name;
        int scoreInt = player.toObject().value("score").toInt();
        score = score.number(scoreInt);
        name = player.toObject().value("name").toString();

        if (rez >= scoreInt && rowRez == -1) {

            QTableWidgetItem *item = new QTableWidgetItem;
            QTableWidgetItem *item2 = new QTableWidgetItem;
            item->setText("");
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
            item->setSelected(true);
            item2->setText(QString::number(rez));
            item2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->tableScorse->setItem(j, 1, item);
            ui->tableScorse->setItem(j, 0, item2);

            ui->tableScorse->scrollToItem(item);
            ui->tableScorse->scrollToItem(item2);

            rowRez = j;
            j++;
        }
        QTableWidgetItem *item = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item->setText(name);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item2->setText(score);
        item2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->tableScorse->setItem(j, 1, item);
        ui->tableScorse->setItem(j, 0, item2);

        if (i == (count - 1) && rowRez == -1) {

            j++;
            QTableWidgetItem *item = new QTableWidgetItem;
            QTableWidgetItem *item2 = new QTableWidgetItem;
            item->setText("");
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
            item2->setText(QString::number(rez));
            item2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

            ui->tableScorse->setItem(j, 1, item);
            ui->tableScorse->setItem(j, 0, item2);

            ui->tableScorse->scrollToItem(item);
            ui->tableScorse->scrollToItem(item2);
            rowRez = j;
        }

        j++;
    }
}

void Record::on_exit_clicked()
{

    emit exitRecord();
    close();
}

void Record::on_save_clicked()
{

    auto item = ui->tableScorse->item(rowRez, 1);
    QJsonObject objValue;
    objValue.insert("name", item->text());
    item = ui->tableScorse->item(rowRez, 0);
    objValue.insert("score", item->text().toInt());

    playersArray.insert(rowRez, objValue);

    item->text();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << " Ошибка открытия файла";
        return;
    }
    QJsonObject rootObject;
    QJsonDocument jsonDoc;

    rootObject.insert("players", playersArray);
    jsonDoc.setObject(rootObject);
    QTextStream stream(&file);
    stream << jsonDoc.toJson(QJsonDocument::Indented);

    //    qDebug() << " Данные успешно сохранены ";
    file.close();

    on_exit_clicked();
}

void Record::closeEvent(QCloseEvent *event)
{

    on_exit_clicked();
    event->accept();
}
