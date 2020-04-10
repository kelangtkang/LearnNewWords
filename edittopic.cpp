#include "edittopic.h"
#include <QDebug>

EditTopic::EditTopic(QString nameTopic)
{
    QString path = tr("data/%1.txt").arg(nameTopic);
    m_data = new QFile(path);

    createGUI();
}

void EditTopic::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this -> deleteLater();
}

void EditTopic::createGUI()
{
    m_actionCreate = new QAction("Create");
    m_actionCreate -> setIcon(QIcon(":/icon/create-button.png"));
    QObject::connect(m_actionCreate, SIGNAL(triggered()), this, SLOT(slotCreateText()));

    m_actionRemove = new QAction("Remove");
    m_actionRemove -> setIcon(QIcon(":/icon/delete-button.png"));
    QObject::connect(m_actionRemove, SIGNAL(triggered()), this, SLOT(slotRemoveText()));

    m_actionRemoveAll = new QAction("Remove All");
    m_actionRemoveAll -> setIcon(QIcon(":/icon/remove.png"));
    QObject::connect(m_actionRemoveAll, SIGNAL(triggered()), this, SLOT(slotRemoveText()));

    QToolBar *toolBar = new QToolBar;
    toolBar -> setIconSize(QSize(15, 15));
    toolBar -> layout() -> setSpacing(10);
    toolBar -> addAction(m_actionCreate);
    toolBar -> addAction(m_actionRemove);

    //Tao nut chuc nang
    m_buttonOK = new QPushButton;
    m_buttonOK -> setText("OK");
    m_buttonOK -> setFont(QFont("Calibre", 10));
    m_buttonOK -> setFixedSize(80, 24);
    QObject::connect(m_buttonOK, SIGNAL(clicked()), this, SLOT(slotUpdateTopic()));

    m_buttonCancel = new QPushButton();
    m_buttonCancel -> setText("Cancel");
    m_buttonCancel -> setFont(QFont("Calibre", 10));
    m_buttonCancel -> setFixedSize(80, 24);
    m_buttonCancel -> setCursor(Qt::PointingHandCursor);
    QObject::connect(m_buttonCancel, SIGNAL(clicked()), this, SLOT(close()));

    //Tao label ten chu de
    QLabel *labelNameTopic = new QLabel;
    labelNameTopic -> setText("Name Topic");

    //Tao LineEdit ten chu de
    m_editNameTopic = new QLineEdit;

    //Tao bang
    m_table = new QTableWidget;
    m_table -> setColumnCount(2);
    m_table -> setColumnWidth(0, 200);
    m_table -> setColumnWidth(1, 200);
    m_table -> setSortingEnabled(true);
    m_table -> setHorizontalHeaderItem(0, new QTableWidgetItem("Tiếng Nga"));
    m_table -> setHorizontalHeaderItem(1, new QTableWidgetItem("Tiếng Việt"));

    //Sap xep giao dien
    QHBoxLayout *hLayoutButton = new QHBoxLayout;
    hLayoutButton -> addWidget(m_buttonOK, 1, Qt::AlignRight);
    hLayoutButton -> addWidget(m_buttonCancel, 0, Qt::AlignRight);
    QHBoxLayout *hLayoutName = new QHBoxLayout;
    hLayoutName -> addWidget(labelNameTopic);
    hLayoutName -> addWidget(m_editNameTopic);
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout -> addWidget(toolBar);
    vLayout -> addLayout(hLayoutName);
    vLayout -> addWidget(m_table);
    vLayout -> addLayout(hLayoutButton);

    this -> setLayout(vLayout);
    this -> resize(470, 600);
}

void EditTopic::slotAddDataToTable(QString nameTopic)
{
    m_nameTopic = nameTopic;
    m_editNameTopic -> setText(nameTopic);

    if(m_data -> open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i = 0;
        QTextStream  out(m_data);
        out.setCodec("UTF-8");
        while (!out.atEnd())
        {
            m_table -> insertRow(i);
            QString textRus = out.readLine();
            QTableWidgetItem *itemRus = new QTableWidgetItem(textRus);
            m_table -> setItem(i, 0, itemRus);

            QString textVi = out.readLine();
            QTableWidgetItem *itemVi = new QTableWidgetItem(textVi);
            m_table -> setItem(i, 1, itemVi);

            ++i;
        }
        m_data -> close();
    }
}

void EditTopic::slotCreateText()
{
    QList<QTableWidgetItem *> listSelectItems = m_table -> selectedItems();

    if(listSelectItems.empty())
    {
        m_table -> insertRow(0);
        m_table -> setItem(0, 0, new QTableWidgetItem());
        m_table -> setItem(0, 1, new QTableWidgetItem());
    }
        else
    {
        int indexRow = m_table -> row(listSelectItems[0]);
        m_table -> insertRow(indexRow);
        m_table -> setItem(indexRow, 0, new QTableWidgetItem());
        m_table -> setItem(indexRow, 1, new QTableWidgetItem());
    }
}

void EditTopic::slotRemoveText()
{
    QList<QTableWidgetItem *> listSelectItems = m_table -> selectedItems();

    foreach(QTableWidgetItem *selectItem, listSelectItems)
    {
        int indexRow = m_table -> row(selectItem);
        m_table -> removeRow(indexRow);
    }
}

void EditTopic::slotUpdateTopic()
{

    if(m_data -> open(QIODevice::WriteOnly))
    {
        QTextStream  out(m_data);
        out.setCodec("UTF-8");

        int indexRow;
        int numberRow = m_table -> rowCount();
        for(indexRow = 0; indexRow < numberRow; indexRow++)
        {
            out << m_table -> item(indexRow, 0) -> text() << endl;
            out << m_table -> item(indexRow, 1) -> text() << endl;
        }
    }
    m_data -> close();
    this -> close();
}
