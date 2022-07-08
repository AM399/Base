
// TestAMCDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "GeneralDef.h"
#include "THButton.h"
#include "DlgPreview.h"
#include "DlgPlayback.h"
#include "DlgPicture.h"
#include "DlgConfiguration.h"



// CTestAMCDlg 对话框
class CTestAMCDlg : public CDialogEx
{
// 构造
public:
	CTestAMCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTAMC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

#define PAGE_NUMBER 4

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnTcnSelchangeTabControl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();

private:
	BOOL DoLogin();
	void DoGetDeviceResoureCfg();
	void CreateDeviceTree();
	void GetDecoderCfg();
	void InitDecoderReferCtrl();

private:
	
	UINT m_Port;
	CString m_User;
	CString m_Password;
	BOOL m_bIsPlaying;
	BOOL m_bIsLogin;
	CIPAddressCtrl m_VCR_IP;

	LOCAL_DEVICE_INFO m_struDeviceInfo;
	int m_iCurChanIndex;
	UINT m_CurSelTab;
	CTabCtrl m_tabCtrl;

	CDlgPreview m_dlgPreview;
	CDlgPlayback m_dlgPlayback;
	CDlgPicture m_dlgPicture;
	CDlgConfiguration m_dlgConfiguration;

	CDialog* m_pDialog[PAGE_NUMBER];

};

