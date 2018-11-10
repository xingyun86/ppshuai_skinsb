// SkinSBDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SkinSBDemo.h"
#include "SkinSBDemoDlg.h"
#include <skinsb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSkinSBDemoDlg dialog




CSkinSBDemoDlg::CSkinSBDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkinSBDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bmScroll.LoadBitmap(IDB_SCROLL);
}

void CSkinSBDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEditCtrl);
}

BEGIN_MESSAGE_MAP(CSkinSBDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CSkinSBDemoDlg message handlers

BOOL CSkinSBDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ListCtrl.InsertColumn(0, TEXT("姓名"), LVCFMT_CENTER, 60);
	m_ListCtrl.InsertColumn(1, TEXT("年龄"), LVCFMT_CENTER, 60);
	m_ListCtrl.InsertColumn(2, TEXT("手机"), LVCFMT_CENTER, 60);
	m_ListCtrl.InsertColumn(4, TEXT("QQ"), LVCFMT_CENTER, 60);
	m_ListCtrl.InsertColumn(5, TEXT("地址"), LVCFMT_CENTER, 60);
	m_ListCtrl.InsertColumn(6, TEXT("信息文本"), LVCFMT_CENTER, 100);

	for( int i = 0; i < 100; i++ )
	{
		int nItem = m_ListCtrl.InsertItem(0, TEXT("测试"));
		m_ListCtrl.SetItemText(nItem, 1, TEXT("测试"));
		m_ListCtrl.SetItemText(nItem, 2, TEXT("测试"));
		m_ListCtrl.SetItemText(nItem, 3, TEXT("测试"));
		m_ListCtrl.SetItemText(nItem, 4, TEXT("测试"));
		m_ListCtrl.SetItemText(nItem, 5, TEXT("皮肤滚动条"));
	}

	//SkinSB_Init(GetDlgItem(IDC_RICHEDIT21)->GetSafeHwnd(), m_bmScroll);

	CRect rcClient;
	GetClientRect(&rcClient);

	//m_RichEditCtrl.MoveWindow(&rcClient);

	//设置控件皮肤
	SkinSB_Init(GetDlgItem(IDC_EDIT1)->GetSafeHwnd(), m_bmScroll);
	SkinSB_Init(m_ListCtrl, m_bmScroll);
	SkinSB_Init(m_RichEditCtrl, m_bmScroll);
	
	UINT nDoubleTime = GetDoubleClickTime();
	TRACE("Double click time %d\n", /*((nDoubleTime * 4) / 5) / 8*/nDoubleTime);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSkinSBDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSkinSBDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSkinSBDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CSkinSBDemoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	

	return 0;
}

void CSkinSBDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

}
