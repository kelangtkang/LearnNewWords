#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFontComboBox>
#include <QCheckBox>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QGroupBox>

#include <QDir>
#include <array>

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QFont, QFont, QString, QString, QString);
    void createGUI(QFont, QFont, QString, QString, QString);
    QGroupBox* createGroupText(const QString, QComboBox*, QComboBox*, QCheckBox*, QCheckBox*);
    QGroupBox* createGroupColor(const QString);

private:
    QFrame *m_frame;
    QLabel *m_labelRus, *m_labelVi;

    QFontComboBox *m_comboFamilyRus, *m_comboFamilyVi;
    QComboBox *m_comboSizeRus, *m_comboSizeVi;
    QCheckBox *m_checkItalicRus, *m_checkItalicVi;
    QCheckBox *m_checkBoldRus, *m_checkBoldVi;

    QPushButton *m_buttonOK, *m_buttonCancel;
    QPushButton *m_buttonFontRus, *m_buttonFontVi;
    QPushButton *m_buttonColorRus, *m_buttonColorVi;

signals:
    void signalSetOptions(QFont, QFont, QString, QString, QString);

public slots:
    void slotSetOptions();
    void slotSetFamilyRus(QString);
    void slotSetFamilyVi(QString);
    void slotSetSizeRus(QString);
    void slotSetSizeVi(QString);
    void slotSetBoldRus(int);
    void slotSetBoldVi(int);
    void slotSetItalicRus(int);
    void slotSetItalicVi(int);
};

#endif // OPTIONS_H
