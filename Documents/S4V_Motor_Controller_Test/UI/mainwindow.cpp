#include "mainwindow.h"
#include "UI/ui_mainwindow.h"
#include <QFile>
#include <QFontDatabase>

void MainWindow::UI_setupPageConnection()
{
    ui->lblStatus->setFixedSize(16, 16);
    ui->lblStatus->setText("");
    ui->lblStatusText->setText("Disconnected");

    /* CONNECTION page */
    QVBoxLayout *pageConnectionLayout = new QVBoxLayout(pageConnectionWidget);

    QFrame* firstSTEPFrame = new QFrame();
    firstSTEPFrame->setObjectName("firstSTEPFrame");
    QVBoxLayout* firstSTEPLayout = new QVBoxLayout(firstSTEPFrame);

    QLabel* firstSTEPLabel = new QLabel("STEP 1: CHOOSE YOUR PORT");
    firstSTEPLabel->setObjectName("lblFirstSTEP");

    //2. CREATE THE BOTTOM SECTION
    QHBoxLayout *firstSTEPBottomLayout = new QHBoxLayout();
    firstSTEPBottomLayout->addWidget(ui->comboBoxPort);

    // TIP: Change spacing from 0 to 15 so the icon doesn't touch the combo box!
    firstSTEPBottomLayout->setSpacing(10);

    // --- NEW: Create the Image Label ---
    QLabel *iconLabel = new QLabel();

    // Load the image from your resources (assuming you have a usb.svg or similar)
    // You can use ":/connection.svg" to test it right now!
    QPixmap iconPix(":/connection.svg");

    // Scale the image down so it fits nicely next to the text box (e.g., 24x24 pixels)
    iconLabel->setPixmap(iconPix.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setAlignment(Qt::AlignRight);
    firstSTEPBottomLayout->addWidget(iconLabel);

    firstSTEPLayout->addWidget(firstSTEPLabel);
    firstSTEPLayout->addLayout(firstSTEPBottomLayout);

    QFrame* secondSTEPFrame = new QFrame();
    secondSTEPFrame->setObjectName("secondSTEPFrame");
    QVBoxLayout* secondSTEPLayout = new QVBoxLayout(secondSTEPFrame);

    QLabel* secondSTEPLabel = new QLabel("STEP 2: CONNECT TO MOTOR CONTROLLER");
    secondSTEPLabel->setObjectName("lblSecondSTEP");
    secondSTEPLayout->addWidget(secondSTEPLabel);
    secondSTEPLayout->addWidget(ui->btnConnect);


    QLabel *lblActiveDevice = new QLabel("ACTIVE DEVICE");
    lblActiveDevice->setObjectName("lblActiveDevice");
    pageConnectionLayout->addSpacing(20);
    pageConnectionLayout->addWidget(firstSTEPFrame);
    pageConnectionLayout->addSpacing(20);
    pageConnectionLayout->addWidget(secondSTEPFrame);

    QFrame* thirdSTEPFrame = new QFrame();
    thirdSTEPFrame->setObjectName("thirdSTEPFrame");

    QVBoxLayout* thirdSTEPLayout = new QVBoxLayout(thirdSTEPFrame);
    thirdSTEPFrame->setFixedHeight(120);
    thirdSTEPFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    pageConnectionLayout->addSpacing(20);
    QLabel* thirdSTEPLabel = new QLabel("CONNECTION STATUS");
    thirdSTEPLabel->setObjectName("lblThirdSTEP");
    thirdSTEPLayout->addWidget(thirdSTEPLabel);

    // Create a horizontal box for the Status Dot and the Status Text
    QHBoxLayout *statusContainer = new QHBoxLayout(thirdSTEPFrame);
    statusContainer->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    statusContainer->setSpacing(8);
    statusContainer->addWidget(ui->lblStatus);
    statusContainer->addWidget(ui->lblStatusText);

    thirdSTEPLayout->addLayout(statusContainer);

    pageConnectionLayout->addWidget(thirdSTEPFrame);
    pageConnectionLayout->addStretch();
    pageConnectionLayout->setContentsMargins(50, 30, 50, 30);
}

void MainWindow::UI_setupPageControl()
{
    /* CONTROL page */
    QVBoxLayout *pageControlLayout = new QVBoxLayout(pageControlWidget);

    QFrame *motorFrame = new QFrame();
    QHBoxLayout *motorHorizontalLayout1 = new QHBoxLayout(motorFrame);

    QFrame* dcMotor1Frame = new QFrame();
    dcMotor1Frame->setObjectName("dcMotor1Frame");
    QVBoxLayout* dcMotor1Layout = new QVBoxLayout(dcMotor1Frame);
    QLabel* dcMotor1Label = new QLabel("DC MOTOR 1");
    dcMotor1Label->setObjectName("lblDcMotor1");

    QFrame* dcMotor2Frame = new QFrame();
    dcMotor2Frame->setObjectName("dcMotor2Frame");
    QVBoxLayout* dcMotor2Layout = new QVBoxLayout(dcMotor2Frame);
    QLabel* dcMotor2Label = new QLabel("DC MOTOR 2");
    dcMotor2Label->setObjectName("lblDcMotor2");


    dcMotor1Layout->addWidget(dcMotor1Label);
    dcMotor2Layout->addWidget(dcMotor2Label);

    motorHorizontalLayout1->addWidget(dcMotor1Frame);
    motorHorizontalLayout1->addWidget(dcMotor2Frame);

    pageControlLayout->addWidget(motorFrame);


    pageControlLayout->addWidget(ui->sliderSpeed);
    pageControlLayout->addWidget(ui->lblValue);
    pageControlLayout->addWidget(ui->btnStart);
    pageControlLayout->addStretch();
}

void MainWindow::UI_setupLeftSidebar()
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

void MainWindow::UI_setupPageUpdate()
{

}

void MainWindow::UI_setupCentralWidget()
{
    /* A Stacked Widget to manage and display (pages) */
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(pageConnectionWidget);
    stackedWidget->addWidget(pageControlWidget);
    stackedWidget->addWidget(pageUpdateWidget);
}
void MainWindow::UI_setupLayouts(){
    /* Create 3 dedicated switchable pages for CONNECTION, MOTOR CONTROL and FIRMWARE UPDATE */
    pageConnectionWidget = new QWidget;
    pageConnectionWidget->setObjectName("pageConnectionWidget");
    pageControlWidget = new QWidget;
    pageControlWidget->setObjectName("pageControlWidget");
    pageUpdateWidget = new QWidget;
    pageUpdateWidget->setObjectName("pageUpdateWidget");

    UI_setupPageConnection();
    UI_setupPageControl();
    UI_setupPageUpdate();
    UI_setupLeftSidebar();
    UI_setupCentralWidget();

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

void MainWindow::UI_setupNavigation(){
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

void MainWindow::UI_applyStyles(){
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

    cableUnplugged = false;

    hardware = new SerialController(this);

    connect(hardware,
                        &SerialController::availablePortsUpdated,
                        this,
                        [this](QStringList ports) {
                            UI_updatePortList(ports);
            });

    connect(hardware,
                        &SerialController::handshakeSuccessful,
                        this,
                        [this](QString portName, QString deviceName) {
                            UI_updateConnection(true, portName, deviceName);
            });

    connect(hardware,
                        &SerialController::connectionError,
                        this,
                        [this] (const QString &errorMessage) {
                UI_showMessageBox(QMessageBox::Critical, "Error", "Failed to connect to device!", errorMessage);
            });

    connect(hardware,
                        &SerialController::deviceDisconnected,
                        this,
                        [this](){
                            UI_updateConnection(false, "", "");
                            UI_resetControlPanel();
            });

    UI_setupLayouts();
    UI_setupNavigation();
    UI_applyStyles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UI_updateConnection(bool connection, QString portName, QString deviceName)
{
    if(!connection) {
        ui->lblStatusText->setText("Disconnected");
        ui->lblStatus->setStyleSheet("background-color: #E74C3C; border-radius: 8px;");
        ui->btnConnect->setText("Connect");
        lblConnectedDevice->setText("Connected Device: None");
        lblHeaderDot->setStyleSheet("background-color: #E74C3C; border-radius: 6px;"); // Turn it red!



        qDebug("The device is unplugged. Stopped the motor!");
    } else {
        QString portName = ui->comboBoxPort->currentText();
        QString fullStatus = "Connected | " + portName + " |  " + deviceName;

        ui->lblStatusText->setText("Connected");
        ui->lblStatus->setStyleSheet("background-color: #2ECC71; border-radius: 8px;");
        ui->btnConnect->setText("Disconnect");
        // QString fullStatus = "Connected | " + portName + " | S4V Motor Controller Rev2.0";
        lblConnectedDevice->setText(fullStatus);
        lblHeaderDot->setStyleSheet("background-color: #2ECC71; border-radius: 6px;"); // Turn it green!
    }
}

//BUTTON CONNECT SLOT
void MainWindow::on_btnConnect_clicked(){
    bool connection = hardware->isConnected();
    if (connection){
        hardware->disconnectDevice();
        cableUnplugged = true;
    }
    else {
        QString selectedPort = ui->comboBoxPort->currentText();
        hardware->connectToDevice(selectedPort);
        cableUnplugged = false;
    }
}

void MainWindow::handleSliderSpeedChanged(int value){
    ui->lblValue->setText(QString::number(value));
    if( (!hardware->isConnected()) || (!isRunning) ){
        return;
    }
    qDebug() << "Motor is running at Speed: " << value << "\n";
}

void MainWindow::on_btnStart_clicked()
{
    if ( !hardware->isConnected()) {
        UI_showMessageBox(QMessageBox::Critical, "Error", "Connect to the device first to control!\n", "");
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
    hardware->setMotorSpeed(value);
}

void MainWindow::UI_updatePortList(QStringList &portList)
{
    //4. If a change happened, update the UI
    QString currentSelection = ui->comboBoxPort->currentText();
    //Wipe the box and add the fresh list
    ui->comboBoxPort->clear();
    ui->comboBoxPort->addItems(portList);

    //Try to restore the previous selection (if that cable is still plugged in)
    int index = ui->comboBoxPort->findText(currentSelection);
    if (index != -1){
        ui->comboBoxPort->setCurrentIndex(index);
    } else {
        cableUnplugged = true;
        // ui->lblStatusText->setText("Disconnected");
        // ui->lblStatus->setStyleSheet("background-color: #E74C3C; border-radius: 8px;");
        // ui->btnConnect->setText("Connect");
        // lblConnectedDevice->setText("Connected Device: None");
        // lblHeaderDot->setStyleSheet("background-color: #E74C3C; border-radius: 6px;"); // Turn it red!
    }
}

void MainWindow::UI_showMessageBox(QMessageBox::Icon icon, const QString &title, const QString &msg, const QString &errorMessage) {
    if (icon == QMessageBox::Critical){
        QMessageBox::critical(this, title, msg + "\n" + errorMessage);
    } else if (icon ==QMessageBox::Warning){
        QMessageBox::warning (this, title, msg + "\n" + errorMessage);
    }
}

void MainWindow::UI_resetControlPanel() {
    ui->btnStart->setText("START");
    ui->sliderSpeed->setSliderPosition(0);
}
