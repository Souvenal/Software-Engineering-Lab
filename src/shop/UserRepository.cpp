#include "UserRepository.h"
#include "ConfigManager.h"
#include "User.h"
#include "Administrator.h"
#include "NormalUser.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

/**
 * @brief UserRepository默认构造函数
 */
UserRepository::UserRepository() {
    // 尝试从文件加载数据
    loadFromJsonFile();
    
    // 如果没有数据，则初始化一些测试用户数据
    if (users.isEmpty()) {
        User* admin = new Administrator(1, 1, "admin", "admin123");
        users.insert(1, admin);
        
        User* normalUser = new NormalUser(2, 2, "user1", "user123");
        users.insert(2, normalUser);
        
        // 保存初始数据到文件
        saveToJsonFile();
    }
}

/**
 * @brief 根据用户ID查找用户
 * @param userId 用户ID
 * @return 用户对象指针
 */
User* UserRepository::findById(int userId) const {
    if (users.contains(userId)) {
        return users.value(userId);
    }
    return nullptr;
}

/**
 * @brief 检查用户角色
 * @param userId 用户ID
 * @param role 角色名称
 * @return 角色匹配返回true，否则返回false
 */
bool UserRepository::checkUserRole(int userId, const QString& role) const {
    User* user = findById(userId);
    if (!user) return false;
    
    if (role == "admin") {
        return user->getRoleId() == 1;
    } else if (role == "normal") {
        return user->getRoleId() != 1;
    }
    return false;
}

/**
 * @brief 添加用户
 * @param user 用户指针
 */
void UserRepository::addUser(User* user) {
    if (user) {
        users.insert(user->getUserId(), user);
        saveToJsonFile();
    }
}

/**
 * @brief 获取所有用户
 * @return 用户列表
 */
QList<User*> UserRepository::getAllUsers() const {
    return users.values();
}

/**
 * @brief 验证用户凭据
 * @param username 用户名
 * @param password 密码
 * @return 用户对象指针，验证失败返回nullptr
 */
User* UserRepository::validateUser(const QString& username, const QString& password) const {
    for (User* user : users) {
        if (user->getUsername() == username && user->getPassword() == password) {
            return user;
        }
    }
    return nullptr;
}

/**
 * @brief 从JSON字符串加载用户信息
 * @param json JSON字符串
 * * @return 加载成功返回true，否则返回false
 */
bool UserRepository::loadFromJson(const QString& json) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(), &error);
    
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
            User* user = createUserFromJson(obj);
            if (user) {
                users.insert(user->getUserId(), user);
            }
        }
    }
    
    return true;
}

/**
 * @brief 将用户信息导出为JSON字符串
 * @return JSON字符串
 */
QString UserRepository::dumpToJson() const {
    QJsonArray array;
    for (User* user : users) {
        array.append(userToJson(user));
    }
    
    QJsonDocument doc(array);
    return doc.toJson(QJsonDocument::Compact);
}

/**
 * @brief 从JSON对象创建用户
 * @param obj JSON对象
 * @return 用户指针
 */
User* UserRepository::createUserFromJson(const QJsonObject& obj) {
    int userId = obj["userId"].toInt();
    int roleId = obj["roleId"].toInt();
    QString username = obj["username"].toString();
    QString password = obj["password"].toString();
    
    if (roleId == 1) {
        // 管理员
        return new Administrator(userId, roleId, username, password);
    } else {
        // 普通用户
        return new NormalUser(userId, roleId, username, password);
    }
}

/**
 * @brief 将用户转换为JSON对象
 * @param user 用户指针
 * @return JSON对象
 */
QJsonObject UserRepository::userToJson(User* user) {
    QJsonObject obj;
    obj["userId"] = user->getUserId();
    obj["roleId"] = user->getRoleId();
    obj["username"] = user->getUsername();
    obj["password"] = user->getPassword();
    return obj;
}

/**
 * @brief 从JSON文件加载数据
 * @return 加载成功返回true，否则返回false
 */
bool UserRepository::loadFromJsonFile() {
    QString fileName = ConfigManager::getUserDataFile();
    QFile file(fileName);
    
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for reading:" << fileName;
        return false;
    }
    
    QString json = file.readAll();
    file.close();
    
    return loadFromJson(json);
}

/**
 * @brief 保存数据到JSON文件
 * @return 保存成功返回true，否则返回false
 */
bool UserRepository::saveToJsonFile() {
    QString fileName = ConfigManager::getUserDataFile();
    QFile file(fileName);
    
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file for writing:" << fileName;
        return false;
    }
    
    QString json = dumpToJson();
    file.write(json.toUtf8());
    file.close();
    
    return true;
}