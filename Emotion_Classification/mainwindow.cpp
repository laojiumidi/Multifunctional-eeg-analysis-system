#include "test_start.h"
#include "ui_mainwindow.h"

double Length_Of_x = 0;

bool save_control = 0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial_open = false;
    connect(ui->result,&QPushButton::clicked,this,&MainWindow::result_show);
    connect(&rlt,&result::back_start,this,&MainWindow::result_to_start);

    curve_date_ch1 = new QwtPlotCurve("Hr_Ch1");
    curve_date_ch1->setPen(Qt::blue,0.5);//??????????? ???
    curve_date_ch1->attach(ui->qwtPlot);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,-0.000001,0.000001);

    curve_date_ch2 = new QwtPlotCurve("Hr_Ch2");
    curve_date_ch2->setPen(Qt::red,0.5);//??????????? ???
    curve_date_ch2->attach(ui->qwtPlot_2);
    ui->qwtPlot_2->setAxisScale(QwtPlot::yLeft,-0.000001,0.000001);

    curve_date_ch3 = new QwtPlotCurve("Hr_Ch3");
    curve_date_ch3->setPen(Qt::green,0.5);//??????????? ???
    curve_date_ch3->attach(ui->qwtPlot_3);
    ui->qwtPlot_3->setAxisScale(QwtPlot::xBottom,0,100);
    ui->qwtPlot_3->setAxisScale(QwtPlot::yLeft,0,100);

    curve_date_ch4 = new QwtPlotCurve("Hr_Ch4");
    curve_date_ch4->setPen(Qt::gray,0.5);//??????????? ???
    curve_date_ch4->attach(ui->qwtPlot_4);
    ui->qwtPlot_4->setAxisScale(QwtPlot::xBottom,0,100);
    ui->qwtPlot_4->setAxisScale(QwtPlot::yLeft,0,100);

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
                                       QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3) );
    curve_date_ch3->setSymbol(symbol);
    curve_date_ch4->setSymbol(symbol);

    readTimer = new QTimer();
    connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));

    timelapse = 0;

    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::back_to_testwin);
    connect(ui->stop,&QPushButton::clicked,this,&MainWindow::stop);
    connect(ui->restart,&QPushButton::clicked,this,&MainWindow::restart);

    connect(ui->film,&QPushButton::clicked,this,&MainWindow::film_show);
    connect(&film,&MulPlayer::back_teststart,this,&MainWindow::film_to_teststart);
}

MainWindow::~MainWindow()
{
    //    delete serial;
    //    delete readTimer;
    //    delete curve_date_ch1;
    //    delete curve_date_ch2;
    //    delete curve_date_ch3;
    //    delete curve_date_ch4;

}

void MainWindow::back_to_testwin()
{
    emit back_testwin(true);
    MainWindow::hide();
    readTimer->stop();
    if(serial_open)
    {
        serial->clear();
        serial->close();
        serial->deleteLater();
        serial_open = false;
    }
    curve_date_ch1_x.clear();
    curve_date_ch1_y.clear();
    ui->qwtPlot->replot();

    curve_date_ch2_x.clear();
    curve_date_ch2_y.clear();
    ui->qwtPlot->replot();

    curve_date_ch3_x.clear();
    curve_date_ch3_y.clear();
    ui->qwtPlot->replot();

    curve_date_ch4_x.clear();
    curve_date_ch4_y.clear();
    ui->qwtPlot->replot();
    Length_Of_x = 0;
}

void MainWindow::film_show()
{
    MainWindow::hide();
    film.show();
}

void MainWindow::film_to_teststart(bool corr)
{
    if(corr)
        MainWindow::show();
}

void MainWindow::on_pushButton_clicked()
{
    serial = new QSerialPort();
    serial->setPortName("/dev/ttySAC3");
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(QSerialPort::Baud57600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    serial_open = true;

    readTimer->start(1000);
}

void MainWindow::stop()
{
    readTimer->stop();
}

void MainWindow::restart()
{
    timelapse = 0;
    rlt.att_sum = 0;
    rlt.med_sum = 0;
    rlt.con = 0;
    rlt.po_con = 0;

    curve_date_ch1_x.clear();
    curve_date_ch1_y.clear();
    ui->qwtPlot->replot();
    curve_date_ch2_x.clear();
    curve_date_ch2_y.clear();
    ui->qwtPlot_2->replot();
    curve_date_ch3_x.clear();
    curve_date_ch3_y.clear();
    ui->qwtPlot_3->replot();
    curve_date_ch4_x.clear();
    curve_date_ch4_y.clear();
    ui->qwtPlot_4->replot();
    Length_Of_x = 0;

    serial_open = true;
    emit restart_color(true);
    readTimer->start(1000);
}

void MainWindow::readMyCom()
{
    timelapse++;

    static vector<unsigned char> uart_buff_vec;

    QByteArray temp = serial->readAll();

    len_temp = temp.size();
    qDebug() << "len_temp:" << len_temp;
    if(len_temp == 0)
    {
        return;
    }
    for(i=0;i<len_temp;i++)
    {
        uart_buff_vec.push_back(temp[i]);
    }

    qDebug() << endl;
    date_accquire* my_date_accquire = new date_accquire();
    my_date_accquire->original_date_accquire(uart_buff_vec);
    qDebug() << "uart_buff_vec size is:"<<uart_buff_vec.size()<<endl;
    Length_Of_EEG = my_date_accquire->EEG_signal.size();
    for(i=0;i<Length_Of_EEG;i++)
    {
        curve_date_ch1_x.append((double)i);
        curve_date_ch1_y.append(my_date_accquire->EEG_signal[i]);
    }

    qDebug() << endl;
    my_date_accquire->Attention_accquire(uart_buff_vec);
    Length_Of_ATT = my_date_accquire->Attention_vec.size();
    for(i=0;i<Length_Of_ATT;i++)
    {
        Length_Of_x++;
        curve_date_ch3_x.append(Length_Of_x);
        curve_date_ch3_y.append(my_date_accquire->Attention_vec[i]);

        curve_date_ch4_x.append(Length_Of_x);
        curve_date_ch4_y.append(my_date_accquire->Meditation_vec[i]);
    }
    rlt.att=my_date_accquire->Attention_vec[my_date_accquire->Attention_vec.size()-1];
    rlt.med=my_date_accquire->Meditation_vec[my_date_accquire->Meditation_vec.size()-1];
    rlt.att_med(rlt.att,rlt.med);
    rlt.att_sum+=rlt.att;
    rlt.med_sum+=rlt.med;

    delete my_date_accquire;

    qDebug() << endl;

    User_Filter my_User_Filter;

    my_User_Filter.Filter_IIR(curve_date_ch1_y,curve_date_ch2_y);

    for(i= 0; i< curve_date_ch2_y.size(); i++)
    {
        curve_date_ch2_x.append((double)i);
    }

    qDebug() << endl;

    eeg_iir_wave.append(curve_date_ch2_y);
    qDebug() << "eeg_iir_wave.size is"<<eeg_iir_wave.size();

    //????????????????svm????
    if(eeg_iir_wave.size() >= 30000)//30000??????????????????
    {
        rlt.updatedata(eeg_iir_wave);
        eeg_iir_wave.erase(eeg_iir_wave.begin(),eeg_iir_wave.end());
        rlt.svm_compute();
    }


    ui->label_time->setText("          "+QString::number(timelapse/60)
                            + "   min   "+QString::number(timelapse%60)+"   sec   ");

    curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
    ui->qwtPlot->replot();
    curve_date_ch1_x.clear();
    curve_date_ch1_y.clear();

    curve_date_ch2->setSamples(curve_date_ch2_x,curve_date_ch2_y);
    ui->qwtPlot_2->replot();
    curve_date_ch2_x.clear();
    curve_date_ch2_y.clear();

    curve_date_ch3->setSamples(curve_date_ch3_x,curve_date_ch3_y);
    ui->qwtPlot_3->replot();
    if(curve_date_ch3_x.size() >= 100)
    {
        curve_date_ch3_x.clear();
        curve_date_ch3_y.clear();
        Length_Of_x = 0;
    }

    curve_date_ch4->setSamples(curve_date_ch4_x,curve_date_ch4_y);
    ui->qwtPlot_4->replot();
    if(curve_date_ch4_x.size() >= 100)
    {
        curve_date_ch4_x.clear();
        curve_date_ch4_y.clear();
        Length_Of_x = 0;
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    curve_date_ch4_x.clear();
    curve_date_ch4_y.clear();
    curve_date_ch3_x.clear();
    curve_date_ch3_y.clear();
    Length_Of_x = 0;
}

//void MainWindow::on_checkBox_clicked(bool checked)
//{
//    save_control = checked;
//}


void MainWindow::result_show()
{
    MainWindow::hide();
    rlt.show();
}

void MainWindow::result_to_start(bool corr)
{
    if(corr)
        MainWindow::show();
}

