#include "napdulieu.h"

using namespace std;

NapDuLieu::NapDuLieu() // Nap tu vao Array[][]
{
    /*
    m_nTuMoi[0][0] = "1";
    m_nTuMoi[0][1] = "A";
    m_nTuMoi[1][0] = "123";
    m_nTuMoi[1][1] = "ABC";
    m_nTuMoi[2][0] = "123456789";
    m_nTuMoi[2][1] = "ABCDEFGHI";
    m_nTuMoi[3][0] = "уголь горизонтального обстрела";
    m_nTuMoi[3][1] = "Goc tam";
    */

//    ifstream Data("Data.txt");
    ifstream Data("D:/Users/Ghost/Desktop/Data.txt");

/*
    if (Data.fail())
    {
        cout << "Failed to open this file!" << endl;
        return -1;
    }
*/

    string A[100];
    int i = 0;
    for (i = 0; i < 50; i++)
    {
        getline(Data, A[i]);
    }
    Data.close();

//Chuyen mang 1 chieu B thanh 2 chieu N
    int k = 0;
    int j;
    for (i = 0; i <= 19; i++)
    {
        for (j = 0; j <= 1; j++)
        {
            m_nTuMoi[i][j] = A[k];
            k++;
        }
    }
}

void NapDuLieu::ChuyenTu(int count) // Gan du lieu tu Array[][] vao chuoi Qstring
{
    m_nTiengNga = m_nTuMoi[count][1].c_str();
    m_nTiengViet = m_nTuMoi[count][0].c_str();
}

QString NapDuLieu::getTiengNga() const // Lay chuoi tieng Nga tu thuoc tinh
{
    return m_nTiengNga;
}
QString NapDuLieu::getTiengViet() const // Lay chuoi tieng Viet tu thuoc tinh
{
    return m_nTiengViet;
}
