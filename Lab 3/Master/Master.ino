#include <SPI.h>

void setup() {
  // Set the slaveSelectPin as an output:
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  // Initialize SPI:
  SPI.begin();
  Serial.begin(9600);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  SPI.beginTransaction(SPISettings(9600, MSBFIRST, SPI_MODE0));
}
int i = 0;

void loop() {
  if(i >= 26){
    i = 0;
  }
  Serial.println("Sending Started !");
  // Enable Slave Select
  if (i % 2 == 0){
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
  } else{
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
  }
  
  // Send test data to the slave:
  SPI.transfer('A'+ i);
  // Disable Slave Select
  
  delay(1000);
  if (i % 2 == 0){
    digitalWrite(10, HIGH);
    Serial.println("Message sent to Slave A");
  } else{
    digitalWrite(9, HIGH);
    Serial.println("Message sent to Slave B");
  }
  i++;
   // Delay for 1 second
}
