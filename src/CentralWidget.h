/*
================================
Central Widget (Currently Text Editor)
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QSyntaxHighlighter>
#include "DrawSchematic.h"

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = nullptr);

private slots:
    void saveText();
    void launchTerminal();
    void launchTerminal1();
    void launchTerminal2();
    void openVcdViewer();

public slots:
    void openFileInEditor(const QString &fileName);
    void openSchematicWindow();

private:
    QTextEdit *OstivalTextEdit;
    QString currentFilePath;
    QSyntaxHighlighter *currentHighlighter = nullptr;
    DrawSchematic *schematicWindow = nullptr;
    QPushButton *saveButton;
    QPushButton *schematicButton;
    QPushButton *terminalButton;
    QPushButton *vcdButton;
    QPushButton *iverilogButton;
    QPushButton *vvpButton;

};

#endif