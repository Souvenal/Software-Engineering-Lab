#include <gtest/gtest.h>
#include <QList>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QDir>
#include <QApplication>

#include "ConfigManager.h"
#include "Product.h"
#include "UserRepository.h"
#include "User.h"
#include "NormalUser.h"
#include "Administrator.h"

// 临时文件路径
const QString TEMP_USER_FILE = QDir::tempPath() + "/test_users.json";

class ProductTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 初始化测试数据
        tags << "tag1" << "tag2" << "tag3";
        time = QDateTime::currentDateTime();
    }

    void TearDown() override {
        // 清理资源
    }

    QList<QString> tags;
    QDateTime time;
};

class UserRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 创建一个干净的UserRepository实例
        repo = new UserRepository();
    }

    void TearDown() override {
        // 清理资源
        delete repo;
        
        // 删除临时文件
        QFile::remove(TEMP_USER_FILE);
    }

    UserRepository* repo;
};

// Product类测试 - 默认构造函数
TEST_F(ProductTest, DefaultConstructor) {
    Product product;
    EXPECT_EQ(product.getProductId(), 0);
    EXPECT_EQ(product.getTitle(), "");
    EXPECT_EQ(product.getCategoryId(), 0);
    EXPECT_EQ(product.getPrice(), 0.0);
    EXPECT_EQ(product.getSellerId(), 0);
    EXPECT_EQ(product.getDescription(), "");
    EXPECT_EQ(product.getLocation(), "");
    EXPECT_EQ(product.getStatus(), "");
    EXPECT_EQ(product.getPublicTime(), QDateTime());
    EXPECT_TRUE(product.getTags().isEmpty());
}

// Product类测试 - 参数构造函数
TEST_F(ProductTest, ParameterizedConstructor) {
    Product product(1, "Test Product", 2, "A test product", 99.99, 100, "Beijing", tags, time, "active");
    
    EXPECT_EQ(product.getProductId(), 1);
    EXPECT_EQ(product.getTitle(), "Test Product");
    EXPECT_EQ(product.getCategoryId(), 2);
    EXPECT_EQ(product.getPrice(), 99.99);
    EXPECT_EQ(product.getSellerId(), 100);
    EXPECT_EQ(product.getDescription(), "A test product");
    EXPECT_EQ(product.getLocation(), "Beijing");
    EXPECT_EQ(product.getStatus(), "active");
    EXPECT_EQ(product.getPublicTime(), time);
    EXPECT_EQ(product.getTags().size(), 3);
    EXPECT_EQ(product.getTags()[0], "tag1");
    EXPECT_EQ(product.getTags()[1], "tag2");
    EXPECT_EQ(product.getTags()[2], "tag3");
}

// Product类测试 - Getter和Setter
TEST_F(ProductTest, GettersSetters) {
    Product product;
    
    product.setProductId(5);
    product.setTitle("New Title");
    product.setCategoryId(3);
    product.setPrice(150.50);
    product.setSellerId(200);
    product.setDescription("New Description");
    product.setLocation("Shanghai");
    product.setStatus("inactive");
    product.setPublicTime(time);
    product.setTags(tags);
    
    EXPECT_EQ(product.getProductId(), 5);
    EXPECT_EQ(product.getTitle(), "New Title");
    EXPECT_EQ(product.getCategoryId(), 3);
    EXPECT_EQ(product.getPrice(), 150.50);
    EXPECT_EQ(product.getSellerId(), 200);
    EXPECT_EQ(product.getDescription(), "New Description");
    EXPECT_EQ(product.getLocation(), "Shanghai");
    EXPECT_EQ(product.getStatus(), "inactive");
    EXPECT_EQ(product.getPublicTime(), time);
    EXPECT_EQ(product.getTags().size(), 3);
    EXPECT_EQ(product.getTags()[0], "tag1");
    EXPECT_EQ(product.getTags()[1], "tag2");
    EXPECT_EQ(product.getTags()[2], "tag3");
}

// Product类测试 - JSON序列化
TEST_F(ProductTest, JsonSerialization) {
    Product original(1, "Test Product", 2, "A test product", 99.99, 100, "Beijing", tags, time, "active");
    
    QJsonObject json = Product::toJson(original);
    Product deserialized = Product::fromJson(json);
    
    EXPECT_EQ(deserialized.getProductId(), original.getProductId());
    EXPECT_EQ(deserialized.getTitle(), original.getTitle());
    EXPECT_EQ(deserialized.getCategoryId(), original.getCategoryId());
    EXPECT_EQ(deserialized.getPrice(), original.getPrice());
    EXPECT_EQ(deserialized.getSellerId(), original.getSellerId());
    EXPECT_EQ(deserialized.getDescription(), original.getDescription());
    EXPECT_EQ(deserialized.getLocation(), original.getLocation());
    EXPECT_EQ(deserialized.getStatus(), original.getStatus());
    EXPECT_EQ(deserialized.getTags().size(), original.getTags().size());
    EXPECT_EQ(deserialized.getPublicTime(), original.getPublicTime());
}

// Product类测试 - JSON序列化边界情况
TEST_F(ProductTest, JsonSerializationEdgeCases) {
    // 测试空值情况
    Product emptyProduct;
    QJsonObject emptyJson = Product::toJson(emptyProduct);
    Product emptyDeserialized = Product::fromJson(emptyJson);
    
    EXPECT_EQ(emptyDeserialized.getProductId(), 0);
    EXPECT_EQ(emptyDeserialized.getTitle(), "");
    EXPECT_EQ(emptyDeserialized.getPrice(), 0.0);
    EXPECT_EQ(emptyDeserialized.getTags().size(), 0);
    
    // 测试特殊字符
    Product specialProduct(1, "Title with \"quotes\" and\nnewlines", 1, 
                          "Description with & special <chars>", 99.99, 1, 
                          "Location with &", QList<QString>(), QDateTime(), "status");
    
    QJsonObject specialJson = Product::toJson(specialProduct);
    Product specialDeserialized = Product::fromJson(specialJson);
    
    EXPECT_EQ(specialDeserialized.getTitle(), specialProduct.getTitle());
    EXPECT_EQ(specialDeserialized.getDescription(), specialProduct.getDescription());
}

// Product类测试 - 大数值测试
TEST_F(ProductTest, LargeValues) {
    Product product(999999, "Large Product", 999999, "A large test product", 999999.99, 999999, "Beijing", tags, time, "active");
    
    EXPECT_EQ(product.getProductId(), 999999);
    EXPECT_EQ(product.getTitle(), "Large Product");
    EXPECT_EQ(product.getCategoryId(), 999999);
    EXPECT_EQ(product.getPrice(), 999999.99);
    EXPECT_EQ(product.getSellerId(), 999999);
}

// UserRepository类测试 - 默认构造函数
TEST_F(UserRepositoryTest, DefaultConstructor) {
    EXPECT_TRUE(repo->getAllUsers().isEmpty());
}

// UserRepository类测试 - 添加和查找用户
TEST_F(UserRepositoryTest, AddAndFindUser) {
    User* user = new NormalUser(1, 2, "testuser", "password");
    repo->addUser(user);
    
    User* found = repo->findById(1);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->getUserId(), 1);
    EXPECT_EQ(found->getUsername(), "testuser");
    EXPECT_EQ(found->getRoleId(), 2);
}

// UserRepository类测试 - 检查用户角色
TEST_F(UserRepositoryTest, CheckUserRole) {
    User* admin = new Administrator(1, 1, "admin", "password");
    User* normal = new NormalUser(2, 2, "normal", "password");
    
    repo->addUser(admin);
    repo->addUser(normal);
    
    EXPECT_TRUE(repo->checkUserRole(1, "admin"));
    EXPECT_FALSE(repo->checkUserRole(2, "admin"));
    EXPECT_FALSE(repo->checkUserRole(1, "normal"));
    EXPECT_TRUE(repo->checkUserRole(2, "normal"));
    EXPECT_FALSE(repo->checkUserRole(999, "admin"));  // 不存在的用户
    EXPECT_FALSE(repo->checkUserRole(1, "invalid_role"));  // 无效角色
}

// UserRepository类测试 - 验证用户凭据
TEST_F(UserRepositoryTest, ValidateUser) {
    User* user = new NormalUser(1, 2, "testuser", "password");
    repo->addUser(user);
    
    // 正确的用户名和密码
    User* validUser = repo->validateUser("testuser", "password");
    EXPECT_NE(validUser, nullptr);
    EXPECT_EQ(validUser->getUserId(), 1);
    
    // 错误的用户名
    User* invalidUser1 = repo->validateUser("wronguser", "password");
    EXPECT_EQ(invalidUser1, nullptr);
    
    // 错误的密码
    User* invalidUser2 = repo->validateUser("testuser", "wrongpass");
    EXPECT_EQ(invalidUser2, nullptr);
    
    // 用户名和密码都错误
    User* invalidUser3 = repo->validateUser("wronguser", "wrongpass");
    EXPECT_EQ(invalidUser3, nullptr);
}

// UserRepository类测试 - 获取所有用户
TEST_F(UserRepositoryTest, GetAllUsers) {
    User* user1 = new NormalUser(1, 2, "user1", "password1");
    User* user2 = new Administrator(2, 1, "admin", "password2");
    User* user3 = new NormalUser(3, 2, "user3", "password3");
    
    repo->addUser(user1);
    repo->addUser(user2);
    repo->addUser(user3);
    
    QList<User*> allUsers = repo->getAllUsers();
    EXPECT_EQ(allUsers.size(), 3);
    
    // 检查是否包含所有用户
    bool hasUser1 = false, hasUser2 = false, hasUser3 = false;
    for (User* u : allUsers) {
        if (u->getUserId() == 1) hasUser1 = true;
        if (u->getUserId() == 2) hasUser2 = true;
        if (u->getUserId() == 3) hasUser3 = true;
    }
    EXPECT_TRUE(hasUser1 && hasUser2 && hasUser3);
}

// UserRepository类测试 - JSON序列化和反序列化
TEST_F(UserRepositoryTest, JsonSerialization) {
    User* user1 = new NormalUser(1, 2, "user1", "password1");
    User* user2 = new Administrator(2, 1, "admin", "password2");
    
    repo->addUser(user1);
    repo->addUser(user2);
    
    QString jsonStr = repo->dumpToJson();
    EXPECT_FALSE(jsonStr.isEmpty());
    
    // 创建新的仓库实例并加载JSON
    UserRepository newRepo;
    bool result = newRepo.loadFromJson(jsonStr);
    EXPECT_TRUE(result);
    
    User* loadedUser1 = newRepo.findById(1);
    EXPECT_NE(loadedUser1, nullptr);
    EXPECT_EQ(loadedUser1->getUserId(), 1);
    EXPECT_EQ(loadedUser1->getUsername(), "user1");
    EXPECT_EQ(loadedUser1->getRoleId(), 2);
    
    User* loadedUser2 = newRepo.findById(2);
    EXPECT_NE(loadedUser2, nullptr);
    EXPECT_EQ(loadedUser2->getUserId(), 2);
    EXPECT_EQ(loadedUser2->getUsername(), "admin");
    EXPECT_EQ(loadedUser2->getRoleId(), 1);
}

// UserRepository类测试 - 无效JSON处理
TEST_F(UserRepositoryTest, InvalidJsonHandling) {
    // 无效JSON
    bool result1 = repo->loadFromJson("invalid json");
    EXPECT_FALSE(result1);
    
    // 不是数组的JSON
    bool result2 = repo->loadFromJson("{\"not\":\"an array\"}");
    EXPECT_FALSE(result2);
    
    // 空数组
    bool result3 = repo->loadFromJson("[]");
    EXPECT_TRUE(result3);
    EXPECT_TRUE(repo->getAllUsers().isEmpty());
}

// UserRepository类测试 - 添加空用户
TEST_F(UserRepositoryTest, AddNullUser) {
    repo->addUser(nullptr);
    EXPECT_TRUE(repo->getAllUsers().isEmpty());
}

// UserRepository类测试 - 查找不存在的用户
TEST_F(UserRepositoryTest, FindNonExistentUser) {
    User* nonExistent = repo->findById(999);
    EXPECT_EQ(nonExistent, nullptr);
}

// UserRepository类测试 - 从JSON创建用户
TEST_F(UserRepositoryTest, CreateUserFromJson) {
    QJsonObject adminObj;
    adminObj["userId"] = 1;
    adminObj["roleId"] = 1;
    adminObj["username"] = "admin";
    adminObj["password"] = "password";
    
    User* admin = repo->createUserFromJson(adminObj);
    ASSERT_NE(admin, nullptr);
    EXPECT_EQ(admin->getUserId(), 1);
    EXPECT_EQ(admin->getRoleId(), 1);
    EXPECT_EQ(admin->getUsername(), "admin");
    EXPECT_EQ(admin->getPassword(), "password");
    EXPECT_EQ(typeid(*admin).name(), typeid(Administrator).name()); // 验证类型
    
    QJsonObject normalObj;
    normalObj["userId"] = 2;
    normalObj["roleId"] = 2;
    normalObj["username"] = "normal";
    normalObj["password"] = "password";
    
    User* normal = repo->createUserFromJson(normalObj);
    ASSERT_NE(normal, nullptr);
    EXPECT_EQ(normal->getUserId(), 2);
    EXPECT_EQ(normal->getRoleId(), 2);
    EXPECT_EQ(normal->getUsername(), "normal");
    EXPECT_EQ(normal->getPassword(), "password");
    EXPECT_EQ(typeid(*normal).name(), typeid(NormalUser).name()); // 验证类型
    
    delete admin;
    delete normal;
}

// 新增测试：测试内存泄漏
TEST_F(UserRepositoryTest, MemoryManagement) {
    // 创建用户并添加到仓库
    User* user = new NormalUser(1, 2, "testuser", "password");
    repo->addUser(user);
    
    // 验证用户存在
    User* found = repo->findById(1);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->getUserId(), 1);
    
    // 测试不需要显式删除found，因为它是repo内部管理的指针
    // repo析构函数会清理所有用户对象
}

// 新增测试：测试大量数据处理
TEST_F(UserRepositoryTest, LargeDataSet) {
    const int USER_COUNT = 1000;
    
    // 添加大量用户
    for(int i = 1; i <= USER_COUNT; i++) {
        User* user = new NormalUser(i, 2, QString("user%1").arg(i), "password");
        repo->addUser(user);
    }
    
    // 验证用户数量
    EXPECT_EQ(repo->getAllUsers().size(), USER_COUNT);
    
    // 验证能正确找到特定用户
    User* found = repo->findById(USER_COUNT/2);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getUsername(), QString("user%1").arg(USER_COUNT/2));
}

// 新增测试：性能测试
TEST_F(ProductTest, PerformanceTest) {
    // 测试大量Product对象的创建和序列化性能
    const int PRODUCT_COUNT = 10000;
    QList<Product> products;
    
    auto startTime = QDateTime::currentDateTime();
    
    // 创建大量产品对象
    for(int i = 0; i < PRODUCT_COUNT; i++) {
        Product p(i, QString("Product %1").arg(i), 1, "Description", 10.0 + i, 1, "Location", 
                 QList<QString>() << "tag1", QDateTime::currentDateTime(), "active");
        products.append(p);
    }
    
    auto endTime = QDateTime::currentDateTime();
    auto creationTime = startTime.msecsTo(endTime);
    std::cout << "创建 " << PRODUCT_COUNT << " 个Product对象耗时: " << creationTime << " ms" << std::endl;
    
    startTime = QDateTime::currentDateTime();
    
    // 序列化和反序列化测试
    for(int i = 0; i < 100; i++) {
        QJsonObject json = Product::toJson(products[i]);
        Product deserialized = Product::fromJson(json);
        EXPECT_EQ(deserialized.getProductId(), products[i].getProductId());
    }
    
    endTime = QDateTime::currentDateTime();
    auto serializationTime = startTime.msecsTo(endTime);
    std::cout << "序列化和反序列化 100 个Product对象耗时: " << serializationTime << " ms" << std::endl;
}

// 新增测试：边界值测试
TEST_F(UserRepositoryTest, BoundaryValues) {
    // 测试大数值ID
    User* user = new NormalUser(999999, 999999, "largeiduser", "password");
    repo->addUser(user);
    
    User* found = repo->findById(999999);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getUserId(), 999999);
    EXPECT_EQ(found->getRoleId(), 999999);
    EXPECT_EQ(found->getUsername(), "largeiduser");
}
