########################################
Ada - Helper classes and event framework
########################################

Arduino with an OO twist... oh and events, everybody likes events

.. code:: c

  #include <Ada.h>
  
  // Button input on pin 8
  Input button(8);
  
  // Handler to handle button being pressed
  void button_onlow(IEventHandler* source) {
    Serial.println("Button press");
  }
  
  // A periodic timer
  Timer myTimer(500, true);
  
  // Handler to handle timeout event
  void myTimer_ontimeout(IEventHandler* source) {
    Serial.println("Timeout event");
  }
  
  void setup() {
    Serial.begin(9600);

    // Bind events
    button.onlow(&onLow);
    myTimer.ontimeout(&onTimeout);

    myTimer.begin();
  }
  
  // Global event handlers
  GLOBAL_EVENT_HANDLERS()
    REGISTER_HANDLER(button)
    REGISTER_HANDLER(myTimer)
  END_EVENT_HANDLERS()

  // Declare event loop (this generates a Loop function)
  EVENT_LOOP()
