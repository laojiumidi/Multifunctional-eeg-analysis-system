#include "standby.h"
#include "ui_standby.h"

standby::standby(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::standby)
{
    ui->setupUi(this);
    connect(ui->open,&QPushButton::clicked,this,&standby::system_weak);
}

standby::~standby()
{
    delete ui;
}

void standby::system_weak()
{
    emit weak(true);
    standby::hide();
}
