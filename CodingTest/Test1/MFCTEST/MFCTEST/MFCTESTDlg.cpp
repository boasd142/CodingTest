
// MFCTESTDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCTEST.h"
#include "MFCTESTDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> points;
std::pair<int, int>* movingpoint = nullptr;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


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


// CMFCTESTDlg 대화 상자
CMFCTESTDlg::CMFCTESTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
	, RADIUS(0)
	, THICK(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, RADIUS);
	DDX_Text(pDX, IDC_EDIT_THICK, THICK);
}

BEGIN_MESSAGE_MAP(CMFCTESTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_BN_CLICKED(IDC_BTN_RESET, &CMFCTESTDlg::OnBnClickedBtnReset)
ON_BN_CLICKED(IDC_BTN_RANDOM, &CMFCTESTDlg::OnBnClickedBtnRandom)
END_MESSAGE_MAP()


// CMFCTESTDlg 메시지 처리기

BOOL CMFCTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	std::cout << "console started" << std::endl;
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	int nWidth = 1080;
	int nHeight = 800;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	
	memset(fm, 0xff, nWidth*nHeight);
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCTESTDlg::OnPaint()
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
HCURSOR CMFCTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCTESTDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray) {
	if (m_image.IsNull()) {
		std::cout << "Error: m_image is not initialized!" << std::endl;
		return;
	}
	
	int nPitch = m_image.GetPitch();
	int minX = 0, minY = 0;
	int maxX = 1079, maxY = 799;
	for (int j = y - nRadius; j < y + nRadius; j++) {
		for (int i = x - nRadius; i < x + nRadius; i++) {
			if (isInCircle(i, j, x, y, nRadius)&& IsInRange(i,j,minX, minY, maxX, maxY)) {
				fm[j * nPitch + i] = nGray;
			}
		}
	}
	updateDisplay();
}
bool CMFCTESTDlg::IsInRange(int i, int j, int minX, int minY, int maxX, int maxY)
{
	return (i >= minX && i <= maxX && j >= minY && j <= maxY);
}

void CMFCTESTDlg::updateDisplay() {
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

bool CMFCTESTDlg::isInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius) {
	double dX = x - nCenterX;
	double dY = y - nCenterY;
	return (dX * dX + dY * dY < nRadius * nRadius);
}

void CMFCTESTDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	UpdateData();
	movingpoint = nullptr;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nRadius = RADIUS;
	int nGray = 0;
	int thick = THICK;
	if (nCcount < 3 && point.x <= 1080 && point.y <= 800 && nRadius >= 1) {
		std::cout << "Mouse Clicked at: (" << point.x << ", " << point.y << ")" << std::endl;

		points.push_back({ point.x, point.y });
		drawCircle(fm, point.x, point.y, nRadius, nGray);

		nCcount++;
		std::cout << "Clicked Count : " << nCcount << std::endl;
	}
	if (nCcount >= 2) {
		drawLargeCircle(fm, points, nGray, thick);
		for (const auto& p : points) {
			drawCircle(fm, p.first, p.second, nRadius, nGray);
		}
	}
	else{
		std::cout << "Can't make point" << std::endl;
	}
	bisblack = false;
	
	CDialogEx::OnLButtonUp(nFlags, point);
}

// 버튼 클릭시 가장 가까운 좌표를 찾고, 검정색인지 확인
void CMFCTESTDlg::OnLButtonDown(UINT nFlags, CPoint point) {
	movingpoint = FindnearP(point.x, point.y);
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nRadius = RADIUS;
	int nGray = 0;

	if (IsBlack(point.x, point.y) && nCcount == 3) {
		std::cout << "Point is black" << std::endl;
		bisblack = true;
	}
	else {
		std::cout << "Point is not black" << std::endl;
		bisblack = false;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


// 검정색이 확인되면 point를 움직이며 이전 좌표들을 지움 또한 행동이 끝나면 모든 points들에 대한 원을 다시 그려낸다.
void CMFCTESTDlg::OnMouseMove(UINT nFlags, CPoint point) {
	int nRadius = RADIUS;
	int nGray = 0;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nPitch = m_image.GetPitch();
	if (bisblack) {
		if (IsBlack(point.x, point.y)) {
			drawCircle(fm, movingpoint->first, movingpoint->second, nRadius, 255);
			if (movingpoint) {
				movingpoint->first = point.x;
				movingpoint->second = point.y;
				memset(fm, 0xff, 1080 * 800);
				std::cout << "POINTS ARE CHANGED TO ";
				for (const auto& p : points) {
					std::cout <<  "(" << p.first << ", " << p.second << ") ";
				}
				std::cout << std::endl;
			}
		}
	}
	
	for (const auto& p : points) {
		drawCircle(fm, p.first, p.second, nRadius, nGray);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CMFCTESTDlg::OnBnClickedBtnReset() {
	RESET();
}

void CMFCTESTDlg::RESET() {
	int nWidth = 1080;
	int nHeight = 800;
	int nBpp = 8;

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	points.clear();
	nCcount = 0;

	std::cout << "Reset background and clear all points" << std::endl;

	updateDisplay();
}

bool CMFCTESTDlg::IsBlack(int x, int y) {
	if (m_image.IsNull()) {
		std::cout << "Error: m_image is not initialized!" << std::endl;
		return false;
	}

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	if (x < 0 || x >= nWidth || y < 0 || y >= nHeight) {
		return false;
	}

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	return (fm[y * nPitch + x] == 0);
}

std::pair<int, int>* CMFCTESTDlg::FindnearP(int x, int y) {
	if (points.empty()) {
		return nullptr;
	}

	std::pair<int, int>* nearestPoint = nullptr;
	double minDist = RADIUS * RADIUS;

	for (auto& p : points) {
		int px = p.first;
		int py = p.second;
		double dist = (px - x) * (px - x) + (py - y) * (py - y);

		if (dist <= minDist) {
			minDist = dist;
			nearestPoint = &p;
		}
	}
	return nearestPoint;
}



void CMFCTESTDlg::drawLargeCircle(unsigned char* fm, const std::vector<std::pair<int, int>>& points, int nGray, double thick) {
	if (points.size() != 3) {
		return;
	}
	
	memset(fm, 0xff, 1080* 800);
	int x1 = points[0].first, y1 = points[0].second;
	int x2 = points[1].first, y2 = points[1].second;
	int x3 = points[2].first, y3 = points[2].second;

	//3점을 지나는 원의 반지름 및 중앙점을 구하는 공식
	double d = 2.0 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

	if (d == 0) {
		return;
	}

	double cx = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / d;
	double cy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / d;

	double radius = (int)sqrt((x1 - cx) * (x1 - cx) + (y1 - cy) * (y1 - cy));

	std::cout << "Circumcircle Center: (" << (int)cx << ", " << (int)cy << "), Radius: " << radius << std::endl;

	drawCircle(fm, (int)cx, (int)cy, radius + thick/2, 0);
	drawCircle(fm, (int)cx, (int)cy, radius - thick/2, 255);	
	
}



#include <random>
#include <thread>

void CMFCTESTDlg::OnBnClickedBtnRandom()
{	
	if (nCcount >= 3) {
		std::thread([this]() {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> distX(0 + RADIUS * 2, 1080 - RADIUS * 2); // X 좌표 범위 (화면 크기 고려)
			std::uniform_int_distribution<int> distY(0 + RADIUS * 2, 800 - RADIUS * 2); // Y 좌표 범위

			for (int i = 0; i < 10; ++i) {
				for (auto& p : points) {
					p.first = distX(gen);
					p.second = distY(gen);
					std::cout << i + 1 << std::endl;
					std::cout << "(" << p.first << ") (" << p.second << ") " << std::endl;
				}

				unsigned char* fm = (unsigned char*)m_image.GetBits();
				memset(fm, 0xff, 1080 * 800);

				int nRadius = RADIUS;
				int nGray = 0;
				int thick = THICK;


				if (points.size() == 3) {
					drawLargeCircle(fm, points, nGray, thick);
				}
				for (const auto& p : points) {
					drawCircle(fm, p.first, p.second, nRadius, nGray);
				}

				PostMessage(WM_PAINT);

				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			}).detach();
	}
	else {
		std::cout << "Not enough points" << std::endl;
		return;
	}
	
}

