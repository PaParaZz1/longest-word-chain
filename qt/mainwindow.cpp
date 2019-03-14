#pragma execution_character_set("utf-8")  
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qtextstream.h>
#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
#include "se_word_chain_core.hpp"
#include "se_word_chain.hpp"
#include "se_word_chain_core.cpp"
#include "se_word_chain_utils.hpp"
#include "se_word_chain_utils.cpp"
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
    //cout<<"onclick_import"<<endl;
}

void MainWindow::on_pushButton_help_clicked()
{
    dialog = new Dialog(this);
    dialog->setModal(false);
    //to-do:helpMsg shows the usage of the gui
    QString helpMsg="�������ļ�����ť��.txt���ı���Ϊ����\n����ѡ��ѡ��-wѡ���-cѡ��\n����ѡ�򡿿���ѡ����ĳ����ĸ��ͷ���β��nullΪ��������\n����Ҫ����-rѡ��빴ѡ�����ʻ���\n�����ı����������г��򡿰�ť��ʼ����������\n�������������ť���Խ�����������ļ�\n ";
    dialog->ui->textBrowser->setPlainText(helpMsg);
    dialog->show();
    //cout<<"onclick_help"<<endl;
}

void MainWindow::on_pushButton_run_clicked()
{
    int para=ui->radioButton_w->isChecked()?1:2;
    bool ring=ui->checkBox_loop->isChecked();
    string content = ui->inputArea->toPlainText().toStdString();
	char head, tail;
	if (ui->comboBox_h->currentIndex() == 0) {
		head = '\0';
	}
	else {
		head = 'a' + ui->comboBox_h->currentIndex() - 1;
	}
	if (ui->comboBox_t->currentIndex() == 0) {
		tail = '\0';
	}
	else {
		tail = 'a' + ui->comboBox_t->currentIndex() - 1;
	}
    if(content.size()==0){
        QString errMsg="empty input!";
        ui->outputArea->setPlainText(errMsg);
    }
    else{
        //call corresponding function
		string output;
		LongestWordChainType type;
		se_errcode code;
		QString s = "fin";
		WordChainError  error;
		if (para == 1) {
			type = word_longest;
			code=Calculate(content, output,type,head,tail,ring,error);
		}
		else {
			type = letter_longest;
			code=Calculate(content, output, type, head, tail, ring,error);
		}
		if (code == SE_OK) {
			QString result = QString::fromStdString(output);
			ui->outputArea->setPlainText(result);
		}
		else {
			string result = error.ToString();
			QString error= QString::fromStdString(result);
			ui->outputArea->setPlainText(error);
		}
    }
    //cout<<"onclick_run"<<endl;
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
    //cout<<"onclick_output"<<endl;
}
