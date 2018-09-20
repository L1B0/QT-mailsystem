#ifndef RECEIVE_H
#define RECEIVE_H

#include <QWidget>
#include <QDebug>

namespace Ui {
    class receive;
}

class receive : public QWidget
{
    Q_OBJECT

public:
    explicit receive(const char *sender, const char *title, const char *time, const char *text, QWidget *parent = 0);
    explicit receive(QWidget *parent = 0);
    ~receive();
    const char *sender;
    const char *title;
    const char *time;
    const char *text;

private slots:

private:
    Ui::receive *ui;
};

#endif // RECEIVE_H
