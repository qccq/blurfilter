/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: ef
 *
 * Created on July 24, 2016, 5:30 PM
 */

#include <QApplication>
#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QString>
#include <QStringList>
#include <QDebug>

#include <blurfilterMainWindow.h>

void setCLIparams(QApplication& App) {

    //http://www.ics.com/blog/whats-new-qt-52-qcommandlineparser
    
    QCoreApplication::setApplicationName("blurfilter");
    QCoreApplication::setApplicationVersion("a0.1");
    
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "Filter to move/delete blurred pictures"));

    // Standard -h / --help options.
    parser.addHelpOption();

    // Standard -v / --version options.
    parser.addVersionOption();

    // Accepts a single filename argument.
    parser.addPositionalArgument("search path", QCoreApplication::translate("main", "root folder to search pictures"));
    
    // -r / --recursive.
    QCommandLineOption recursiveOption(QStringList() << "r" << "recursive", QCoreApplication::translate("main", "recursive search."));
    parser.addOption(recursiveOption);

    parser.process(App);
    
    const QStringList args = parser.positionalArguments();

    // Check that one and only one filename option was specified.
    if (args.size() != 1) {
        fprintf(stderr, "%s\n", qPrintable(QCoreApplication::translate("main", "Error: Must specify one filename argument.")));
        parser.showHelp(1);
    }

    /*
    // Check that format is a number between 1 and 4.
    int format = parser.value(formatOption).toInt();
    if (format < 1 || format > 4) {
        fprintf(stderr, "%s\n", qPrintable(QCoreApplication::translate("main", "Error: Invalid format argument. Must be 1, 2, 3, or 4.")));
        parser.showHelp(1);
    }
    
     * // Get address option. TODO: Could add checking here that address is a valid number in the correct range.
    int address = parser.value(addressOption).toInt();
     
    */
}


int main(int argc, char *argv[]) 

{
   
    //http://stackoverflow.com/questions/23844867/qt-application-with-optional-gui
    //http://www.qtcentre.org/threads/38171-Both-a-command-line-and-GUI-application-at-the-same-time

    //http://stackoverflow.com/questions/23844867/qt-application-with-optional-gui
    
    //https://www.youtube.com/watch?v=c-dsWmG9dps
    //Creating Qt GUI application using Netbeans IDE and Ubuntu
    
    QApplication app(argc, argv);
    
    blurfilterMainWindow w;
    
    bool CLIMode = false;
    
    if(CLIMode)
    {
        setCLIparams(app); 
        //start some non gui functions
    }
    else
    {
        w.show();
    }
    
    //fuck you

    return app.exec();
}
