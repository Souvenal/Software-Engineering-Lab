#include "ProductRepository.h"
#include "ConfigManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>

/**
 * @brief ProductRepository默认构造函数
 */
ProductRepository::ProductRepository() : nextId(1) {
    // 尝试从文件加载数据
    loadFromFile();
}

/**
 * @brief 生成下一个可用的商品ID
 * @return 下一个商品ID
 */
int ProductRepository::generateNextId() {
    return nextId++;
}

/**
 * @brief 保存商品
 * @param product 商品对象
 * @return 保存成功返回true，否则返回false
 */
bool ProductRepository::save(const Product& product) {
    // 如果商品ID为0，则分配新的ID
    if (product.getProductId() == 0) {
        Product newProduct = product;
        // 注意：在实际实现中，需要修改Product对象的ID
        // 但由于Product的ID没有setter方法，这里简化处理
        products.insert(nextId++, product);
    } else {
        products.insert(product.getProductId(), product);
        if (product.getProductId() >= nextId) {
            nextId = product.getProductId() + 1;
        }
    }
    
    // 保存到文件
    return saveToFile();
}

/**
 * @brief 根据ID查找商品
 * @param productId 商品ID
 * @return 商品对象
 */
Product ProductRepository::findById(int productId) const {
    if (products.contains(productId)) {
        return products.value(productId);
    }
    // 如果未找到，返回默认构造的Product对象
    return Product();
}

/**
 * @brief 更新商品
 * @param product 商品对象
 * @return 更新成功返回true，否则返回false
 */
bool ProductRepository::update(const Product& product) {
    if (product.getProductId() <= 0) {
        return false;
    }
    
    products.insert(product.getProductId(), product);
    return saveToFile();
}

/**
 * @brief 删除商品
 * @param productId 商品ID
 * @return 删除成功返回true，否则返回false
 */
bool ProductRepository::remove(int productId) {
    bool result = products.remove(productId) > 0;
    if (result) {
        return saveToFile();
    }
    return result;
}

/**
 * @brief 根据卖家ID查找商品列表
 * @param sellerId 卖家ID
 * @return 商品列表
 */
QList<Product> ProductRepository::findBySellerId(int sellerId) const {
    QList<Product> result;
    for (const Product& product : products) {
        if (product.getSellerId() == sellerId) {
            result.append(product);
        }
    }
    return result;
}

/**
 * @brief 获取所有商品
 * @return 商品列表
 */
QList<Product> ProductRepository::getAllProducts() const {
    return products.values();
}

/**
 * @brief 从文件加载数据
 * @return 加载成功返回true，否则返回false
 */
bool ProductRepository::loadFromFile() {
    QString fileName = ConfigManager::getProductDataFile();
    QFile file(fileName);
    
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for reading:" << fileName;
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << error.errorString();
        return false;
    }
    
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format: not an array";
        return false;
    }
    
    QJsonArray array = doc.array();
    for (const QJsonValue& value : array) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            Product product = Product::fromJson(obj);
            products.insert(product.getProductId(), product);
            
            // 更新nextId
            if (product.getProductId() >= nextId) {
                nextId = product.getProductId() + 1;
            }
        }
    }
    
    return true;
}

/**
 * @brief 保存数据到文件
 * @return 保存成功返回true，否则返回false
 */
bool ProductRepository::saveToFile() {
    QString fileName = ConfigManager::getProductDataFile();
    QFile file(fileName);
    
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file for writing:" << fileName;
        return false;
    }
    
    QJsonArray array;
    for (const Product& product : products) {
        array.append(Product::toJson(product));
    }
    
    QJsonDocument doc(array);
    file.write(doc.toJson());
    file.close();
    
    file.close();
    
    return true;
}