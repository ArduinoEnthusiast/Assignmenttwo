// This is a fairly simple Potentiometer based solution to the challenge. The most 
// challenging part of coding it was finding a way to stop the value from defulting 
// to zero every few seconds.

int potPin= A0;  //Declare potPin to be analog pin A0
int readValue;  // Use this variable to read Potentiometer
int writeValue; // Use this variable for writing to LED

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "388577a78f9f46b8921741a760264405";

char ssid[] = "network";
char pass[] = "password";

BlynkTimer timer;

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(A0, writeValue = (7./1023.));
}

 
void setup() {
  pinMode(potPin, INPUT);  //set potPin to be an input
  
  Serial.begin(115200);      // turn on Serial Port

 Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
//  Blynk.virtualWrite(V1, val);
}
 
void loop() {
  
 readValue = analogRead(potPin);  //Read the voltage on the Potentiometer
 writeValue = (7./1023.) * readValue; //Calculate Write Value for LED

Blynk.run();
 // timer.run(); // Initiates BlynkTimer
 
 Serial.println(writeValue);

 delay(500);

// For some reason my code prefered values written as above 1 and below 3 (2) then as 2
// I'm not quite sure why but if I just wrote values as they were then they would defult
// to 0 after a couple of second, I was considering adding this into the code and having
// 0 as No Wind but then if the wind was blowing really hard in one direction then the
// vane would read no wind and be fairly useless
 
 if (writeValue == 0) {
Serial.println ("North West");
}
else if (writeValue >= 0 && writeValue < 2){
  Serial.println("North");
}
else if (writeValue >= 1 && writeValue < 3){
  Serial.println("North East");
}
else if (writeValue >= 2 && writeValue < 4){
  Serial.println("East");
}
else if (writeValue >= 3 && writeValue < 5){
  Serial.println("South East");
}
else if (writeValue >= 4 && writeValue < 6){
  Serial.println("South");
}
else if (writeValue >= 5 && writeValue < 7){
  Serial.println("South West");
}
else if (writeValue >= 6 && writeValue < 8){
  Serial.println("West");
}

}
