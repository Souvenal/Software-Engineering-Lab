#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QCoreApplication>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    radioButtonNormalUser(new QRadioButton("普通用户")),
    radioButtonAdmin(new QRadioButton("管理员"))
{
    // 设置默认选中项
    radioButtonNormalUser->setChecked(true);
    
    // 创建按钮框
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    // 创建布局
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new QLabel("请选择登录身份："));
    layout->addWidget(radioButtonNormalUser);
    layout->addWidget(radioButtonAdmin);
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
    // 简化处理，根据用户类型返回不同的ID
    if (radioButtonAdmin->isChecked()) {
        return 1; // 管理员ID
    } else {
        return 2; // 普通用户ID
    }
    return 1; // 默认返回管理员ID
}