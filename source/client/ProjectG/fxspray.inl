inline WVector CFxSpray::GetBgPos(const CFxParticle* particle)
{
	return m_param.bStrongBond ? GetBgPos() : particle->bgPos;
}

inline WMatrix CFxSpray::GetBgRot(const CFxParticle* particle)
{
	return m_param.bStrongBond ? m_rot : particle->bgRot;
}

inline void CFxSpray::SetActive(bool bActive)
{
	m_bActive = bActive;
}

inline WVector& CFxSpray::Pos()
{
	return m_pos;
}

inline WVector& CFxSpray::Vel()
{
	return m_vel;
}

inline WVector& CFxSpray::InitialMinVel()
{
	return m_param.initVelocity.min;
}

inline WVector& CFxSpray::InitialMaxVel()
{
	return m_param.initVelocity.max;
}

inline void CFxSpray::GetBoneMatrix(WMatrix* mat)
{
	WMatrix rot;

	mat->Reset();

	for (int i = 0; i < 4; i++)
	{
		if (m_attachMat[i] == NULL)
			break;

		m_attachMat[i]->GetRotMatrix(&rot);
		*mat = *mat * rot;
	}
}
