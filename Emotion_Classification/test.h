#ifndef TEST_H
#define TEST_H

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
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    ~test();
    void init_qwtplot(QwtPlot *qwtplot);
    void reloaddata();
    void set_dense_points();
    void add_dense_points();
    svm svm_train;
signals:
    void to_home(bool corr);
public slots:
    void test_slot(bool corr);
    void to_home_slot();
    void start_slot();
    void updatedataSlot();
    void svm_compute();
private:
    Ui::test *ui;
    QVector<double> xdata;
    QTimer updateTimer;
    QTimer computeTimer;
    QString plotName;
    QwtPlotCurve *curve ;
    QwtPlot *qwtplot;
};

#endif // TEST_H
