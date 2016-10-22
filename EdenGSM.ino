#include <GSM.h>
//#include "LowPower.h"
#include <avr/sleep.h>
// PIN Number
#define PINNUMBER ""
// APN data
#define GPRS_APN       "apn" // replace your GPRS APN
#define GPRS_LOGIN     ""    // replace with your GPRS login
#define GPRS_PASSWORD  "" // replace with your GPRS password
// initialize the library instance
GSMClient client;
GPRS gprs;
GSM_SMS sms;
GSM gsmAccess(true);
// URL, path & port (for example: arduino.cc)
const unsigned long __TIMEOUT__ = 10*1000;
String URL = "Your Server IP Here"; //insert your server's IP address here
int port = 80; // port 80 is the default for HTTP
int ledPin = 11;

//Well Specific Variables
String wellId = "1"; //adjust this number for each well you install the device on also update this on your server
String password = "Password123"; //insert your password that you have set on the server

// FLOW DATA VARIABLES
volatile int NbTopsFan; //measuring the rising edges of the signal
float Calc;                               
int hallsensor = 2;    //The pin location of the sensor (typically the yellow wire)
float d=0;             //my summation variable
int totalVolume = 0;
int waitCounter = 0;

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A0, LOW);
  digitalWrite(A3, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(100);
  digitalWrite(7, LOW);
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  // ++++++++++++++++++++
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  attachInterrupt(0, rpm, RISING); //and the interrupt is attached
  // ++++++++++++++++++++
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Starting Arduino web client.");
  // connection state
  boolean notConnected = true;
  // After starting the modem with GSM.begin()
  // attach the shield to the GPRS network with the APN, login and password
  
  while (notConnected)
  {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY){
      Serial.println("gsmAccess good");
      if(gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY){
        notConnected = false;
        Serial.println("Connected");
        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      }else{
        Serial.println("Gprs access bad");
      }
    }else{
      Serial.println("Not connected");
      delay(1000);
    }
  }

  digitalWrite(ledPin,HIGH);
  // if you get a connection, report back via serial:
  
}

void loop()
{
  //sleep_disable();
  NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
  sei();      //Enables interrupts
  delay (1000);   //Wait 1 second
  //cli();      //Disable interrupts
  Calc = (NbTopsFan/(60/4.5)); //(Pulse frequency x 60) / 4.5Q, = flow rate in L/hour 
  int transmit = 100 * Calc;
  Serial.println("Buffer filled. Sending:");
  long t = millis();
 // totalVolume = transmit + totalVolume;
  if(transmit == 0){
    if(waitCounter >= 15){
      Serial.print("Posting XML:");
      String totalVolumeString = String(totalVolume);
      String PostString = "<Event><WellId>" + wellId + "</WellId><Password>abc123</Password><FlowVolume>"+ totalVolumeString +"</FlowVolume></Event>";
      Serial.print(totalVolume);
      Serial.print("\n\n");
      //Comment out the line below to disable http post
      send_data(PostString);
      
      //Serial.print("Enter a mobile number: ");
      //char remoteNumber[20] = "+18022814561";  // telephone number to send sms: +18022814561
      //Serial.print("Now, enter SMS content: ");
      //char txtMsg[200] = "totalVolumeString";//not needed
      //Serial.println("SENDING");
      //Serial.println();
      //Serial.println("Message:");
      //Serial.println(txtMsg);

       // send the message
       //sms.beginSMS(remoteNumber);
       //sms.print("wellid:" + wellId + ";volume:"+ totalVolumeString +";password:" + password);
       //sms.endSMS(); 
       Serial.println("\nCOMPLETE!\n");
       digitalWrite(ledPin, LOW);
       delay(500);
       digitalWrite(ledPin, HIGH);
       delay(500);
       digitalWrite(ledPin, LOW);
       delay(500);
       digitalWrite(ledPin, HIGH);
       delay(500); 
       digitalWrite(ledPin, LOW);
       delay(500);
       digitalWrite(ledPin, HIGH);   
           
       totalVolume = 0;   
       waitCounter = 0;
    }
    else{
      if(totalVolume > 0){
        waitCounter++;
      }
      Serial.print("Waiting: ");
      Serial.print(waitCounter);
    }

  }
  else{
    waitCounter = 0;
    totalVolume = transmit + totalVolume;
  }
  Serial.print("\n\n");
  Serial.print("Flow reading: ");
  Serial.print(transmit);
  Serial.print("   Total Volume is: ");
  Serial.print(totalVolume);
  Serial.print("  ");
  Serial.print("Time was: ");
  Serial.print(millis() - t);
  Serial.print("\n\n");
}

void rpm ()             //This is the function that the interupt calls 
{ 
  NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
}

void send_data(String PostData){
  Serial.println("connecting...");
  boolean notConnectedtoserver = true;
  while (notConnectedtoserver = true) 
  {
    
    if (client.connect("52.25.30.66", port))
    {
      client.beginWrite();
      Serial.println("connected");
      // Make a HTTP request:
      client.print("POST /TestPost");
      client.print(" HTTP/1.1\n");
      client.print("Host: ");
      client.println("52.25.30.66");
      client.println("Connection: close");
      client.print("Content-Length: ");
      client.println(PostData.length());
      client.println();
      client.println(PostData);   
      Serial.println("disconnecting.");
      client.stop();
      digitalWrite(ledPin, LOW);
      delay(500);
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
      digitalWrite(ledPin, HIGH);
      delay(500); 
      digitalWrite(ledPin, LOW);
      delay(500);
      digitalWrite(ledPin, HIGH);
      notConnectedtoserver = false;    
    }
    else
    {
      // if you didn't get a connection to the server:
      Serial.println("connection failed... trying again\n");
      delay(1000);
    }
  }
}
