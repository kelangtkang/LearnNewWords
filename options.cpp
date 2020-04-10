#include "options.h"
#include <QDebug>

Options::Options(QFont fontRus, QFont fontVi, QString colorRus, QString colorVi, QString colorWindow) : QDialog()
{
    this -> createGUI(fontRus, fontVi, colorRus, colorVi, colorWindow);
}

void Options::createGUI(QFont fontRus, QFont fontVi, QString colorRus, QString colorVi, QString colorWindow)
{
    //Tao nut chuc nang
    m_buttonOK = new QPushButton;
    m_buttonOK -> setText("OK");
    m_buttonOK -> setFont(QFont("Calibre", 10));
    m_buttonOK -> setFixedSize(80, 24);
    QObject::connect(m_buttonOK, SIGNAL(clicked()), this, SLOT(slotSetOptions()));

    m_buttonCancel = new QPushButton();
    m_buttonCancel -> setText("Cancel");
    m_buttonCancel -> setFont(QFont("Calibre", 10));
    m_buttonCancel -> setFixedSize(80, 24);
    m_buttonCancel -> setCursor(Qt::PointingHandCursor);
    QObject::connect(m_buttonCancel, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *layoutButton = new QHBoxLayout;
    layoutButton -> addWidget(m_buttonOK, 1, Qt::AlignRight);
    layoutButton -> addWidget(m_buttonCancel, 0, Qt::AlignRight);

    //Tao man hinh truc quan
    m_labelRus = new QLabel("Русский Язык");
    m_labelRus -> setFont(fontRus);
    m_labelRus -> setAlignment(Qt::AlignCenter);
    m_labelRus -> setAutoFillBackground(true);

    m_labelVi = new QLabel("Tiếng Việt", this);
    m_labelVi -> setFont(fontVi);
    m_labelVi -> setAlignment(Qt::AlignCenter);
    m_labelVi -> setAutoFillBackground(true);

    QVBoxLayout *layoutText = new QVBoxLayout;
    layoutText -> addWidget(m_labelRus);
    layoutText -> addWidget(m_labelVi);

    m_frame = new QFrame;
    m_frame -> setFrameShape(QFrame::Box);
    m_frame -> setLineWidth(1);
    m_frame -> setLayout(layoutText);
    m_frame -> setStyleSheet("background-color: white");

    //Tao frame thay doi font chu
    m_comboFamilyRus = new QFontComboBox;
    QObject::connect(m_comboFamilyRus, SIGNAL(currentTextChanged(QString)), this, SLOT(slotSetFamilyRus(QString)));
    m_comboSizeRus = new QComboBox;
    QObject::connect(m_comboSizeRus, SIGNAL(currentTextChanged(QString)), this, SLOT(slotSetSizeRus(QString)));
    m_checkBoldRus = new QCheckBox;
    QObject::connect(m_checkBoldRus, SIGNAL(stateChanged(int)), this, SLOT(slotSetBoldRus(int)));
    m_checkItalicRus = new QCheckBox;
    QObject::connect(m_checkItalicRus, SIGNAL(stateChanged(int)), this, SLOT(slotSetItalicRus(int)));
    QGroupBox *groupFontRus = createGroupText("Rus", m_comboFamilyRus, m_comboSizeRus, m_checkBoldRus, m_checkItalicRus);
    m_comboFamilyRus -> setCurrentFont(fontRus);
    m_comboSizeRus -> setCurrentText(QString::number(fontRus.pointSize()));
    if(fontRus.bold()) { m_checkBoldRus -> setChecked(true); }
    if(fontRus.italic()) { m_checkItalicRus -> setChecked(true); }

    m_comboFamilyVi = new QFontComboBox;
    QObject::connect(m_comboFamilyVi, SIGNAL(currentTextChanged(QString)), this, SLOT(slotSetFamilyVi(QString)));
    m_comboSizeVi = new QComboBox;
    QObject::connect(m_comboSizeVi, SIGNAL(currentTextChanged(QString)), this, SLOT(slotSetSizeVi(QString)));
    m_checkBoldVi = new QCheckBox;
    QObject::connect(m_checkBoldVi, SIGNAL(stateChanged(int)), this, SLOT(slotSetBoldVi(int)));
    m_checkItalicVi = new QCheckBox;
    QObject::connect(m_checkItalicVi, SIGNAL(stateChanged(int)), this, SLOT(slotSetItalicVi(int)));
    QGroupBox *groupFontVi = createGroupText("Vi", m_comboFamilyVi, m_comboSizeVi, m_checkBoldVi, m_checkItalicVi);
    m_comboFamilyVi -> setCurrentFont(fontVi);
    m_comboSizeVi -> setCurrentText(QString::number(fontVi.pointSize()));
    if(fontVi.bold()) { m_checkBoldVi -> setChecked(true); }
    if(fontVi.italic()) { m_checkItalicVi -> setChecked(true); }

    QVBoxLayout *layoutFrameText = new QVBoxLayout;
    layoutFrameText -> addWidget(groupFontRus);
    layoutFrameText -> addWidget(groupFontVi);

    QFrame *frameFont = new QFrame;
    frameFont -> setLayout(layoutFrameText);

    //Tao frame thay doi color chu
    QVBoxLayout *layoutFrameColor = new QVBoxLayout;
    layoutFrameColor -> addWidget(m_frame);

    QFrame *frameColor = new QFrame;
    frameColor -> setLayout(layoutFrameColor);

    //Tao tab font va color
    QTabWidget *tabWidget = new QTabWidget();
    tabWidget -> addTab(frameFont, "Font");
    tabWidget -> addTab(frameColor, "Color");

    //Sap xep giao dien
    QVBoxLayout *layoutDoc = new QVBoxLayout;
    layoutDoc -> addWidget(tabWidget);
    layoutDoc -> addWidget(m_frame);
    layoutDoc -> addLayout(layoutButton);

    this -> setWindowTitle("Options");
    this -> setLayout(layoutDoc);
}

QGroupBox* Options::createGroupText(const QString nameGroup, QComboBox *comboFamily, QComboBox *comboSize, QCheckBox *checkBold, QCheckBox *checkItalic)
{
    QLabel *labelFamily = new QLabel("Family");
    QLabel *labelSize = new QLabel("Size");
    QStringList listSizeText = {"6", "7", "8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72"};
    comboSize -> addItems(listSizeText);

    QLabel *labelItalic = new QLabel("Italic");
    QLabel *labelBold = new QLabel("Bold");

    QHBoxLayout *layoutText = new QHBoxLayout;
    layoutText -> addWidget(labelFamily);
    layoutText -> addWidget(comboFamily);
    layoutText -> addWidget(labelSize);
    layoutText -> addWidget(comboSize);
    layoutText -> addWidget(labelBold);
    layoutText -> addWidget(checkBold);
    layoutText -> addWidget(labelItalic);
    layoutText -> addWidget(checkItalic);
    QGroupBox *groupFont = new QGroupBox(nameGroup);
    groupFont -> setLayout(layoutText);

    return groupFont;
}

QGroupBox *Options::createGroupColor(const QString)
{

}

void Options::slotSetOptions()
{
    QFont fontRus = m_labelRus -> font();
    QFont fontVi = m_labelVi -> font();
    emit signalSetOptions(fontRus, fontVi, "", "", "");
    this -> hide();
}

void Options::slotSetFamilyRus(QString fontRus)
{
    QFont font = m_labelRus -> font();
    font.setFamily(fontRus);
    m_labelRus -> setFont(font);
}

void Options::slotSetFamilyVi(QString fontVi)
{
    QFont font = m_labelVi -> font();
    font.setFamily(fontVi);
    m_labelVi -> setFont(font);
}

void Options::slotSetSizeRus(QString sizeRus)
{
    QFont font = m_labelRus -> font();
    font.setPointSize(sizeRus.toInt());
    m_labelRus -> setFont(font);
}

void Options::slotSetSizeVi(QString sizeVi)
{
    QFont font = m_labelVi -> font();
    font.setPointSize(sizeVi.toInt());
    m_labelVi -> setFont(font);
}

void Options::slotSetBoldRus(int index)
{
    if(index == 2)
    {
        QFont font = m_labelRus -> font();
        font.setBold(true);
        m_labelRus -> setFont(font);
    }
    else
    {
        QFont font = m_labelRus -> font();
        font.setBold(false);
        m_labelRus -> setFont(font);
    }
}

void Options::slotSetBoldVi(int index)
{
    if(index == 2)
    {
        QFont font = m_labelVi -> font();
        font.setBold(true);
        m_labelVi -> setFont(font);
    }
    else
    {
        QFont font = m_labelVi -> font();
        font.setBold(false);
        m_labelVi -> setFont(font);
    }
}

void Options::slotSetItalicRus(int index)
{
    if(index == 2)
    {
        QFont font = m_labelRus -> font();
        font.setItalic(true);
        m_labelRus -> setFont(font);
    }
    else
    {
        QFont font = m_labelRus -> font();
        font.setItalic(false);
        m_labelRus -> setFont(font);
    }
}

void Options::slotSetItalicVi(int index)
{
    if(index == 2)
    {
        QFont font = m_labelVi -> font();
        font.setItalic(true);
        m_labelVi -> setFont(font);
    }
    else
    {
        QFont font = m_labelVi -> font();
        font.setItalic(false);
        m_labelVi -> setFont(font);
    }
}
