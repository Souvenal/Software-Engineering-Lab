#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "ui/ProductListWidget.h"
#include "shop/ProductRepository.h"
#include "shop/UserRepository.h"
#include "shop/ProductManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& userType, int userId, QWidget* parent = nullptr);
    ~MainWindow();

private:
    void loadProducts();

    QString m_userType;
    int m_userId;
    ProductRepository* productRepository;
    UserRepository* userRepository;
    ProductManager* productManager;
    ProductListWidget* m_productListWidget;
};

#endif // MAINWINDOW_H