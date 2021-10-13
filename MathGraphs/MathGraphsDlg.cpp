
// MathGraphsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MathGraphs.h"
#include "MathGraphsDlg.h"
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


// CMathGraphsDlg dialog



CMathGraphsDlg::CMathGraphsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MATHGRAPHS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMathGraphsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MATH_FUNCTION_FORMULA, m_math_function_formula);
	DDX_Control(pDX, IDC_VALUE_A, m_function_parameter_a);
	DDX_Control(pDX, IDC_VALUE_B, m_function_parameter_b);
	DDX_Control(pDX, IDC_VALUE_C, m_function_parameter_c);
}

BEGIN_MESSAGE_MAP(CMathGraphsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_MATH_FUNCTION_FORMULA, &CMathGraphsDlg::OnStnClickedMathFunctionFormula)
	ON_BN_CLICKED(IDC_DRAW, &CMathGraphsDlg::OnClickedDraw)
END_MESSAGE_MAP()


// CMathGraphsDlg message handlers

BOOL CMathGraphsDlg::OnInitDialog()
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

	dc = GetDC();
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	graph_pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMathGraphsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMathGraphsDlg::OnPaint()
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
HCURSOR CMathGraphsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMathGraphsDlg::OnStnClickedMathFunctionFormula()
{
	// TODO: Dodaj tutaj swój kod procedury obs³ugi powiadamiania kontrolki
}

int quadraticFunction(float p_a, float p_b, float p_c, int x) {
	return (int)((p_a * x * x) + (p_b * x) + p_c);
}

int mod(int n) {
	return n < 0 ? -n : n; 
}

void CMathGraphsDlg::OnClickedDraw()
{
	CString p_a, p_b, p_c, _functionFormula;
	float f_a, f_b, f_c;

	m_function_parameter_a.GetWindowTextW(p_a);
	m_function_parameter_b.GetWindowTextW(p_b);
	m_function_parameter_c.GetWindowTextW(p_c);

	f_a = _ttof(p_a);
	f_b = _ttof(p_b);
	f_c = _ttof(p_c);

	_functionFormula =
		(CString)"y = " +
		p_a + (CString)"x^2 + " +
		p_b + (CString)"x + " + p_c;

	m_math_function_formula.SetWindowTextW(_functionFormula);

	int g_posx = 25;
	int g_posy = 200;

	int g_width = 800;
	int g_height = 350;

	COLORREF rectangeColor = dc->GetBkColor();
	COLORREF insideRect = RGB(20, 190, 0);

	dc->FillSolidRect(g_posx, g_posy, g_width, g_height, rectangeColor);
	//dc->FillSolidRect(g_posx + 25, g_posy + 25, 200, 200, insideRect);

	// drawind x axies
	dc->SelectObject(&pen);
	dc->MoveTo(g_posx, g_posy + (g_height / 2));
	dc->LineTo(g_posx + g_width, g_posy + (g_height / 2));

	// drawing y axies
	dc->MoveTo(g_posx + (g_width / 2), g_posy);
	dc->LineTo(g_posx + (g_width / 2), g_posy + g_height);

	CPoint graph_pen_position;

	dc->SelectObject(&graph_pen);
	for (int x = g_width/-2; x < g_width/2; x++) {
		int y = quadraticFunction(f_a, f_b, f_c, x);

		int x_position = g_posx + (g_width / 2) + x;
		int y_position = g_posy + (g_height / 2) - y;
		graph_pen_position.SetPoint(x_position, y_position);

		if (!(mod(y) > g_height / 2)) {
			dc->LineTo(graph_pen_position);
			dc->MoveTo(graph_pen_position);
		}
	}

}
