#include "serialcontroller.h"

SerialController::SerialController(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);

    connect(serial,
                        &QSerialPort::readyRead,
                        this,
            &SerialController::readIncomingData);

    portTimer = new QTimer(this);
    connect(portTimer,
                        &QTimer::timeout,
                        this,
            &SerialController::pollPorts);
    portTimer->start(1000);

    pollPorts(); //Run once immediately
}

SerialController::~SerialController()
{
    if (serial->isOpen()){
        serial->close();
    }
}

//PUBLIC FUNCTIONS (Called by MainWindow)
void SerialController::connectToDevice(const QString &portName)
{
    // if (serial->isOpen()){
    //     disconnectDevice();
    // }

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud115200);

    if (serial->open(QIODevice::ReadWrite)){
        //Prevent auto-reset on connection
        serial->setDataTerminalReady(false); //Pulls DTR low
        serial->setRequestToSend(false); //Pulls RTS low

        //Ping the connected device for its ID
        serial->write("?ID\n");
        emit handshakeSuccessful(portName, "S4V Motor Controller Rev2.0");
    } else {
        //Inform the UI that the connection trial failed
        emit connectionError(serial->errorString());
    }
}

void SerialController::disconnectDevice()
{
    if (serial->isOpen()){
        serial->close();
        //Inform the UI that disconnection is completed
        emit deviceDisconnected();
    }
}

void SerialController::setMotorSpeed(int speed)
{
    if (serial->isOpen()){
        QByteArray data = QByteArray::number(speed) + '\n';
        serial->write(data);
    }
}

bool SerialController::isConnected() const
{
    return serial->isOpen();
}

//INTERNAL SLOTS
void SerialController::pollPorts()
{
    //1. Get the live list of ports connected at the moment
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    QStringList livePortNames;

    for (const QSerialPortInfo &port : availablePorts){
        livePortNames  << port.portName();
    }
    if (livePortNames != currentPortList) {
        //Only inform the UI if a device is unplugged or new device is added to port list
        currentPortList = livePortNames;
        emit availablePortsUpdated(livePortNames);
    }
}

void SerialController::readIncomingData()
{
    if (serial->canReadLine()) {
        QByteArray data = serial->readLine().trimmed();

        if (data.startsWith("ID:")) {
            QString deviceName = data.mid(3);
            //Inform the UI to update the device connection status
            emit handshakeSuccessful(serial->portName(), deviceName);
        }
    }
}
