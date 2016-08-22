/* 
 * File:   Blurfilter.cpp
 * Author: ef
 * 
 * Created on July 29, 2016, 10:50 PM
 */

#include "header/Blurfilter.h"


// constructor
Blurfilter::Blurfilter():
    CLI(0),
    verbose(0),    
    recursive(0),
    rename(0)
{    
}

Blurfilter::Blurfilter(Blurfilter const& obj):
    CLI(obj.CLI),
    verbose(obj.verbose),
    recursive(obj.recursive),
    rename(obj.rename)
{
}

void Blurfilter::set_sourcePath(const QDir &source) {
    sourcePath = source;
}

void Blurfilter::set_threshold(int threshold) {
    filterthreshold = threshold;
}

void Blurfilter::set_cliFlag(bool cli) {
    CLI = cli;
}

void Blurfilter::set_verboseFlag(bool verboseFlag) {
    verbose = verboseFlag;    
}

void Blurfilter::set_recursiveFlag(bool recursiveFlag) {
    recursive = recursiveFlag;    
}

void Blurfilter::set_rename(bool renameFlag, const QString &prefix) {
    rename = renameFlag;
    renamePrefix = prefix;
}

bool Blurfilter::isfromCLI() const {
    return CLI;
}

void Blurfilter::applyFilter() {

    progress = 0;                   // reset progress
    selectedPictures = 0;           // reset number of selected Pictures    
    
    qDebug() << QString("SOURCE PATH: %1").arg(sourcePath.absolutePath());
    qDebug() << QString("VERBOSE: %1").arg(verbose);
    qDebug() << QString("RECURSIVE: %1").arg(recursive);
    qDebug() << QString("RENAME : %1").arg(rename);
    qDebug() << QString("RENAME PREFIX: %1").arg(renamePrefix);
    qDebug() << QString("THRESHOLD: %1").arg(QString::number(filterthreshold));
    
    // search for picture files in SOURCEPATH
    searchPictures();
    
    if (CLI) {
        msg_foundfiles();
        msg_processing();
    }
    
    // create picture objects for each file found
    foreach (QStringList file, pathList){        
        
        // increment progress counter
        calculateProgress();
        
        Pictures pic(file.at(0), file.at(1));
        
        if (pic.getScore() <= filterthreshold) {
            // flag picture below threshold
            pic.setSelected();
            selectedPictures++;
        }
        
        pictureList.append(pic);
        
        if (verbose){
            // print progress bar
            msg_progress(pic);
        }
    }
    
    // sort pictureList by score
    std::sort(pictureList.begin(), pictureList.end());
    
    if (CLI){        
        msg_results();
        
        foreach (Pictures pic, pictureList) {
            // only print result from selected picture
            if (pic.isSelected()) {
                pic.printInfo();
            }
            // exit loop at first Picture non selected
            // pictureList must be sorted
            else {
                break;
            }
        }
    }
    
    if (rename) {
        
        foreach (Pictures pic, pictureList) {
            if (pic.isSelected()) {
                pic.renameFile(renamePrefix);
            }
        }
    }
    
}

void Blurfilter::searchPictures() {
    
    // search filter
    // file type compatible with openCV imread())
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg";
    nameFilters << "*.bmp";
    nameFilters << "*.png";
    
    // apply filter to QDirIterator
    QDirIterator::IteratorFlags flags;
    
    if (recursive) {
        // QDirIterator::Subdirectories
        flags |= QDirIterator::Subdirectories;
    }
    else {
        // QDirIterator::NoIteratorFlags
        flags |= QDirIterator::NoIteratorFlags;
    }
    
    // iterator used to navigate to each file in SOURCEPATH
    QDirIterator fileIt(sourcePath.absolutePath(), nameFilters, QDir::Files, flags);
        
    while (fileIt.hasNext())
    {
        QString filepath = fileIt.next();       // absolute path
        QString filename = fileIt.fileName();   // filename
        
        QDir file(filepath);
        
        // check if file is readable
        if (file.isReadable()){
            QStringList path;
            path << filename << filepath;
            
            pathList << path;                   // add path to pathlist
        }
    }
    
    foundFiles = pathList.count();
}

void Blurfilter::calculateProgress() {
    
    progress++;
    
    percentcomplete = float(progress) / float(foundFiles);
    
    return;
}

void Blurfilter::msg_results() const {
    QString s = "";
    
    if (selectedPictures > 1){
        s = "s";
    }
    
    std::cout << qPrintable(QString("Found %1 picture%2 below threshold").arg(QString::number(selectedPictures), s));
    std::cout << std::endl; 
}

void Blurfilter::msg_foundfiles() const {

    QString s = "";
    
    if (foundFiles > 1){
        s = "s";
    }
    
    std::cout << qPrintable(QString("Found %1 picture%2").arg(QString::number(foundFiles), s));
    std::cout << std::endl; 
}

void Blurfilter::msg_processing() const {
    std::cout << qPrintable(QString("Processing ..."));
    std::cout << std::endl; 
}

void Blurfilter::msg_progress(Pictures &picture) const {
    
    int barLength = 38;
    QString bar;
    QString empty;
    QString path = picture.getFilename().leftJustified(36, ' ');
    
    int barNumber = int(percentcomplete * barLength);
    
    bar = bar.fill('|', barNumber);
    empty = empty.fill(' ', (barLength - barNumber));
    
    std::cout << qPrintable(QString("\r[%1%2] %3").arg(bar, empty, path)) << std::flush;
    
    // add newline on last iteration
    if (progress == foundFiles) {
        std::cout << std::endl;
    }
}

Blurfilter::~Blurfilter() {
}
