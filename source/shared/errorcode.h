#pragma once

namespace Cm
{
	enum eErrorCode
	{
		ERROR_CODE_SUCCESS,
	};
}

inline bool IS_SUCCESSFUL(Cm::eErrorCode code)
{
	return code == Cm::ERROR_CODE_SUCCESS ? true : false;
}
