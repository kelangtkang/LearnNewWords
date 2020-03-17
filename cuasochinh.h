#ifndef CUASOCHINH_H
#define CUASOCHINH_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QColor>
#include <QFontDialog>
#include <QColorDialog>
#include <QString>
#include <string>

class CuaSoChinh : public QMainWindow //: public QWidget
{
    Q_OBJECT

public:
    CuaSoChinh();

public slots:
    void hienTuSau();
    void hienTuTruoc();
    void setFontNga();
    void setFontViet();
    void setOnTop();
    void ngaColor();
    void vietColor();
    void windowColor();

private:
    void createMenu();

    QPushButton *m_preview;
    QPushButton *m_next;
    QAction *m_ngaFont;
    QAction *m_vietFont;
    QAction *m_ngaColor;
    QAction *m_vietColor;
    QAction *m_windowColor;
    QAction *m_setOnTop;
//    QCheckBox *m_setOnTop;
    QMenu *m_font;
    QMenu *m_color;
    QMenu *m_onTop;
    QLabel *m_tiengNga;
    QLabel *m_tiengViet;
    int m_count;
};

#endif // CUASOCHINH_H
