#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"
#include <QString>

/**
 * @brief 管理员类
 * 
 * Administrator类继承自User类，表示系统管理员，具有管理商品的权限
 */
class Administrator : public User {
public:
    /**
     * @brief 构造函数
     * @param userId 用户ID
     * @param roleId 角色ID
     * @param username 用户名
     * @param password 密码
     */
    Administrator(int userId, int roleId, const QString& username, const QString& password);

    /**
     * @brief 封禁商品
     * @param productId 商品ID
     * @return 封禁成功返回true，否则返回false
     */
    bool banProduct(int productId);

    /**
     * @brief 解封商品
     * @param productId 商品ID
     * @return 解封成功返回true，否则返回false
     */
    bool unbanProduct(int productId);

    /**
     * @brief 删除任意商品
     * @param productId 商品ID
     * @return 删除成功返回true，否则返回false
     */
    bool deleteAnyProduct(int productId);
};

#endif // ADMINISTRATOR_H