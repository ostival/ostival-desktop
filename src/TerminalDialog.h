/*
================================
Intractive Terminal to run scripts
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/
#ifndef TERMINALDIALOG_H
#define TERMINALDIALOG_H

#include <QDialog>
#include <QProcess>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>

class TerminalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TerminalDialog(const QString &program, const QStringList &arguments, QWidget *parent = nullptr);
    ~TerminalDialog();

private slots:
    void readStandardOutput();
    void readStandardError();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void sendInputToProcess();

private:
    QProcess *process;
    QTextEdit *outputDisplay;
    QLineEdit *inputLine;
};

#endif
