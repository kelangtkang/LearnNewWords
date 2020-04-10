#ifndef TOPIC_H
#define TOPIC_H

#include <QWidget>
#include <QtWidgets>

#include <string>
#include <fstream>
#include <locale>
#include <codecvt>

#include "dialogaddtopic.h"
#include "edittopic.h"

class Topic : public QDialog
{
    Q_OBJECT

public:
    explicit Topic(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
    void createGUI();
    void createTable();
    void updateTable();
    void editTopic(); 

signals:
    void signalListTopic(QStringList);
    void signalEditTopic(QString);
    void signalUpdateTopic();

public slots:
    void slotCreateTopic(QString);
    void slotEditTopic();
    void slotRemoveTopic();
    void slotListTopic();

private:
    QList<QString> m_listTopic;
    QTableWidget *m_table;
    DialogAddTopic *m_dialogAddTopic;
    EditTopic *m_editTopic;

    QPushButton *m_buttonCancel;
    QAction *m_actionEdit, *m_actionCreate, *m_actionRemove, *m_actionRemoveAll;
};

#endif // TOPIC_H
