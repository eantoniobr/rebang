#pragma once
#include "gatewaydoc.h"
#include "../../shared/globalnetworkdefine.h"
namespace _gateway
{
	struct sTradeBuyBase
	{
		sTradeItem item;
		sItemInfo itemInfo;
		unsigned char countingType;
	};
	struct sTradeSellParam
	{
		std::vector<sTradeItem> items;
		int result;
		__int64 pang;
	};
	struct sTradeBuyParam
	{
		std::vector<sTradeBuyBase> items;
		int result;
		__int64 pang;
	};
	struct sTradeMinusParam
	{
		std::vector<sTradeItem> items;
		std::string name;
		int state;
		unsigned long uid;
	};

}
