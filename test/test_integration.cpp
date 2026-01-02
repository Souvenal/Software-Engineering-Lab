#include <iostream>
#include <gtest/gtest.h>
#include <QList>
#include <QString>
#include <QDateTime>

#include "ProductRepository.h"
#include "UserRepository.h"
#include "ProductManager.h"
#include "Product.h"
#include "User.h"
#include "Administrator.h"
#include "NormalUser.h"

/**
 * @brief 集成测试报告
 * 
 * 测试概述：
 * 本测试采用自底向上的集成测试方法，逐步验证各模块间的接口正确性和数据传递准确性。
 * 第一组测试：ProductRepository 与 Product 的集成
 * 第二组测试：ProductManager 与 ProductRepository、UserRepository 的集成
 * 
 * 测试环境：C++17, Qt5, Google Test
 * 测试工具：Google Test框架
 */

// 第一组集成测试：ProductRepository 与 Product 的集成
class ProductRepoIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 初始化测试数据
        testProduct = Product(1, "测试商品", 1, "这是一个测试商品", 99.9, 1001, "北京", 
                              QList<QString>() << "测试" << "商品", QDateTime::currentDateTime(), "active");
    }

    Product testProduct;
    ProductRepository repo;
};

// 测试ProductRepository与Product的集成
TEST_F(ProductRepoIntegrationTest, SaveAndFindProduct) {
    // 测试保存商品
    bool saveResult = repo.save(testProduct);
    EXPECT_TRUE(saveResult) << "商品应该成功保存";
    
    // 测试根据ID查找商品
    Product foundProduct = repo.findById(1);
    EXPECT_EQ(foundProduct.getProductId(), 1) << "商品ID应该为1";
    EXPECT_EQ(foundProduct.getTitle(), "测试商品") << "商品标题应该为'测试商品'";
}

TEST_F(ProductRepoIntegrationTest, GetAllProducts) {
    // 先保存一个商品
    repo.save(testProduct);
    
    // 测试获取所有商品
    QList<Product> allProducts = repo.getAllProducts();
    EXPECT_EQ(allProducts.size(), 1) << "应该有一个商品";
    EXPECT_EQ(allProducts[0].getProductId(), 1) << "商品ID应该为1";
    EXPECT_EQ(allProducts[0].getTitle(), "测试商品") << "商品标题应该为'测试商品'";
}

TEST_F(ProductRepoIntegrationTest, UpdateProduct) {
    // 先保存一个商品
    repo.save(testProduct);
    
    // 测试更新商品
    Product updatedProduct(1, "更新后的商品", 1, "这是一个更新后的测试商品", 199.9, 1001, "上海", 
                          QList<QString>() << "更新" << "商品", QDateTime::currentDateTime(), "active");
    bool updateResult = repo.update(updatedProduct);
    EXPECT_TRUE(updateResult) << "商品应该成功更新";
    
    // 验证更新结果
    Product verifyUpdated = repo.findById(1);
    EXPECT_EQ(verifyUpdated.getTitle(), "更新后的商品") << "商品标题应该更新为'更新后的商品'";
}

TEST_F(ProductRepoIntegrationTest, RemoveProduct) {
    // 先保存一个商品
    repo.save(testProduct);
    
    // 测试删除商品
    bool deleteResult = repo.remove(1);
    EXPECT_TRUE(deleteResult) << "商品应该成功删除";
    
    // 验证删除结果
    Product verifyDeleted = repo.findById(1);
    EXPECT_EQ(verifyDeleted.getProductId(), 0) << "商品应该已被删除（ID为0）";
}

// 第二组集成测试：ProductManager 与 ProductRepository、UserRepository 的集成
class ProductManagerIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 创建测试用户
        admin = new Administrator(1, 1, "admin", "password");
        normalUser = new NormalUser(2, 2, "user", "password");
        userRepo.addUser(admin);
        userRepo.addUser(normalUser);
    }

    void TearDown() override {
        // 清理资源
        delete admin;
        delete normalUser;
    }

    ProductRepository productRepo;
    UserRepository userRepo;
    ProductManager manager{productRepo, userRepo};
    User* admin;
    User* normalUser;
};

TEST_F(ProductManagerIntegrationTest, PublishAndRetrieveProduct) {
    // 测试发布商品
    Product newProduct(0, "新商品", 1, "这是一个新发布的商品", 129.9, 2, "上海", 
                       QList<QString>() << "新商品", QDateTime::currentDateTime(), "active");
    bool publishResult = manager.publishProduct(newProduct, 2); // 使用普通用户ID为2
    EXPECT_TRUE(publishResult) << "商品应该成功发布";
    
    // 验证商品是否已保存
    QList<Product> allProducts = manager.getAllProducts();
    EXPECT_EQ(allProducts.size(), 1) << "应该有一个商品";
    if (allProducts.size() > 0) {
        EXPECT_EQ(allProducts[0].getTitle(), "新商品") << "商品标题应该为'新商品'";
        
        // 测试获取特定商品
        Product retrievedProduct = manager.getProduct(allProducts[0].getProductId());
        EXPECT_EQ(retrievedProduct.getProductId(), allProducts[0].getProductId()) << "获取的商品ID应该匹配";
    }
}

TEST_F(ProductManagerIntegrationTest, EditProduct) {
    // 先发布一个商品
    Product newProduct(0, "原始商品", 1, "这是一个原始商品", 129.9, 2, "上海", 
                       QList<QString>() << "原始", QDateTime::currentDateTime(), "active");
    bool publishResult = manager.publishProduct(newProduct, 2);
    ASSERT_TRUE(publishResult) << "商品应该成功发布";
    
    QList<Product> allProducts = manager.getAllProducts();
    ASSERT_GT(allProducts.size(), 0) << "应该有一个商品";
    
    // 测试编辑商品
    int productId = allProducts[0].getProductId();
    Product updatedProduct(0, "编辑后的商品", 1, "这是编辑后的商品", 149.9, 2, "北京", 
                          QList<QString>() << "编辑", QDateTime::currentDateTime(), "active");
    bool editResult = manager.editProduct(productId, updatedProduct, 2);
    EXPECT_TRUE(editResult) << "商品应该成功编辑";
    
    // 验证编辑结果
    Product editedProduct = manager.getProduct(productId);
    EXPECT_EQ(editedProduct.getTitle(), "编辑后的商品") << "商品标题应该更新为'编辑后的商品'";
}

TEST_F(ProductManagerIntegrationTest, DeleteProduct) {
    // 先发布一个商品
    Product newProduct(0, "待删除商品", 1, "这是一个待删除商品", 129.9, 2, "上海", 
                       QList<QString>() << "待删除", QDateTime::currentDateTime(), "active");
    bool publishResult = manager.publishProduct(newProduct, 2);
    ASSERT_TRUE(publishResult) << "商品应该成功发布";
    
    QList<Product> allProducts = manager.getAllProducts();
    ASSERT_GT(allProducts.size(), 0) << "应该有一个商品";
    
    // 测试删除商品
    int productId = allProducts[0].getProductId();
    bool deleteResult = manager.deleteProduct(productId, 2); // 用商品所有者删除
    EXPECT_TRUE(deleteResult) << "商品应该成功删除";
    
    // 验证删除结果
    Product verifyDeleted = manager.getProduct(productId);
    // 如果商品被正确删除，获取的商品应该不等于原始商品
    EXPECT_TRUE(verifyDeleted.getProductId() == 0 || 
                verifyDeleted.getTitle() != allProducts[0].getTitle()) << "商品应该已被删除";
}

TEST_F(ProductManagerIntegrationTest, PermissionControl) {
    // 发布一个普通用户商品
    Product normalUserProduct(0, "普通用户商品", 1, "普通用户发布的商品", 129.9, 2, "上海", 
                             QList<QString>() << "普通", QDateTime::currentDateTime(), "active");
    bool publishResult = manager.publishProduct(normalUserProduct, 2);
    ASSERT_TRUE(publishResult) << "普通用户商品应该成功发布";
    
    QList<Product> allProducts = manager.getAllProducts();
    ASSERT_GT(allProducts.size(), 0) << "应该有一个商品";
    
    // 测试权限控制 - 尝试用错误用户编辑商品
    int productId = allProducts[0].getProductId();
    Product unauthorizedEdit(0, "未授权编辑", 1, "这应该失败", 1.0, 1, "北京", 
                            QList<QString>(), QDateTime::currentDateTime(), "inactive");
    bool unauthorizedEditResult = manager.editProduct(productId, unauthorizedEdit, 1); // 管理员尝试编辑普通用户商品
    
    // 根据权限控制逻辑，这可能成功或失败，取决于具体实现
    // 假设只有商品所有者可以编辑，那么这个操作应该失败
    EXPECT_FALSE(unauthorizedEditResult) << "非商品所有者不应该能编辑商品";
}