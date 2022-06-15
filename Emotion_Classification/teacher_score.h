#ifndef TEACHER_SCORE_H
#define TEACHER_SCORE_H

#include <QDialog>
//qwt
#include <qwt_plot_curve.h>
#include <qwt_plot_dict.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>

namespace Ui {
class Teacher_Score;
}

class Teacher_Score : public QDialog
{
    Q_OBJECT

public:
    explicit Teacher_Score(QWidget *parent = 0);
    ~Teacher_Score();

private slots:
    void on_pushButton_teacher_clicked();

    void on_pushButton_teacher_3_clicked();

private:
    Ui::Teacher_Score *ui;

    QVector<double> curve_date_ch1_x;
    QVector<double> curve_date_ch1_y;
    QwtPlotCurve* curve_date_ch1;
    QwtPlotGrid* grid1;

    QwtPlotCurve* curve_date_ch2;
    QVector<double> curve_date_ch2_x;
    QVector<double> curve_date_ch2_y;
};

#endif // TEACHER_SCORE_H
