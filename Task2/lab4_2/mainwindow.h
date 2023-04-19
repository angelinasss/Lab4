#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_strcmp_clicked();

    void on_pushButton_strcat_clicked();

    void on_pushButton_strerror_clicked();

    void on_pushButton_memset_clicked();

    void on_pushButton_strcoll_clicked();

    void on_pushButton_strxfrm_clicked();

    void on_pushButton_strncmp_clicked();

    void on_pushButton_strtok_clicked();

    void on_pushButton_memcmp_clicked();

    void on_pushButton_strcpy_2_clicked();

    void on_pushButton_strlen_clicked();

    void on_pushButton_strncpy_clicked();

    void on_pushButton_memcpy_clicked();

    void on_pushButton_memmove_clicked();

    void on_pushButton_strncat_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
