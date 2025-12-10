#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

/**
 * @brief 配置管理类
 * 
 * ConfigManager类负责管理系统配置，包括数据文件路径等
 */
class ConfigManager {
public:
    /**
     * @brief 获取商品数据文件路径
     * @return 商品数据文件路径
     */
    static QString getProductDataFile();
    
    /**
     * @brief 获取用户数据文件路径
     * @return 用户数据文件路径
     */
    static QString getUserDataFile();
};

#endif // CONFIGMANAGER_H