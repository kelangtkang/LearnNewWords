#ifndef NAPDULIEU_H
#define NAPDULIEU_H

#include <QWidget>
#include <QString>
#include <fstream>
#include <string>

class NapDuLieu : public QWidget
{
    Q_OBJECT

public:
    NapDuLieu();
    QString getTiengNga() const;
    QString getTiengViet() const;

public slots:
    void ChuyenTu(int count);

private:
    QString m_nTiengNga;
    QString m_nTiengViet;
    std::string m_nTuMoi[50][2];
};

#endif // NAPDULIEU_H
