#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QImageWidget* img = new QImageWidget(parent);
    ui->verticalLayout_1->addWidget(img);
    connect(ui->pushButton,SIGNAL(clicked()),img,SLOT(openFile()));
    connect(img,SIGNAL(imgTextChanged(QString)),this,SLOT(textImgShow(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::textImgShow(QString tex)
{

    ui->lineEdit->setText(tex);
}




