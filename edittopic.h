#ifndef EDITTOPIC_H
#define EDITTOPIC_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QToolBar>
#include <QAction>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QDir>

#include <string>
#include <vector>
#include <fstream>

class EditTopic : public QDialog
{
    Q_OBJECT

public:
    EditTopic(QString);
    void closeEvent(QCloseEvent *event);
    void createGUI();

private slots:
    void slotAddDataToTable(QString);
    void slotCreateText();
    void slotRemoveText();
    void slotUpdateTopic();

private:
    std::vector <QString> m_vectorRus;
    std::vector <QString> m_vectorVi;
    QFile *m_data;

    QString m_nameTopic;
    QLineEdit *m_editNameTopic;
    QTableWidget *m_table;
    QPushButton *m_buttonOK, *m_buttonCancel;
    QAction *m_actionCreate, *m_actionRemove, *m_actionRemoveAll;
};

#endif // EDITTOPIC_H
