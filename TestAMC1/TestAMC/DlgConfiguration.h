#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CDlgConfiguration 对话框

class CDlgConfiguration : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfiguration)

public:
	CDlgConfiguration(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgConfiguration();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONFIGURATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:


	CFont m_Font;

	virtual BOOL OnInitDialog();
private:
	CTreeCtrl m_TreeCtrl;
public:
	afx_msg void OnNMClickTreeDirectory(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
private:
	CEdit m_etView;
	void ProcessNode(CComPtr<MSXML2::IXMLDOMNode>& spNode, int tmp);
};

