#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QThread>

class Processor : public QThread
{
    Q_OBJECT

private :

    bool m_isProcessing;
    QString m_filepath;

public:
    Processor(QString a_filepath);
    ~Processor();

public :

    bool isProcessing();

public :
    void run () Q_DECL_OVERRIDE ;

signals:

    void onProcessStart();
    void onCategoryStart(unsigned int a_category);
    void onHandStart(unsigned int a_hand1, unsigned int a_hand2);
    void onHandEnd();
    void onCategoryEnd();
    void onProcessDone();
    void onPercentageChange(double a_percentDone);
};

#endif // PROCESSOR_H
