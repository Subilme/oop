#include "CCar.h"

const std::map<int, std::pair<int, int>> CCar::m_gearSpeedRanges = {
	{-1, { -20, 0 }},
	{ 0, {0, 150} },
	{ 1, {0, 30} },
	{ 2, {20, 50} },
	{ 3, {30, 60} },
	{ 4, {40, 90} },
	{ 5, {50, 150} }
};

bool CCar::TurnOnEngine()
{
	m_isTurnedOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_isTurnedOn = false;
	}
	return !m_isTurnedOn;
}

bool CCar::SetGear(const int gear)
{
	if (!m_isTurnedOn)
	{
		return false;
	}
	if ((gear < -1) || (gear > 5))
	{
		return false;
	}
	switch (gear)
	{
	case -1:
		if (m_speed != 0)
		{
			if (m_gear != gear)
			{
				return false;
			}

			return true;
		}
		break;
	case 0:
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		// TODO: Вынести в переменную результат find
		if ((m_speed < m_gearSpeedRanges.find(gear)->second.first) || 
			(m_speed > m_gearSpeedRanges.find(gear)->second.second))
		{
			return false;
		}
		break;
	default:
		return false;
	}

	m_gear = gear;
	return true;
}

bool CCar::SetSpeed(const int speed)
{
	if (!IsTurnedOn())
	{
		return false;
	}
	if ((speed < 0) || (speed > 150))
	{
		return false;
	}
	switch (m_gear)
	{
	case -1:
		if (-speed < m_gearSpeedRanges.find(-1)->second.first)
		{
			return false;
		}
		m_speed = -speed;
		UpdateDirection();
		return true;
	case 0:
		if (speed > abs(m_speed))
		{
			return false;
		}
		m_speed = (speed > 0) ? speed : -speed;
		UpdateDirection();
		return true;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		// TODO: Вынести в переменную результат find
		if ((speed < m_gearSpeedRanges.find(m_gear)->second.first) || 
			(speed > m_gearSpeedRanges.find(m_gear)->second.second))
		{
			return false;
		}

		m_speed = speed;
		UpdateDirection();
		return true;
	default:
		return false;
	}
}

void CCar::UpdateDirection()
{
	if (m_speed > 0)
	{
		m_direction = CCar::Direction::Forward;
	}
	else if (m_speed < 0)
	{
		m_direction = CCar::Direction::Backward;
	}
	else
	{
		m_direction = CCar::Direction::None;
	}
}

bool CCar::IsTurnedOn() const
{
	return m_isTurnedOn;
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}

int CCar::GetSpeed() const
{
	return abs(m_speed);
}

int CCar::GetGear() const
{
	return m_gear;
}
