#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "processor.h"

#include <chrono>
#include <ctime>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Processor processor;

    std::chrono::time_point <std::chrono::system_clock> start = std::chrono::system_clock::now();

    processor.process();
    //processor.processHand(24, 48);

    std::chrono::time_point <std::chrono::system_clock> end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "Finished computation in " << (elapsed_seconds.count() * 1000.) << " ms" << std::endl;


}

MainWindow::~MainWindow()
{
    delete ui;
}
