
// KalkulatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Kalkulator.h"
#include "KalkulatorDlg.h"
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


// CKalkulatorDlg dialog



CKalkulatorDlg::CKalkulatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KALKULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKalkulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT1, m_input1);
	DDX_Control(pDX, IDC_INPUT2, m_input2);
	DDX_Control(pDX, IDC_OUTPUT, m_output);
}

BEGIN_MESSAGE_MAP(CKalkulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CKalkulatorDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_ADDITION, &CKalkulatorDlg::OnClickedAddition)
	ON_BN_CLICKED(IDC_SUBTRACTION, &CKalkulatorDlg::OnClickedSubtraction)
	ON_BN_CLICKED(IDC_MULTIPLICATION, &CKalkulatorDlg::OnClickedMultiplication)
	ON_BN_CLICKED(IDC_DIVISION, &CKalkulatorDlg::OnClickedDivision)
END_MESSAGE_MAP()


// CKalkulatorDlg message handlers

BOOL CKalkulatorDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKalkulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKalkulatorDlg::OnPaint()
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
HCURSOR CKalkulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKalkulatorDlg::OnEnChangeEdit1()
{
	// TODO:  Je¿eli to jest kontrolka RICHEDIT, to kontrolka nie bêdzie
	// wyœlij to powiadomienie, chyba ¿e przes³onisz element CDialogEx::OnInitDialog()
	// funkcja i wywo³anie CRichEditCtrl().SetEventMask()
	// z flag¹ ENM_CHANGE zsumowan¹ logicznie z mask¹.

	// TODO:  Dodaj tutaj swój kod procedury obs³ugi powiadamiania kontrolki
}

void CKalkulatorDlg::make_operation(MathOperations operation) {

	CString str_num1, str_num2, str_result;
	float f_num1, f_num2, _result;
	bool _error = false;

	m_input1.GetWindowTextW(str_num1);
	m_input2.GetWindowTextW(str_num2);


	f_num1 = _ttof(str_num1);
	f_num2 = _ttof(str_num2);

	switch (operation)
	{
	case ADDITION:
		_result = f_num1 + f_num2;
		break;
	case SUBTRACTION:
		_result = f_num1 - f_num2;
		break;
	case MULTIPLICATION:
		_result = f_num1 * f_num2;
		break;
	case DIVISON:
		if (f_num2 == 0) {
			_error = true;
			break;
		}
		_result = f_num1 / f_num2;
		break;
	}

	if(_error)
		m_output.SetWindowTextW((CString)"ERROR");
	else{
		str_result.Format(_T("%f"), _result);
		m_output.SetWindowTextW(str_result);
	}
}

void CKalkulatorDlg::OnClickedAddition()
{
	make_operation(ADDITION);
}


void CKalkulatorDlg::OnClickedSubtraction()
{
	make_operation(SUBTRACTION);
}


void CKalkulatorDlg::OnClickedMultiplication()
{
	make_operation(MULTIPLICATION);
}


void CKalkulatorDlg::OnClickedDivision()
{
	make_operation(DIVISON);
}
