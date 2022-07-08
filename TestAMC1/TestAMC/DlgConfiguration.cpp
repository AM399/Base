// DlgConfiguration.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestAMC.h"
#include "DlgConfiguration.h"
#include "afxdialogex.h"
#include "tinyxml.h"

int count = 0;
  
// CDlgConfiguration �Ի���

IMPLEMENT_DYNAMIC(CDlgConfiguration, CDialogEx)

CDlgConfiguration::CDlgConfiguration(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConfiguration::IDD, pParent)
{

		MSXML2::IXMLDOMDocument2Ptr pXMLDom;
		MSXML2::IXMLDOMProcessingInstructionPtr pi;
		
		HRESULT hr;
		CoInitialize(NULL);
		hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument));
		if (FAILED(hr))
		{
			printf("Failed to CreateInstance on an XML DOM");

		}
		pXMLDom->preserveWhiteSpace = VARIANT_TRUE;

		//�������
		pi = pXMLDom->createProcessingInstruction("xml", "version='1.0' encoding='GBK'");
		if (pi != NULL) {
			pXMLDom->appendChild(pi);
			pi.Release();
		}
		// ���������
		_variant_t varNodeType((short)MSXML2::NODE_ELEMENT);
		MSXML2::IXMLDOMNodePtr pXMLNodeRoot = NULL;
		pXMLNodeRoot = pXMLDom->createNode(varNodeType, _T("root"), _T(""));
		pXMLDom->appendChild(pXMLNodeRoot);

		MSXML2::IXMLDOMElementPtr  xmlLabel;
		xmlLabel = pXMLDom->createElement(_T("QueryCondition"));

		//��������
//		xmlRoot->setAttribute("id", (const char *)"ID123s");
		pXMLNodeRoot->appendChild(xmlLabel);
		MSXML2::IXMLDOMElementPtr pNode_hphm;

		//��ӡ�hphm��Ԫ��
		pNode_hphm = pXMLDom->createElement((_bstr_t)"hphm");
		pNode_hphm->Puttext((_bstr_t)(const char *)"�� BAA123");
		xmlLabel->appendChild(pNode_hphm);

		MSXML2::IXMLDOMElementPtr pNode_hpzl;
		//��ӡ�hpzl��Ԫ��
		pNode_hpzl = pXMLDom->createElement("hpzl");
		pNode_hpzl->Puttext((const char *)"02");
		xmlLabel->appendChild(pNode_hpzl);

		MSXML2::IXMLDOMElementPtr pNode_clsbdh;
		//��ӡ�hpzl��Ԫ��
		pNode_clsbdh = pXMLDom->createElement("clsbdh");
		pNode_clsbdh->Puttext((const char *)"1234");
		xmlLabel->appendChild(pNode_clsbdh);


		hr = pXMLDom->save((_variant_t)"xmDom.xml");
		
}

CDlgConfiguration::~CDlgConfiguration()
{
}

void CDlgConfiguration::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE_DIRECTORY, m_TreeCtrl);
	DDX_Control(pDX, IDC_EDIT_VIEW, m_etView);
}


BEGIN_MESSAGE_MAP(CDlgConfiguration, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_TREE_DIRECTORY, &CDlgConfiguration::OnNMClickTreeDirectory)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgConfiguration::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgConfiguration ��Ϣ�������


BOOL CDlgConfiguration::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

//	m_TreeCtrl.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
	m_TreeCtrl.SetBkColor(RGB(200, 200, 255)); //�������οؼ��ı���ɫ
	m_TreeCtrl.SetTextColor(RGB(127, 0, 0));   //�����ı���ɫ
//	m_TreeCtrl.Select(h11, TVGN_CARET);       //����h11Ϊѡ����

	//��Ӹ��ڵ�root
	HTREEITEM root = m_TreeCtrl.InsertItem(_T("root"));
	m_TreeCtrl.SetItemData(root, 1);
	//��Ӹ��ڵ�parent1��parent2
	HTREEITEM parent1 = m_TreeCtrl.InsertItem(_T("parent1"));
	m_TreeCtrl.SetItemData(parent1, 2);
	HTREEITEM parent2 = m_TreeCtrl.InsertItem(_T("parent2"));
	m_TreeCtrl.SetItemData(parent2, 3);
	//��Ӹ��ڵ�root���ӽڵ�rootchild
	HTREEITEM rootchild = m_TreeCtrl.InsertItem(_T("rootchild"), root);
	m_TreeCtrl.SetItemData(rootchild, 4);
	//��Ӹ��ڵ�parent1���ӽڵ�
	HTREEITEM child1 = m_TreeCtrl.InsertItem(_T("child1"), parent1);
	m_TreeCtrl.SetItemData(child1, 5);
	HTREEITEM child2 = m_TreeCtrl.InsertItem(_T("child2"), parent1, child1);
	m_TreeCtrl.SetItemData(child2, 6);
	HTREEITEM child3 = m_TreeCtrl.InsertItem(_T("child3"), parent1, child2);
	m_TreeCtrl.SetItemData(child3, 7);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgConfiguration::OnNMClickTreeDirectory(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CPoint pt = GetCurrentMessage()->pt;

	m_TreeCtrl.ScreenToClient(&pt);

	UINT uFlags = 0;

	HTREEITEM hItem = m_TreeCtrl.HitTest(pt, &uFlags);

	if ((hItem != NULL) && (TVHT_ONITEMLABEL & uFlags))
	{
		int nDat = m_TreeCtrl.GetItemData(hItem);
		switch (nDat)
		{
		case 1:   MessageBox("root");   break;
		case 2:   MessageBox("parent1");   break;
		case 3:   MessageBox("parent2");   break;
		case 4:   MessageBox("rootchild");   break;
		case 5:   MessageBox("child1");   break;
		case 6:   MessageBox("child2");   break;
		case 7:   MessageBox("child3");   break;
		case 8:   MessageBox("child11");   break;
		case 9:   MessageBox("child22");   break;
		case 10:   MessageBox("child33");   break;
		default:   MessageBox("ERROR");

		}
	}



	*pResult = 0;

}


void CDlgConfiguration::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MSXML2::IXMLDOMDocument2Ptr pXMLDom;
	MSXML2::IXMLDOMElementPtr XMLRoot;

	HRESULT hr;
	CoInitialize(NULL);
	hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument));
	if (FAILED(hr))
	{
		printf("Failed to CreateInstance on an XML DOM");

	}

	if (! pXMLDom->load("xmDom.xml"))
	{
		return;
	}
	
	MSXML2::IXMLDOMNodeListPtr nodeList = NULL;
	XMLRoot = pXMLDom->GetdocumentElement();
	XMLRoot->get_childNodes(&nodeList);
	LONG listlength;

	nodeList->get_length(&listlength);

	for (int i = 0; i < listlength; i++)
	{
		CComPtr<MSXML2::IXMLDOMNode> spNode;
		nodeList->get_item(i, &spNode);
		ProcessNode(spNode, 0);
	}


	
}


void CDlgConfiguration::ProcessNode(CComPtr<MSXML2::IXMLDOMNode>& spNode, int tmp)
{
	MSXML2::DOMNodeType eNodeType;
	spNode->get_nodeType(&eNodeType);
	if (eNodeType == NODE_ELEMENT)
	{
		BSTR bstrName ;
		BSTR bstrText;
		spNode->get_nodeName(&bstrName);
		spNode->get_text(&bstrText);


		int nLen = m_etView.GetWindowTextLength();
		m_etView.SetSel(nLen, -1);

		CString strtmp;

		
		
		for (int i = 0; i < tmp; i++)
		{
			strtmp += "\t";
		}

		if (!strcmp("QueryCondition", (char*)(_bstr_t)bstrName))
		{
			m_etView.ReplaceSel(strtmp + "<" + CString(bstrName) + ">" + "\r\n");
		}
		else
		{
			m_etView.ReplaceSel(strtmp + "<" + CString(bstrName) + ">" + CString(bstrText) + +"\r\n");
		}

		
		LONG listlength;

		MSXML2::IXMLDOMNodeListPtr spNodeList = NULL;

		spNode->get_childNodes(&spNodeList);
		spNodeList->get_length(&listlength);
	
		int tmp = 0;
		
		for (int i = 0; i < listlength; i++)
		{
			CComPtr<MSXML2::IXMLDOMNode> pNode;
			spNodeList->get_item(i, &pNode);

			if (i == 0)
			{
				tmp = ++count;
			}
			MSXML2::DOMNodeType eNodeType;
			pNode->get_nodeType(&eNodeType);
			if (eNodeType == NODE_TEXT)
			{
				int nLen = m_etView.GetWindowTextLength();
				m_etView.SetSel(nLen-2, -1);
				m_etView.ReplaceSel("");

			}
			ProcessNode(pNode, tmp);



		}

		if (!strcmp("QueryCondition", (char*)(_bstr_t)bstrName))
		{
			m_etView.ReplaceSel( "<" + CString(bstrName) + ">" + "\r\n");
		}
		else
		{
			m_etView.ReplaceSel("<" + CString(bstrName) + ">" + "\r\n");
		}

	}

}
