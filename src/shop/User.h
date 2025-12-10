#ifndef USER_H
#define USER_H

#include <QString>

/**
 * @brief 用户基类
 * 
 * User类是所有用户的基类，包含了用户的基本属性和方法
 */
class User {
public:
    /**
     * @brief 构造函数
     * @param userId 用户ID
     * @param roleId 角色ID
     * @param username 用户名
     * @param password 密码
     */
    User(int userId, int roleId, const QString& username, const QString& password);

    /**
     * @brief 用户登录
     * @return 登录成功返回true，否则返回false
     */
    bool login();

    /**
     * @brief 用户登出
     */
    void logout();

    // Getters
    int getUserId() const;
    int getRoleId() const;
    QString getUsername() const;
    QString getPassword() const;

protected:
    int userId;      ///< 用户ID
    int roleId;      ///< 角色ID
    QString username; ///< 用户名
    QString password; ///< 密码
};

#endif // USER_H