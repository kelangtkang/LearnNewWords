#ifndef DIALOGADDTOPIC_H
#define DIALOGADDTOPIC_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>

namespace Ui {
class DialogAddTopic;
}

class DialogAddTopic : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddTopic(QWidget *parent = nullptr);
    ~DialogAddTopic();

signals:
    void signalCreateTopic(QString);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void slotListTopic(QStringList);

private:
    Ui::DialogAddTopic *ui;
};

#endif // DIALOGADDTOPIC_H
