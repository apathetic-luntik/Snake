#include "new_level.h"
#include "ui_new_level.h"

New_Level::New_Level(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::New_Level)
{
    ui->setupUi(this);
}

New_Level::~New_Level()
{
    delete ui;
}
