#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const char *ssid = "Smart LED";
const char *password = "A@*#0000";

// Create a webserver object that listens for HTTP request on port 80
ESP8266WebServer server(80);

// function prototypes for HTTP handlers
void handleRoot();              
void handleLED();
void handleNotFound();

void setup(void){
  
///////EEPROM////////
   
  EEPROM.begin(512);
  digitalWrite(15,EEPROM.read(0));
  
///////EEPROM////////

  pinMode(15, OUTPUT);

//Remove the password parameter if you want the AP to be open
  WiFi.softAP(ssid, password);

// Call the 'handleRoot' function when a client requests URI "/"
  server.on("/", HTTP_GET, handleRoot);     

// Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.on("/LED", HTTP_POST, handleLED);  

// When a client requests an unknown URI, call function "handleNotFound"
  server.onNotFound(handleNotFound);        

// Actually start the server
  server.begin();             
}

void loop(void){
// Listen for HTTP requests from clients
  server.handleClient();                    
}

void handleRoot() {                         
 
// When URI / is requested, send a web page with a button to toggle the LED

 if(digitalRead(15))
 {
  server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><center><h1 style=\"font-size:75px; margin:340px 0 0 0;\">Smart Bulb</h1><button type=\"submit\" style=\"width:750px; height:300px; background-color:#1BE7FA; margin:400px 0 0 0; border-radius:20px;\"><h1 style=\"font-size:65px;\">Turn OFF</h1></button></center></form>");  
 }
else{
  server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><center><h1 style=\"font-size:75px; margin:340px 0 0 0;\">Smart Bulb</h1><button type=\"submit\" style=\"width:750px; height:300px; background-color:#1BE7FA; margin:400px 0 0 0; border-radius:20px;\"><h1 style=\"font-size:65px;\">Turn ON</h1></button></center></form>");  
 }
 
}

void handleLED() { //If a POST request is made to URI /LED

// Change the state of the LED
  digitalWrite(15,!digitalRead(15));      

// Add a header to respond with a new location for the browser to go to the home page again
  server.sendHeader("Location","/");        

// Send it back to the browser with an HTTP status 303 to redirect
  server.send(303);      

//////////EEPROM///////////
  
  if(EEPROM.read(0)!=digitalRead(15))
  {
     EEPROM.write(0,digitalRead(15));
  }
  EEPROM.commit();
  
//////////EEPROM///////////
}


void handleNotFound(){
// Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
  server.send(404, "text/html", "<h1 align=\"center\">You want chickens but only eggs are here!<\h1>"); 
}
