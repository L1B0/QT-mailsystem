#ifndef FIRSTSTACK_H
#define FIRSTSTACK_H

#include <QWidget>

namespace Ui {
    class firststack;
}

class firststack : public QWidget
{
    Q_OBJECT

public:
    explicit firststack(QWidget *parent = 0);
    ~firststack();

private:
    Ui::firststack *ui;
};

#endif // FIRSTSTACK_H
