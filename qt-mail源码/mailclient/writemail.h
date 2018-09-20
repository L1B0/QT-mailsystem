#ifndef WRITEMAIL_H
#define WRITEMAIL_H

#include <QWidget>
#include <QDebug>
#include <QDateTime>

namespace Ui {
    class writemail;
}

class writemail : public QWidget
{
    Q_OBJECT

public:
    explicit writemail(QString username, int fd, QWidget *parent = 0);
    ~writemail();
    int fd;
    QString username;

private:
    Ui::writemail *ui;

private slots:
    void on_CLOSEB_clicked();
    void on_SENDB_clicked();
};

#endif // WRITEMAIL_H
