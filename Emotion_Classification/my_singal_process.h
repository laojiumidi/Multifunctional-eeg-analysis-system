#ifndef MY_SINGAL_PROCESS_H
#define MY_SINGAL_PROCESS_H

#include <filter_co.h>

#include <stdio.h>
#include <vector>
using namespace std;
#define N 10//The number of images which construct a time series for each pixel
#define PI 3.14159

class my_singal_process
{
public:
    my_singal_process(vector<double> &input_vec);

    vector<double> EEG_signal_filted;
private:
    double *ComputeLP( int FilterOrder );

    double *ComputeHP( int FilterOrder );

    double *ComputeNumCoeffs(int FilterOrder);

    double *ComputeDenCoeffs( int FilterOrder, double Lcutoff, double Ucutoff );

    double *TrinomialMultiply( int FilterOrder, double *b, double *c );

    void filter(int ord, double *a, double *b, int np, double *x, double *y);
};


#endif // MY_SINGAL_PROCESS_H
