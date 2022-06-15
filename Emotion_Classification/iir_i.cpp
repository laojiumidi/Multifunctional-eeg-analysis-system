#include "iir_i.h"

IIR_I::IIR_I()
{
    m_pNum = NULL;
    m_pDen = NULL;
    m_px = NULL;
    m_py = NULL;
    m_num_order = -1;
    m_den_order = -1;
}

void IIR_I::reset()
{
    for(int i = 0; i <= m_num_order; i++)
    {
        m_pNum[i] = 0.0;
    }
    for(int i = 0; i <= m_den_order; i++)
    {
        m_pDen[i] = 0.0;
    }
}

void IIR_I::setPara(double num[], int num_order, double den[], int den_order)
{
    delete[] m_pNum;
    delete[] m_pDen;
    delete[] m_px;
    delete[] m_py;
    m_pNum = new double[num_order + 1];
    m_pDen = new double[den_order + 1];
    m_num_order = num_order;
    m_den_order = den_order;
    m_px = new double[num_order + 1];
    m_py = new double[den_order + 1];
    for(int i = 0; i <= m_num_order; i++)
    {
        m_pNum[i] = num[i];
        m_px[i] = 0.0;
    }
    for(int i = 0; i <= m_den_order; i++)
    {
        m_pDen[i] = den[i];
        m_py[i] = 0.0;
    }
}

void IIR_I::resp(double data_in[], int M, double data_out[], int N)
{
    int i, k, il;
    for(k = 0; k < N; k++)
    {
        data_out[k] = 0.0;
        for(i = 0; i <= m_num_order; i++)
        {
            if( k - i >= 0)
            {
                il = ((k - i) < M) ? (k - i) : (M - 1);
                data_out[k] = data_out[k] + m_pNum[i] * data_in[il];
            }
        }
        for(i = 1; i <= m_den_order; i++)
        {
            if( k - i >= 0)
            {
                data_out[k] = data_out[k] - m_pDen[i] * data_out[k - i];
            }
        }
    }
}

/** \brief �˲�����������ֱ��I�ͽṹ
 *
 * \param data[] �����������ݣ�����ʱ�����˲���Ľ��
 * \param len data[] ����ĳ���
 * \return
 */
void IIR_I::filter(double data[], int len)
{
    int i, k;
    for(k = 0; k < len; k++)
    {
        m_px[0] = data[k];
        data[k] = 0.0;
        for(i = 0; i <= m_num_order; i++)
        {
            data[k] = data[k] + m_pNum[i] * m_px[i];
        }
        for(i = 1; i <= m_den_order; i++)
        {
            data[k] = data[k] - m_pDen[i] * m_py[i];
        }
        // we get the y value now
        m_py[0] = data[k];
        for(i = m_num_order; i >= 1; i--)
        {
            m_px[i] = m_px[i-1];
        }
        for(i = m_den_order; i >= 1; i--)
        {
            m_py[i] = m_py[i-1];
        }
    }
}
/** \brief �˲�����������ֱ��I�ͽṹ
 *
 * \param data_in[] ��������
 * \param data_out[] �����˲��������
 * \param len ����ĳ���
 * \return
 */
void IIR_I::filter(double data_in[], double data_out[], int len)
{
    int i, k;
    for(k = 0; k < len; k++)
    {
        m_px[0] = data_in[k];
        m_py[0] = 0.0;
        for(i = 0; i <= m_num_order; i++)
        {
            m_py[0] = m_py[0] + m_pNum[i] * m_px[i];
        }
        for(i = 1; i <= m_den_order; i++)
        {
            m_py[0] = m_py[0] - m_pDen[i] * m_py[i];
        }
        for(i = m_num_order; i >= 1; i--)
        {
            m_px[i] = m_px[i-1];
        }
        for(i = m_den_order; i >= 1; i--)
        {
            m_py[i] = m_py[i-1];
        }
        data_out[k] = m_py[0];
    }
}
