#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

void MainWindow::setupLayouts(){
    /* Create 3 dedicated switchable pages for CONNECTION, MOTOR CONTROL and FIRMWARE UPDATE */
    pageConnectionWidget = new QWidget;
    pageConnectionWidget->setObjectName("pageConnectionWidget");
    pageControlWidget = new QWidget;
    pageControlWidget->setObjectName("pageControlWidget");
    pageFirmwareWidget = new QWidget;
    pageFirmwareWidget->setObjectName("pageFirmwareWidget");

    /* A Stacked Widget to manage and display (pages) */
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(pageConnectionWidget);
    stackedWidget->addWidget(pageControlWidget);
    stackedWidget->addWidget(pageFirmwareWidget);

    /* CONNECTION page */
    QVBoxLayout *pageConnectionLayout = new QVBoxLayout(pageConnectionWidget);
    pageConnectionLayout->addWidget(ui->comboBoxPort);
    pageConnectionLayout->addWidget(ui->btnConnect);
    pageConnectionLayout->addWidget(ui->lblStatus);

    ui->lblStatus->setFixedSize(16, 16);
    ui->lblStatus->setText("   Disconnected");

    /* CONTROL page */
    QVBoxLayout *pageControlLayout = new QVBoxLayout(pageControlWidget);
    pageControlLayout->addWidget(ui->sliderSpeed);
    pageControlLayout->addWidget(ui->lblValue);
    pageControlLayout->addWidget(ui->btnStart);

    /* Create a horizontal layout to arrange objects from left to right
    (to display a left Side Bar & a central Stacked Widget) */
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    sideBarFrame = new QFrame();
    sideBarFrame->setObjectName("leftSideBar");
    sideBarFrame->setFixedWidth(120); // Adjust this between 100-150 until it looks perfect

    QVBoxLayout *sideBarLayout = new QVBoxLayout(sideBarFrame);

    // --- NEW: Add the Logo ---
    QLabel *logoLabel = new QLabel();
    // Load the image and scale it smoothly to fit
    QPixmap logoPix(":/steamforvietnam.png");
    logoLabel->setPixmap(logoPix.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);

    // Add the logo to the top of the layout
    sideBarLayout->addWidget(logoLabel);

    // Add a little space between the logo and the first button
    sideBarLayout->addSpacing(20);

    /* Put the button group 'navGroup' of navigation push buttons into the side bar frame */
    sideBarLayout->addWidget(ui->btnNavConnection);
    sideBarLayout->addWidget(ui->btnNavControl);
    sideBarLayout->addWidget(ui->btnNavFirmware);
    sideBarLayout->addStretch();
    sideBarLayout->setContentsMargins(0, 20, 0, 20);

    /* Put the Side bar Frame and Stacked Widget into the Main Layout */
    mainLayout->addWidget(sideBarFrame);
    mainLayout->addWidget(stackedWidget);

    ui->btnNavConnection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->btnNavControl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->btnNavFirmware->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    ui->btnNavConnection->setIcon(QIcon(":/connection.svg"));
    ui->btnNavControl->setIcon(QIcon(":/control.svg"));
    ui->btnNavFirmware->setIcon(QIcon(":/update.svg"));

    QSize iconSize(32, 32);
    ui->btnNavConnection->setIconSize(iconSize);
    ui->btnNavControl->setIconSize(iconSize);
    ui->btnNavFirmware->setIconSize(iconSize);
}

void MainWindow::setupNavigation(){
    connect(ui->btnNavConnection, &QPushButton::clicked, [this]() {
        /* Switch to CONNECTION page when the Connection navigation button is clicked */
        stackedWidget->setCurrentIndex(stackedWidget->indexOf(pageConnectionWidget));
    });

    connect(ui->btnNavControl, &QPushButton::clicked, [this](){
        /* Switch to CONTROL page when the Connection navigation button is clicked */
        stackedWidget->setCurrentIndex(stackedWidget->indexOf(pageControlWidget));
    });

    /* Set navigation buttons as radio buttons that are checkable */
    ui->btnNavConnection->setCheckable(true);
    ui->btnNavControl->setCheckable(true);
    ui->btnNavFirmware->setCheckable(true);

    QButtonGroup *navGroup = new QButtonGroup(this);
    navGroup->addButton(ui->btnNavConnection);
    navGroup->addButton(ui->btnNavControl);
    navGroup->addButton(ui->btnNavFirmware);

    /* Allows only 01 button is checked at a time */
    navGroup->setExclusive(true);

    /* Set the initial visible page as CONNECTION page */
    ui->btnNavConnection->setChecked(true);
}

void MainWindow::applyStyles(){
    // ui->lblStatus->setFixedSize(100, 100);

    QFile styleFile(":/style.qss");

    qDebug() << "1. Does QSS exist? :" << QFile::exists(":/style.qss");

    if(styleFile.open(QFile::ReadOnly)){
        // Use fromUtf8 to safely read the text
        QString styleSheet = QString::fromUtf8(styleFile.readAll());

        qDebug() << "2. File opened successfully.";
        qDebug() << "3. Characters read :" << styleSheet.length();
        qDebug() << "4. File Contents :\n" << styleSheet;

        this->setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        qDebug() << "FAILED to open file for reading!";
    }
}

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



    setupLayouts();

    setupNavigation();

    applyStyles();
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
        ui->lblStatus->setStyleSheet("background-color: #E74C3C; border-radius: 8px;");
        ui->btnConnect->setText("Connect");
    }
    else {
        serial->setPortName(ui->comboBoxPort->currentText());

        serial->setBaudRate(QSerialPort::Baud115200);

        if (serial->open(QIODevice::ReadWrite)){
            ui->lblStatus->setText("Connected");
            ui->lblStatus->setStyleSheet("background-color: #2ECC71; border-radius: 8px;");
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