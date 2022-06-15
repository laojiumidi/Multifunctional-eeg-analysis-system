#ifndef BAR_H
#define BAR_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
//#include "topwin.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class bar;
}

class bar : public QMainWindow
{
    Q_OBJECT

public:
    explicit bar(QWidget *parent = 0);
    ~bar();
    void setbar(QStringList , QVector<int> , QVector<int>);
    void barshow();

    QChartView *chartView;
    QBarCategoryAxis *axis;
    QStringList categories;
    QChart *chart;
    QBarSeries *series;
    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;

//    topwin top;
};

#endif // BAR_H
