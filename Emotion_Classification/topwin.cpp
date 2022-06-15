#include "topwin.h"
#include "ui_topwin.h"

topwin::topwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::topwin)
{
    ui->setupUi(this);

    connect(ui->test,&QPushButton::clicked,this,&topwin::testwin_show);
    connect(&testwin,&Widget::back_topwin,this,&topwin::testwin_to_topwin);

    connect(ui->drive,&QPushButton::clicked,this,&topwin::drivewin_show);
    connect(&drivewin,&drive::back_topwin,this,&topwin::drivewin_to_topwin);

    connect(ui->classroom,&QPushButton::clicked,this,&topwin::teachwin_show);
    connect(&teachwin,&classwin::back_topwin,this,&topwin::teachwin_to_topwin);

    connect(ui->close,&QPushButton::clicked,this,&topwin::system_sleep);
    connect(&sleep,&standby::weak,this,&topwin::system_weak);
}

topwin::~topwin()
{
    delete ui;
}

void topwin::testwin_show()
{
    topwin::hide();
    testwin.show();
}

void topwin::testwin_to_topwin(bool corr)
{
    if(corr)
        topwin::show();
}

void topwin::drivewin_show()
{
    topwin::hide();
    drivewin.show();
}

void topwin::drivewin_to_topwin(bool corr)
{
    if(corr)
        topwin::show();
}

void topwin::teachwin_show()
{
    topwin::hide();
    teachwin.show();
}

void topwin::teachwin_to_topwin(bool corr)
{
    if(corr)
        topwin::show();
}

void topwin::system_sleep()
{
    topwin::hide();
    sleep.show();
}

void topwin::system_weak(bool corr)
{
    if(corr)
        topwin::show();
}

