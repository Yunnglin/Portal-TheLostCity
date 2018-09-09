#include "TimeCounter.h"

bool TimeCounter::init() {
	return true;
}
void TimeCounter::updateTime(float dt) {
	if (m_sec == 0) {
		m_sec = 60;
		m_min--;
	}
	m_sec -= 1;
}
int TimeCounter::getSec() {

	return m_sec;
}

int TimeCounter::getMin() {

	return m_min;
}

void TimeCounter::start() {
	m_sec = 0;
	m_min = 2;
	this->schedule(schedule_selector(TimeCounter::updateTime) , 1.0f);
}