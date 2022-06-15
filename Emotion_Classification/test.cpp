#include "test.h"
#include "ui_test.h"

test::test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    set_dense_points();
    init_qwtplot(ui->qwtplot);
    ui->label_result->setStyleSheet("background-color: rgb(170, 170, 127);");

    connect(ui->home,&QPushButton::clicked,this,&test::to_home_slot);
    connect(ui->start,&QPushButton::clicked,this,&test::start_slot);
    connect(&computeTimer,SIGNAL(timeout()),this,SLOT(svm_compute()));
    connect(&updateTimer,SIGNAL(timeout()),this,SLOT(updatedataSlot()));
}

test::~test()
{
    delete ui;
}

void test::init_qwtplot(QwtPlot *qwtplot)
{
    //初始化xdata,x对应长度为1的坐标，y初始全为0
    for(int i=1001;i>=1;i--)
    {
        xdata.append(1-double(i)/1000);
        svm_train.wave.ydata.append(0);
    }

    plotName = "Real Time EEG Data";
    qwtplot->setTitle(plotName);
    qwtplot->setCanvasBackground(Qt::gray);//背景
    qwtplot->insertLegend(new QwtLegend(),QwtPlot::LeftLegend);//标签

    curve = new QwtPlotCurve();
    curve->setTitle("脑电信号");//曲线名字
    curve->setPen( Qt::red, 1 );//曲线的颜色 宽度;

    QTime curtime;
    curtime=curtime.currentTime();
    qwtplot->setAxisTitle(QwtPlot::xBottom, "time");
    qwtplot->setAxisTitle(QwtPlot::yLeft,"EEG");
    qwtplot->setAxisScale(QwtPlot::yLeft,1,9,1);
    qwtplot->setAxisScale(QwtPlot::xBottom,0,1,0.1);

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->enableX( true );//设置网格线
    grid->enableY( true );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach(qwtplot);

    //    connect(&updateTimer,SIGNAL(timeout()),this,SLOT(updatedataSlot()));
}

void test::svm_compute()
{
    svm_train.wave.wavedec(svm_train.wave,128);
    add_dense_points();
    //    svm_train.compute();
    //    cout<<svm_train.result_final[1][1]<<endl;
    if(svm_train.compute()==1)
        ui->label_result->setStyleSheet("background-color: rgb(255, 0, 0);");
    else if(svm_train.compute()==-1)
        ui->label_result->setStyleSheet("background-color: rgb(0, 170, 255);");
}

//更新ydata,实际情况就是read数据
void test::updatedataSlot()
{
    //static QTime dataTime(QTime::currentTime());
    //long int eltime = dataTime.elapsed();
    //static int lastpointtime = 0;

    //int size = (eltime - lastpointtime);

    int size = 5;    //frequency = 500 Hz

    //    if(size>0)//有数据传入
    //    {
    svm_train.wave.ydata.erase(svm_train.wave.ydata.begin(),svm_train.wave.ydata.begin()+size);//擦除多余的数据
    for(int i=1;i<size+1;i++)
    {
//        double data=data_eeg.EEG_signal.end();
        svm_train.wave.ydata.append(svm_train.wave.getdata());
        curve->setSamples(xdata,svm_train.wave.ydata);
        curve->attach(ui->qwtplot);
        ui->qwtplot->replot();
    }
    //lastpointtime = eltime;
    //    }
}

void test::test_slot(bool corr)
{
    if(corr)
        test::show();
}

void test::to_home_slot()
{
    emit to_home(true);
    updateTimer.stop();
    computeTimer.stop();

    svm_train.wave.ydata.erase(svm_train.wave.ydata.begin(),svm_train.wave.ydata.end());
    for(int i=1001;i>=1;i--)
    {
        xdata.append(1-double(i)/1000);
        svm_train.wave.ydata.append(0);
    }
    curve->setSamples(xdata,svm_train.wave.ydata);
    curve->attach(ui->qwtplot);
    ui->qwtplot->replot();

    test::close();
}

void test::start_slot()
{
    updateTimer.start(10);
    computeTimer.start(1000);
}

void test::set_dense_points()
{
    string line;
    ifstream f("energy.txt");
    vector<double> item;
    vector<vector<double> > arr;
    while(!f.eof()){
        double num=0;
        getline(f,line);
        if(line.empty())continue;
        istringstream input(line);
        item.clear();
        while(!input.eof()){
            input>>num;
            item.push_back(num);
        }
        arr.push_back(item);
    }
    f.close();
    for (int i=0;i<(int)arr.size();i++)
    {
        item=arr[i];
        for (int j=0;j<(int)item.size();j++)
        {
            svm_train.dense_points[i][j]=item[j];
        }
    }
}

void test::add_dense_points()
{
    for(int i=0;i<dim;i++)
        svm_train.dense_points[NN-1][i]=svm_train.wave.Energy[i];
}
