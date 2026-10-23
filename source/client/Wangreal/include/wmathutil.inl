#pragma once

inline float GetBaseAngle(float angle)
{
	if (Abs(angle) > g_2_PI)
		angle -= floorf(angle / g_2_PI) * g_2_PI;
	if (angle > g_PI)
		return angle - g_2_PI;
	if (angle < -g_PI)
		return angle + g_2_PI;
	return angle;
}
