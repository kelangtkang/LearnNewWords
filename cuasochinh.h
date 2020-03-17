#ifndef CUASOCHINH_H
#define CUASOCHINH_H

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QColor>
#include <QFontDialog>
#include <QColorDialog>
#include <QString>
#include <string>

class CuaSoChinh : public QWidget
{
    Q_OBJECT

public:
    CuaSoChinh();

public slots:
    void hienTuSau();
    void hienTuTruoc();
    void setFontNga();
    void setFontViet();
    void ngaColor();
    void vietColor();
    void windowColor();

private:
    QPushButton *m_preview;
    QPushButton *m_next;
    QPushButton *m_ngaFont;
    QPushButton *m_vietFont;
    QPushButton *m_ngaColor;
    QPushButton *m_vietColor;
    QPushButton *m_windowColor;
    QLabel *m_tiengNga;
    QLabel *m_tiengViet;
    QLabel *m_haiCham;
    int m_count;
};

#endif // CUASOCHINH_H
