// Christine Onita ECE303 Lab/Project 4 Winter 2021

int led = 5; //timer 3
int photocell_array[10]; // will use this to get ten values then find average
int ledd_array[10]; // will use this to get ten values then find average
float sumph=0;
float suml=0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); // baud rate
  pinMode(led, OUTPUT); //initialize pin 5 as output  
  
  TCCR3A=0b10000010; // Initializes all bits in TCCR3A to zero
  TCCR3B=0b00010001; // Set prescalar of 1
  TCNT3=0; // Initializes counter TCNT3 to 0
  ICR3 = 8000;
  OCR3A = 0; //this woul make the duty cycle start from 0%
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  while (OCR3A <= ICR3) {
    delay(3000); // time delay (3 seconds) to get proper transient readings
    
    for (int i = 0; i < 10; i++ ){ // from i=0 to i=9, the voltage is measured (that's ten values for each case)
      photocell_array[i] = analogRead(A0); // records the photocell voltage on a scale of 0 to 1023
      ledd_array[i] = analogRead(led); // records/reads the  voltage on a scale of 0 to 1023
      
    }   
    
    //This is for the LED Circuit Resistor Voltage
    for (int i=0; i<10; i++)
      long suml = 0L ;  // sum will be larger than an item, long for safety.
      for (int i = 0 ; i < 10 ; i++)
        suml =suml + ledd_array[i] ;
        Serial.print((suml / 10)*5/1023);
    Serial.println();

    //This is for the Photocell Circuit Resistor Voltage
    for (int i=0; i<10; i++) 
      long sumph = 0L ;  // sum will be larger than an item, long for safety.
      for (int i = 0 ; i < 10 ; i++)
        sumph =sumph + photocell_array[i] ;
        Serial.print((sumph / 10)*5/1023);
    Serial.println();
    
    OCR3A += 80; // this would make sure the duty cycle is increased in incremements of 1%
    suml = 0;
    sumph = 0;
  }
}
