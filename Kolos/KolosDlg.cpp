
// KolosDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Kolos.h"
#include "KolosDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKolosDlg dialog



CKolosDlg::CKolosDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KOLOS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKolosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT1, m_input1);
	DDX_Control(pDX, IDC_INPUT2, m_input2);
	DDX_Control(pDX, IDC_INPUT3, m_input3);
	DDX_Control(pDX, IDC_INPUT4, m_input4);
	DDX_Control(pDX, IDC_INPUT5, m_input5);
	DDX_Control(pDX, IDC_INPUT6, m_input6);
	DDX_Control(pDX, IDC_INPUT7, m_input7);
	//  DDX_Control(pDX, IDC_INPUT8, m_input9);
	//  DDX_Control(pDX, IDC_INPUT9, m_input9);
	//  DDX_Control(pDX, IDC_INPUT8, m_input8);
	DDX_Control(pDX, IDC_INPUT10, m_input10);
	DDX_Control(pDX, IDC_INPUT8, m_input8);
	DDX_Control(pDX, IDC_INPUT9, m_input9);
	DDX_Control(pDX, IDC_OUTPUT_AVERAGE, m_output_average);
	DDX_Control(pDX, IDC_OUTPUT_STANDARD_DEVIATION, m_output_standard_deviation);
}

BEGIN_MESSAGE_MAP(CKolosDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_INPUT1, &CKolosDlg::OnChangeInput1)
	ON_EN_CHANGE(IDC_INPUT2, &CKolosDlg::OnChangeInput2)
	ON_EN_CHANGE(IDC_INPUT3, &CKolosDlg::OnChangeInput3)
	ON_EN_CHANGE(IDC_INPUT4, &CKolosDlg::OnChangeInput4)
	ON_EN_CHANGE(IDC_INPUT5, &CKolosDlg::OnChangeInput5)
	ON_EN_CHANGE(IDC_INPUT6, &CKolosDlg::OnChangeInput6)
	ON_EN_CHANGE(IDC_INPUT7, &CKolosDlg::OnChangeInput7)
	ON_EN_CHANGE(IDC_INPUT10, &CKolosDlg::OnChangeInput10)
	ON_EN_CHANGE(IDC_INPUT8, &CKolosDlg::OnChangeInput8)
	ON_EN_CHANGE(IDC_INPUT9, &CKolosDlg::OnChangeInput9)
	ON_BN_CLICKED(IDC_BUTTON1, &CKolosDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CKolosDlg message handlers

BOOL CKolosDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// dla wygody
	input[0] = &m_input1;
	input[1] = &m_input2;
	input[2] = &m_input3;
	input[3] = &m_input4;
	input[4] = &m_input5;
	input[5] = &m_input6;
	input[6] = &m_input7;
	input[7] = &m_input8;
	input[8] = &m_input9;
	input[9] = &m_input10;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKolosDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKolosDlg::OnPaint()
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
HCURSOR CKolosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



float f_average(float tab[], const size_t& n)
{
	float _avg = 0;
	for (size_t i = 0; i < n; i++) {
		_avg += tab[i];
	}

	return _avg / (float)n;
}

float f_standardDeviation(float tab[], const size_t& n)
{
	const float _avg = f_average(tab, n);
	float deviation = 0;

	for (size_t i = 0; i < n; i++)
	{
		deviation += (tab[i] - _avg) * (tab[i] - _avg);
	}
	
	return sqrtf(deviation / n);
}

void CKolosDlg::randomizeInput()
{
	CString s_value;

	for (size_t i = 0; i < 10; i++)
	{
		s_value.Format(_T("%.0f"), (float)(rand() % 100));
		input[i]->SetWindowTextW(s_value);
	}
}

void CKolosDlg::updateOutput()
{
	float values[10];
	CString s_value;

	for (size_t i = 0; i < 10; i++)
	{
		input[i]->GetWindowTextW(s_value);
		values[i] = (bool)input[i]->GetWindowTextLengthW() ? _ttof(s_value) : 0;
	}

	s_value.Format(_T("%.2f"), f_average(values, 10));
	m_output_average.SetWindowTextW(s_value);

	s_value.Format(_T("%.2f"), f_standardDeviation(values, 10));
	m_output_standard_deviation.SetWindowTextW(s_value);
}

void CKolosDlg::onParametersChange()
{
	updateOutput();
}


void CKolosDlg::OnChangeInput1() { onParametersChange(); }

void CKolosDlg::OnChangeInput2() { onParametersChange(); }

void CKolosDlg::OnChangeInput3() { onParametersChange(); }

void CKolosDlg::OnChangeInput4() { onParametersChange(); }

void CKolosDlg::OnChangeInput5() { onParametersChange(); }

void CKolosDlg::OnChangeInput6() { onParametersChange(); }

void CKolosDlg::OnChangeInput7() { onParametersChange(); }

void CKolosDlg::OnChangeInput8() { onParametersChange(); }

void CKolosDlg::OnChangeInput9() { onParametersChange(); }

void CKolosDlg::OnChangeInput10() { onParametersChange(); }

void CKolosDlg::OnBnClickedButton1() { randomizeInput(); }
