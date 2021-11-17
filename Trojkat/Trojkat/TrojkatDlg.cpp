
// TrojkatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Trojkat.h"
#include "TrojkatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrojkatDlg dialog



CTrojkatDlg::CTrojkatDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CTrojkatDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrojkatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NODE_A_ACTIVE, m_NODE_A_ACTIVE);
	DDX_Control(pDX, IDC_NODE_B_ACTIVE, m_NODE_B_ACTIVE);
	DDX_Control(pDX, IDC_NODE_C_ACTIVE, m_NODE_C_ACTIVE);
	DDX_Control(pDX, IDC_NODE_A_SLIDER_X, m_NODE_A_SLIDER_X);
	DDX_Control(pDX, IDC_NODE_A_SLIDER_Y, m_NODE_A_SLIDER_Y);
	DDX_Control(pDX, IDC_NODE_B_SLIDER_X, m_NODE_B_SLIDER_X);
	DDX_Control(pDX, IDC_NODE_B_SLIDER_Y, m_NODE_B_SLIDER_Y);
	DDX_Control(pDX, IDC_NODE_C_SLIDER_X, m_NODE_C_SLIDER_X);
	DDX_Control(pDX, IDC_NODE_C_SLIDER_Y, m_NODE_C_SLIDER_Y);
}

BEGIN_MESSAGE_MAP(CTrojkatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_B_SLIDER_Y, &CTrojkatDlg::OnNMCustomdrawNodeBSliderY)
	ON_BN_CLICKED(IDC_NODE_A_ACTIVE, &CTrojkatDlg::OnBnClickedNodeAActive)
	ON_BN_CLICKED(IDC_NODE_B_ACTIVE, &CTrojkatDlg::OnBnClickedNodeBActive)
	ON_BN_CLICKED(IDC_NODE_C_ACTIVE, &CTrojkatDlg::OnBnClickedNodeCActive)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_A_SLIDER_X, &CTrojkatDlg::OnCustomdrawNodeASliderX)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_A_SLIDER_Y, &CTrojkatDlg::OnCustomdrawNodeASliderY)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_B_SLIDER_X, &CTrojkatDlg::OnCustomdrawNodeBSliderX)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_B_SLIDER_Y, &CTrojkatDlg::OnCustomdrawNodeBSliderY)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_C_SLIDER_X, &CTrojkatDlg::OnCustomdrawNodeCSliderX)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_C_SLIDER_Y, &CTrojkatDlg::OnCustomdrawNodeCSliderY)
END_MESSAGE_MAP()


// CTrojkatDlg message handlers

BOOL CTrojkatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// sliders -------=----
	m_NODE_A_SLIDER_X.SetRangeMin(-100);
	m_NODE_A_SLIDER_X.SetRangeMax(100);
	m_NODE_A_SLIDER_X.SetPos(0);

	m_NODE_A_SLIDER_Y.SetRangeMin(-100);
	m_NODE_A_SLIDER_Y.SetRangeMax(100);
	m_NODE_A_SLIDER_Y.SetPos(0);

	m_NODE_B_SLIDER_X.SetRangeMin(-100);
	m_NODE_B_SLIDER_X.SetRangeMax(100);
	m_NODE_B_SLIDER_X.SetPos(0);

	m_NODE_B_SLIDER_Y.SetRangeMin(-100);
	m_NODE_B_SLIDER_Y.SetRangeMax(100);
	m_NODE_B_SLIDER_Y.SetPos(0);

	m_NODE_C_SLIDER_X.SetRangeMin(-100);
	m_NODE_C_SLIDER_X.SetRangeMax(100);
	m_NODE_C_SLIDER_X.SetPos(0);

	m_NODE_C_SLIDER_Y.SetRangeMin(-100);
	m_NODE_C_SLIDER_Y.SetRangeMax(100);
	m_NODE_C_SLIDER_Y.SetPos(0);

	// checkboxes [x]
	m_NODE_A_ACTIVE.SetCheck(true);
	m_NODE_B_ACTIVE.SetCheck(true);
	m_NODE_C_ACTIVE.SetCheck(true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrojkatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrojkatDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrojkatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// -=-=-=-=-=-=-=-=-=-=-=-= checkboxes -=-=-=-=-=-=-=-=-=-=-=-=

void CTrojkatDlg::OnBnClickedNodeAActive() {}

void CTrojkatDlg::OnBnClickedNodeBActive() {}

void CTrojkatDlg::OnBnClickedNodeCActive() {}


// // -=-=-=-=-=-=-=-=-=-=-=-= sliders -=-=-=-=-=-=-=-=-=-=-=-=

void CTrojkatDlg::OnCustomdrawNodeASliderX(NMHDR *pNMHDR, LRESULT *pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; }

void CTrojkatDlg::OnCustomdrawNodeASliderY(NMHDR *pNMHDR, LRESULT *pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; }

void CTrojkatDlg::OnCustomdrawNodeBSliderX(NMHDR *pNMHDR, LRESULT *pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; }

void CTrojkatDlg::OnCustomdrawNodeBSliderY(NMHDR *pNMHDR, LRESULT *pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; }

void CTrojkatDlg::OnCustomdrawNodeCSliderX(NMHDR *pNMHDR, LRESULT *pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; }

void CTrojkatDlg::OnCustomdrawNodeCSliderY(NMHDR *pNMHDR, LRESULT *pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; }
