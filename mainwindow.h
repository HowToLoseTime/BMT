#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QIntValidator>
#include <QDoubleValidator>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QGraphicsRectItem>
#include<QGraphicsView>
#include<QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct ro_obj{
    int id, x, y, w, h, id_quadra;
    QColor color;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ro_paint();
private slots:
    void on_pushButton_load_clicked();
    void updateButtonState();

private:
    QVector<ro_obj> ro_objs;
    Ui::MainWindow *ui;
    QIntValidator *validator_int;
    QDoubleValidator *validator_double;
    QGraphicsScene *scene;


};
#endif // MAINWINDOW_H
