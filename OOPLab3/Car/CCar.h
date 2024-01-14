#pragma once
#include <map>

class CCar
{
public:
	enum class Direction
	{
		Forward,
		Backward,
		None
	};
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(const int gear);
	bool SetSpeed(const int speed);

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

private:
	void UpdateDirection();

	static const std::map<int, std::pair<int, int>> m_gearSpeedRanges;
	bool m_isTurnedOn = false;
	Direction m_direction = Direction::None;
	int m_speed = 0;
	int m_gear = 0;
};
