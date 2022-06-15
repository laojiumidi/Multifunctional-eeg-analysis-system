#ifndef STUDENT_DIALOG_H
#define STUDENT_DIALOG_H

#include <QDialog>

//qwt
#include <qwt_plot_curve.h>
#include <qwt_plot_dict.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_marker.h>
//filter
#include "user_filter.h"

namespace Ui {
class Student_Dialog;
}

class Student_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Student_Dialog(QWidget *parent = 0);

    ~Student_Dialog();

    void receive_EEG(const QVector<double> &vec,const QVector<double> &vec1,const QVector<double> &vec2);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Student_Dialog *ui;

    QVector<double> curve_date_ch1_x;

    QVector<double> curve_date_ch1_y;

    QwtPlotCurve* curve_date_ch1;

    QwtPlotHistogram *m_histogram;
    QVector<QwtPlotHistogram*> m_plotVec;
    QVector<double> shang_vec1;

};

#endif // STUDENT_DIALOG_H
