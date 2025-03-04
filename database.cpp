#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

class Database {
public:
    Database(const QString &filePath) : m_filePath(filePath) {
        // Создаем файл, если он не существует
        QFile file(m_filePath);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
        }
    }

    void addEntry(const QString &name, int age, const QString &email) {
        QFile file(m_filePath);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << name << "," << age << "," << email << "\n";
            file.close();
        } else {
            qDebug() << "Не удалось открыть файл для добавления записи:" << file.errorString();
        }
    }

    void readEntries() {
        QFile file(m_filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                qDebug() << line; // Выводим каждую строку в консоль
            }
            file.close();
        } else {
            qDebug() << "Не удалось открыть файл для чтения:" << file.errorString();
        }
    }

private:
    QString m_filePath;
};
