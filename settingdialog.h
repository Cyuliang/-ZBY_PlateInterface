#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QSettings>
#include <QDir>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
