
// BendingMomentsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BendingMoments.h"
#include "BendingMomentsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define or ||
#define and &&

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


// CBendingMomentsDlg dialog



CBendingMomentsDlg::CBendingMomentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BENDINGMOMENTS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBendingMomentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MATERIAL_SELECT, m_select_material);
	DDX_Control(pDX, IDC_SECTION_SELECT, m_select_section);
	//  DDX_Control(pDX, IDC_BEAM_DEFLECTION_AT_CHOSEN_POINT, m_value_beam_deflection_at_chosen_point);
	//  DDX_Control(pDX, IDC_MAX_BENDING_MOMENT, m_value_max_bending_moment);
	DDX_Control(pDX, IDC_FORCE_APPLICATION_POINT_VALUE, m_value_apply_force_at);
	DDX_Control(pDX, IDC_FORCE_APPLICATION_POINT, m_slider_applay_force_at);
	DDX_Control(pDX, IDC_DEFLECTION_AT_POINT, m_slider_deflection_at_point);
	DDX_Control(pDX, IDC_DEFLECTION_AT_POINT_VALUE, m_value_deflection_at_point);
	DDX_Control(pDX, IDC_BEAM_LENGTH, m_beam_length);
	DDX_Control(pDX, IDC_FORCE_VALUE, m_force_value);
	//  DDX_Control(pDX, IDC_CHECK_MATERIAL_ADVANCED2, m_check_material_advanced);
	DDX_Control(pDX, IDC_CHECK_SECTION_ADVANCED, m_check_section_advanced);
	//  DDX_Control(pDX, IDC_CHECK_MATERIAL_ADVANCED2, m_check_custom_material);
	//  DDX_Control(pDX, IDC_BENDING_INDEX, m_bending_index);
	DDX_Control(pDX, IDC_BEAM_DEFLECTION_AT_CHOSEN_POINT, m_answear_deflection);
	DDX_Control(pDX, IDC_MAX_BENDING_MOMENT, m_answear_max_bending_moment);
	DDX_Control(pDX, IDC_BENDING_INDEX, m_answear_bending_index);
}

BEGIN_MESSAGE_MAP(CBendingMomentsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_FORCE_APPLICATION_POINT, &CBendingMomentsDlg::OnNMCustomdrawForceApplicationPoint)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_DEFLECTION_AT_POINT, &CBendingMomentsDlg::OnNMCustomdrawDeflectionAtPoint)
//	ON_BN_CLICKED(IDC_CHECK_MATERIAL_ADVANCED2, &CBendingMomentsDlg::OnBnClickedCheckMaterialAdvanced2)
	ON_BN_CLICKED(IDC_CHECK_SECTION_ADVANCED, &CBendingMomentsDlg::OnBnClickedCheckSectionAdvanced)
	ON_EN_CHANGE(IDC_BEAM_LENGTH, &CBendingMomentsDlg::OnEnChangeBeamLength)
	ON_EN_CHANGE(IDC_FORCE_VALUE, &CBendingMomentsDlg::OnEnChangeForceValue)
	ON_CBN_SELCHANGE(IDC_MATERIAL_SELECT, &CBendingMomentsDlg::OnCbnSelchangeMaterialSelect)
	ON_CBN_SELCHANGE(IDC_SECTION_SELECT, &CBendingMomentsDlg::OnCbnSelchangeSectionSelect)
END_MESSAGE_MAP()


// CBendingMomentsDlg message handlers

BOOL CBendingMomentsDlg::OnInitDialog()
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

	sectionAdvanced.Create(IDD_CSECTION_ADVANCED);

	for (int i = 0; i < (int)IsotropicMaterials::END_OF_MATERIALS; i++)
		m_select_material.AddString(getMaterialName((IsotropicMaterials)i));

	for (int i = 0; i < (int)SectionType::END_OF_SECTIONS; i++)
		m_select_section.AddString(getSectionName((SectionType)i));

	m_slider_applay_force_at.SetRangeMin(0);
	m_slider_applay_force_at.SetRangeMax(1000);
	m_slider_applay_force_at.SetPos(1000/2);
	m_slider_applay_force_at.EnableWindow(true);

	m_slider_deflection_at_point.SetRangeMin(0);
	m_slider_deflection_at_point.SetRangeMax(1000);
	m_slider_deflection_at_point.SetPos(1000 / 2);
	m_slider_deflection_at_point.EnableWindow(true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBendingMomentsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBendingMomentsDlg::OnPaint()
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
HCURSOR CBendingMomentsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBendingMomentsDlg::clearAnswears() {
	m_answear_bending_index.SetWindowTextW(_T(""));
	m_answear_deflection.SetWindowTextW(_T(""));
	m_answear_max_bending_moment.SetWindowTextW(_T(""));
}

long double CBendingMomentsDlg::getSliderPercent(const CSliderCtrl& slider) {
	return (long double)slider.GetPos() / 1000.0L;
}

void CBendingMomentsDlg::onParametersChange()
{

	if (m_check_section_advanced.GetCheck())
	{
		SectionType s_type = getSectionType((SectionType)m_select_section.GetCurSel());
		sectionAdvanced.pickImg(s_type);
	}

	// when done like that interesting thing happens
	/*_beam = Beam(
		BeamSection(
			getSectionType((SectionType)m_select_section.GetCurSel()),
			getDefaultValues(getSectionType((SectionType)m_select_section.GetCurSel()))
		),
		IsotropicMaterial(
			getMaterial((IsotropicMaterials)m_select_material.GetCurSel())
		)
	);*/

	CString length, force;
	long double d_length, d_force;

	m_beam_length.GetWindowTextW(length);
	m_force_value.GetWindowTextW(force);

	d_length = length.GetLength() == 0 ? 0 : _tcstold(length, NULL);
	d_force = force.GetLength() == 0 ? 0 : _tcstold(force, NULL);


	SectionType s_type = (SectionType)m_select_section.GetCurSel();
	size_t args = getNumberOfArgs(s_type);
	long double* values = new long double[args];

	for (size_t i = 0; i < args; i++) {
		if(m_check_section_advanced.GetCheck())
			values[i] = sectionAdvanced.getValues()[i];
		else values[i] = getDefaultValues(s_type)[i];
	}

	Beam _beam = Beam(
		BeamSection(
			s_type,
			values
		),
		IsotropicMaterial(
			getMaterial((IsotropicMaterials)m_select_material.GetCurSel())
		),
		d_length
	);

	delete[] values;

	if (!_beam.isValid()) {
		clearAnswears();
		return;
	}

	CString s_answear;

	s_answear.Format(_T("%.4Le"), _beam.section.getBendingIndex());
	m_answear_bending_index.SetWindowTextW(s_answear);

	s_answear.Format(
		_T("%.4Le"), 
		_beam.getMaxBendingMoment(
			getSliderPercent(m_slider_applay_force_at) * _beam.length,
			d_force
		)
	);
	m_answear_max_bending_moment.SetWindowTextW(s_answear);

	s_answear.Format(
	_T("%.4Le"),
		_beam.getDefleftionAt(
			getSliderPercent(m_slider_applay_force_at) * _beam.length,
			getSliderPercent(m_slider_deflection_at_point) * _beam.length,
			d_force
		)
	);
	m_answear_deflection.SetWindowTextW(s_answear);
}


//void CBendingMomentsDlg::OnBnClickedCheckMaterialAdvanced2()
//{
//	// nothing yet :D
//}

void CBendingMomentsDlg::OnBnClickedCheckSectionAdvanced()
{
	if (m_check_section_advanced.GetCheck()) {
		sectionAdvanced.ShowWindow(SW_SHOWNORMAL);
		SectionType s_type = getSectionType((SectionType)m_select_section.GetCurSel());
		sectionAdvanced.pickImg(s_type);
	}
	else sectionAdvanced.ShowWindow(SW_HIDE);
}

void CBendingMomentsDlg::OnNMCustomdrawForceApplicationPoint(NMHDR* pNMHDR, LRESULT* pResult)
{ 
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; 
	CString _ret;
	_ret.Format(_T("%.1f%%"), (float)m_slider_applay_force_at.GetPos() / 10.0);

	m_value_apply_force_at.SetWindowTextW(_ret);
	onParametersChange();
}

void CBendingMomentsDlg::OnNMCustomdrawDeflectionAtPoint(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0;
	CString _ret;
	_ret.Format(_T("%.1f%%"), (float)m_slider_deflection_at_point.GetPos()/10.0);

	m_value_deflection_at_point.SetWindowTextW(_ret);
	onParametersChange();
}

void CBendingMomentsDlg::OnEnChangeBeamLength() { onParametersChange(); }

void CBendingMomentsDlg::OnEnChangeForceValue() { onParametersChange(); }

void CBendingMomentsDlg::OnCbnSelchangeMaterialSelect() { onParametersChange(); }

void CBendingMomentsDlg::OnCbnSelchangeSectionSelect() { onParametersChange(); }