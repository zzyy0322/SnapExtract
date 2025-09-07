#include "pch.h"
#include "SEMainWindow.h"

SEMainWindow::SEMainWindow(QWidget* parent)
	:QMainWindow(parent)
{
	this->setWindowFlags(this->windowFlags());
	this->resize(1000, 600);
	this->setWindowTitle("SnapExtract");
	this->setMinimumSize(100, 60);

	__initUI();
}

void SEMainWindow::setScenntShotInterface(SEScenntShotInter* _pInter)
{
	m_pScenntShot = _pInter;
	__initSingalSlots();
}

void SEMainWindow::updateStatusBar()
{
	lblTip->setText(QStringLiteral("请通过鼠标点击截图"));
}

void SEMainWindow::__initUI()
{
	// 2. 创建中心部件（QMainWindow 必须通过 centralWidget 承载内容）
	centralWidget = new QWidget(this);
	this->setCentralWidget(centralWidget);

	// 3. 初始化顶层布局（垂直布局：顶部工具栏 → 左右分栏 → 底部状态栏）
	QVBoxLayout* topLayout = new QVBoxLayout(centralWidget);
	topLayout->setContentsMargins(0, 0, 0, 0); // 顶层布局无边距
	topLayout->setSpacing(0);                  // 布局内控件无间距

	// 4. 初始化各区域控件（按文档顺序：顶部→分栏→底部）
	// -------------------------- 步骤1：初始化顶部工具栏 --------------------------
	// 顶部工具栏容器（固定高度 40px）
	QWidget* topToolWidget = new QWidget(centralWidget);
	topToolWidget->setFixedHeight(40);
	QHBoxLayout* topToolLayout = new QHBoxLayout(topToolWidget);
	topToolLayout->setContentsMargins(10, 0, 10, 0); // 左右留边 15px
	topToolLayout->setSpacing(10);                   // 控件间距 10px

	// 创建顶部工具栏控件（按文档“左-中-右”顺序）
	// 左侧：截图按钮（图标+文字，快捷键提示）
	btnCapture = new QPushButton(topToolWidget);
	btnCapture->setText(QStringLiteral("截图"));
	btnCapture->setToolTip("Win+Shift+S");

	// 左侧：重新截图按钮（默认禁用，图标为刷新）
	btnReCapture = new QPushButton(topToolWidget);
	btnReCapture->setText(QString(QStringLiteral("重新截图")));
	btnReCapture->setEnabled(false); // 默认禁用

	// 中间：识别模式选择框（选项：通用文字、代码优先，默认通用文字）
	cbxRecogMode = new QComboBox(topToolWidget);
	cbxRecogMode->addItem(QStringLiteral("通用文字"));
	cbxRecogMode->addItem(QStringLiteral("代码优先"));
	cbxRecogMode->setCurrentIndex(0); // 默认选中第一个

	// 右侧：设置按钮（图标为偏好设置）
	btnSettings = new QPushButton(topToolWidget);

	// 将顶部控件添加到布局（通过 addStretch() 实现“左-中-右”对齐）
	topToolLayout->addWidget(btnCapture);
	topToolLayout->addWidget(btnReCapture);
	topToolLayout->addStretch(1); // 左侧控件与中间控件之间拉伸
	topToolLayout->addWidget(cbxRecogMode);
	//topToolLayout->addStretch(1); // 中间控件与右侧控件之间拉伸
	topToolLayout->addWidget(btnSettings);
	topToolLayout->addSpacing(10);

	// 将顶部工具栏添加到顶层布局
	topLayout->addWidget(topToolWidget);

	// -------------------------- 步骤2：初始化左右分栏（QSplitter） --------------------------
	QSplitter* splitterMain = new QSplitter(centralWidget);
	splitterMain->setOrientation(Qt::Horizontal); // 水平分栏
	splitterMain->setSizes(QList<int>() << 500 << 500); // 默认宽比 1:1
	splitterMain->setHandleWidth(6); // 分隔线宽度 6px
	splitterMain->setOpaqueResize(true); // 拖动时实时显示

	// -------------- 左侧分栏：截图内容展示区（QFrame 容器）--------------
	frameLeft = new QFrame(splitterMain);
	frameLeft->setFrameStyle(QFrame::Box | QFrame::Sunken); // 带边框样式
	QVBoxLayout* leftFrameLayout = new QVBoxLayout(frameLeft);
	leftFrameLayout->setContentsMargins(0, 0, 0, 0);
	leftFrameLayout->setSpacing(0);

	// 左侧标题栏（文字“截图预览”，加粗，背景 #F5F5F5，高度 28px）
	lblLeftTitle = new QLabel(frameLeft);
	lblLeftTitle->setText(QStringLiteral("截图预览"));
	lblLeftTitle->setFixedHeight(28);
	lblLeftTitle->setAlignment(Qt::AlignCenter);

	// 左侧预览容器（显示截图，默认提示文字，居中对齐）
	lblPreview = new QLabel(frameLeft);
	lblPreview->setText(QStringLiteral("点击左侧｢截图｣按钮开始捕获"));
	lblPreview->setAlignment(Qt::AlignCenter);
	lblPreview->setStyleSheet("color: #999;"); // 灰色字体
	// 支持图像按比例缩放（后续截图后设置图像时生效）
	lblPreview->setScaledContents(true);
	lblPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// 左侧编辑工具栏（隐藏式，截图后显示，高度 30px）
	leftEditToolWidget = new QWidget(frameLeft);
	leftEditToolWidget->setFixedHeight(30);
	leftEditToolWidget->setVisible(false); // 默认隐藏
	QHBoxLayout* leftEditToolLayout = new QHBoxLayout(leftEditToolWidget);
	leftEditToolLayout->setContentsMargins(0, 0, 0, 0);
	leftEditToolLayout->setAlignment(Qt::AlignCenter);

	// 编辑工具栏按钮（仅显示图标，无文字）
	btnRectMark = new QPushButton(leftEditToolWidget);
	//btnRectMark->setIcon(this->style()->standardIcon(QStyle::SP_DrawRect));
	btnArrow = new QPushButton(leftEditToolWidget);
	//btnArrow->setIcon(this->style()->standardIcon(QStyle::SP_Arrow));
	btnTextMark = new QPushButton(leftEditToolWidget);
	//btnTextMark->setIcon(this->style()->standardIcon(QStyle::SP_Text));
	btnCrop = new QPushButton(leftEditToolWidget);
	//btnCrop->setIcon(this->style()->standardIcon(QStyle::SP_Crop));

	// 将编辑按钮添加到布局（按钮间距 10px）
	leftEditToolLayout->addWidget(btnRectMark);
	leftEditToolLayout->addSpacing(10);
	leftEditToolLayout->addWidget(btnArrow);
	leftEditToolLayout->addSpacing(10);
	leftEditToolLayout->addWidget(btnTextMark);
	leftEditToolLayout->addSpacing(10);
	leftEditToolLayout->addWidget(btnCrop);

	// 将左侧子控件添加到左侧布局
	leftFrameLayout->addWidget(lblLeftTitle);
	leftFrameLayout->addWidget(lblPreview);
	leftFrameLayout->addWidget(leftEditToolWidget);

	// -------------- 右侧分栏：识别内容展示区（QFrame 容器）--------------
	frameRight = new QFrame(splitterMain);
	frameRight->setFrameStyle(QFrame::Box | QFrame::Sunken); // 带边框样式
	QVBoxLayout* rightFrameLayout = new QVBoxLayout(frameRight);
	rightFrameLayout->setContentsMargins(0, 0, 0, 0);
	rightFrameLayout->setSpacing(0);

	// 右侧标题栏（容器+标题+状态，背景 #F5F5F5，高度 28px）
	rightTitleWidget = new QWidget(frameRight);
	rightTitleWidget->setFixedHeight(28);
	QHBoxLayout* rightTitleLayout = new QHBoxLayout(rightTitleWidget);
	rightTitleLayout->setContentsMargins(15, 0, 15, 0);
	rightTitleLayout->setSpacing(0);

	// 右侧标题（文字“识别结果”，加粗）
	lblRightTitle = new QLabel(rightTitleWidget);
	lblRightTitle->setText(QStringLiteral("识别结果"));
	// 右侧状态提示（默认“待识别”，右对齐）
	lblStatus = new QLabel(rightTitleWidget);
	lblStatus->setText(QStringLiteral("待识别"));
	lblStatus->setAlignment(Qt::AlignRight);
	rightTitleLayout->addWidget(lblRightTitle);
	rightTitleLayout->addStretch(1); // 标题与状态之间拉伸（右对齐状态）
	rightTitleLayout->addWidget(lblStatus);

	// 右侧内容编辑区（QTextEdit，默认禁用，识别后启用，代码字体 Consolas）
	textEditResult = new QTextEdit(frameRight);
	textEditResult->setReadOnly(true); // 默认只读
	textEditResult->setFont(QFont("Consolas", 10)); // 代码友好字体
	textEditResult->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// 右侧导出工具栏（隐藏式，识别后显示，高度 30px）
	rightExportToolWidget = new QWidget(frameRight);
	rightExportToolWidget->setFixedHeight(30);
	rightExportToolWidget->setVisible(false); // 默认隐藏
	QHBoxLayout* rightExportToolLayout = new QHBoxLayout(rightExportToolWidget);
	rightExportToolLayout->setContentsMargins(0, 0, 0, 0);
	rightExportToolLayout->setAlignment(Qt::AlignCenter);

	// 导出工具栏按钮（图标+文字，按文档设置图标）
	btnExportTXT = new QPushButton(rightExportToolWidget);
	btnExportTXT->setIcon(this->style()->standardIcon(QStyle::SP_FileDialogNewFolder));
	btnExportTXT->setText(QStringLiteral("导出 TXT"));
	btnExportMD = new QPushButton(rightExportToolWidget);
	btnExportMD->setIcon(this->style()->standardIcon(QStyle::SP_FileDialogInfoView));
	btnExportMD->setText(QStringLiteral("导出 MD"));
	btnExportCode = new QPushButton(rightExportToolWidget);
	//btnExportCode->setIcon(this->style()->standardIcon(QStyle::SP_FileCode));
	btnExportCode->setText(QStringLiteral("导出代码文件"));
	btnExportPDF = new QPushButton(rightExportToolWidget);
	//btnExportPDF->setIcon(this->style()->standardIcon(QStyle::SP_FilePdf));
	btnExportPDF->setText(QStringLiteral("导出 PDF"));

	// 将导出按钮添加到布局（按钮间距 15px）
	rightExportToolLayout->addWidget(btnExportTXT);
	rightExportToolLayout->addSpacing(15);
	rightExportToolLayout->addWidget(btnExportMD);
	rightExportToolLayout->addSpacing(15);
	rightExportToolLayout->addWidget(btnExportCode);
	rightExportToolLayout->addSpacing(15);
	rightExportToolLayout->addWidget(btnExportPDF);

	// 将右侧子控件添加到右侧布局
	rightFrameLayout->addWidget(rightTitleWidget);
	rightFrameLayout->addWidget(textEditResult);
	rightFrameLayout->addWidget(rightExportToolWidget);

	// 将左右 Frame 添加到分栏控件
	splitterMain->addWidget(frameLeft);
	splitterMain->addWidget(frameRight);
	// 将分栏控件添加到顶层布局
	topLayout->addWidget(splitterMain);

	// -------------------------- 步骤3：初始化底部状态栏 --------------------------
	bottomStatusWidget = new QWidget(centralWidget);
	bottomStatusWidget->setFixedHeight(24);
	QHBoxLayout* bottomStatusLayout = new QHBoxLayout(bottomStatusWidget);
	bottomStatusLayout->setContentsMargins(15, 0, 15, 0);
	bottomStatusLayout->setSpacing(0);

	// 左侧提示（文本“截图后自动开始识别”）
	lblTip = new QLabel(bottomStatusWidget);
	lblTip->setText(QStringLiteral("截图后自动开始识别"));
	lblTip->setStyleSheet("color: #666;");
	// 右侧状态统计（文本“识别耗时：-- | 历史：0 条”）
	lblStats = new QLabel(bottomStatusWidget);
	lblStats->setText(QStringLiteral("识别耗时：-- | 历史：0 条"));
	lblStats->setStyleSheet("color: #666;");
	lblStats->setAlignment(Qt::AlignRight);

	// 将状态栏标签添加到布局（拉伸实现左右对齐）
	bottomStatusLayout->addWidget(lblTip);
	bottomStatusLayout->addStretch(1);
	bottomStatusLayout->addWidget(lblStats);

	// 将底部状态栏添加到顶层布局
	topLayout->addWidget(bottomStatusWidget);
}

void SEMainWindow::__initSingalSlots()
{
	connect(btnCapture, &QPushButton::clicked, this, &SEMainWindow::do_pushbtCapture);

	if (m_pScenntShot)
	{
		// 开始截图
		connect(this, &SEMainWindow::screenshotRequested,
			m_pScenntShot, &SEScenntShotInter::startScreenshot);
	}

}

void SEMainWindow::do_pushbtCapture()
{
	emit screenshotRequested();
}