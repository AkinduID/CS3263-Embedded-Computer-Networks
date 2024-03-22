#include <Arduino.h>

// Function to delay in milliseconds
void delay_ms(int ms){
    TIFR0 |= (1 << OCF0A);          // Clear Timer0 compare match flag
    int count = 0;
    while (count < ms){
        TCNT0 = 0;                   // Reset Timer0 counter
        TCCR0A = 0;                  // Initialize Timer0 control register A
        TCCR0B = 0;                  // Initialize Timer0 control register B
        TCCR0B |= 0b00000011;        // Set Timer0 prescaler to 64
        OCR0A = 250;                 // Set Timer0 output compare register A value
        int temp = TIFR0;
        temp = (TIFR0 & 0b00000010); // Check Timer0 compare match flag
        while(temp != 0b00000010){   // Wait until Timer0 compare match flag is set
            temp = (TIFR0 & 0b00000010);
        }
        TIFR0 |= 1 << OCF0A;         // Clear Timer0 compare match flag
        count++;
    }
}

// Function to wait for the UART transmit buffer to be empty
void waiting(){
  while (!(UCSR0A & (1 << UDRE0)))
    ;
}

// Function to increment a counter and print its value
void counter(){
  short i = 1;
  uint16_t value = 0;
  while (true){
    delay_ms(20);                   // Delay for 20ms
    value++;                        // Increment value by 1 every 20ms
    if (i == 5){                    // Print value every 100ms
      i = 1;                        // Reset i
      uint16_t temp = value;
      char number[3] = {0, 0, 0};
      for (int j = 0; j < 3; j++){ // Convert value to string
        number[2 - j] = char(temp % 10) + '0';
        temp = temp / 10;
      }
      for (int j = 0; j < 3; j++){ // Print number
        waiting();                  // Wait for transmit buffer to be empty
        UDR0 = number[j];
      }
      waiting();                    // Wait for transmit buffer to be empty
      UDR0 = '\n';                  // Print newline
    }
    else{
      i++;
    }
  }
}

void setup(){
    UBRR0H = 0;                     // Set baud rate to 9600
    UBRR0L = 103;                   // Set baud rate to 9600
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Set frame format: 8data, 1stop bit
    counter();                      // Call counter function
}

void loop(){
    // No operation in loop as the program operates in the counter function
}
