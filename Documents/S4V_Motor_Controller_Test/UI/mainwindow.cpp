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

    QLabel* firstSTEPLabel = new QLabel("Step 1: Select Device port");
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

    QLabel* secondSTEPLabel = new QLabel("Step 2: Connect/Disconnect Device");
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

    QHBoxLayout* thirdSTEPMasterLayout = new QHBoxLayout(thirdSTEPFrame);
    thirdSTEPMasterLayout->setContentsMargins(25, 20, 25, 20); // (Left, Top, Right, Bottom) breathing room
    thirdSTEPMasterLayout->setAlignment(Qt::AlignVCenter); // Centers everything vertically

    QVBoxLayout* thirdSTEPLayout = new QVBoxLayout();
    thirdSTEPFrame->setFixedHeight(120);
    thirdSTEPFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    pageConnectionLayout->addSpacing(20);
    QLabel* thirdSTEPLabel = new QLabel("Device Connection Status");
    thirdSTEPLabel->setObjectName("lblThirdSTEP");
    thirdSTEPLayout->addWidget(thirdSTEPLabel);

    thirdSTEPMasterLayout->addLayout(thirdSTEPLayout);

    // Create a horizontal box for the Status Dot and the Status Text
    QHBoxLayout *statusContainer = new QHBoxLayout();
    statusContainer->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    statusContainer->setSpacing(8);
    statusContainer->addWidget(ui->lblStatus);
    statusContainer->addWidget(ui->lblStatusText);
    statusContainer->addStretch();

    thirdSTEPLayout->addLayout(statusContainer);

    // // --- NEW: Create the Image Label ---
    devicePictureLabel = new QLabel();

    // TIP: Change this to a .png with a transparent background!
    QPixmap deviceIconPix(":/motor_controller.png");

    // Increased size slightly for better proportions, but kept it smooth
    devicePictureLabel->setPixmap(deviceIconPix.scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Center the image within its own bounding box
    devicePictureLabel->setAlignment(Qt::AlignCenter);

    // --- NEW: Prevent the layout from shifting ---
    QSizePolicy retainPolicy = devicePictureLabel->sizePolicy();
    retainPolicy.setRetainSizeWhenHidden(true); // Reserves the space when hidden!
    devicePictureLabel->setSizePolicy(retainPolicy);
    // ---------------------------------------------

    devicePictureLabel->hide();
    thirdSTEPMasterLayout->addWidget(devicePictureLabel);

    pageConnectionLayout->addWidget(thirdSTEPFrame);
    pageConnectionLayout->addStretch();
    pageConnectionLayout->setContentsMargins(50, 30, 50, 30);
}


void MainWindow::UI_setupPageControl()
{
    /* CONTROL page */
    QVBoxLayout *pageControlLayout = new QVBoxLayout(pageControlWidget);

    QFrame *idFrame = new QFrame();
    /* Set up Motor ID configuration box */
    QHBoxLayout *idConfigLayout = new QHBoxLayout(idFrame);

    // --- Create the Motor Logo Label ---
    QLabel *motorLogoLabel = new QLabel();
    motorLogoLabel->setObjectName("lblMotorLogo");
    QPixmap iconPix(":/motor_controller.png");
    motorLogoLabel->setPixmap(iconPix.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    motorLogoLabel->setAlignment(Qt::AlignLeft);
    idConfigLayout->addWidget(motorLogoLabel);

    QVBoxLayout *masterLayout = new QVBoxLayout();
    QLabel *deviceName = new QLabel("Motor Controller Rev2.0");
    deviceName->setObjectName("lblDeviceName");

    QHBoxLayout *inputLayout = new QHBoxLayout();
    QLabel *idText = new QLabel("Device ID: ");
    idText->setObjectName("lblIdText");

    // Create the Input Box (Right Side)
    QLineEdit *idInput = new QLineEdit();
    idInput->setText("1");
    idInput->setObjectName("idInput"); // Crucial for applying the blue border style
    idInput->setFixedWidth(60);

    inputLayout->addWidget(idText);
    inputLayout->addWidget(idInput);
    inputLayout->addStretch();

    masterLayout->addWidget(deviceName);
    masterLayout->addLayout(inputLayout);

    idConfigLayout->addSpacing(20);
    idConfigLayout->addLayout(masterLayout);
    idConfigLayout->addStretch();

    pageControlLayout->addWidget(idFrame);

    /* Set up Motor Horizontal Layout:       DC Motor 1    -     DC Motor 2 */
    QFrame *motorFrame = new QFrame();
    QVBoxLayout *masterControlLayout  = new QVBoxLayout(motorFrame);
    QHBoxLayout *motorHorizontalLayout1 = new QHBoxLayout();

    // ==========================================
    // --- DC MOTOR 1 SETUP ---
    // ==========================================
    QFrame* dcMotor1Frame = new QFrame();
    dcMotor1Frame->setObjectName("dcMotor1Frame");
    QVBoxLayout* dcMotor1Layout = new QVBoxLayout(dcMotor1Frame);

    QLabel* dcMotor1Label = new QLabel("DC MOTOR 1");
    dcMotor1Label->setObjectName("lblDcMotor1");
    dcMotor1Layout->addWidget(dcMotor1Label);

    // This layout splits the slider (left) and the stats boxes (right)
    QHBoxLayout *dcMotor1SliderAndButtonsLayout = new QHBoxLayout();
    dcMotor1SliderAndButtonsLayout ->addSpacing(100);
    dcMotor1SliderAndButtonsLayout->addWidget(ui->motor1Slider); // Added ONLY ONCE
    dcMotor1SliderAndButtonsLayout ->addSpacing(60);
    // This vertical layout stacks the boxes on the right
    QVBoxLayout *motor1StatsLayout = new QVBoxLayout();
    motor1StatsLayout->setAlignment(Qt::AlignVCenter);
    motor1StatsLayout->setSpacing(8);

    // --- Box 1: Speed ---
    QFrame* motor1SpeedFrame = new QFrame();
    motor1SpeedFrame->setObjectName("motor1SpeedFrame");
    motor1SpeedFrame->setFixedHeight(28);

    QHBoxLayout *motor1ValueLayout = new QHBoxLayout(motor1SpeedFrame);
    motor1ValueLayout->setObjectName("motor1ValueLayout");
    motor1ValueLayout->setContentsMargins(10, 0, 10, 0);
    motor1ValueLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    motor1ValueLayout->setSpacing(8);

    QLabel *speed1LogoLabel = new QLabel();
    speed1LogoLabel->setObjectName("lblSpeedLogo");
    QPixmap speed1IconPix(":/speed.svg");

    // FIX: Safely using the speed variables now instead of overwriting the main logo
    speed1LogoLabel->setPixmap(speed1IconPix.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    speed1LogoLabel->setAlignment(Qt::AlignLeft);

    motor1ValueLayout->addWidget(speed1LogoLabel);
    motor1ValueLayout->addWidget(new QLabel("Speed:"));
    motor1ValueLayout->addStretch();
    motor1ValueLayout->addWidget(ui->lblMotor1Value);

    // FIX: Add the WIDGET (Frame) to the layout, not the internal layout!
    motor1StatsLayout->addWidget(motor1SpeedFrame);

    // --- Box 2: Mode ---
    QFrame* motor1ModeFrame = new QFrame();
    motor1ModeFrame->setObjectName("motor1ModeFrame");
    motor1ModeFrame->setFixedHeight(28);
    // Set the initial starting state property!
    motor1ModeFrame->setProperty("activeMode", "coast");

    QHBoxLayout *motor1ModeLayout = new QHBoxLayout(motor1ModeFrame);
    motor1ModeLayout->setContentsMargins(10, 0, 10, 0);
    motor1ModeLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QLabel *mode1LogoLabel = new QLabel();
    mode1LogoLabel->setObjectName("lblMode1Logo");
    QPixmap mode1IconPix(":/brake.svg");
    // FIX: Safely using the speed variables now instead of overwriting the main logo
    mode1LogoLabel->setPixmap(mode1IconPix.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    mode1LogoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    motor1ModeLayout->addWidget(mode1LogoLabel);
    motor1ModeLayout->addWidget(new QLabel("Mode:"));
    motor1ModeLayout->addStretch();
    // QLabel *lblMotor1Mode = new QLabel("COAST");

    ui->btnMotor1Mode->setObjectName("btnMotor1Mode");
    motor1Mode = true;
    ui->btnMotor1Mode->setText("COAST");

    motor1ModeLayout->addWidget(ui->btnMotor1Mode);

    motor1StatsLayout->addWidget(motor1ModeFrame);

    // --- Box 3: Current ---
    QFrame* motor1CurrentFrame = new QFrame();
    motor1CurrentFrame->setObjectName("motor1CurrentFrame");
    motor1CurrentFrame->setFixedHeight(28);

    QHBoxLayout *motor1CurrentLayout = new QHBoxLayout(motor1CurrentFrame);
    motor1CurrentLayout->setContentsMargins(10, 0, 10, 0);

    QLabel *current1LogoLabel = new QLabel();
    current1LogoLabel->setObjectName("lblCurrent1Logo");
    QPixmap current1IconPix(":/electricity.svg");
    // FIX: Safely using the speed variables now instead of overwriting the main logo
    current1LogoLabel->setPixmap(current1IconPix.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    current1LogoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    motor1CurrentLayout->addWidget(current1LogoLabel);
    motor1CurrentLayout->addWidget(new QLabel("Current:"));
    motor1CurrentLayout->addStretch();
    QLabel *lblMotor1Current = new QLabel("0.00 A");
    motor1CurrentLayout->addWidget(lblMotor1Current);

    motor1StatsLayout->addWidget(motor1CurrentFrame);

    // Assemble Motor 1 Layouts
    dcMotor1SliderAndButtonsLayout->addLayout(motor1StatsLayout);
    dcMotor1Layout->addLayout(dcMotor1SliderAndButtonsLayout);
    dcMotor1Layout->addWidget(ui->btnMotor1Start);


    // ==========================================
    // --- DC MOTOR 2 SETUP ---
    // ==========================================
    QFrame* dcMotor2Frame = new QFrame();
    dcMotor2Frame->setObjectName("dcMotor2Frame");
    QVBoxLayout* dcMotor2Layout = new QVBoxLayout(dcMotor2Frame);

    QLabel* dcMotor2Label = new QLabel("DC MOTOR 2");
    dcMotor2Label->setObjectName("lblDcMotor2");
    dcMotor2Layout->addWidget(dcMotor2Label);

    // This layout splits the slider (left) and the stats boxes (right)
    QHBoxLayout *dcMotor2SliderAndButtonsLayout = new QHBoxLayout();
    dcMotor2SliderAndButtonsLayout ->addSpacing(100);
    dcMotor2SliderAndButtonsLayout->addWidget(ui->motor2Slider); // Added ONLY ONCE
    dcMotor2SliderAndButtonsLayout ->addSpacing(60);
    // This vertical layout stacks the boxes on the right
    QVBoxLayout *motor2StatsLayout = new QVBoxLayout();
    motor2StatsLayout->setAlignment(Qt::AlignVCenter);
    motor2StatsLayout->setSpacing(8);

    // --- Box 1: Speed ---
    QFrame* motor2SpeedFrame = new QFrame();
    motor2SpeedFrame->setObjectName("motor2SpeedFrame");
    motor2SpeedFrame->setFixedHeight(28);

    QHBoxLayout *motor2ValueLayout = new QHBoxLayout(motor2SpeedFrame);
    motor2ValueLayout->setObjectName("motor2ValueLayout");
    motor2ValueLayout->setContentsMargins(10, 0, 10, 0);
    motor2ValueLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    motor2ValueLayout->setSpacing(8);

    QLabel *speed2LogoLabel = new QLabel();
    speed2LogoLabel->setObjectName("lblSpeed2Logo");
    QPixmap speed2IconPix(":/speed.svg");

    // FIX: Safely using the speed variables now instead of overwriting the main logo
    speed2LogoLabel->setPixmap(speed2IconPix.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    speed2LogoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    motor2ValueLayout->addWidget(speed2LogoLabel);
    motor2ValueLayout->addWidget(new QLabel("Speed:"));
    motor2ValueLayout->addStretch();
    motor2ValueLayout->addWidget(ui->lblMotor2Value);



    // FIX: Add the WIDGET (Frame) to the layout, not the internal layout!
    motor2StatsLayout->addWidget(motor2SpeedFrame);

    // --- Box 2: Mode ---
    QFrame* motor2ModeFrame = new QFrame();
    motor2ModeFrame->setObjectName("motor2ModeFrame");
    motor2ModeFrame->setFixedHeight(28);
    motor2ModeFrame->setProperty("activeMode", "coast");

    QHBoxLayout *motor2ModeLayout = new QHBoxLayout(motor2ModeFrame);
    motor2ModeLayout->setContentsMargins(10, 0, 10, 0);

    QLabel *mode2LogoLabel = new QLabel();
    mode2LogoLabel->setObjectName("lblMode2Logo");
    QPixmap mode2IconPix(":/brake.svg");
    // FIX: Safely using the speed variables now instead of overwriting the main logo
    mode2LogoLabel->setPixmap(mode2IconPix.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    mode2LogoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    motor2ModeLayout->addWidget(mode2LogoLabel);
    motor2ModeLayout->addWidget(new QLabel("Mode:"));

    motor2ModeLayout->addStretch();

    ui->btnMotor2Mode->setObjectName("btnMotor2Mode");
    motor2Mode = true;
    ui->btnMotor2Mode->setText("COAST");



    motor2ModeLayout->addWidget(ui->btnMotor2Mode);

    motor2StatsLayout->addWidget(motor2ModeFrame);

    // --- Box 3: Current ---
    QFrame* motor2CurrentFrame = new QFrame();
    motor2CurrentFrame->setObjectName("motor2CurrentFrame");
    motor2CurrentFrame->setFixedHeight(28);

    QHBoxLayout *motor2CurrentLayout = new QHBoxLayout(motor2CurrentFrame);
    motor2CurrentLayout->setContentsMargins(10, 0, 10, 0);

    QLabel *current2LogoLabel = new QLabel();
    current2LogoLabel->setObjectName("lblCurrent2Logo");
    QPixmap current2IconPix(":/electricity.svg");

    // FIX: Safely using the speed variables now instead of overwriting the main logo
    current2LogoLabel->setPixmap(current2IconPix.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    current2LogoLabel->setAlignment(Qt::AlignLeft);

    motor2CurrentLayout->addWidget(current2LogoLabel);
    motor2CurrentLayout->addWidget(new QLabel("Current:"));
    motor2CurrentLayout->addStretch();
    QLabel *lblMotor2Current = new QLabel("0.00 A");
    motor2CurrentLayout->addWidget(lblMotor2Current);

    motor2StatsLayout->addWidget(motor2CurrentFrame);

    // Assemble Motor 1 Layouts
    dcMotor1SliderAndButtonsLayout->addLayout(motor1StatsLayout);
    dcMotor1Layout->addLayout(dcMotor1SliderAndButtonsLayout);
    dcMotor1Layout->addWidget(ui->btnMotor1Start);
    // Assemble Motor 2 Layouts
    dcMotor2SliderAndButtonsLayout->addLayout(motor2StatsLayout);
    dcMotor2Layout->addLayout(dcMotor2SliderAndButtonsLayout);
    dcMotor2Layout->addWidget(ui->btnMotor2Start);

    // Assemble Master Layouts
    motorHorizontalLayout1->addWidget(dcMotor1Frame);
    motorHorizontalLayout1->addWidget(dcMotor2Frame);

    masterControlLayout->addLayout(motorHorizontalLayout1);
    pageControlLayout->addWidget(motorFrame);
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

    connect(ui->motor1Slider,
            &QSlider::valueChanged,
            this,
            &MainWindow::handleMotor1SliderSpeedChanged);

    connect(ui->motor2Slider,
            &QSlider::valueChanged,
            this,
            &MainWindow::handleMotor2SliderSpeedChanged);


    //Set isRunning initially as false (not running)
    motor1IsRunning = false;
    motor2IsRunning = false;

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
                            devicePictureLabel->show();

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
                            devicePictureLabel->hide();
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

//SHOW DEVICE PICTURE ON SUCCESSFUL CONNECTION

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

//BUTTON MODE MOTOR1 SLOT
void MainWindow::on_btnMotor1Mode_clicked(){
    motor1Mode = !motor1Mode;

    //Find local frame from the UI tree
    QFrame* modeFrame = this->findChild<QFrame*>("motor1ModeFrame");

    if (motor1Mode) {
        ui->btnMotor1Mode->setText("COAST");
        if (modeFrame) {
            modeFrame->setProperty("activeMode", "coast");
        }
    }
    else {
        ui->btnMotor1Mode->setText("BRAKE");
        if (modeFrame) {
            modeFrame->setProperty("activeMode", "brake");
        }
    }

    // CRITICAL: Force Qt to recalculate and redraw the frame's style!
    if (modeFrame) {
        modeFrame->style()->unpolish(modeFrame);
        modeFrame->style()->polish(modeFrame);
    }
}

void MainWindow::on_btnMotor2Mode_clicked(){
    motor2Mode = !motor2Mode;

    //Find local frame from the UI tree
    QFrame* modeFrame = this->findChild<QFrame*>("motor2ModeFrame");

    if (motor2Mode) {
        ui->btnMotor2Mode->setText("COAST");
        if (modeFrame) {
            modeFrame->setProperty("activeMode", "coast");
        }
    }
    else {
        ui->btnMotor2Mode->setText("BRAKE");
        if (modeFrame) {
            modeFrame->setProperty("activeMode", "brake");
        }
    }

    // CRITICAL: Force Qt to recalculate and redraw the frame's style!
    if (modeFrame) {
        modeFrame->style()->unpolish(modeFrame);
        modeFrame->style()->polish(modeFrame);
    }
}


void MainWindow::handleMotor1SliderSpeedChanged(int value){
    ui->lblMotor1Value->setText(QString::number(value));

    if( (!hardware->isConnected()) || (!motor1IsRunning) ){
        return;
    }
    qDebug() << "Motor 1 is running at Speed: " << value << "\n";
}

void MainWindow::handleMotor2SliderSpeedChanged(int value){
    ui->lblMotor2Value->setText(QString::number(value));

    if( (!hardware->isConnected()) || (!motor2IsRunning) ){
        return;
    }
    qDebug() << "Motor 2 is running at Speed: " << value << "\n";
}

void MainWindow::on_btnMotor1Start_clicked()
{
    if ( !hardware->isConnected()) {
        UI_showMessageBox(QMessageBox::Critical, "Error", "Connect to the device first to control!\n", "");
        return;
    }

    motor1IsRunning = !motor1IsRunning;

    if (!motor1IsRunning){
        ui->btnMotor1Start->setText("START");
        qDebug("Stopped the motor 1!");
    } else {
        ui->btnMotor1Start->setText("STOP");
        qDebug("Started the motor 1!");
    }

    int value = ui->motor1Slider->value();
    // hardware->setMotorSpeed(value);
}

void MainWindow::on_btnMotor2Start_clicked()
{
    if ( !hardware->isConnected()) {
        UI_showMessageBox(QMessageBox::Critical, "Error", "Connect to the device first to control!\n", "");
        return;
    }

    motor2IsRunning = !motor2IsRunning;

    if (!motor2IsRunning){
        ui->btnMotor2Start->setText("START");
        qDebug("Stopped the motor 2!");
    } else {
        ui->btnMotor2Start->setText("STOP");
        qDebug("Started the motor 2!");
    }

    int value = ui->motor2Slider->value();
    // hardware->setMotorSpeed(value);
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
    }
    else {
        cableUnplugged = true;
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
    ui->btnMotor1Start->setText("START");
    ui->btnMotor2Start->setText("START");
    ui->motor1Slider->setSliderPosition(0);
    ui->motor2Slider->setSliderPosition(0);
}
