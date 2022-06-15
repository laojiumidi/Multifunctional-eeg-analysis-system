#include "student_score.h"
#include "ui_student_score.h"

int chinese[10] = {91,90,98,95,94,96,90,94,80,86};
int math[10] = {78,78,80,82,85,83,88,89,92,93};
int english[10] = {82,85,83,88,89,78,78,80,82,85,};
int physics[10] = {83,88,89,78,78,98,95,94,96,90,};
int chemistry[10] = {91,90,98,95,83,88,89,78,90,94};
int biology[10] = {83,88,89,78,78,98,95,94,96,90,};

Student_Score::Student_Score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student_Score)
{
    ui->setupUi(this);
    setGeometry(0,0,1024,768);
    //sql
    QStringList namelist;
    Change_Datebase* my_Change_Datebase =new Change_Datebase();
    namelist = my_Change_Datebase->get_all_name();
    delete my_Change_Datebase;
    ui->comboBox_namelist->addItems(namelist);

    //qwtplot_1
    ui->qwtPlot_1->enableAxis(QwtPlot::yLeft,true);
    ui->qwtPlot_1->enableAxis(QwtPlot::xBottom,true);
    ui->qwtPlot_1->setAxisScale(QwtPlot::yLeft,50,100);
    curve_date_ch1 = new QwtPlotCurve("Hr_Ch1");
    curve_date_ch1->setPen(Qt::red,3);//设置曲线颜色 粗细
    curve_date_ch1->attach(ui->qwtPlot_1);
    for(double i =1;i<=10;i++)
    {
        curve_date_ch1_x.append(i);
    }
    for(int i=0;i<10;i++)
    {
        curve_date_ch1_y.append(chinese[i]);
    }

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 6, 6) );
    curve_date_ch1->setSymbol(symbol);

    curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
    ui->qwtPlot_1->replot();

}

Student_Score::~Student_Score()
{
    delete ui;
}

void Student_Score::on_pushButton_teacher_clicked()
{
    accept();
}

void Student_Score::on_pushButton_teacher_2_clicked()
{
//    int temp = ui->comboBox_zhou1->currentIndex();
//    switch(temp)
//    {
//    case 1:

//    }
}

void Student_Score::on_pushButton_teacher_3_clicked()
{
    if(ui->comboBox_subject1->currentText() == "Chinese")
    {
        curve_date_ch1_y.clear();
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(chinese[i]);
        }
        curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
        ui->qwtPlot_1->replot();
    }
    if(ui->comboBox_subject1->currentText() == "Math")
    {
        curve_date_ch1_y.clear();
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(math[i]);
        }
        curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
        ui->qwtPlot_1->replot();
    }
    if(ui->comboBox_subject1->currentText() == "English")
    {
        curve_date_ch1_y.clear();
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(english[i]);
        }
        curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
        ui->qwtPlot_1->replot();
    }
    if(ui->comboBox_subject1->currentText() == "Physics")
    {
        curve_date_ch1_y.clear();
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(physics[i]);
        }
        curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
        ui->qwtPlot_1->replot();
    }
    if(ui->comboBox_subject1->currentText() == "Chemistry")
    {
        curve_date_ch1_y.clear();
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(chemistry[i]);
        }
        curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
        ui->qwtPlot_1->replot();
    }
    if(ui->comboBox_subject1->currentText() == "Biology")
    {
        curve_date_ch1_y.clear();
        for(int i=0;i<10;i++)
        {
            curve_date_ch1_y.append(biology[i]);
        }
        curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
        ui->qwtPlot_1->replot();
    }
}
