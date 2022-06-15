#include "testwin.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->login,&QPushButton::clicked,this,&Widget::login_show);

    connect(ui->test,&QPushButton::clicked,this,&Widget::start_show);
    connect(&summ.mainw,&MainWindow::back_testwin,this,&Widget::start_to_testwin);

    connect(ui->result,&QPushButton::clicked,this,&Widget::summary_showup);
    connect(this,&Widget::summary_show,&summ,&summary::summary_show);
    connect(&summ,&summary::back_testwin,this,&Widget::summary_to_testwin);

//    connect(ui->quit,&QPushButton::clicked,this,&Widget::film_show);
//    connect(&film,&MulPlayer::back_testwin,this,&Widget::film_to_testwin);

    connect(ui->back,&QPushButton::clicked,this,&Widget::back_to_topwin);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::login_show()
{
    summ.log.show();
}

void Widget::summary_showup()
{
    emit summary_show(true);
    Widget::hide();
}

void Widget::start_show()
{
    Widget::hide();
    summ.mainw.show();
}

//void Widget::film_show()
//{
//    Widget::hide();
//    film.show();
//}

void Widget::start_to_testwin(bool corr)
{
    if(corr)
        Widget::show();
}

//void Widget::film_to_testwin(bool corr)
//{
//    if(corr)
//        Widget::show();
//}

void Widget::summary_to_testwin(bool corr)
{
    if(corr)
        Widget::show();
}

void Widget::back_to_topwin()
{
    emit back_topwin(true);
    Widget::hide();
}
