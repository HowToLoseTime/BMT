#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::updateButtonState);

    connect(ui->lineEdit_manSection, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_manFio, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_manSection, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_manWeight, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);

    connect(ui->lineEdit_sectionName, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_sectionRenew, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);

    connect(ui->lineEdit_quadrantHeight, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_quadrantWidth, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_quadrantX, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_quadrantY, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);

    connect(ui->lineEdit_objectHeight, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_objectWidth, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_objectX, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_objectY, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_objectQuadrant, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);
    connect(ui->lineEdit_objectCololr, &QLineEdit::textChanged, this, &MainWindow::updateButtonState);

    validator_int = new QIntValidator(-100, 100, this);
    validator_double = new QDoubleValidator(-1, 1, 2, this);
    validator_double->setNotation(QDoubleValidator::StandardNotation);

//    ui->lineEdit_quadrantX->setValidator(validator_int);
//    ui->lineEdit_quadrantY->setValidator(validator_int);

//    ui->lineEdit_manWeight->setValidator(validator_double);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
    ui->graphicsView->setSceneRect(0,0, ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->scale(1,-1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ro_paint()
{
    scene->clear();



    scene->addLine(15, 0, 15 ,ui->graphicsView->height());
    scene->addLine(ui->graphicsView->width(), 15, 0, 15);
    scene->addText("x")->setPos(scene->width()-20, -8);
    QGraphicsTextItem *tt =scene->addText("y");
    tt->setPos(2, scene->height()-40);
    tt->setRotation(180);
    for(auto it : ro_objs){
        QGraphicsRectItem *rect = new QGraphicsRectItem(it.x, it.y, it.w, it.h);
        rect->setBrush(QBrush(it.color));
        scene->addItem(rect);
    }

}

// Получение пути к файлам
void MainWindow::on_pushButton_load_clicked()
{
    ro_paint();
    QString path_file = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Файлы данных (*.csv)");
}

void MainWindow::updateButtonState()
{
    int currentIndex = ui->tabWidget->currentIndex(); // Получаем индекс текущей вкладки
    QString currentTabName = ui->tabWidget->tabText(currentIndex); // Получаем текст текущей вкладки

    bool enabled = true;

    if (currentTabName == "Люди"){
        qDebug() << "Люди";
        if (ui->lineEdit_manFio->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_manSection->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_manWeight->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_manSection->text() == ""){
            enabled = false;
        }
        qDebug() << enabled;
    }
    else if(currentTabName == "Подразделения"){
        if (ui->lineEdit_sectionName->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_sectionRenew->text() == ""){
            enabled = false;
        }
    }
    else if(currentTabName == "Квадранты"){
        if (ui->lineEdit_quadrantX->text() == ""){
                enabled = false;
            }
        else if (ui->lineEdit_quadrantY->text() == ""){
                enabled = false;
            }
        else if (ui->lineEdit_quadrantHeight->text() == ""){
                enabled = false;
            }
        else if (ui->lineEdit_quadrantWidth->text() == ""){
                enabled = false;
            }
    }
    else if(currentTabName == "Объекты"){
        if (ui->lineEdit_objectX->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_objectY->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_objectWidth->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_objectHeight->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_objectQuadrant->text() == ""){
            enabled = false;
        }
        else if (ui->lineEdit_objectCololr->text() == ""){
            enabled = false;
        }
    }

    ui->pushButton_add->setEnabled(enabled);
}

