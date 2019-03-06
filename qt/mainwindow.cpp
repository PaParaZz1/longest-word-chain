#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qtextstream.h"
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
    //todo-create a new window & show help
    cout<<"onclick_help"<<endl;
}

void MainWindow::on_pushButton_run_clicked()
{
    bool para_w = ui->radioButton_w->isChecked();
    bool para_c = ui->radioButton_c->isChecked();
    bool para_h = ui->radioButton_h->isChecked();
    bool para_t = ui->radioButton_t->isChecked();
    bool para_r = ui->radioButton_r->isChecked();
    string content = ui->inputArea->toPlainText().toStdString();
    cout<<content<<endl;
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
