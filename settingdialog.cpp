#include "settingdialog.h"
#include "ui_settingdialog.h"
SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    QSettings set(QDir::toNativeSeparators(QString("%1/Sys.ini").arg(QCoreApplication::applicationDirPath())),QSettings::IniFormat);
    set.setIniCodec("UTF-8");
    set.beginGroup("Camera");
    ui->lineEdit->setText(set.value("address1","192.168.1.101").toString());
    ui->lineEdit_2->setText(set.value("address2","192.168.1.102").toString());
    set.endGroup();

    set.beginGroup("Tcp");
    ui->lineEdit_3->setText(set.value("tcpAddr1","127.0.0.1").toString());
    ui->lineEdit_5->setText(set.value("tcpAddr2","127.0.0.1").toString());
    ui->lineEdit_4->setText(set.value("tcpPort1",50001).toString());
    ui->lineEdit_6->setText(set.value("tcpPort2",50002).toString());
    set.endGroup();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Ok)){
        QSettings set(QDir::toNativeSeparators(QString("%1/Sys.ini").arg(QCoreApplication::applicationDirPath())),QSettings::IniFormat);
        set.setIniCodec("UTF-8");
        set.beginGroup("Camera");
        set.setValue("address1",ui->lineEdit->text().trimmed());
        set.setValue("address2",ui->lineEdit_2->text().trimmed());
        set.endGroup();

        set.beginGroup("Tcp");
        set.setValue("tcpAddr1",ui->lineEdit_3->text().trimmed());
        set.setValue("tcpAddr2",ui->lineEdit_5->text().trimmed());
        set.setValue("tcpPort1",ui->lineEdit_4->text().trimmed());
        set.setValue("tcpPort2",ui->lineEdit_6->text().trimmed());
        set.endGroup();

        this->accept();
    }
    else {
        this->reject();
    }
}
