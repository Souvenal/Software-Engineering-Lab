#ifndef PRODUCTEDITWIDGET_H
#define PRODUCTEDITWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QList>
#include <QDateTime>
#include "shop/Product.h"

class ProductEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductEditWidget(QWidget *parent = nullptr);
    explicit ProductEditWidget(const Product& product, QWidget *parent = nullptr);
    ~ProductEditWidget();

    Product getProduct() const;
    void setProduct(const Product& product);

signals:
    void productSaved(const Product& product);
    void cancelled();

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    void setupUI();
    void updateProductFromUI();
    void updateUIFromProduct();

    Product product;
    bool isNewProduct;

    // UI控件
    QLineEdit *titleEdit;
    QSpinBox *categoryIdSpinBox;
    QTextEdit *descriptionTextEdit;
    QDoubleSpinBox *priceSpinBox;
    QLineEdit *locationEdit;
    QLineEdit *tagsEdit;  // 用逗号分隔的标签
    QComboBox *statusCombo;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif // PRODUCTEDITWIDGET_H