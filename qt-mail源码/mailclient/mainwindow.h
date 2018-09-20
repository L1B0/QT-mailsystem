#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "protocol.h"
#include "receive.h"
#include <QMessageBox>
#include <QMainWindow>
class QStackedWidget ;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString username, int fd, QWidget *parent = 0);
    ~MainWindow();
    int fd;
    QString username;
    void get_unread_num();
private:
    Ui::MainWindow *ui;
    QStackedWidget *stack;

private slots:
    void on_recyclebin_clicked();
    void on_draft_clicked();
    void on_sendmail_clicked();
    void on_receive_clicked();
    void on_writemail_clicked();
    void on_pushButton_clicked();
    void on_label_4_linkActivated(QString link);
    void on_logout_clicked();
};

#endif // MAINWINDOW_H
