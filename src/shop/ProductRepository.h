#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H

#include "Product.h"
#include <QList>
#include <QHash>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

/**
 * @brief 商品仓库类
 * 
 * ProductRepository类负责商品数据的持久化操作，
 * 提供保存、查找、更新、删除以及JSON序列化等功能
 */
class ProductRepository {
public:
    /**
     * @brief 默认构造函数
     */
    ProductRepository();

    /**
     * @brief 保存商品
     * @param product 商品对象
     * @return 保存成功返回true，否则返回false
     */
    bool save(const Product& product);

    /**
     * @brief 根据ID查找商品
     * @param productId 商品ID
     * @return 商品对象
     */
    Product findById(int productId) const;

    /**
     * @brief 获取所有商品
     * @return 商品列表
     */
    QList<Product> getAllProducts() const;

    /**
     * @brief 更新商品
     * @param product 商品对象
     * @return 更新成功返回true，否则返回false
     */
    bool update(const Product& product);

    /**
     * @brief 删除商品
     * @param productId 商品ID
     * @return 删除成功返回true，否则返回false
     */
    bool remove(int productId);

    /**
     * @brief 根据卖家ID查找商品列表
     * @param sellerId 卖家ID
     * @return 商品列表
     */
    QList<Product> findBySellerId(int sellerId) const;

    /**
     * @brief 从JSON字符串加载商品信息
     * @param json JSON字符串
     * @return 加载成功返回true，否则返回false
     */
    bool loadFromJson(const QString& json);

    /**
     * @brief 将商品信息导出为JSON字符串
     * @return JSON字符串
     */
    QString dumpToJson() const;

    /**
     * @brief 从文件加载数据
     * @return 加载成功返回true，否则返回false
     */
    bool loadFromFile();

    /**
     * @brief 保存数据到文件
     * @return 保存成功返回true，否则返回false
     */
    bool saveToFile();

    /**
     * @brief 从JSON对象创建商品
     * @param obj JSON对象
     * @return 商品对象
     */
    static Product createProductFromJson(const QJsonObject& obj);

    /**
     * @brief 将商品转换为JSON对象
     * @param product 商品对象
     * @return JSON对象
     */
    static QJsonObject productToJson(const Product& product);

    /**
     * @brief 生成下一个可用的商品ID
     * @return 下一个商品ID
     */
    int generateNextId();

private:
    QHash<int, Product> products; ///< 商品存储哈希表，键为商品ID
    int nextId;                   ///< 下一个可用的商品ID
};

#endif // PRODUCTREPOSITORY_H