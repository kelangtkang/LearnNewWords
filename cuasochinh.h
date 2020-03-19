#ifndef CUASOCHINH_H
#define CUASOCHINH_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>

#include <QColor>
#include <QFontDialog>
#include <QColorDialog>

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QDir>

#include <string>
#include <vector>
#include <fstream>

class CuaSoChinh : public QMainWindow
{
    Q_OBJECT

public:
    CuaSoChinh();
    void napDuLieu(int);
    void createGUI();
    void createMenu();

public slots:
    void changeTopic(int);
    void hienTuSau();
    void hienTuTruoc();
    void setFontNga();
    void setFontViet();
    void setOnTop();
    void ngaColor();
    void vietColor();
    void windowColor();

private:
    int m_index;
    int m_indexComboBox;
    QFileInfoList m_listData;

    std::vector <QString> m_vectorRus;
    std::vector <QString> m_vectorVi;

    QPushButton *m_preview;
    QPushButton *m_next;

    QAction *m_addTopic, *m_exit;
    QAction *m_ngaFont, *m_vietFont;
    QAction *m_ngaColor, *m_vietColor, *m_windowColor;
    QAction *m_setOnTop;

    QComboBox *m_combo;
    QLabel *m_labelRus, *m_labelVi;
};

#endif // CUASOCHINH_H
