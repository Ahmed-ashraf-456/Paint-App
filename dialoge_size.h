#ifndef DIALOGE_SIZE_H
#define DIALOGE_SIZE_H
#include<QMouseEvent>
#include <QDialog>
namespace Ui {
class Dialoge_Size;
}

class Dialoge_Size : public QDialog
{
    Q_OBJECT

public:
     Dialoge_Size(QWidget *parent = nullptr);
    ~Dialoge_Size();
   void mousePressEvent(QMouseEvent* event);
   void mouseReleaseEvent(QMouseEvent* event);
private:
    Ui::Dialoge_Size *ui;

};

#endif // DIALOGE_SIZE_H
