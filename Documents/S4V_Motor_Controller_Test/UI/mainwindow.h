#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QFrame>
#include <QIcon>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QDirIterator>
#include "Hardware/serialcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnConnect_clicked();
    void handleSliderSpeedChanged(int value);
    void on_btnStart_clicked();

private:
    Ui::MainWindow *ui;
    QFrame *sideBarFrame;
    QStackedWidget *stackedWidget;
    QWidget *pageConnectionWidget;
    QFrame *statusPill;
    QLabel *lblHeaderDot;
    QLabel *lblConnectedDevice;
    QWidget *pageControlWidget;
    QWidget *pageUpdateWidget;

    bool isRunning;
    bool cableUnplugged;
    SerialController* hardware;

    //Helper functions in constructor
    void UI_setupLayouts();
    void UI_setupLeftSidebar();
    void UI_setupCentralWidget();
    void UI_setupPageConnection();
    void UI_setupPageControl();
    void UI_setupPageUpdate();
    void UI_setupNavigation();
    void UI_applyStyles();

    //Helper functions for updating UI
    void UI_updateConnection(bool connection, QString portName, QString deviceName);
    void UI_updatePortList(QStringList &portList);
    void UI_showMessageBox(QMessageBox::Icon icon,  const QString &title, const QString &msg, const QString &errorMessage);
    void UI_resetControlPanel();
};
#endif // MAINWINDOW_H