#include "teacher_score.h"
#include "ui_teacher_score.h"






Teacher_Score::Teacher_Score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Teacher_Score)
{
    ui->setupUi(this);
    setGeometry(0,0,1024,768);
    ui->qwtPlot->enableAxis(QwtPlot::yLeft,true);
    ui->qwtPlot->enableAxis(QwtPlot::xBottom,true);
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,12);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,30,100);
    curve_date_ch1 = new QwtPlotCurve("Hr_Ch1");
    curve_date_ch1->setPen(Qt::red,2);
    curve_date_ch1->attach(ui->qwtPlot);
    grid1 = new QwtPlotGrid();
    grid1->enableX(true);
    grid1->enableY(true);
    grid1->setMajorPen(QPen(Qt::black,0,Qt::DotLine));
    grid1->attach(ui->qwtPlot);

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 6, 6) );

    curve_date_ch1->setSymbol(symbol);for(int i=0;i<10;i++)
    {
        curve_date_ch1_x.append(i);
    }
}

Teacher_Score::~Teacher_Score()
{
    delete ui;
}

void Teacher_Score::on_pushButton_teacher_clicked()
{
    accept();
}

void Teacher_Score::on_pushButton_teacher_3_clicked()
{
    int chinese[10] = {87,89,85,88,90,92,97,96,91,88};
    int math[10] =    {95,80,89,84,87,87,89,85,96,89};
    int english[10] = {89,87,89,92,97,96,91,88,87,80};
    int physics[10] = {89,92,97,89,92,92,97,92,97,88};
    int chemistry[10]={87,80,89,84,89,84,87,96,91,88};
    int biology[10] = {89,84,87,91,88,87,97,89,92,92,};

    curve_date_ch1_y.clear();
    if(ui->comboBox_subject->currentIndex()==0)
    {
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(chinese[i]);
        }
    }
    if(ui->comboBox_subject->currentIndex()==1)
    {
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(math[i]);
        }
    }
    if(ui->comboBox_subject->currentIndex()==2)
    {
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(english[i]);
        }
    }
    if(ui->comboBox_subject->currentIndex()==3)
    {
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(physics[i]);
        }
    }
    if(ui->comboBox_subject->currentIndex()==4)
    {
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(chemistry[i]);
        }
    }
    if(ui->comboBox_subject->currentIndex()==5)
    {
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(biology[i]);
        }
    }
    curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
    ui->qwtPlot->replot();
}
