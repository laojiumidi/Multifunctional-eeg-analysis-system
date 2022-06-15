#ifndef WAVELET_H
#define WAVELET_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string.h>
//#include "testwin.h"
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <math.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_draw.h>

using namespace std;

typedef struct tagFilter
{
    double *lowFilterDec;  // 小波变换分解时对应的低通滤波器
    double *highFilterDec; // 小波变换分解时对应的高通滤波器
    int length;
}Filter;

class Wavelet
{
public:
    Wavelet();
    ~Wavelet();
    void InitDB();
    int Dwt(double *sourceData, int dataLen, Filter db, double *cA, double *cD);
    void wavedec(Wavelet ww, int size_1);
    void updata();
    double getdata();
    QVector<double> ydata;
    Filter db4;
    Filter m_db;
    int switch_dec = 0;
    //db小波系数
    double db4L[8]={-0.0106,0.0329,0.0308,-0.1870 ,-0.0280,0.6309,0.7148,0.2304};
    double db4H[8]={ -0.2304,0.7148,-0.6309,-0.0280,0.1870,0.0308,-0.0329,-0.0106};
    double Energy[5];
public slots:
    void slot_wavedec(bool dec);
};


#endif // WAVELET_H
