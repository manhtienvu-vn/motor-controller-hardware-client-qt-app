#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QStringList>

class SerialController : public QObject
{
    Q_OBJECT
public:
    explicit SerialController(QObject *parent = nullptr);
    ~SerialController();

    void connectToDevice(const QString &portName);
    void disconnectDevice();
    void setMotorSpeed(int speed);
    bool isConnected() const;

signals:
    //Hardware sends updates back to the UI
    void availablePortsUpdated(const QStringList &ports);
    void handshakeSuccessful(const QString &portName, const QString &deviceName);
    void deviceDisconnected();
    void connectionError(const QString &errorMessage);

private slots:
    //Internal hardware events
    void pollPorts();
    void readIncomingData();

private:
    QSerialPort *serial;
    QTimer *portTimer;
    QStringList currentPortList; //A list of portNames use to frequently update changes
};

#endif // SERIALCONTROLLER_H
