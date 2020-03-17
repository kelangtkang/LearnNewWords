#include "cuasochinh.h"
#include "napdulieu.h"

using namespace std;

CuaSoChinh::CuaSoChinh() : QWidget()
{
//    setFixedSize(300, 150);
    this -> setWindowFlags(Qt::WindowStaysOnTopHint);

    // Tao Button
    m_next = new QPushButton("Tu tiep theo", this);
    m_next -> setFont(QFont("Calibri", 10));
    m_next -> setCursor(Qt::PointingHandCursor); //    m_preview -> setGeometry(0,130,80,20);

    m_preview = new QPushButton("Tu truoc do", this);
    m_preview -> setFont(QFont("Calibri", 10));
    m_preview -> setCursor(Qt::PointingHandCursor);

    m_ngaFont = new QPushButton("Font 1", this);
    m_ngaFont -> setFont(QFont("Calibri", 10));
    m_ngaFont -> setCursor(Qt::PointingHandCursor);

    m_vietFont = new QPushButton("Font 2", this);
    m_vietFont -> setFont(QFont("Calibri", 10));
    m_vietFont -> setCursor(Qt::PointingHandCursor);

    m_ngaColor = new QPushButton("Color 1", this);
    m_ngaColor -> setFont(QFont("Calibri", 10));
    m_ngaColor -> setCursor(Qt::PointingHandCursor);

    m_vietColor = new QPushButton("Color 2", this);
    m_vietColor -> setFont(QFont("Calibri", 10));
    m_vietColor -> setCursor(Qt::PointingHandCursor);

    m_windowColor = new QPushButton("Background", this);
    m_windowColor -> setFont(QFont("Calibri", 10));
    m_windowColor -> setCursor(Qt::PointingHandCursor);

// Tao QLabel
    m_tiengNga = new QLabel("Русский Язык",this);
    m_tiengNga -> setFont(QFont("Segoe UI",26));
    m_tiengNga -> setAlignment(Qt::AlignCenter);//    m_tiengNga ->setStyleSheet("QLabel { background-color : red; color : blue; }");

    m_tiengViet = new QLabel("Tiếng Việt", this);
    m_tiengViet -> setFont(QFont("Times New Roman",14));
    m_tiengViet -> setAlignment(Qt::AlignCenter);//    m_tiengViet -> setStyleSheet("color: green;");

// Sap xep Layout
    QHBoxLayout *hDuoi = new QHBoxLayout();
    hDuoi -> setAlignment(Qt::AlignBottom);
    QHBoxLayout *hTren = new QHBoxLayout();
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox -> setSpacing(15);

    hTren -> addWidget(m_ngaFont);
    hTren -> addWidget(m_vietFont);
    hTren -> addWidget(m_ngaColor);
    hTren -> addWidget(m_vietColor);
    hTren -> addWidget(m_windowColor);
    hDuoi -> addWidget(m_preview,1,Qt::AlignLeft);
    hDuoi -> addWidget(m_next,0,Qt::AlignRight);
    vbox -> addLayout(hTren);
    vbox -> addWidget(m_tiengNga);
    vbox -> addWidget(m_tiengViet);
    vbox -> addLayout(hDuoi);

// Ket noi tin hieu
    QObject::connect(m_next, SIGNAL(clicked()), this, SLOT(hienTuSau()));
    QObject::connect(m_preview, SIGNAL(clicked()), this, SLOT(hienTuTruoc()));
    QObject::connect(m_ngaFont, SIGNAL(clicked()), this, SLOT(setFontNga()));
    QObject::connect(m_vietFont, SIGNAL(clicked()), this, SLOT(setFontViet()));
    QObject::connect(m_ngaColor, SIGNAL(clicked()), this, SLOT(ngaColor()));
    QObject::connect(m_vietColor, SIGNAL(clicked()), this, SLOT(vietColor()));
    QObject::connect(m_windowColor, SIGNAL(clicked()), this, SLOT(windowColor()));

    m_count = -1; // Gia tri ban dau cua bien chay
}

void CuaSoChinh::hienTuSau()
{
    m_count ++;
    NapDuLieu tuMoi;
    tuMoi.ChuyenTu(m_count);
    if(tuMoi.getTiengNga() == "")
    {
        m_count = 0;
        tuMoi.ChuyenTu(m_count);
    }
    else{}
    m_tiengNga -> setText(tuMoi.getTiengNga());
    m_tiengNga -> adjustSize();
    m_tiengViet -> setText(tuMoi.getTiengViet());
    m_tiengViet -> adjustSize();
}

void CuaSoChinh::hienTuTruoc()
{
    if(m_count <= 0)
    {
        m_count = 0;
    }
    else
    {
        m_count --;
    }
    NapDuLieu tuMoi;
    tuMoi.ChuyenTu(m_count);
    m_tiengNga -> setText(tuMoi.getTiengNga());
    m_tiengNga -> adjustSize();
    m_tiengViet -> setText(tuMoi.getTiengViet());
    m_tiengViet -> adjustSize();
}

void CuaSoChinh::setFontNga() // Doi font chu tieng Nga
{
    bool ok;
    QFont kieuChu = QFontDialog::getFont(&ok, QFont("Segoe UI", 26), this);
    if (ok)
    {
        m_tiengNga -> setFont(kieuChu);
        m_tiengNga -> adjustSize();
    }
}

void CuaSoChinh::setFontViet() // Doi font chu tieng Viet
{
    bool ok;
    QFont kieuChu = QFontDialog::getFont(&ok, QFont("Times New Roman", 14), this);
    if (ok)
    {
        m_tiengViet -> setFont(kieuChu);
        m_tiengViet-> adjustSize();
    }
}

void CuaSoChinh::ngaColor() // Doi mau chu tieng Nga
{
    QColor mau = QColorDialog::getColor(Qt::black, this);
    QPalette bangMau;
    bangMau.setColor(QPalette::WindowText, mau);
    m_tiengNga -> setPalette(bangMau);
}

void CuaSoChinh::vietColor() // Doi mau chu tieng Viet
{
    QColor mau = QColorDialog::getColor(Qt::black, this);
    QPalette bangMau;
    bangMau.setColor(QPalette::WindowText, mau);
    m_tiengViet -> setPalette(bangMau);
}

void CuaSoChinh::windowColor() // Doi mau nen cua so
{
    QColor mau = QColorDialog::getColor(Qt::white, this);
    QPalette bangMau;
    bangMau.setColor(QPalette::Window, mau);
    this -> setPalette(bangMau);
}
