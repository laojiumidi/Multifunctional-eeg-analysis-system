#include "svm.h"

svm::svm(){}

svm::~svm(){}

int svm::compute()
{
    //设置样本值矩阵
    //setX();
    //设置目标值矩阵
    setT();
    //有e种目标分法，end_support_i个样本，1个测试样本，分别对每一种情况进行训练。
    int i,j;
    for(int aa=first_test_i;aa<NN;aa++)
    {
        for(i=0;i<e_dim;i++)
        {//i=0;
            result=0;
            for(j=0;j<end_support_i;j++)
            {
                target[j]=target1[j][i];

            }
            smoExample();
            for(j=0;j<end_support_i;j++)
            {
                if(alph[j]>0)
                    result+=target[j]*alph[j]*kernel_func(j,aa);
            }
            result=result-b;
            if(result>0)
                result=1;
            else
                result=-1;

            //            result_final[aa-first_test_i][i]=result;
        }
    }
    return result;
}

//set targetT[]
void svm::setT()
{
    //为了在需要时方便地检索要处理的数据，数据应保存在文件中。
    string line;
    ifstream f("/opt/ec/energy_label.txt");
    vector<int> item;
    vector<vector<int> > arr;
    while(!f.eof()){
        int num=0;
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
            target1[i][j]=item[j];
        }
    }
}

void svm::smoExample()
{
    int numChanged=0;
    int examineAll=1;

    initialize();
    //以下两层循环，开始时检查所有样本，选择不符合KKT条件的两个乘子进行优化，选择成功，返回1，否则，返回0
    //所以成功了，numChanged必然>0，从第二遍循环时，不从整个样本中去寻找不符合KKT条件的两个乘子进行优化，
    //而是从非边界乘子中去寻找，因为非边界样本需要调整的可能性更大，边界样本往往不被调整而始终停留在边界上。
    //如果没找到，再从整个样本中去找，直到整个样本中再也找不到需要改变的乘子为止，此时算法结束。
    while(numChanged>0||examineAll)
    {
        numChanged=0;
        if(examineAll)
        {
            for(int k=0;k<end_support_i;k++)
            {
                numChanged+=examineExample(k);//examine all examples
            }
        }
        else
        {
            for(int k=0;k<end_support_i;k++)
            {
                if(alph[k]!=0&&alph[k]!=C)
                    numChanged+=examineExample(k);//loop k over all non-bound Lagrange multipliers
            }
        }
        if(examineAll==1)
        {
            examineAll=0;
        }
        else if(numChanged==0)
        {
            examineAll=1;
        }
    }
}

//假定第一个乘子ai(位置为i1)，examineExample(i1)首先检查，如果它超出tolerance而违背KKT条件，那么它就成为第一个乘子；
//然后，寻找第二个乘子(位置为i2),通过调用takeStep(i1,i2)来优化这两个乘子。
int svm::examineExample(int i1)
{
    int y1;
    double alph1,E1,r1;
    y1=target[i1];
    alph1=alph[i1];
    //alphi在initialize();中的初始化为0.0。
    if(alph1>0&&alph1<C)
        E1=error_cache[i1];
    else
        E1=learned_func(i1)-y1;//learned_func为计算输出函数
    r1=y1*E1;
    //违反KKT(Karush-Kuhn-Tucker)条件的判断
    /*
    KKT condition:
        if alphi == 0, yi*Ei >= 0;
        if 0 < alphi < C, yi*Ei == 0;
        if alphi == 0, yi*Ei <= 0;
    */
    if((r1>tolerance&&alph1>0)||(r1<-tolerance&&alph1<C))
    {
        /*使用三种方法选择第二个乘子:
        hierarchy one：在non-bound乘子中寻找maximum fabs(E1-E2)的样本
        hierarchy two：如果上面没取得进展,那么从随机位置查找non-boundary 样本
        hierarchy three：如果上面也失败，则从随机位置查找整个样本,改为bound样本
        */
        if (examineFirstChoice(i1,E1))//hierarchy one
        {
            return 1;
        }
        if (examineNonBound(i1))//hierarchy two
        {
            return 1;
        }

        if (examineBound(i1))//hierarchy three
        {
            return 1;
        }

    }
    //没有进展
    return 0;
}

//hierarchy one：在non-bound乘子中寻找maximum fabs(E1-E2)的样本
int svm::examineFirstChoice(int i1,double E1)
{
    int k,i2;
    double tmax;
    double E2,temp;
    for(i2=-1,tmax=0.0,k=0;k<end_support_i;k++)//end_support_i
    {
        if(alph[k]>0&&alph[k]<C)//choose non-bound multiplier
        {
            E2=error_cache[k];
            temp=fabs(E1-E2);
            if(temp>tmax)
            {
                tmax=temp;
                i2=k;
            }
        }
    }
    if(i2>=0)//如果没有non-bound multiplier，i2==-1。
    {
        if(takeStep(i1,i2))//If there has a positive progress, return 1.
        {
            return 1;
        }
    }
    return 0;
}
//hierarchy two：如果上面没取得进展,那么从随机位置查找non-boundary 样本
int svm::examineNonBound(int i1)
{
    int k;
    int k0 = rand()%end_support_i;
    int i2;
    for (k = 0; k < end_support_i; k++)
    {
        i2 = (k + k0) % end_support_i;//从随机位开始
        if (alph[i2] > 0.0 && alph[i2] < C)//查找non-bound样本
        {
            if (takeStep(i1, i2))//As soon as there has positive progress, return 1.
            {
                return 1;
            }
        }
    }
    return 0;
}
//hierarchy three：如果上面也失败，则从随机位置查找整个样本,(改为bound样本)
int svm::examineBound(int i1)
{
    int k;
    int k0 = rand()%end_support_i;

    int i2;
    for (k = 0; k < end_support_i; k++)
    {
        i2 = (k + k0) % end_support_i;//从随机位开始
        //if (alph[i2]= 0.0 || alph[i2]=C)//修改****************************************************
        {
            if (takeStep(i1, i2))//As soon as there has positive progress, return 1.
            {
                return 1;
            }
        }
    }
    return 0;
}
//takeStep()
//用于优化两个乘子，成功，返回1，否则，返回0
int svm::takeStep(int i1,int i2)
{
    int y1,y2,s;
    double alph1,alph2;//两个乘子的旧值
    double a1,a2;//两个乘子的新值
    double k11,k22,k12;
    double E1,E2,L,H,eta,Lobj,Hobj,delta_b;

    if(i1==i2)
        return 0;//当两个样本相同，不进行优化。
    //给变量赋值
    alph1=alph[i1];
    alph2=alph[i2];
    y1=target[i1];
    y2=target[i2];
    if(alph1>0&&alph1<C)
        E1=error_cache[i1];
    else
        E1=learned_func(i1)-y1;//learned_func(int)为非线性的评价函数，即输出函数
    if(alph2>0&&alph2<C)
        E2=error_cache[i2];
    else
        E2=learned_func(i2)-y2;
    s=y1*y2;
    //计算乘子的上下限
    //y1或y2的取值为1或-1(Binary Case)
    if(y1==y2)
    {
        double gamma=alph1+alph2;
        if(gamma>C)
        {
            L=gamma-C;
            H=C;
        }
        else
        {
            L=0;
            H=gamma;
        }
    }
    else
    {
        double gamma=alph1-alph2;
        if(gamma>0)
        {
            L=0;
            H=C-gamma;
        }
        else
        {
            L=-gamma;
            H=C;
        }
    }//计算乘子的上下限
    if(fabs(L-H) < eps)//L equals H
    {
        return 0;
    }
    //计算eta
    k11=kernel_func(i1,i1);//kernel_func(int,int)为核函数
    k22=kernel_func(i2,i2);
    k12=kernel_func(i1,i2);
    eta=k11+k22-2*k12;//eta是>=0的。
    if(eta>0)
    {
        a2=alph2+y2*(E1-E2)/eta;//计算新的alph2
        //调整a2，使其处于可行域
        if(a2<L)
        {
            a2=L;
        }
        if(a2>H)
        {
            a2=H;
        }
    }
    else//此时eta==0，得分别从端点H,L求目标函数值Lobj,Hobj，然后设a2为求得最大目标函数值的端点值
    {
        double c1=eta/2;
        double c2=y2*(E1-E2)-eta*alph2;
        Lobj=c1*L*L+c2*L;
        Hobj=c1*H*H+c2*H;
        if(Lobj>Hobj+eps)//eps==1e-3，是一个近似0的小数。
            a2=L;
        else if(Lobj<Hobj-eps)
            a2=H;
        else
            a2=alph2;//加eps的目的在于，使得Lobj与Hobj尽量分开，如果，很接近，就认为没有改进(make progress)
    }
    if(a2<eps)
        a2=0;
    if(a2>C-eps)
        a2=C;
    if(fabs(a2-alph2)<eps*(a2+alph2+eps))
    {
        return 0;
    }
    /***********************************
    计算新的a1
    ***********************************/
    a1=alph1-s*(a2-alph2);
    if(a1<0)//调整a1,使其符合条件*****??????????????????????????????????????????
    {
        a2+=s*a1;
        a1=0;
    }
    else if(a1>C)
    {
        double t=a1-C;
        a2+=s*t;
        a1=C;
    }
    //更新阀值b
    //After each step, b is re-computed.
    {
        double b1,b2,bnew;
        if(a1>0&&a1<C)
        {
            bnew=b+E1 + y1*(a1-alph1)*k11 + y2*(a2-alph2)*k12;

        }
        else
        {
            if(a2>0&&a2<C)
                bnew=b+E2 + y1*(a1-alph1)*k12 + y2*(a2-alph2)*k22;

            else
            {
                b1=b+E1+y1*(a1-alph1)*k11+y2*(a2-alph2)*k12;
                b2=b+E2+y1*(a1-alph1)*k12+y2*(a2-alph2)*k22;
                bnew=(b1+b2)/2;

            }
        }
        delta_b=bnew-b;
        b=bnew;
    }

    //对于线性情况，要更新权向量，这里不用了
    //更新error_cache，对取得进展的a1,a2,所对应的i1,i2的error_cache[i1]=error_cache[i2]=0
    {
        double t1=y1*(a1-alph1);
        double t2=y2*(a2-alph2);
        for(int i=0;i<end_support_i;i++)
        {
            if(0<alph[i]&&alph[i]<C)

                error_cache[i]+=t1*kernel_func(i1,i)+t2*(kernel_func(i2,i))-delta_b;
        }
        error_cache[i1]=0.0;
        error_cache[i2]=0.0;
    }
    alph[i1]=a1;//store a1 in the alpha array
    alph[i2]=a2;//store a2 in the alpha array
    return 1;//说明已经取得进展
}

//learned_func(int)
//评价分类学习函数 ui
double svm::learned_func(int k)
{
    double s=0.0;
    for(int i=0;i<end_support_i;i++)
    {
        if(alph[i]>0)//alph[i]是属于[0, C]的。此行可省略。
        {
            s+=alph[i]*target[i]*kernel_func(i,k);
        }
    }
    s-=b;
    return s;
}
//计算点积函数dot_product_func(int,int)
double svm::dot_product_func(int i1,int i2)
{
    double dot=0;
    for(int i=0;i<dim;i++)
    {
        dot+=dense_points[i1][i]*dense_points[i2][i];
    }
    return dot;
}
//The kernel_func(int, int) is RBF(Radial-Basis Function).
//K(Xi, Xj)=exp(-||Xi-Xj||^2/(2*sigma^2))
double svm::kernel_func(int i1,int i2)
{
    long double s=dot_product_func(i1,i2);
    s*=-2;
    //s+=precomputed_self_dot_product[i1]+precomputed_self_dot_product[i2];//应用余弦定理
    s+=dot_product_func(i1,i1)+dot_product_func(i2,i2);
    s=exp(-s/two_sigma_squared);
    return s;
}
//初始化initialize()
void svm::initialize()
{
    int i;
    //初始化阀值b为0
    b=0.0;
    //初始化alph[]为0
    for(i=0;i<end_support_i;i++)
    {
        alph[i]=0.0;
        error_cache[i]=0.0;
    }
}

