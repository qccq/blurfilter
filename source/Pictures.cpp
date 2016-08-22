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
    
    // http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html?highlight=imread#imread
    // open picture file, converted to grayscale
    // TODO: add error detection
    grayscaleImage = cv::imread(path.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
    
    // http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html?highlight=laplacian#cv2.Laplacian
    // apply the Laplacian using the following kernel:
    //                                                  [0  1  0]
    //                                                  [1 -4  1]
    //                                                  [0  1  0]
    cv::Laplacian(grayscaleImage, lapalce, CV_64F);
    
    // http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html?highlight=meanstd#meanstddev
    // calc the standard deviation of the Laplacian
    cv::meanStdDev(lapalce, mean, stddev);
        
    // the variance is equal to -> stddev²
    var = stddev.val[0] * stddev.val[0];
    
    return var;
}

void Pictures::renameFile(const QString& prefix) {
    
    QFile file(path);                       // used for rename
    QFileInfo fileInfo(file);               // used to get path of file
    
    // ex: /home/user/pic/mypicture.jpg
    QString basePath = fileInfo.path();     // return: /home/user/pic/
    
    // new filename
    QString newName = QString("%1%2").arg(prefix, filename);
    
    // add new filename to basePath
    QString newFileNameAbsolutePath = QString("%1/%2").arg(basePath, newName);
    
    // used to detect if rename was successful.
    bool succes;
    
    // rename operation
    succes = QFile::rename(path, newFileNameAbsolutePath);
    
    if (! succes) {
        // rename failed, possible cause:
        // newname already exist, the file is open, file is not writable
        // TODO: add error detection
        qDebug() << QString("Rename of %1 failed").arg(filename);
    }
    
    return;
}

void Pictures::printInfo() const {
    QString ljFilename = filename.leftJustified(60, ' ');
    QString rjScore = QString::number(score, 'f', 1).rightJustified(6, ' ');
    
    std::cout << qPrintable(QString("%1%2").arg(ljFilename, rjScore)) << std::endl;
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