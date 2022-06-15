#include "student_dialog.h"
#include "ui_student_dialog.h"

Student_Dialog::Student_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student_Dialog)
{
    ui->setupUi(this);
    //qwtplot_1
    ui->qwtPlot->enableAxis(QwtPlot::yLeft,false);
    ui->qwtPlot->enableAxis(QwtPlot::xBottom,true);
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,2);
    ui->qwtPlot->setAxisMaxMajor(QwtPlot::yLeft,5);
    ui->qwtPlot->setAxisMaxMinor(QwtPlot::yLeft,1);
    curve_date_ch1 = new QwtPlotCurve("Hr_Ch1");
    curve_date_ch1->setPen(Qt::red,0.5);//设置曲线颜色 粗细
    curve_date_ch1->attach(ui->qwtPlot);
    QwtPlotGrid* grid1 = new QwtPlotGrid();
    grid1->enableX(true);
    grid1->enableY(true);
    grid1->setMajorPen(QPen(Qt::black,0,Qt::DotLine));
    grid1->attach(ui->qwtPlot);
    for(double i =0;i<1024;i++)
    {
        curve_date_ch1_x.append(i/512);
    }

    ui->qwtPlot_2->enableAxis(QwtPlot::xBottom,true);
    ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,0,250);

    for(int i=0;i<5;i++)
    {
        m_histogram = new QwtPlotHistogram();
        m_plotVec.push_back(m_histogram);
        m_plotVec[i]->attach(ui->qwtPlot_2);
    }

    QVector<QColor> my_QColor;
    my_QColor.append(QColor(0,125,0));
    my_QColor.append(QColor(125,125,0));
    my_QColor.append(QColor(125,125,125));
    my_QColor.append(QColor(125,125,120));
    my_QColor.append(QColor(0,125,0));

    shang_vec1.append(20);
    shang_vec1.append(3);
    shang_vec1.append(10);
    shang_vec1.append(12);
    shang_vec1.append(0);
    QVector<QwtIntervalSample> samples(1);
    for(int i=0;i<5;i++)
    {
        QwtInterval interval( double( i*50), i*50 + 45 );
        interval.setBorderFlags( QwtInterval::ExcludeMaximum );
        //11
        samples[0] = QwtIntervalSample( shang_vec1[i] , interval );
        m_plotVec[i]->setBrush(my_QColor[i]);
        m_plotVec[i]->setData(new QwtIntervalSeriesData(samples));
    }
}

Student_Dialog::~Student_Dialog()
{
    delete ui;
}

void Student_Dialog::receive_EEG(const QVector<double> &vec,const QVector<double> &vec1,const QVector<double> &vec2)
{
    qDebug() << vec.size();
    qDebug() << vec1.size();
    qDebug() << vec2.size();

    User_Filter my_User_Filter;

    my_User_Filter.Filter_IIR(vec,curve_date_ch1_y);

    curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
    ui->qwtPlot->replot();
    curve_date_ch1_y.clear();
}

void Student_Dialog::on_pushButton_clicked()
{
    accept();
}
