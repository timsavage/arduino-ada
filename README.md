# Ada - Helper classes and event framework
Arduino with an OO twist... oh and events, everybody likes events

    #include <Ada.h>

    // An input button
    Input button(8);
    
    // A periodic timer
    Timer myTimer(500, true);
    
    // Button event handler
    void onLow(IEventHandler* source) {
      Serial.println("Button press");
    }
    
    // Timer event handler
    void onTimeout(IEventHandler* source) {
      Serial.println("Timeout event");
    }
    
    void setup() {
      Serial.begin(9600);
      
      button.onlow(&onLow);
      myTimer.ontimeout(&onTimeout);
      
      myTimer.begin();
    }
    
    // Global event handlers
    GLOBAL_EVENT_HANDLERS()
      REGISTER_HANDLER(button)
      REGISTER_HANDLER(myTimer)
    END_EVENT_HANDLERS()
    
    EVENT_LOOP()
  
