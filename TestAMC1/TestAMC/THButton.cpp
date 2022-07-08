// THButton.cpp : 实现文件
//

#include "stdafx.h"
#include "TestAMC.h"
#include "THButton.h"


// CTHButton

IMPLEMENT_DYNAMIC(CTHButton, CButton)

LONG CTHButton::m_lBtnPlayHandle;

CTHButton::CTHButton()
{

	m_lBtnPlayHandle = -1;
	m_bIsError = TRUE;
}

CTHButton::~CTHButton()
{
}


BEGIN_MESSAGE_MAP(CTHButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CTHButton 消息处理程序
void CTHButton::SetPlayHandle(LONG PlayHandle)
{
	m_lBtnPlayHandle = PlayHandle;
}


//按下左键时
void CTHButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	TripodHead(0);

	CButton::OnLButtonDown(nFlags, point);
}

//释放左键时
void CTHButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	TripodHead(1);

	CButton::OnLButtonUp(nFlags, point);
}




void CTHButton::TripodHead(DWORD wStop)
{
	UINT nID = GetDlgCtrlID();

	DWORD dwPTZCommand = 0;

	if (-1 == m_lBtnPlayHandle)
	{
		return;
	}

	switch (nID)
	{
	case IDC_BUTTON_UP_LEFT:
		dwPTZCommand = UP_LEFT;
		break;
	case IDC_BUTTON_TILT_UP:
		dwPTZCommand = TILT_UP;
		break;
	case IDC_BUTTON_UP_RIGHT:
		dwPTZCommand = UP_RIGHT;
		break;
	case IDC_BUTTON_PAN_LEFT:
		dwPTZCommand = PAN_LEFT;
		break;
	case IDC_BUTTON_PAN_AUTO:
		dwPTZCommand = PAN_AUTO;
		break;
	case IDC_BUTTON_PAN_RIGHT:
		dwPTZCommand = PAN_RIGHT;
		break;
	case IDC_BUTTON_DOWN_LEFT:
		dwPTZCommand = DOWN_LEFT;
		break;
	case IDC_BUTTON_TILT_DOWN:
		dwPTZCommand = TILT_DOWN;
		break;
	case IDC_BUTTON_DOWN_RIGHT:
		dwPTZCommand = DOWN_RIGHT;
		break;
	case IDC_BUTTON_ZOOM_IN:
		dwPTZCommand = ZOOM_IN;
		break;
	case IDC_BUTTON_ZOOM_OUT:
		dwPTZCommand = ZOOM_OUT;
		break;
	case IDC_BUTTON_FOCUS_NEAR:
		dwPTZCommand = FOCUS_NEAR;
		break;
	case IDC_BUTTON_FOCUS_FAR:
		dwPTZCommand = FOCUS_FAR;
		break;
	case IDC_BUTTON_IRIS_OPEN:
		dwPTZCommand = IRIS_OPEN;
		break;
	case IDC_BUTTON_IRIS_CLOSE:
		dwPTZCommand = IRIS_CLOSE;
		break;
	default:
		MessageBox("操作失败");
		return;
		break;
	}



	if (!NET_DVR_PTZControl(m_lBtnPlayHandle, dwPTZCommand, wStop))
	{
		if (m_bIsError)
		{ 
			CString strError;
			if (NET_DVR_NOSUPPORT != NET_DVR_GetLastError())
			{
				strError.Format("云台控制失败 错误代码%d ", NET_DVR_GetLastError());
				MessageBox(strError);
			}
			else
			{
				MessageBox("云台控制失败 此设备不支持");
			}


			m_bIsError = FALSE;
			return;
		}

		m_bIsError = TRUE;
	}
	return;
}