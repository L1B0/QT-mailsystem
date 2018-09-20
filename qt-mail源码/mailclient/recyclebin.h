#ifndef RECYCLEBIN_H
#define RECYCLEBIN_H

#include <QWidget>

namespace Ui {
    class recyclebin;
}

class recyclebin : public QWidget
{
    Q_OBJECT

public:
    explicit recyclebin(QWidget *parent = 0);
    ~recyclebin();

private:
    Ui::recyclebin *ui;
};

#endif // RECYCLEBIN_H
