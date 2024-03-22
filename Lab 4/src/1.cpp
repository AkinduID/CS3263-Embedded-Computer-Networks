#include <Arduino.h>

void delay_ms(int ms){
    TIFR0 |= (1 << OCF0A);  // Clear Timer0 compare match flag
    int count = 0;
    while (count < ms){
        TCNT0 = 0;            // Reset Timer0 counter
        TCCR0A = 0;           // Initialize Timer0 control register A
        TCCR0B = 0;           // Initialize Timer0 control register B
        TCCR0B |= 0b00000011; // Set Timer0 prescaler to 64
        OCR0A = 250;          // Set Timer0 output compare register A value
        int temp = TIFR0;
        temp = (TIFR0 & 0b00000010); // Check Timer0 compare match flag
        while(temp != 0b00000010){   // Wait until Timer0 compare match flag is set
            temp = (TIFR0 & 0b00000010);
        }
        TIFR0 |= 1 << OCF0A;  // Clear Timer0 compare match flag
        count++;
    }
}

void delay_us(int us){
    TIFR0 |= (1 << OCF0A);  // Clear Timer0 compare match flag
    int count = 0;
    while (count < us){
        TCNT0 = 0;            // Reset Timer0 counter
        TCCR0A = 0;           // Initialize Timer0 control register A
        TCCR0B = 0;           // Initialize Timer0 control register B
        TCCR0B |= 0b00000010; // Set Timer0 prescaler to 8
        OCR0A = 2;            // Set Timer0 output compare register A value
        int temp = TIFR0;
        temp = (TIFR0 & 0b00000010); // Check Timer0 compare match flag
        while(temp == 0b00000010){   // Wait until Timer0 compare match flag is set
            temp = (TIFR0 & 0b00000010);
        }
        TIFR0 |= 1 << OCF0A;  // Clear Timer0 compare match flag
        count++;
    }
}

void setup(){
    Serial.begin(9600); // Initialize serial communication
}

void loop(){
    Serial.println("Hello, world!"); // Print "Hello, world!" to serial monitor
    delay_us(1000000);  // Delay for 1 second
}
