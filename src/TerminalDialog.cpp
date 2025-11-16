/*
================================
Intractive Terminal to run scripts
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#include <QDebug>
#include <QScrollBar>
#include "TerminalDialog.h"

TerminalDialog::TerminalDialog(const QString &program, const QStringList &arguments, QWidget *parent)
    : QDialog(parent),
      process(new QProcess(this))
{
    setWindowTitle(QString("Interactive Process: %1").arg(program));
    setMinimumSize(700, 500);


    outputDisplay = new QTextEdit(this);
    outputDisplay->setReadOnly(true);

    outputDisplay->setStyleSheet("background-color: #000000; color: #00FF00; font-family: 'Consolas', 'Monospace'; font-size: 12pt; border: none; padding: 10px;");

    inputLine = new QLineEdit(this);
    inputLine->setPlaceholderText("Type your input and press Enter...");
    inputLine->setStyleSheet("background-color: #2c2c2c; color: #ffffff; border: 1px solid #444444; border-radius: 4px; padding: 12px; font-size: 10pt;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(outputDisplay);
    mainLayout->addWidget(inputLine);

    connect(process, &QProcess::readyReadStandardOutput, this, &TerminalDialog::readStandardOutput);
    connect(process, &QProcess::readyReadStandardError, this, &TerminalDialog::readStandardError);
    connect(process, &QProcess::finished, this, &TerminalDialog::processFinished);
    connect(inputLine, &QLineEdit::returnPressed, this, &TerminalDialog::sendInputToProcess);

    process->start(program, arguments);

    if (!process->waitForStarted(2000)) {
        outputDisplay->append("<span style='color: red;'>*** ERROR: Could not start process. Check PATH and script location. ***</span>");
        inputLine->setEnabled(false);
    } else {
        outputDisplay->append(QString("<span style='color: yellow;'>[Process '%1' started. Enter input when prompted.]</span>").arg(program));
        inputLine->setFocus();
    }
}

TerminalDialog::~TerminalDialog()
{
    if (process->state() != QProcess::NotRunning) {
        process->terminate();
        process->waitForFinished(500);
    }
}

void TerminalDialog::readStandardOutput()
{
    QByteArray output = process->readAllStandardOutput();

    outputDisplay->append(QString::fromUtf8(output).trimmed().replace("\n", "<br>"));
    outputDisplay->verticalScrollBar()->setValue(outputDisplay->verticalScrollBar()->maximum());
}

void TerminalDialog::readStandardError()
{
    QByteArray error = process->readAllStandardError();

    outputDisplay->append(QString("<span style='color: #FF5555;'>%1</span>").arg(QString::fromUtf8(error).trimmed().replace("\n", "<br>")));
    outputDisplay->verticalScrollBar()->setValue(outputDisplay->verticalScrollBar()->maximum());
}

void TerminalDialog::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString statusMsg;
    if (exitStatus == QProcess::NormalExit) {
        statusMsg = QString("Process finished normally. Exit Code: %1").arg(exitCode);
    } else {
        statusMsg = QString("Process terminated unexpectedly. Exit Status: %1").arg(exitStatus);
    }

    outputDisplay->append(QString("<br><span style='color: #4CC9F0;'>--- %1 ---</span>").arg(statusMsg));
    inputLine->setEnabled(false);
    inputLine->setPlaceholderText("Process finished. Close this window.");
}

void TerminalDialog::sendInputToProcess()
{
    QString input = inputLine->text() + "\n"; // Append newline character to simulate 'Enter'
    QByteArray inputData = input.toUtf8();

    if (process->state() == QProcess::Running) {
        qint64 bytesWritten = process->write(inputData);

        if (bytesWritten > 0) {
            outputDisplay->append(QString("<span style='color: #00FFFF;'>&gt; %1</span>").arg(inputLine->text()));
            outputDisplay->verticalScrollBar()->setValue(outputDisplay->verticalScrollBar()->maximum());
        }
    }


    inputLine->clear();
}
