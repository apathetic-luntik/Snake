#include "gamescreen.h"

#include "ui_gamescreen.h"

GameScreen::GameScreen(QWidget *parent) : QWidget(parent), ui(new Ui::GameScreen)
{
    ui->setupUi(this);

    timer = new QTimer;
    w_record = new Record;
    exitMessageNoSave =
        new QMessageBox(QMessageBox::Information, "Змейка", " Игра не сохранится ",
                        QMessageBox::Ok | QMessageBox::Cancel);

    ui->tableGame->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableGame->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    connect(w_record, SIGNAL(exitRecord()), this, SLOT(restart()));
}

GameScreen::~GameScreen()
{
    delete ui;
    delete timer;
    delete exitMessageNoSave;
    if (model != nullptr)
        delete model;
    delete w_record;
}

void GameScreen::showLevel(QString name)
{
    nameLevel = name;
    qDebug() << "Уровень" << nameLevel;
    QDir dir = QDir::current();
    dir.cdUp();
    QString filePath = dir.path() + "/data/card_" + nameLevel + ".json";
    model = new Table_model(filePath);
    connect(model, SIGNAL(deadSnake()), this, SLOT(gameOver()));
    connect(model, SIGNAL(eatSnake()), this, SLOT(eat()));
    ui->tableGame->setModel(model);
    dirSnake = model->snakeDir();

    int sizeSection = ui->tableGame->horizontalHeader()->defaultSectionSize();
    if (ui->tableGame->horizontalHeader()->defaultSectionSize() *
            ui->tableGame->horizontalHeader()->count() <
        ui->groupBox->geometry().width() - 40) {
        sizeSection = (ui->groupBox->geometry().width() - 40) /
                          ui->tableGame->horizontalHeader()->count() +
                      1;
    }

    int w = sizeSection * ui->tableGame->horizontalHeader()->count() + 40;
    int h = sizeSection * ui->tableGame->verticalHeader()->count() +
            ui->groupBox->geometry().height() + 50;
    auto geom = this->geometry();

    geom.setHeight(h);
    geom.setWidth(w);
    setGeometry(geom);
    this->setMinimumHeight(h);
    this->setMinimumWidth(w);
    show();

    m_scaleParamWtoH = (qreal) w / h;
}

void GameScreen::slotTimerAlarm()
{
    model->turnSnake(dirSnake);
    dirSnake = model->snakeDir();
}

void GameScreen::restart()
{
    ui->label->setText("0");
    model->restart();
    dirSnake = model->snakeDir();
    this->setEnabled(true);
}

void GameScreen::gameOver()
{
    timer->stop();

    int rez = ui->label->text().toInt();

    int x = this->geometry().center().x();
    int y = this->geometry().center().y();
    w_record->showRecord(nameLevel, rez, x, y);

    this->setEnabled(false);
}
void GameScreen::eat()
{
    QString sl = ui->label->text();
    int newSL = sl.toInt();
    newSL++;
    ui->label->setText(sl.number(newSL));
}

void GameScreen::on_exit_clicked()
{
    bool activ = false;
    if (timer->isActive()) {
        timer->stop();
        activ = true;
    }
    if (exitMessageNoSave->exec() == QMessageBox::Ok) {
        int x = this->geometry().x();
        int y = this->geometry().y();

        emit exitGamesMain(x, y);
        close();
    } else {
        exitMessageNoSave->hide();
        if (activ)
            timer->start(speed);
    }
}

void GameScreen::on_level_clicked()
{
    bool activ = false;
    if (timer->isActive()) {
        timer->stop();
        activ = true;
    }
    if (exitMessageNoSave->exec() == QMessageBox::Ok) {
        int x = this->geometry().x();
        int y = this->geometry().y();

        emit exitGames(x, y);
    } else {
        exitMessageNoSave->hide();
        if (activ)
            timer->start(speed);
    }
}
void GameScreen::on_zanovo_clicked()
{
    bool activ = false;
    if (timer->isActive()) {
        timer->stop();
        activ = true;
    }
    if (exitMessageNoSave->exec() == QMessageBox::Ok) {
        exitMessageNoSave->hide();
        restart();
    } else {
        exitMessageNoSave->hide();
        if (activ)
            timer->start(speed);
    }
}

void GameScreen::on_start_clicked()
{
    qDebug() << Q_FUNC_INFO;
    //в мкс
    timer->start(speed);
}

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up: {
            if (timer->isActive())
                dirSnake = TYPE_DIRECTION::UP;
            std::cout << dirSnake;
            break;
        }

        case Qt::Key_Down: {
            if (timer->isActive())
                dirSnake = TYPE_DIRECTION::DOWN;
            std::cout << dirSnake;
            break;
        }
        case Qt::Key_Left: {
            if (timer->isActive())
                dirSnake = TYPE_DIRECTION::LEFT;
            std::cout << dirSnake;
            break;
        }
        case Qt::Key_Right: {
            if (timer->isActive())
                dirSnake = TYPE_DIRECTION::RIGHT;

            std::cout << dirSnake;
            break;
        }
        case Qt::Key_Return: {
            //ломается ли какая либо логика, когда повторно нажимаешь?
            if (!timer->isActive())
                on_start_clicked();
            qDebug() << " PressKey START";
            break;
        }
        default: return;
    }
}

void GameScreen::closeEvent(QCloseEvent *event)
{
    w_record->close();
    event->accept();
}

//bool GameScreen::winEvent(MSG *message, long *result)
//{

//    switch (message->message) {
//        case (WM_SIZING): {
//            // Получаем прямоугольник окна, которым мы должны стать
//            RECT *rect = (RECT *) message->lParam;

//            // Вычленяем размеры рабочей области
//            int fWidth = frameGeometry().width() - width();
//            int fHeight = frameGeometry().height() - height();
//            int nWidth = rect->right - rect->left - fWidth;
//            int nHeight = rect->bottom - rect->top - fHeight;

//            // Меняем размеры на нужные нам
//            switch (message->wParam) {
//                case WMSZ_BOTTOM:
//                case WMSZ_TOP:
//                    rect->right = rect->left + (qreal) nHeight * m_scaleParamWtoH + fWidth;
//                    break;

//                case WMSZ_BOTTOMLEFT:
//                case WMSZ_BOTTOMRIGHT:
//                    if ((qreal) nWidth / nHeight > m_scaleParamWtoH)
//                        rect->bottom = rect->top + (qreal) nWidth / m_scaleParamWtoH + fHeight;
//                    else
//                        rect->right = rect->left + (qreal) nHeight * m_scaleParamWtoH + fWidth;
//                    break;

//                case WMSZ_LEFT:
//                case WMSZ_RIGHT:
//                    rect->bottom = rect->top + (qreal) nWidth / m_scaleParamWtoH + fHeight;
//                    break;

//                case WMSZ_TOPLEFT:
//                case WMSZ_TOPRIGHT:
//                    if ((qreal) nWidth / nHeight > m_scaleParamWtoH)
//                        rect->bottom = rect->top + (qreal) nWidth / m_scaleParamWtoH + fHeight;
//                    else
//                        rect->right = rect->left + (qreal) nHeight * m_scaleParamWtoH + fWidth;
//                    break;
//            }
//        }

//            return true;
//        default: return false;
//    }
