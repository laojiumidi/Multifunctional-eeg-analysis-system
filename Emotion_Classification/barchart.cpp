#include "barchart.h"
#include "ui_barchart.h"

barchart::barchart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::barchart)
{
    ui->setupUi(this);
    setGeometry(350,250,643,292);
    barshow();
}

barchart::~barchart()
{
    delete ui;
}

void barchart::setbar()
{
    set0 = new QBarSet("Jane");
    set1 = new QBarSet("John");
    set2 = new QBarSet("Axel");
    set3 = new QBarSet("Mary");
    set4 = new QBarSet("Samantha");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;// Jane 6个月份的值
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 19<< 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
    chart->setAxisX(axis, series);//设置坐标轴

    chart->legend()->setVisible(true); //设置图例为显示状态
    chart->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void barchart::barshow()
{
    barchart::show();
}

