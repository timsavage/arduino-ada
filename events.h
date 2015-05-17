/**
 * Macros to define event handling.
 *
 * Usage:
 * 
 *   BEGIN_GLOBAL_EVENT_HANDLERS()
 *     REGISTER_HANDLER(myButton)
 *     REGISTER_HANDLER(myTimer)
 *   END_EVENT_HANDLERS()
 *
 * Any object that implements the IEventHandler can be used with REGISTER_HANDLER.
 *
 * And for your loop method use:
 *
 *   void loop() { 
 *     HANDLE_GLOBAL_EVENTS() 
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
#define BEGIN_EVENT_HANDLERS(NAME) IEventHandler* __##NAME_eventHandlers[] = {

 // Register an IEventHandler object
#define REGISTER_HANDLER(x)	&x,

// End event handler block.
#define END_EVENT_HANDLERS() };

// Helper that provides the length of an event handler array
#define EVENT_HANDLER_COUNT(NAME) (sizeof(__##NAME_eventHandlers) / sizeof(IEventHandler*))

// Execute each event handler.
#define HANDLE_EVENTS(NAME) \
	size_t _idx; \
	for (_idx = 0; _idx < EVENT_HANDLER_COUNT(NAME); _idx++) { \
		__##NAME_eventHandlers[_idx]->handleEvents(); \
	}

// Short cut global even handlers
#define BEGIN_GLOBAL_EVENT_HANDLERS() BEGIN_EVENT_HANDLERS(global)

// Short cut method to simply define a loop method that just calls executes event handlers.
#define GLOBAL_EVENT_LOOP() void loop() { HANDLE_EVENTS(global) }

#endif //!_events__h
