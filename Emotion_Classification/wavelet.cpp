#include "wavelet.h"


Wavelet::~Wavelet(){}

Wavelet::Wavelet()
{
    InitDB();
}

void Wavelet::InitDB()
{
    db4.length=8;
    db4.lowFilterDec=new double[db4.length];
    memcpy(db4.lowFilterDec,db4L,db4.length*sizeof(double));
    db4.highFilterDec=new double[db4.length];
    memcpy(db4.highFilterDec,db4H,db4.length*sizeof(double));
}

int Wavelet::Dwt(double *sourceData, int dataLen, Filter db, double *cA, double *cD)
{
    if(dataLen < 2)
        return -1;
    if((NULL == sourceData)||(NULL == cA)||(NULL == cD))
        return -1;

    m_db = db;
    int filterLen = m_db.length;
    int n,k,p;
    int decLen = (dataLen+filterLen-1)/2;
    double tmp=0;
    //cout<<"decLen="<<decLen<<endl;

    for(n=0; n<decLen; n++)
    {
        cA[n] = 0;
        cD[n] = 0;
        for(k=0; k<filterLen; k++)
        {
            p = 2*n-k+1;

            //信号边沿对称延拓
            if((p<0)&&(p>=-filterLen+1))
                tmp = sourceData[-p-1];
            else if((p>dataLen-1)&&(p<=dataLen+filterLen-2))
                tmp = sourceData[2*dataLen-p-1];
            else if((p>=0)&&(p<dataLen-1))
                tmp = sourceData[p];
            else
                tmp = 0;

            //分解后的近似部分序列-低频部分
            cA[n] += m_db.lowFilterDec[k]*tmp;

            //分解后的细节部分序列-高频部分
            cD[n] += m_db.highFilterDec[k]*tmp;
        }

    }

    return decLen;
}

void Wavelet::wavedec(Wavelet ww, int size_1)
{
    int decLen;
    int i;
    double *ca,*cd;
    ca  = new double[size_1];
    cd  = new double[size_1];

    double CA_1[size_1];
    double source[size_1];
    //    ifstream in("data2.txt");
    //    for(int i=0;i<size_1;i++)
    //        in>>source[i];
    //    in.close();
    for(i=0;i<size_1;i++)
        source[i]=ydata[i];
    decLen = ww.Dwt(source,size_1,db4,ca,cd);
    for (i=0; i<decLen; i++)
    {
        CA_1[i]=ca[i];
    }
    /*****************************/
    int size_2=decLen;
    double CA_2[size_2];
    double CD_2[size_2];
    decLen = ww.Dwt(CA_1,size_2,db4,ca,cd);
    for (i=0; i<decLen; i++)
    {
        CA_2[i]=ca[i];
        CD_2[i]=cd[i];
    }
    /*****************************/
    int size_3=decLen;
    double CA_3[size_3];
    double CD_3[size_3];
    decLen = ww.Dwt(CA_2,size_3,db4,ca,cd);
    for (i=0; i<decLen; i++)
    {
        CA_3[i]=ca[i];
        CD_3[i]=cd[i];
    }
    /*****************************/
    int size_4=decLen;
    double CA_4[size_4];
    double CD_4[size_4];
    decLen = ww.Dwt(CA_3,size_4,db4,ca,cd);
    for (i=0; i<decLen; i++)
    {
        CA_4[i]=ca[i];
        CD_4[i]=cd[i];
    }
    /*****************************/
    int size_5=decLen;
    double CA_5[size_5];
    double CD_5[size_5];
    decLen = ww.Dwt(CA_4,size_5,db4,ca,cd);
    for (i=0; i<decLen; i++)
    {
        CA_5[i]=ca[i];
        CD_5[i]=cd[i];
    }
    delete ca;
    delete cd;

    double sum;
    sum=0;
    for(i=0;i<size_4;i++)
    {
        sum+=pow(double(CD_4[i]),2);
    }
    Energy[0]=sqrt(sum);

    sum=0;
    for(i=0;i<size_3;i++)
    {
        sum+=pow(double(CD_3[i]),2);
    }
    Energy[1]=sqrt(sum);

    sum=0;
    for(i=0;i<size_5;i++)
    {
        sum+=pow(double(CD_5[i]),2);
    }
    Energy[2]=sqrt(sum);

    sum=0;
    for(i=0;i<size_2;i++)
    {
        sum+=pow(double(CD_2[i]),2);
    }
    Energy[3]=sqrt(sum);

    sum=0;
    for(i=0;i<size_5;i++)
    {
        sum+=pow(double(CA_5[i]),2);
    }
    Energy[4]=sqrt(sum);

    //    ofstream out("energy.txt",ios::app);
    //    for(i=0;i<5;i++)
    //        out<<Energy[i]<<endl;
    //    out.close();
}

double Wavelet::getdata()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+ qrand());

    double data_min=1;
    double data_max=9;
    double data_rand;

    data_rand=data_min+qrand()/(double)(RAND_MAX/(data_max-data_min));

    return data_rand;
}
