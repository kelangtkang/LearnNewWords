#ifndef CUASOCHINH_H
#define CUASOCHINH_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QSettings>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QColor>
#include <QFontDialog>
#include <QColorDialog>
#include <QString>

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
    void doiChuDe(int i);

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
    QAction *m_ngayThang;
    QAction *m_soDem;
    QAction *m_soThuTu;
//    QCheckBox *m_setOnTop;
    QMenu *m_font;
    QMenu *m_color;
    QMenu *m_onTop;
    QComboBox *m_combo;
    QLabel *m_tiengNga;
    QLabel *m_tiengViet;
    int m_count;
    int m_countComboBox;
};

#endif // CUASOCHINH_H
