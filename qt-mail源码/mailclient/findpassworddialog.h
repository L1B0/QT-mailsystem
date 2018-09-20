#ifndef FINDPASSWORDDIALOG_H
#define FINDPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
    class FindPasswordDialog;
}

class FindPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindPasswordDialog(QWidget *parent = 0);
    ~FindPasswordDialog();
    int fd;

private:
    Ui::FindPasswordDialog *ui;

private slots:
    void on_okbtn_clicked();
    void on_cancelbtn_clicked();
};

#endif // FINDPASSWORDDIALOG_H
