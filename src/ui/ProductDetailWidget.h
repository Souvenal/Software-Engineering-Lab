#ifndef PRODUCTDETAILWIDGET_H
#define PRODUCTDETAILWIDGET_H

#include <QWidget>
#include "shop/Product.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

class ProductDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductDetailWidget(const Product& product, QWidget *parent = nullptr);
    ~ProductDetailWidget();

private:
    Product product;
    
    // UI控件
    QLabel *titleLabel;
    QLabel *productIdLabel;
    QLabel *categoryIdLabel;
    QLabel *priceLabel;
    QLabel *sellerIdLabel;
    QLabel *locationLabel;
    QLabel *statusLabel;
    QTextEdit *descriptionTextEdit;
    QLabel *publicTimeLabel;
    QPushButton *closeButton;
};

#endif // PRODUCTDETAILWIDGET_H