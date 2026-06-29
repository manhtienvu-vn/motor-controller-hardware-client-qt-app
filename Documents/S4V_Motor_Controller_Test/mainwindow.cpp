#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    //Check for available connected device ports
    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts()){
        qDebug() << port.portName();

        ui->comboBoxPort->addItem(port.portName());
    }

    connect(ui->sliderSpeed,
            &QSlider::valueChanged,
            this,
            &MainWindow::handleSliderSpeedChanged);

    //Set isRunning initially as false (not running)
    isRunning = false;

    // ui->sliderSpeed->setVisible(false);
    // ui->btnStart->setVisible(false);
    // ui->lblValue->setVisible(false);

    QWidget *firstPageWidget = new QWidget;
    QWidget *secondPageWidget = new QWidget;
    QWidget *thirdPageWidget = new QWidget;

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(firstPageWidget);
    stackedWidget->addWidget(secondPageWidget);
    stackedWidget->addWidget(thirdPageWidget);

    QVBoxLayout *pageConnectionLayout = new QVBoxLayout(firstPageWidget);
    pageConnectionLayout->addWidget(ui->comboBoxPort);
    pageConnectionLayout->addWidget(ui->btnConnect);
    pageConnectionLayout->addWidget(ui->lblStatus);


    QVBoxLayout *pageControlLayout = new QVBoxLayout(secondPageWidget);
    pageControlLayout->addWidget(ui->sliderSpeed);
    pageControlLayout->addWidget(ui->lblValue);
    pageControlLayout->addWidget(ui->btnStart);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *sideBarLayout = new QVBoxLayout();

    sideBarLayout->addWidget(ui->btnNavConnection);
    sideBarLayout->addWidget(ui->btnNavControl);
    sideBarLayout->addWidget(ui->btnNavFirmware);
    sideBarLayout->addStretch();

    mainLayout->addLayout(sideBarLayout);

    mainLayout->addWidget(stackedWidget);


    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(ui->btnNavConnection, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnNavControl, &QPushButton::clicked, [this](){
        stackedWidget->setCurrentIndex(1);
    });

    ui->btnNavConnection->setCheckable(true);
    ui->btnNavControl->setCheckable(true);
    ui->btnNavFirmware->setCheckable(true);

    QButtonGroup *navGroup = new QButtonGroup(this);
    navGroup->setExclusive(true);

    navGroup->addButton(ui->btnNavConnection);
    navGroup->addButton(ui->btnNavControl);
    navGroup->addButton(ui->btnNavFirmware);

    ui->btnNavConnection->setChecked(true);

    // Define the style sheet string
    QString buttonStyle =
        //Default state (Unchecked)
        "QPushButton {"
        "   background-color: transparent;" // No background normally
        "   color: #A0A0A0;"               // Gray text
        "   border: none;"
        "   text-align: left;"             // Align text to the left
        "   padding: 10px 20px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "}"
        // Hover state (When mouse is over it but not clicked)
        "QPushButton:hover {"
        "   color: #A0A0A0;"               // Text turns white
        "   background-color: transparent;"    // Slight dark gray background
        "}"
        // Checked state (The active active page)
        "QPushButton:checked {"
        "   background-color: #14887B;"    // Bright Blue highlight
        "   color: #DAF4F2;"               // White text
        "   border-left: 4px solid #00BFFF;" // A nice accent line on the left
        "}";

    // Apply the style to the buttons
    ui->btnNavConnection->setStyleSheet(buttonStyle);
    ui->btnNavControl->setStyleSheet(buttonStyle);
    ui->btnNavFirmware->setStyleSheet(buttonStyle);
}


MainWindow::~MainWindow()
{
    delete ui;
}

//BUTTON CONNECT SLOT
void MainWindow::on_btnConnect_clicked(){

    if (serial->isOpen()){
        serial->close();

        ui->lblStatus->setText("Disconnected");

        ui->btnConnect->setText("Connect");

        // ui->sliderSpeed->setVisible(false);
        // ui->btnStart->setVisible(false);
        // ui->lblValue->setVisible(false);
    }
    else {
        // ui->sliderSpeed->setVisible(true);
        // ui->btnStart->setVisible(true);
        // ui->lblValue->setVisible(true);

        serial->setPortName(ui->comboBoxPort->currentText());

        serial->setBaudRate(QSerialPort::Baud115200);

        if (serial->open(QIODevice::ReadWrite)){
            ui->lblStatus->setText("Connected");

            ui->btnConnect->setText("Disconnect");
        }
    }

}

void MainWindow::handleSliderSpeedChanged(int value){
    ui->lblValue->setText(QString::number(value));
    if((!serial->isOpen()) || (!isRunning)){
        return;
    }
    qDebug() << "Motor is running at Speed: " << value << "\n";
}

void MainWindow::on_btnStart_clicked(){
    if (!serial->isOpen()){
        return;
    }
    isRunning = !isRunning;

    if (!isRunning){
        ui->btnStart->setText("START");
        qDebug("Stopped the motor!");
    } else {
        ui->btnStart->setText("STOP");
        qDebug("Started the motor!");
    }

    int value = ui->sliderSpeed->value();

    QByteArray data = QByteArray::number(value);
    data.append('\n');

    serial->write(data);
}

