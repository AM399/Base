// DlgDownload.cpp : 实现文件
//

#include "stdafx.h"
#include "TestAMC.h"
#include "DlgDownload.h"
#include "afxdialogex.h"


// CDlgDownload 对话框

IMPLEMENT_DYNAMIC(CDlgDownload, CDialogEx)

CDlgDownload::CDlgDownload(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDownload::IDD, pParent)
	, m_dwFileType(0)
{

}

CDlgDownload::~CDlgDownload()
{
}

void CDlgDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_DATE, m_ctrStartDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_TIME, m_ctrStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FINISH_DATE, m_ctrFinishDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FINISH_TIME, m_ctrFinishTime);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
}


BEGIN_MESSAGE_MAP(CDlgDownload, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CDlgDownload::OnBnClickedButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CDlgDownload::OnBnClickedButtonFind)
END_MESSAGE_MAP()


// CDlgDownload 消息处理程序


BOOL CDlgDownload::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UINT nPngW = 1060;
	UINT nPngH = 760;
	
	int x, y;
	x = ::GetSystemMetrics(SM_CXSCREEN) * nPngW / 1920;
	y = ::GetSystemMetrics(SM_CYSCREEN) * nPngH / 1080;

	MoveWindow((GetSystemMetrics(SM_CXSCREEN) - x) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - y) / 2, x, y); 

	m_listFile.SetExtendedStyle(LVS_SHOWSELALWAYS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_listFile.InsertColumn(0, _T(" 序号 "), LVCFMT_LEFT, 50);
	m_listFile.InsertColumn(1, _T("文件名"), LVCFMT_CENTER, 190);
	m_listFile.InsertColumn(2, _T("文件的开始时间 "), LVCFMT_CENTER, 180);
	m_listFile.InsertColumn(3, _T("文件的结束时间 "), LVCFMT_CENTER, 180);
	m_listFile.InsertColumn(4, _T("文件大小 "), LVCFMT_CENTER, 80);





	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgDownload::SetPZTPreview(BOOL bIsLogin, UINT iCurChanIndex, LOCAL_DEVICE_INFO struDeviceInfo)
{
	m_bIsLogin = bIsLogin;
	memcpy((void*)&m_struDeviceInfo, (void*)&struDeviceInfo, sizeof(LOCAL_DEVICE_INFO));
	m_iCurChanIndex = iCurChanIndex;

	if (!m_bIsLogin)
	{
		m_lPlayHandle = -1;
	}

}

BOOL CDlgDownload::ByTimeFindVideoFile()
{

	DWORD   dwFileType = 0xff;
	NET_DVR_TIME lStartDateTime;
	NET_DVR_TIME lStopDateTime;

	CTime timeStartDate;
	CTime timeStartTime;
	CTime timeFinishDate;
	CTime timeFinishTime;

	UINT nConunt = 0;

	CString strBuff;

	memset(&lStartDateTime, 0, sizeof(NET_DVR_TIME));
	memset(&lStopDateTime, 0, sizeof(NET_DVR_TIME));

	if (0 == m_dwFileType)
	{
		dwFileType = 0xff;
	}
	else
	{
		dwFileType = m_dwFileType -1;
	}

	m_ctrStartDate.GetTime(timeStartDate);
	m_ctrStartTime.GetTime(timeStartTime);
	m_ctrFinishDate.GetTime(timeFinishDate);
	m_ctrFinishTime.GetTime(timeFinishTime);

	lStartDateTime.dwYear = timeStartDate.GetYear();
	lStartDateTime.dwMonth = timeStartDate.GetMonth();
	lStartDateTime.dwDay = timeStartDate.GetDay();

	lStartDateTime.dwHour = timeStartTime.GetHour();
	lStartDateTime.dwMinute = timeStartTime.GetMinute();
	lStartDateTime.dwSecond = timeStartTime.GetSecond();

	lStopDateTime.dwYear = timeFinishDate.GetYear();
	lStopDateTime.dwMonth = timeFinishDate.GetMonth();
	lStopDateTime.dwDay = timeFinishDate.GetDay();

	lStopDateTime.dwHour = timeFinishTime.GetHour();
	lStopDateTime.dwMinute = timeFinishTime.GetMinute();
	lStopDateTime.dwSecond = timeFinishTime.GetSecond();

	LONG lChannel = m_iCurChanIndex + 1;

	m_lPlayHandle = NET_DVR_FindFile(m_struDeviceInfo.lLoginID, lChannel, dwFileType,
		&lStartDateTime, &lStopDateTime);
	if (-1 == m_lPlayHandle)
	{
		CString CError;
		CError.Format("错误代码 %d!\n", NET_DVR_GetLastError());
		MessageBox(CError);
		return FALSE;
	}

	LONG result = NET_DVR_ISFINDING;
	NET_DVR_FIND_DATA  lFindData;
	
	while (1)
	{
		memset(&lFindData, 0, sizeof(NET_DVR_FIND_DATA));

		result = NET_DVR_FindNextFile(m_lPlayHandle, &lFindData);
		
		if (-1 == result)
		{
			CString CError;
			CError.Format("错误代码 %d!\n", NET_DVR_GetLastError());
			MessageBox(CError);
			m_lPlayHandle = -1;
			return FALSE;
		}

		
		if (NET_DVR_ISFINDING != result || NET_DVR_FILE_SUCCESS != result)
		{
			break;
		}

		strBuff = "";
		strBuff.Format("%d", nConunt);
		m_listFile.InsertItem(nConunt, strBuff, 0);

		m_listFile.SetItemText(nConunt, 1, lFindData.sFileName);

		strBuff = "";
		strBuff.Format("%d-%d-%d %d:%d:%d", lFindData.struStartTime.dwYear,
			lFindData.struStartTime.dwMonth, lFindData.struStartTime.dwDay,
			lFindData.struStartTime.dwHour, lFindData.struStartTime.dwMinute,
			lFindData.struStartTime.dwSecond);

		m_listFile.SetItemText(nConunt, 2, strBuff);

		strBuff = "";
		strBuff.Format("%d-%d-%d %d:%d:%d", lFindData.struStopTime.dwYear,
			lFindData.struStopTime.dwMonth, lFindData.struStopTime.dwDay,
			lFindData.struStopTime.dwHour, lFindData.struStopTime.dwMinute,
			lFindData.struStopTime.dwSecond);

		m_listFile.SetItemText(nConunt, 3, strBuff);

		strBuff = "";
		strBuff.Format("%d", lFindData.dwFileSize);

		m_listFile.SetItemText(nConunt, 4, strBuff);

		nConunt++;
	}

	switch (result)
	{
	case NET_DVR_FILE_SUCCESS:
	case NET_DVR_ISFINDING:
		break;

	case NET_DVR_FILE_NOFIND:
	case NET_DVR_NOMOREFILE:
		MessageBox("未查找到文件");
		return FALSE;

	case NET_DVR_FILE_EXCEPTION:
		MessageBox("查找文件时异常");
		return FALSE;

	default:
		break;
	}
}

void CDlgDownload::OnBnClickedButtonDownload()
{
	// TODO:  在此添加控件通知处理程序代码
	vector<CString> vectorFile;

	char   sSavedFileName[256] ;

	m_listFile.InsertItem(0, "1", 0);
	m_listFile.SetItemText(0, 1, "是的");
	m_listFile.SetItemText(0, 2, "是的");

	memset(&sSavedFileName, 0, sizeof(sSavedFileName));

	::GetCurrentDirectory(MAX_PATH, sSavedFileName);

#if 0
	if (!m_bIsLogin || 0 == m_listFile.GetItemCount())
	{
		return;
	}
#endif


	

	for (int i = 0; i < m_listFile.GetItemCount(); i++)
	{
		if (m_listFile.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			vectorFile.push_back(m_listFile.GetItemText(i, 1));
		}
	}

	for (int i = 0; vectorFile.size(); i++)
	{

		NET_DVR_GetFileByName(m_struDeviceInfo.lLoginID, vectorFile.at(i).GetBuffer(), sSavedFileName);
	}
	

}


void CDlgDownload::OnBnClickedButtonFind()
{
	// TODO:  在此添加控件通知处理程序代码

	if (!m_bIsLogin )
	{
		return;
	}

	ByTimeFindVideoFile();

	UpdateData();
}



