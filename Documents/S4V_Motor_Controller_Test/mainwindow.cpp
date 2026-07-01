#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

void MainWindow::setupPageConnection()
{
    ui->lblStatus->setFixedSize(16, 16);
    ui->lblStatus->setText("");
    ui->lblStatusText->setText("Disconnected");

    /* CONNECTION page */
    QVBoxLayout *pageConnectionLayout = new QVBoxLayout(pageConnectionWidget);
    // Add Active Device Label and Combo Box to Header
    QLabel *lblActiveDevice = new QLabel("ACTIVE DEVICE");
    lblActiveDevice->setObjectName("lblActiveDevice");
    pageConnectionLayout->addWidget(lblActiveDevice);
    pageConnectionLayout->addWidget(ui->comboBoxPort);
    pageConnectionLayout->addWidget(ui->btnConnect);

    // Create a horizontal box for the Status Dot and the Status Text
    QHBoxLayout *statusContainer = new QHBoxLayout();
    statusContainer->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    statusContainer->setSpacing(8);
    statusContainer->addWidget(ui->lblStatus);
    statusContainer->addWidget(ui->lblStatusText);

    pageConnectionLayout->addLayout(statusContainer);
    pageConnectionLayout->addStretch();
}

void MainWindow::setupPageControl()
{
    /* CONTROL page */
    QVBoxLayout *pageControlLayout = new QVBoxLayout(pageControlWidget);

    pageControlLayout->addWidget(ui->sliderSpeed);
    pageControlLayout->addWidget(ui->lblValue);
    pageControlLayout->addWidget(ui->btnStart);
    pageControlLayout->addStretch();
}

void MainWindow::setupLeftSidebar()
{
    sideBarFrame = new QFrame();
    sideBarFrame->setObjectName("leftSideBar");
    sideBarFrame->setFixedWidth(100); // Adjust this between 100-150 until it looks perfect

    QVBoxLayout *sideBarLayout = new QVBoxLayout(sideBarFrame);
    // Add a little space between the logo and the first button
    sideBarLayout->addSpacing(10);

    /* Put the button group 'navGroup' of navigation push buttons into the side bar frame */
    sideBarLayout->addWidget(ui->btnNavConnection);
    sideBarLayout->addWidget(ui->btnNavControl);
    sideBarLayout->addWidget(ui->btnNavFirmware);
    sideBarLayout->addStretch();
    sideBarLayout->setContentsMargins(0, 20, 0, 20);

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

void MainWindow::setupPageUpdate()
{

}

void MainWindow::setupCentralWidget()
{
    /* A Stacked Widget to manage and display (pages) */
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(pageConnectionWidget);
    stackedWidget->addWidget(pageControlWidget);
    stackedWidget->addWidget(pageUpdateWidget);
}
void MainWindow::setupLayouts(){
    /* Create 3 dedicated switchable pages for CONNECTION, MOTOR CONTROL and FIRMWARE UPDATE */
    pageConnectionWidget = new QWidget;
    pageConnectionWidget->setObjectName("pageConnectionWidget");
    pageControlWidget = new QWidget;
    pageControlWidget->setObjectName("pageControlWidget");
    pageUpdateWidget = new QWidget;
    pageUpdateWidget->setObjectName("pageUpdateWidget");

    setupPageConnection();
    setupPageControl();
    setupPageUpdate();
    setupLeftSidebar();
    setupCentralWidget();

    //1. CREATE THE GLOBAL HEADER
    QFrame *headerFrame = new QFrame();
    headerFrame->setObjectName("headerFrame");
    headerFrame->setFixedHeight(65);

    QHBoxLayout *headerLayout = new QHBoxLayout(headerFrame);
    headerLayout->setContentsMargins(20, 0, 20, 0);

    //Add logo to Header
    QLabel *logoLabel = new QLabel();
    // Load the image and scale it smoothly to fit
    QPixmap logoPix(":/steamforvietnam.png");
    logoLabel->setPixmap(logoPix.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    headerLayout->addWidget(logoLabel);
    headerLayout->addSpacing(30);

    // //Create the Container Frame
    statusPill = new QFrame();
    statusPill->setObjectName("statusPill");
    statusPill->setFixedHeight(28);

    //Give the Pill a horizontal layout
    QHBoxLayout *pillLayout = new QHBoxLayout(statusPill);
    pillLayout->setContentsMargins(10, 0, 10, 0);
    pillLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    pillLayout->setSpacing(8); //space between the dot and the text label

    //Create the Status Dot
    lblHeaderDot = new QLabel();
    lblHeaderDot->setObjectName("lblHeaderDot");
    lblHeaderDot->setFixedSize(12, 12);
    lblHeaderDot->setText("");          // CRITICAL: Ensure no text is in the dot
    lblHeaderDot->setStyleSheet("background-color: #E74C3C; border-radius: 6px;"); // Turn it red!

    //Create the Status Text
    lblConnectedDevice = new QLabel("Connected Device: None");
    lblConnectedDevice->setObjectName("lblConnectedDevice");

    pillLayout->addWidget(lblHeaderDot);
    pillLayout->addWidget(lblConnectedDevice);
    pillLayout->addStretch();
    headerLayout->addWidget(statusPill);
    headerLayout->addStretch();

    //2. CREATE THE BOTTOM SECTION (Sidebar + Content)
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->setSpacing(0);
    bottomLayout->addWidget(sideBarFrame);
    bottomLayout->addWidget(stackedWidget);

    //3. MASTER ASSEMBLY (Vertical Split)
    QVBoxLayout *masterLayout = new QVBoxLayout();
    masterLayout->setContentsMargins(0, 0, 0, 0);
    masterLayout->setSpacing(0);
    masterLayout->addWidget(headerFrame);
    masterLayout->addLayout(bottomLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(masterLayout);
    setCentralWidget(centralWidget);
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
    QFile styleFile(":/style.qss");

    qDebug() << "1. Does QSS exist? :" << QFile::exists(":/style.qss");

    if(styleFile.open(QFile::ReadOnly)){
        // Use fromUtf8 to safely read the text
        QString styleSheet = QString::fromUtf8(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        qDebug() << "FAILED to open file for reading!";
    }
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) , ui(new Ui::MainWindow)
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

        ui->lblStatusText->setText("Disconnected");
        ui->lblStatus->setStyleSheet("background-color: #E74C3C; border-radius: 8px;");
        ui->btnConnect->setText("Connect");
        lblConnectedDevice->setText("Connected Device: None");
        lblHeaderDot->setStyleSheet("background-color: #E74C3C; border-radius: 6px;"); // Turn it red!
    }
    else {
        serial->setPortName(ui->comboBoxPort->currentText());
        serial->setBaudRate(QSerialPort::Baud115200);

        if (serial->open(QIODevice::ReadWrite)){
            ui->lblStatusText->setText("Connected");
            ui->lblStatus->setStyleSheet("background-color: #2ECC71; border-radius: 8px;");
            ui->btnConnect->setText("Disconnect");

            QString portName = ui->comboBoxPort->currentText();
            QString fullStatus = "Connected | " + portName + " | S4V Motor Controller Rev2.0";
            lblConnectedDevice->setText(fullStatus);
            lblHeaderDot->setStyleSheet("background-color: #2ECC71; border-radius: 6px;"); // Turn it green!
        }
    }
}

void MainWindow::handleSliderSpeedChanged(int value){
    ui->lblValue->setText(QString::number(value));
    if( (!serial->isOpen()) || (!isRunning) ){
        return;
    }
    qDebug() << "Motor is running at Speed: " << value << "\n";
}

void MainWindow::on_btnStart_clicked()
{
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

// void MainWindow::on_connection_changed()
// {

// }