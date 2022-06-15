#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>
#include <user_filter.h>
#include "date_accquire.h"
#include "iir_i.h"
#include "iir_ii.h"
#include "result.h"
#include "test_film.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVector<double> eeg_iir_wave;
    int len_temp;
    int Length_Of_EEG;
    int Length_Of_ATT;
    int i;
    int timelapse = 0;
    bool serial_open;

    result rlt;
    MulPlayer film;
signals:
    void back_testwin(bool corr);
public slots:
    void back_to_testwin();

    void result_show();

    void result_to_start(bool corr);

    void on_pushButton_clicked();

    void readMyCom();

    void on_pushButton_2_clicked();

    void stop();

    void restart();

    void film_show();
    void film_to_teststart(bool corr);

signals:
    void restart_color(bool corr);

//    void on_checkBox_clicked(bool checked);

public:
    Ui::MainWindow *ui;

    QSerialPort *serial;


    QTimer *readTimer;

    QVector<double> curve_date_ch1_x;
    QVector<double> curve_date_ch1_y;
    QwtPlotCurve* curve_date_ch1;

    QVector<double> curve_date_ch2_x;
    QVector<double> curve_date_ch2_y;
    QwtPlotCurve* curve_date_ch2;

    QVector<double> curve_date_ch3_x;
    QVector<double> curve_date_ch3_y;
    QwtPlotCurve* curve_date_ch3;

    QVector<double> curve_date_ch4_x;
    QVector<double> curve_date_ch4_y;
    QwtPlotCurve* curve_date_ch4;


    QVector<double> singal_original;
    QVector<double> singal_filted;
};

#endif // MAINWINDOW_H
