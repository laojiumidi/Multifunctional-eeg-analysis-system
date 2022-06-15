#include "result.h"
#include "ui_result.h"

result::result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);
    ui->Emotion->setStyleSheet("background-color: rgb(170, 170, 127);");
    connect(ui->HOME,&QPushButton::clicked,this,&result::back_to_start);
    con = 0;
    po_con = 0;
}

result::~result()
{
    delete ui;
}

void result::svm_compute()
{
    svm_train.wave.wavedec(svm_train.wave,svm_train.wave.ydata.size());

    add_dense_points();

    if(svm_train.compute()==1)
    {
        ui->Emotion->setStyleSheet("background-color: rgb(255, 0, 0)");  //red-positive
        po_con++;
    }
    else if(svm_train.compute()==-1)
        ui->Emotion->setStyleSheet("background-color: rgb(0, 170, 255)"); //blue-negative
    con++;
}


//更新ydata,实际情况就是read数据
void result::updatedata(QVector<double> &input_vec)
{
    svm_train.wave.ydata.clear();
    svm_train.wave.ydata.append(input_vec);
}

void result::att_med(double attention, double medtation)
{
    QString a = QString::number(attention);
    QString m = QString::number(medtation);
    ui->Attention->setText(a);
    ui->Meditation->setText(m);
}

void result::set_dense_points()
{
    string line;
    ifstream f("/opt/ec/energy.txt");
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

void result::add_dense_points()
{
    for(int i=0;i<dim;i++)
        svm_train.dense_points[NN-1][i]=svm_train.wave.Energy[i];
}

//void result::result_show(bool corr)
//{
//    if(corr)
//        result::show();
//}

void result::back_to_start()
{
    emit back_start(true);
    result::hide();
}

void result::restart_color(bool corr)
{
    if(corr)
        ui->Emotion->setStyleSheet("background-color: rgb(170, 170, 127);");
}
