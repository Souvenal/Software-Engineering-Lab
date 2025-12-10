#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QCoreApplication>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    radioButtonNormalUser(new QRadioButton("普通用户")),
    radioButtonAdmin(new QRadioButton("管理员")),
    userIdEdit(new QLineEdit)
{
    // 设置默认选中项
    radioButtonNormalUser->setChecked(true);
    
    // 设置ID输入框的占位符文本
    userIdEdit->setPlaceholderText("请输入用户ID");
    
    // 创建按钮框
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, [this]() {
        if (userIdEdit->text().isEmpty()) {
            QMessageBox::warning(this, "输入错误", "请输入用户ID");
            return;
        }
        accept();
    });
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    // 创建布局
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new QLabel("请选择登录身份："));
    layout->addWidget(radioButtonNormalUser);
    layout->addWidget(radioButtonAdmin);
    
    // 添加ID输入框
    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("用户ID:", userIdEdit);
    layout->addLayout(formLayout);
    
    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout->addWidget(buttonBox);
    
    // 设置对话框布局
    setLayout(layout);
    setWindowTitle("商城系统 - 登录");
    resize(300, 200);
}

LoginDialog::~LoginDialog()
{
    // 控件会随父对象自动删除，无需手动释放
}

QString LoginDialog::getUserType() const
{
    if (radioButtonNormalUser->isChecked()) {
        return "normal";
    } else if (radioButtonAdmin->isChecked()) {
        return "admin";
    }
    return "normal"; // 默认返回普通用户
}

int LoginDialog::getUserId() const
{
    bool ok;
    int userId = userIdEdit->text().toInt(&ok);
    if (ok) {
        return userId;
    }
    return -1; // 返回无效ID
}