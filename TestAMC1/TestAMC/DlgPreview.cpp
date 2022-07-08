// DlgPreview.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestAMC.h"
#include "DlgPreview.h"
#include "afxdialogex.h"

// CDlgPreview ��Ϣ�������
IMPLEMENT_DYNAMIC(CDlgPreview, CDialogEx)

CDlgPreview::CDlgPreview(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPreview::IDD, pParent)
	, m_bIsPlaying(FALSE)
	, m_bIsLogin(FALSE)
	, m_iCurChanIndex(-1)
	, m_bIsRecording(FALSE)
	, m_bIsSceenshot(FALSE)
{

	m_lPlayHandle = 0;
	m_iCurChanIndex = 0;
}

CDlgPreview::~CDlgPreview()
{

}

void CDlgPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ID, m_TreeCtrlID);
	DDX_Control(pDX, IDC_BUTTON_UP_LEFT, m_THBtnUpLeft);
	DDX_Control(pDX, IDC_BUTTON_TILT_UP, m_THBtnTiltUp);
	DDX_Control(pDX, IDC_BUTTON_UP_RIGHT, m_THBtnUpRight);
	DDX_Control(pDX, IDC_BUTTON_PAN_LEFT, m_THBtnPanLeft);
	DDX_Control(pDX, IDC_BUTTON_PAN_AUTO, m_THBtnPanAuto);
	DDX_Control(pDX, IDC_BUTTON_PAN_RIGHT, m_THBtnPanRight);
	DDX_Control(pDX, IDC_BUTTON_DOWN_LEFT, m_THBtnDownLeft);
	DDX_Control(pDX, IDC_BUTTON_TILT_DOWN, m_THBtnTiltDown);
	DDX_Control(pDX, IDC_BUTTON_DOWN_RIGHT, m_THBtnDownRight);
	DDX_Control(pDX, IDC_BUTTON_ZOOM_IN, m_THBtnZoomIn);
	DDX_Control(pDX, IDC_BUTTON_ZOOM_OUT, m_THBtnZoomOut);
	DDX_Control(pDX, IDC_BUTTON_FOCUS_NEAR, m_THBtnFocusNera);
	DDX_Control(pDX, IDC_BUTTON_FOCUS_FAR, m_THBtnFocusFar);
	DDX_Control(pDX, IDC_BUTTON_IRIS_OPEN, m_THBtnItisOpen);
	DDX_Control(pDX, IDC_BUTTON_IRIS_CLOSE, m_THBtnIrisClose);
}

BEGIN_MESSAGE_MAP(CDlgPreview, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CDlgPreview::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_SCREENSHOT, &CDlgPreview::OnBnClickedButtonScreenshot)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO, &CDlgPreview::OnBnClickedButtonVideo)
END_MESSAGE_MAP()


// CDlgPreview ��Ϣ�������



// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�


void CDlgPreview::OnBnClickedButtonPlay()
{
	// TODO: Add your control notification handler code here


	if (!m_bIsLogin)
	{
		MessageBox("  ���ȵ�¼  ");
		return;
	}

	if (!m_bIsPlaying)
	{
		StartPlay();

		m_bIsPlaying = TRUE;
		GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText("ֹͣ����");
		CTHButton::SetPlayHandle(m_lPlayHandle);
	}
	else
	{
		if (m_bIsRecording)
		{
			MessageBox("����¼��������ͣ¼����ֹͣ����");
		}
		else
		{
			StopPlay();

			m_bIsPlaying = FALSE;
			GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText("����");
			CTHButton::SetPlayHandle(-1);
		}

	}

	UpdateData();
}


void CDlgPreview::StartPlay()
{
	NET_DVR_CLIENTINFO ClientInfo;

	ClientInfo.hPlayWnd = GetDlgItem(IDC_EDIT_VIDEO_WIN)->m_hWnd;
	ClientInfo.lChannel = m_iCurChanIndex + 1;
	ClientInfo.lLinkMode = 0;
	ClientInfo.sMultiCastIP = NULL;

	m_lPlayHandle = NET_DVR_RealPlay_V30(m_struDeviceInfo.lLoginID, &ClientInfo, NULL, NULL, TRUE);

	if (-1 == m_lPlayHandle)
	{
		CString CError;
		CError.Format("���Ŵ��� ERROR�� %d!\n", NET_DVR_GetLastError());
		MessageBox(CError);

	}
}


void CDlgPreview::StopPlay()
{


	if (m_lPlayHandle != -1)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
		m_bIsPlaying = FALSE;
		GetDlgItem(IDC_EDIT_VIDEO_WIN)->Invalidate();
	}


}



void CDlgPreview::OnBnClickedButtonScreenshot()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (-1 != m_lPlayHandle)
	{
		CString strError;
		char sPicFileName[256];
		memset(sPicFileName, 0, sizeof(sPicFileName));

		BOOL bValues = NET_DVR_SetCapturePictureMode(BMP_MODE);
		if (bValues)
		{


			CTime CurTime = CTime::GetCurrentTime();

			sprintf(sPicFileName, "%04d%02d%02d%02d%02d%02d.bmp", CurTime.GetYear(), CurTime.GetMonth(),
				CurTime.GetDay(), CurTime.GetHour(), CurTime.GetMinute(), CurTime.GetSecond());

			bValues = NET_DVR_CapturePicture(m_lPlayHandle, sPicFileName);

		}

		if (!bValues)
		{
			strError.Format("ץͼʧ�� �������%d ", NET_DVR_GetLastError());
			MessageBox(strError);
		}
		else
		{
			strError.Format("ץͼ�ɹ�%s", sPicFileName);
			MessageBox(strError);
		}
	}
	else
	{
		MessageBox("���ȿ���Ԥ������");
	}

}


void CDlgPreview::OnBnClickedButtonVideo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	static char strFlieName[256];

	if (!m_bIsRecording)
	{
		CTime CurTime = CTime::GetCurrentTime();

		memset(strFlieName, 0, sizeof(strFlieName));

		sprintf(strFlieName, "%04d%02d%02d%02d%02d%02d.mp4", CurTime.GetYear(), CurTime.GetMonth(),
			CurTime.GetDay(), CurTime.GetHour(), CurTime.GetMinute(), CurTime.GetSecond());

		StartRecord(strFlieName);
	}
	else
	{
		StopRecord(strFlieName);
	}
}


void CDlgPreview::StartRecord(char* pFlieName)
{

	if (!NET_DVR_SaveRealData(m_lPlayHandle, pFlieName))
	{
		MessageBox("����ʧ��");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_VIDEO)->SetWindowText(_T("��ͣ¼��"));
		m_bIsRecording = TRUE;
	}

}


void CDlgPreview::StopRecord(char* pFlieName)
{
	if (!NET_DVR_StopSaveRealData(m_lPlayHandle))
	{
		MessageBox("��ͣʧ��");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_VIDEO)->SetWindowText(_T("��ʼ¼��"));
		m_bIsRecording = FALSE;

		CString FlieName;
		FlieName.Format("��Ƶ¼��ɹ�%s", pFlieName);
		MessageBox(FlieName);
	}
}

void CDlgPreview::SetPZTPreview(BOOL bIsLogin, UINT iCurChanIndex, LOCAL_DEVICE_INFO struDeviceInfo)
{
	m_bIsLogin = bIsLogin;
	memcpy((void*)&m_struDeviceInfo, (void*)&struDeviceInfo, sizeof(LOCAL_DEVICE_INFO));
	m_iCurChanIndex = iCurChanIndex;
	
	if (!m_bIsLogin)
	{
		m_lPlayHandle = -1;
	}
		
}


BOOL CDlgPreview::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UINT nPngW = 840;
	UINT nPngH = 540;

	MoveWindow(0, 0, nPngW, nPngH);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
