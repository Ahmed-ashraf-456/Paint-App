#include "dialoge_size.h"
#include "ui_dialoge_size.h"

Dialoge_Size::Dialoge_Size(QWidget *parent) :QDialog(parent),ui(new Ui::Dialoge_Size)
{
    ui->setupUi(this);
}

Dialoge_Size::~Dialoge_Size()
{
    delete ui;
}

void Dialoge_Size::mousePressEvent(QMouseEvent *event)
{
ui->label_press_eve->setText("Mouse Press Event : X:"+ QString::number(event->x())+ " Y:"+QString::number(event->y()));
}

void Dialoge_Size::mouseReleaseEvent(QMouseEvent *event)
{
ui->label_release_eve->setText("Mouse Release Event : X:"+ QString::number(event->x())+ " Y:"+QString::number(event->y()));
}
