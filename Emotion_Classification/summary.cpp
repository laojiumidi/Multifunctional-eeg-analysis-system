#include "test_summary.h"
#include "ui_summary.h"

summary::summary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::summary)
{
    ui->setupUi(this);
    time = mainw.timelapse;

    connect(ui->home,&QPushButton::clicked,this,&summary::back_to_testwin);
}

summary::~summary()
{
    delete ui;
}

void summary::summary_show(bool corr)
{
    if(corr)
    {
        ui->id->setText("                  "+log.ID);
        time = mainw.timelapse;
        ui->time_lapse->setText("          "+QString::number(time/60)
                                + "   min   "+QString::number(time%60)+"   sec   ");
        ui->ave_att->setText("                  "+QString::number(mainw.rlt.att_sum/(double)time));
        ui->ave_med->setText("                  "+QString::number(mainw.rlt.med_sum/(double)time));
        ui->positive_rate->setText("                  "+QString::number(mainw.rlt.po_con/mainw.rlt.con*100)+"  %");
        summary::show();
    }
}

void summary::back_to_testwin()
{
    emit back_testwin(true);
    summary::hide();
//    mainw.serial->clear();
//    mainw.serial->close();
//    mainw.serial->deleteLater();
}
