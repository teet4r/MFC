#pragma once

// CSocServer 명령 대상

class CSocServer : public CSocket
{
public:
	CSocServer();
	virtual ~CSocServer();

	void Init(HWND hWnd);
	HWND m_hWnd; // 메인 윈도우 핸들
	CSocCom m_socCom;
	virtual void OnAccept(int nErrorCode);
	CSocCom* GetAcceptSocCom();
};


