#pragma once
#include "GeneralDef.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include <vector>
using namespace std;

// CDlgDownload 对话框

class CDlgDownload : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDownload)

public:
	CDlgDownload(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDownload();

// 对话框数据
	enum { IDD = IDD_DIALOG_DOWNLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetPZTPreview(BOOL bIsLogin, UINT iCurChanIndex, LOCAL_DEVICE_INFO struDeviceInfo);


	BOOL m_bIsLogin;
	UINT m_iCurChanIndex;
	LONG m_lPlayHandle;
	LOCAL_DEVICE_INFO m_struDeviceInfo;

	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnBnClickedButtonFind();

	DWORD m_dwFileType;

	CDateTimeCtrl m_ctrStartDate;
	CDateTimeCtrl m_ctrStartTime;
	CDateTimeCtrl m_ctrFinishDate;
	CDateTimeCtrl m_ctrFinishTime;
	CListCtrl m_listFile;
private:
	BOOL ByTimeFindVideoFile();

	
};
