NodeMCU with ESP8266 as switch for raspberry pi server with geekworm x735

Circuit:
NodeMcu:
* D1 to transistor base
* GND to Collector
* GND to Raspberry GND

Raspberry geekworm x735

* GND (incoming from transistor collector)
* VCC to transistor emitter (red wire of the power button; on the board, pin 1--toward the ethernet port)

NodeMcu can handle 5V power supply (using a phone charger).


config.h needs to be created.
