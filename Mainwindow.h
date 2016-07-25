/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mainwindow.h
 * Author: ef
 *
 * Created on July 24, 2016, 6:30 PM
 */

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "ui_mainwindow.h"

class mainwindow : public QMainWindow {
    Q_OBJECT
public:
    mainwindow();
    virtual ~mainwindow();
private:
    Ui::mainwindow widget;
};

#endif /* _MAINWINDOW_H */
