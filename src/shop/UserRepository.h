#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "shop/User.h"
#include <QHash>
#include <QList>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

/**
 * @brief 用户仓库类
 * 
 * UserRepository类负责用户数据的持久化操作，
 * 提供查找用户、检查用户角色以及JSON序列化等方法
 */
class UserRepository {
public:
    /**
     * @brief 默认构造函数
     */
    UserRepository();

    /**
     * @brief 根据用户ID查找用户
     * @param userId 用户ID
     * @return 用户对象指针
     */
    User* findById(int userId) const;

    /**
     * @brief 检查用户角色
     * @param userId 用户ID
     * @param role 角色名称
     * @return 角色匹配返回true，否则返回false
     */
    bool checkUserRole(int userId, const QString& role) const;

    /**
     * @brief 添加用户
     * @param user 用户指针
     */
    void addUser(User* user);

    /**
     * @brief 获取所有用户
     * @return 用户列表
     */
    QList<User*> getAllUsers() const;

    /**
     * @brief 验证用户凭据
     * @param username 用户名
     * @param password 密码
     * @return 用户对象指针，验证失败返回nullptr
     */
    User* validateUser(const QString& username, const QString& password) const;

    /**
     * @brief 从JSON字符串加载用户信息
     * @param json JSON字符串
     * @return 加载成功返回true，否则返回false
     */
    bool loadFromJson(const QString& json);

    /**
     * @brief 将用户信息导出为JSON字符串
     * @return JSON字符串
     */
    QString dumpToJson() const;

    /**
     * @brief 从JSON对象创建用户
     * @param obj JSON对象
     * @return 用户指针
     */
    static User* createUserFromJson(const QJsonObject& obj);

    /**
     * @brief 将用户转换为JSON对象
     * @param user 用户指针
     * @return JSON对象
     */
    static QJsonObject userToJson(User* user);

    /**
     * @brief 从JSON文件加载数据
     * @return 加载成功返回true，否则返回false
     */
    bool loadFromJsonFile();

    /**
     * @brief 保存数据到JSON文件
     * @return 保存成功返回true，否则返回false
     */
    bool saveToJsonFile();

private:
    QHash<int, User*> users; ///< 用户存储哈希表，键为用户ID
};

#endif // USERREPOSITORY_H