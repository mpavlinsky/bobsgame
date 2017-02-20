#ifndef _UTTHREAD_H
#define _UTTHREAD_H

#include <QtCore/QCoreApplication>
#include <QThread>
class UTThread : public QThread
{
    Q_OBJECT
     // private run
    void run (){}
    public:
        static void sleep(unsigned long secs) {
            QThread::sleep(secs);
        }
        static void msleep(unsigned long msecs) {
            QThread::msleep(msecs);
        }
        static void usleep(unsigned long usecs) {
            QThread::usleep(usecs);
        }
};

#endif