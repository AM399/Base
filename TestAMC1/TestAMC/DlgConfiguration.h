#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CDlgConfiguration �Ի���

class CDlgConfiguration : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfiguration)

public:
	CDlgConfiguration(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgConfiguration();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONFIGURATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

