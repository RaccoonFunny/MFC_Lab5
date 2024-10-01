
// MFC_Lab5Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC_Lab5.h"
#include "MFC_Lab5Dlg.h"
#include "afxdialogex.h"

#include <fstream>   // Для работы с файлами
#include <sstream>   // Для работы с потоками строк
#include <vector>    // Для использования временного хранения данных

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CT_A 0 //константы для задания режима «заморозки» переменных a,b,r
#define CT_B 1 // константы для задания режима «заморозки» переменных b,a,r
#define CT_R 2 // константы для задания режима «заморозки» переменных r,a,b


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCLab5Dlg dialog



CMFCLab5Dlg::CMFCLab5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_LAB5_DIALOG, pParent)
	, aprX(10)
	, filePath(_T("C:\\Users\\RaccoonF\\Downloads\\dat.txt"))
	, aprY(9)
	, aprR(8)
	, aprRes(_T(""))
	, calcX(_T(""))
	, calcY(_T(""))
	, calcR(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCLab5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, aprX);
	DDX_Text(pDX, IDC_EDIT1, filePath);
	DDX_Text(pDX, IDC_EDIT3, aprY);
	DDX_Text(pDX, IDC_EDIT4, aprR);
	DDX_Text(pDX, IDC_EDIT6, aprRes);
	DDX_Text(pDX, IDC_EDIT5, calcX);
	DDX_Text(pDX, IDC_EDIT7, calcY);
	DDX_Text(pDX, IDC_EDIT8, calcR);
}

BEGIN_MESSAGE_MAP(CMFCLab5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCLab5Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCLab5Dlg::OnEnChangeEdit6)
END_MESSAGE_MAP()


// CMFCLab5Dlg message handlers

BOOL CMFCLab5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCLab5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCLab5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCLab5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double MSQ(double a, double b, double r, int size, double** arr)
{
	double res = 0;
	//цикл по всем точкам 
	for (int i = 0; i < size; i++)
	{
		//отклонение по нормали к дуге окружности
		double delta = pow(arr[i][0] - a, 2) + pow(arr[i][1] - b, 2) - r * r;
		res += delta * delta; //возводим отклонение в квадрат
	}
	return res; //возвращаем результат в программу верхнего уровня

}


double** getArray(CString filePath, int& numRows){
	FILE* file;
	// Открытие файла
	if (fopen_s(&file, CStringA(filePath), "r") != 0) {
		return nullptr;
	}

	std::vector<std::vector<double>> tempData;
	char line[256];

	while (fgets(line, sizeof(line), file)) {
		std::vector<double> row;
		char* context;
		char* token = strtok_s(line, "\t", &context);

		while (token) {
			// Заменяем запятую на точку потому что "Я РУССКИЙ и я иду до конца"
			for (char* p = token; *p; ++p) {
				if (*p == ',') {
					*p = '.';
				}
			}

			row.push_back(static_cast<double>(atof(token)));
			token = strtok_s(nullptr, "\t", &context);
		}

		if (row.size() == 2) { // Ожидаем два столбца
			tempData.push_back(row);
		}
	}

	fclose(file); // Закрываем файл

	numRows = tempData.size(); // Количество строк
	double** result = new double* [numRows];

	for (int i = 0; i < numRows; ++i) {
		result[i] = new double[2];
		result[i][0] = tempData[i][0]; // Первый столбец
		result[i][1] = tempData[i][1]; // Второй столбец
	}

	return result; // Возвращаем массив double**
}

void LinearDixotomy(double& value1, double value2, double value3, int type, int size, double** arr)
{
	double epsilon = 0.000001f; //погрешность вычисления

	double step = epsilon * 100; //шаг

	double V_Left, V_Right, MSQ1, MSQ2; //значения на границах интервала и СКО

	switch (type) //переключатель по типам расчета
	{
	case CT_A: //расчет по а
		MSQ1 = MSQ(value1, value2, value3, size, arr);
		MSQ2 = MSQ(value1 - step, value2, value3, size, arr);
		break;
	case CT_B: //расчет по b
		MSQ1 = MSQ(value2, value1, value3, size, arr);
		MSQ2 = MSQ(value2, value1 - step, value3, size, arr);
		break;
	case CT_R: //расчет по r
		MSQ1 = MSQ(value2, value3, value1, size, arr);
		MSQ2 = MSQ(value2, value3, value1 - step, size, arr);
		break;
	}

	if (MSQ1 > MSQ2)
	{
		V_Right = V_Left = value1;
		while (true)
		{
			V_Left = V_Left - step;

			switch (type)
			{
			case CT_A: //расчет по а
				MSQ1 = MSQ(V_Left, value2, value3, size, arr);
				MSQ2 = MSQ(V_Left + step, value2, value3, size, arr);
				break;
			case CT_B: //расчет по b
				MSQ1 = MSQ(value2, V_Left, value3, size, arr);
				MSQ2 = MSQ(value2, V_Left + step, value3, size, arr);
				break;
			case CT_R: //расчет по r
				MSQ1 = MSQ(value2, value3, V_Left, size, arr);
				MSQ2 = MSQ(value2, value3, V_Left + step, size, arr);
				break;
			}

			if (MSQ1 > MSQ2)
				break;
		}
	}
	else
	{
		V_Right = V_Left = value1;
		while (true)
		{
			V_Right = V_Right + step;
			switch (type)
			{
			case CT_A: //расчет по а
				MSQ1 = MSQ(V_Right, value2, value3, size, arr);
				MSQ2 = MSQ(V_Right + step, value2, value3, size, arr);
				break;
			case CT_B: //расчет по b
				MSQ1 = MSQ(value2, V_Right, value3, size, arr);
				MSQ2 = MSQ(value2, V_Right + step, value3, size, arr);
				break;
			case CT_R: //расчет по c
				MSQ1 = MSQ(value2, value3, V_Right, size, arr);
				MSQ2 = MSQ(value2, value3, V_Right + step, size, arr);
				break;
			}
			if (MSQ1 < MSQ2)
				break;
		}
	}

	double V_Mid; //значение в середине интервала

	//финальная дихотомия	
	while (V_Right - V_Left > epsilon) //цикл дихотомии
	{
		V_Mid = (V_Right + V_Left) / 2.f; //вычисление середины интервала
		switch (type) //переключатель по типам расчета
		{
		case CT_A: //расчет по а
			MSQ1 = MSQ(V_Mid + epsilon / 3, value2, value3, size, arr);
			MSQ2 = MSQ(V_Mid - epsilon / 3, value2, value3, size, arr);
			break;

		case CT_B: //расчет по b
			MSQ1 = MSQ(value2, V_Mid + epsilon / 3, value3, size, arr);
			MSQ2 = MSQ(value2, V_Mid - epsilon / 3, value3, size, arr);
			break;
		case CT_R: //расчет по r
			MSQ1 = MSQ(value2, value3, V_Mid + epsilon / 3, size, arr);
			MSQ2 = MSQ(value2, value3, V_Mid - epsilon / 3, size, arr);
			break;
		}
		if (MSQ1 < MSQ2)
		{
			V_Left = V_Mid;
		}
		else
		{
			V_Right = V_Mid;
		}

	}

	value1 = (V_Right + V_Left) / 2.f; //середина интервала

}


void CMFCLab5Dlg::OnBnClickedButton1()
{
	int numRows = 0;
	double** arr = getArray(filePath, numRows);
	if (arr == nullptr) {
		AfxMessageBox(_T("Ошибка при открытии файла или чтении данных."));
		return;
	}
	double x = 0;
	double y = 0;
	double r = 0;

	for (int i = 0; i < numRows; i++) {
		x += arr[i][0];
		y += arr[i][1];
	}

	x /= numRows;
	y /= numRows;

	for (int i = 0; i < numRows; i++)
	{
		r += sqrt(pow(arr[i][0] - x, 2) + pow(arr[i][1] - y, 2));
	}

	r /= numRows;
	
	double oldX, oldY, oldR;
	while (true) //цикл пока не достигнем требуемой точности
	{
		oldX = x; //запоминаем старое значение А
		oldY = y; //запоминаем старое значение B
		oldR = r; //запоминаем старое значение R

		LinearDixotomy(x, y, r, CT_A, numRows, arr); //запускаем дихотомию по А
		LinearDixotomy(y, x, r, CT_B, numRows, arr); //запускаем дихотомию по B
		LinearDixotomy(r, x, y, CT_R, numRows, arr); //запускаем дихотомию по R

		if (sqrt(pow(x - oldX, 2) + pow(y - oldY, 2) + pow(r - oldR, 2)) < 0.0001)
			break; //если достигли требуемой точности - выходим
	}

	double rMin = 100000;
	double rMax = -100000;
	double temp = 0;
	for (int i = 0; i < numRows; i++)
	{
		temp = sqrt(pow(arr[i][0] - x, 2) + pow(arr[i][1] - y, 2));
		if (temp > rMax) {
			rMax = temp;
		}
		if (temp < rMin) {
			rMin = temp;
		}

	}

	calcX.Format(L"%.9lf", x);
	calcY.Format(L"%.9lf", y);
	calcR.Format(L"%.9lf", r);
	aprRes.Format(L"%.9lf", abs((rMin - rMax) / 2));
	UpdateData(false);
}


void CMFCLab5Dlg::OnEnChangeEdit6()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
