#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

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
    void on_pushButton_load_clicked();
    void updateButtonState();

    void on_pushButton_add_clicked();

private:
    Ui::MainWindow *ui;
    QIntValidator *validator_int;
    QDoubleValidator *validator_double;


};
#endif // MAINWINDOW_H
