#ifndef _ui__h
#define _ui__h

#include <Arduino.h>
#include "events.h"

/********************************************************************
 * One-shot or periodic timer class.
 *******************************************************************/
class Timer : public IEventHandler
{
DECLARE_EVENT(timeout)

public:
	Timer(uint32_t delay, bool periodic=false);

	/**
	 * Begin timer (if the timer is already running will reset it without raising an event)
	 */
	void begin();
	
	/**
	 * Begin a timer and reset the delay.
	 */
	void begin(uint32_t delay);

	/**
	 * Cancel the timer.
	 */
	void cancel();

	/**
	 * Time to the timer expires.
	 */
	uint32_t ttl();

	/**
	 * Elapsed time.
	 */
	uint32_t elapsed();

	/**
	 * Is currently active
	 */
	inline bool isActive() { 
		return m_active;
	}

	virtual void handleEvents();

private:
	uint32_t m_delay;
	bool m_periodic;

	uint32_t m_expires;
	bool m_active;
};


/********************************************************************
 * Pin
 *******************************************************************/
class Pin
{
public:
	Pin(int pin, int mode)
	: m_pin(pin) { pinMode(pin, mode); }

	inline int read() { return digitalRead(m_pin);	}
	inline void write(int state) { digitalWrite(m_pin, state); }
	inline void toggle() { write(!read()); }

protected:
	int m_pin;
};


/********************************************************************
 * Input
 *******************************************************************/
class Input : public Pin, public IEventHandler
{
DECLARE_EVENT(high)
DECLARE_EVENT(low)

public:
	Input(int pin, int mode=INPUT_PULLUP);

	virtual void handleEvents();

protected:
	int m_lastState;
};

#endif // _ui__h
