
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

	dc = GetDC();

	_pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));

	magicColors[0] = RGB(105, 89, 88);
	magicColors[1] = RGB(182, 200, 169);
	magicColors[2] = RGB(200, 234, 211);
	magicColors[3] = RGB(207, 255, 229);
	magicColors[4] = RGB(206, 218, 218);
	magicColors[5] = RGB(251, 54, 64);
	magicColors[6] = RGB(36, 123, 160);
	magicColors[7] = RGB(153, 154, 198);
	magicColors[8] = RGB(0, 56, 68);
	magicColors[9] = RGB(0, 108, 103);

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

float f_max(float tab[], const size_t& n) {
	float _max = tab[0];
	for (size_t i = 0; i < n; i++)
		if (tab[i] > _max) _max = tab[i];
	return _max;
}

void CKolosDlg::randomizeInput()
{
	CString s_value;

	for (size_t i = 0; i < 10; i++)
	{
		s_value.Format(_T("%.0f"), (float)(rand() % 101));
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

void CKolosDlg::updateGraph()
{
	float values[10];
	CString s_value;

	for (size_t i = 0; i < 10; i++)
	{
		input[i]->GetWindowTextW(s_value);
		values[i] = (bool)input[i]->GetWindowTextLengthW() && _ttof(s_value) >= 0 ? _ttof(s_value) : 0;
	}

	const int _x = 750;
	const int _y = 20;
	const int _length = 700;
	const int _height = 400;

	#define __WHITE RGB(255, 255, 255)
	#define __BLACK RGB(0, 0, 0)

	const COLORREF _color = __WHITE; //RGB(255, 255, 255);

	dc->FillSolidRect(_x, _y, _length, _height, _color);


	// length / 10 = 70px
	// padding 5px -> 60px

	const int padding = 5;
	const int happyHalloween = 50;

	for (size_t i = 0; i < 10; i++) {
		//int thisColorNum = happyHalloween + (i * 5);
		//COLORREF thisColor = RGB(thisColorNum, thisColorNum, thisColorNum);

		int height = (_height/f_max(values, 10)) * values[i];
		COLORREF thisColor = magicColors[i];
		dc->FillSolidRect(_x + (60 * i) + (5 * (i+1)), _y + _height, 60, -height, thisColor);
	}

	// I added and removed 5 from x because it looks better
	dc->SelectObject(&_pen);
	dc->MoveTo(_x + 5, _y + _height - (4*f_average(values, 10)));
	dc->LineTo(_x + _length - 5, _y + _height - (4 * f_average(values, 10)));

}

void CKolosDlg::onParametersChange()
{
	updateOutput();
	updateGraph();
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
