#ifndef TEACHER_DIALOG_H
#define TEACHER_DIALOG_H

#include <QDialog>

#include "student_dialog.h"
#include "uart_class.h"

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>

//QMessageBox
#include "QMessageBox"
//time
#include <QTimer>
#include <QTime>

namespace Ui {
class Teacher_Dialog;
}

class Teacher_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Teacher_Dialog(QWidget *parent = 0);
    ~Teacher_Dialog();
    int con = 0;
    double att_sum,med_sum,temp_att,temp_med;
    void receive_att_med(const QVector<double> &vec,const QVector<double> &vec1);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_begin_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_begin_2_clicked();

    void on_pushButton_35_clicked();

    void QTimer_disp1_fun();

    void on_pushButton_29_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::Teacher_Dialog *ui;

    Uart_Class* my_Uart_Class;

    QVector<double> curve_date_ch1_x;

    QVector<double> curve_date_ch1_y;

    QwtPlotCurve* curve_date_ch1;

    QVector<double> curve_date_ch2_x;

    QVector<double> curve_date_ch2_y;

    QwtPlotCurve* curve_date_ch2;

    QTimer* QTimer_disp1;

    int temp_select;
};

#endif // TEACHER_DIALOG_H
