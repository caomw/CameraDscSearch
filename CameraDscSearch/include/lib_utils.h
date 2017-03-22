#ifndef LIB_UTILS_H
#define LIB_UTILS_H

#include <QThread>
#include <QString>

#include <iostream>

class Sleeper: public QThread {
public:
    static void usleep(unsigned long dt) { QThread::usleep(dt); }
    static void msleep(unsigned long dt) { QThread::msleep(dt); }
    static void sleep (unsigned long dt) { QThread::sleep (dt); }
};

class SortedIndex {
public:
    SortedIndex() : idx(-1), val(-1) {}
    SortedIndex(int idx, double val) {
        this->idx   = idx;
        this->val   = val;
    }
    ~SortedIndex(){}
    QString toQString() const {
        return QString("%1 -> %2").arg(idx).arg(val);
    }
    std::string toString() const {
        return toQString().toStdString();
    }
    bool operator <(const SortedIndex& o) const {
        return ( (*this).val < o.val );
    }
    friend std::ostream& operator<< (std::ostream& out, const SortedIndex& si);
public:
    int     idx;
    double val;
};

#ifdef _UNIX
#include <cstdio>
#include <sys/time.h>
class SimpleTimer {
 private:
    timeval     startTime;
    timeval     stopTime;
    double      duration;
 public:
    void start() {
        gettimeofday(&startTime, NULL);
    }
    double stop()  {
        gettimeofday(&stopTime, NULL);
        duration = (stopTime.tv_sec-startTime.tv_sec)*1000.0 + (stopTime.tv_usec-startTime.tv_usec)/1000.0;
        return duration;
    }
    void printTime() {
        printf("%5.6fms\n", duration);
    }
    void stopAndPrint() {
        stop();
        printTime();
    }
    void stopAndPrint(const std::string& msg) {
        stop();
        printf("%s: %5.6fms\n", msg.c_str(),  duration);
    }
};
#endif

#endif // LIB_UTILS_H
