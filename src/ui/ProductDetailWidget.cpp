#include "ProductDetailWidget.h"
#include <QDateTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFont>
#include <QFrame>
#include "shop/Product.h"

ProductDetailWidget::ProductDetailWidget(const Product& product, QWidget *parent) :
    QWidget(parent),
    product(product),
    titleLabel(new QLabel(product.getTitle())),
    productIdLabel(new QLabel(QString::number(product.getProductId()))),
    categoryIdLabel(new QLabel(QString::number(product.getCategoryId()))),
    priceLabel(new QLabel(QString("¥%1").arg(product.getPrice()))),
    sellerIdLabel(new QLabel(QString::number(product.getSellerId()))),
    locationLabel(new QLabel(product.getLocation())),
    statusLabel(new QLabel(product.getStatus())),
    descriptionTextEdit(new QTextEdit()),
    publicTimeLabel(new QLabel(product.getPublicTime().toString("yyyy-MM-dd hh:mm:ss"))),
    closeButton(new QPushButton("关闭"))
{
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    
    // 创建表单布局的标签和值
    QLabel* productIdTextLabel = new QLabel("商品ID:");
    
    QLabel* categoryIdTextLabel = new QLabel("分类ID:");
    
    QLabel* priceTextLabel = new QLabel("价格:");
    
    QLabel* sellerIdTextLabel = new QLabel("卖家ID:");
    
    QLabel* locationTextLabel = new QLabel("地址:");
    
    QLabel* statusTextLabel = new QLabel("状态:");
    
    QLabel* publicTimeTextLabel = new QLabel("发布时间:");
    
    // 描述文本框
    descriptionTextEdit->setText(product.getDescription());
    descriptionTextEdit->setReadOnly(true);
    
    // 隐藏关闭按钮
    closeButton->hide();
    
    // 创建表单布局
    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(productIdTextLabel, productIdLabel);
    formLayout->addRow(categoryIdTextLabel, categoryIdLabel);
    formLayout->addRow(priceTextLabel, priceLabel);
    formLayout->addRow(sellerIdTextLabel, sellerIdLabel);
    formLayout->addRow(locationTextLabel, locationLabel);
    formLayout->addRow(statusTextLabel, statusLabel);
    formLayout->addRow(publicTimeTextLabel, publicTimeLabel);
    formLayout->addRow("描述:", descriptionTextEdit);
    
    // 创建垂直布局
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(line);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(closeButton);
    
    setLayout(mainLayout);
    
    // 设置窗口标题
    setWindowTitle(QString("商品详情 - %1").arg(product.getTitle()));
}

ProductDetailWidget::~ProductDetailWidget()
{
    // 控件会随父对象自动删除，无需手动释放
}
