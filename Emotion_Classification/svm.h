#ifndef SVM_H
#define SVM_H
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>
#include <sstream>
#include <string.h>
#include "ctype.h"
#include "time.h"
#include "wavelet.h"

#define NN 6//样本数总数
#define end_support_i 5
#define first_test_i 5
#define dim 5//训练样本维数
#define e_dim 1//目标维数
using namespace std;
class svm
{
public:
    svm();
    ~svm();
    //int N=     //样本数
    double C=2;//惩罚参数
    double tolerance=0.001;//ui与边界0,C之间的公差范围
    double eps=1e-3;//一个近似0的小数
    double two_sigma_squared=1;//RBF(Radial-Basis Function)核函数中的参数。sigma==(10/2)^1/2。
    double alph[end_support_i];//Lagrange multipiers
    double b;//threshold
    double error_cache[end_support_i];//存放non-bound样本误差
    int target[end_support_i];//训练样本的目标值
    int target1[end_support_i][e_dim];
    //double precomputed_self_dot_product[N];//预存dot_product_func(i,i)的值，以减少计算量
    double dense_points[NN][dim];//存放训练和测试样本，0-end_support_i-1训练;first_test_i-N测试
    double test_points[dim];
    double result;
    double result_final[NN-first_test_i][e_dim];
    double test_svm[NN-first_test_i][e_dim];
    double rate;
    //函数的申明
    int takeStep(int,int);
    int examineNonBound(int);
    int examineBound(int);
    int examineFirstChoice(int,double);
    int examineExample(int);
    double kernel_func(int,int);
    double learned_func(int);
    double dot_product_func(int,int);
    double kernel_func1(int);
    double dot_product_func1(int);
    //double error_rate();
    void setT();//设置目标值向量y
    void initialize();
    void smoExample();
    void right_rate();
    int compute();

    Wavelet wave;
};

#endif // SVM_H
