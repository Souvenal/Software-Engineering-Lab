#include "User.h"

/**
 * @brief User构造函数
 * @param userId 用户ID
 * @param roleId 角色ID
 * @param username 用户名
 * @param password 密码
 */
User::User(int userId, int roleId, const QString& username, const QString& password)
    : userId(userId), roleId(roleId), username(username), password(password) {
}

/**
 * @brief 用户登录方法
 * @return 登录成功返回true，否则返回false
 */
bool User::login() {
    // 简单实现，实际应用中需要更复杂的认证逻辑
    return !username.isEmpty() && !password.isEmpty();
}

/**
 * @brief 用户登出方法
 */
void User::logout() {
    // 登出逻辑，此处为空实现
}

/**
 * @brief 获取用户ID
 * @return 用户ID
 */
int User::getUserId() const {
    return userId;
}

/**
 * @brief 获取角色ID
 * @return 角色ID
 */
int User::getRoleId() const {
    return roleId;
}

/**
 * @brief 获取用户名
 * @return 用户名
 */
QString User::getUsername() const {
    return username;
}

/**
 * @brief 获取密码
 * @return 密码
 */
QString User::getPassword() const {
    return password;
}