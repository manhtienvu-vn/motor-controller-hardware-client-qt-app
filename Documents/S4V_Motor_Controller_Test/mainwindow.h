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
    void updatePortList();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QStackedWidget *stackedWidget;
    QWidget *pageConnectionWidget;
    QWidget *pageControlWidget;
    QWidget *pageUpdateWidget;
    QFrame *sideBarFrame;
    QFrame *statusPill;
    QLabel *lblHeaderDot;
    QLabel *lblConnectedDevice;
    QTimer *portTimer;
    bool isRunning;
    bool cableUnplugged;

    //Helper functions in constructor
    void setupLayouts();
    void setupLeftSidebar();
    void setupCentralWidget();
    void setupPageConnection();
    void setupPageControl();
    void setupPageUpdate();
    void setupNavigation();
    void applyStyles();
};
#endif // MAINWINDOW_H
