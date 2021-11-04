
// TriangleDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Triangle.h"
#include "TriangleDlg.h"
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


// CTriangleDlg dialog



CTriangleDlg::CTriangleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRIANGLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTriangleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NODE_A_ACTIVE, m_NODE_A_ACTIVE);
	DDX_Control(pDX, IDC_NODE_B_ACTIVE, m_NODE_B_ACTIVE);
	DDX_Control(pDX, IDC_NODE_C_ACTIVE, m_NODE_C_ACTIVE);
	DDX_Control(pDX, IDC_NODE_A_SLIDEBAR_X, m_NODE_A_SLIDER_X);
	DDX_Control(pDX, IDC_NODE_B_SLIDEBAR_X, m_NODE_B_SLIDER_X);
	DDX_Control(pDX, IDC_NODE_C_SLIDEBAR_X, m_NODE_C_SLIDER_X);
	DDX_Control(pDX, IDC_NODE_A_SLIDEBAR_Y, m_NODE_A_SLIDER_Y);
	DDX_Control(pDX, IDC_NODE_B_SLIDEBAR_Y, m_NODE_B_SLIDER_Y);
	DDX_Control(pDX, IDC_NODE_C_SLIDEBAR_Y, m_NODE_C_SLIDER_Y);
	DDX_Control(pDX, IDC_DRAWING_FRAME, m_DRAWING_FRAME);
	DDX_Control(pDX, IDC_TRIANGLE_PROPERTIES_ACTIVE, m_TRIANGLE_PROPERTIES_ACTIVE);
}

BEGIN_MESSAGE_MAP(CTriangleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NODE_A_ACTIVE, &CTriangleDlg::OnBnClickedNodeAActive)
	ON_BN_CLICKED(IDC_NODE_B_ACTIVE, &CTriangleDlg::OnBnClickedNodeBActive)
	ON_BN_CLICKED(IDC_NODE_C_ACTIVE, &CTriangleDlg::OnBnClickedNodeCActive)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_A_SLIDEBAR_X, &CTriangleDlg::OnNMCustomdrawNodeASlidebarX)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_A_SLIDEBAR_Y, &CTriangleDlg::OnNMCustomdrawNodeASlidebarY)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_B_SLIDEBAR_X, &CTriangleDlg::OnNMCustomdrawNodeBSlidebarX)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_B_SLIDEBAR_Y, &CTriangleDlg::OnNMCustomdrawNodeBSlidebarY)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_C_SLIDEBAR_X, &CTriangleDlg::OnNMCustomdrawNodeCSlidebarX)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_NODE_C_SLIDEBAR_Y, &CTriangleDlg::OnNMCustomdrawNodeCSlidebarY)
	ON_BN_CLICKED(IDC_TRIANGLE_PROPERTIES_ACTIVE, &CTriangleDlg::OnBnClickedTrianglePropertiesActive)
END_MESSAGE_MAP()


// CTriangleDlg message handlers

BOOL CTriangleDlg::OnInitDialog()
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

	triangle_prop.Create(IDD_TRIANGLE_PROPERTIES);

	// seting max and min values for sliders

	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_DRAWING_FRAME);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect); //optional step

	df_x = rect.left;
	df_y = rect.top;
	df_width = rect.Width();
	df_height = rect.Height();
	df_margin = 5; // margin between group field and drawing in pixels

	// -

	dc = GetDC(); // some shit :D

	// Buttons [x]

	m_NODE_A_ACTIVE.SetCheck(true);
	m_NODE_B_ACTIVE.SetCheck(true);
	m_NODE_C_ACTIVE.SetCheck(true);


	// Sliders ------=---

	 // IDC_DIALOG
	const int SLIDER_X_MIN = df_x + df_margin;
	const int SLIDER_X_MAX = df_x + df_width - df_margin;
	const int SLIDER_Y_MIN = df_y + df_margin;
	const int SLIDER_Y_MAX = df_y + df_height - df_margin;


	m_NODE_A_SLIDER_X.SetRangeMin(SLIDER_X_MIN);
	m_NODE_A_SLIDER_X.SetRangeMax(SLIDER_X_MAX);
	m_NODE_A_SLIDER_X.SetPos(SLIDER_X_MAX/2);

	m_NODE_A_SLIDER_Y.SetRangeMin(SLIDER_Y_MIN);
	m_NODE_A_SLIDER_Y.SetRangeMax(SLIDER_Y_MAX);
	m_NODE_A_SLIDER_Y.SetPos(SLIDER_Y_MAX/2);

	m_NODE_B_SLIDER_X.SetRangeMin(SLIDER_X_MIN);
	m_NODE_B_SLIDER_X.SetRangeMax(SLIDER_X_MAX);
	m_NODE_B_SLIDER_X.SetPos(SLIDER_X_MAX/2);

	m_NODE_B_SLIDER_Y.SetRangeMin(SLIDER_Y_MIN);
	m_NODE_B_SLIDER_Y.SetRangeMax(SLIDER_Y_MAX);
	m_NODE_B_SLIDER_Y.SetPos(SLIDER_Y_MAX/2);

	m_NODE_C_SLIDER_X.SetRangeMin(SLIDER_X_MIN);
	m_NODE_C_SLIDER_X.SetRangeMax(SLIDER_X_MAX);
	m_NODE_C_SLIDER_X.SetPos(SLIDER_X_MAX/2);

	m_NODE_C_SLIDER_Y.SetRangeMin(SLIDER_Y_MIN);
	m_NODE_C_SLIDER_Y.SetRangeMax(SLIDER_Y_MAX);
	m_NODE_C_SLIDER_Y.SetPos(SLIDER_Y_MAX/2);

	_penRed.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	_penGreen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	_penBlue.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	
	// IDC_TRIANGLE_PROPERITES

	{
		#define tp triangle_prop
		tp.m_IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER.SetPos(0);
		tp.m_IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER.SetRangeMin(0);
		tp.m_IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER.SetRangeMax(15);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTriangleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTriangleDlg::OnPaint()
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
HCURSOR CTriangleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// my functions(😴)

void CTriangleDlg::drawTriangle() {
	// There is a bug while drawing triangle
	// when points are on the edges of drawing field
	// they are leaving path of lines connecting them
	// it's caused because of the fact that drawing
	// field has specified width and height and
	// in fact points aren't overflowing drawing field
	// but lines are 2px wide and points are 4px wide
	// so actually they are kind of overflowing drawing field
	// Although I'm not going to do anything about it :)

	// IDC_DRAWING_FRAME coordinates
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_DRAWING_FRAME);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect); //optional step

	// basic coordinates
	const int g_x = df_x + df_margin;
	const int g_y = df_y + df_margin;
	const int g_width = df_width - 2 * df_margin;
	const int g_height = df_height - 2 * df_margin;
	const COLORREF g_color = RGB(255, 255, 255);
	const int x_o = g_width / 2;
	const int y_o = g_height / 2;

	// geting active fields
	const bool nodeA_active = m_NODE_A_ACTIVE.GetCheck();
	const bool nodeB_active = m_NODE_B_ACTIVE.GetCheck();
	const bool nodeC_active = m_NODE_C_ACTIVE.GetCheck();

	// coordinates form sliders
	const int nodeA_x = nodeA_active ? m_NODE_A_SLIDER_X.GetPos() : x_o;
	const int nodeA_y = nodeA_active ? m_NODE_A_SLIDER_Y.GetPos() : y_o;
	const int nodeB_x = nodeB_active ? m_NODE_B_SLIDER_X.GetPos() : x_o;
	const int nodeB_y = nodeB_active ? m_NODE_B_SLIDER_Y.GetPos() : y_o;
	const int nodeC_x = nodeC_active ? m_NODE_C_SLIDER_X.GetPos() : x_o;
	const int nodeC_y = nodeC_active ? m_NODE_C_SLIDER_Y.GetPos() : y_o;

	#define _BLACK RGB(0, 0, 0)

	// Drawing background
	dc->FillSolidRect(g_x, g_y, g_width, g_height, g_color);

	// drawing points and connecting them with lines
	dc->SelectObject(&_penRed);
	dc->MoveTo(nodeA_x, nodeA_y);
	dc->LineTo(nodeB_x, nodeB_y);
	dc->FillSolidRect(nodeA_x, nodeA_y, 4, 4, _BLACK);

	dc->SelectObject(&_penGreen);
	dc->MoveTo(nodeB_x, nodeB_y);
	dc->LineTo(nodeC_x, nodeC_y);
	dc->FillSolidRect(nodeB_x, nodeB_y, 4, 4, _BLACK);

	dc->SelectObject(&_penBlue);
	dc->MoveTo(nodeC_x, nodeC_y);
	dc->LineTo(nodeA_x, nodeA_y);
	dc->FillSolidRect(nodeC_x, nodeC_y, 4, 4, _BLACK);

}

float line_length(const int posAx, const int posAy, const int posBx, const int posBy) {
	return sqrt( ((posAx - posBx) * (posAx - posBx)) + ((posAy - posBy) * (posAy - posBy)) );
}

TriangleInfo CTriangleDlg::getTriangleInfo() {

	// basic coordinates
	const int g_width = df_width - 2 * df_margin;
	const int g_height = df_height - 2 * df_margin;
	const int x_o = g_width / 2;
	const int y_o = g_height / 2;

	// geting active fields
	const bool nodeA_active = m_NODE_A_ACTIVE.GetCheck();
	const bool nodeB_active = m_NODE_B_ACTIVE.GetCheck();
	const bool nodeC_active = m_NODE_C_ACTIVE.GetCheck();

	// coordinates form sliders
	const int nodeA_x = nodeA_active ? m_NODE_A_SLIDER_X.GetPos() : x_o;
	const int nodeA_y = nodeA_active ? m_NODE_A_SLIDER_Y.GetPos() : y_o;
	const int nodeB_x = nodeB_active ? m_NODE_B_SLIDER_X.GetPos() : x_o;
	const int nodeB_y = nodeB_active ? m_NODE_B_SLIDER_Y.GetPos() : y_o;
	const int nodeC_x = nodeC_active ? m_NODE_C_SLIDER_X.GetPos() : x_o;
	const int nodeC_y = nodeC_active ? m_NODE_C_SLIDER_Y.GetPos() : y_o;

	TriangleInfo _info;
	float a_len = line_length(nodeA_x, nodeA_y, nodeB_x, nodeB_y);
	float b_len = line_length(nodeB_x, nodeB_y, nodeC_x, nodeC_y);
	float c_len = line_length(nodeA_x, nodeA_y, nodeC_x, nodeC_y);
	
	// first I'm checking is it valid triangle
	bool statementA = a_len + b_len > c_len; statementA = !statementA;
	bool statementB = b_len + c_len > a_len; statementB = !statementB;
	bool statementC = a_len + c_len > b_len; statementC = !statementC;

	if (statementA || statementB || statementC) {
		_info.isItTriangle = false; return _info;
	} _info.isItTriangle = true;
	
	_info.circuit = a_len + b_len + c_len;
	const float p_const = _info.circuit / 2;
	// don't even ask ;/
	// _info.field = sqrt(p_const * (p_const - a_len) * (p_const - b_len) * (p_const - c_len));
	_info.field = (float)sqrt((double)p_const * (double)((double)p_const - (double)a_len) * (double)((double)p_const - (double)b_len) * (double)((double)p_const - (double)c_len));
	return _info;
}

void CTriangleDlg::onAnyChange() {
	drawTriangle();
	triangle_prop.updateData(getTriangleInfo());
}

 // Buttons [x]

void CTriangleDlg::OnBnClickedNodeAActive() { onAnyChange(); }

void CTriangleDlg::OnBnClickedNodeBActive() { onAnyChange(); }

void CTriangleDlg::OnBnClickedNodeCActive() { onAnyChange(); }


 // Sliders -----=---
 // all function below has exactly the same content
void CTriangleDlg::OnNMCustomdrawNodeASlidebarX(NMHDR* pNMHDR, LRESULT* pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; onAnyChange(); }

void CTriangleDlg::OnNMCustomdrawNodeASlidebarY(NMHDR* pNMHDR, LRESULT* pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; onAnyChange(); }

void CTriangleDlg::OnNMCustomdrawNodeBSlidebarX(NMHDR* pNMHDR, LRESULT* pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; onAnyChange(); }

void CTriangleDlg::OnNMCustomdrawNodeBSlidebarY(NMHDR* pNMHDR, LRESULT* pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; onAnyChange(); }

void CTriangleDlg::OnNMCustomdrawNodeCSlidebarX(NMHDR* pNMHDR, LRESULT* pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; onAnyChange(); }

void CTriangleDlg::OnNMCustomdrawNodeCSlidebarY(NMHDR* pNMHDR, LRESULT* pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; onAnyChange(); }

void CTriangleDlg::OnBnClickedTrianglePropertiesActive() { if (m_TRIANGLE_PROPERTIES_ACTIVE.GetCheck()) triangle_prop.ShowWindow(SW_SHOWNORMAL); else triangle_prop.ShowWindow(SW_HIDE); }
