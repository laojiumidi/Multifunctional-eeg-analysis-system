#include "drivewin.h"
#include "ui_drive.h"

drive::drive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drive)
{
    ui->setupUi(this);

    connect(ui->back,&QPushButton::clicked,this,&drive::back_to_topwin);
    connect(ui->monitor,&QPushButton::clicked,this,&drive::monitor_show);
    connect(&monitor,&dr_monitor::back_drivewin,this,&drive::monitor_to_drivewin);

    connect(ui->result,&QPushButton::clicked,this,&drive::result_show);
    connect(&result,&dr_result::back_drivewin,this,&drive::result_to_drivewin);

    connect(ui->login,&QPushButton::clicked,this,&drive::dr_login_show);

}

drive::~drive()
{
    delete ui;
}

void drive::back_to_topwin()
{
    emit back_topwin(true);
    drive::hide();
}

void drive::monitor_show()
{
    drive::hide();
    monitor.show();
}

void drive::result_show()
{
    drive::hide();
    result.show();
}

void drive::dr_login_show()
{
    dr_login.clear_slot();
    dr_login.show();
}

void drive::monitor_to_drivewin(bool corr)
{
    if(corr)
    {
        result.user = dr_login.ID; //user
        result.ave_att = QString::number(monitor.att_sum/monitor.timelapse); //ave_att
        result.timelapse = QString::number(monitor.timelapse);  //timelapse
        result.warn_times = QString::number(monitor.warn_times);  //warn_times
        result.date = monitor.start_datetime.toString("yyyy-MM-dd hh:mm:ss");  //start_datetime
        result.writetable();

        result.user.clear();
        result.ave_att.clear();
        result.timelapse.clear();
        result.warn_times.clear();
        result.date.clear();

        drive::show();

    }
}

void drive::result_to_drivewin(bool corr)
{
    if(corr)
        drive::show();
}
