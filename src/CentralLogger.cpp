/*
================================
Central Logging
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include "CentralLogger.h"

QFile* CentralLogger::logFile = nullptr;
QTextStream* CentralLogger::logStream = nullptr;
QMutex CentralLogger::logMutex;

bool CentralLogger::initialize(const QString& logFilePath)
{
    cleanup();

    logFile = new QFile(logFilePath);

    if (!logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qCritical() << "Failed to open log file:" << logFilePath;
        delete logFile;
        logFile = nullptr;
        return false;
    }

    logStream = new QTextStream(logFile);

    qInstallMessageHandler(customMessageHandler);

    qInfo() << "--- Logger Initialized Successfully ---";
    return true;
}

void CentralLogger::cleanup()
{
    qInstallMessageHandler(nullptr);

    if (logFile && logFile->isOpen()) {
        logFile->close();
    }

    delete logStream;
    logStream = nullptr;
    delete logFile;
    logFile = nullptr;
}

void CentralLogger::customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QMutexLocker locker(&logMutex);

    if (!logStream) {
        QTextStream(stderr) << msg << Qt::endl;
        return;
    }

    QString logType;
    switch (type) {
    case QtDebugMsg:    logType = "DEBUG"; break;
    case QtInfoMsg:     logType = "INFO "; break;
    case QtWarningMsg:  logType = "WARN "; break;
    case QtCriticalMsg: logType = "CRIT "; break;
    case QtFatalMsg:    logType = "FATAL"; break;
    default:            logType = "OTHER"; break;
    }

    const QString formattedMessage = QString("[%1] [%2] (%3:%4) - %5")
        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
        .arg(logType)
        .arg(context.file)
        .arg(context.line)
        .arg(msg);


    *logStream << formattedMessage << Qt::endl;
    logStream->flush();

    QTextStream(stderr) << formattedMessage << Qt::endl;

    if (type == QtFatalMsg) {
        abort();
    }
}
