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
#include "ProjectFileHandler.h"
#include "CentralLogger.h"

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
    ProjectFileHandler project_file;
    if(TempFiles::tempFileExists()){                            // If temp file exists, it means there is a history of the project. Check history and 
        qDebug() << "temp file exists\n";
        TempFiles::readTempFile(projectName, projectPath);      // Reads last project name and path
    } else {                                                    // It there is not temp file, it means no history, and create one.
        InitialDialog dialog;                                   //Initial dialog box is added so that user can choose project path and project name.

        if (dialog.exec() == QDialog::Accepted) {
            projectName = dialog.getProjectName();                      //Project path is the main directory for the project.
            projectPath = dialog.getProjectPath();                      //Project name is the identifier for the project.
            TempFiles::createTempFile(projectName,projectPath);         //Create temp file
        } else {
            qDebug() << "Cancelled Pressed\n";
            return 0;
        }
    }

    if(project_file.checkFile()){
        projectFile = projectPath + "/" + projectName + "/" + projectName + ".ostival";
        qDebug() << "Project File Exists\n";
    } else {
        qDebug() << "Project File does not Exists, maybe someone deleted the file\n";
        InitialDialog dialog;                                   //Initial dialog box is added so that user can choose project path and project name.
        if (dialog.exec() == QDialog::Accepted) {
            projectName = dialog.getProjectName();                      //Project path is the main directory for the project.
            projectPath = dialog.getProjectPath();                      //Project name is the identifier for the project.
            TempFiles::createTempFile(projectName,projectPath);         //This needs to be update with -> update temp file with latest file path and name
            project_file.createInitialfile();                           //Create Project Initial file.
        } else {
            qDebug() << "Cancelled Pressed\n";
            return 0;
        }
    }

    // We got project path and project name. Good to start the GUI.
    MainGUIWindow window;

    // Init logger
    QString log_file_path = projectPath + "/" + projectName + "/all_log_files/mainlog.txt";
    if (!CentralLogger::initialize(log_file_path)) {
        qDebug() << "Unable to create log file\n";
        qDebug() << log_file_path;
    }

    window.setWindowTitle("Ostival Desktop");
    window.showMaximized();

    return app.exec();
}