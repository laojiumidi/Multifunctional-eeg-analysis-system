#ifndef RESULT_H
#define RESULT_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <math.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_draw.h>

#include "svm.h"

namespace Ui {
class result;
}

class result : public QWidget
{
    Q_OBJECT

public:
    explicit result(QWidget *parent = 0);
    ~result();
    svm svm_train;
    double att = 0,med = 0,att_sum = 0,med_sum = 0,con = 0,po_con = 0;
    void updatedata(QVector<double> &input_vec);
    void svm_compute();
    void att_med(double attention,double medtation);
    void set_dense_points();
    void add_dense_points();
signals:
    void back_start(bool corr);

public slots:
//    void result_show(bool corr);
    void back_to_start();
    void restart_color(bool corr);
private:
    Ui::result *ui;
};

#endif // RESULT_H
