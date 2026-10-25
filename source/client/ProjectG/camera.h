#pragma once

#include "actor.h"

class CCamera : public IActor
{
public:
	DECLARE_OBJECT(CCamera)
	struct sSpotCam
	{
		WVector start;
		float startPitch;
		WVector end;
		float endPitch;
		WVector velocity;
		float pitch;
		float time;
		bool moving;
	};

protected:
	CCamera();

public:
	virtual ~CCamera() { }
	virtual void OnInit();
	virtual void OnProcess(float dt);

protected:
	float GetChangeRate();
	float GetHeightRate(float height);
	void LookAt(WVector& pos, WVector& target);
	void GetRotateAcc(float dt);
	void GetMoveAcc(float dt);
	void GetHorizonAcc(float dt);
	void YawFixedCamera(float dt);
	void PitchFixedCamera(float dt);
	void SetSpotCamera(bool apply);
	void ProcessMousePick(float dt);
	float GetCameraAngle();
	void ProcessToSpot(float dt);
	void Translate(float dt);
	void UpDown(float dt);
	void RotateEnvironment(float angle);
	void RotateForGallery(float angle);
	void Rotate(float dt);
	void FixedCamera(float dt);
	void ProcessInput(float dt);
	void ProcessForcedMove(float dt);

protected:
	virtual void HandleMsg(const MsgObject& msg);
	int m_rotateDirection;
	float m_totalRotation;
	float m_remainRotation;
	int m_moveDirection;
	int m_horizonDirection;
	float m_rotateAcc;
	float m_moveAcc;
	float m_horizonAcc;
	WVector m_pos;
	WVector m_target;
	float m_heightRate;
	float m_change;
	float m_ceiling;
	float m_lowest;
	bool m_translated;
	float m_initialHeightRate;
	float m_baseHeightRate;
	bool m_active;
	float m_inputDelay;
	bool m_camMode;
	float m_yaw;
	float m_pitch;
	float m_sendTime;
	bool m_angleChanged;
	float m_currentAngle;
	float m_targetAngle;
	sSpotCam m_spotCam;
};
