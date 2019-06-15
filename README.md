# Smart-Light
IOT (Internet of things) based project to Light a 100W bulb by giving instructions from the phone

Hardware Required:
The hardware requirements for the project are as follows:
1. 100W bulb
2. Arduino Uno
3. Node MCU
4. Wires
5. Jumper wires
6. Relay
7. Bread board
8. Power supply for the bulb (220V)
9. Power supply for the Arduino board
10. Laptop (preinstalled with Arduino ide) to burn the code
onto the board
11. Mobile phone (preinstalled with My MQTT app) to give
on/off instructions

Procedure:
1.	Make connections as per the circuit diagram between Arduino, node mcu, relay and the bulb.
2.	The relay has 3 terminals (NC, N and NO) which connect to the bulb and on the other side there are 3 pins (Gnd, Vcc, Signal). Inside the relay is a 120-240V switch that’s connected to an electromagnet. When the relay receives a HIGH signal at the signal pin, the electromagnet becomes charged and moves the contacts of the switch open or closed.   
3.	Type the program on the ide., compile it and upload it onto the Arduino board.
4.	Go to the MQTT app on your phone.
5.	Open settings and type (iot.eclipse.org”) as the broker URL.
6.	Now click on connect button, wait until you are connected.
7.	Click the publish button, enter the topic (inTopic007), type ‘1’ as the message and click on Publish button. Thus, the bulb turns “on”
8.	Click the publish button, enter the topic (inTopic007), type ‘0’ as the message and click on Publish button. Thus, the bulb turns “off”
