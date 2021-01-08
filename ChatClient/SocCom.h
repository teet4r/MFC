#pragma once

// CSocCom 명령 대상

class CSocCom : public CSocket
{
public:
	CSocCom();
	virtual ~CSocCom();

	void Init(HWND hWnd);
	HWND m_hWnd;
	virtual void OnReceive(int nErrorCode);
};