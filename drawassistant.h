/*
 * DrawAssistant is a singleton, mediate class between MainWindow and Canvas. It encapsulates the logic
 * of run-time objects identification and creation of the necessary ones, depending on options, chosen by
 * user.
 *
 */

#pragma once

#include <QMap>
#include <QColor>
#include <QString>
#include <QMessageBox>
#include <exception>
#include <functional>
#include <algorithm>

#include "shapes/line.h"
#include "shapes/brush.h"
#include "shapes/rectangle.h"
#include "shapes/circle.h"

class Shape;

enum class ShapesId{BRUSH, LINE, RECTANGLE, CIRCLE, LOL,TRIANGLE};

class DrawAssistant
{
public:

    void setarea(double areafromcanvas);
    void setparimeter(double parimeterfromcanvas);
    void setname(QString namefromcanvas);
    double getarea() const;
    double getparimeter() const;
    QString getname()const ;

    DrawAssistant(float x ,float y ,QString w);
    static DrawAssistant& getInstance();
    void setNewShapeId(ShapesId id);

    int getshapeid();
    void setshapeid(int x);

    void setCurrentWidth(int width);
    int getCurrentWidth()const;

    void setCurrentColor(const QColor &color);
    QColor getCurrentColor()const;

    std::shared_ptr<IDrawable> getShapeById(ShapesId shapeId);
    std::shared_ptr<IDrawable> getCurrentShape()const;

    void startShapeDerivation(const QPoint& startPoint);
    void finishShapeDerivation(const QPoint& endPoint);

    DrawAssistant(DrawAssistant &) = delete;
    DrawAssistant(DrawAssistant &&) = delete;

    DrawAssistant& operator=(DrawAssistant &) = delete;
    DrawAssistant& operator=(DrawAssistant &&) = delete;

private:

    ShapesId _currentShapeId;
    int xx;
    double area;
    double parimeter;
    QString name;
    int _currentWidth;
    QColor _currentColor;
    std::shared_ptr<IDrawable> _currentShape;
    QMap<ShapesId, std::function<std::shared_ptr<IDrawable>()>> _shapesList;

    DrawAssistant();
    std::shared_ptr<IDrawable> shapeFabric(ShapesId shapeId);
};
