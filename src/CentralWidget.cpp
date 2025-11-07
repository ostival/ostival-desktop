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
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "CentralWidget.h"
#include "SyntaxHighlighter.h"
#include "SyntaxHighlighterPython.h"
#include "config.h"
#include "TerminalDialog.h"
#include "VcdViewer.h"


CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent) {

    OstivalTextEdit = new QTextEdit(this);
    OstivalTextEdit->setPlaceholderText("Ostival text editor...");
    OstivalTextEdit->setFont(QFont("Courier", 16));
    OstivalTextEdit->setStyleSheet("background-color: #282A36; color: #F8F8F2;");

    saveButton = new QPushButton("Save File", this);
    saveButton->setFixedHeight(36);
    saveButton->setStyleSheet(MODERN_BUTTON_STYLE);

    schematicButton = new QPushButton("Open Schematic", this);
    schematicButton->setStyleSheet(MODERN_BUTTON_STYLE1);
    schematicButton->setFixedHeight(36);

    // --- New Terminal Button ---
    terminalButton = new QPushButton("Run Python Script", this);
    terminalButton->setStyleSheet(MODERN_BUTTON_STYLE2);
    terminalButton->setFixedHeight(36);

    // --- Run iVerilog ---
    iverilogButton = new QPushButton("Run iVerilog", this);
    iverilogButton->setStyleSheet(MODERN_BUTTON_STYLE3);
    iverilogButton->setFixedHeight(36);

    // --- Run VVP ---
    vvpButton = new QPushButton("run VVP", this);
    vvpButton->setStyleSheet(MODERN_BUTTON_STYLE4);
    vvpButton->setFixedHeight(36);

    // VCD dialog open button
    vcdButton = new QPushButton("Open VCD Viewer", this);
    vcdButton->setStyleSheet(MODERN_BUTTON_STYLE5);
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
    connect(vvpButton, &QPushButton::clicked, this, &CentralWidget::launchTerminal2);
    connect(vcdButton, &QPushButton::clicked, this, &CentralWidget::openVcdViewer);

    auto *mainLayout = new QVBoxLayout;
    QHBoxLayout* buttonRowLayout = new QHBoxLayout;

    buttonRowLayout->addWidget(saveButton);
    buttonRowLayout->addWidget(iverilogButton);
    buttonRowLayout->addWidget(vvpButton);
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
    QStringList arguments;

    script_path = projectPath + "/" + projectName + "/python_src/" + mainPythonFile;

    #ifdef Q_OS_WIN
        program = "python";
    #else
        program = "python3";
    #endif

    arguments << script_path;

    if (mainPythonFile == ""){
        QMessageBox::warning(this, "No Main File Exists","Right click on the file and choose select main file before running the Python script.");
    } else {
        TerminalDialog *dialog = new TerminalDialog(program, arguments, this);
        dialog->setModal(false); 
        dialog->setAttribute(Qt::WA_DeleteOnClose); 
        dialog->show();
    }
}

void CentralWidget::launchTerminal1(){
    QStringList arguments;
    QString program;
    QString script_path;
    QString output_path;
    QString jsonpath;
    int designArrayLength;
    int testbenchArrayLength;
    
    jsonpath = projectPath + "/" + projectName + "/" + projectName + ".ostival";
    script_path = projectPath + "/" + projectName + "/design_src/";
    output_path = projectPath + "/" + projectName + "/all_log_files/main";

    program = "iverilog";

    arguments << "-o";
    arguments << output_path;

    QFile f(jsonpath);

    if (f.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
        f.close();

        QJsonObject obj = doc.object();
        QJsonArray designArr = obj["src_files"].toArray();
        QJsonArray testbenchArr = obj["testbench_files"].toArray();

        designArrayLength = designArr.size();
        testbenchArrayLength = testbenchArr.size();

        for (int makepath = 0; makepath < testbenchArrayLength; makepath++ ){
            QString quotedFileName = testbenchArr[makepath].toString();

            if (quotedFileName.startsWith('"') && quotedFileName.endsWith('"') && quotedFileName.length() >= 2) {
                quotedFileName = quotedFileName.mid(1, quotedFileName.length() - 2);
            }
            QString makingpath = script_path + quotedFileName;
            
            qDebug() << makingpath;
            arguments << makingpath;
        }

        for (int makepath = 0; makepath < designArrayLength; makepath++ ){
            QString quotedFileName = designArr[makepath].toString();

            if (quotedFileName.startsWith('"') && quotedFileName.endsWith('"') && quotedFileName.length() >= 2) {
                quotedFileName = quotedFileName.mid(1, quotedFileName.length() - 2);
            }
            QString makingpath = script_path + quotedFileName;
            
            qDebug() << makingpath;
            arguments << makingpath;
        }
    } else {
        QMessageBox::warning(this, "No Main File Exists","Unable to read the file");
    }

    if (designArrayLength == 0 && testbenchArrayLength == 0){
        QMessageBox::warning(this, "No Main File Exists","Right click on the file and choose select main file before running the iVerilog");
    } else {
        qDebug() << "running the program";
        TerminalDialog *dialog = new TerminalDialog(program, arguments, this);
        dialog->setModal(false); 
        dialog->setAttribute(Qt::WA_DeleteOnClose); 
        dialog->show();
    }
}

void CentralWidget::launchTerminal2(){
    QString program;
    QString file_path;
    QStringList arguments;

    file_path = projectPath + "/" + projectName + "/all_log_files/main";
    program = "vvp";
    arguments << file_path;

    if (QFile::exists(file_path)){
        TerminalDialog *dialog = new TerminalDialog(program, arguments, this);
        dialog->setModal(false); 
        dialog->setAttribute(Qt::WA_DeleteOnClose); 
        dialog->show();
    } else {
        QMessageBox::warning(this, "No Main File Exists","The is no output form iVerilog, either compile the project or fix the error if there are some");
    }
}

void CentralWidget::openVcdViewer()
{
    // Create and show the VCD Viewer dialog
    VcdViewer *viewer = new VcdViewer(this);
    viewer->setModal(false); 
    viewer->setAttribute(Qt::WA_DeleteOnClose); 
    viewer->show();
}