#ifndef PRODUCTLISTWIDGET_H
#define PRODUCTLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QEvent>
#include <QStackedWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include "shop/Product.h"
#include "ui/ProductDetailWidget.h"

class ProductListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductListWidget(QWidget *parent = nullptr);
    ~ProductListWidget();

    // 添加商品到列表
    void addProduct(const Product& product);
    
    // 清空商品列表
    void clearProducts();

protected:
    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onCloseButtonClicked();
    void onProductClicked(int index);
    void onBackButtonClicked();

private:
    QStackedWidget *stackedWidget;
    QWidget *productListPage;
    QScrollArea *scrollArea;
    QVBoxLayout *productListLayout;
    QVector<Product> products;
    
    // 添加一个详情页面的指针
    ProductDetailWidget *productDetailWidget;
    
    // 创建商品显示控件
    QWidget* createProductWidget(const Product& product, int index);
};

#endif // PRODUCTLISTWIDGET_H