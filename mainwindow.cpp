#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    if(!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалость открыть бд");
        return;
    }
    //создаю таблицы
    QSqlQuery query;
    query.exec("CREATE TABLE People (id INTEGER PRIMARY KEY AUTOINCREMENT, fio TEXT, weight REAL, departament TEXT)");
    query.exec("CREATE TABLE Departaments (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, rotation INTEGER)");
    query.exec("CREATE TABLE Quadrants (id INTEGER PRIMARY KEY AUTOINCREMENT, x REAL, y REAL, width REAL, height REAL)");
    query.exec("CREATE TABLE Objects (id INTEGER PRIMARY KEY AUTOINCREMENT, x REAL, y REAL, height REAL, width REAL, quadrant INTEGER, color TEXT)");



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

    repaint();
//    ui->lineEdit_quadrantX->setValidator(validator_int);
//    ui->lineEdit_quadrantY->setValidator(validator_int);

//    ui->lineEdit_manWeight->setValidator(validator_double);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p;
    int x0 = ui->label_5->x(), y0 = ui->label_5->y(), xn = ui->label_5->width() + x0,yn = y0 + ui->label_5->height();
    p.begin(this);
    p.setBrush(Qt::white);
    p.drawRect(x0,y0,xn,yn);
    p.drawLine(x0,y0,xn,yn);
    p.end();
}

// Получение пути к файлам
void MainWindow::on_pushButton_load_clicked()
{
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


/*void MainWindow::on_pushButton_add_clicked()
{
        QString filename = "data.csv";
        QFile file(filename);

        if(!file.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
            return;
        }
        QTextStream out(&file);


        //сохранение данных из lineedit в csv
        out << ui->lineEdit_manFio->text() << ","
        << ui->lineEdit_manWeight->text() << ","
        << ui->lineEdit_manSection->text() << ","
        << ui->lineEdit_sectionName->text() << ","
        << ui->lineEdit_sectionRenew->text() << ","
        << ui->lineEdit_quadrantX->text() << ","
        << ui->lineEdit_quadrantY->text() << ","
        << ui->lineEdit_quadrantWidth->text() << ","
        << ui->lineEdit_quadrantHeight->text() << ","
        << ui->lineEdit_objectX->text() << ","
        << ui->lineEdit_objectY->text() << ","
        << ui->lineEdit_objectHeight->text() << ","
        << ui->lineEdit_objectWidth->text() << ","
        << ui->lineEdit_objectCololr->text() << ","
        << ui->lineEdit_objectQuadrant->text() << "\n";


        file.close();
        QMessageBox::information(this, "успех", "данные успешно сохранены");
}*/


void MainWindow::on_pushButton_add_clicked()
{
    QSqlQuery query;
    //запросы для вставки в таблицу people
    query.prepare("INSERT INTO People (fio, weight, departament) VALUES (:fio, :weight, :departament)");
    query.bindValue(":fio", ui->lineEdit_manFio->text());
    query.bindValue(":weight", ui->lineEdit_manWeight->text().toDouble());
    query.bindValue(":departament", ui->lineEdit_manSection->text());

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранть данные" + query.lastError().text());
        return;


}     //для второй
    query.prepare("INSERT INTO Departaments (name, rotation) VALUES (:name, :rotation)");

    query.bindValue(":name", ui->lineEdit_sectionName->text());
    query.bindValue(":rotation", ui->lineEdit_sectionRenew->text());

    if(!query.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранть данные" + query.lastError().text());
        return;
    }



    //для третей
    query.prepare("INSERT INTO Quadrants (x, y, width, height) VALUES (:x, :y, :width, :height)");

    query.bindValue(":x", ui->lineEdit_quadrantX->text().toDouble());
    query.bindValue(":y", ui->lineEdit_quadrantY->text().toDouble());
    query.bindValue(":width", ui->lineEdit_quadrantWidth->text().toDouble());
    query.bindValue(":height", ui->lineEdit_quadrantHeight->text().toDouble());


     if (!query.exec()) {

         QMessageBox::warning(this, "Ошибка", "Не удалось сохранить данные в таблицу 'Quadrants': " + query.lastError().text());

         return; // Прерываем выполнение, если произошла ошибка

     }
     // Запросы для вставки в таблицу Objects

        query.prepare("INSERT INTO Objects (x, y, height, width, quadrant, color) VALUES (:x, :y, :height, :width, :quadrant, :color)");

        query.bindValue(":x", ui->lineEdit_objectX->text().toDouble());
        query.bindValue(":y", ui->lineEdit_objectY->text().toDouble());
        query.bindValue(":height", ui->lineEdit_objectHeight->text().toDouble());
        query.bindValue(":width", ui->lineEdit_objectWidth->text().toDouble());
        query.bindValue(":quadrant", ui->lineEdit_objectQuadrant->text().toInt());
        query.bindValue(":color", ui->lineEdit_objectCololr->text());


        if (!query.exec()) {

            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить данные в таблицу 'Objects': " + query.lastError().text());

            return; // Прерываем выполнение, если произошла ошибка

        }




}



