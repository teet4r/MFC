﻿// SocCom.cpp: 구현 파일
//

#include "pch.h"
#include <afxsock.h>
#include "ChatServerR.h"
#include "SocCom.h"


// CSocCom

CSocCom::CSocCom()
{
}

CSocCom::~CSocCom()
{
}


// CSocCom 멤버 함수


void CSocCom::Init(HWND hWnd)
{
	// TODO: 여기에 구현 코드 추가.
	m_hWnd = hWnd;
}


void CSocCom::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hWnd, UM_RECEIVE, 0, 0);

	CSocket::OnReceive(nErrorCode);
}
