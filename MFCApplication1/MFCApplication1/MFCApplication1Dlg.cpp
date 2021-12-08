
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
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


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPEED_CONTROL, m_speed_control);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_SPEED_CONTROL, &CMFCApplication1Dlg::OnEnChangeSpeedControl)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// Static variables declarations
	CDC* CMFCApplication1Dlg::dc;
	CPen CMFCApplication1Dlg::clock_face_pen;
	CPen CMFCApplication1Dlg::clock_hand_pen;
	int CMFCApplication1Dlg::clock_speed;
	CEdit CMFCApplication1Dlg::m_speed_control;
	bool CMFCApplication1Dlg::doTickTick;
	bool CMFCApplication1Dlg::killClock;

// CMFCApplication1Dlg message handlers


BOOL CMFCApplication1Dlg::OnInitDialog()
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

	dc = GetDC();
	clock_face_pen.CreatePen(PS_SOLID, 6, RGB(255, 108, 3));
	clock_hand_pen.CreatePen(PS_SOLID, 6, RGB(64, 24, 193));

	clock_speed		= 1;
	doTickTick		= true;
	killClock		= false;

	HWND* phObjectHandle = new HWND;
	*phObjectHandle = GetSafeHwnd();

	clock = AfxBeginThread(initClock, phObjectHandle);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// lol lol lol lol lol lol lol lol lol lol lol lol lol lol lol lol lol lol lol lol lol

CMFCApplication1Dlg::~CMFCApplication1Dlg()
{
	killClock = true;
}

UINT CMFCApplication1Dlg::initClock(LPVOID  pvParam)
{
	HWND* phObjectHandle = static_cast<HWND*>(pvParam);

	#define __PI 3.14159265L
	const int x = 10;
	const int y = 10;
	const int radius = 200;

	const int mid_point_x = x + radius;
	const int mid_point_y = y + radius;

	struct Point2d
	{
		int x, y;
	};

	Point2d midPoint;
	midPoint.x = mid_point_x;
	midPoint.y = mid_point_y;

	Point2d previous;
	previous.x = mid_point_x + radius * sin(0.0f);
	previous.y = mid_point_y + radius * cos(0.0f);

	bool dalejDalejSmigloGadzeta = false;

	const int multi_prec = 2;
	int i = 0;
	while(!killClock)
	{
		if (!doTickTick)
		{
			Sleep(100);
			continue;
		}
		if (i > 359 || i < -359)
		{
			dalejDalejSmigloGadzeta = !dalejDalejSmigloGadzeta;
			i = 0;
		}
		Point2d current;

		dc->SelectObject(&clock_face_pen);
		dc->FillSolidRect(x, y, 2 * radius, 2 * radius, RGB(255, 255, 255));
		for (size_t j = 0; j < 360 * multi_prec; j++)
		{
			current.x = mid_point_x + (radius * sin((double)(((double)j / (double)multi_prec) * __PI / 180)));
			current.y = mid_point_y + (radius * cos((double)(((double)j / (double)multi_prec) * __PI / 180)));
			dc->MoveTo(previous.x, previous.y);
			dc->LineTo(current.x, current.y);
			previous = current;
		}

		dc->SelectObject(&clock_hand_pen);

		if (dalejDalejSmigloGadzeta)
		{
			current.x = mid_point_x + (radius * sin((double)(((double)-i / (double)multi_prec) * __PI / 180)));
			current.y = mid_point_y + (radius * cos((double)(((double)-i / (double)multi_prec) * __PI / 180)));
		} else {
			current.x = mid_point_x - (radius * sin((double)(((double)-i / (double)multi_prec) * __PI / 180)));
			current.y = mid_point_y - (radius * cos((double)(((double)-i / (double)multi_prec) * __PI / 180)));
		}

		dc->MoveTo(midPoint.x, midPoint.y);
		dc->LineTo(current.x, current.y);
		Sleep(60);

		i+= clock_speed;
	}

	delete phObjectHandle;
	ExitThread(0);
	return 0;
}



void CMFCApplication1Dlg::changeClockSpeed(int new_speed)
{
	#define or ||
	clock_speed = new_speed > 10 or new_speed < -10 ? clock_speed : new_speed;
}

void CMFCApplication1Dlg::OnEnChangeSpeedControl()
{
	CString t_str;
	m_speed_control.GetWindowTextW(t_str);
	changeClockSpeed(_ttoi(t_str));
}

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	if (doTickTick) doTickTick = false;
	else doTickTick = true;
}
