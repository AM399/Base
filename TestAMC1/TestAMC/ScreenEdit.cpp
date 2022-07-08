// ScreenEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "TestAMC.h"
#include "ScreenEdit.h"


// CScreenEdit

IMPLEMENT_DYNAMIC(CScreenEdit, CEdit)

CScreenEdit::CScreenEdit()
{

}

CScreenEdit::~CScreenEdit()
{
}


BEGIN_MESSAGE_MAP(CScreenEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CScreenEdit 消息处理程序




HBRUSH CScreenEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// TODO:  在此更改 DC 的任何特性
	LOGBRUSH   m_LogBrush;
	m_LogBrush.lbColor = RGB(0, 0, 0);
	m_BackBrush.GetLogBrush(&m_LogBrush);                                               //   得到背景颜色的逻辑刷 
	pDC->SetBkColor(m_LogBrush.lbColor);                                                 //   设置背景颜色 
	return   HBRUSH(m_BackBrush);
	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
}
