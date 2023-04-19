#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parser.h"
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QPlainTextEdit>
using namespace std;
QString path;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    QString code = ui->textEdit->toPlainText();
    vector<string> rows;
    QString row;
    for (int i = 0; i < code.size(); i++) {
        row.push_back(code[i]);
        if (code[i] == '\n') {
            rows.push_back(row.toStdString());
            row.clear();
        }
    }
    Parser prs(rows);
    vector<pair<string, pair<size_t, size_t>>> res = prs.get_variables();
    ui->textBrowser->append("Count of variables: " + QString::number(res.size()));
    for (auto &type: res) {
        ui->textBrowser->append(QString::fromStdString(type.first) + "\t[" + QString::number(type.second.first) + ", " + QString::number(type.second.second) + "]");
    }

    ui->textBrowser->append("\nCount of classes: " + QString::number(prs.get_classes().size()));
    vector<string> res3 = prs.get_classes();
    for (auto &type: res3) {
        ui->textBrowser->append(QString::fromStdString(type));
    }

    res3 = prs.get_structs();
    ui->textBrowser->append("\nCount of structs: " + QString::number(prs.get_structs().size()));
    for (auto &type: res3) {
        ui->textBrowser->append(QString::fromStdString(type));
    }

    res3 = prs.get_arrays();
    ui->textBrowser->append("\nCount of arrays: " + QString::number(res3.size()));
    for (auto &type: res3) {
        ui->textBrowser->append(QString::fromStdString(type));
    }

    ui->textBrowser->append("\nCount of function prototypes: " + QString::number(prs.get_prototypes().size()));
    const vector<pair<pair<string, string>, pair<size_t, size_t>>> res2 = prs.get_prototypes();
    for (auto &type : res2) {
        ui->textBrowser->append(QString::fromStdString(type.first.first));
    }

    pair<vector<pair<string, pair<size_t, size_t>>>, size_t> pr = prs.overloadedCount();
    ui->textBrowser->append("\nCount of overloaded functions: " + QString::number(pr.second));
    for (const auto& p : pr.first) {
        ui->textBrowser->append(QString::fromStdString(p.first) + "\t[" + QString::number(p.second.first) + ", " + QString::number(p.second.first) + "]");
    }

    vector<pair<string, pair<size_t, size_t>>> ch = prs.variablesChanges();
    ui->textBrowser->append("\nCount of changing variables: ");
    for (auto &change: ch) {
        ui->textBrowser->append(QString::fromStdString(change.first) + "\t[" + QString::number(change.second.first) + ", " + QString::number(change.second.second) + "]");
    }

    ui->textBrowser->append("\nCount of branches: ");
    prs.findBranches();
    vector<int> r = prs.get_branchesCount();
    for (size_t i = 0; i < rows.size(); i++) {
        if (r[i]) {
            ui->textBrowser->append(QString::fromStdString(rows[i].substr(0, rows[i].size() - 1)) + "\tDepth: " + QString::number(static_cast<int>(log(r[i] * 2) / log(2))));
        }
    }

    vector<pair<string, pair<size_t, size_t>>> er = prs.logicErrors();
    if (er.empty()) {
        ui->textBrowser->append("\nCount of logic errors: 0");
    }
    else {
        ui->textBrowser->append("\nCount of logic errors: ");
    }
    for (auto &error: er) {
        ui->textBrowser->append(QString::fromStdString(error.first) + "\t[" + QString::number(error.second.first) + ", " + QString::number(error.second.second) + "]");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
    path = QFileDialog::getOpenFileName(this, "Choose a document", "C:/", "*.cpp *.h");
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream File(&file);
    ui->textEdit->setPlainText(File.readAll());
    file.close();
}
