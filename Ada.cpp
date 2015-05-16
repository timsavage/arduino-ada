#include "UI.h"


Timer::Timer(uint32_t delay, bool periodic)
: m_delay(delay), 
  m_periodic(periodic),
  m_active(false) {}

/**
 * Begin timer (if the timer is already running will reset it without raising an event)
 */
void Timer::begin() {
	if (m_delay) {
		m_expires = millis() + m_delay;
		m_active = true;
	} else {
		m_active = false;
	}
}

/**
 * Begin a timer and reset the delay.
 */
void Timer::begin(uint32_t delay) {
	m_delay = delay;
	this->begin();
}

/**
 * Cancel the timer.
 */
void Timer::cancel() {
	m_active = false;
}

/**
 * Time to the timer expires.
 */
uint32_t Timer::ttl() {
	uint32_t result = m_expires - millis();
	if (millis() - m_expires < 0x80000000UL) {
		return 0;
	} else {
		return result;
	}
}

/**
 * Elapsed time.
 */
uint32_t Timer::elapsed() {
	if (m_active) {
		return millis() - m_expires + m_delay;
	} else {
		return 0;
	}
}

void Timer::handleEvents() {
	if (m_active) {
		if (millis() - m_expires < 0x80000000UL) {
			m_active = false;
			if (m_periodic) this->begin();
			RAISE_EVENT(timeout);
		}
	}
}


Input::Input(int pin, int mode) 
: Pin(pin, mode) {
	m_lastState = read();
}

void Input::handleEvents() {
	int state = this->read();
	if (state != m_lastState) {
		m_lastState = state;
		if (state) {
			RAISE_EVENT(high);
		} else {
			RAISE_EVENT(low);
		}
	}
}
