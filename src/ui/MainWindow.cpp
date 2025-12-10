#include "MainWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "shop/ProductManager.h"
#include "shop/ProductRepository.h"
#include "shop/UserRepository.h"

MainWindow::MainWindow(const QString& userType, int userId, QWidget* parent)
    : QMainWindow(parent)
    , m_userType(userType)
    , m_userId(userId)
    , productRepository(new ProductRepository())
    , userRepository(new UserRepository())
    , productManager(new ProductManager(*productRepository, *userRepository))
    , m_productListWidget(new ProductListWidget())
{
    // 设置窗口标题
    setWindowTitle(QString("购物应用 - %1").arg(userType == "admin" ? "管理员" : "普通用户"));
    
    // 设置窗口大小
    resize(1000, 700);
    
    // 创建中央窗口部件
    setCentralWidget(m_productListWidget);
    
    // 创建菜单栏
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    
    // 创建文件菜单
    QMenu* fileMenu = menuBar->addMenu("文件");
    
    // 添加退出动作
    QAction* exitAction = fileMenu->addAction("退出");
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    
    // 如果是管理员，添加管理菜单
    if (userType == "admin") {
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