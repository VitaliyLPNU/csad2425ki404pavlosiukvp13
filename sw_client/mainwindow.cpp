#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
{
    ui->setupUi(this);

    setupSerialPort();

    // Підключаємо сигнал зчитування даних з порту до слоту
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readFromSerial);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSerialPort() {
    // Налаштування серійного порту
    serial->setPortName("COM3");  // Назва порту може варіюватися, залежно від системи
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Error", "Unable to open the serial port!");
        return;  // Додаємо return, щоб зупинити виконання, якщо порт не відкрився
    }
}

void MainWindow::on_sendButton_clicked()
{
    // Отримання тексту з поля введення
    QString message = ui->inputText->text();

    // Відправка повідомлення на Arduino
    serial->write(message.toUtf8());

    // Виведення повідомлення у поле логів
    ui->logText->append("Send: " + message);
    ui->logText->append("");  // Додаємо новий рядок для відступу
}


void MainWindow::readFromSerial() {
    static QByteArray buffer;

    buffer.append(serial->readAll());

    int endIndex = buffer.indexOf('\n');  // Чекаємо на кінець рядка
    while (endIndex != -1) {
        QString receivedMessage = QString::fromUtf8(buffer.left(endIndex).trimmed());
        ui->logText->append("Received: " + receivedMessage);
        buffer.remove(0, endIndex + 1);
        endIndex = buffer.indexOf('\n');
    }
}

QSerialPort* MainWindow::getSerialPort() const {
    return serial;
}

// mainwindow.cpp

void MainWindow::setInputText(const QString &text) {
    ui->inputText->setText(text);
}

QString MainWindow::getLogText() const {
    return ui->logText->toPlainText();
}

void MainWindow::simulateReceivedMessage(const QString& message) {
    ui->logText->append("Received: " + message);  // Directly append to the log for testing
}


