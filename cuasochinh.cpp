#include "cuasochinh.h"
#include <vector>
#include <QDebug>
#include <QFileInfo>

using namespace std;

CuaSoChinh::CuaSoChinh()
{
    createGUI();
    createMenu();
    m_indexComboBox = 0;
}

void CuaSoChinh::hienTuSau()
{
    if(m_indexComboBox !=0)
    {
        m_index ++;
        if (m_index < int(m_vectorRus.size()))
        {
            m_labelRus -> setText(m_vectorRus[m_index]);
            m_labelRus -> adjustSize();
            m_labelVi -> setText(m_vectorVi[m_index]);
            m_labelVi -> adjustSize();
        }
        else
        {
            m_labelRus -> setText(m_vectorRus[0]);
            m_labelRus -> adjustSize();
            m_labelVi -> setText(m_vectorVi[0]);
            m_labelVi -> adjustSize();
            m_index = 0;
        }
    }
}

void CuaSoChinh::hienTuTruoc()
{
    if(m_indexComboBox !=0)
    {
        m_index --;
        if (m_index >= 0)
        {
            m_labelRus -> setText(m_vectorRus[m_index]);
            m_labelRus -> adjustSize();
            m_labelVi -> setText(m_vectorVi[m_index]);
            m_labelVi -> adjustSize();
        }
        else
        {
            m_labelRus -> setText(m_vectorRus[int(m_vectorRus.size()) - 1]);
            m_labelRus -> adjustSize();
            m_labelVi -> setText(m_vectorVi[int(m_vectorRus.size()) - 1]);
            m_labelVi -> adjustSize();
            m_index = int(m_vectorRus.size()) - 1;
        }
    }
}

void CuaSoChinh::changeTopic(int iComboBox)
{
    m_indexComboBox = iComboBox;

    if(iComboBox != 0)
    {
        QString link = m_listData[iComboBox - 1].filePath();
        qDebug() << iComboBox << link;

        QFile Data(link);
        m_vectorVi.clear();
        m_vectorRus.clear();

        if(Data.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream  out(&Data);
            while (!out.atEnd())
            {
                m_vectorRus.push_back(out.readLine());
                m_vectorVi.push_back(out.readLine());
            }
            Data.close();
        }

        m_labelRus -> setText(m_vectorRus[0]);
        m_labelRus -> adjustSize();
        m_labelVi -> setText(m_vectorVi[0]);
        m_labelVi -> adjustSize();

        m_index = 0;
    }
    else
    {
        m_labelRus -> setText("sdf");
        m_labelVi -> setText("sdf");
    }
}

void CuaSoChinh::setOnTop() //Giu cua so phia tren
{
    if (m_setOnTop -> isChecked())
    {
        this -> setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    else
    {
        this -> setWindowFlags(Qt::WindowStaysOnBottomHint);
    }
    show();
}

void CuaSoChinh::setFontNga() //Doi font chu tieng Nga
{
    bool ok;
    QFont kieuChu = QFontDialog::getFont(&ok, QFont("Segoe UI", 26, QFont::Bold), this);
    if (ok)
    {
        m_labelRus -> setFont(kieuChu);
        m_labelRus -> adjustSize();
    }
}

void CuaSoChinh::setFontViet() //Doi font chu tieng Viet
{
    bool ok;
    QFont kieuChu = QFontDialog::getFont(&ok, QFont("Times New Roman", 14), this);
    if (ok)
    {
        m_labelVi -> setFont(kieuChu);
        m_labelVi-> adjustSize();
    }
}

void CuaSoChinh::createGUI()
{
    QWidget *widget = new QWidget; // Tao cua so
    setCentralWidget(widget); //Importance

    setWindowIcon(QIcon("icon.png")); //Tao icon

    // Tao Button
    m_next = new QPushButton(">", this);
    m_next -> setFont(QFont("AIGDT", 10, QFont::Bold));
    m_next -> setFixedSize(50, 22);
    m_next -> setCursor(Qt::PointingHandCursor);

    m_preview = new QPushButton("<", this);
    m_preview -> setFont(QFont("AIGDT", 10, QFont::Bold));
    m_preview -> setFixedSize(50, 22);
    m_preview -> setCursor(Qt::PointingHandCursor);

    // Tao QLabel
    m_labelRus = new QLabel("Русский Язык", this);
    m_labelRus -> setFont(QFont("Segoe UI", 26, QFont::Bold));
    m_labelRus -> setAlignment(Qt::AlignCenter);

    m_labelVi = new QLabel("Tiếng Việt", this);
    m_labelVi -> setFont(QFont("Times New Roman",14));
    m_labelVi -> setAlignment(Qt::AlignCenter);

    // Tao Combo Box
    m_combo = new QComboBox(this);
    m_combo -> setFixedSize(110, 20);
    m_combo -> addItem("Chọn chủ đề");

    QDir directory("data");

    m_listData = directory.entryInfoList(QDir::Files);
    foreach (QFileInfo filename, m_listData)
    {
        qDebug() << filename.filePath();//.baseName();
        m_combo -> addItem(filename.baseName());
    }

    // Sap xep Layout
    QHBoxLayout *layoutNgang = new QHBoxLayout();
    layoutNgang -> setAlignment(Qt::AlignBottom);
    QVBoxLayout *layoutDoc = new QVBoxLayout(this);
    layoutDoc -> setSpacing(15);

    layoutNgang -> addWidget(m_combo,0, Qt::AlignLeft);
    layoutNgang -> addWidget(m_preview,1,Qt::AlignRight);
    layoutNgang -> addWidget(m_next,0,Qt::AlignRight);
    layoutDoc -> addWidget(m_labelRus);
    layoutDoc -> addWidget(m_labelVi);
    layoutDoc -> addLayout(layoutNgang);
    widget -> setLayout(layoutDoc); // Importance

    // Ket noi tin hieu
    QObject::connect(m_next, SIGNAL(clicked()), this, SLOT(hienTuSau()));
    QObject::connect(m_preview, SIGNAL(clicked()), this, SLOT(hienTuTruoc()));
    QObject::connect(m_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTopic(int)));
}

void CuaSoChinh::createMenu() //Tao Menu
{
    QPixmap newpix(":/icon/icon.ico");
    QFont font = QFont("Calibri", 12);

    m_addTopic = new QAction("Thêm chủ đề");
    m_exit = new QAction("Exit");
    QMenu *menuFile = new QMenu;
    menuFile = menuBar() -> addMenu("&File");
    menuFile -> addAction(m_addTopic);
    menuFile -> addAction(m_exit);

    m_ngaFont = new QAction(newpix, "Font tiếng Nga", this);
    m_ngaFont -> setFont(font);
    m_vietFont = new QAction("Font tiếng Việt", this);
    m_vietFont -> setFont(font);
    QMenu *menuFont = new QMenu();
    menuFont = menuBar() -> addMenu("&Font");
    menuFont -> addAction(m_ngaFont);
    menuFont -> addAction(m_vietFont);

    m_ngaColor = new QAction("Màu chữ tiếng Nga", this);
    m_ngaColor -> setFont(font);
    m_vietColor = new QAction("Màu chữ tiếng Việt", this);
    m_vietColor -> setFont(font);
    m_windowColor = new QAction("Màu nền cửa sổ", this);
    m_windowColor -> setFont(font);
    QMenu *menuColor = new QMenu();
    menuColor = menuBar() -> addMenu(("&Color"));
    menuColor -> addAction(m_ngaColor);
    menuColor -> addAction(m_vietColor);
    menuColor -> addAction(m_windowColor);

    m_setOnTop = new QAction("Set On Top", this);
    m_setOnTop -> setCheckable(true);
    m_setOnTop -> setChecked(false);
    QMenu *onTop = new QMenu();
    onTop = menuBar() -> addMenu("&On Top");
    onTop -> addAction(m_setOnTop);

    QObject::connect(m_ngaFont, SIGNAL(triggered()), this, SLOT(setFontNga()));
    QObject::connect(m_vietFont, SIGNAL(triggered()), this, SLOT(setFontViet()));
    QObject::connect(m_ngaColor, SIGNAL(triggered()), this, SLOT(ngaColor()));
    QObject::connect(m_vietColor, SIGNAL(triggered()), this, SLOT(vietColor()));
    QObject::connect(m_windowColor, SIGNAL(triggered()), this, SLOT(windowColor()));
    QObject::connect(m_setOnTop, SIGNAL(triggered()), this, SLOT(setOnTop()));
}

void CuaSoChinh::ngaColor() //Doi mau chu tieng Nga
{
    QColor mau = QColorDialog::getColor(Qt::black, this);
    QPalette bangMau;
    bangMau.setColor(QPalette::WindowText, mau);
    m_labelRus -> setPalette(bangMau);
}

void CuaSoChinh::vietColor() //Doi mau chu tieng Viet
{
    QColor mau = QColorDialog::getColor(Qt::black, this);
    QPalette bangMau;
    bangMau.setColor(QPalette::WindowText, mau);
    m_labelVi -> setPalette(bangMau);
}

void CuaSoChinh::windowColor() //Doi mau nen cua so
{
    QColor mau = QColorDialog::getColor(Qt::white, this);
    QPalette bangMau;
    bangMau.setColor(QPalette::Window, mau);
    this -> setPalette(bangMau);
}
