#ifndef SENDMAIL_H
#define SENDMAIL_H

#include <QWidget>
#include <QDebug>

namespace Ui {
    class sendmail;
}

class sendmail : public QWidget
{
    Q_OBJECT

public:
    explicit sendmail(const char *recver, const char *title, const char *time, const char *text, QWidget *parent = 0);
    explicit sendmail(QWidget *parent = 0);
    ~sendmail();
    const char *recver;
    const char *title;
    const char *time;
    const char *text;

private slots:

private:
    Ui::sendmail *ui;
};

#endif // SENDMAIL_H
