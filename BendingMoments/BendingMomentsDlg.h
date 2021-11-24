
// BendingMomentsDlg.h : header file
//

#pragma once

#include "PrayToTheLordBecauseHeGaveUsShawtiesAndCoffe.h"
#include "CSECTION_ADVANCED.h"


// CBendingMomentsDlg dialog
class CBendingMomentsDlg : public CDialogEx
{
// Construction
	CBendingMomentsDlg& returnThisClass() {
		return *this;
	}

public:
	CBendingMomentsDlg(CWnd* pParent = nullptr);	// standard constructor
	CSECTION_ADVANCED sectionAdvanced();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BENDINGMOMENTS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_select_material;
	CComboBox m_select_section;
//	CEdit m_value_beam_deflection_at_chosen_point;
//	CEdit m_value_max_bending_moment;
	CStatic m_value_apply_force_at;
	CSliderCtrl m_slider_applay_force_at;
	CSliderCtrl m_slider_deflection_at_point;
	CStatic m_value_deflection_at_point;
	CEdit m_beam_length;
	CEdit m_force_value;
//	CButton m_check_material_advanced;
	CButton m_check_section_advanced;
	afx_msg void OnNMCustomdrawForceApplicationPoint(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawDeflectionAtPoint(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnBnClickedCheckMaterialAdvanced2();
	afx_msg void OnBnClickedCheckSectionAdvanced();
	afx_msg void onParametersChange();
//	CButton m_check_custom_material;
	afx_msg void OnEnChangeBeamLength();
	afx_msg void OnEnChangeForceValue();
//	CEdit m_bending_index;
	CEdit m_answear_deflection;
	CEdit m_answear_max_bending_moment;
	CEdit m_answear_bending_index;
	afx_msg void OnCbnSelchangeMaterialSelect();
	afx_msg void OnCbnSelchangeSectionSelect();
	afx_msg void clearAnswears();
	afx_msg long double getSliderPercent(const CSliderCtrl& slider);
};
