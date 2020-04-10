#include "topic.h"

Topic::Topic(QWidget *parent) : QDialog(parent)
{
    m_dialogAddTopic = new DialogAddTopic;
    QObject::connect(m_dialogAddTopic, SIGNAL(signalCreateTopic(QString)), this, SLOT(slotCreateTopic(QString)));

    createGUI();
}

void Topic::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit signalUpdateTopic();
}

void Topic::createGUI()
{
    this -> setWindowTitle("Chủ đề");
    this -> createTable();

    //Tao Tool Bar
    m_actionEdit = new QAction("Edit");
    m_actionEdit -> setIcon(QIcon(":/icon/edit-button.png"));
    QObject::connect(m_actionEdit, SIGNAL(triggered()), this, SLOT(slotEditTopic()));

    m_actionCreate = new QAction("Create");
    m_actionCreate -> setIcon(QIcon(":/icon/create-button.png"));
    QObject::connect(m_actionCreate, SIGNAL(triggered()), m_dialogAddTopic, SLOT(show()));

    m_actionRemove = new QAction("Remove");
    m_actionRemove -> setIcon(QIcon(":/icon/delete-button.png"));
    QObject::connect(m_actionRemove, SIGNAL(triggered()), this, SLOT(slotRemoveTopic()));

    m_actionRemoveAll = new QAction("Remove All");
    m_actionRemoveAll -> setIcon(QIcon(":/icon/remove.png"));
    QObject::connect(m_actionRemoveAll, SIGNAL(triggered()), this, SLOT(slotRemoveText()));

    QToolBar *toolBar = new QToolBar;
    toolBar -> setIconSize(QSize(15, 15));
    toolBar -> layout() -> setSpacing(10);
    toolBar -> addAction(m_actionEdit);
    toolBar -> addAction(m_actionCreate);
    toolBar -> addAction(m_actionRemove);

    //Tao button
    m_buttonCancel = new QPushButton;
    m_buttonCancel -> setText("Cancel");
    m_buttonCancel -> setFont(QFont("Calibre", 10));
    m_buttonCancel -> setFixedSize(80, 24);
    m_buttonCancel -> setCursor(Qt::PointingHandCursor);
    QObject::connect(m_buttonCancel, SIGNAL(clicked()), this, SLOT(close()));

    //Sap xep giao dien
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout -> addWidget(m_buttonCancel);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout -> addWidget(toolBar);
    vLayout -> addWidget(m_table);
    vLayout -> addLayout(hLayout);

    this -> setLayout(vLayout);
    this -> resize(250, 400);
}

void Topic::createTable()
{
    m_table = new QTableWidget();
    QStringList nameHeader;
    m_table -> setColumnCount(1);
    m_table -> setColumnWidth(0 , 250);
    m_table -> setSortingEnabled(true);
    m_table -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table -> setHorizontalHeaderItem(0, new QTableWidgetItem("Tên chủ đề"));

    this -> updateTable();
}

void Topic::updateTable()
{
    QDir directory("data");
    QFileInfoList listData = directory.entryInfoList(QDir::Files);
    foreach (QFileInfo filename, listData)
    {
        m_table -> insertRow(0);
        QTableWidgetItem *itemTopic = new QTableWidgetItem(filename.baseName());
        m_table -> setItem(0, 0, itemTopic);
    }
}

void Topic::slotEditTopic()
{
    if(m_table -> currentRow() == -1)
    {
        QMessageBox::information(this, tr("Error"), tr("Hãy chọn chủ đề."));
    }
    else
    {
        QString nameCurent = m_table -> item(m_table -> currentRow(), 0) -> text();
        m_editTopic = new EditTopic(nameCurent);
        QObject::connect(this, SIGNAL(signalEditTopic(QString)), m_editTopic, SLOT(slotAddDataToTable(QString)));
        m_editTopic -> show();
        emit signalEditTopic(nameCurent);
    }
}

void Topic::slotCreateTopic(QString nameNewTopic)
{
    int rowCount = m_table -> rowCount();
    for(int i = 0; i < rowCount; i++)
    {
        QString nameItem = m_table -> item(i, 0) -> text();
        m_listTopic.insert(i, nameItem);
    }

    if(!m_listTopic.contains(nameNewTopic))
    {
        m_table -> insertRow(0);
        QTableWidgetItem *itemNewTopic = new QTableWidgetItem(nameNewTopic);
        m_table -> setItem(0, 0, itemNewTopic);

        QFile file(tr("data/%1.txt").arg(nameNewTopic));
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << endl << endl;
    }
    else
    {
        QMessageBox::information(this, tr("Duplicate Name"), tr("Tên chủ đề \"%1\" đã tồn tại.").arg(nameNewTopic));
    }
}

void Topic::slotRemoveTopic()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Chú ý !", "Bạn có muốn xóa chủ đề này?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QList<QTableWidgetItem *> listSelectItems = m_table -> selectedItems();

        foreach(QTableWidgetItem *selectItem, listSelectItems)
        {
            int indexRow = m_table -> row(selectItem);
            QString nameSelectItem;
            nameSelectItem = m_table -> item(indexRow, 0) -> text();

            QFile file(tr("data/%1.txt").arg(nameSelectItem));
            file.remove();
            m_table -> removeRow(indexRow);
        }
    }
}

void Topic::slotListTopic()
{
}
