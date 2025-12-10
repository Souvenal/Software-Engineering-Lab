#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <memory>
#include "ui/LoginDialog.h"
#include "ui/MainWindow.h"
#include "shop/NormalUser.h"
#include "shop/Administrator.h"
#include "shop/Product.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 显示登录对话框
    LoginDialog loginDialog;
    int result = loginDialog.exec();
    
    if (result == QDialog::Accepted) {
        QString userType = loginDialog.getUserType();
        int userId = loginDialog.getUserId();
        
        // 创建并显示主窗口
        auto mainWindow = std::make_unique<MainWindow>(userType, userId);
        mainWindow->show();
        
        return app.exec();
    } else {
        qDebug() << "用户取消了登录";
        return 0;
    }

    // 默认返回
    return 0;
}