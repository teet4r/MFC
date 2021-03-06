﻿
// BingoCntDlg.h: 헤더 파일
//

#pragma once


// CBingoCntDlg 대화 상자
class CBingoCntDlg : public CDialogEx
{
// 생성입니다.
public:
	CBingoCntDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CSocCom m_socCom; // 통신용 소켓

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINGOCNT_DIALOG };
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
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	afx_msg void ONButtonSend();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonConnect();
//	CString m_strStatus;
	CString m_strMe;
	CString m_strStatus;
	CString m_strConnect;
	CListBox m_list;
	CString m_strSend;
	void SendGame(int iType, CString strTmp);
	void DrawRec(); // 250 * 250 사각형 그리
	void DrawLine(); // 선 그리기
	void DrawNum(int iRow, int iCol, int iNum); // 숫자 그리기
	void DrawCheck(int iRow, int iCol); // 체크 된 곳 표시

	int m_iGame[5][5];
	BOOL m_bGame[5][5];

	int m_iOrder;
	BOOL m_bStart; // 1~25를 다 채우면 TRUE
	BOOL m_bStartSvr; // 서버가 준비 끝나면 TRUE
	BOOL m_bConnect; // 다른 쪽과 접속했을 때 TRUE
	BOOL m_bMe; // 내가 선택할 차례이면 TRUE
	BOOL m_bCntEnd, m_bSvrEnd; // 클라이언트/서버가 끝났는지(빙고) 검사
	void InitGame();
	void OrderNum(int iRow, int iCol);
	void PosToIndex(CPoint pnt, int& iRow, int& iCol);
	void NumToIndex(int iNum, int& iRow, int& iCol);
	BOOL IsGameEnd();
	void SetGameEnd();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
