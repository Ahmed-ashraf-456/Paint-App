/*
 *  Canvas class and their interaction with DrawAssistant are the key point of the program logic.
 *  DrawAssistant provides common data (current brush width, color, provides with constructed Shape objects).
 *  In it's turn, Canvas encapsulates all drawable entities, provides interface for drawing, and the RTTI ensures
 *  that each entity will be drawn in a correct way.
 *
 */

#pragma once

#include <QWidget>
#include <QStack>
#include <QPainter>
#include <QPair>
#include <QMouseEvent>
#include <QAction>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <QtMath>
#include <QDebug>
#include<QMessageBox>
#include <search.h>
#include<algorithm>

#include "drawassistant.h"
#include "interfaces/shape.h"

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:

    explicit Canvas(QWidget *parent = nullptr, DrawAssistant *assistant = nullptr);
      Canvas(float x,float y,QString w);
    ~Canvas();

    void setDrawAssistant(DrawAssistant &assistant);
    void clearCanvas();
    void setBackgroundColor(const QColor &);

    void undo();
    void redo();
    void search();
    void sort();
    void bubble_sort(double arr[],int n);


    float arearectangle(double x,double y);
    float areacircle(double x,double y);
    float arealine();
    float perameterrectangle(double x,double y);
    float perametercircle(double x,double y);
    float perameterrline(double x,double y);
    float getarea();
    float getparemeter();
    QString getname();
    void fillvector(QVector<DrawAssistant>&  , float area ,float parimeter,QString name);
    void passShapeIdToAssistant(double areatoass,double parimetertoass,QString nametoass);

private:

    Ui::Canvas *ui;
    QVector<DrawAssistant> mydata;
    QVector<std::shared_ptr<IDrawable>>_shapes;
    QStack<std::shared_ptr<IDrawable>> _undoRedoStack;
    DrawAssistant* _drawAssistant;
    double x_coor_R;
    double y_coor_R;
    double x_coor_P;
    double y_coor_P;
    float helparea;
    float helpparimater;
    QString helpname;


protected:

    void paintEvent(QPaintEvent *eve);
    void mousePressEvent(QMouseEvent *eve);
    void mouseMoveEvent(QMouseEvent *eve);
    void mouseReleaseEvent(QMouseEvent *eve);

};
