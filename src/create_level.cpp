#include "create_level.h"

#include "ui_create_level.h"

Create_Level::Create_Level(QWidget *parent) : QMainWindow(parent), ui(new Ui::Create_Level)
{
    ui->setupUi(this);
    flag_filling = Qt::gray;
    auto geom = this->geometry();

    sizeHeight = geom.height();
    sizeWidth = geom.width();

    ui->tableField->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableField->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->col_spinBox, SIGNAL(valueChanged(int)), this, SLOT(col_spinBox_clicked()));
    connect(ui->row_spinBox, SIGNAL(valueChanged(int)), this, SLOT(row_spinBox_clicked()));
    connect(ui->tableField, SIGNAL(itemSelectionChanged()), this, SLOT(filling()));
    connect(ui->draw, SIGNAL(triggered(bool)), this, SLOT(slot_draw(bool)));
    connect(ui->wash, SIGNAL(triggered(bool)), this, SLOT(slot_wash(bool)));
    connect(ui->save, SIGNAL(triggered(bool)), this, SLOT(slot_save()));
    connect(ui->open, SIGNAL(triggered(bool)), this, SLOT(slot_open()));
    connect(ui->new_create, SIGNAL(triggered(bool)), this, SLOT(slot_new_create()));
}

Create_Level::~Create_Level()
{
    delete ui;
}

void Create_Level::closeEvent(QCloseEvent *event)
{
    checkSave();
    event->accept();
}

void Create_Level::updateTable()
{
    for (int i = 0; i < ui->tableField->rowCount(); i++)
        for (int j = 0; j < ui->tableField->columnCount(); j++) {

            auto item = ui->tableField->item(i, j);
            if (item == nullptr) {
                item = new QTableWidgetItem;
                item->setBackground(Qt::white);
                ui->tableField->setItem(i, j, item);
            }
        }
    //    qDebug() << " ui->tableField->horizontalHeader()->defaultSectionSize() "
    //             << ui->tableField->horizontalHeader()->defaultSectionSize();
    int sizeSection = ui->tableField->horizontalHeader()->defaultSectionSize();

    if (ui->tableField->horizontalHeader()->count() == 0 ||
        ui->tableField->verticalHeader()->count() == 0) {
        sizeSection = ui->horizontalLayout_box->minimumSize().width();
        return;
    } else {
        sizeSection = (ui->horizontalLayout_box->minimumSize().width()) /
                          ui->tableField->horizontalHeader()->count() +
                      1;
    }
    if (sizeSection < 20)
        sizeSection = 20;
    //    qDebug() << " sizeSection " << sizeSection;
    //    qDebug() << "  ui->horizontalLayout_box->geometry().height() "
    //             << ui->horizontalLayout_box->minimumSize().height();
    //    qDebug() << " row - col " << ui->tableField->verticalHeader()->count() << " - "
    //             << ui->tableField->horizontalHeader()->count();
    int w = sizeSection * ui->tableField->horizontalHeader()->count() + 20;
    int h = sizeSection * ui->tableField->verticalHeader()->count() +
            ui->horizontalLayout_box->minimumSize().height() + 100;
    //    qDebug() << " h " << h;
    //    qDebug() << " w " << w;
    auto geom = this->geometry();

    this->setMinimumHeight(h);
    this->setMinimumWidth(w);
    geom.setHeight(h);
    geom.setWidth(w);
    setGeometry(geom);
}
void Create_Level::row_spinBox_clicked()
{
    int row = ui->row_spinBox->value();
    ui->tableField->setRowCount(row);
    updateTable();
}

void Create_Level::col_spinBox_clicked()
{
    int col = ui->col_spinBox->value();
    ui->tableField->setColumnCount(col);
    updateTable();
}

void Create_Level::filling()
{
    QList<QTableWidgetSelectionRange> rangesList = ui->tableField->selectedRanges();
    foreach (QTableWidgetSelectionRange range, rangesList) {
        for (int i = range.topRow(); i <= range.bottomRow(); i++)
            for (int j = range.leftColumn(); j <= range.rightColumn(); j++) {

                auto item = ui->tableField->item(i, j);
                if (item == nullptr) {
                    item = new QTableWidgetItem;
                } else {
                    item = ui->tableField->item(i, j)->clone();
                }
                item->setBackground(flag_filling);
                ui->tableField->setItem(i, j, item);
            }
    }
}

void Create_Level::slot_draw(bool checked)
{
    if (checked) {
        flag_filling = Qt::gray;
        ui->wash->setChecked(false);
    } else
        ui->draw->setChecked(true);
}

void Create_Level::slot_wash(bool checked)
{
    if (checked) {
        flag_filling = Qt::white;
        ui->draw->setChecked(false);
    } else
        ui->wash->setChecked(true);
}

void Create_Level::slot_save()
{
    QString nameLevel = ui->name_edit->text();
    if (nameLevel == "")
        nameLevel = defaultName;
    int row = ui->row_spinBox->value();
    int col = ui->col_spinBox->value();

    QJsonObject rootObject;
    QJsonDocument jsonDoc;
    rootObject.insert("col_card", col);
    jsonDoc.setObject(rootObject);
    rootObject.insert("row_card", row);
    jsonDoc.setObject(rootObject);

    QJsonArray wallArray;
    QJsonObject wall;
    for (int i = 0; i < ui->tableField->rowCount(); i++)
        for (int j = 0; j < ui->tableField->columnCount(); j++) {
            auto item = ui->tableField->item(i, j);
            if (item == nullptr) {
                continue;
            } else {
                if (item->background() == Qt::gray) {
                    wall.insert("col", j);
                    wall.insert("row", i);
                    wallArray.push_back(wall);
                }
            }
        }
    rootObject.insert("wall", wallArray);
    jsonDoc.setObject(rootObject);

    QDir dir = QDir::current();
    dir.cdUp();
    QString filePath = dir.path() + "/data/card_level" + nameLevel + ".json";
    fileCard.setFileName(filePath);

    if (fileCard.exists()) {

        QMessageBox *exitMessage =
            new QMessageBox(QMessageBox::Information, "Сохранение",
                            " Файл с таким именем уже существует. Перезаписать его? ",
                            QMessageBox::Yes | QMessageBox::No);
        auto n = exitMessage->exec();
        if (n == QMessageBox::Yes) {

            if (!fileCard.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
                qDebug() << " Ошибка чтения файла";
                return;
            }
            fileCard.resize(0);
            QTextStream stream(&fileCard);
            stream << jsonDoc.toJson(QJsonDocument::Indented);
            fileCard.close();

            //После обновления уровня, обновляется файл с рейтингом
            filePath = dir.path() + "/data/scores_level" + nameLevel + ".json";
            QFile fileScore(filePath);
            if (!fileScore.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
                qDebug() << " Ошибка чтения файла";
                return;
            }
            fileScore.resize(0);
            fileScore.close();
            return;
        }
        while (fileCard.exists()) {
            nameLevel = nameLevel + "_copy";
            filePath = dir.path() + "/data/card_level" + nameLevel + ".json";
            fileCard.setFileName(filePath);
        }
    }

    if (!fileCard.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        qDebug() << " Ошибка чтения файла";
        return;
    }

    QTextStream stream(&fileCard);
    stream << jsonDoc.toJson(QJsonDocument::Indented);
    fileCard.close();
    return;
}

void Create_Level::slot_open()
{
    qDebug() << Q_FUNC_INFO;
}
void Create_Level::slot_new_create()
{
    checkSave();
    ui->tableField->setRowCount(0);
    ui->tableField->setColumnCount(0);
    ui->name_edit->setText("");
    ui->row_spinBox->setValue(0);
    ui->col_spinBox->setValue(0);

    //вернуть изначальный размер окна
    auto geom = this->geometry();
    this->setMinimumHeight(sizeHeight);
    this->setMinimumWidth(sizeWidth);
    geom.setHeight(sizeHeight);
    geom.setWidth(sizeWidth);
    setGeometry(geom);
}

void Create_Level::checkSave()
{
    if (ui->tableField->rowCount() != 0 || ui->tableField->columnCount() != 0 ||
        ui->name_edit->text() != "") {
        QMessageBox *exitMessage = new QMessageBox(QMessageBox::Information, "Создание",
                                                   " Сохранить текущие изменения ?",
                                                   QMessageBox::Yes | QMessageBox::No);
        auto n = exitMessage->exec();
        if (n == QMessageBox::Yes) {
            slot_save();
        }
    }
}
