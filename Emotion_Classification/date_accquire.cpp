#include "date_accquire.h"

date_accquire::date_accquire()
{
    ;
}

void date_accquire::original_date_accquire(vector<unsigned char> &input_vec)
{
    unsigned char targetBuff_2[5] = {0xAA,0xAA,0x04,0x80,0x02};

    vector<unsigned char> targetVec_2(targetBuff_2,targetBuff_2 + 5);

    vector<unsigned char>::iterator posIt;

    unsigned char high_byte;

    unsigned char low_byte;

    unsigned char check_sum;

    double one_point;

    while(1)
    {
        if(input_vec.size() < 8)
        {
            break;
        }
        posIt= search(input_vec.begin(),input_vec.end(),targetVec_2.begin(),targetVec_2.end());

        if((input_vec.end() - posIt) < 8)
        {
            break;
        }
        high_byte = *(posIt+5);

        low_byte = *(posIt+6);

        check_sum = *(posIt+7);

        unsigned char sum  =((0x80 + 0x02 + high_byte + low_byte)^0xFFFFFFFF)&0xFF;

        if(sum == check_sum)
        {
            one_point = (double)((high_byte << 8) | low_byte);
            one_point=one_point*1.8/4096/2000;
            EEG_signal.push_back(one_point);
        }
        else
        {
            cout << "check fail.!" << endl;
        }
        input_vec.erase(posIt,posIt+8);
        if(input_vec.size() < 8)
        {
            break;
        }
        posIt= search(input_vec.begin(),input_vec.end(),targetVec_2.begin(),targetVec_2.end());

        if(input_vec.end() == posIt)
        {
            break;
        }
    }
    cout << "EEG_signal size is " << EEG_signal.size() << endl;
}

void date_accquire::Attention_accquire(vector<unsigned char> &input_vec)
{
    unsigned char targetBuff_1[4] = {0xaa,0xaa,0x20,0x02};

    vector<unsigned char> targetVec_1(targetBuff_1,targetBuff_1 + 4);

    vector<unsigned char>::iterator posIt;

    unsigned char Attention_32;

    unsigned char Meditation_34;

    while(1)
    {
        if(input_vec.size() < 36)
        {
            break;
        }
        posIt= search(input_vec.begin(),input_vec.end(),targetVec_1.begin(),targetVec_1.end());

        if((input_vec.end() - posIt)<36)
        {
            break;
        }

        if(((*(posIt+31)) == 0x04)&&((*(posIt+33)) == 0x05))
        {
            Attention_32 = *(posIt+32);

            Meditation_34 = *(posIt+34);

            Attention_vec.push_back(Attention_32);

            Meditation_vec.push_back(Meditation_34);
        }
        else
        {
            cout << "big packet err.!" << endl;
        }

        input_vec.erase(posIt,posIt+36);

        if(input_vec.size() < 36)
        {
            break;
        }

        posIt= search(input_vec.begin(),input_vec.end(),targetVec_1.begin(),targetVec_1.end());

        if(input_vec.end() == posIt)
        {
            break;
        }
    }
    qDebug() << "big packet out ";
}


