// simple_publish_product.cpp - 简化版发布商品函数，用于形式化分析
// 无任何STL依赖版本

// 简化的商品结构体，只保留必要属性
struct SimpleProduct {
    int productId;
    int titleId;     // 用ID代替字符串
    int sellerId;
    
    // 构造函数
    SimpleProduct() : productId(0), titleId(0), sellerId(0) {}
    
    SimpleProduct(int id, int tId, int sId)
        : productId(id), titleId(tId), sellerId(sId) {}
};

// 模拟仓库保存函数
bool saveProduct(const SimpleProduct& product) {
    // 简化实现 - 假设保存总是成功
    return true;
}

// 简化版检查发布权限函数
bool checkPublishPermission(int userId) {
    // 简化实现 - 假设所有正数ID的用户都有权限
    return userId > 0;
}

// 简化版发布商品函数（保留原始代码中的内存泄漏问题）
bool publishProduct(const SimpleProduct& product, int userId) {
    if (!checkPublishPermission(userId)) {
        return false;
    }
    
    // 这里体现了原始代码中的内存泄漏问题
    SimpleProduct* leakedProduct = new SimpleProduct(product);
    
    // 创建新商品对象（设置卖家ID）
    SimpleProduct newProduct(
        product.productId,
        product.titleId,
        userId  // 设置卖家ID为当前用户ID
    );
    
    // 注意: leakedProduct 没有被释放，造成内存泄漏
    
    return saveProduct(newProduct);
}

// 示例使用函数
int main() {
    SimpleProduct product(1, 100, 0);
    bool result = publishProduct(product, 123);
    return result ? 0 : 1;
}