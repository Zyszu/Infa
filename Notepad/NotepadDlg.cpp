
// NotepadDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Notepad.h"
#include "NotepadDlg.h"
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


// CNotepadDlg dialog



CNotepadDlg::CNotepadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTEPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNotepadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTEPAD, m_notepad);
	DDX_Control(pDX, IDC_PATH, m_path);
}

BEGIN_MESSAGE_MAP(CNotepadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ_FILE, &CNotepadDlg::OnBnClickedReadFile)
	ON_BN_CLICKED(IDC_SAVE_FILE, &CNotepadDlg::OnBnClickedSaveFile)
END_MESSAGE_MAP()


// CNotepadDlg message handlers

BOOL CNotepadDlg::OnInitDialog()
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

	isFileNotSaved = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNotepadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNotepadDlg::OnPaint()
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
HCURSOR CNotepadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNotepadDlg::OnOK() {
	// it's here just to prevent cloasing the window after pressing enter button
}

void CNotepadDlg::justReadFile(CFileDialog& fFile)
{
	CString path = fFile.GetPathName();
	m_path.SetWindowTextW(fFile.GetPathName());
	if (path.IsEmpty()) return;

	CStdioFile plik(fFile.GetPathName(), CFile::modeRead | CFile::typeText);
	CString temp;
	plik.ReadString(temp);
	m_notepad.SetWindowTextW(temp);

	isFileNotSaved = true;
}

void CNotepadDlg::justSaveFile(CFileDialog& fFile, CString path)
{
	CString temp;
	m_notepad.GetWindowTextW(temp);

	if (path == (CString)"")
	{
		CStdioFile plik(fFile.GetPathName(), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		plik.WriteString(temp);
	}
	else
	{
		CStdioFile plik(path, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		plik.WriteString(temp);
	}

	isFileNotSaved = false;
}

// if user wants to save changes function returns true
bool CNotepadDlg::unsavedFileWarnign()
{
	if (!isFileNotSaved) return true;
	if (
		AfxMessageBox(
			_T("Do you want to save changes?"),
			MB_OKCANCEL | MB_ICONWARNING
		) == IDYES
	)
		return true;
	else
		return false;
	
}

void CNotepadDlg::OnBnClickedReadFile()
{
	CFileDialog fInput(TRUE);
	if (!unsavedFileWarnign()) justSaveFile(fInput, currFile);
	
	if (!fInput.DoModal()) return;
	currFile = fInput.GetPathName();

	justReadFile(fInput);
}


void CNotepadDlg::OnBnClickedSaveFile()
{
	LPCTSTR pszFilter = _T("Tekstowy (*.txt)|*.txt|");
	CFileDialog fInput(FALSE, _T("txt"), _T("Nowy plik.txt"), OFN_OVERWRITEPROMPT, pszFilter);
	if (!fInput.DoModal()) return;

	justSaveFile(fInput);
}
