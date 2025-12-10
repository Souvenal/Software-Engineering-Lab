#include "ConfigManager.h"
#include <QDir>
#include <QCoreApplication>
#include <QDebug>

QString ConfigManager::getProductDataFile() {
    // 获取应用程序数据目录
    QString dataDir = QCoreApplication::applicationDirPath();
    QDir dir(dataDir);
    
    // 返回商品数据文件路径
    return dir.filePath("products.json");
}

QString ConfigManager::getUserDataFile() {
    // 获取应用程序数据目录
    QString dataDir = QCoreApplication::applicationDirPath();
    QDir dir(dataDir);
    
    // 返回用户数据文件路径
    return dir.filePath("users.json");
}