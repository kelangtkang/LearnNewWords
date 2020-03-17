#include "napdulieu.h"

using namespace std;

NapDuLieu::NapDuLieu(int iComboBox) // Nap tu vao Array[][]
{
    int i;
    string A[100];
    if (iComboBox == 0)
    {
        ifstream Data("Data/SoDem.txt");
//        ifstream Data("D:/Users/Ghost/Desktop/First App/Data/SoDem.txt");
        for (i = 0; i < 100; i++)
        {
            getline(Data, A[i]);
        }
        Data.close();
    }
    else if(iComboBox == 1)
    {
        ifstream Data("Data/SoThuTu.txt");
//        ifstream Data("D:/Users/Ghost/Desktop/First App/Data/SoThuTu.txt");
        for (i = 0; i < 100; i++)
        {
            getline(Data, A[i]);
        }
        Data.close();
    }
    else if(iComboBox == 2)
    {
        ifstream Data("Data/SoDem.txt");
//        ifstream Data("D:/Users/Ghost/Desktop/First App/Data/Data.txt");
        for (i = 0; i < 100; i++)
        {
            getline(Data, A[i]);
        }
        Data.close();
    }
    else if(iComboBox == 3){}
    else if(iComboBox == 4){}
    else if(iComboBox == 5){}
    else if(iComboBox == 6){}
    else if(iComboBox == 7){}
    else if(iComboBox == 8){}
    else if(iComboBox == 9){}

//Chuyen mang 1 chieu B thanh 2 chieu N
    int k(0);
    int j;
    for (i = 0; i < 50; i++)
    {
        for (j = 0; j < 2; j++)
        {
            m_nTuMoi[i][j] = A[k];
            k++;
        }
    }
}

void NapDuLieu::ChuyenTu(int count) // Gan du lieu tu Array[][] vao chuoi Qstring
{
    m_nTiengNga = m_nTuMoi[count][0].c_str();
    m_nTiengViet = m_nTuMoi[count][1].c_str();
}

QString NapDuLieu::getTiengNga() const // Lay chuoi tieng Nga tu thuoc tinh
{
    return m_nTiengNga;
}
QString NapDuLieu::getTiengViet() const // Lay chuoi tieng Viet tu thuoc tinh
{
    return m_nTiengViet;
}
