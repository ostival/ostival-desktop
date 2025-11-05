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
    void openVcdViewer();

public slots:
    void openFileInEditor(const QString &fileName);
    void openSchematicWindow();

private:
    QTextEdit *OstivalTextEdit;
    QPushButton *saveButton;
    QString currentFilePath;
    QPushButton *schematicButton;
    DrawSchematic *schematicWindow = nullptr;
    QPushButton *terminalButton;
    QPushButton *vcdButton;
    QSyntaxHighlighter *currentHighlighter = nullptr;
    QPushButton *iverilogButton;

};

#endif