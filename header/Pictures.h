/* 
 * File:   Pictures.h
 * Author: ef
 *
 * Created on August 2, 2016, 12:33 AM
 */

#ifndef PICTURES_H
#define PICTURES_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QtGlobal>

#include <iostream>


class Pictures {
public:
    Pictures(QString _filename, QString _path);
    Pictures(Pictures const& orig);
    
    float getScore() const;    
    QString getFilename() const;
    
    void setSelected();
    
    bool isSelected() const;
    void printInfo() const;
    void renameFile(QString const& prefix);
  
    virtual ~Pictures();
    
private:

    QString filename;           // filename of the picture
    QString path;               // absolute path of the picture
    float calcScore();          // apply the filter on the picture
    float score;                // result of the Laplacian variation
    bool selected;              // set True if SCORE if bellow a threshold
};

#endif /* PICTURES_H */

// used by std::sort
bool operator < (Pictures const &pic1, Pictures const &pic2);
