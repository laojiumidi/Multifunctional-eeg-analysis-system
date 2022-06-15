#include "bar.h"
#include <QDebug>

bar::bar(QWidget *parent) :
    QMainWindow(parent)
{
//    connect(&top.drivewin.result,&dr_result::bar_show,this,&bar::setbar);
}

bar::~bar()
{
    delete set0;
    delete set1;
    delete set2;
    delete series;
    delete chart;
    delete axis;
    delete chartView;
}

void bar::setbar(QStringList userList,QVector<int> sum_times,QVector<int> sum_warn_times)
{
    set0 = new QBarSet("Total Times");
    set1 = new QBarSet("Total Warn Times");
    set2 = new QBarSet("Ave Warn Times");

    int con = sum_times.count();
    qDebug()<<con<<endl;
    for(int i = 0;i<con;i++)
    {
        set0->append(sum_times.at(i));
        qDebug()<<set0->at(i)<<endl;
        set1->append(sum_warn_times.at(i));
        set2->append((double)sum_warn_times.at(i)/sum_times.at(i));
    }

    series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    axis = new QBarCategoryAxis();
    axis->append(userList);
    chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
    chart->setAxisX(axis, series);//设置坐标轴

    chart->legend()->setVisible(true); //设置图例为显示状态
    chart->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    bar::setCentralWidget(chartView);
    bar::resize(850,700);
    bar::show();
    bar::setWindowFlags(bar::windowFlags() | Qt::WindowStaysOnTopHint);
}


