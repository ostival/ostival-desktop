/*
========================================
The main function of the Ostival Desktop
----------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------
*/

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QProcess>
#include "config.h"
#include "ToolCommunicator.h"
#include "MainGUIWindow.h"
#include "InitialDialog.h"
#include "TempFiles.h"
#include "cliHandler.h"

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    /*
    Application metadata
    */
    app.setApplicationName(APP_NAME);
    app.setApplicationDisplayName(APP_NAME);
    app.setApplicationVersion(APP_VERSION);
    app.setOrganizationName(DEV_TEAM);
    app.setOrganizationDomain(DOMAIN_NAME);

    /*
    Command line parser for Command Line Interface (CLI)
    */
    QCommandLineParser parser;
    cliHandler::setupParser(parser);
    parser.process(app);

    /*
    Exit the application if it is running in CLI mode
    */
    if (cliHandler::run(parser) == 0) {
        return 0;
    }

    /*
    GUI application if there is no CLI command. 
    */
    qDebug() << "Ostival Desktop Started";

    /*
    VLSI Tool availability check
    */
   ToolCommunicator toolcheck;

    if(toolcheck.iverilogcheck())
        qDebug() << "iVerilog tool not found\n";

    if(toolcheck.yosyscheck())
        qDebug() << "Yosys tool not found\n";
    
    if(toolcheck.magiccheck())
        qDebug() << "Magic tool not found\n";

    if(toolcheck.netgencheck())
        qDebug() << "Netgen tool not found\n";

    /*
    Ensure temp file exsists or not. If not, create one so that we can use it for other purposes.
    Like, check the last project. No need to open initial dialog again and again.
    */
    TempFiles::ensureTempFileExists();

    QString projectName, projectPath;
    if (TempFiles::readTempFile(projectName, projectPath)) {
        qDebug() << "Project Name:" << projectName;
        qDebug() << "Project Path:" << projectPath;
    }

    /*
    Initial dialog box is added so that user can choose project path.
    */
    InitialDialog dialog;

    if (dialog.exec() == QDialog::Accepted)
    {
        /*
        Project path is the main directory for the app.
        Project name is the identifier for the project.
        */
        projectName = dialog.getProjectName();
        projectPath = dialog.getProjectPath();

        MainGUIWindow window;
        window.setWindowTitle("Ostival Desktop");
        window.showMaximized();

        qDebug() << projectPath;

        return app.exec();
    }

    return 0;
}