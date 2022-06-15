#ifndef DR_MONITOR_H
#define DR_MONITOR_H

#include <QWidget>
#include "test_start.h"

namespace Ui {
class dr_monitor;
}

class dr_monitor : public QWidget
{
    Q_OBJECT

public:
    explicit dr_monitor(QWidget *parent = 0);
    ~dr_monitor();
    int len_temp = 0;
    int Length_Of_x = 0;
    int Length_Of_ATT = 0;
    int i = 0;
    double attation;
    double att_sum;
    int timelapse;
    int warn_times;
    bool serial_open;
    bool monitor_finish;
    bool signal_good;

    QDateTime start_datetime;

signals:
    void back_drivewin(bool corr);

public slots:
    void back_to_drivewin();
    void readMyCom();
    void start();
    void stop();
    void restart();

private:
    Ui::dr_monitor *ui;

    QSerialPort *serial;

    QTimer *readTimer;

    QVector<double> curve_date_ch1_x;
    QVector<double> curve_date_ch1_y;
    QwtPlotCurve* curve_date_ch1;
};

#endif // DR_MONITOR_H
