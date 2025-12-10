#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "Product.h"
#include "ProductRepository.h"
#include "UserRepository.h"
#include <QList>

// Forward declarations for SearchCriteria
class SearchCriteria;

/**
 * @brief 商品管理器类
 * 
 * ProductManager类提供商品管理的核心业务逻辑，
 * 包括发布商品、编辑商品、删除商品、获取商品和搜索商品等功能
 */
class ProductManager {
public:
    /**
     * @brief 构造函数
     * @param productRepo 商品仓库引用
     * @param userRepo 用户仓库引用
     */
    ProductManager(ProductRepository& productRepo, UserRepository& userRepo);

    /**
     * @brief 发布商品
     * @param product 商品对象
     * @param userId 用户ID
     * @return 发布成功返回true，否则返回false
     */
    bool publishProduct(const Product& product, int userId);

    /**
     * @brief 编辑商品
     * @param productId 商品ID
     * @param product 新的商品信息
     * @param userId 用户ID
     * @return 编辑成功返回true，否则返回false
     */
    bool editProduct(int productId, const Product& product, int userId);

    /**
     * @brief 删除商品
     * @param productId 商品ID
     * @param userId 用户ID
     * @return 删除成功返回true，否则返回false
     */
    bool deleteProduct(int productId, int userId);

    /**
     * @brief 获取商品
     * @param productId 商品ID
     * @return 商品对象
     */
    Product getProduct(int productId) const;

    /**
     * @brief 获取所有商品
     * @return 商品列表
     */
    QList<Product> getAllProducts() const;

    /**
     * @brief 搜索商品
     * @param criteria 搜索条件
     * @return 商品列表
     */
    QList<Product> searchProducts(const SearchCriteria& criteria) const;

private:
    /**
     * @brief 验证商品所有权
     * @param productId 商品ID
     * @param userId 用户ID
     * @return 验证成功返回true，否则返回false
     */
    bool validateOwnership(int productId, int userId) const;

    /**
     * @brief 检查发布权限
     * @param userId 用户ID
     * @return 有权限返回true，否则返回false
     */
    bool checkPublishPermission(int userId) const;

    ProductRepository& productRepository; ///< 商品仓库引用
    UserRepository& userRepository;        ///< 用户仓库引用
};

#endif // PRODUCTMANAGER_H