// DlgPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "TestAMC.h"
#include "DlgPicture.h"
#include "afxdialogex.h"


// CDlgPicture 对话框

IMPLEMENT_DYNAMIC(CDlgPicture, CDialogEx)

CDlgPicture::CDlgPicture(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPicture::IDD, pParent)
{

}

CDlgPicture::~CDlgPicture()
{
}

void CDlgPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPicture, CDialogEx)
END_MESSAGE_MAP()


// CDlgPicture 消息处理程序
