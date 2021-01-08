
// project__Dlg.h: 헤더 파일
//

#pragma once
#include "ListCtrlEx.h"

// CprojectDlg 대화 상자
class CprojectDlg : public CDialogEx
{
// 생성입니다.
public:
	CprojectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT___DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTcnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLbnSelchangeList4();
	CTabCtrl m_tab;
	CButton m_btnStart;
	CButton m_btn_search;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEditFilename();
//	CEdit m_strFileLocation;
//	CEdit m_strFileName;
	BOOL m_bSub;
	CString m_strFileLocation;
	CString m_strFileName;
	afx_msg void OnStnClickedStaticStatus2();
	CStatic m_stcStatus1;
//	CStatic m_stcStatus2;
	afx_msg void OnLvnItemchangedListResult(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrlEx m_lstResult;
	CImageList m_img;
	void SearFileNotSub();
	BOOL m_bStop;
	CString m_strToken;
	void SearFile(CString strStartFolder);
	afx_msg void OnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	CStatic m_stcStatus;
};
