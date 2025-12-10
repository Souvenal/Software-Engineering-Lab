#include "Product.h"
#include <QJsonArray>
#include <QJsonValue>

/**
 * @brief Product默认构造函数
 */
Product::Product() : productId(0), categoryId(0), price(0.0), sellerId(0) {
}

/**
 * @brief Product构造函数
 */
Product::Product(int productId, const QString& title, int categoryId, 
                 const QString& description, double price, int sellerId,
                 const QString& location, const QList<QString>& tags,
                 const QDateTime& publicTime, const QString& status)
    : productId(productId), title(title), categoryId(categoryId), 
      description(description), price(price), sellerId(sellerId),
      location(location), tags(tags), publicTime(publicTime), status(status) {
}

// Getters
int Product::getProductId() const { return productId; }
QString Product::getTitle() const { return title; }
int Product::getCategoryId() const { return categoryId; }
QString Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getSellerId() const { return sellerId; }
QString Product::getLocation() const { return location; }
QList<QString> Product::getTags() const { return tags; }
QDateTime Product::getPublicTime() const { return publicTime; }
QString Product::getStatus() const { return status; }

// Setters
void Product::setProductId(int id) { productId = id; }
void Product::setTitle(const QString& t) { title = t; }
void Product::setCategoryId(int id) { categoryId = id; }
void Product::setDescription(const QString& desc) { description = desc; }
void Product::setPrice(double p) { price = p; }
void Product::setSellerId(int id) { sellerId = id; }
void Product::setLocation(const QString& loc) { location = loc; }
void Product::setTags(const QList<QString>& t) { tags = t; }
void Product::setPublicTime(const QDateTime& time) { publicTime = time; }
void Product::setStatus(const QString& s) { status = s; }

Product Product::fromJson(const QJsonObject& obj) {
    Product product;
    
    product.setProductId(obj["productId"].toInt());
    product.setTitle(obj["title"].toString());
    product.setCategoryId(obj["categoryId"].toInt());
    product.setDescription(obj["description"].toString());
    product.setPrice(obj["price"].toDouble());
    product.setSellerId(obj["sellerId"].toInt());
    product.setLocation(obj["location"].toString());
    product.setStatus(obj["status"].toString());
    
    // 解析时间
    QString timeStr = obj["publicTime"].toString();
    product.setPublicTime(QDateTime::fromString(timeStr, Qt::ISODate));
    
    // 解析标签
    QList<QString> tags;
    QJsonArray tagsArray = obj["tags"].toArray();
    for (const QJsonValue& value : tagsArray) {
        tags.append(value.toString());
    }
    product.setTags(tags);
    
    return product;
}

QJsonObject Product::toJson(const Product& product) {
    QJsonObject obj;
    
    obj["productId"] = product.getProductId();
    obj["title"] = product.getTitle();
    obj["categoryId"] = product.getCategoryId();
    obj["description"] = product.getDescription();
    obj["price"] = product.getPrice();
    obj["sellerId"] = product.getSellerId();
    obj["location"] = product.getLocation();
    obj["status"] = product.getStatus();
    
    // 时间转换为字符串
    obj["publicTime"] = product.getPublicTime().toString(Qt::ISODate);
    
    // 标签转换为数组
    QJsonArray tagsArray;
    for (const QString& tag : product.getTags()) {
        tagsArray.append(tag);
    }
    obj["tags"] = tagsArray;
    
    return obj;
}