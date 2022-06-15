#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

//QDEBUG
#include <QDebug>

using namespace std;

class date_accquire
{
public:
    date_accquire();

    void original_date_accquire(vector<unsigned char> &input_vec);

    void Attention_accquire(vector<unsigned char> &input_vec);

    QVector<double> EEG_signal;

    QVector<double> Attention_vec;

    QVector<double> Meditation_vec;

    int singal_length;
};
