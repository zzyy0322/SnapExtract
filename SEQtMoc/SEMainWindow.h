#pragma once

#include <QtWidgets/QMainWindow>
#include "SEScenntShotInter.h"

class SEMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	SEMainWindow(QWidget* parent = nullptr);

public:
    void setScenntShotInterface(SEScenntShotInter* _pInter);

public:
    void updateStatusBar();
    void endScreenshot(QPixmap _screenPixmap);

private:
    void __initUI();
    void __initSingalSlots();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void hideEvent(QHideEvent* event) override;

private slots:
    /*截图按钮*/
    void do_pushbtCapture();
    /*重新截图*/
    void do_pushbtReCapture();

signals:
    // 请求开始截图
    void screenshotRequested();

private:
    void showScenntPixMap();

private:
    SEScenntShotInter* m_pScenntShot;
    enActionType m_ScenntType = enActionType::enNone;
    QPixmap* m_ScenntPixMap = nullptr;

private:
    // 声明控件
    QWidget* centralWidget;       // 主窗口中心部件（必选，QMainWindow 要求）
    // 顶部工具栏控件
    QPushButton* btnCapture;      // 截图按钮
    QPushButton* btnReCapture;    // 重新截图按钮
    QComboBox* cbxRecogMode;      // 识别模式选择框
    QPushButton* btnSettings;     // 设置按钮

    // 左侧截图区控件
    QFrame* frameLeft;            // 左侧容器（QFrame）
    QLabel* lblLeftTitle;         // 左侧标题栏（截图预览）
    QLabel* lblPreview;           // 截图预览标签
    QWidget* leftEditToolWidget;  // 左侧编辑工具栏容器
    QPushButton* btnRectMark;     // 矩形标注按钮
    QPushButton* btnArrow;        // 箭头标注按钮
    QPushButton* btnTextMark;     // 文字标注按钮
    QPushButton* btnCrop;         // 裁剪按钮
    // 右侧识别区控件
    QFrame* frameRight;           // 右侧容器（QFrame）
    QWidget* rightTitleWidget;    // 右侧标题栏容器
    QLabel* lblRightTitle;        // 右侧标题（识别结果）
    QLabel* lblStatus;            // 右侧状态提示（待识别/识别中/识别完成）
    QTextEdit* textEditResult;    // 识别结果编辑区
    QWidget* rightExportToolWidget;// 右侧导出工具栏容器
    QPushButton* btnExportTXT;    // 导出 TXT 按钮
    QPushButton* btnExportMD;     // 导出 MD 按钮
    QPushButton* btnExportCode;   // 导出代码文件按钮
    QPushButton* btnExportPDF;    // 导出 PDF 按钮
    // 底部状态栏控件
    QWidget* bottomStatusWidget;  // 底部状态栏容器
    QLabel* lblTip;               // 左侧操作提示
    QLabel* lblStats;             // 右侧状态统计（耗时+历史记录）

private:
    QPoint m_originalPos; // 记录窗口原始位置
    bool m_wasVisible;    // 记录窗口原始可见状态
};

