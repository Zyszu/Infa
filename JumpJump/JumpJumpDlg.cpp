
// JumpJumpDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "JumpJump.h"
#include "JumpJumpDlg.h"
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


// CJumpJumpDlg dialog



CJumpJumpDlg::CJumpJumpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JUMPJUMP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJumpJumpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJumpJumpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MOVE_UP, &CJumpJumpDlg::OnBnClickedMoveUp)
	ON_BN_CLICKED(IDC_MOVE_LEFT, &CJumpJumpDlg::OnBnClickedMoveLeft)
	ON_BN_CLICKED(IDC_MOVE_RIGHT, &CJumpJumpDlg::OnBnClickedMoveRight)
	ON_BN_CLICKED(IDC_MOVE_DOWN, &CJumpJumpDlg::OnBnClickedMoveDown)
END_MESSAGE_MAP()



	// Static variables declarations
	int CJumpJumpDlg::game_filed_width = 600;
	int CJumpJumpDlg::game_filed_height = 600;
	int CJumpJumpDlg::game_filed_offset = 50;

	CJumpJumpDlg::Point2 CJumpJumpDlg::game_player_pos = CJumpJumpDlg::getRandPoint();
	CJumpJumpDlg::Point2 CJumpJumpDlg::game_point_pos = CJumpJumpDlg::getRandPoint();

	int CJumpJumpDlg::game_points_total = 0;

	CJumpJumpDlg::Point2 CJumpJumpDlg::game_fields_total = { 15, 15 };

	CJumpJumpDlg::FrogMove CJumpJumpDlg::game_move_next_direction;

// CJumpJumpDlg message handlers

BOOL CJumpJumpDlg::OnInitDialog()
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
	srand(time(0));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJumpJumpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJumpJumpDlg::OnPaint()
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
HCURSOR CJumpJumpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





CJumpJumpDlg::Point2 CJumpJumpDlg::getRandPoint() {
	Point2 pt;
	pt.x = rand() % game_fields_total.x;
	pt.y = rand() % game_fields_total.y;
	return pt;
}

void CJumpJumpDlg::drawPlain()
{
	dc->FillSolidRect(50,50, 600, 600, RGB(255, 255, 255));

}

void CJumpJumpDlg::drawPlayer()
{
	int player_width = game_filed_width / game_fields_total.x;
	int player_height = game_filed_height / game_fields_total.y;
	COLORREF player_color = RGB(0, 255, 0);

	int draw_player_at_x = game_filed_offset + (game_player_pos.x - 1) * player_width;
	int draw_player_at_y = game_filed_offset + game_player_pos.y * player_height;

	dc->FillSolidRect(draw_player_at_x, draw_player_at_y, player_width, -player_height, player_color);
}

void CJumpJumpDlg::drawPoint()
{
	int point_width = game_filed_width / game_fields_total.x;
	int point_height = game_filed_height / game_fields_total.y;
	COLORREF point_color = RGB(50, 0, 0);

	int draw_point_at_x = game_filed_offset + (game_point_pos.x - 1) * point_width;
	int draw_point_at_y = game_filed_offset + game_point_pos.y * point_height;

	dc->FillSolidRect(draw_point_at_x, draw_point_at_y, point_width, -point_height, point_color);
}

bool CJumpJumpDlg::collision_wall()
{
	int move_many = game_points_total / 10 + 1;

	switch (game_move_next_direction)
	{

	}

	return false;
}

bool CJumpJumpDlg::collision_point()
{
	#define and &&
	if (game_player_pos.x == game_point_pos.x and game_player_pos.y == game_point_pos.y)
	{
		game_points_total++;
		return true;
	}
	return false;
}

void CJumpJumpDlg::OnBnClickedMoveUp()
{
	drawPlayer();
}


void CJumpJumpDlg::OnBnClickedMoveLeft()
{
	drawPoint();
}


void CJumpJumpDlg::OnBnClickedMoveRight()
{
	// TODO: Add your control notification handler code here
}


void CJumpJumpDlg::OnBnClickedMoveDown()
{
	drawPlain();
}
