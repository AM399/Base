#pragma once
#include "GeneralDef.h"

// CTHButton

class CTHButton : public CButton
{
	DECLARE_DYNAMIC(CTHButton)

public:
	CTHButton();
	virtual ~CTHButton();



protected:
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	static void SetPlayHandle(LONG PlayHandle);

	void TripodHead(DWORD wStop);

private:
	static LONG m_lBtnPlayHandle;

	UCHAR m_bIsError;
};



