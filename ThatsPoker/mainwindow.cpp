#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <processor.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->m_processorProgressBar->setVisible(false);

    m_processorThread = new Processor("probas.xml");
    connect(m_processorThread, SIGNAL(onProcessStart()), this, SLOT(onProcessorProcessStart()));
    connect(m_processorThread, SIGNAL(onCategoryStart(unsigned int)), this, SLOT(onProcessorCategoryStart(unsigned int)));
    connect(m_processorThread, SIGNAL(onHandStart(unsigned int,unsigned int)), this, SLOT(onProcessorHandStart(unsigned int, unsigned int)));
    connect(m_processorThread, SIGNAL(onHandEnd()), this, SLOT(onProcessorHandEnd()));
    connect(m_processorThread, SIGNAL(onCategoryEnd()), this, SLOT(onProcessorCategoryEnd()));
    connect(m_processorThread, SIGNAL(onProcessDone()), this, SLOT(onProcessorProcessDone()));
    connect(m_processorThread, SIGNAL(onPercentageChange(double)), this, SLOT(onProcessorPercentageChange(double)));
}

MainWindow::~MainWindow()
{
    delete ui;

    m_processorThread->quit();
    m_processorThread->wait();
    delete m_processorThread;
}

void MainWindow::refreshProbas()
{
    if(! m_processorThread->isProcessing())
        m_processorThread->start();
}

void MainWindow::onProcessorProcessStart()
{
    ui->m_processorProgressBar->setVisible(true);
    ui->m_processorProgressBar->setValue(0.);
}

void MainWindow::onProcessorCategoryStart(unsigned int a_category)
{

}

void MainWindow::onProcessorHandStart(unsigned int a_hand1, unsigned int a_hand2)
{

}

void MainWindow::onProcessorHandEnd()
{

}

void MainWindow::onProcessorCategoryEnd()
{

}

void MainWindow::onProcessorProcessDone()
{
    ui->m_processorProgressBar->setVisible(false);
}

void MainWindow::onProcessorPercentageChange(double a_percentDone)
{
    int newValue = (int) a_percentDone;
    int currentValue = ui->m_processorProgressBar->value();

    if(newValue != currentValue)
        ui->m_processorProgressBar->setValue(a_percentDone);
}

