// ScreenEdit.cpp : ʵ���ļ�
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



// CScreenEdit ��Ϣ�������




HBRUSH CScreenEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	LOGBRUSH   m_LogBrush;
	m_LogBrush.lbColor = RGB(0, 0, 0);
	m_BackBrush.GetLogBrush(&m_LogBrush);                                               //   �õ�������ɫ���߼�ˢ 
	pDC->SetBkColor(m_LogBrush.lbColor);                                                 //   ���ñ�����ɫ 
	return   HBRUSH(m_BackBrush);
	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
}
