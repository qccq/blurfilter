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
#include <QDir>
#include <QDebug>

#include <header/Blurfilter.h>

// Inspiration
// http://www.pyimagesearch.com/2015/09/07/blur-detection-with-opencv/

QString THRESHOLD_DEFAULTVALUE = "100";
QString RENAME_DEFAULTVALUE = "blurry.";

enum ParseResult
{
    ArgumentOk,
    ArgumentError,
};

struct ParseResponse
{
    QDir path;
    QString errormsg;
    QString prefix;
    int threshold;
};

ParseResult checkArgument(const QString& argPath, ParseResponse& res){
    
    QDir path(argPath);
            
    if (! path.exists()) {
        // Path don't exist.
        res.errormsg = QString("Error: Path %1 don't exist.").arg(path.path());
        return ArgumentError;
    }

    if (! path.isReadable()) {
        // Path is not readable.
        res.errormsg = QString("Error: Path %1 is non readable.").arg(path.path());
        return ArgumentError;
    }

    if (path.isRelative()) {
        // Make path absolute if relative.
        path.makeAbsolute();
    }
    
    res.path = path;

    return ArgumentOk;    
}

ParseResult checkRename(const QCommandLineParser& parser, ParseResponse& res) {
    
    // parse prefix value
    QString prefixValue = parser.value("n");
    
    if (prefixValue.contains("/")) {
        // invalid character in prefix
        res.errormsg = QString("Error: Invalid file prefix, can't use / .");
        return ArgumentError;
    }
    
    if (prefixValue.contains("\\0")) {
        // invalid character in prefix
        res.errormsg = QString("Error: Invalid file prefix, can't use \\0 .");
        return ArgumentError;
    }    
    
    res.prefix = prefixValue;

    return ArgumentOk; 
}

ParseResult checkThreshold(const QCommandLineParser& parser, ParseResponse& res) {
    
    // used to check if conversion error occured
    bool ok;
    
    // parse threshold value
    int thresholdValue = parser.value("t").toInt(&ok);

    if (! ok) {
        // error in conversion
        res.errormsg = QString("Error: Invalid value assigned to threshold.");
        return ArgumentError;
    }
    
    if (thresholdValue < 0) {
        // exclude value bellow 0
        res.errormsg = QString("Error: Threshold value must be positive.");
        return ArgumentError;
    }
    
    res.threshold = thresholdValue;
   
    return ArgumentOk;        
}

void setCLIparams(QApplication& app, QCommandLineParser& parser) {
    
    app.setApplicationName("blurfilter");
    app.setApplicationVersion("version: a1.0");
    
    // Application description
    parser.setApplicationDescription(app.translate("main", 
        "On every picture within a destination folder, a filter is applied "
        "to determine the blur level. The filter used return the variation of the Laplacian. "
        "This program is an introduction to the C++ programming language, the OpenCV and Qt library."));
    
    // Standard -h / --help options.
    parser.addHelpOption();

    // Standard -v / --version options.
    parser.addVersionOption();
    
    // -v / --verbose.
    QCommandLineOption verboseOption(QStringList() << "b", app.translate("main", "Verbose output."));
    verboseOption.setDefaultValues(QStringList() << "0");
    parser.addOption(verboseOption);    
    
    // -r / --recursive.
    QCommandLineOption recursiveOption(QStringList() << "r", app.translate("main", "Recursive search."));
    recursiveOption.setDefaultValues(QStringList() << "0");
    parser.addOption(recursiveOption);
    
    // -n / --rename.
    QCommandLineOption renameOption(QStringList() << "n" , app.translate("main", 
        "If set, file below threshold will be renamed with an added <prefix>."),
        app.translate("main", "prefix"), RENAME_DEFAULTVALUE);
    parser.addOption(renameOption);
    
    // -t / --threshold.
    QCommandLineOption thresholdOption(QStringList() << "t" , app.translate("main", 
        "Filter threshold, picture evaluated bellow this value will be flagged as blurry. (default is 100)."),
        app.translate("main", "threshold"), THRESHOLD_DEFAULTVALUE);
    parser.addOption(thresholdOption);

    // Search path source.
    parser.addPositionalArgument("[SOURCE]", app.translate("main", "Source folder to search pictures."));
}

void checkCLIparams(const QApplication& app, QCommandLineParser& parser, Blurfilter& blurfilter) {
    // =========================================================================
    // Check on positional arguments
    // =========================================================================
    
    // Structure to store parsing results
    ParseResponse response;
    
    // Process the actual command line arguments given by the user
    parser.process(app);
    
    // SOURCE is args.at(0)
    const QStringList args = parser.positionalArguments();
    
    // ckeck if arguments were given
    if (args.size() > 0) {
        // Set CLI mode as true
        blurfilter.set_cliFlag(1);
        
        // Check that no more than 1 argument was specified.
        if (args.size() > 1) {
            fprintf(stderr, "%s\n", qPrintable(app.translate("main", 
                "Error: Must specify one filepath argument.")));
            parser.showHelp(1);
        }
        
        // Get source path
        QString sourcePath = args.at(0);

        // Check that the path is valid
        switch (checkArgument(sourcePath, response)) {
            // path valid, assign path to Model
            case ArgumentOk:
                blurfilter.set_sourcePath(response.path);
                break;
            // path invalid, throw error
            case ArgumentError:
                fprintf(stderr, "%s\n", qPrintable(response.errormsg));
                parser.showHelp(1);
        }
    }
    
    // verbose
    if (parser.isSet("b")) {
        blurfilter.set_verboseFlag(1);
    }
        
    // recursive
    if (parser.isSet("r")) {
        blurfilter.set_recursiveFlag(1);
    } 
    
    // rename
    if (parser.isSet("n")) {
        // Check that the rename prefix is valid
        switch (checkRename(parser, response)) {
        // prefix valid, assign value to Model
        case ArgumentOk:
            blurfilter.set_rename(1, response.prefix);
            break;
        // prefix invalid, throw error
        case ArgumentError:
            fprintf(stderr, "%s\n", qPrintable(response.errormsg));
            parser.showHelp(1);
        }
    } 
    
    // threshold
    // Check that the threshold value is valid
    switch (checkThreshold(parser, response)) {
        // threshold valid, assign value to Model
        case ArgumentOk:
            blurfilter.set_threshold(response.threshold);
            break;
        // threshold invalid, throw error
        case ArgumentError:
            fprintf(stderr, "%s\n", qPrintable(response.errormsg));
            parser.showHelp(1);
    }
}

int main(int argc, char *argv[]) {
   
    QApplication app(argc, argv);
    QCommandLineParser parser;    
    
    // Model
    Blurfilter blurfilter;
    
    setCLIparams(app, parser);                  // set parameter used for the CLI
    checkCLIparams(app, parser, blurfilter);    // parse parameters returned by the user
    
    if (blurfilter.isfromCLI())
    {
        // CLI mode, run model
        blurfilter.applyFilter();        
    }
    
    else
    {
        // GUI code goes here
        //w.show();
        //app.exec();
    }

    return 0;
}
