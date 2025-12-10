#include "ProductListWidget.h"
#include "ProductDetailWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QString>
#include <QMouseEvent>
#include <QScrollArea>
#include <QStackedWidget>
#include <QApplication>

ProductListWidget::ProductListWidget(QWidget *parent) :
    QWidget(parent),
    stackedWidget(new QStackedWidget()),
    productListPage(new QWidget()),
    scrollArea(new QScrollArea()),
    productListLayout(new QVBoxLayout()),
    productDetailWidget(nullptr)
{
    // 设置滚动区域
    scrollArea->setWidgetResizable(true);
    QWidget* contentWidget = new QWidget();
    contentWidget->setLayout(productListLayout);
    scrollArea->setWidget(contentWidget);
    
    // 创建页面布局
    QVBoxLayout* pageLayout = new QVBoxLayout();
    QLabel* titleLabel = new QLabel("商品列表");
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    titleLabel->setFont(font);
    titleLabel->setAlignment(Qt::AlignCenter);
    
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    
    pageLayout->addWidget(titleLabel);
    pageLayout->addWidget(line);
    pageLayout->addWidget(scrollArea);
    
    productListPage->setLayout(pageLayout);
    stackedWidget->addWidget(productListPage);
    
    // 创建主布局
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}

ProductListWidget::~ProductListWidget()
{
    // 控件会随父对象自动删除，无需手动释放
}

void ProductListWidget::addProduct(const Product& product)
{
    products.append(product);
    
    // 创建商品显示控件并添加到布局中
    QWidget* productWidget = createProductWidget(product, products.size() - 1);
    productListLayout->addWidget(productWidget);
}

void ProductListWidget::clearProducts()
{
    // 清空布局中的所有控件
    QLayoutItem* item;
    while ((item = productListLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    
    products.clear();
}

QWidget* ProductListWidget::createProductWidget(const Product& product, int index)
{
    // 创建商品显示框架
    QFrame* frame = new QFrame();
    frame->setFrameStyle(QFrame::Box);
    frame->setLineWidth(1);
    frame->setCursor(Qt::PointingHandCursor); // 设置鼠标手势为手型，表示可点击
    
    // 为框架添加一个属性来存储商品索引
    frame->setProperty("productIndex", index);
    
    // 创建主布局
    QHBoxLayout* mainLayout = new QHBoxLayout(frame);
    
    // 创建信息布局
    QVBoxLayout* infoLayout = new QVBoxLayout();
    
    // 商品标题
    QString title = product.getTitle();
    QLabel* titleLabel = new QLabel(QString("<b>%1</b>").arg(title));
    titleLabel->setStyleSheet("font-size: 16px;");
    
    // 商品描述
    QString description = product.getDescription();
    QLabel* descLabel = new QLabel(description);
    descLabel->setWordWrap(true);
    
    // 商品价格
    QLabel* priceLabel = new QLabel(QString("价格: ¥%1").arg(product.getPrice()));
    priceLabel->setStyleSheet("color: red; font-weight: bold;");
    
    // 商品位置
    QString location = product.getLocation();
    QLabel* locationLabel = new QLabel(QString("位置: %1").arg(location));
    
    // 商品状态
    QString status = product.getStatus();
    QLabel* statusLabel = new QLabel(QString("状态: %1").arg(status));
    
    // 添加到信息布局
    infoLayout->addWidget(titleLabel);
    infoLayout->addWidget(descLabel);
    infoLayout->addWidget(priceLabel);
    infoLayout->addWidget(locationLabel);
    infoLayout->addWidget(statusLabel);
    
    // 添加到主布局
    mainLayout->addLayout(infoLayout);
    
    // 安装事件过滤器以捕获鼠标点击事件
    frame->installEventFilter(this);
    
    // 设置框架的最小高度以确保可点击区域足够大
    frame->setMinimumHeight(100);
    
    return frame;
}

bool ProductListWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QWidget *widget = qobject_cast<QWidget*>(obj);
            if (widget) {
                QVariant indexVariant = widget->property("productIndex");
                if (indexVariant.isValid()) {
                    int index = indexVariant.toInt();
                    onProductClicked(index);
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void ProductListWidget::onProductClicked(int index)
{
    if (index >= 0 && index < products.size()) {
        Product product = products.at(index);
        
        // 创建详情页面并替换当前视图
        if (productDetailWidget) {
            delete productDetailWidget;
        }
        
        productDetailWidget = new ProductDetailWidget(product);
        
        // 创建一个包含返回按钮和详情页面的布局
        QWidget* detailContainer = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(detailContainer);
        
        // 创建返回按钮
        QPushButton* backButton = new QPushButton("← 返回商品列表");
        backButton->setStyleSheet("QPushButton {"
                                  "   background-color: #f0f0f0;"
                                  "   border: 1px solid #ccc;"
                                  "   padding: 5px;"
                                  "   font-weight: bold;"
                                  "} "
                                  "QPushButton:hover {"
                                  "   background-color: #e0e0e0;"
                                  "}");
        
        connect(backButton, &QPushButton::clicked, this, &ProductListWidget::onBackButtonClicked);
        
        layout->addWidget(backButton);
        layout->addWidget(productDetailWidget);
        
        // 切换到详情视图
        stackedWidget->addWidget(detailContainer);
        stackedWidget->setCurrentWidget(detailContainer);
    }
}

void ProductListWidget::onBackButtonClicked()
{
    // 返回商品列表视图
    stackedWidget->setCurrentIndex(0);

    // 删除详情页面以释放内存
    if (productDetailWidget) {
        productDetailWidget = nullptr;
    }

    // 移除详情容器（除了主列表页面外的所有页面）
    while (stackedWidget->count() > 1) {
        QWidget* widget = stackedWidget->widget(1);
        stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void ProductListWidget::onCloseButtonClicked()
{
    this->close();
}