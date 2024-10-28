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


    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readFromSerial);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSerialPort() {

    serial->setPortName("COM3");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Error", "Unable to open the serial port!");
        return;
    }
}

void MainWindow::on_sendButton_clicked()
{

    QString message = ui->inputText->text();


    serial->write(message.toUtf8());


    ui->logText->append("Send: " + message);
    ui->logText->append("");
}


void MainWindow::readFromSerial() {
    static QByteArray buffer;

    buffer.append(serial->readAll());

    int endIndex = buffer.indexOf('\n');
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



void MainWindow::setInputText(const QString &text) {
    ui->inputText->setText(text);
}

QString MainWindow::getLogText() const {
    return ui->logText->toPlainText();
}

void MainWindow::simulateReceivedMessage(const QString& message) {
    ui->logText->append("Received: " + message);
}


