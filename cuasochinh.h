#ifndef CUASOCHINH_H
#define CUASOCHINH_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>

#include <QPushButton>
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QFrame>

#include <QColor>
#include <QFontDialog>
#include <QColorDialog>

#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QDir>

#include <string>
#include <vector>
#include <fstream>

#include "topic.h"
#include "options.h"

class CuaSoChinh : public QMainWindow
{
    Q_OBJECT

public:
    CuaSoChinh();
    void closeEvent(QCloseEvent *event);
    void writeSettings();
    void readSettings();
    void napDuLieu(int);
    void createGUI();
    void createMenu();

public slots:
    void changeTopic(int);
    void slotEditTopic();
    void slotUpdateTopic();
    void hienTuSau();
    void hienTuTruoc();

    void slotSetOnTop();
    void slotReset();
    void slotSetOptions(QFont, QFont, QString, QString, QString);

private:
    int m_index;
    int m_indexComboBox;
    Topic *m_topic;
    Options *m_options;

    QDir m_directory;
    QFileInfoList m_listData;
    std::vector <QString> m_vectorRus;
    std::vector <QString> m_vectorVi;

    QSettings setting;

    QPushButton *m_preview;
    QPushButton *m_next;

    QAction *m_exit;
    QAction *m_actionTopic, *m_actionOptions;
    QAction *m_actionOnTop, *m_actionReset;

    QComboBox *m_combo;
    QLabel *m_labelRus, *m_labelVi;
    QFrame *m_frame;
};

#endif // CUASOCHINH_H
