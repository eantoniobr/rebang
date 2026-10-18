#pragma once

template <int N>
struct xtAlways
{
	static bool Get() { return false; }
};
