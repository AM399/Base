#pragma once
#include "GeneralDef.h"
#include "THButton.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "DlgDownload.h"
#include "afxcmn.h"

// CDlgPlayback �Ի���

class CDlgPlayback : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPlayback)

public:
	CDlgPlayback(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPlayback();

// �Ի�������
	enum { IDD = IDD_DIALOG_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	

public:
	afx_msg void OnBnClickedButtonPlay();



	virtual BOOL OnInitDialog();
	void SetPZTPreview(BOOL bIsLogin, UINT iCurChanIndex, LOCAL_DEVICE_INFO struDeviceInfo);

	BOOL ByTimeFindPlayback(BOOL bIsOnlyFind);


private:
	CButton m_BtnPlayStop;
	CButton m_BtnSlow;
	CButton m_BtnPlay;
	CButton m_BtnFast;
	CButton m_BtnScreenshot;
	CButton m_BtnFilmEditing;
	CButton m_BtnmDownload;
	CButton m_BtnFind;
	CButton m_BtnTimeOk;
	CEdit m_EditHour;
	CEdit m_EditMinute;
	CEdit m_EditSecond;
	CMonthCalCtrl m_Data;

	BOOL m_bIsLogin; //��¼����
	LOCAL_DEVICE_INFO m_struDeviceInfo; //��������
	UINT m_iCurChanIndex; //ͨ����
	LONG m_lPlayHandle;   //��¼ID��Ϣ
	UCHAR m_cIsPlaying;    //���ſ���
	BOOL m_bIsFilmEditing; 

public:
	afx_msg void OnBnClickedButtonPlayStop();
	afx_msg void OnBnClickedButtonFast();
	afx_msg void OnBnClickedButtonSlow();

	afx_msg void OnBnClickedButtonScreenshot();
	afx_msg void OnBnClickedButtonFilmEditing();
private:
	void StartFilmEditing(char* pFlieName);
	void StopFilmEditing(char* pFlieName);


	afx_msg void OnBnClickedButtonFind();

	BOOL m_bIsStopPlayBack;
public:
	afx_msg void OnBnClickedButtonTimeOk();
	afx_msg void OnBnClickedButtonDownload();
private:
	CTreeCtrl m_Tree;
};
