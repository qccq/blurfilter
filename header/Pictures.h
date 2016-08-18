/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
#include <QtGlobal>

#include <iostream>


class Pictures {
public:
    Pictures(QString _filename, QString _path);
    Pictures(Pictures const& orig);
    
    float getScore() const;    
    QString getFilename() const;
    void printInfo() const;
    void setSelected();
    bool isSelected() const;
  
    virtual ~Pictures();
    
private:

    QString filename;
    QString path;
    float calcScore();
    float score;
    bool selected;
};

#endif /* PICTURES_H */

bool operator < (Pictures const &pic1, Pictures const &pic2);
