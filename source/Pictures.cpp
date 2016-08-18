/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pictures.cpp
 * Author: ef
 * 
 * Created on August 2, 2016, 12:33 AM
 */

#include "header/Pictures.h"


Pictures::Pictures(QString _filename, QString _path):
    filename(_filename),
    path(_path)
{
    score = calcScore();
    selected = false;
}

Pictures::Pictures(Pictures const& obj):
    filename(obj.filename),
    path(obj.path),
    score(obj.score),
    selected(obj.selected)
{
}

float Pictures::getScore() const{
    return score;
}

QString Pictures::getFilename() const{
    return filename;
}

float Pictures::calcScore() {
    cv::Mat grayscaleImage, lapalce;
    cv::Scalar mean, stddev;
    float var;
    
    //http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html?highlight=imread#imread
    grayscaleImage = cv::imread(path.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
    
    //http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html?highlight=laplacian#cv2.Laplacian
    cv::Laplacian(grayscaleImage, lapalce, CV_64F);
    
    //http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html?highlight=meanstd#meanstddev
    //cv::meanStdDev(lapalce, mean, stddev, cv::Mat() );
    cv::meanStdDev(lapalce, mean, stddev);
        
    //variance = stddev²
    var = stddev.val[0] * stddev.val[0];
    
    return var;
}

void Pictures::printInfo() const {
    QString ljFilename = filename.leftJustified(60, ' ');
    QString rjScore = QString::number(score, 'f', 1).rightJustified(6, ' ');
    std::cout << qPrintable(QString("%1%2").arg(ljFilename, rjScore));
    std::cout << std::endl; 
}

void Pictures::setSelected() {
    selected = true;
}

bool Pictures::isSelected() const {
    return selected;
}

Pictures::~Pictures() {
}

bool operator < (Pictures const &pic1, Pictures const &pic2){
    return pic1.getScore() < pic2.getScore();
}