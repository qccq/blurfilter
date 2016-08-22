/* 
 * File:   blurfilter.h
 * Author: ef
 *
 * Created on July 29, 2016, 10:50 PM
 */

#ifndef BLURFILTER_H
#define BLURFILTER_H

#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include <QFileInfo>
#include <QtGlobal>
#include <QList>
#include <QDebug>

#include <header/Pictures.h>

#include <iostream>
#include <algorithm>



class Blurfilter {

public:
    Blurfilter();
    Blurfilter(Blurfilter const& orig);
    
    void set_sourcePath(const QDir &source);
    void set_threshold(int threshold);
    void set_cliFlag(bool cli);
    void set_verboseFlag(bool verboseFlag);
    void set_recursiveFlag(bool recursiveFlag);
    void set_rename(bool renameFlag, const QString &prefix);
    
    bool isfromCLI() const;
   
    void applyFilter();
    
    virtual ~Blurfilter();

private:
    QDir sourcePath;
    int filterthreshold;
    QString renamePrefix;           // prefix to add to file with the rename operation
    bool CLI;                       // CLI mode
    bool verbose;                   // verbose mode
    bool recursive;                 // recursive search
    bool rename;                    // rename mode
    int selectedPictures;           // number of pictures below threshold
    int foundFiles;                 // number of file found
    int progress;                   // used to calculate PERCENTCOMPLETE
    float percentcomplete;          // show the completion of all the pictures to process [%]]
    
    QList<QStringList> pathList;    //list of file found in [sourcepath]
    QList<Pictures> pictureList;    //list of Pictures objects
    
    void msg_foundfiles() const;
    void msg_processing() const;
    void msg_results() const;
    void msg_progress(Pictures &picture) const;
    
    void searchPictures();
    void calculateProgress();    
};

#endif /* BLURFILTER_H */

