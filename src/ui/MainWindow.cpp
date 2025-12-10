#include "MainWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>
#include "shop/ProductManager.h"
#include "shop/ProductRepository.h"
#include "shop/UserRepository.h"
#include "shop/NormalUser.h"
#include "shop/Administrator.h"

MainWindow::MainWindow(const QString& userType, int userId, QWidget* parent)
    : QMainWindow(parent)
    , m_userType(userType)
    , m_userId(userId)
    , productRepository(new ProductRepository())
    , userRepository(new UserRepository())
    , productManager(new ProductManager(*productRepository, *userRepository))
    , m_productListWidget(new ProductListWidget())
    , m_productEditWidget(nullptr)
{
    // 设置窗口标题
    setWindowTitle(QString("购物应用 - %1").arg(userType == "admin" ? "管理员" : "普通用户"));
    
    // 设置窗口大小
    resize(1000, 700);
    
    // 创建中央窗口部件
    setCentralWidget(m_productListWidget);
    
    // 检查用户是否存在，如果不存在则添加
    User* user = userRepository->findById(userId);
    if (!user) {
        if (userType == "admin") {
            user = new Administrator(userId, 1, QString("admin_%1").arg(userId), "password");
        } else {
            user = new NormalUser(userId, 2, QString("user_%1").arg(userId), "password");
        }
        userRepository->addUser(user);
        qDebug() << "Added new user with ID:" << userId;
    } else {
        qDebug() << "Found existing user with ID:" << userId;
    }
    
    // 创建菜单栏
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    
    // 创建文件菜单
    QMenu* fileMenu = menuBar->addMenu("文件");
    
    // 添加退出动作
    QAction* exitAction = fileMenu->addAction("退出");
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    
    // 如果是普通用户，添加发布商品菜单
    if (userType == "normal") {
        QMenu* productMenu = menuBar->addMenu("商品");
        QAction* publishAction = productMenu->addAction("发布商品");
        connect(publishAction, &QAction::triggered, this, &MainWindow::onPublishProduct);
    }
    // 如果是管理员，添加管理菜单
    else if (userType == "admin") {
        QMenu* manageMenu = menuBar->addMenu("管理");
        QAction* productManageAction = manageMenu->addAction("商品管理");
        connect(productManageAction, &QAction::triggered, this, [=]() {
            QMessageBox::information(this, "提示", "商品管理功能待实现");
        });
    }

    // 加载商品数据
    loadProducts();
}

MainWindow::~MainWindow() 
{
    if (!productRepository->saveToFile())
        qDebug() << "保存商品数据失败";
    
    if (!userRepository->saveToJsonFile())
        qDebug() << "保存用户数据失败";

    qDebug() << "保存成功";

    delete productManager;
    delete productRepository;
    delete userRepository;
}

void MainWindow::loadProducts()
{
    // 清空现有商品
    m_productListWidget->clearProducts();
    
    // 获取所有商品并添加到列表
    QList<Product> products = productManager->getAllProducts();
    
    for (const Product& product : products) {
        m_productListWidget->addProduct(product);
    }
}

void MainWindow::onPublishProduct()
{
    // 创建发布商品的对话框
    m_productEditWidget = new ProductEditWidget(this);
    
    // 创建模态对话框包装
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("发布新商品");
    dialog->resize(400, 350);
    
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(m_productEditWidget);
    
    // 连接信号
    connect(m_productEditWidget, &ProductEditWidget::productSaved, this, [=](const Product& product) {
        // 设置商品ID和卖家ID
        Product newProduct = product;
        newProduct.setProductId(productRepository->generateNextId());
        newProduct.setSellerId(m_userId);
        
        // 添加到仓库
        if (productRepository->save(newProduct)) {
            // 添加到列表显示
            m_productListWidget->addProduct(newProduct);
            dialog->accept();
            QMessageBox::information(this, "成功", "商品发布成功！");
        } else {
            QMessageBox::warning(this, "失败", "商品发布失败！");
        }
    });
    
    connect(m_productEditWidget, &ProductEditWidget::cancelled, dialog, &QDialog::reject);
    
    // 显示对话框
    dialog->exec();
    
    // 清理资源
    dialog->deleteLater();
    m_productEditWidget = nullptr;
}