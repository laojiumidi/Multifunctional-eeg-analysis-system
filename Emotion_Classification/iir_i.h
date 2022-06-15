#ifndef IIR_I_H
#define IIR_I_H

#include <iostream>

class IIR_I
{
private:
    double *m_pNum;
    double *m_pDen;
    double *m_px;
    double *m_py;
    int m_num_order;
    int m_den_order;
public:
    IIR_I();
    void reset();
    void setPara(double num[], int num_order, double den[], int den_order);
    void resp(double data_in[], int M, double data_out[], int N);
    double filter(double data);
    void filter(double data[], int len);
    void filter(double data_in[], double data_out[], int len);
};

#endif // IIR_I_H
