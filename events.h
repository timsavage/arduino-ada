/**
 * Macros to define event handling.
 *
 * Usage:
 * 
 *   BEGIN_EVENT_HANDLERS()
 *     REGISTER_HANDLER(myButton)
 *     REGISTER_HANDLER(myTimer)
 *   END_EVENT_HANDLERS()
 *
 * Any object that implements the IEventHandler can be used with REGISTER_HANDLER.
 *
 * And for your loop method use:
 *
 *   void loop() { 
 *     HANDLE_EVENTS() 
 *   }
 */
#ifndef _events__h
#define _events__h

/**
 * Defines a interface for the event loop to call to provide events.
 */
class IEventHandler
{
public:
	/**
	 * Method that is called every cycle of the event loop.
	 */
	virtual void handleEvents() = 0;
};

// Definition of an event callback
typedef void eventCallback(IEventHandler*);

// Declare an event on a class, defines callback member variable and 
// a binding function.
#define DECLARE_EVENT(NAME) \
	public: \
		void on##NAME(eventCallback* callback) { m_on##NAME = callback; } \
	protected: \
		eventCallback* m_on##NAME = 0;

// Raise a defined event, checks if a callback has been defined.
#define RAISE_EVENT(NAME) if (m_on##NAME) m_on##NAME(this);

// Start event handler block
#define BEGIN_EVENT_HANDLERS() IEventHandler* __ui_eventHandlers[] = {

 // Register a IEventHandler object
#define REGISTER_HANDLER(x)	&x,

// End event handler block.
#define END_EVENT_HANDLERS() }; \
	const size_t __ui_eventHandlerCount = sizeof(__ui_eventHandlers) / sizeof(IEventHandler*); \
	size_t __ui_idx;

// Execute each event handler.
#define HANDLE_EVENTS() \
	for (__ui_idx = 0; __ui_idx < __ui_eventHandlerCount; __ui_idx++) { \
		__ui_eventHandlers[__ui_idx]->handleEvents(); \
	}

// Short cut method to simply define a loop method that just calls executes event handlers.
#define EVENT_LOOP() void loop() { HANDLE_EVENTS() }

// Helper that provides access to the event handler array
#define EVENT_HANDLERS __ui_eventHandlers

// Helper that provides the length of the event handler array
#define EVENT_HANDLER_COUNT __ui_eventHandlerCount

#endif //_events__h
