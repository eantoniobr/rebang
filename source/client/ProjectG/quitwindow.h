#pragma once

// TODO: incomplete
class CQuitWindow : public WSingleton<CQuitWindow>
{
public:
	void CreateOptionWindow();
	bool IsActive();
};
