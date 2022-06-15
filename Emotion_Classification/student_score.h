#ifndef STUDENT_SCORE_H
#define STUDENT_SCORE_H

#include <QDialog>

//qwt
#include <qwt_plot_curve.h>
#include <qwt_plot_dict.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_plot_panner.h>

//mymysql
#include "change_datebase.h"

namespace Ui {
class Student_Score;
}

class Student_Score : public QDialog
{
    Q_OBJECT

public:
    explicit Student_Score(QWidget *parent = 0);
    ~Student_Score();

private slots:
    void on_pushButton_teacher_clicked();

    void on_pushButton_teacher_2_clicked();

    void on_pushButton_teacher_3_clicked();

private:
    Ui::Student_Score *ui;

    //qwtplot_1
    QVector<double> curve_date_ch1_x;
    QVector<double> curve_date_ch1_y;
    QwtPlotCurve* curve_date_ch1;
    QwtPlotPanner *panner1;
};

#endif // STUDENT_SCORE_H
