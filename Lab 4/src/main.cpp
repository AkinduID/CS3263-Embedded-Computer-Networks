#include <Arduino.h>

void delay_ms(int ms){
    TIFR0 |= (1 << OCF0A);
    int count = 0;
    while (count < ms){
        TCNT0 = 0;
        TCCR0A = 0;           // Init Timer0
        TCCR0B = 0;           // Init Timer0
        TCCR0B |= 0b00000011;  // Prescalar = 64
        OCR0A = 250;
        int temp = TIFR0;
        temp = (TIFR0 & 0b00000010);
        while(temp != 0b00000010){
            temp = (TIFR0 & 0b00000010);
        }
        TIFR0 |= 1 << OCF0A;
        count++;
    }
}

void delay_us(int us){
    TIFR0 |= (1 << OCF0A);
    int count = 0;
    while (count < us){
        TCNT0 = 0;
        TCCR0A = 0;           // Init Timer0
        TCCR0B = 0;           // Init Timer0
        TCCR0B |= 0b00000010;  // Prescalar = 8
        OCR0A = 2;
        int temp = TIFR0;
        temp = (TIFR0 & 0b00000010);
        while(temp == 0b00000010){
            temp = (TIFR0 & 0b00000010);
        }
        TIFR0 |= 1 << OCF0A;
        count++;
    }
}

void waiting(){
  while (!(UCSR0A & (1 << UDRE0)))
    ;
}

void counter(){
  short i = 1;
  uint16_t value = 0;
  while (true)
  {
    delay_ms(1);
    value++; // increment value by 1 every 20ms
    if (i == 5) // print value every 100ms
    {
      i = 1; // reset i
      uint16_t temp = value;
      char number[3] = {0, 0, 0};
      for (int j = 0; j < 3; j++){ // convert value to string
        number[2 - j] = char(temp % 10) + '0';
        temp = temp / 10;
      }
      for (int j = 0; j < 3; j++){ // print number
        waiting();
        UDR0 = number[j];
      }
      waiting(); // print newline
      UDR0 = '\n';
    }
    else{
      i++;
    }
  }
}

void setup(){
    UBRR0H = 0;   // set baud rate to 9600
    UBRR0L = 103; // set baud rate to 9600
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // set frame format: 8data, 1stop bit
    counter(); // call counter function
}

void loop(){
    // Serial.println("Hello, world!");
    // delay_us(1000000);
}
