#ifndef IIR_II_H
#define IIR_II_H

#include <iostream>

class IIR_II
{
public:
    IIR_II();
    void reset();
    void setPara(double num[], int num_order, double den[], int den_order);
    void resp(double data_in[], int M, double data_out[], int N);
    double filter(double data);
    void filter(double data[], int len);
    void filter(double data_in[], double data_out[], int len);
protected:
    private:
    double *m_pNum;
    double *m_pDen;
    double *m_pW;
    int m_num_order;
    int m_den_order;
    int m_N;
};

#endif // IIR_II_H
