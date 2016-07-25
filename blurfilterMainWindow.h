/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   blurfilterMainWindow.h
 * Author: ef
 *
 * Created on 25 juillet 2016, 22:45
 */

#ifndef _BLURFILTERMAINWINDOW_H
#define _BLURFILTERMAINWINDOW_H

#include "ui_blurfilterMainWindow.h"

class blurfilterMainWindow : public QMainWindow {
    Q_OBJECT
public:
    blurfilterMainWindow();
    virtual ~blurfilterMainWindow();
private:
    Ui::blurfilterMainWindow widget;
};

#endif /* _BLURFILTERMAINWINDOW_H */
