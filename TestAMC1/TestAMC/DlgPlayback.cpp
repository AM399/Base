// DlgPlayback.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestAMC.h"
#include "DlgPlayback.h"
#include "afxdialogex.h"


// CDlgPlayback �Ի���

IMPLEMENT_DYNAMIC(CDlgPlayback, CDialogEx)

CDlgPlayback::CDlgPlayback(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPlayback::IDD, pParent)
{

	m_iCurChanIndex = 0;
	m_lPlayHandle = -1;
	m_cIsPlaying = NET_DVR_PLAYSTART;
	m_bIsFilmEditing = FALSE;
	m_bIsStopPlayBack = TRUE;
}

CDlgPlayback::~CDlgPlayback()
{
}

void CDlgPlayback::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PLAY_STOP, m_BtnPlayStop);
	DDX_Control(pDX, IDC_BUTTON_SLOW, m_BtnSlow);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_BtnPlay);
	DDX_Control(pDX, IDC_BUTTON_FAST, m_BtnFast);
	DDX_Control(pDX, IDC_BUTTON_SCREENSHOT, m_BtnScreenshot);
	DDX_Control(pDX, IDC_BUTTON_FILM_EDITING, m_BtnFilmEditing);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOAD, m_BtnmDownload);
	DDX_Control(pDX, IDC_BUTTON_FIND, m_BtnFind);
	DDX_Control(pDX, IDC_BUTTON_TIME_OK, m_BtnTimeOk);
	DDX_Control(pDX, IDC_EDIT_HOUR, m_EditHour);
	DDX_Control(pDX, IDC_EDIT_MINUTE, m_EditMinute);
	DDX_Control(pDX, IDC_EDIT_SECOND, m_EditSecond);
	DDX_Control(pDX, IDC_MONTHCALENDAR_DATE, m_Data);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
}


BEGIN_MESSAGE_MAP(CDlgPlayback, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CDlgPlayback::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_STOP, &CDlgPlayback::OnBnClickedButtonPlayStop)
	ON_BN_CLICKED(IDC_BUTTON_FAST, &CDlgPlayback::OnBnClickedButtonFast)
	ON_BN_CLICKED(IDC_BUTTON_SLOW, &CDlgPlayback::OnBnClickedButtonSlow)
	ON_BN_CLICKED(IDC_BUTTON_SCREENSHOT, &CDlgPlayback::OnBnClickedButtonScreenshot)
	ON_BN_CLICKED(IDC_BUTTON_FILM_EDITING, &CDlgPlayback::OnBnClickedButtonFilmEditing)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CDlgPlayback::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_TIME_OK, &CDlgPlayback::OnBnClickedButtonTimeOk)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CDlgPlayback::OnBnClickedButtonDownload)
END_MESSAGE_MAP()


// CDlgPlayback ��Ϣ�������


BOOL CDlgPlayback::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	UINT nPngW = 840;
	UINT nPngH = 540;

	MoveWindow(0, 0, nPngW, nPngH);

	CFont * f;

	f = new CFont;

	f->CreateFont(16,            // nHeight

		0,           // nWidth

		0,           // nEscapement

		0,           // nOrientation

		FW_LIGHT,     // nWeight

		FALSE,        // bItalic

		FALSE,       // bUnderline

		0,          // cStrikeOut

		ANSI_CHARSET,              //nCharSet

		OUT_DEFAULT_PRECIS,        //nOutPrecision

		CLIP_DEFAULT_PRECIS,       //nClipPrecision

		DEFAULT_QUALITY,           //nQuality

		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily

		_T("����"));             // lpszFac


	m_EditHour.SetLimitText(2);
	m_EditMinute.SetLimitText(2);
	m_EditSecond.SetLimitText(2);

	m_EditHour.SetFont(f);
	m_EditMinute.SetFont(f);
	m_EditSecond.SetFont(f);

	m_EditHour.SetWindowTextA("00");
	m_EditMinute.SetWindowTextA("00");
	m_EditSecond.SetWindowTextA("00");

	GetDlgItem(IDC_BUTTON_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FILM_EDITING)->EnableWindow(FALSE);

	HTREEITEM hRoot;

	hRoot = m_Tree.InsertItem("ROOT", TVI_ROOT, TVI_LAST);
	HTREEITEM hRoot2 = m_Tree.InsertItem("ROOT2", TVI_ROOT, TVI_LAST);

	HTREEITEM hChild1 = m_Tree.InsertItem("����1", hRoot);
	HTREEITEM hChild2 = m_Tree.InsertItem("����2", hRoot);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CDlgPlayback::SetPZTPreview(BOOL bIsLogin, UINT iCurChanIndex, LOCAL_DEVICE_INFO struDeviceInfo)
{
	m_bIsLogin = bIsLogin;
	memcpy((void*)&m_struDeviceInfo, (void*)&struDeviceInfo, sizeof(LOCAL_DEVICE_INFO));
	m_iCurChanIndex = iCurChanIndex;

	if (!m_bIsLogin)
	{
		m_lPlayHandle = -1;
	}

}

//��ʱ����һط�¼��
BOOL CDlgPlayback::ByTimeFindPlayback(BOOL bIsOnlyFind)
{
	SYSTEMTIME time;
	DWORD   dwFileType = 0xff;
	NET_DVR_TIME lStartTime;
	NET_DVR_TIME lStopTime;


	memset(&lStartTime, 0, sizeof(NET_DVR_TIME));
	memset(&lStopTime, 0, sizeof(NET_DVR_TIME));

	m_Data.GetCurSel(&time);
	
	lStartTime.dwYear = time.wYear;
	lStartTime.dwMonth = time.wMonth;
	lStartTime.dwDay = time.wDay;

	CString strTime = "";

	m_EditHour.GetWindowTextA(strTime);
	lStartTime.dwHour = _ttoi(strTime);

	strTime = "";
	m_EditMinute.GetWindowTextA(strTime);
	lStartTime.dwMinute = _ttoi(strTime);
	
	strTime = "";
	m_EditSecond.GetWindowTextA(strTime);
	lStartTime.dwSecond = _ttoi(strTime);

	lStopTime.dwYear = time.wYear;
	lStopTime.dwMonth = time.wMonth;
	lStopTime.dwDay = time.wDay;

	lStopTime.dwHour = lStartTime.dwHour +1;

	if (++lStopTime.dwMinute  == 60)
	{
		lStopTime.dwMinute = 0;
		
		if (++lStopTime.dwHour  == 24)
		{
			lStopTime.dwHour = 0;
			if (++lStopTime.dwDay == 30)
			{
				lStopTime.dwDay = 0;
			}
		}
	}
	
	LONG lChannel = m_iCurChanIndex + 1;
	lStopTime.dwSecond = lStartTime.dwSecond;

	m_lPlayHandle = NET_DVR_FindFile(m_struDeviceInfo.lLoginID, lChannel, dwFileType,
		&lStartTime, &lStopTime);
	if (-1 == m_lPlayHandle)
	{
		CString CError;
		CError.Format("������� %d!\n", NET_DVR_GetLastError());
		MessageBox(CError);
		return FALSE;
	}

	LONG result = NET_DVR_ISFINDING;
	NET_DVR_FIND_DATA  lFindData;

	while (NET_DVR_ISFINDING == result)
	{
		result = NET_DVR_FindNextFile(m_lPlayHandle, &lFindData);

		if (-1 == result)
		{
			CString CError;
			CError.Format("������� %d!\n", NET_DVR_GetLastError());
			MessageBox(CError);
			m_lPlayHandle = -1;
			return FALSE;
		}

	}

	switch (result)
	{
	case NET_DVR_FILE_SUCCESS:
	case NET_DVR_ISFINDING:
		break;

	case NET_DVR_FILE_NOFIND:
	case NET_DVR_NOMOREFILE:
		MessageBox("δ���ҵ��ļ�");
		return FALSE;

	case NET_DVR_FILE_EXCEPTION:
		MessageBox("�����ļ�ʱ�쳣");
		return FALSE;

	default:
		break;
	}

	m_lPlayHandle = -1;

	if (!bIsOnlyFind)
	{
		m_lPlayHandle = NET_DVR_PlayBackByTime(m_struDeviceInfo.lLoginID, lChannel,
			&lStartTime, &lStopTime, GetDlgItem(IDC_EDIT_PLAYBACK)->m_hWnd);
		if (-1 == m_lPlayHandle)
		{
			CString CError;
			CError.Format("������� %d!\n", NET_DVR_GetLastError());
			MessageBox(CError);
			return FALSE;
		}
	}

	return TRUE;
}


void CDlgPlayback::OnBnClickedButtonPlay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString strBtnText;
	UCHAR cPlaying = 0;
	BOOL bPlay = FALSE;


	if (-1 == m_lPlayHandle)
	{
		if (!ByTimeFindPlayback(FALSE))
		{
			return;
		}
	}

	switch (m_cIsPlaying)
	{
	case NET_DVR_PLAYSTART:
		cPlaying = NET_DVR_PLAYSTART;
		m_cIsPlaying = NET_DVR_PLAYPAUSE;
		strBtnText = "��ͣ";
		break;
	case NET_DVR_PLAYPAUSE:
		cPlaying = NET_DVR_PLAYPAUSE;
		m_cIsPlaying = NET_DVR_PLAYRESTART;
		strBtnText = "����";
		break;
	case NET_DVR_PLAYRESTART:
		cPlaying = NET_DVR_PLAYRESTART;
		m_cIsPlaying = NET_DVR_PLAYPAUSE;
		strBtnText = "��ͣ";
		break;
	default:
		break;
	}


	if (!NET_DVR_PlayBackControl(m_lPlayHandle, cPlaying, NULL, NULL))
	{
		CString CError;
		CError.Format("������� %d!\n", NET_DVR_GetLastError());
		MessageBox(CError);

		m_cIsPlaying = cPlaying;
		return;
	} 

	GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(strBtnText);

	if (NET_DVR_PLAYSTART == cPlaying || NET_DVR_PLAYRESTART == cPlaying)
	{
		bPlay = TRUE;

	} else
	{
		bPlay = FALSE;
	}

	GetDlgItem(IDC_BUTTON_SLOW)->EnableWindow(bPlay);
	GetDlgItem(IDC_BUTTON_FAST)->EnableWindow(bPlay);
	GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(bPlay);
	GetDlgItem(IDC_BUTTON_FILM_EDITING)->EnableWindow(bPlay);

	m_bIsStopPlayBack = FALSE;
}




void CDlgPlayback::OnBnClickedButtonPlayStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	if (m_bIsStopPlayBack)
	{
		return;
	}

	if (!NET_DVR_StopPlayBack(m_lPlayHandle))
	{
		CString CError;
		CError.Format("������� %d!\n", NET_DVR_GetLastError());
		MessageBox(CError);

		return;
	}

	GetDlgItem(IDC_BUTTON_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SCREENSHOT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FILM_EDITING)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText("����");

	m_lPlayHandle = -1;
	m_cIsPlaying = NET_DVR_PLAYSTART;

	m_bIsStopPlayBack = TRUE;
}


void CDlgPlayback::OnBnClickedButtonFast()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYFAST, NULL, NULL))
	{
		CString CError;
		CError.Format("������� %d!\n", NET_DVR_GetLastError());
		MessageBox(CError);

		return;
	}
}


void CDlgPlayback::OnBnClickedButtonSlow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYSLOW, NULL, NULL))
	{
		CString CError;
		CError.Format("������� %d!\n", NET_DVR_GetLastError());
		MessageBox(CError);

		return;
	}
}


void CDlgPlayback::OnBnClickedButtonScreenshot()
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

			bValues = NET_DVR_PlayBackCaptureFile(m_lPlayHandle, sPicFileName);

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
		MessageBox("���ȿ�������");
	}

}


void CDlgPlayback::OnBnClickedButtonFilmEditing()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	static char strFlieName[256];

	if (!m_bIsFilmEditing)
	{
		CTime CurTime = CTime::GetCurrentTime();

		memset(strFlieName, 0, sizeof(strFlieName));

		sprintf(strFlieName, "%04d%02d%02d%02d%02d%02d.mp4", CurTime.GetYear(), CurTime.GetMonth(),
			CurTime.GetDay(), CurTime.GetHour(), CurTime.GetMinute(), CurTime.GetSecond());

		StartFilmEditing(strFlieName);
	}
	else
	{
		StopFilmEditing(strFlieName);
	}

}


void CDlgPlayback::StartFilmEditing(char* pFlieName)
{
	if (!NET_DVR_PlayBackSaveData(m_lPlayHandle, pFlieName))
	{
		MessageBox("����ʧ��");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_FILM_EDITING)->SetWindowText(_T("��ͣ����"));
		m_bIsFilmEditing = TRUE;
	}
}


void CDlgPlayback::StopFilmEditing(char* pFlieName)
{
	if (!NET_DVR_StopPlayBackSave(m_lPlayHandle))
	{
		MessageBox("��ͣʧ��");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_FILM_EDITING)->SetWindowText(_T("��ʼ����"));
		m_bIsFilmEditing = FALSE;

		CString FlieName;
		FlieName.Format("��Ƶ�����ɹ�%s", pFlieName);
		MessageBox(FlieName);
	}
}


void CDlgPlayback::OnBnClickedButtonFind()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (!m_bIsStopPlayBack)
	{
		MessageBox("����ֹͣ��ǰ���ڻط�");
		return;
	}

	ByTimeFindPlayback(TRUE);

}


void CDlgPlayback::OnBnClickedButtonTimeOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (!m_bIsStopPlayBack)
	{
		MessageBox("����ֹͣ��ǰ���ڻط�");
		return;
	}

	ByTimeFindPlayback(TRUE);
}


void CDlgPlayback::OnBnClickedButtonDownload()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CDlgDownload dlgDownlad;

	dlgDownlad.SetPZTPreview(m_bIsLogin, m_iCurChanIndex, m_struDeviceInfo);

	dlgDownlad.DoModal();

}
