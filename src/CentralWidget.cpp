/*
================================
Central Widget (Currently Text Editor)
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include <QVBoxLayout>
#include <QFont>
#include <QFile>
#include <QShortcut>
#include <QKeySequence>
#include "CentralWidget.h"
#include "SyntaxHighlighter.h"
#include "config.h"

const QString MODERN_BUTTON_STYLE = R"(
    QPushButton {
        background-color: #00A9A5;
        color: white;
        border: none;
        border-radius: 6px;
        padding: 8px 16px;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: #008F8B;
    }
    QPushButton:pressed {
        background-color: #006B68;
    }
)";

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent) {

    OstivalTextEdit = new QTextEdit(this);
    
    OstivalTextEdit->setPlaceholderText("Ostival text editor...");

    OstivalTextEdit->setFont(QFont("Courier", 16));

    OstivalTextEdit->setStyleSheet("background-color: #282A36; color: #F8F8F2;");

    new SyntaxHighlighter(OstivalTextEdit->document());

    saveButton = new QPushButton("Save File", this);
    saveButton->setFixedHeight(36);
    saveButton->setStyleSheet(MODERN_BUTTON_STYLE);
    schematicButton = new QPushButton("Open Schematic", this);

    /*
    For handling save file 1. keyboard 2. button in UI
    */
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+s"), this);
    connect(shortcut, &QShortcut::activated, this, &CentralWidget::saveText);
    connect(saveButton, &QPushButton::clicked, this, &CentralWidget::saveText);
    connect(schematicButton, &QPushButton::clicked, this, &CentralWidget::openSchematicWindow);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(OstivalTextEdit);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(schematicButton);

    setLayout(mainLayout);
}


void CentralWidget::saveText()
{
    if (currentFilePath.isEmpty()) {
        qWarning() << "No file currently open to save!";
        return;
    }

    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot save file:" << currentFilePath << file.errorString();
        return;
    }

    file.write(OstivalTextEdit->toPlainText().toUtf8());
    file.close();

    qDebug() << "File saved:" << currentFilePath;
}


void CentralWidget::openFileInEditor(const QString &fileName)
{
    QString filePath = projectPath + "/" + projectName + fileName;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file:" << filePath << file.errorString();
        currentFilePath.clear();
        return;
    }

    OstivalTextEdit->setPlainText(file.readAll());
    file.close();

    currentFilePath = filePath;
    qDebug() << "Loaded file into editor:" << filePath;
}


void CentralWidget::openSchematicWindow()
{
    if (schematicWindow == nullptr) {
        schematicWindow = new DrawSchematic();
        
        schematicWindow->setAttribute(Qt::WA_DeleteOnClose);
        
        connect(schematicWindow, &QObject::destroyed, [this]() {
            schematicWindow = nullptr;
        });
    }

    schematicWindow->show();
    schematicWindow->raise();
    schematicWindow->activateWindow();
}