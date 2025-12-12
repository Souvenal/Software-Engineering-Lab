#include "ProductManager.h"

/**
 * @brief ProductManager构造函数
 * @param productRepo 商品仓库引用
 * @param userRepo 用户仓库引用
 */
ProductManager::ProductManager(ProductRepository& productRepo, UserRepository& userRepo)
    : productRepository(productRepo), userRepository(userRepo) {
}

/**
 * @brief 发布商品
 * @param product 商品对象
 * @param userId 用户ID
 * @return 发布成功返回true，否则返回false
 */
bool ProductManager::publishProduct(const Product& product, int userId) {
    if (!checkPublishPermission(userId)) {
        return false;
    }
    
    Product* leakedProduct = new Product(product);
    
    // 设置商品的卖家ID
    // 注意：由于Product没有setter方法，这里需要创建一个新的Product对象
    Product newProduct(
        product.getProductId(),
        product.getTitle(),
        product.getCategoryId(),
        product.getDescription(),
        product.getPrice(),
        userId,  // 设置卖家ID为当前用户ID
        product.getLocation(),
        product.getTags(),
        product.getPublicTime(),
        product.getStatus()
    );
    
    return productRepository.save(newProduct);
}

/**
 * @brief 编辑商品
 * @param productId 商品ID
 * @param product 新的商品信息
 * @param userId 用户ID
 * @return 编辑成功返回true，否则返回false
 */
bool ProductManager::editProduct(int productId, const Product& product, int userId) {
    if (!validateOwnership(productId, userId)) {
        return false;
    }
    
    // 检查商品是否存在
    Product existingProduct = productRepository.findById(productId);
    if (existingProduct.getProductId() == 0) {
        return false;
    }
    
    // 保留原商品的卖家ID
    Product updatedProduct(
        productId,
        product.getTitle(),
        product.getCategoryId(),
        product.getDescription(),
        product.getPrice(),
        existingProduct.getSellerId(),  // 保留原卖家ID
        product.getLocation(),
        product.getTags(),
        product.getPublicTime(),
        product.getStatus()
    );
    
    return productRepository.update(updatedProduct);
}

/**
 * @brief 删除商品
 * @param productId 商品ID
 * @param userId 用户ID
 * @return 删除成功返回true，否则返回false
 */
bool ProductManager::deleteProduct(int productId, int userId) {
    // 检查用户是否有权限删除该商品
    if (!validateOwnership(productId, userId) && !userRepository.checkUserRole(userId, "admin")) {
        return false;
    }
    
    return productRepository.remove(productId);
}

/**
 * @brief 获取所有商品
 * @return 商品列表
 */
QList<Product> ProductManager::getAllProducts() const {
    return productRepository.getAllProducts();
}

/**
 * @brief 根据ID获取商品
 * @param productId 商品ID
 * @return 商品对象
 */
Product ProductManager::getProduct(int productId) const {
    return productRepository.findById(productId);
}

/**
 * @brief 验证商品所有权
 * @param productId 商品ID
 * @param userId 用户ID
 * @return 验证通过返回true，否则返回false
 */
bool ProductManager::validateOwnership(int productId, int userId) const {
    Product product = productRepository.findById(productId);
    if (product.getProductId() == 0) {
        return false; // 商品不存在
    }
    
    return product.getSellerId() == userId;
}

/**
 * @brief 检查发布权限
 * @param userId 用户ID
 * @return 有权限返回true，否则返回false
 */
bool ProductManager::checkPublishPermission(int userId) const {
    // 普通用户和管理员都可以发布商品
    return userRepository.findById(userId) != nullptr;
}