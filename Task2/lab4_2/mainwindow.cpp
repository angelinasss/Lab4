#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Cstring.cpp"

char first[] = "1234567890";
char second[] = "1987654320";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_strcmp_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strcmp: " + QString::number(strcmp_(first, second)));
}


void MainWindow::on_pushButton_strcat_clicked()
{
    char first[] = "1234567890";
    char second[] = "1987654320";
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strcat: ");
    strcat_(first, second);
    ui->textBrowser->append(first);
}


void MainWindow::on_pushButton_strerror_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strerror(13): ");
    ui->textBrowser->append(strerror_(13));
}


void MainWindow::on_pushButton_memset_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("memset(the first five - 9): ");
    ui->textBrowser->append((char*)memset_(first, '9', 5));
}


void MainWindow::on_pushButton_strcoll_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strcoll: ");
    ui->textBrowser->append(QString::number(strcoll_(first, second)));
}


void MainWindow::on_pushButton_strxfrm_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strxfrm(5): ");
    ui->textBrowser->append(QString::number(strxfrm_(first, second, 5)));
}


void MainWindow::on_pushButton_strncmp_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strncmp(4): " + QString::number(strncmp_(first, second, 4)));
}


void MainWindow::on_pushButton_strtok_clicked()
{
    char first[] = "1:2:3/4:5/6/7:8/90";
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strtok(:): ");
    ui->textBrowser->append(strtok_(first, ':'));
}


void MainWindow::on_pushButton_memcmp_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("memcmp(3): ");
    ui->textBrowser->append(QString::number(memcmp_(first, second, 3)));
}


void MainWindow::on_pushButton_strcpy_2_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strcpy: ");
    ui->textBrowser->append(strcpy_(first, second));
}


void MainWindow::on_pushButton_strlen_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strlen(first): ");
    ui->textBrowser->append(QString::number(strlen_(first)));
}


void MainWindow::on_pushButton_strncpy_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strncpy(7): ");
    ui->textBrowser->append(strncpy_(first, second, 7));
}


void MainWindow::on_pushButton_memcpy_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("memcpy(4): ");
    ui->textBrowser->append((char*)memcpy_(first, second, 4));
}


void MainWindow::on_pushButton_memmove_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("memmove(6): ");
    ui->textBrowser->append((char*)memmove_(first, second, 6));
}


void MainWindow::on_pushButton_strncat_clicked()
{
    char first[] = "1234567890";
    char second[] = "1987654320";
    ui->textBrowser->clear();
    ui->textBrowser->append(first);
    ui->textBrowser->append(second);
    ui->textBrowser->append("strncat(3): ");
    strncat_(first, second, 3);
    ui->textBrowser->append(first);
}

