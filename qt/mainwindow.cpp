#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qtextstream.h>
#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_import_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Choose File"),"",tr("text(*.txt)"));
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QString errMsg="error when import file";
        ui->outputArea->setText(errMsg);
        return;
    }
    QTextStream in(&file);
    ui->inputArea->clear();
    ui->inputArea->setText(in.readAll());
    cout<<"onclick_import"<<endl;
}

void MainWindow::on_pushButton_help_clicked()
{
    dialog = new Dialog(this);
    dialog->setModal(false);
    //to-do:helpMsg shows the usage of the gui
    //read from file?
    QString helpMsg="test help";
    dialog->ui->textBrowser->setPlainText(helpMsg);
    dialog->show();
    cout<<"onclick_help"<<endl;
}

void MainWindow::on_pushButton_run_clicked()
{
    bool para_w = ui->radioButton_w->isChecked();
    bool para_c = ui->radioButton_c->isChecked();
    bool para_h = ui->radioButton_h->isChecked();
    bool para_t = ui->radioButton_t->isChecked();
    int para=para_w?1:(para_c?2:(para_h?3:(para_t?4:5)));
    string content = ui->inputArea->toPlainText().toStdString();
    //call corresponding function
    cout<<"onclick_run"<<endl;
}

void MainWindow::on_pushButton_output_clicked()
{
    ui->outputArea->setText("output result");
    //output path
    QFile file("/Users/retr0/Desktop/result.txt");
    if (file.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream out(&file);
        out<<ui->outputArea->toPlainText()<<endl;
        out.flush();
        file.close();
    }
    cout<<"onclick_output"<<endl;
}
