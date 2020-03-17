#include "cuasochinh.h"
#include "napdulieu.h"

using namespace std;

CuaSoChinh::CuaSoChinh()
{
    // Tao cua so
    QWidget *widget = new QWidget;
    setCentralWidget(widget); // Importance

    // Tao icon
    setWindowIcon(QIcon("icon.png"));

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
    m_tiengNga = new QLabel("Русский Язык", this);
    m_tiengNga -> setFont(QFont("Segoe UI", 26, QFont::Bold));
    m_tiengNga -> setAlignment(Qt::AlignCenter);

    m_tiengViet = new QLabel("Tiếng Việt", this);
    m_tiengViet -> setFont(QFont("Times New Roman",14));
    m_tiengViet -> setAlignment(Qt::AlignCenter);

    // Tao Combo Box
    m_combo = new QComboBox(this);
    m_combo -> setFixedSize(110, 20);

    m_combo -> addItem("Chọn chủ đề");
    m_combo -> addItem("Số đếm");
    m_combo -> addItem("Số thứ tự");
    m_combo -> addItem("Ngày - Tháng");
    m_combo -> addItem("Động từ");
    m_combo -> addItem("Tính từ");
    m_combo -> addItem("Súng pháo");
    m_combo -> addItem("Đạn dược");
    m_combo -> addItem("Tên lửa");
    m_combo -> addItem("Kỹ thuật");

    // Ket noi tin hieu
    QObject::connect(m_next, SIGNAL(clicked()), this, SLOT(hienTuSau()));
    QObject::connect(m_preview, SIGNAL(clicked()), this, SLOT(hienTuTruoc()));
    QObject::connect(m_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(doiChuDe(int)));

    // Sap xep Layout
    QHBoxLayout *hDuoi = new QHBoxLayout();
    hDuoi -> setAlignment(Qt::AlignBottom);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox -> setSpacing(15);

    hDuoi -> addWidget(m_combo,0, Qt::AlignLeft);
    hDuoi -> addWidget(m_preview,1,Qt::AlignRight);
    hDuoi -> addWidget(m_next,0,Qt::AlignRight);
    vbox -> addWidget(m_tiengNga);
    vbox -> addWidget(m_tiengViet);
    vbox -> addLayout(hDuoi);
    widget -> setLayout(vbox); // Importance

    createMenu();
    m_count = -1; // Gia tri ban dau cua bien chay
}

void CuaSoChinh::createMenu() // Tao Menu
{
    // Create Action
    QPixmap newpix("D:/Users/Ghost/Desktop/First App/icon.png");

    m_ngaFont = new QAction(newpix, "Font tiếng Nga", this);
    m_ngaFont -> setFont(QFont("Calibri", 12));

    m_vietFont = new QAction("Font tiếng Việt", this);
    m_vietFont -> setFont(QFont("Calibri", 12));

    m_ngaColor = new QAction("Màu chữ tiếng Nga", this);
    m_ngaColor -> setFont(QFont("Calibri", 12));

    m_vietColor = new QAction("Màu chữ tiếng Việt", this);
    m_vietColor -> setFont(QFont("Calibri", 12));

    m_windowColor = new QAction("Màu nền cửa sổ", this);
    m_windowColor -> setFont(QFont("Calibri", 12));

    m_setOnTop = new QAction("Set On Top", this);
    m_setOnTop -> setCheckable(true);
    m_setOnTop -> setChecked(false);

    // Create Menu
    m_font = new QMenu();
    m_font = menuBar() -> addMenu("&Font");
    m_font -> addAction(m_ngaFont);
    m_font -> addAction(m_vietFont);

    m_color = new QMenu();
    m_color = menuBar() -> addMenu(("&Color"));
    m_color -> addAction(m_ngaColor);
    m_color -> addAction(m_vietColor);
    m_color -> addAction(m_windowColor);

    m_onTop = new QMenu();
    m_onTop = menuBar() -> addMenu("&On Top");
    m_onTop -> addAction(m_setOnTop);

    // Ket noi tin hieu
    QObject::connect(m_ngaFont, SIGNAL(triggered()), this, SLOT(setFontNga()));
    QObject::connect(m_vietFont, SIGNAL(triggered()), this, SLOT(setFontViet()));
    QObject::connect(m_ngaColor, SIGNAL(triggered()), this, SLOT(ngaColor()));
    QObject::connect(m_vietColor, SIGNAL(triggered()), this, SLOT(vietColor()));
    QObject::connect(m_windowColor, SIGNAL(triggered()), this, SLOT(windowColor()));
    QObject::connect(m_setOnTop, SIGNAL(triggered()), this, SLOT(setOnTop()));
}

void CuaSoChinh::doiChuDe(int i)
{
    if (i == 1)
    {
        m_countComboBox = 0;
    }
    else if (i == 2)
    {
        m_countComboBox = 1;
    }
    else if (i == 3)
    {
        m_countComboBox = 2;
    }
    else if (i == 3){}
    else if (i == 4){}
    else if (i == 5){}
    else if (i == 6){}
    else if (i == 7){}
    else if (i == 8){}
    else if (i == 9){}
    m_count = 0;
    NapDuLieu tuMoi(m_countComboBox);
    tuMoi.ChuyenTu(m_count);
    m_tiengNga -> setText(tuMoi.getTiengNga());
    m_tiengNga -> adjustSize();
    m_tiengViet -> setText(tuMoi.getTiengViet());
    m_tiengViet -> adjustSize();
}

void CuaSoChinh::hienTuSau()
{
    m_count ++;
    NapDuLieu tuMoi(m_countComboBox);
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
    NapDuLieu tuMoi(m_countComboBox);
    tuMoi.ChuyenTu(m_count);
    m_tiengNga -> setText(tuMoi.getTiengNga());
    m_tiengNga -> adjustSize();
    m_tiengViet -> setText(tuMoi.getTiengViet());
    m_tiengViet -> adjustSize();
}

void CuaSoChinh::setOnTop() // Giu cua so phia tren
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

void CuaSoChinh::setFontNga() // Doi font chu tieng Nga
{
    bool ok;
    QFont kieuChu = QFontDialog::getFont(&ok, QFont("Segoe UI", 26, QFont::Bold), this);
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
