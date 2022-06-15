#include "my_singal_process.h"

my_singal_process::my_singal_process(vector<double> &input_vec)
{
    /* filter */
    int singal_length = input_vec.size();
    double *x_buff;
    double *y_buff;
    x_buff = (double *)malloc(sizeof(double)*singal_length);
    y_buff = (double *)malloc(sizeof(double)*singal_length);

    for(int i=0;i<singal_length;i++)
    {
        x_buff[i] = input_vec[i];
    }
    int FiltOrd = 119;
    filter(FiltOrd, DEN, NUM, singal_length, x_buff, y_buff);
    for(int i=0;i<singal_length;i++)
    {
        EEG_signal_filted.push_back(y_buff[i]);
    }
}

double *my_singal_process::ComputeLP(int FilterOrder)
{
    double *NumCoeffs;
    int m;
    int i;
    NumCoeffs = (double *)calloc( FilterOrder+1, sizeof(double) );
    if( NumCoeffs == NULL ) return( NULL );
    NumCoeffs[0] = 1;
    NumCoeffs[1] = FilterOrder;
    m = FilterOrder/2;
    for( i=2; i <= m; ++i)
    {
        NumCoeffs[i] =(double) (FilterOrder-i+1)*NumCoeffs[i-1]/i;
        NumCoeffs[FilterOrder-i]= NumCoeffs[i];
    }
    NumCoeffs[FilterOrder-1] = FilterOrder;
    NumCoeffs[FilterOrder] = 1;
    return NumCoeffs;
}

double *my_singal_process::ComputeHP(int FilterOrder)
{
    double *NumCoeffs;
    int i;
    NumCoeffs = ComputeLP(FilterOrder);
    if(NumCoeffs == NULL ) return( NULL );
    for( i = 0; i <= FilterOrder; ++i)
        if( i % 2 ) NumCoeffs[i] = -NumCoeffs[i];
    return NumCoeffs;
}

double *my_singal_process::ComputeNumCoeffs(int FilterOrder)
{
    double *TCoeffs;
    double *NumCoeffs;
    int i;
    NumCoeffs = (double *)calloc( 2*FilterOrder+1, sizeof(double) );
    if( NumCoeffs == NULL ) return( NULL );
    TCoeffs = ComputeHP(FilterOrder);
    if( TCoeffs == NULL ) return( NULL );
    for( i = 0; i <FilterOrder; ++i)
    {
        NumCoeffs[2*i] = TCoeffs[i];
        NumCoeffs[2*i+1] = 0.0;
    }
    NumCoeffs[2*FilterOrder] = TCoeffs[FilterOrder];
    free(TCoeffs);
    return NumCoeffs;
}

double *my_singal_process::ComputeDenCoeffs(int FilterOrder, double Lcutoff, double Ucutoff)
{
    int k;//loop variables
    double theta;//PI * (Ucutoff - Lcutoff)/2.0
    double cp;//cosine of phi
    double st;//sine of theta
    double ct;//cosine of theta
    double s2t;//sine of 2*theta
    double c2t;//cosine 0f 2*theta
    double *RCoeffs;//z^-2 coefficients
    double *TCoeffs;//z^-1 coefficients
    double *DenomCoeffs;//dk coefficients
    double PoleAngle;//pole angle
    double SinPoleAngle;//sine of pole angle
    double CosPoleAngle;//cosine of pole angle
    double a;//workspace variables
    cp = cos(PI * (Ucutoff + Lcutoff)/2.0);
    theta = PI * (Ucutoff - Lcutoff)/2.0;
    st = sin(theta);
    ct = cos(theta);
    s2t = 2.0*st*ct;//sine of 2*theta
    c2t = 2.0*ct*ct - 1.0;//cosine of 2*theta
    RCoeffs = (double *)calloc( 2 * FilterOrder, sizeof(double) );
    TCoeffs = (double *)calloc( 2 * FilterOrder, sizeof(double) );
    for( k = 0; k <FilterOrder; ++k )
    {
        PoleAngle = PI * (double)(2*k+1)/(double)(2*FilterOrder);
        SinPoleAngle = sin(PoleAngle);
        CosPoleAngle = cos(PoleAngle);
        a = 1.0 + s2t*SinPoleAngle;
        RCoeffs[2*k] = c2t/a;
        RCoeffs[2*k+1] = s2t*CosPoleAngle/a;
        TCoeffs[2*k] = -2.0*cp*(ct+st*SinPoleAngle)/a;
        TCoeffs[2*k+1] = -2.0*cp*st*CosPoleAngle/a;
    }
    DenomCoeffs = TrinomialMultiply(FilterOrder, TCoeffs, RCoeffs );
    free(TCoeffs);
    free(RCoeffs);
    DenomCoeffs[1] = DenomCoeffs[0];
    DenomCoeffs[0] = 1.0;
    for( k = 3; k <= 2*FilterOrder; ++k )
        DenomCoeffs[k] = DenomCoeffs[2*k-2];
    return DenomCoeffs;
}

double *my_singal_process::TrinomialMultiply(int FilterOrder, double *b, double *c)
{
    int i, j;
    double *RetVal;
    RetVal = (double *)calloc( 4 * FilterOrder, sizeof(double) );
    if( RetVal == NULL ) return( NULL );
    RetVal[2] = c[0];
    RetVal[3] = c[1];
    RetVal[0] = b[0];
    RetVal[1] = b[1];
    for( i = 1; i <FilterOrder; ++i )
    {
        RetVal[2*(2*i+1)] += c[2*i] * RetVal[2*(2*i-1)] - c[2*i+1] * RetVal[2*(2*i-1)+1];
        RetVal[2*(2*i+1)+1] += c[2*i] * RetVal[2*(2*i-1)+1] + c[2*i+1] * RetVal[2*(2*i-1)];
        for( j = 2*i; j> 1; --j )
        {
            RetVal[2*j] += b[2*i] * RetVal[2*(j-1)] - b[2*i+1] * RetVal[2*(j-1)+1] +
                    c[2*i] * RetVal[2*(j-2)] - c[2*i+1] * RetVal[2*(j-2)+1];
            RetVal[2*j+1] += b[2*i] * RetVal[2*(j-1)+1] + b[2*i+1] * RetVal[2*(j-1)] +
                    c[2*i] * RetVal[2*(j-2)+1] + c[2*i+1] * RetVal[2*(j-2)];
        }
        RetVal[2] += b[2*i] * RetVal[0] - b[2*i+1] * RetVal[1] + c[2*i];
        RetVal[3] += b[2*i] * RetVal[1] + b[2*i+1] * RetVal[0] + c[2*i+1];
        RetVal[0] += b[2*i];
        RetVal[1] += b[2*i+1];
    }
    return RetVal;
}

void my_singal_process::filter(int ord, double *a, double *b, int np, double *x, double *y)
{
    int i,j;
    y[0]=b[0] * x[0];
    for (i=1;i<ord+1;i++)
    {
        y[i]=0.0;
        for (j=0;j<i+1;j++)
            y[i]=y[i]+b[j]*x[i-j];
        for (j=0;j<i;j++)
            y[i]=y[i]-a[j+1]*y[i-j-1];
    }
    for (i=ord+1;i<np+1;i++)
    {
        y[i]=0.0;
        for (j=0;j<ord+1;j++)
            y[i]=y[i]+b[j]*x[i-j];
        for (j=0;j<ord;j++)
            y[i]=y[i]-a[j+1]*y[i-j-1];
    }
}

