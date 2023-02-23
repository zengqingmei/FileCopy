#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FileCopy.h"

class FileCopy : public QMainWindow
{
    Q_OBJECT

public:
    FileCopy(QWidget *parent = nullptr);
    ~FileCopy();

private:
    Ui::FileCopyClass ui;
};
