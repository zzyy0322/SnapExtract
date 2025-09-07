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

private:
    void __initUI();
    void __initSingalSlots();

private slots:
    /*��ͼ��ť*/
    void do_pushbtCapture();

signals:
    // ����ʼ��ͼ
    void screenshotRequested();

private:
    SEScenntShotInter* m_pScenntShot;

private:
    // �����ؼ�
    QWidget* centralWidget;       // ���������Ĳ�������ѡ��QMainWindow Ҫ��
    // �����������ؼ�
    QPushButton* btnCapture;      // ��ͼ��ť
    QPushButton* btnReCapture;    // ���½�ͼ��ť
    QComboBox* cbxRecogMode;      // ʶ��ģʽѡ���
    QPushButton* btnSettings;     // ���ð�ť

    // ����ͼ���ؼ�
    QFrame* frameLeft;            // ���������QFrame��
    QLabel* lblLeftTitle;         // ������������ͼԤ����
    QLabel* lblPreview;           // ��ͼԤ����ǩ
    QWidget* leftEditToolWidget;  // ���༭����������
    QPushButton* btnRectMark;     // ���α�ע��ť
    QPushButton* btnArrow;        // ��ͷ��ע��ť
    QPushButton* btnTextMark;     // ���ֱ�ע��ť
    QPushButton* btnCrop;         // �ü���ť
    // �Ҳ�ʶ�����ؼ�
    QFrame* frameRight;           // �Ҳ�������QFrame��
    QWidget* rightTitleWidget;    // �Ҳ����������
    QLabel* lblRightTitle;        // �Ҳ���⣨ʶ������
    QLabel* lblStatus;            // �Ҳ�״̬��ʾ����ʶ��/ʶ����/ʶ����ɣ�
    QTextEdit* textEditResult;    // ʶ�����༭��
    QWidget* rightExportToolWidget;// �Ҳർ������������
    QPushButton* btnExportTXT;    // ���� TXT ��ť
    QPushButton* btnExportMD;     // ���� MD ��ť
    QPushButton* btnExportCode;   // ���������ļ���ť
    QPushButton* btnExportPDF;    // ���� PDF ��ť
    // �ײ�״̬���ؼ�
    QWidget* bottomStatusWidget;  // �ײ�״̬������
    QLabel* lblTip;               // ��������ʾ
    QLabel* lblStats;             // �Ҳ�״̬ͳ�ƣ���ʱ+��ʷ��¼��
};

