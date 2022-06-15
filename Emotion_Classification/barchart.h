#ifndef BARCHART_H
#define BARCHART_H

#include <QDialog>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QMainWindow>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class barchart;
}

class barchart : public QMainWindow
{
    Q_OBJECT

public:
    explicit barchart(QWidget *parent = 0);
    ~barchart();
    void setbar();
    void barshow();

    QChartView *chartView;
    QBarCategoryAxis *axis;
    QStringList categories;
    QChart *chart;
    QBarSeries *series;
    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;
    QBarSet *set3;
    QBarSet *set4;
    QBarSet *set5;
private:
    Ui::barchart *ui;
};

#endif // BARCHART_H
