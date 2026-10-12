#include "bingoeventdlg.h"

extern Fresh* g_pFresh;

namespace NS_BINGO
{
	// clang-format off
	int ns_board[10][5 * 5] = {
		{
			13, 2 , 10, 25, 1 ,
			12, 8 , 22, 5 , 16,
			19, 6 , 15, 14, 24,
			17, 7 , 4 , 21, 18,
			9 , 20, 23, 11, 3 ,
		},
		{
			7 , 16, 18, 10, 21,
			14, 1 , 20, 2 , 9 ,
			19, 3 , 6 , 13, 25,
			8 , 5 , 17, 23, 12,
			15, 11, 24, 22, 4 ,
		},
		{
			12, 3 , 16, 9 , 1 ,
			4 , 5 , 2 , 21, 10,
			23, 6 , 18, 14, 22,
			20, 24, 15, 13, 17,
			7 , 8 , 19, 11, 25,
		},
		{
			6 , 2 , 21, 3 , 17,
			22, 20, 19, 8 , 10,
			14, 5 , 13, 25, 1 ,
			7 , 23, 11, 18, 16,
			24, 9 , 12, 15, 4 ,
		},
		{
			20, 17, 12, 9 , 10,
			25, 1 , 19, 14, 15,
			16, 3 , 4 , 7 , 11,
			18, 13, 21, 23, 22,
			6 , 8 , 2 , 5 , 24,
		},
		{
			23, 7 , 3 , 21, 11,
			2 , 4 , 22, 24, 5 ,
			19, 17, 10, 8 , 18,
			14, 15, 20, 6 , 16,
			12, 13, 25, 1 , 9 ,
		},
		{
			23, 21, 3 , 4 , 16,
			2 , 15, 24, 11, 10,
			13, 18, 17, 6 , 22,
			5 , 9 , 8 , 7 , 1 ,
			25, 14, 12, 20, 19,
		},
		{
			1 , 16, 15, 4 , 24,
			5 , 2 , 12, 20, 22,
			9 , 13, 8 , 23, 21,
			17, 11, 3 , 19, 18,
			7 , 14, 6 , 25, 10,
		},
		{
			5 , 20, 10, 4 , 7 ,
			8 , 23, 17, 24, 22,
			3 , 13, 12, 25, 14,
			16, 9 , 19, 6 , 11,
			18, 21, 15, 1 , 2 ,
		},
		{
			25, 15, 17, 7 , 18,
			19, 13, 20, 22, 11,
			1 , 14, 21, 5 , 16,
			9 , 4 , 2 , 8 , 24,
			10, 6 , 12, 3 , 23,
		},
	};
	// clang-format on
	unsigned long ns_pointTable[25] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40,
		0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000,
		0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000,
		0x800000, 0x1000000 };
	unsigned int ns_resultTable[12] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40,
		0x80, 0x100, 0x200, 0x400, 0x800 };
}

CBingoPoint::CBingoPoint(int number)
	: m_pointNumber(number), m_bEnable(false)
{
}

CBingoPoint::~CBingoPoint()
{
}

void CBingoPoint::DrawPoint(FrGraphicInterface* gdi,
	const Bitmap** const bitmap, const WRect& rect, float x, float y)
{
	const Bitmap* image;
	if (IsProperty(PROPERTY_OVER))
		image = bitmap[4];
	else if (IsProperty(PROPERTY_AIMED))
		image = bitmap[3];
	else
		image = bitmap[2];
	gdi->DrawTexture(image, rect, WRect(x, y, rect.w, rect.h), 0xffffffff, 0);
}

CBingoPoint& CBingoPoint::operator=(int number)
{
	m_pointNumber = number;
	return *this;
}

CBingoPoint& CBingoPoint::operator=(bool enabled)
{
	m_bEnable = enabled;
	return *this;
}

CBingoLine::CBingoLine(int size)
{
}

CBingoLine::~CBingoLine()
{
}

void CBingoLine::ClearOverProperty()
{
	int count = m_points.size();
	for (int i = 0; i < count; ++i)
		m_points[i].DisableProperty(CBingoPoint::PROPERTY_OVER);
}

CBingoPoint* CBingoLine::FindBingoPoint(int number)
{
	int count = m_points.size();
	for (int i = 0; i < count; ++i)
		if (m_points[i].GetPointNumber() == number)
			return &m_points[i];
	return NULL;
}

CBingoPoint& CBingoLine::GetBingoPoint(int index)
{
	return m_points[index];
}

const CBingoPoint& CBingoLine::GetBingoPoint(int index) const
{
	return m_points[index];
}

int CBingoLine::IsHavePointNumber(int number)
{
	if (m_points.empty())
		return -1;
	int count = m_points.size();
	for (int i = 0; i < count; ++i)
		if (m_points[i].GetPointNumber() == number)
			return i;
	return -1;
}

bool CBingoLine::IsCompleteLine()
{
	int count = m_points.size();
	for (int i = 0; i < count; ++i)
		if (!m_points[i].IsProperty(CBingoPoint::PROPERTY_AIMED))
			return false;
	return true;
}

int CBingoLine::operator[](int index)
{
	return m_points[index].GetPointNumber();
}

const int CBingoLine::operator[](int index) const
{
	return m_points[index].GetPointNumber();
}

CBingoLine& CBingoLine::operator=(const CBingoLine& line)
{
	m_points.clear();
	m_points.assign(line.m_points.begin(), line.m_points.end());
	m_reserved = line.m_reserved;
	return *this;
}

bool CBingoLine::operator+=(CBingoPoint& point)
{
	m_points.push_back(point);
	return true;
}

CBingoBoard::CBingoBoard()
{
	Initialize();
}

CBingoBoard::~CBingoBoard()
{
}

CBingoLine& CBingoBoard::operator[](int index)
{
	return m_lines[index];
}

bool CBingoBoard::Initialize()
{
	if (!m_lines.empty())
		m_lines.clear();
	for (int row = 0; row < 5; ++row)
	{
		CBingoLine line(5);
		for (int col = 0; col < 5; ++col)
		{
			CBingoPoint point(NS_BINGO::ns_board[0][row * 5 + col]);
			line += point;
		}
		m_lines.push_back(line);
	}
	m_completeLine.reserve(m_lines.size() * 2 + 2);
	m_completeLine.assign(12, 0);
	return true;
}

bool CBingoBoard::AimPoint(int number)
{
	int count = m_lines.size();
	int pointIndex = -1;
	int row = 0;
	for (; row < count; ++row)
	{
		pointIndex = m_lines[row].IsHavePointNumber(number);
		if (pointIndex != -1)
			break;
	}
	CBingoPoint& point = m_lines[row].GetBingoPoint(pointIndex);
	if (point.IsProperty(CBingoPoint::PROPERTY_AIMED))
		return false;
	point.EnableProperty(CBingoPoint::PROPERTY_AIMED);
	ReScanBoard();
	return true;
}

void CBingoBoard::ClearOverProperty()
{
	int count = m_lines.size();
	for (int i = 0; i < count; ++i)
		m_lines[i].ClearOverProperty();
}

CBingoPoint* CBingoBoard::FindBingoPoint(int number)
{
	int count = m_lines.size();
	for (int i = 0; i < count; ++i)
	{
		CBingoPoint* point = m_lines[i].FindBingoPoint(number);
		if (point)
			return point;
	}
	return NULL;
}

void CBingoBoard::ReScanBoard()
{
	int resultIndex = 0;
	int count = m_lines.size();
	for (int row = 0; row < count; ++row)
	{
		if (m_lines[row].IsCompleteLine())
			m_completeLine[resultIndex] = 1;
		++resultIndex;
	}
	bool complete = false;
	for (int col = 0; col < count; ++col)
	{
		for (int row = 0; row < count; ++row)
		{
			if (!m_lines[row].GetBingoPoint(row).IsProperty(
					CBingoPoint::PROPERTY_AIMED))
				break;
			complete = true;
		}
		if (complete == true)
			m_completeLine[resultIndex] = 1;
		++resultIndex;
		complete = false;
	}
	complete = true;
	for (int row = 0, col = 0; row < count; ++row)
	{
		if (!m_lines[row].GetBingoPoint(col--).IsProperty(
				CBingoPoint::PROPERTY_AIMED))
		{
			complete = false;
			break;
		}
	}
	if (complete == true)
		m_completeLine[resultIndex++] = 1;
	complete = true;
	for (int row = 0, col = count - 1; row < count; ++row)
	{
		if (!m_lines[row].GetBingoPoint(col--).IsProperty(
				CBingoPoint::PROPERTY_AIMED))
		{
			complete = false;
			break;
		}
	}
	if (complete == true)
		m_completeLine[resultIndex] = 1;
}

IMPLEMENT_OBJECT(FrBingoEventDlg, FrForm)
BEGIN_FRESH_MSGMAP(FrBingoEventDlg, FrForm)
ON_FRESH_VI("start", FRCMD_INIT, FrBingoEventDlg::OnInitStartButton)
ON_FRESH_VV("start", FRCMD_LBUTTONDOWN,
	FrBingoEventDlg::OnLButtonDownStartButton)
ON_FRESH_VI("detail", FRCMD_INIT, FrBingoEventDlg::OnInitEventDetail)
ON_FRESH_VV("detail", FRCMD_LBUTTONDOWN,
	FrBingoEventDlg::OnLButtonDownEventDetail)
ON_FRESH_VI("boardNumber", FRCMD_INIT, FrBingoEventDlg::OnInitBoardNumberArea)
ON_FRESH_VI("boardNumber", FRCMD_OWNERDRAW,
	FrBingoEventDlg::OnOwnerDrawBoardNumberArea)
END_FRESH_MSGMAP()

FrBingoEventDlg::FrBingoEventDlg()
{
	m_pStartButton = NULL;
	m_pEventDetail = NULL;
	m_pDetailDlg = NULL;
	m_pGiftDlg = NULL;
	m_tryCount = 0;
	m_boardIndex = 0;
	memset(m_pBitmap, 0, sizeof(m_pBitmap));
	m_pBoardNumberArea = NULL;
	m_selectedNumber = 0;
	m_completeLine = 0;
	m_aimedPoint = 0;
	m_newLine = 0;
	m_bWaitResult = false;
	m_bReserved1 = false;
	m_bReserved2 = false;
	memset(m_tryCountText, 0, sizeof(m_tryCountText));
}

FrBingoEventDlg::~FrBingoEventDlg()
{
}

bool FrBingoEventDlg::OnInit()
{
	m_boardIndex = Doc()->m_myInfo.info.dwUID % 10;
	LoadBingoImage();
	m_boardPos = WPoint(40, 205);
	m_randomNumberPos = WPoint(380, 180);
	m_tryCountPos = WPoint(380, 403);
	InitCharMatchMap();
	InitNumberMatchMap();
	return FrForm::OnInit();
}

void __fastcall CalcOffset(int index, int columns, float& x, float& y,
	float width, float height, float gap)
{
	x = (float)(index % columns) * width;
	y = (float)(index / columns) * height;
}

bool FrBingoEventDlg::OnDetailDlgResult(int result, FrForm* form)
{
	m_pDetailDlg = NULL;
	return true;
}

bool FrBingoEventDlg::OnGiftDlgResult(int result, FrForm* form)
{
	m_pGiftDlg = NULL;
	return true;
}

void FrBingoEventDlg::SetBingoData(GlobalEnum::sBingoInfo* info)
{
	m_tryCount = info->tryCount;
	m_completeLine = info->completeLine;
	m_aimedPoint = info->aimedPoint;
	memset(m_tryCountText, 0, sizeof(m_tryCountText));
	itoa(m_tryCount > 99 ? 99 : m_tryCount, m_tryCountText, 10);
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 5; ++col)
		{
			CBingoPoint& point = m_board[row].GetBingoPoint(col);
			int number = NS_BINGO::ns_board[m_boardIndex][row * 5 + col];
			point.SetPointNumber(number);
			if (m_aimedPoint & NS_BINGO::ns_pointTable[number - 1])
				point.EnableProperty(CBingoPoint::PROPERTY_AIMED);
		}
	}
}

void FrBingoEventDlg::SetGiftData(std::vector<unsigned long>* gifts,
	unsigned int completeLine)
{
	m_completeLine = completeLine;
	m_pGiftDlg =
		CreateForm<FrBingoGiftDlg>(g_pFresh->GetManager(), this, "bingo_gift");
	if (m_pGiftDlg)
	{
		m_pGiftDlg->Open((FRESH_PFN_RESULT)&FrBingoEventDlg::OnGiftDlgResult,
			1);
		m_pGiftDlg->SetGiftData(gifts);
	}
}

void FrBingoEventDlg::SetSelectedData(int number, int count,
	unsigned int newLine)
{
	m_selectedNumber = number;
	CBingoPoint* point = m_board.FindBingoPoint(number);
	if (point)
		point->EnableProperty(CBingoPoint::PROPERTY_OVER);
	m_newLine = newLine;
	m_bWaitResult = false;
}

void FrBingoEventDlg::InitCharMatchMap()
{
	char character = '0';
	for (int i = 0; i < 10; ++i)
	{
		float x, y;
		CalcOffset(i, 10, x, y, 20, 32, 0);
		m_charMatchMap.insert(std::make_pair(character++, sPoint(x, y)));
	}
}

void FrBingoEventDlg::InitNumberMatchMap()
{
	for (int i = 0; i < 25; ++i)
	{
		float x, y;
		CalcOffset(i, 6, x, y, 39, 32, 0);
		m_boardNumberMatchMap.insert(std::make_pair(i + 1, sPoint(x, y)));
	}
	for (int i = 0; i < 25; ++i)
	{
		float x, y;
		CalcOffset(i, 5, x, y, 48, 37, 0);
		m_randomNumberMatchMap.insert(std::make_pair(i + 1, sPoint(x, y)));
	}
}

void FrBingoEventDlg::LoadBingoImage()
{
	const char* images[] = { "bingo_conut_num_all", "bingo_num_all",
		"bingo_num_01", "bingo_num_02", "bingo_num_03", "bingo_line_1",
		"bingo_line_2", "bingo_line_3", "bingo_line_4", "bingo_ment" };
	for (int i = 0; i < 10; ++i)
		m_pBitmap[i] = g_pFresh->RegisterBitmap(images[i]);
}

void FrBingoEventDlg::OnProc(const float dt)
{
}

void FrBingoEventDlg::DrawBoardNumber(FrGraphicInterface* gdi,
	const WRect& rect)
{
	WRect source(0, 0, 39, 32);
	float colX = 0;
	float rowY = 0, rowX = 0;
	float colGap = 0, rowGap = 0;
	for (int row = 0; row < 5; colX = 0, colGap = 0, ++row)
	{
		float colY = 0;
		for (int col = 0; col < 5; ++col)
		{
			int number = m_board[row][col];
			const sPoint& point = m_boardNumberMatchMap[number];
			source.x = point.x;
			source.y = point.y;
			CBingoPoint& cell = m_board[row].GetBingoPoint(col);
			float x = colGap + rect.x + rowX + colX + m_boardPos.x;
			float y = rect.y + m_boardPos.y + colY + rowGap + rowY;
			cell.DrawPoint(gdi, m_pBitmap, source, x, y);
			colX = (source.w + 9) * (col + 1);
			colGap += 4;
			colY -= 8;
		}
		rowX = 9.0f * (row + 1);
		rowY = (source.h + 18) * (row + 1);
		rowGap += 2;
	}
}

void FrBingoEventDlg::DrawRandomNumber(FrGraphicInterface* gdi,
	const WRect& rect)
{
	WRect source(0, 0, 48, 37);
	const sPoint& point = m_randomNumberMatchMap[m_selectedNumber];
	source.x = point.x;
	source.y = point.y;
	gdi->DrawTexture(m_pBitmap[1], source,
		WRect(m_randomNumberPos.x + rect.x, m_randomNumberPos.y + rect.y,
			source.w, source.h),
		0xffffffff, 0);
}

void FrBingoEventDlg::DrawTryCount(FrGraphicInterface* gdi, const WRect& rect)
{
	WRect source(0, 0, 20, 32);
	float offset = 0;
	int count = strlen(m_tryCountText);
	float x = m_tryCountPos.x + rect.x;
	float y = m_tryCountPos.y + rect.y;
	switch (count)
	{
	case 1:
		x += 12;
		break;
	case 2:
		x += 3;
		break;
	}
	for (int i = 0; i < count; ++i)
	{
		const sPoint& point = m_charMatchMap[m_tryCountText[i]];
		source.x = point.x;
		source.y = point.y;
		gdi->DrawTexture(m_pBitmap[0], source,
			WRect(x + offset, y, source.w, source.h), 0xffffffff, 0);
		offset += 20;
	}
}

void FrBingoEventDlg::DrawCompleteBar(FrGraphicInterface* gdi,
	const WRect& rect)
{
	for (int i = 0; i < 12; ++i)
	{
		const Bitmap* image;
		float x, y, width, height;
		if (i < 5)
		{
			image = m_pBitmap[5];
			width = 221;
			height = 42;
			x = i * 7.5f + 15;
			y = i * 53.0f - 20;
		}
		else if (i < 10 && i > 4)
		{
			image = m_pBitmap[6];
			width = 44;
			height = 219;
			x = (i - 5) * 54.0f + 10;
			y = 15 - (i - 5) * 8.0f;
		}
		else if (i == 10)
		{
			image = m_pBitmap[7];
			width = 246;
			height = 181;
			x = 20;
			y = 20;
		}
		else
		{
			image = m_pBitmap[8];
			width = 181;
			height = 246;
			x = 50;
			y = -15;
		}
		if (m_completeLine & NS_BINGO::ns_resultTable[i])
			gdi->DrawTexture(image,
				WRect(m_boardPos.x + rect.x + x, m_boardPos.y + rect.y + y,
					width, height),
				0xffffffff, 0);
	}
}

void FrBingoEventDlg::DrawBingoLogo(FrGraphicInterface* gdi, const WRect& rect)
{
	unsigned int width = m_pBitmap[9]->Width();
	unsigned int height = m_pBitmap[9]->Height();
	for (int i = 0; i < 12; ++i)
	{
		float x, y;
		if (i < 5)
		{
			y = i * 53.0f - 20;
			x = (i * 7.5f + 15) + (float)(width / 2);
		}
		else if (i < 10 && i > 4)
		{
			x = (i - 5) * 54.0f + 10;
			y = (float)(height / 2) + (15 - (i - 5) * 8.0f);
		}
		else if (i == 10)
		{
			x = (float)(width / 2) + 20;
			y = (float)(height / 2) + 20;
		}
		else
		{
			x = (float)(width / 2) + 50;
			y = (float)(height / 2) - 15;
		}
		if (m_newLine & NS_BINGO::ns_resultTable[i])
			gdi->DrawTexture(m_pBitmap[9],
				WRect(m_boardPos.x + rect.x + x, m_boardPos.y + rect.y + y, 67,
					32),
				0xffffffff, 0);
	}
}

void FrBingoEventDlg::OnInitStartButton(int param)
{
	m_pStartButton = DYNAMIC_CAST(FrButton, (FrWnd*)param);
}

void FrBingoEventDlg::OnLButtonDownStartButton()
{
	if (m_bWaitResult == true)
		return;
	if (m_tryCount < 1)
	{
		AfxGetTask()->GetActor("Lobby") << MsgObject(NULL, 35,
			(int)"\xc3\xdf\xc3\xb7\xb1\xc7\xc0\xcc \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.",
			0, 0, 0, 0);
		return;
	}
	m_board.ClearOverProperty();
	m_newLine = 0;
	int allLines = 0;
	for (int i = 0; i < 12; ++i)
		allLines += NS_BINGO::ns_resultTable[i];
	if (m_completeLine == allLines)
	{
		AfxGetTask()->GetActor("Lobby") << MsgObject(NULL, 35,
			(int)"\xc0\xcc\xb9\xcc \xb8\xf0\xb5\xe7 \xbc\xb1\xb9\xb0\xc0\xbb \xb4\xd9 \xb9\xde\xc0\xb8\xbc\xcc\xbd\xc0\xb4\xcf\xb4\xd9.",
			0, 0, 0, 0);
		return;
	}
	WSendPacket packet((enumClientPacket)0xe5);
	packet.Encode4(1);
	packet.Send(TO_GAME);
	m_bWaitResult = true;
	AfxGetTask()->SendMsgToMainActor(MsgObject(NULL, 1, 0, 0, 0, 0, 0));
}

void FrBingoEventDlg::OnInitEventDetail(int param)
{
	m_pEventDetail = DYNAMIC_CAST(FrButton, (FrWnd*)param);
}

void FrBingoEventDlg::OnLButtonDownEventDetail()
{
	m_pDetailDlg = CreateForm<FrBingoDetailDlg>(g_pFresh->GetManager(), this,
		"bingo_detail");
	if (m_pDetailDlg)
		m_pDetailDlg->Open(
			(FRESH_PFN_RESULT)&FrBingoEventDlg::OnDetailDlgResult, 1);
}

void FrBingoEventDlg::OnInitBoardNumberArea(int param)
{
	m_pBoardNumberArea = DYNAMIC_CAST(FrArea, (FrWnd*)param);
}

void FrBingoEventDlg::OnOwnerDrawBoardNumberArea(int param)
{
	FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
	if (gdi)
	{
		DrawCompleteBar(gdi, m_rect);
		DrawBoardNumber(gdi, m_rect);
		DrawRandomNumber(gdi, m_rect);
		DrawTryCount(gdi, m_rect);
		DrawBingoLogo(gdi, m_rect);
	}
}

IMPLEMENT_OBJECT(FrBingoDetailDlg, FrForm)
BEGIN_FRESH_MSGMAP(FrBingoDetailDlg, FrForm)
ON_FRESH_VI("detailview", FRCMD_INIT, FrBingoDetailDlg::OnInitExplaneViewer)
END_FRESH_MSGMAP()

FrBingoDetailDlg::FrBingoDetailDlg()
{
}

FrBingoDetailDlg::~FrBingoDetailDlg()
{
}

void FrBingoDetailDlg::OnInitExplaneViewer(int param)
{
	m_pExplaneViewer = DYNAMIC_CAST(FrViewer, (FrWnd*)param);
	if (m_pExplaneViewer)
		m_pExplaneViewer->Open("bingo_explanation.jpg");
}

IMPLEMENT_OBJECT(FrBingoGiftDlg, FrForm)
BEGIN_FRESH_MSGMAP(FrBingoGiftDlg, FrForm)
ON_FRESH_VI("giftList", FRCMD_INIT, FrBingoGiftDlg::OnInitGiftArea)
ON_FRESH_VI("giftList", FRCMD_OWNERDRAW, FrBingoGiftDlg::OnOwnerDrawGiftArea)
END_FRESH_MSGMAP()

FrBingoGiftDlg::FrBingoGiftDlg()
{
	m_pGiftArea = NULL;
	m_offsetX[0] = 84;
	m_offsetX[1] = 52;
	m_offsetX[2] = 21;
	m_offsetX[3] = -5;
}

FrBingoGiftDlg::~FrBingoGiftDlg()
{
}

void FrBingoGiftDlg::SetGiftData(std::vector<unsigned long>* gifts)
{
	static sGift images[] = { sGift(0x1a0000cb, "bingo_item_01"),
		sGift(0x1a000035, "bingo_item_02"), sGift(0x18000010, "bingo_item_03"),
		sGift(0x18000011, "bingo_item_04"), sGift(0x18000012, "bingo_item_05"),
		sGift(0x10000015, "bingo_item_06"),
		sGift(0x24410006, "bingo_item_07") };
	std::map<unsigned long, const char*> imageMap;
	for (int i = 0; i < 7; ++i)
		imageMap[images[i].typeId] = images[i].image;
	m_giftList.assign(gifts->begin(), gifts->end());
	int count = m_giftList.size();
	for (int i = 0; i < count; ++i)
		m_pGiftImage[i] = g_pFresh->RegisterBitmap(imageMap[m_giftList[i]]);
}

void FrBingoGiftDlg::OnInitGiftArea(int param)
{
	m_pGiftArea = DYNAMIC_CAST(FrArea, (FrWnd*)param);
}

void FrBingoGiftDlg::OnOwnerDrawGiftArea(int param)
{
	FrGraphicInterface* gdi = g_pFresh->GetManager()->GetGDI();
	if (gdi)
	{
		const WRect& rect = m_pGiftArea->GetRect();
		float offset = 0;
		int count = m_giftList.size();
		for (int i = 0; i < count; ++i)
		{
			float x = offset + rect.x + m_offsetX[count - 1];
			float y = rect.y;
			float width = (float)m_pGiftImage[i]->Width();
			float height = (float)m_pGiftImage[i]->Height();
			gdi->DrawTexture(m_pGiftImage[i], WRect(x, y, width, height),
				0xffffffff, 0);
			offset += 63;
		}
	}
}
