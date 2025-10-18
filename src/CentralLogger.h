#ifndef CENTRALLOGGER_H
#define CENTRALLOGGER_H

#include <QFile>
#include <QMutex>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>


class CentralLogger {
public:
    static bool initialize(const QString& logFilePath);
    static void cleanup();

private:
    static QFile* logFile;
    static QTextStream* logStream;
    static QMutex logMutex;
    static void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

    CentralLogger() = delete;
};

#endif