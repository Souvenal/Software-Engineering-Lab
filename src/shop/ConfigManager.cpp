#include "ConfigManager.h"
#include <QDir>
#include <QStandardPaths>

QString ConfigManager::getProductDataFile() {
    // 获取应用程序数据目录
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataDir);
    
    // 如果目录不存在则创建
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    // 返回商品数据文件路径
    return dir.filePath("products.json");
}

QString ConfigManager::getUserDataFile() {
    // 获取应用程序数据目录
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataDir);
    
    // 如果目录不存在则创建
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    // 返回用户数据文件路径
    return dir.filePath("users.json");
}