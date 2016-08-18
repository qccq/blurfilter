/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
    recursive(0)
{    
}

Blurfilter::Blurfilter(Blurfilter const& obj):
    CLI(obj.CLI),
    verbose(obj.verbose),
    recursive(obj.recursive)
{
}

void Blurfilter::set_sourcePath(QDir source) {
    sourcePath = source;
}

void Blurfilter::set_threshold(float threshold) {
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

bool Blurfilter::isfromCLI() const {
    return CLI;
}

void Blurfilter::applyFilter() {

    progress = 0;
    selectedPictures = 0;    

    print_status();
    
    searchPictures();
    
    if (CLI) {
        msg_foundfiles();
        msg_processing();
    }
    
    // create picture objects for each file found
    foreach (QStringList file, pathList){        
        
        calculateProgress();
        
        Pictures pic(file.at(0), file.at(1));
        
        if (pic.getScore() <= filterthreshold) {
            pic.setSelected();
            selectedPictures++;
        }
        
        pictureList.append(pic);
        
        if (verbose){
            msg_progress(pic);
        }
    }
    
    // sort pictureList by score
    std::sort(pictureList.begin(), pictureList.end());
    
    if (CLI){        
        msg_results();
        
        foreach (Pictures pic, pictureList) {
            if (pic.isSelected()) {
                pic.printInfo();
            }
            else {
                break;
            }
        }
    }
    
//    printResults();
//    moveToDestination();
    
}

void Blurfilter::searchPictures() {
    
    // search filter
    // file type compatible with openCV imread())
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg";
    nameFilters << "*.bmp";
    nameFilters << "*.png";
    
    QDirIterator::IteratorFlags flags;
    
    if (recursive) {
        // QDirIterator::Subdirectories
        flags |= QDirIterator::Subdirectories;
    }
    else {
        // QDirIterator::NoIteratorFlags
        flags |= QDirIterator::NoIteratorFlags;
    }
    
    QDirIterator fileIt(sourcePath.absolutePath(), nameFilters, QDir::Files, flags);
    
    
    while (fileIt.hasNext())
    {
        QString filepath = fileIt.next();
        QString filename = fileIt.fileName();
        
        QDir file(filepath);
        
        // check if file is readable
        if (file.isReadable()){
            QStringList path;
            path << filename << filepath;
            
            pathList << path;
        }
    }
    
    foundFiles = pathList.count();
}

void Blurfilter::moveToDestination() {

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

void Blurfilter::print_status() const {

    std::cout << std::endl;
    std::cout << qPrintable(QString("SOURCE PATH: %1").arg(sourcePath.absolutePath())) << std::endl;
    std::cout << qPrintable(QString("VERBOSE: %1").arg(verbose)) << std::endl;
    std::cout << qPrintable(QString("RECURSIVE: %1").arg(recursive)) << std::endl;
    std::cout << qPrintable(QString("THRESHOLD: %1").arg(QString::number(filterthreshold))) << std::endl;
    std::cout << std::endl;
}

Blurfilter::~Blurfilter() {
}
