# WiFi controlled LED bulb using ESP8266
Switch on & off any LED bulb through WiFi Access Point (a hotspot network).
   

## How to get started
Simply load the WiFi_LED.ino file in Arduino IDE.  
Make sure you have the required libraries and driver for ESP8266 installed.  
Flash the file. 
   
The WiFi hotspot get turned on automatically with the following details :  
   
> SSID : Smart LED  
Password : A@*#0000  

You can change both of these in the .ino file.

Now connect any device(laptop or smartphone) to the hotspot network using the above credentials. Open up a browser and go to *192.168.4.1* 
(This is the ip address of the ESP8266, it might change. To be sure, check the network details on your device to find the ip.)

   

You will be shown an interface like this :   
    
<img src="https://github.com/kushanksriraj/wifi-led/blob/master/browser-ui.png" alt="Browser-UI" width="240" height="420"/>   

The button is self-explanatory. It changes the state from ON to OFF when clicked.

## Working 
When the button is turned on, a POST request is sent to the server in ESP8266. This sends the command to the pin 15 which then turns on the relay.   
This on or off state of the pin is stored in the EEPROM of the board. Storing the state of the pin lets the board stay turned on or off even after power is cut.   
The board uses a simple AC relay which is connected to the pin 15 (D8) of the board. 

## Further development
This setup can be used to control any electrical appliance such as a fan, computer, etc. Moreover, many other controls can be developed such as speed control for fan. 
