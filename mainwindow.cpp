#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMaineWindow();
    loadParmenter();
    initCamera();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMaineWindow()
{
    comBox=new QComboBox(this);
    comBox->addItem("In");
    comBox->addItem("Out");
    QList<QAction*> actions=ui->toolBar->actions();
    ui->toolBar->insertWidget(actions[3],comBox);

    QWidget *spacer=new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer);

    control1=new QLabel(this);
    control1->setText("control1");
    control1->setStyleSheet("QLabel{color:wihte;background-color:red}");
    control2=new QLabel(this);
    control2->setText("control2");
    control2->setStyleSheet("QLabel{color:wihte;background-color:red}");
    ui->toolBar->addWidget(control1);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(control2);

    startTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz");
    ui->plainTextEdit->appendPlainText(startTime);
}

void MainWindow::initCamera()
{
    Plate=new ICE_Plate();
    connect(this,&MainWindow::SignalLoginCamera,Plate,&ICE_Plate::SlotLoginCamera);
    connect(Plate,&ICE_Plate::SignalMessage,this,&MainWindow::SlotMessage);
    connect(this,&MainWindow::SignalTrigger,Plate,&ICE_Plate::SlotTrigger);
    connect(this,&MainWindow::SignalRestart,Plate,&ICE_Plate::SlotRestart);
    connect(Plate,&ICE_Plate::SignalPlateConnect,this,&MainWindow::SlotPlateConnect);

    connect(Plate,&ICE_Plate::SignalPlateConnect,client1,&TcpClient::SlotPlateConnect);
    connect(Plate,&ICE_Plate::SignalPlateConnect,client2,&TcpClient::SlotPlateConnect);
    connect(Plate,&ICE_Plate::SignalPlateResults,client1,&TcpClient::SlotPlateResults);
    connect(Plate,&ICE_Plate::SignalPlateResults,client2,&TcpClient::SlotPlateResults);

    connect(client1,&TcpClient::SIgnalSimulationCapture,Plate,&ICE_Plate::SlotSimulationCapture);
    connect(client2,&TcpClient::SIgnalSimulationCapture,Plate,&ICE_Plate::SlotSimulationCapture);

    SignalLoginCamera(address1,ui->label_4->winId());
    SignalLoginCamera(address2,ui->label_5->winId());    
}

void MainWindow::loadParmenter()
{
    QSettings set(QDir::toNativeSeparators(QString("%1/Sys.ini").arg(QCoreApplication::applicationDirPath())),QSettings::IniFormat);
    set.setIniCodec("UTF-8");
    set.beginGroup("Camera");
    address1=set.value("address1","192.168.1.101").toString();
    address2=set.value("address2","192.168.1.102").toString();
    set.endGroup();

    set.beginGroup("Tcp");
    tcpAddr1=set.value("tcpAddr1","127.0.0.1").toString();
    tcpAddr2=set.value("tcpAddr2","127.0.0.1").toString();
    tcpPort1=set.value("tcpPort1",50001).toInt();
    tcpPort2=set.value("tcpPort2",50002).toInt();
    set.endGroup();

//    ///
//    /// \brief SignalPlateConnect 相机链接状态
//    /// \param address
//    /// \param state
//    ///
//    void SignalPlateConnect(QString address,bool state);

//    ///
//    /// \brief SignalPlateResults 车牌识别结果
//    /// \param arr
//    ///
//    void SignalPlateResults(QString address,QByteArray arr);

    client1=new TcpClient(this,address1,tcpPort1);
    connect(client1,&TcpClient::SignalPlateConnect,this,&MainWindow::SlotPlateConnect);
    connect(this,&MainWindow::SignalStartLink,client1,&TcpClient::startLinkSlot);
    connect(client1,&TcpClient::SignalMessage,this,&MainWindow::SlotMessage);


    client2=new TcpClient(this,address2,tcpPort2);
    connect(client2,&TcpClient::SignalPlateConnect,this,&MainWindow::SlotPlateConnect);
    connect(this,&MainWindow::SignalStartLink,client2,&TcpClient::startLinkSlot);
    connect(client2,&TcpClient::SignalMessage,this,&MainWindow::SlotMessage);

    emit SignalStartLink();
//    clientMap.insert(address1,client1);
//    clientMap.insert(address2,client2);
}


void MainWindow::on_actionSetting_triggered()
{
    QSharedPointer<SettingDialog> dlg(new SettingDialog());
    dlg->exec();
}

void MainWindow::on_actionPreview_triggered()
{
    /*****************************
    * @brief:not use
    ******************************/
}

void MainWindow::on_plainTextEdit_textChanged()
{
    if(ui->plainTextEdit->document()->blockCount()>300){
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(startTime);
    }
}

void MainWindow::SlotMessage(QString msg)
{
    ui->plainTextEdit->appendPlainText(QString("%1 %2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz"),msg));    
}

void MainWindow::SlotPlateConnect(QString addr, bool state)
{
    if(addr==address1){
        if(state){
            control1->setStyleSheet("QLabel{color:wihte;background-color:green}");
        }
        else {
            control1->setStyleSheet("QLabel{color:wihte;background-color:red}");
        }
    }
    if(addr==address2){
        if(state){
            control2->setStyleSheet("QLabel{color:wihte;background-color:green}");
        }
        else {
            control2->setStyleSheet("QLabel{color:wihte;background-color:red}");
        }
    }
}

void MainWindow::on_actionCapture_triggered()
{
    QString addr="";
    if(comBox->currentIndex()==0){
        addr=address1;
    }
    if(comBox->currentIndex()==1){
        addr=address2;
    }

    emit SignalTrigger(addr);
}

void MainWindow::on_actionRestart_triggered()
{
    QString addr="";
    if(comBox->currentIndex()==0){
        addr=address1;
    }
    if(comBox->currentIndex()==1){
        addr=address2;
    }

    emit SignalRestart(addr);
}
