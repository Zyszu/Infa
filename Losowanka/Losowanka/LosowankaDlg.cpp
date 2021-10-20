
// LosowankaDlg.cpp : implementation file
//
#include <time.h>

#include "stdafx.h"
#include "Losowanka.h"
#include "LosowankaDlg.h"
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


// CLosowankaDlg dialog



CLosowankaDlg::CLosowankaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLosowankaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLosowankaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_NUMBER1, r_number1);
	//  DDX_Control(pDX, IDC_NUMBER2, r_number2);
	//  DDX_Control(pDX, IDC_NUMBER3, r_number3);
	//  DDX_Control(pDX, IDC_NUMBER4, r_number4);
	//  DDX_Control(pDX, IDC_NUMBER5, r_number5);
	DDX_Control(pDX, IDC_OUTPUT1, m_output1);
	DDX_Control(pDX, IDC_OUTPUT2, m_output2);
	DDX_Control(pDX, IDC_OUTPUT3, m_output3);
	DDX_Control(pDX, IDC_OUTPUT4, m_output4);
	DDX_Control(pDX, IDC_OUTPUT5, m_output5);
	DDX_Control(pDX, IDC_NUMBER1, m_rand_number1);
	DDX_Control(pDX, IDC_NUMBER2, m_rand_number2);
	DDX_Control(pDX, IDC_NUMBER3, m_rand_number3);
	DDX_Control(pDX, IDC_NUMBER4, m_rand_number4);
	//  DDX_Control(pDX, IDC_NUMBER5, m_rand_number6);
	DDX_Control(pDX, IDC_NUMBER5, m_rand_number5);
	DDX_Control(pDX, IDC_SORT_INFO, m_sort_info);
	DDX_Control(pDX, IDC_SORT_ASC, m_sort_asc);
}

BEGIN_MESSAGE_MAP(CLosowankaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_SORT_ASC, &CLosowankaDlg::OnClickedSortAsc)
//	ON_BN_CLICKED(IDC_SORT_DESC, &CLosowankaDlg::OnClickedSortDesc)
	ON_BN_CLICKED(IDC_GEN_RAND_NUM, &CLosowankaDlg::OnClickedGenRandNum)
	ON_BN_CLICKED(IDC_SORT, &CLosowankaDlg::OnClickedSort)
	ON_BN_CLICKED(IDC_SORT_ASC, &CLosowankaDlg::OnClickedSortAsc)
END_MESSAGE_MAP()


void CLosowankaDlg::gen_numbers()
{
	CString str_numbers[5];
	int int_numbers[5];

	for (size_t i = 0; i < 5; i++) int_numbers[i] = rand() % 100 + 1;

	for (size_t i = 0; i < 5; i++) str_numbers[i].Format(_T("%i"), int_numbers[i]);

	m_rand_number1.SetWindowTextW(str_numbers[0]);
	m_rand_number2.SetWindowTextW(str_numbers[1]);
	m_rand_number3.SetWindowTextW(str_numbers[2]);
	m_rand_number4.SetWindowTextW(str_numbers[3]);
	m_rand_number5.SetWindowTextW(str_numbers[4]);

	m_output1.SetWindowTextW((CString)"");
	m_output2.SetWindowTextW((CString)"");
	m_output3.SetWindowTextW((CString)"");
	m_output4.SetWindowTextW((CString)"");
	m_output5.SetWindowTextW((CString)"");
}

// CLosowankaDlg message handlers

BOOL CLosowankaDlg::OnInitDialog()
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

	srand(time(0));
	gen_numbers();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLosowankaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLosowankaDlg::OnPaint()
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
HCURSOR CLosowankaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void int_swap(int& i, int&j) { int k; k = i; i = j; j = k; }

void CLosowankaDlg::bubbleSort(bool ascending = true)
{
	CString str_numbers[5];
	int int_numbers[5];

	m_rand_number1.GetWindowTextW(str_numbers[0]);
	m_rand_number2.GetWindowTextW(str_numbers[1]);
	m_rand_number3.GetWindowTextW(str_numbers[2]);
	m_rand_number4.GetWindowTextW(str_numbers[3]);
	m_rand_number5.GetWindowTextW(str_numbers[4]);

	for (size_t i = 0; i < 5; i++) int_numbers[i] = _ttoi(str_numbers[i]);

	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 4 - i; j++){
			bool statement = ascending == true ? int_numbers[j] > int_numbers[j + 1] : int_numbers[j] < int_numbers[j + 1];
			if (statement) int_swap(int_numbers[j], int_numbers[j + 1]);
		}

	for (size_t i = 0; i < 5; i++) str_numbers[i].Format(_T("%i"), int_numbers[i]);

	m_output1.SetWindowTextW(str_numbers[0]);
	m_output2.SetWindowTextW(str_numbers[1]);
	m_output3.SetWindowTextW(str_numbers[2]);
	m_output4.SetWindowTextW(str_numbers[3]);
	m_output5.SetWindowTextW(str_numbers[4]);
}

void CLosowankaDlg::OnClickedGenRandNum() { gen_numbers(); }

void CLosowankaDlg::OnClickedSortAsc()
{
	CString _return[2] = { (CString)"sort ascending", (CString)"sort descending" };
	m_sort_info.SetWindowTextW(_return[m_sort_asc.GetCheck()]);
}

void CLosowankaDlg::OnClickedSort() { bubbleSort(!m_sort_asc.GetCheck()); }

