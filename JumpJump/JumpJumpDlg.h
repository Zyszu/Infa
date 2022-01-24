
// JumpJumpDlg.h : header file
//

#pragma once


// CJumpJumpDlg dialog
class CJumpJumpDlg : public CDialogEx
{
// Construction
public:
	CJumpJumpDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JUMPJUMP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
public:
	afx_msg CDC* dc;
protected:
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	struct Point2
	{
		int x = 0;
		int y = 0;
	};


	static int				game_filed_width;
	static int				game_filed_height;
	static int				game_filed_offset;

	static Point2			getRandPoint();

	static Point2			game_player_pos;
	static Point2			game_point_pos;

	static int				game_points_total;

	static Point2			game_fields_total;

public:
	enum class FrogMove {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	static FrogMove			game_move_next_direction;
public:
	afx_msg void OnBnClickedMoveUp();
	afx_msg void OnBnClickedMoveLeft();
	afx_msg void OnBnClickedMoveRight();
	afx_msg void OnBnClickedMoveDown();

public:
	afx_msg void drawPlain();
	afx_msg void drawPlayer();
	afx_msg void drawPoint();
	afx_msg bool collision_wall();
	afx_msg bool collision_point();
	afx_msg void move_player(FrogMove direction);
};
