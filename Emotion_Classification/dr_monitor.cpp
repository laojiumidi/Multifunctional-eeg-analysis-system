#include "dr_monitor.h"
#include "ui_dr_monitor.h"

dr_monitor::dr_monitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dr_monitor)
{
    ui->setupUi(this);
    serial_open = false;
    monitor_finish = false;
    signal_good = false;
    timelapse = 0;
    connect(ui->back,&QPushButton::clicked,this,&dr_monitor::back_to_drivewin);
    connect(ui->start,&QPushButton::clicked,this,&dr_monitor::start);
    connect(ui->stop,&QPushButton::clicked,this,&dr_monitor::stop);
    connect(ui->restart,&QPushButton::clicked,this,&dr_monitor::restart);

    curve_date_ch1 = new QwtPlotCurve("Hr_Ch1");
    curve_date_ch1->setPen(Qt::green,0.5);//设置曲线颜色 粗细
    curve_date_ch1->attach(ui->qwtPlot);
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,100);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,0,100);

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
                                       QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3) );
    curve_date_ch1->setSymbol(symbol);

    readTimer = new QTimer();
    connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));
}

dr_monitor::~dr_monitor()
{
    delete ui;
    //    delete serial;
    //    delete readTimer;
    //    delete curve_date_ch1;
}

void dr_monitor::back_to_drivewin()
{
    emit back_drivewin(true);
    dr_monitor::hide();

    readTimer->stop();

    if(serial_open)
    {
        serial->clear();
        serial->close();
        serial->deleteLater();
        serial_open = false;
        monitor_finish = true;
    }
    else
        monitor_finish = false;

    curve_date_ch1_x.clear();
    curve_date_ch1_y.clear();
    ui->qwtPlot->replot();
    Length_Of_x = 0;
}

void dr_monitor::readMyCom()
{
    if(signal_good)
    {
        timelapse ++ ;
        //**************************//signal_good
    }

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

    my_date_accquire->Attention_accquire(uart_buff_vec);
    Length_Of_ATT = my_date_accquire->Attention_vec.size();
    for(i=0;i<Length_Of_ATT;i++)
    {
        Length_Of_x++;
        curve_date_ch1_x.append(Length_Of_x);
        curve_date_ch1_y.append(my_date_accquire->Attention_vec[i]);
    }
    attation=my_date_accquire->Attention_vec[my_date_accquire->Attention_vec.size()-1];
    if(attation > 0)
        signal_good = true;
    if(attation > 0 && attation<20)
        warn_times++ ;
    att_sum+=attation;

    delete my_date_accquire;

    qDebug() << endl;

    curve_date_ch1->setSamples(curve_date_ch1_x,curve_date_ch1_y);
    ui->qwtPlot->replot();
    if(curve_date_ch1_x.size() >= 100)
    {
        curve_date_ch1_x.clear();
        curve_date_ch1_y.clear();
        Length_Of_x = 0;
    }
}

void dr_monitor::start()
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

    curve_date_ch1_x.clear();
    curve_date_ch1_y.clear();
    ui->qwtPlot->replot();
    Length_Of_x = 0;

    attation = 0;
    att_sum = 0;
    warn_times = 0;

    readTimer->start(1000);

    start_datetime = QDateTime::currentDateTime();
}

void dr_monitor::stop()
{
    readTimer->stop();
}

void dr_monitor::restart()
{
    curve_date_ch1_x.clear();
    curve_date_ch1_y.clear();
    ui->qwtPlot->replot();
    Length_Of_x = 0;

    serial_open = true;

    attation = 0;
    att_sum = 0;
    timelapse = 0;
    warn_times = 0;

    readTimer->start(1000);

    start_datetime = QDateTime::currentDateTime();

}
