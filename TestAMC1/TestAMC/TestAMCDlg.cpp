
// TestAMCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestAMC.h"
#include "TestAMCDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestAMCDlg 对话框



CTestAMCDlg::CTestAMCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestAMCDlg::IDD, pParent)
	, m_Port(8000)
	, m_User(_T("admin"))
	, m_Password(_T("admin12345"))
	, m_bIsLogin(FALSE)
	, m_CurSelTab(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iCurChanIndex = 0;
}

void CTestAMCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_VCR_IP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_USER, m_User);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);
	DDX_Control(pDX, IDC_TAB_CONTROL, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CTestAMCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CTestAMCDlg::OnBnClickedButtonLogin)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, &CTestAMCDlg::OnTcnSelchangeTabControl)
	ON_WM_CLOSE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CTestAMCDlg 消息处理程序

BOOL CTestAMCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	UINT nPngW = 1240;
	UINT nPngH = 840;
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	int x, y;
	x = ::GetSystemMetrics(SM_CXSCREEN) * nPngW / 1920;
	y = ::GetSystemMetrics(SM_CYSCREEN) * nPngH / 1080;
	CRect rcw(0, 0, x , y );
	MoveWindow(rcw, true);

	MoveWindow(0, 0, nPngW, nPngH);

	// TODO:  在此添加额外的初始化代码
	m_VCR_IP.SetAddress(192,168,1,207) ;

	m_tabCtrl.InsertItem(0, _T(" 预览 "));
	m_tabCtrl.InsertItem(1, _T(" 回放 "));
	m_tabCtrl.InsertItem(2, _T(" 图片 "));
	m_tabCtrl.InsertItem(3, _T(" 配置 "));

	m_dlgPreview.Create(IDD_DIALOG_PREVIEW, &m_tabCtrl);
	m_dlgPlayback.Create(IDD_DIALOG_PLAYBACK, &m_tabCtrl);
	m_dlgPicture.Create(IDD_DIALOG_PICTURE, &m_tabCtrl);
	m_dlgConfiguration.Create(IDD_DIALOG_CONFIGURATION, &m_tabCtrl);

	CRect rc;
	m_tabCtrl.GetClientRect(&rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;

	m_dlgPreview.MoveWindow(&rc);
	m_dlgPlayback.MoveWindow(&rc);
	m_dlgPicture.MoveWindow(&rc);
	m_dlgConfiguration.MoveWindow(&rc);

	m_pDialog[0] = &m_dlgPreview;
	m_pDialog[1] = &m_dlgPlayback;
	m_pDialog[2] = &m_dlgPicture;
	m_pDialog[3] = &m_dlgConfiguration;

	m_pDialog[0]->ShowWindow(SW_SHOW);
	m_pDialog[1]->ShowWindow(SW_HIDE);
	m_pDialog[2]->ShowWindow(SW_HIDE);
	m_pDialog[3]->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestAMCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestAMCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestAMCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestAMCDlg::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	if (! m_bIsLogin)
	{
		if (!DoLogin())
			return;

		DoGetDeviceResoureCfg();
		CreateDeviceTree();
		GetDecoderCfg();
		InitDecoderReferCtrl();
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("退出");
		m_bIsLogin = TRUE;

		m_dlgPreview.SetPZTPreview(m_bIsLogin, m_iCurChanIndex, m_struDeviceInfo);
		m_dlgPlayback.SetPZTPreview(m_bIsLogin, m_iCurChanIndex, m_struDeviceInfo);

	}
	else
	{
	
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("登录");

		if (m_bIsLogin)
		{
			//StopPlay();
			NET_DVR_Logout_V30(m_struDeviceInfo.lLoginID);
		}
		m_bIsLogin = FALSE;
		memset(&m_struDeviceInfo, 0, sizeof(m_struDeviceInfo));

		m_dlgPreview.SetPZTPreview(m_bIsLogin, -1, m_struDeviceInfo);
		m_dlgPlayback.SetPZTPreview(m_bIsLogin, -1, m_struDeviceInfo);
	}

}

/*************************************************
函数名:    	DoLogin
函数描述:	向设备注册
输入参数:
输出参数:
返回值:
**************************************************/
BOOL CTestAMCDlg::DoLogin()
{
	UpdateData(TRUE);

	CString IPAddress;
	BYTE nFirld0, nFiedl1, nFiedl2, nFiedl3;
	m_VCR_IP.GetAddress(nFirld0, nFiedl1, nFiedl2, nFiedl3);
	IPAddress.Format("%d.%d.%d.%d", nFirld0, nFiedl1, nFiedl2, nFiedl3);

	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
	memset(&DeviceInfoTmp, 0, sizeof(NET_DVR_DEVICEINFO_V30));

	LONG lLoginID = NET_DVR_Login_V30(IPAddress.GetBuffer(IPAddress.GetLength()), \
		m_Port, m_User.GetBuffer(m_User.GetLength()), \
		m_Password.GetBuffer(m_Password.GetLength()), &DeviceInfoTmp);

	if (-1 == lLoginID)
	{
		CString CError;
		CError.Format("Login to Device failed %d!\n", NET_DVR_GetLastError());
		MessageBox(CError);
		return FALSE;
	}

	m_struDeviceInfo.lLoginID = lLoginID;
	m_struDeviceInfo.iDeviceChanNum = DeviceInfoTmp.byChanNum;
	m_struDeviceInfo.iIPChanNum = DeviceInfoTmp.byIPChanNum;
	m_struDeviceInfo.iStartChan = DeviceInfoTmp.byStartChan;
	m_struDeviceInfo.iIPStartChan = DeviceInfoTmp.byStartDChan;

	return TRUE;
}


void CTestAMCDlg::DoGetDeviceResoureCfg()
{
	NET_DVR_IPPARACFG_V40 IPAccessCfg;
	memset(&IPAccessCfg, 0, sizeof(IPAccessCfg));

	DWORD dowRetturned;

	m_struDeviceInfo.bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo.lLoginID,
		NET_DVR_GET_IPPARACFG_V40, 0, &IPAccessCfg, sizeof(NET_DVR_IPPARACFG_V40), &dowRetturned);

	int i;
	if (!m_struDeviceInfo.bIPRet)   //不支持ip接入,9000以下设备不支持禁用模拟通道
	{
		for (i = 0; i<MAX_ANALOG_CHANNUM; i++)
		{
			if (i < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[i].iChanIndex = i + m_struDeviceInfo.iStartChan;  //通道号
				m_struDeviceInfo.struChanInfo[i].bEnable = TRUE;

			}
			else
			{
				m_struDeviceInfo.struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName, "");
			}
		}
	}
	else        //支持IP接入，9000设备
	{
		for (i = 0; i<MAX_ANALOG_CHANNUM; i++)  //模拟通道
		{
			if (i < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[i].iChanIndex = i + m_struDeviceInfo.iStartChan;
				if (IPAccessCfg.byAnalogChanEnable[i])
				{
					m_struDeviceInfo.struChanInfo[i].bEnable = TRUE;
				}
				else
				{
					m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				}

			}
			else//clear the state of other channel
			{
				m_struDeviceInfo.struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName, "");
			}
		}

		//数字通道
		for (i = 0; i<MAX_IP_CHANNEL; i++)
		{
			if (IPAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable)  //ip通道在线
			{
				m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = TRUE;
				m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = i + IPAccessCfg.dwStartDChan;
				sprintf(m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].chChanName, "IP Camera %d", i + 1);

			}
			else
			{
				m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = FALSE;
				m_struDeviceInfo.struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = -1;
			}
		}


	}
}


void CTestAMCDlg::CreateDeviceTree()
{
	for (int i = 0; i<MAX_CHANNUM_V30; i++)
	{
		if (m_struDeviceInfo.struChanInfo[i].bEnable)   //通道有效，插入通道树
		{
			m_iCurChanIndex = i;
		}
	}
}

void CTestAMCDlg::GetDecoderCfg()
{

}


void CTestAMCDlg::InitDecoderReferCtrl()
{
}


void CTestAMCDlg::OnTcnSelchangeTabControl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;


	//把当前的页面隐藏起来
	m_pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_CurSelTab = m_tabCtrl.GetCurSel();
	//把新的页面显示出来
	m_pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

}

void CTestAMCDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_bIsLogin)
	{
		NET_DVR_Logout_V30(m_struDeviceInfo.lLoginID);
	}
	CDialogEx::OnClose();
}
