
// project__Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "project__.h"
#include "project__Dlg.h"
#include "afxdialogex.h"
#include "FileFindEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CprojectDlg 대화 상자



CprojectDlg::CprojectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT___DIALOG, pParent)
	, m_bSub(FALSE)
	, m_strFileLocation(_T(""))
	, m_strFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strToken = _T("");
}

void CprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btn_search);
	DDX_Check(pDX, IDC_CHECK_SUB, m_bSub);
	DDX_Text(pDX, IDC_EDIT_FILELOCATION, m_strFileLocation);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	//DDX_Control(pDX, IDC_STATIC_STATUS1, m_stcStatus1);
	DDX_Control(pDX, IDC_LIST_RESULT, m_lstResult);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_stcStatus);
}

BEGIN_MESSAGE_MAP(CprojectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON2, &CprojectDlg::OnBnClickedButton2)
//	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CprojectDlg::OnTcnSelchangeTab2)
//	ON_EN_CHANGE(IDC_EDIT1, &CprojectDlg::OnEnChangeEdit1)
//	ON_LBN_SELCHANGE(IDC_LIST4, &CprojectDlg::OnLbnSelchangeList4)
//ON_EN_CHANGE(IDC_EDIT3, &CprojectDlg::OnEnChangeEdit3)
ON_EN_CHANGE(IDC_EDIT_FILENAME, &CprojectDlg::OnEnChangeEditFilename)
ON_STN_CLICKED(IDC_STATIC_STATUS2, &CprojectDlg::OnStnClickedStaticStatus2)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RESULT, &CprojectDlg::OnLvnItemchangedListResult)
ON_BN_CLICKED(IDC_BUTTON_START, &CprojectDlg::OnClickedButtonStart)
ON_BN_CLICKED(IDC_BUTTON_STOP, &CprojectDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CprojectDlg 메시지 처리기

BOOL CprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_img.Create(IDB_LIST, 16, 2, RGB(255, 255, 255));
	m_lstResult.SetImageList(&m_img, LVSIL_SMALL);

	m_lstResult.InsertColumn(0, _T("이름"), LVCFMT_LEFT, 150);
	m_lstResult.InsertColumn(1, _T("위치"), LVCFMT_LEFT, 150);
	m_lstResult.InsertColumn(2, _T("크기(byte)"), LVCFMT_RIGHT, 80);
	m_lstResult.InsertColumn(3, _T("생성날짜"), LVCFMT_CENTER, 80);
	m_tab.InsertItem(0, _T("이름 및 위치"));

	TCHAR pBuf[256];
	GetCurrentDirectory(256, pBuf);
	m_strFileLocation.Format(_T("%s"), pBuf);
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CprojectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CprojectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprojectDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CprojectDlg::OnTcnSelchangeTab2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CprojectDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CprojectDlg::OnLbnSelchangeList4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CprojectDlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CprojectDlg::OnEnChangeEditFilename()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CprojectDlg::OnStnClickedStaticStatus2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CprojectDlg::OnLvnItemchangedListResult(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CprojectDlg::SearFileNotSub(void)
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(TRUE);

	CString strTmp, strFolder, strName;
	CFileFindEx cfile;
	int i;
	BOOL b;
	MSG msg;

	if (m_strFileLocation.Right(1) == "\\")
		strTmp = m_strFileLocation + _T("*.*");
	else {
		strTmp = m_strFileLocation + _T("\\");
		strTmp += "*.*";
	}
	b = cfile.FindFile(strTmp);

	while (b) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (m_bStop)
			return;

		b = cfile.FindNextFile();

		if (cfile.IsDots())
			continue;

		i = m_lstResult.GetItemCount();

		m_stcStatus.SetWindowText(cfile.GetFilePath());
		strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') + 1);

		strName = cfile.GetFileName();

		strName.MakeUpper();
		if (strName.Find(m_strToken) != -1) {	//m_strToken이 검색어
			if (cfile.IsDirectory()) {
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem(_T("파일폴더"), i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
			else {
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 1);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem(cfile.GetLengthString(), i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
		}
	}
}


void CprojectDlg::SearFile(CString strStartFolder)
{
	// TODO: 여기에 구현 코드 추가.
	UpdateData(TRUE);

	CString strTmp, strFolder, strName;
	CFileFindEx cfile;
	int i;
	BOOL b;
	MSG msg;

	if (strStartFolder.Right(1) == "\\")
		strTmp = strStartFolder + _T("*.*");
	else {
		strTmp = strStartFolder + _T("\\");
		strTmp += "*.*";
	}
	b = cfile.FindFile(strTmp);

	while (b) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (m_bStop)
			return;

		b = cfile.FindNextFile();

		if (cfile.IsDots())
			continue;

		i = m_lstResult.GetItemCount();
		m_stcStatus.SetWindowText(cfile.GetFilePath());
		strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') + 1); // 너랑 어디가 다름?

		strName = cfile.GetFileName();
		strName.MakeUpper();
		if (cfile.IsDirectory()) {
			if (strName.Find(m_strToken) != -1) {
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem(_T("파일폴더"), i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
			SearFile(cfile.GetFilePath());
		}
		else {
			if (strName.Find(m_strToken) != -1) {
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 1);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem(cfile.GetLengthString(), i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
		}
	}
}

// 이게 버튼 눌렀을때 실행
void CprojectDlg::OnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_bStop = FALSE;
	m_lstResult.DeleteAllItems();							// 리스트초기화
	m_strToken = m_strFileName.MakeUpper();					// 대문자 변환
	// 여기에 체크박스 상태
	m_bSub ? SearFile(m_strFileLocation) : SearFileNotSub();
}

// 중단 버튼 눌렀을때
void CprojectDlg::OnBnClickedButtonStop()
{
	UpdateData(TRUE);
	m_bStop = TRUE;
}
