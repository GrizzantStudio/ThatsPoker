#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class Processor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private :

    Processor * m_processorThread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots :

    void refreshProbas();

    void onProcessorProcessStart();
    void onProcessorCategoryStart(unsigned int a_category);
    void onProcessorHandStart(unsigned int a_hand1, unsigned int a_hand2);
    void onProcessorHandEnd();
    void onProcessorCategoryEnd();
    void onProcessorProcessDone();
    void onProcessorPercentageChange(double a_percentDone);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
