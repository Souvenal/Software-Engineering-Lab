#ifndef NORMALUSER_H
#define NORMALUSER_H

#include "User.h"
#include "Product.h"
#include <QList>
#include <QVector>

/**
 * @brief 普通用户类
 * 
 * NormalUser继承自User类，具有普通用户特有的功能，
 * 如发布商品、编辑商品、删除商品等
 */
class NormalUser : public User {
public:
    /**
     * @brief 构造函数
     * @param userId 用户ID
     * @param roleId 角色ID
     * @param username 用户名
     * @param password 密码
     */
    NormalUser(int userId, int roleId, const QString& username, const QString& password);

    /**
     * @brief 发布商品
     * @param product 要发布的商品
     * @return 发布成功返回true，否则返回false
     */
    bool publishProduct(const Product& product);

    /**
     * @brief 编辑商品
     * @param productId 商品ID
     * @param product 新的商品信息
     * @return 编辑成功返回true，否则返回false
     */
    bool editProduct(int productId, const Product& product);

    /**
     * @brief 删除商品
     * @param productId 商品ID
     * @return 删除成功返回true，否则返回false
     */
    bool deleteProduct(int productId);
    
    /**
     * @brief 获取用户所拥有的商品列表
     * @return 商品列表的 QVector
     */
    QVector<Product> getOwnedProducts() const;
};

#endif // NORMALUSER_H