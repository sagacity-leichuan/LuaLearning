
// MyLuaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyLua.h"
#include "MyLuaDlg.h"
#include "afxdialogex.h"
#include <atlconv.h>
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyLuaDlg �Ի���

lua_State *lua;

CMyLuaDlg::CMyLuaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYLUA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyLuaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyLuaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyLuaDlg::OnBnClickedLoad)
END_MESSAGE_MAP()


// CMyLuaDlg ��Ϣ�������
static CMyLuaDlg *dlg;

int Alert(lua_State *L)
{
	const char *msg = lua_tostring(L,-1);
	USES_CONVERSION;
	MessageBox(0, A2W(msg), L"Lua msg", 0);
	return 0;
}

int GetText(lua_State *L)
{
	int id = lua_tonumber(L, 1);
	CString path;
	dlg->GetDlgItem(id)->GetWindowTextW(path);
	USES_CONVERSION;
	char *p = T2A(path);
	lua_pushstring(L, p);
	return 1;
}

int SetText(lua_State *L)
{
	int id = lua_tonumber(L, 1);
	const char* text = lua_tostring(L, 2);
	USES_CONVERSION;
	dlg->GetDlgItem(id)->SetWindowTextW(A2W(text));
	return 0;
}

BOOL CMyLuaDlg::OnInitDialog()
{
	dlg = this;
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	lua = lua_open();
	luaopen_base(lua);		//�򿪻�����
	luaopen_table(lua);		//��table��
	luaL_openlibs(lua);		//��IO��
	luaopen_string(lua);	//��string��
	luaopen_math(lua);		//��math��

	lua_register(lua, "GetText", GetText);
	lua_register(lua, "SetText", SetText);
	lua_register(lua, "Alert", Alert);

	if (luaL_loadfile(lua, "mylua.lua"))
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n ִ�нű��ļ�ʧ��", error);
		return TRUE;
	}
	if (lua_pcall(lua, 0, 0, 0))
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n ִ�нű��ļ�ʧ��", error);
		return TRUE;
	}

	lua_getglobal(lua, "width");
	int width = lua_tonumber(lua, -1);
	lua_pop(lua, 1);
	lua_getglobal(lua, "hight");
	int hight = lua_tonumber(lua, -1);
	lua_pop(lua, 1);
	this->MoveWindow(0, 0, width, hight);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyLuaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyLuaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyLuaDlg::OnBnClickedLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	lua_getglobal(lua, "Load");
	lua_pcall(lua, 0, 0, 0);
}
