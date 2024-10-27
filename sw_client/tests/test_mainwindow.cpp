#include <QtTest>
#include "mainwindow.h"
#include <QPushButton>
#include <QSignalSpy>

class TestMainWindow : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();             // Initialization before tests
    void cleanupTestCase();          // Cleanup after tests

    void testSerialPortSetup();      // Test if serial port is correctly set up
    void testSendMessage();          // Test sending a message
    void testReceiveMessage();       // Test receiving a message

private:
    MainWindow* mainWindow;
};

void TestMainWindow::initTestCase() {
    mainWindow = new MainWindow();
}

void TestMainWindow::cleanupTestCase() {
    delete mainWindow;
}

void TestMainWindow::testSerialPortSetup() {
    QSerialPort* serial = mainWindow->getSerialPort();

    QVERIFY(serial != nullptr);                           // Check that serial port is initialized
    QCOMPARE(serial->baudRate(), QSerialPort::Baud9600);  // Verify baud rate
    QCOMPARE(serial->dataBits(), QSerialPort::Data8);     // Verify data bits
    QCOMPARE(serial->parity(), QSerialPort::NoParity);    // Verify parity
    QCOMPARE(serial->stopBits(), QSerialPort::OneStop);   // Verify stop bits
    QCOMPARE(serial->flowControl(), QSerialPort::NoFlowControl);  // Verify flow control
}

void TestMainWindow::testSendMessage() {
    QString testMessage = "Hello Arduino";
    mainWindow->setInputText(testMessage);  // Set input text

    // Find the send button in the UI and simulate a click
    QPushButton* sendButton = mainWindow->findChild<QPushButton*>("sendButton");
    QVERIFY(sendButton != nullptr);  // Ensure the button exists
    QTest::mouseClick(sendButton, Qt::LeftButton);  // Simulate button click

    QString logOutput = mainWindow->getLogText();
    QVERIFY(logOutput.contains("Send: " + testMessage));  // Ensure log shows sent message
}

void TestMainWindow::testReceiveMessage() {
    QString testReceivedMessage = "Arduino Response";

    mainWindow->simulateReceivedMessage(testReceivedMessage);  // Simulate received message

    QString logOutput = mainWindow->getLogText();
    QVERIFY2(logOutput.contains("Received: " + testReceivedMessage), "Log output does not contain the expected received message.");
}

QTEST_MAIN(TestMainWindow)
#include "test_mainwindow.moc"
