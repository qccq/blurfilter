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
#include <QDir>

#include <header/Blurfilter.h>
#include <qt4/QtCore/qglobal.h>

//#include <blurfilterMainWindow.h>

// Inspiration
// http://www.pyimagesearch.com/2015/09/07/blur-detection-with-opencv/

QString THRESHOLD_DEFAULTVALUE = "100";
//QString DESTINATION_DEFAULTVALUE = "./blurfilter";

float checkThreshold(QCommandLineOption& thresholdOption, QCommandLineParser& parser) {
    
    // default threshold value
    int thresholdValue = thresholdOption.defaultValues().at(0).toInt();        

    bool threshold = parser.isSet(thresholdOption);    

    // Check that the threshold is valid.
    if (threshold) 
    {
        thresholdValue = parser.value(thresholdOption).toFloat();
        // http://doc.qt.io/qt-4.8/qstring.html#toInt
        //  check thresholdValue>= 0
    }
    
    return thresholdValue;        
}

int checkRecursive(QCommandLineOption& recursiveOption, QCommandLineParser& parser) {
    
    // default threshold value
    int recursiveValue = recursiveOption.defaultValues().at(0).toInt();        

    bool threshold = parser.isSet(recursiveOption);    

    // Check that the threshold is valid.
    if (threshold) 
    {
        recursiveValue = parser.value(recursiveOption).toInt();
        // http://doc.qt.io/qt-4.8/qstring.html#toInt
        //  check thresholdValue>= 0
    }
    
    return recursiveValue;        
}

int checkOption(QCommandLineOption& option, QCommandLineParser& parser, bool& CLImode) {
    
    //option value
    int value;

    bool isSet = parser.isSet(option);    

    // Check that the threshold is valid.
    if (isSet) 
    {
        CLImode = 1;
        
        value = parser.value(option).toInt();
        // http://doc.qt.io/qt-4.8/qstring.html#toInt
        //  check thresholdValue>= 0
    }
    else 
    {
        value = option.defaultValues().at(0).toInt();
    }
    
    return value;        
}

QDir checkArgument(const QString argPath){
    
//    QString currentDir = QDir::currentPath();
//    QDir path(currentDir);
    
    QDir path(argPath);
    
//    if (argPath.isEmpty()) {
//        path.setPath(DESTINATION_DEFAULTVALUE);
//    }
//    else {
//        path.setPath(argPath);
//    }
    
    if (path.isRelative()) {
        path.makeAbsolute();
    }
    
    // if exist
    
    // mkdir
    
    return path;    
}

void setCLIparams(QApplication& app, QCommandLineParser& parser, Blurfilter& blurfilter) {

    //http://www.ics.com/blog/whats-new-qt-52-qcommandlineparser
    
    app.setApplicationName("blurfilter");
    app.setApplicationVersion("version: a1.0");
    
    // Application description
    parser.setApplicationDescription(app.translate("main", "On every picture within a destination folder, a filter is applied to determine the blur level. "
            "Picture bellow the threshold will be move to a destination folder."));

    // Standard -h / --help options.
    parser.addHelpOption();

    // Standard -v / --version options.
    parser.addVersionOption();
    
    // -v / --verbose.
    QCommandLineOption verboseOption(QStringList() << "b" , app.translate("main", "Verbose output."));
    parser.addOption(verboseOption);
    verboseOption.setDefaultValues(QStringList() << "0");
    
    // -r / --recursive.
    QCommandLineOption recursiveOption(QStringList() << "r" , app.translate("main", "Recursive search."));
    parser.addOption(recursiveOption);
    recursiveOption.setDefaultValues(QStringList() << "0");
    
    // -t / --threshold.
    /*QString thresholdDescription = "Filter threshold, picture evaluated bellow this "
            "value will be moved to the destination folder. Default to 100.";*/
    QCommandLineOption thresholdOption(QStringList() << "t" , app.translate("main", "Filter threshold, picture evaluated bellow this "
            "value will be moved to the destination folder. Default to 100."));
    parser.addOption(thresholdOption);
    thresholdOption.setDefaultValues(QStringList() << THRESHOLD_DEFAULTVALUE);
    
    // Search path source.
    parser.addPositionalArgument("[SOURCE]", app.translate("main", "Source folder to search pictures."));
    
    // Move destination.
//    parser.addPositionalArgument("[DESTINATION]", app.translate("main", "Destination folder to move blurred pictures. Default to ./blurfilter/"));
    
    // =========================================================================
    // Check on positional arguments
    // =========================================================================
    
    // Process the actual command line arguments given by the user
    parser.process(app);
    
    // False: GUI mode
    // True: CLI mode activated
    bool CLImode = 0;
    
    // source is args.at(0), destination is args.at(1)
    QStringList args = parser.positionalArguments();
    
    // ckeck if arguments was given
    if (args.size() > 0) {
        CLImode = 1;
    }
    // if not, set default path
    else {
        // default source path
        args.append(QDir::homePath());
        
        // default destination path
//        args.append(DESTINATION_DEFAULTVALUE);
    }
    
    // verbose
    if (parser.isSet(verboseOption)) {
        blurfilter.set_verboseFlag(1);
    }
        
    // recursive
    if (parser.isSet(recursiveOption)) {
        blurfilter.set_recursiveFlag(1);
    } 
    
    // threshold
    float thresholdValue = checkOption(thresholdOption, parser, CLImode);
    blurfilter.set_threshold(thresholdValue);
  
    if (CLImode) {
        // Check that no more than 2 arguments was specified.
        if (args.size() > 2) {
            fprintf(stderr, "%s\n", qPrintable(app.translate("main", "Error: More than 2 arguments was specified.")));
            parser.showHelp(1);
        }

        // Apply default destination path if not specified.
//        if (args.size() == 1) {
//            args.append(DESTINATION_DEFAULTVALUE);
//        }
    }
    
    // source path
    QDir sourcePath = checkArgument(args.at(0));
    blurfilter.set_sourcePath(sourcePath);
    
    // destination path
//    QDir destinationPath = checkArgument(args.at(1));
//    blurfilter.set_destinationPath(destinationPath);
            
    blurfilter.set_cliFlag(CLImode);
}

int main(int argc, char *argv[]) {
   
    //http://stackoverflow.com/questions/23844867/qt-application-with-optional-gui
    //http://www.qtcentre.org/threads/38171-Both-a-command-line-and-GUI-application-at-the-same-time

    //http://stackoverflow.com/questions/23844867/qt-application-with-optional-gui
    
    //https://www.youtube.com/watch?v=c-dsWmG9dps
    //Creating Qt GUI application using Netbeans IDE and Ubuntu
    
    // Isolate the non blurred part of foucsed image
    //http://dsp.stackexchange.com/questions/22355/isolate-the-non-blurred-part-of-foucsed-image
    
    QApplication app(argc, argv);
    QCommandLineParser parser;    
    Blurfilter blurfilter;
    
    setCLIparams(app, parser, blurfilter);

    
    if (blurfilter.isfromCLI())
    {
        blurfilter.applyFilter();
        
    }
    else
    {
        //w.show();
        
        
        //app.exec();
    }
    
    //fuck you
    app.quit();

    return 0;
}
