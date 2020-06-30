#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 9
#define TEMPERATURE_PRECISION 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress CPU, GPU; 
// sensors.getAddress(deviceAddress, index)
//DeviceAddress CPU = {0x28, 0xAA, 0x10, 0xA4, 0x55, 0x14, 0x01, 0x91}
//DeviceAddress GPU = {0x28, 0xAA, 0x32, 0x7A, 0x55, 0x14, 0x01, 0xFE}
 
//--------------------------------------------------------------------------------------------------------------//

int pwmPin     = 3; // digital PWM pin 3
int pwmVal     = 1; // The PWM Value
unsigned long time;
unsigned int rpm;
String stringRPM;
//--------------------------------------------------------------------------------------------------------------//
void setup()
{
   // generate 25kHz PWM pulse rate on Pin 3
   pinMode(pwmPin, OUTPUT);   // OCR2B sets duty cycle
   // Set up Fast PWM on Pin 3
   TCCR2A = 0x23;     // COM2B1, WGM21, WGM20 
   // Set prescaler  
   TCCR2B = 0x0A;   // WGM21, Prescaler = /8
   // Set TOP and initialize duty cycle to zero(0)
   OCR2A = 79;    // TOP DO NOT CHANGE, SETS PWM PULSE RATE
   OCR2B = 0;    // duty cycle for Pin 3 (0-79) generates 1 500nS pulse even when 0 :
   digitalWrite(2, HIGH);   // Starts reading
   Serial.begin(9600);
   //-------------------------------------------------------------------------------------------------------------//
 

  delay (20);
  sensors.begin();  // Start up the Dallas library
  delay (20);
  Serial.print("Wha Gwan my G, Booting up just now King");
  delay(5000);
  Serial.println();
   // locate devices on the bus
  Serial.print("Checking thermals...");
  delay(500);
  Serial.print("Found ");
  delay(100);
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
    
   if (!sensors.getAddress(CPU, 0)) Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(GPU, 1)) Serial.println("Unable to find address for Device 1");
// Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to CPU
  //if (!oneWire.search(CPU)) Serial.println("Unable to find address for CPU");
  // assigns the second address found to GPU
  //if (!oneWire.search(GPU)) Serial.println("Unable to find address for GPU");

  
  // set the resolution to 9 bit per device
  sensors.setResolution(CPU, TEMPERATURE_PRECISION);
  sensors.setResolution(GPU, TEMPERATURE_PRECISION);

    Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(CPU), DEC);
  Serial.println();

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(GPU), DEC);
  Serial.println();
  }

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}

void loop()
{
 unsigned int x;
 // ramp up fan speed by increasing duty cycle every 200mS, takes 16 seconds
 //for(x = 0; x < 80; x++) {
 //  OCR2B = x;    // set duty cycle
 //  getRPMS();
 //  Serial.println(x);
 //  delay(200);
 //}

 
 
 while (Serial.available() == 0);
 int val = Serial.parseInt();
 if (val > 0 && val < 80) {
     OCR2B = val;
 }}

char getRPMS() {
 time = pulseIn(2, HIGH);
 rpm = (1000000 * 60) / (time * 4);
 stringRPM = String(rpm);
 if (stringRPM.length() < 5) {
   Serial.println(rpm, DEC);
 }
 delay (6000);
}
