
// MFC_Lab5Dlg.h : header file
//

#pragma once


// CMFCLab5Dlg dialog
class CMFCLab5Dlg : public CDialogEx
{
// Construction
public:
	CMFCLab5Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_LAB5_DIALOG };
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
	float aprX;
	afx_msg void OnBnClickedButton1();
	CString filePath;
	float aprY;
	float aprR;
	CString aprRes;
	CString calcX;
	CString calcY;
	CString calcR;
	afx_msg void OnEnChangeEdit6();
};
