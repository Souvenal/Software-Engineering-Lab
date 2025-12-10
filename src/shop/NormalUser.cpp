#include "NormalUser.h"
#include <QApplication>
#include <QDebug>

NormalUser::NormalUser(int userId, int roleId, const QString& username, const QString& password)
    : User(userId, roleId, username, password)
{
}

/**
 * @brief 发布商品
 * @param product 要发布的商品
 * @return 发布成功返回true，否则返回false
 */
bool NormalUser::publishProduct(const Product& product) {
    // 实际实现中会调用ProductManager的相关方法
    // 这里只是简单示意
    return true;
}

/**
 * @brief 编辑商品
 * @param productId 商品ID
 * @param product 新的商品信息
 * @return 编辑成功返回true，否则返回false
 */
bool NormalUser::editProduct(int productId, const Product& product) {
    // 实际实现中会调用ProductManager的相关方法
    // 这里只是简单示意
    Q_UNUSED(productId);
    Q_UNUSED(product);
    return true;
}

/**
 * @brief 删除商品
 * @param productId 商品ID
 * @return 删除成功返回true，否则返回false
 */
bool NormalUser::deleteProduct(int productId) {
    // 实际实现中会调用ProductManager的相关方法
    // 这里只是简单示意
    Q_UNUSED(productId);
    return true;
}

/**
 * @brief 获取用户所拥有的商品列表
 * @return 商品列表的 QVector
 */
QVector<Product> NormalUser::getOwnedProducts() const {
    // 实际实现中会从ProductRepository获取属于当前用户的所有商品
    // 这里返回一个空的 QVector 作为示例
    return QVector<Product>();
}