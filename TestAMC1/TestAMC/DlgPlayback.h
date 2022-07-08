#pragma once
#include "GeneralDef.h"
#include "THButton.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "DlgDownload.h"
#include "afxcmn.h"

// CDlgPlayback 对话框

class CDlgPlayback : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPlayback)

public:
	CDlgPlayback(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPlayback();

// 对话框数据
	enum { IDD = IDD_DIALOG_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	

public:
	afx_msg void OnBnClickedButtonPlay();



	virtual BOOL OnInitDialog();
	void SetPZTPreview(BOOL bIsLogin, UINT iCurChanIndex, LOCAL_DEVICE_INFO struDeviceInfo);

	BOOL ByTimeFindPlayback(BOOL bIsOnlyFind);


private:
	CButton m_BtnPlayStop;
	CButton m_BtnSlow;
	CButton m_BtnPlay;
	CButton m_BtnFast;
	CButton m_BtnScreenshot;
	CButton m_BtnFilmEditing;
	CButton m_BtnmDownload;
	CButton m_BtnFind;
	CButton m_BtnTimeOk;
	CEdit m_EditHour;
	CEdit m_EditMinute;
	CEdit m_EditSecond;
	CMonthCalCtrl m_Data;

	BOOL m_bIsLogin; //登录开关
	LOCAL_DEVICE_INFO m_struDeviceInfo; //播放数据
	UINT m_iCurChanIndex; //通道号
	LONG m_lPlayHandle;   //登录ID信息
	UCHAR m_cIsPlaying;    //播放开关
	BOOL m_bIsFilmEditing; 

public:
	afx_msg void OnBnClickedButtonPlayStop();
	afx_msg void OnBnClickedButtonFast();
	afx_msg void OnBnClickedButtonSlow();

	afx_msg void OnBnClickedButtonScreenshot();
	afx_msg void OnBnClickedButtonFilmEditing();
private:
	void StartFilmEditing(char* pFlieName);
	void StopFilmEditing(char* pFlieName);


	afx_msg void OnBnClickedButtonFind();

	BOOL m_bIsStopPlayBack;
public:
	afx_msg void OnBnClickedButtonTimeOk();
	afx_msg void OnBnClickedButtonDownload();
private:
	CTreeCtrl m_Tree;
};
