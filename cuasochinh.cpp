#include "cuasochinh.h"

#include <QDebug>

using namespace std;

CuaSoChinh::CuaSoChinh()
{
    m_indexComboBox = 0;
    this -> adjustSize();
    m_directory = QDir("data");
    m_topic = new Topic;
    QObject::connect(m_topic, SIGNAL(signalUpdateTopic()), this, SLOT(slotUpdateTopic()));

    createGUI();
    createMenu();
    readSettings();
}

void CuaSoChinh::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    writeSettings();
}

void CuaSoChinh::writeSettings()
{
    QSettings setting("Company", "LearnNewWords");
    setting.beginGroup("MainWindow");

    QFont fontRus = m_labelRus -> font();
    setting.setValue("fontRusFamily", fontRus.family());
    setting.setValue("fontRusSize", fontRus.pointSize());
    setting.setValue("fontRusBold", fontRus.bold());
    setting.setValue("fontRusItalic", fontRus.italic());

    QFont fontVi = m_labelVi -> font();
    setting.setValue("fontViFamily", fontVi.family());
    setting.setValue("fontViSize", fontVi.pointSize());
    setting.setValue("fontViBold", fontVi.bold());
    setting.setValue("fontViItalic", fontVi.italic());

    QColor colorTextRus = m_labelRus -> palette().color(QPalette::WindowText);
    setting.setValue("colorTextRus", colorTextRus.name());

    QColor colorTextVi = m_labelVi -> palette().color(QPalette::WindowText);
    setting.setValue("colorTextVi", colorTextVi.name());

    QColor colorWindow = this -> palette().color(QPalette::Window);
    setting.setValue("colorWindow", colorWindow.name());

    setting.setValue("size", size());
    setting.setValue("pos", pos());
    setting.endGroup();
}

void CuaSoChinh::readSettings()
{
    QSettings setting("Company", "LearnNewWords");
    setting.beginGroup("MainWindow");

    resize(setting.value("size", QSize(400, 200)).toSize());
    move(setting.value("pos", QPoint(300, 300)).toPoint());

    QString fontRusFamily = setting.value("fontRusFamily", "Segoe UI").toString();
    int fontRusSize = setting.value("fontRusSize", 26).toInt();
    bool fontRusBold = setting.value("fontRusBold", false).toBool();
    bool fontRusItalic = setting.value("fontRusItalic", false).toBool();
    QFont fontRus(fontRusFamily, fontRusSize);
    fontRus.setBold(fontRusBold);
    fontRus.setItalic(fontRusItalic);
    m_labelRus -> setFont(fontRus);

    QString fontViFamily = setting.value("fontViFamily", "Segoe UI").toString();
    int fontViSize = setting.value("fontViSize", 26).toInt();
    bool fontViBold = setting.value("fontViBold", false).toBool();
    bool fontViItalic = setting.value("fontViItalic", false).toBool();
    QFont fontVi(fontViFamily, fontViSize);
    fontVi.setBold(fontViBold);
    fontVi.setItalic(fontViItalic);
    m_labelVi -> setFont(fontVi);

    QString colorTextRus = setting.value("colorTextRus", "").toString();
    m_labelRus -> setStyleSheet(tr("color: %1").arg(colorTextRus));

    QString colorTextVi = setting.value("colorTextVi", "").toString();
    m_labelVi -> setStyleSheet(tr("color: %1").arg(colorTextVi));

    QString colorWindow = setting.value("colorWindow", "").toString();

    setting.endGroup();
    m_options = new Options(fontRus, fontVi, colorTextRus, colorTextVi, colorWindow);
    QObject::connect(m_options, SIGNAL(signalSetOptions(QFont, QFont, QString, QString, QString)), this, SLOT(slotSetOptions(QFont, QFont, QString, QString, QString)));
    QObject::connect(m_actionOptions, SIGNAL(triggered()), m_options,SLOT(show()));
}

void CuaSoChinh::hienTuSau()
{
    if(m_indexComboBox != 0)
    {
        m_index ++;
        if (m_index < int(m_vectorRus.size()))
        {
            m_labelRus -> setText(m_vectorRus[m_index]);
            m_labelVi -> setText(m_vectorVi[m_index]);

        }
        else
        {
            m_labelRus -> setText(m_vectorRus[0]);
            m_labelVi -> setText(m_vectorVi[0]);
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
            m_labelVi -> setText(m_vectorVi[m_index]);
        }
        else
        {
            m_labelRus -> setText(m_vectorRus[int(m_vectorRus.size()) - 1]);
            m_labelVi -> setText(m_vectorVi[int(m_vectorRus.size()) - 1]);
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
        QFile Data(link);
        m_vectorVi.clear();
        m_vectorRus.clear();

        if(Data.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream  out(&Data);
            out.setCodec("UTF-8");
            while (!out.atEnd())
            {
                m_vectorRus.push_back(out.readLine());
                m_vectorVi.push_back(out.readLine());
            }
            Data.close();
        }

        if(m_vectorRus.empty() || m_vectorVi.empty())
        {
            m_labelRus -> setText(" ");
            m_labelVi -> setText(" ");
        }
        else
        {
            m_labelRus -> setText(m_vectorRus[0]);
            m_labelVi -> setText(m_vectorVi[0]);
        }
        m_index = 0;
    }
    else
    {
        m_labelRus -> setText("Русский Язык");
        m_labelVi -> setText("Tiếng Việt");
    }
}

void CuaSoChinh::createGUI()
{
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
    m_labelRus = new QLabel("Русский Язык");
    m_labelRus -> setFont(QFont("Segoe UI", 26, QFont::Bold));
    m_labelRus -> setAlignment(Qt::AlignCenter);
    m_labelRus -> setAutoFillBackground(true);

    m_labelVi = new QLabel("Tiếng Việt", this);
    m_labelVi -> setFont(QFont("Times New Roman",14));
    m_labelVi -> setAlignment(Qt::AlignCenter);
    m_labelVi -> setAutoFillBackground(true);

    // Tao Combo Box
    m_combo = new QComboBox(this);
    //m_combo -> setFixedSize(110, 20);
    m_combo -> addItem("Chọn chủ đề");

    m_listData = m_directory.entryInfoList(QDir::Files);
    foreach (QFileInfo filename, m_listData)
    {
        m_combo -> addItem(filename.baseName());
    }

    // Sap xep Layout
    QHBoxLayout *layoutNgang = new QHBoxLayout;
    QVBoxLayout *layoutDoc = new QVBoxLayout;
    QVBoxLayout *layoutText = new QVBoxLayout;
    //layoutDoc -> setSpacing(15);

    layoutNgang -> addWidget(m_combo,0, Qt::AlignLeft);
    layoutNgang -> addWidget(m_preview,1,Qt::AlignRight);
    layoutNgang -> addWidget(m_next,0,Qt::AlignRight);
    layoutText -> addWidget(m_labelRus);
    layoutText -> addWidget(m_labelVi);

    m_frame = new QFrame;
    m_frame -> setFrameShape(QFrame::Box);
    m_frame -> setLineWidth(1);
    m_frame -> setLayout(layoutText);
    m_frame -> setStyleSheet("background-color: white");

    layoutDoc -> addWidget(m_frame);
    layoutDoc -> addLayout(layoutNgang);

    QWidget *widget = new QWidget;
    widget -> setLayout(layoutDoc);
    setCentralWidget(widget); //Importance

    // Ket noi tin hieu
    QObject::connect(m_next, SIGNAL(clicked()), this, SLOT(hienTuSau()));
    QObject::connect(m_preview, SIGNAL(clicked()), this, SLOT(hienTuTruoc()));
    QObject::connect(m_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTopic(int)));
}

void CuaSoChinh::createMenu() //Tao Menu
{
    QFont font = QFont("Calibri", 12);

    QMenu *menuFile = new QMenu;
    menuFile = menuBar() -> addMenu("&File");
    m_exit = new QAction("Exit");
    m_exit -> setIcon(QIcon(":/icon/cancel-button.png"));
    menuFile -> addAction(m_exit);
    QObject::connect(m_exit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *menuSettings = new QMenu;
    menuSettings = menuBar() -> addMenu("&Tools");
    m_actionTopic = new QAction("Topics");
    m_actionTopic -> setIcon(QIcon(":/icon/folder-button.png"));
    menuSettings -> addAction(m_actionTopic);
    QObject::connect(m_actionTopic, SIGNAL(triggered()), this, SLOT(slotEditTopic()));
    m_actionOptions = new QAction("Options");
    m_actionOptions -> setIcon(QIcon(":/icon/settings-button.png"));
    menuSettings -> addAction(m_actionOptions);

    QMenu *menuWindow = new QMenu;
    menuWindow = menuBar() -> addMenu("Window");
    m_actionOnTop = new QAction("Set on top");
    m_actionOnTop -> setCheckable(true);
    menuWindow -> addAction(m_actionOnTop);
    QObject::connect(m_actionOnTop, SIGNAL(triggered()), this, SLOT(slotSetOnTop()));
    m_actionReset = new QAction("Reset");
    m_actionReset -> setIcon(QIcon(":/icon/reset-button.png"));
    menuWindow -> addAction(m_actionReset);
    QObject::connect(m_actionReset, SIGNAL(triggered()), this, SLOT(slotReset()));

}

void CuaSoChinh::slotEditTopic()
{
    m_topic -> show();
}

void CuaSoChinh::slotUpdateTopic()
{
    int indexCombo;
    int countCombo = m_combo -> count();
    for(indexCombo = countCombo - 1; indexCombo > 0; indexCombo--)
    {
        m_combo -> removeItem(indexCombo);
    }
//    m_combo -> clear();

    m_listData = m_directory.entryInfoList(QDir::Files);
    foreach (QFileInfo filename, m_listData)
    {
        m_combo -> addItem(filename.baseName());
    }
}

void CuaSoChinh::slotSetOnTop() //Giu cua so phia tren
{
    if (m_actionOnTop -> isChecked())
    {
        this -> setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    else
    {
        this -> setWindowFlags(Qt::WindowStaysOnBottomHint);
    }
    show();
}

void CuaSoChinh::slotSetOptions(QFont fontRus, QFont fontVi, QString colorRus, QString colorVi, QString colorFrame) //Thay doi cai dat
{
    m_labelRus -> setFont(fontRus);
    m_labelVi -> setFont(fontVi);
}

void CuaSoChinh::slotReset()
{
    m_labelRus -> setFont(QFont("Segoe UI", 26, QFont::Bold));
    m_labelRus -> setText("Русский Язык");
    m_labelVi -> setFont(QFont("Times New Roman",14));
    m_labelVi -> setText("Tiếng Việt");

    m_labelRus -> setStyleSheet("color: black");
    m_labelVi -> setStyleSheet("color: black");

    this -> adjustSize();
    this -> adjustSize();
}
