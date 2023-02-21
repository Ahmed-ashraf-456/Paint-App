#include "canvas.h"
#include "ui_canvas.h"
#include<QInputDialog>

Canvas::Canvas(QWidget *parent, DrawAssistant *assistant)
   :QWidget(parent),
    ui(new Ui::Canvas),
    _drawAssistant(assistant)
{
    ui->setupUi(this);
    try{
    DrawAssistant &drawAssistant = DrawAssistant::getInstance();

    }
    catch (const std::bad_alloc & ex)
    {
        QMessageBox::critical(this, "Memory allocation error.", ex.what());

        close();
    }
    catch (...)
    {
        std::terminate();
    }
    setBackgroundColor(Qt::white);
}

Canvas::Canvas(float x, float y, QString w)
{
    helparea = x;
    helpparimater = y;
    helpname = w;
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);

    for(auto &shape : _shapes){

        shape->draw(&painter);
    }
}

void Canvas::mousePressEvent(QMouseEvent * ev)
{
    if (ev->buttons() & Qt::LeftButton){

        try
        {
            x_coor_P = ev->x()/37.8;
            y_coor_P = ev->y()/37.8;
            _drawAssistant->startShapeDerivation(ev->pos());

            _shapes.push_back(_drawAssistant->getCurrentShape());
        }
        catch(const std::bad_alloc & err)
        {
            QMessageBox::critical(this, "Memory allocation error.", err.what());

            exit(1);
        }
        catch(const std::runtime_error &err)
        {
            QMessageBox::critical(this, "!", err.what());

            exit(1);
        }
        catch(...)
        {
            std::terminate();
        }

        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent * ev)
{
    if (ev->buttons() & Qt::LeftButton){

        _drawAssistant->finishShapeDerivation(ev->pos());

        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *eve)
{
    x_coor_R = eve->x()/37.8;
    y_coor_R = eve->y()/37.8;
    if(_drawAssistant->getshapeid() != 0){
     QString name = QInputDialog::getText(this ,"shape name","Enter shape name");
   switch (_drawAssistant->getshapeid()){

   case (1):

       qDebug() << "Area of circle : "<<areacircle(x_coor_R,y_coor_R)<<" Parimeter of circle : "<<perametercircle(x_coor_R,y_coor_R)<<" name is "<< name;
       //fillvector(mydata , areacircle(x_coor_R,y_coor_R),perametercircle(x_coor_R,y_coor_R),name);
       break;


   case (2):

       qDebug() << "Area of rectangle : "<< arearectangle(x_coor_R,y_coor_R) <<" Parimeter of rectangle : "<<perameterrectangle(x_coor_R,y_coor_R)<<" name is "<< name ;
       //fillvector(mydata , arearectangle(x_coor_R,y_coor_R),perameterrectangle(x_coor_R,y_coor_R),name);
       break;


   case (3):

       qDebug() << "Area of line : "<<arealine()<< "parimeter of line : " <<perameterrline(x_coor_R,y_coor_R)<<" name is "<< name;
       //fillvector(mydata , arealine(),perameterrline(x_coor_R,y_coor_R),name);
       break;

   }
    }
}

void Canvas::setBackgroundColor(const QColor &col)
{
    QPalette pal;
    pal.setColor(QPalette::Window, col);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void Canvas::undo()
{
    if (!_shapes.empty()){

        std::shared_ptr<IDrawable> undoValue = _shapes.back();
        _undoRedoStack.push(undoValue);
        _shapes.pop_back();

        update();
    }
}

void Canvas::redo()
{
    if (!_undoRedoStack.empty()){

        std::shared_ptr<IDrawable> redoValue = _undoRedoStack.pop();
        _shapes.append(redoValue);

        update();
    }
}


//void Canvas::search()
//{
// QString name = QInputDialog::getText(this ,"shape name","Enter shape name");
// int size = mydata.size();
// for (int i =0; i < size ; i++){
//     if (name == mydata[i].getname());
//        qDebug ()<<"it found /t" <<"its area is: "<< mydata[i].getarea()  <<"its parimeter :"<<mydata[i].getparimeter();


// }

//}



//void Canvas::sort()
//{
//    int size = mydata.size();
//    double arr [size];
//    for (int i =0 ;i< size ; i++){
//            arr[i] = mydata[i].getparimeter();}
//    bubble_sort(arr,size);

//}


//void Canvas::bubble_sort(double arr[], int n)
//{
//    for (int i =1;i<= n-1;i++){
//        for (int j=0;j<=+(n-i-1);j++){
//             if(arr[j] > arr[j+1]){
//             std::swap(arr[j],arr[j+1]);}
//    }
//    }
//    for(int i = 0;i<n;i++)
//    qDebug()<<arr[i];
//}

float Canvas::arearectangle(double x,double y)
{
    double area = abs((x_coor_P - x)*(y_coor_P - y));
    return area;
}

float Canvas::areacircle(double x,double y)
{
    double pi =22/7;
    double area = abs(pi*(x_coor_P - x)*(y_coor_P - y)/4);
    return area;
}

float Canvas::arealine()
{
    return 0;
}

float Canvas::perameterrectangle(double x,double y)
{
    double paremeter = abs(((x_coor_P - x)+(y_coor_P - y))*2);
    return paremeter;
}

float Canvas::perametercircle(double x,double y)
{
    double pi = 22/7;
    double paremeter = abs(2*pi*(pow(pow((x_coor_P - x),2)+pow((y_coor_P - y),2),0.5))/8);
    return paremeter;
}

float Canvas::perameterrline(double x,double y)
{
    double length = abs(pow(pow((x_coor_P - x),2)+pow((y_coor_P - y),2),0.5));
    return length;
}

float Canvas::getarea()
{
    return helparea;
}

float Canvas::getparemeter()
{
    return helpparimater;
}

QString Canvas::getname()
{
    return helpname;
}

//void Canvas::fillvector(QVector<DrawAssistant>& myclass, float area, float parimeter, QString name)
//{
//    DrawAssistant newdata(area , parimeter, name);
//    myclass.push_back(newdata);
//}

void Canvas::passShapeIdToAssistant(double areatoass, double parimetertoass, QString nametoass)
{
    try
    {
        DrawAssistant &drawAssistant = DrawAssistant::getInstance();
        //drawAssistant.setNewShapeId(shapeId);
        //drawAssistant.setshapeid(x);
    }
    catch (const std::bad_alloc &ex)
    {
        QMessageBox::critical(this, "Allocation error!", ex.what());

        close();
    }
    catch (const std::bad_cast &ex)
    {
        QMessageBox::critical(this, "Cast error", ex.what());

        close();
    }
    catch(const std::runtime_error &ex)
    {
        QMessageBox::critical(this, "!", ex.what());

        close();
    }
    catch (...)
    {
        QMessageBox::critical(this, "Ouch!", "Something went wrong, please relaunch the program.");

        close();
    }
}

void Canvas::setDrawAssistant(DrawAssistant &assistant){

    _drawAssistant = &assistant;
}

void Canvas::clearCanvas()
{
    _shapes.clear();
    _undoRedoStack.clear();

    update();
}
