#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{  
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->widget->setProportions(100,200,300);
    ui->widget->repaint();
    ui->label->setText("object "+ QString::number(1) + " contained " + QString::number(ui->widget->getNumbTriangles()) + " triangles");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->setProportions(250,300,50);
    ui->widget->repaint();
    ui->label->setText("object "+ QString::number(2) + " contained " + QString::number(ui->widget->getNumbTriangles()) + " triangles");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->widget->setProportions(120,140,350);
    ui->widget->repaint();
    ui->label->setText("object "+ QString::number(3) + " contained " + QString::number(ui->widget->getNumbTriangles()) + " triangles");
}
