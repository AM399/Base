#pragma once


// CScreenEdit

class CScreenEdit : public CEdit
{
	DECLARE_DYNAMIC(CScreenEdit)

public:
	CScreenEdit();
	virtual ~CScreenEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT /*nCtlColor*/);
private:
	CBrush m_BackBrush;
};


