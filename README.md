# Ada - Helper classes and event framework
Arduino with an OO twist... oh and events, everybody likes events

    #include <Ada.h>

    // Declare an Input and get events from it
    Input button(8);
    
    // Setup a periodic timer
    Timer myTimer(500, true);
    
    void onLow(IEventHandler* source) {
      Serial.println("Button press");
    }
    
    void onTimeout(IEventHandler* source) {
      Serial.println("Timeout event");
    }
    
    void setup() {
      Serial.begin(9600);
      
      button.onlow(&onLow);
      myTimer.ontimeout(&onTimeout);
      
      myTimer.begin();
    }
    
    BEGIN_GLOBAL_EVENT_HANDLERS()
      REGISTER_HANDLER(button)
      REGISTER_HANDLER(myTimer)
    END_EVENT_HANDLERS()
    
    EVENT_LOOP()
  
