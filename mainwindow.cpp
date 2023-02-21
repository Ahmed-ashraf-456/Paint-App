#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    try
    {
        DrawAssistant &drawAssistant = DrawAssistant::getInstance();

        canvas = new Canvas(this, &drawAssistant);
        setCentralWidget(canvas);

        shapeNameLabel = new QLabel("Tool: Brush");
        shapeWidthLabel = new QLabel("\tWidth: 5");
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

    this->resize(1000, 800);
    this->setWindowIcon(QIcon("://resource//icon.png"));

    auto font = shapeNameLabel->font();
    font.setBold(true);
    font.setPointSize(8);

    shapeNameLabel->setFont(font);
    shapeWidthLabel->setFont(font);

    ui->toolBar->addWidget(shapeNameLabel);
    ui->toolBar->addWidget(shapeWidthLabel);

    this->setWindowTitle("Paint project");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::passShapeIdToAssistant(ShapesId shapeId ,int x)
{
    try
    {
        DrawAssistant &drawAssistant = DrawAssistant::getInstance();
        drawAssistant.setNewShapeId(shapeId);
        drawAssistant.setshapeid(x);
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

void MainWindow::on_actionClear_triggered()
{
    this->canvas->clearCanvas();
    this->update();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionBrush_triggered()
{
    shapeNameLabel->setText("Tool: Brush");
    count =0;

    passShapeIdToAssistant(ShapesId::BRUSH,count);
}

void MainWindow::on_actionLine_triggered()
{
    shapeNameLabel->setText("Tool: Line");
    count =3;

    passShapeIdToAssistant(ShapesId::LINE,count);
   // dialoge = new Dialoge_Size(this);
  //  dialoge->show();
}

void MainWindow::on_actionRectangle_triggered()
{

    shapeNameLabel->setText("Tool: Rectangle");
    count = 2;

    passShapeIdToAssistant(ShapesId::RECTANGLE,2);
    //dialoge = new Dialoge_Size(this);
    //dialoge->show();

}

void MainWindow::on_actionEllipse_triggered()
{
    shapeNameLabel->setText("Tool: Circle");
    count = 1;
   passShapeIdToAssistant(ShapesId::CIRCLE , count);
    //dialoge = new Dialoge_Size(this);
    //dialoge->show();
}

void MainWindow::on_actionWidth_triggered()
{
    DrawAssistant &drawAssistant = DrawAssistant::getInstance();

    DialogBrushWidth dialog;
    dialog.setValue(drawAssistant.getCurrentWidth());

    if (dialog.exec() == QDialog::Accepted)
    {
        int width = dialog.getValue();
        drawAssistant.setCurrentWidth(width);

        shapeWidthLabel->setText("\tWidth: " + QString::number(width));
    }
}

void MainWindow::on_actionColor_triggered()
{
    QColorDialog colorDialog;

    QColor color = colorDialog.getColor();

    DrawAssistant &drawAssistant = DrawAssistant::getInstance();
    drawAssistant.setCurrentColor(color);
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::information(this, "Simple paint-like application",
                             "offers minimalistic design and tools for drawing geometric primitives. "
                             "Changing of pen color/thickness is available. "
                             "Application gives the ability to save your paintings. "
                             "Created by Ahmed Ashraf : ahmdabwsad@gmail.com");
}

void MainWindow::on_actionUndo_triggered()
{
    this->canvas->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    this->canvas->redo();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save your art", "",
                                                    "JPEG(*.jpg;*.jpeg;*.jpe);;All Files (*)");

    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "OOPS!",
                                  "Failed to retrieve filename and save.");
    }
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::warning(this, "Unable to open file for writing.",
                                     file.errorString());
            return;
        }

        QPixmap px = ui->centralWidget->grab();

        QDataStream out(&file);
        out << px;

        file.close();
    }
}



void MainWindow::on_action_Search_triggered()
{
    //this->canvas->search();
}


void MainWindow::on_action_Sort_triggered()
{
    //this->canvas->sort();
}

