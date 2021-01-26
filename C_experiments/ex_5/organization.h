#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QWidget>

namespace Ui {
class Organization;
}

class Organization : public QWidget
{
    Q_OBJECT

public:
    explicit Organization(QWidget *parent = nullptr);
    ~Organization();

private:
    Ui::Organization *ui;
};

#endif // ORGANIZATION_H
