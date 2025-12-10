#include "ProductEditWidget.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDateTime>

ProductEditWidget::ProductEditWidget(QWidget *parent) :
    QWidget(parent),
    product(),
    isNewProduct(true),
    titleEdit(new QLineEdit),
    categoryIdSpinBox(new QSpinBox),
    descriptionTextEdit(new QTextEdit),
    priceSpinBox(new QDoubleSpinBox),
    locationEdit(new QLineEdit),
    tagsEdit(new QLineEdit),
    statusCombo(new QComboBox),
    saveButton(new QPushButton("保存")),
    cancelButton(new QPushButton("取消"))
{
    setupUI();
    // 设置默认值
    product.setPublicTime(QDateTime::currentDateTime());
    product.setStatus("在售");
    updateUIFromProduct();
}

ProductEditWidget::ProductEditWidget(const Product& product, QWidget *parent) :
    QWidget(parent),
    product(product),
    isNewProduct(false),
    titleEdit(new QLineEdit),
    categoryIdSpinBox(new QSpinBox),
    descriptionTextEdit(new QTextEdit),
    priceSpinBox(new QDoubleSpinBox),
    locationEdit(new QLineEdit),
    tagsEdit(new QLineEdit),
    statusCombo(new QComboBox),
    saveButton(new QPushButton("保存")),
    cancelButton(new QPushButton("取消"))
{
    setupUI();
    updateUIFromProduct();
}

ProductEditWidget::~ProductEditWidget()
{
    // 控件会随父对象自动删除，无需手动释放
}

void ProductEditWidget::setupUI()
{
    // 设置spinbox范围
    categoryIdSpinBox->setRange(0, 999999);
    priceSpinBox->setRange(0, 9999999.99);
    priceSpinBox->setDecimals(2);
    
    // 设置状态选项
    statusCombo->addItem("在售");
    statusCombo->addItem("已售");
    statusCombo->addItem("下架");
    
    // 连接信号槽
    connect(saveButton, &QPushButton::clicked, this, &ProductEditWidget::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ProductEditWidget::onCancelClicked);
    
    // 创建表单布局
    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("商品名称:", titleEdit);
    formLayout->addRow("分类ID:", categoryIdSpinBox);
    formLayout->addRow("价格:", priceSpinBox);
    formLayout->addRow("地址:", locationEdit);
    formLayout->addRow("标签:", tagsEdit);
    formLayout->addRow("状态:", statusCombo);
    formLayout->addRow("描述:", descriptionTextEdit);
    
    // 创建按钮布局
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    
    // 创建主布局
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);
    setWindowTitle(isNewProduct ? "发布新商品" : "编辑商品");
    resize(400, 300);
}

Product ProductEditWidget::getProduct() const
{
    return product;
}

void ProductEditWidget::setProduct(const Product& product)
{
    this->product = product;
    isNewProduct = false;
    updateUIFromProduct();
    setWindowTitle("编辑商品");
}

void ProductEditWidget::updateProductFromUI()
{
    product.setTitle(titleEdit->text());
    product.setCategoryId(categoryIdSpinBox->value());
    product.setDescription(descriptionTextEdit->toPlainText());
    product.setPrice(priceSpinBox->value());
    product.setLocation(locationEdit->text());
    
    // 处理标签
    QStringList tagList = tagsEdit->text().split(",", Qt::SkipEmptyParts);
    QList<QString> tags;
    for (const QString& tag : tagList) {
        tags.append(tag.trimmed());
    }
    product.setTags(tags);
    
    product.setStatus(statusCombo->currentText());
}

void ProductEditWidget::updateUIFromProduct()
{
    titleEdit->setText(product.getTitle());
    categoryIdSpinBox->setValue(product.getCategoryId());
    descriptionTextEdit->setPlainText(product.getDescription());
    priceSpinBox->setValue(product.getPrice());
    locationEdit->setText(product.getLocation());
    
    // 处理标签
    QStringList tagList = QStringList(product.getTags());
    tagsEdit->setText(tagList.join(", "));
    
    // 设置状态
    int statusIndex = statusCombo->findText(product.getStatus());
    if (statusIndex >= 0) {
        statusCombo->setCurrentIndex(statusIndex);
    } else {
        statusCombo->setCurrentIndex(0); // 默认为"在售"
    }
}

void ProductEditWidget::onSaveClicked()
{
    if (titleEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "商品名称不能为空！");
        return;
    }
    
    updateProductFromUI();
    emit productSaved(product);
}

void ProductEditWidget::onCancelClicked()
{
    emit cancelled();
}