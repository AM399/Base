#pragma once
#include "afxcmn.h"
#include "GeneralDef.h"
#include "THButton.h"

// CDlgPreview 对话框

class CDlgPreview : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPreview)

public:
	CDlgPreview(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPreview();

// 对话框数据
	enum { IDD = IDD_DIALOG_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// 实现


public:
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonScreenshot();
	afx_msg void OnBnClickedButtonVideo();

private:

	void StartPlay();
	void StopPlay();

	void StartRecord(char* pFlieName);
	void StopRecord(char* pFlieName);
	void TripodHead(DWORD dwPTZCommand, DWORD dwStop);

public:
	void SetPZTPreview(BOOL bIsLogin, UINT iCurChanIndex, LOCAL_DEVICE_INFO struDeviceInfo);
	virtual BOOL OnInitDialog();

private:

	BOOL m_bIsPlaying;
	BOOL m_bIsLogin;

	LOCAL_DEVICE_INFO m_struDeviceInfo;

	BOOL m_bIsRecording;
	LONG m_lPlayHandle;
	BOOL m_bIsSceenshot;
	CTreeCtrl m_TreeCtrlID;
	UINT m_iCurChanIndex;

	CTHButton m_THBtnUpLeft;
	CTHButton m_THBtnTiltUp;
	CTHButton m_THBtnUpRight;
	CTHButton m_THBtnPanLeft;
	CTHButton m_THBtnPanAuto;
	CTHButton m_THBtnPanRight;
	CTHButton m_THBtnDownLeft;
	CTHButton m_THBtnTiltDown;
	CTHButton m_THBtnDownRight;
	CTHButton m_THBtnZoomIn;
	CTHButton m_THBtnZoomOut;
	CTHButton m_THBtnFocusNera;
	CTHButton m_THBtnFocusFar;
	CTHButton m_THBtnItisOpen;
	CTHButton m_THBtnIrisClose;


};



