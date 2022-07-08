
// TestAMCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestAMC.h"
#include "TestAMCDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestAMCDlg �Ի���



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


// CTestAMCDlg ��Ϣ�������

BOOL CTestAMCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	UINT nPngW = 1240;
	UINT nPngH = 840;
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	int x, y;
	x = ::GetSystemMetrics(SM_CXSCREEN) * nPngW / 1920;
	y = ::GetSystemMetrics(SM_CYSCREEN) * nPngH / 1080;
	CRect rcw(0, 0, x , y );
	MoveWindow(rcw, true);

	MoveWindow(0, 0, nPngW, nPngH);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_VCR_IP.SetAddress(192,168,1,207) ;

	m_tabCtrl.InsertItem(0, _T(" Ԥ�� "));
	m_tabCtrl.InsertItem(1, _T(" �ط� "));
	m_tabCtrl.InsertItem(2, _T(" ͼƬ "));
	m_tabCtrl.InsertItem(3, _T(" ���� "));

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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestAMCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("�˳�");
		m_bIsLogin = TRUE;

		m_dlgPreview.SetPZTPreview(m_bIsLogin, m_iCurChanIndex, m_struDeviceInfo);
		m_dlgPlayback.SetPZTPreview(m_bIsLogin, m_iCurChanIndex, m_struDeviceInfo);

	}
	else
	{
	
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("��¼");

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
������:    	DoLogin
��������:	���豸ע��
�������:
�������:
����ֵ:
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
	if (!m_struDeviceInfo.bIPRet)   //��֧��ip����,9000�����豸��֧�ֽ���ģ��ͨ��
	{
		for (i = 0; i<MAX_ANALOG_CHANNUM; i++)
		{
			if (i < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[i].iChanIndex = i + m_struDeviceInfo.iStartChan;  //ͨ����
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
	else        //֧��IP���룬9000�豸
	{
		for (i = 0; i<MAX_ANALOG_CHANNUM; i++)  //ģ��ͨ��
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

		//����ͨ��
		for (i = 0; i<MAX_IP_CHANNEL; i++)
		{
			if (IPAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable)  //ipͨ������
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
		if (m_struDeviceInfo.struChanInfo[i].bEnable)   //ͨ����Ч������ͨ����
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;


	//�ѵ�ǰ��ҳ����������
	m_pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//�õ��µ�ҳ������
	m_CurSelTab = m_tabCtrl.GetCurSel();
	//���µ�ҳ����ʾ����
	m_pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);

}

void CTestAMCDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bIsLogin)
	{
		NET_DVR_Logout_V30(m_struDeviceInfo.lLoginID);
	}
	CDialogEx::OnClose();
}
