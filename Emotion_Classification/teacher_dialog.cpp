#include "teacher_dialog.h"
#include "ui_teacher_dialog.h"



Teacher_Dialog::Teacher_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Teacher_Dialog)
{
    ui->setupUi(this);
    setGeometry(0,0,1024,768);
    qDebug() << "Teacher_Dialog in:" ;
    curve_date_ch1 = new QwtPlotCurve("a");
    curve_date_ch1->setStyle(QwtPlotCurve::Dots);
    curve_date_ch1->attach(ui->qwtPlot);
    curve_date_ch1->setPen(Qt::red,40);//设置曲线颜色  cuxie

    ui->qwtPlot->enableAxis(QwtPlot::yLeft,false);
    ui->qwtPlot->enableAxis(QwtPlot::xBottom,false);

    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,100);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,0,100);

    QwtPlotMarker *mX = new QwtPlotMarker();
    //mX->setLabel(QString::fromLatin1(">>> 专注度+ >>>"));
    mX->setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
    mX->setLabelOrientation(Qt::Horizontal);
    mX->setLineStyle(QwtPlotMarker::HLine);
    mX->setLinePen(QPen(Qt::black, 1, Qt::SolidLine));
    mX->setYValue(50);
    mX->attach(ui->qwtPlot);

    QwtPlotMarker *mX1 = new QwtPlotMarker();
    //mX1->setLabel(QString::fromLatin1(">>> 情感+ >>>"));
    mX1->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
    mX1->setLabelOrientation(Qt::Vertical);
    mX1->setLineStyle(QwtPlotMarker::VLine);
    mX1->setLinePen(QPen(Qt::black, 1, Qt::SolidLine));
    mX1->setXValue(50);
    mX1->attach(ui->qwtPlot);

    QwtPlotMarker *mX2 = new QwtPlotMarker();
    //mX2->setLabel(QString::fromLatin1("情绪警戒线"));
    mX2->setLabelAlignment(Qt::AlignLeft | Qt::AlignTop);
    mX2->setLabelOrientation(Qt::Vertical);
    mX2->setLineStyle(QwtPlotMarker::VLine);
    mX2->setLinePen(QPen(Qt::red, 1, Qt::DashLine));
    mX2->setXValue(20);
    mX2->attach(ui->qwtPlot);

    QwtPlotMarker *mX3 = new QwtPlotMarker();
    //mX3->setLabel(QString::fromLatin1("专注度警戒线"));
    mX3->setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
    mX3->setLabelOrientation(Qt::Horizontal);
    mX3->setLineStyle(QwtPlotMarker::HLine);
    mX3->setLinePen(QPen(Qt::red, 1, Qt::DashLine));
    mX3->setYValue(20);
    mX3->attach(ui->qwtPlot);

    ui->pushButton_begin_2->setDisabled(true);  //set "xiake" off


    //test
    QTimer_disp1 = new QTimer();
    connect(QTimer_disp1,SIGNAL(timeout()),this,SLOT(QTimer_disp1_fun()));
    curve_date_ch2 = new QwtPlotCurve();
    curve_date_ch2->setStyle(QwtPlotCurve::Dots);
    curve_date_ch2->attach(ui->qwtPlot);
    curve_date_ch2->setPen(Qt::red,40);//设置曲线颜色  cuxie
}

Teacher_Dialog::~Teacher_Dialog()
{
    delete ui;
//    delete curve_date_ch1;
//    delete curve_date_ch2;
}

void Teacher_Dialog::receive_att_med(const QVector<double> &vec, const QVector<double> &vec1)
{

    qDebug() << "att is" << vec;
    qDebug() << "med is" << vec1;
    con++;
    if(con < 4)
    {
        att_sum +=(double)*(vec.begin());
        med_sum +=(double)*(vec1.begin());
    }
    if(con == 4)
    {
        temp_att=(double)att_sum/con;
        temp_med=(double)med_sum/con;
        if(temp_att>=30 && temp_att<=50)
            temp_att += 20;
        if(temp_att>10 && temp_att<20)
            temp_att += 15;
        if(temp_med>30 && temp_med<45)
            temp_med += 15;
        if(temp_med>=45 && temp_med<50)
            temp_med += 5;
        curve_date_ch1_x.append(temp_att);
        curve_date_ch1_y.append(temp_med);
        curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
        ui->qwtPlot->replot();

        curve_date_ch1_x.clear();
        curve_date_ch1_y.clear();

        con = 0;
        att_sum = 0;
        med_sum = 0;
    }

}

void Teacher_Dialog::on_pushButton_clicked()
{
    //    if(ui->label_status->text() == "下课")
    //    {
    //        //back
    //        QMessageBox::warning(this,tr("上课"),tr("有课时段能有效学生有效状态."),QMessageBox::Yes);
    //        return;
    //    }

    //    my_Uart_Class->select_flag = 1;

    //    Student_Dialog* my_Student_Dialog = new Student_Dialog();

    //    QObject::connect(my_Uart_Class,&Uart_Class::new_Date_EEG,
    //                     my_Student_Dialog,&Student_Dialog::receive_EEG);

    //    my_Student_Dialog->exec();

    //    delete my_Student_Dialog;

    //    my_Uart_Class->select_flag = 0;
}

void Teacher_Dialog::on_pushButton_begin_clicked()
{
    ui->label_status->setText("in class");

    ui->pushButton_begin->setDisabled(true);

    ui->pushButton_begin_2->setEnabled(true);

    my_Uart_Class = new Uart_Class();

    QObject::connect(my_Uart_Class,&Uart_Class::new_Date_max,
                     this,&Teacher_Dialog::receive_att_med);

    my_Uart_Class->start();
}

void Teacher_Dialog::on_pushButton_begin_2_clicked()
{
    ui->label_status->setText("finish class");

    ui->pushButton_begin_2->setDisabled(true);

    ui->pushButton_begin->setEnabled(true);

    my_Uart_Class->over();

    my_Uart_Class->deleteLater();
}

void Teacher_Dialog::on_pushButton_back_clicked()
{
    if(ui->label_status->text() == "in class")
    {
        my_Uart_Class->over();

        my_Uart_Class->deleteLater();
    }

    accept();
}



void Teacher_Dialog::on_pushButton_35_clicked()
{
    QTimer_disp1->start(1000);
    temp_select = 0;
}

void Teacher_Dialog::QTimer_disp1_fun()
{
    curve_date_ch2_x.clear();
    curve_date_ch2_y.clear();
    if(temp_select == 0)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        curve_date_ch2_x.append(qrand()%50+50);
        curve_date_ch2_x.append(qrand()%50+50);
        curve_date_ch2_y.append(qrand()%50+50);
        curve_date_ch2_y.append(qrand()%50+50);
        curve_date_ch2->setSamples(curve_date_ch2_x,curve_date_ch2_y);
        ui->qwtPlot->replot();
    }
    if(temp_select == 1)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        curve_date_ch2_x.append(qrand()%20);
        curve_date_ch2_x.append(qrand()%20);
        curve_date_ch2_y.append(qrand()%100);
        curve_date_ch2_y.append(qrand()%100);
        curve_date_ch2->setSamples(curve_date_ch2_x,curve_date_ch2_y);
        ui->qwtPlot->replot();
    }
    if(temp_select == 2)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        curve_date_ch2_x.append(qrand()%20);
        curve_date_ch2_x.append(qrand()%20);
        curve_date_ch2_y.append(qrand()%20);
        curve_date_ch2_y.append(qrand()%20);
        curve_date_ch2->setSamples(curve_date_ch2_x,curve_date_ch2_y);
        ui->qwtPlot->replot();
    }
    if(temp_select == 3)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        curve_date_ch2_x.append(qrand()%100);
        curve_date_ch2_x.append(qrand()%100);
        curve_date_ch2_y.append(qrand()%100);
        curve_date_ch2_y.append(qrand()%100);
        curve_date_ch2->setSamples(curve_date_ch2_x,curve_date_ch2_y);
        ui->qwtPlot->replot();
    }

}

void Teacher_Dialog::on_pushButton_29_clicked()
{
    QTimer_disp1->start(1000);
    temp_select = 1;
}

void Teacher_Dialog::on_pushButton_28_clicked()
{
    QTimer_disp1->start(1000);
    temp_select = 2;
}

void Teacher_Dialog::on_pushButton_27_clicked()
{
    QTimer_disp1->start(1000);
    temp_select = 3;
}
