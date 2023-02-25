#include "FileCopy.h"
#include <QFileDialog>
#include <QMessageBox>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

FileCopy::FileCopy(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(this->width(), this->height());
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(chooseShareFile()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(chooseLocalFile()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(copyFile()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(close()));
}

void FileCopy::chooseShareFile() {
	QString filePath = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择共享盘文件"),QString(getenv("HOMEDRIVE"))+QString("\\"),QString::fromLocal8Bit("所有文件(*.*)"));
	if (filePath.isEmpty()) {
		QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("你没有选择文件！"));
	}
	else {
		ui.lineEdit->setText(filePath);
	}
}

void FileCopy::chooseLocalFile() {
	QString fileName;
	if (ui.lineEdit->text().isEmpty()) {
		fileName = QString::fromLocal8Bit(getenv("USERPROFILE")) + QString("\\Desktop");
	}
	else {
		fileName = ui.lineEdit->text().mid(ui.lineEdit->text().lastIndexOf("\\"));
	}
	QString filePath = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存到文件"), fileName, QString::fromLocal8Bit("所有文件(*.*)"));
	if (filePath.isEmpty()) {
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("你没有选择文件！"));
	}
	else {
		ui.lineEdit_2->setText(filePath);
	}
}

void FileCopy::copyFile() {
	if (ui.lineEdit->text().isEmpty() || ui.lineEdit_2->text().isEmpty()) return;
	FILE *srcfile = fopen(ui.lineEdit->text().toLocal8Bit().data(), "rb");
	FILE *destfile = fopen(ui.lineEdit_2->text().toLocal8Bit().data(), "wb");
	if (srcfile == NULL || destfile == NULL) return;
	char buf[1024];
	size_t count;
	while ((count = fread(buf, 1, sizeof(buf), srcfile)) > 0) {
		fwrite(buf, 1, count, destfile);
	}
	fclose(srcfile);
	fclose(destfile);
	ui.lineEdit->setText(QString());
	ui.lineEdit_2->setText(QString());
	QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件复制成功！"));
}

FileCopy::~FileCopy(){}
