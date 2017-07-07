The following are the bugs in the version 1 of Plug and Play board and uC based board.

Bugs:

Plug and Play Board:
1. 7805 Placement: The 7805 was not positioned at the end. Becuase of
this there was no sucient space to add the heat sink.
2. Port Expander Naming: The names of port expander are interchanged
in the Daughter board. The names of port expander printed on the
Daughter board are interchanged. Port B is named as port A and vice
versa.
3. Switch Connection : The switch is used to connect the Ground of
Launchpad and Daughter board for programming. The connections of
this switch is incorrect.
4. The bot has to powered rst and then micro USB should be connected
to program the bot. This is because of the absence of switch explained
in the previous step
5. LCD starts displaying data on alternate press of reset button. It gets
initialised everytime but fails to display data.
6. Buzzer and red LED of TIVA launchad are on the same pin. Certain
motors pins and red and green LED pins also overlap.

uC based Board:
1. RX and TX LEDs: LEDs attached to RX and TX pins of serial com-
munication are not woring. The bot is able to communicate with the
laptop serial but the LEDs are not glowing.
2. Crystal Placement: The Crystal is placed far from the microcontroller.
Because of this the inductance of wires may eect the crysal frequency.
3. Heat Sink: The heat sink provided for LM1117 is not sucient.
4. Naming : The names of port expamders, servo headers, programming
headers are not printer on the board. The names of SCL and SDA pins
on the board is interchanged i.e SCL pin is printed as SDA and vice
versa.
5. The bot does not get programmed everytime because of connection
problems.(Resolderig the pins of uC might help solve the problem)
6. LCD starts displaying data on alternate press of reset button. It gets
initialised everytime but fails to display data.