#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort* getSerialPort() const;
    void setInputText(const QString &text);     // Set input text for testing
    QString getLogText() const;                 // Get log text for validation
    void simulateReceivedMessage(const QString &message); // Simulate a received message for testing

private slots:
    void on_sendButton_clicked();
    void readFromSerial();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    void setupSerialPort();
};

#endif // MAINWINDOW_H
