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
#include "SyntaxHighlighterPython.h"
#include "config.h"
#include "TerminalDialog.h"
#include "VcdViewer.h"

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

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent) {

    OstivalTextEdit = new QTextEdit(this);
    OstivalTextEdit->setPlaceholderText("Ostival text editor...");
    OstivalTextEdit->setFont(QFont("Courier", 16));
    OstivalTextEdit->setStyleSheet("background-color: #282A36; color: #F8F8F2;");

    saveButton = new QPushButton("Save File", this);
    saveButton->setFixedHeight(36);
    saveButton->setStyleSheet(MODERN_BUTTON_STYLE);

    schematicButton = new QPushButton("Open Schematic", this);
    schematicButton->setStyleSheet("background-color: #aca634; color: white; border: none; border-radius: 4px; padding: 5px 10px; font-weight: bold;");
    schematicButton->setFixedHeight(36);

    // --- New Terminal Button ---
    terminalButton = new QPushButton("Run Python Script", this);
    terminalButton->setStyleSheet("background-color: #4CAF50; color: white; border: none; border-radius: 4px; padding: 5px 10px; font-weight: bold;");
    terminalButton->setFixedHeight(36);

    // --- Run iVerilog ---
    iverilogButton = new QPushButton("Run iVerilog", this);
    iverilogButton->setStyleSheet("background-color: #4CAF50; color: white; border: none; border-radius: 4px; padding: 5px 10px; font-weight: bold;");
    iverilogButton->setFixedHeight(36);

    // VCD dialog open button
    vcdButton = new QPushButton("Open VCD Viewer", this);
    vcdButton->setStyleSheet("background-color: #FF5555; color: white; border: none; border-radius: 4px; padding: 5px 10px; font-weight: bold;");
    vcdButton->setFixedHeight(36);

    /*
    For handling save file 1. keyboard 2. button in UI
    */
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+s"), this);
    connect(shortcut, &QShortcut::activated, this, &CentralWidget::saveText);
    connect(saveButton, &QPushButton::clicked, this, &CentralWidget::saveText);
    connect(schematicButton, &QPushButton::clicked, this, &CentralWidget::openSchematicWindow);
    connect(terminalButton, &QPushButton::clicked, this, &CentralWidget::launchTerminal);
    connect(iverilogButton, &QPushButton::clicked, this, &CentralWidget::launchTerminal1);
    connect(vcdButton, &QPushButton::clicked, this, &CentralWidget::openVcdViewer);

    auto *mainLayout = new QVBoxLayout;
    QHBoxLayout* buttonRowLayout = new QHBoxLayout;

    buttonRowLayout->addWidget(saveButton);
    buttonRowLayout->addWidget(iverilogButton);
    buttonRowLayout->addWidget(schematicButton);
    buttonRowLayout->addWidget(terminalButton);
    buttonRowLayout->addWidget(vcdButton);

    mainLayout->addWidget(OstivalTextEdit);
    mainLayout->addLayout(buttonRowLayout);
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
    // Delete the old syntax highlighter
    if (currentHighlighter) {
        delete currentHighlighter;
        currentHighlighter = nullptr;
    }

    // Determine highlighter based on the file extension
    if (fileName.endsWith(".v", Qt::CaseInsensitive)) {
        currentHighlighter = new SyntaxHighlighter(OstivalTextEdit->document());
        qDebug() << "Syntax Highlighter set to Verilog";
    } else if (fileName.endsWith(".py", Qt::CaseInsensitive)) {
        currentHighlighter = new SyntaxHighlighterPython(OstivalTextEdit->document());
        qDebug() << "Syntax Highlighter set to Python";
    } else {
        currentHighlighter = new SyntaxHighlighter(OstivalTextEdit->document());
        qDebug() << "Syntax Highlighter set to Default";
    }

    // Read the file
    QString filePath = projectPath + "/" + projectName + fileName;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file:" << filePath << file.errorString();
        currentFilePath.clear();
        return;
    }

    // Load the file into the text editor
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

void CentralWidget::launchTerminal(){

    QString program;
    QString script_path;

    script_path = projectPath + "/" + projectName + "/python_src/" + mainPythonFile;

    #ifdef Q_OS_WIN
        program = "python";
    #else
        program = "python3";
    #endif

    QStringList arguments;
    arguments << script_path;

    TerminalDialog *dialog = new TerminalDialog(program, arguments, this);
    dialog->setModal(false); 
    dialog->setAttribute(Qt::WA_DeleteOnClose); 
    dialog->show();
}

void CentralWidget::launchTerminal1(){

    QString program;
    QString script_path;
    QString output_path;

    script_path = projectPath + "/" + projectName + "/design_src/" + mainDesignFile;
    output_path = projectPath + "/" + projectName + "/all_log_files/main";

    program = "iverilog";

    QStringList arguments;
    arguments << "-o";
    arguments << output_path;
    arguments << script_path;

    TerminalDialog *dialog = new TerminalDialog(program, arguments, this);
    dialog->setModal(false); 
    dialog->setAttribute(Qt::WA_DeleteOnClose); 
    dialog->show();
}

void CentralWidget::openVcdViewer()
{
    // Create and show the VCD Viewer dialog
    VcdViewer *viewer = new VcdViewer(this);
    viewer->setModal(false); 
    viewer->setAttribute(Qt::WA_DeleteOnClose); 
    viewer->show();
}