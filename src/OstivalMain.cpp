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
    Ensure temp file exsists or not. If not, create one using the dialog so that we don't have to enter project name again and again.
    */
    if(TempFiles::tempFileExists()){

        TempFiles::readTempFile(projectName, projectPath);

        /*
        GUI Window start
        */
        MainGUIWindow window;

        window.setWindowTitle("Ostival Desktop");
        window.showMaximized();

        qDebug() << projectPath;

        return app.exec();
    } else {
        /*
        Initial dialog box is added so that user can choose project path and project name.
        */
        InitialDialog dialog;

        if (dialog.exec() == QDialog::Accepted)
        {
            /*
            Project path is the main directory for the project.
            Project name is the identifier for the project.
            */
            projectName = dialog.getProjectName();
            projectPath = dialog.getProjectPath();

            TempFiles::createTempFile(projectName,projectPath);

            /*
            GUI Window start
            */
            MainGUIWindow window;

            window.setWindowTitle("Ostival Desktop");
            window.showMaximized();

            qDebug() << projectPath;

            return app.exec();
        }
    }

    return 0;
}