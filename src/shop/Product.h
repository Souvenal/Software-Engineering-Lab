#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QList>
#include <QDateTime>
#include <QJsonObject>

/**
 * @brief 商品类
 * 
 * Product类表示商城中的商品，包含商品的各种属性
 */
class Product {
public:
    /**
     * @brief 默认构造函数
     */
    Product();

    /**
     * @brief 构造函数
     * @param productId 商品ID
     * @param title 商品标题
     * @param categoryId 分类ID
     * @param description 商品描述
     * @param price 价格
     * @param sellerId 卖家ID
     * @param location 地址
     * @param tags 标签列表
     * @param publicTime 发布时间
     * @param status 状态
     */
    Product(int productId, const QString& title, int categoryId, 
            const QString& description, double price, int sellerId,
            const QString& location, const QList<QString>& tags,
            const QDateTime& publicTime, const QString& status);

    // Getters
    int getProductId() const;
    QString getTitle() const;
    int getCategoryId() const;
    QString getDescription() const;
    double getPrice() const;
    int getSellerId() const;
    QString getLocation() const;
    QList<QString> getTags() const;
    QDateTime getPublicTime() const;
    QString getStatus() const;

    // Setters
    void setProductId(int productId);
    void setTitle(const QString& title);
    void setCategoryId(int categoryId);
    void setDescription(const QString& description);
    void setPrice(double price);
    void setSellerId(int sellerId);
    void setLocation(const QString& location);
    void setTags(const QList<QString>& tags);
    void setPublicTime(const QDateTime& publicTime);
    void setStatus(const QString& status);

    /**
     * @brief 从JSON对象创建Product实例
     * @param obj JSON对象
     * @return Product实例
     */
    static Product fromJson(const QJsonObject& obj);

    /**
     * @brief 将Product实例转换为JSON对象
     * @param product Product实例
     * @return JSON对象
     */
    static QJsonObject toJson(const Product& product);

private:
    int productId;
    QString title;
    int categoryId;
    QString description;
    double price;
    int sellerId;
    QString location;
    QList<QString> tags;
    QDateTime publicTime;
    QString status;
};

#endif // PRODUCT_H