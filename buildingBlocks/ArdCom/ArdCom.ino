/**************
   This is the test code for communicating with the processing sketch running the visualizer. Two variables
   affect how this sketch recieves data: TIMEOUT and INPUT_SIZE. TIMEOUT controlls how long after calling readBytes()
   the code waits for input. During this time, whatever comes onto the serial buffer is added to the array returned by readBytes().
   INPUT_SIZE is the maxium length of the array returned by readBytes()---it must exceed or match the expected packet length in
   order to recieve all of the data. It should be as close as possible to the actual input size to be most efficeint.
   The Processing sketch expects a newline after every data packet sent. It will not read data otherwise.

   Author: Stuart Dilts

 **************/
//3 packets of 30 values each


#include <Adafruit_NeoPixel.h>

//Uses equivelent ASCII codes to share input
//Used to send commands and data to Processing sketch
//may need to find out how to tell this(Arduino) program to do things
#define EOT 10
#define ENQ 5
#define STP 4 //actually EOT char in ASCII
#define INPUT_SIZE 30
#define LED_NUM 150

//Timeout delay for reading from Serial:
#define TIMEOUT 100
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM, 6, NEO_RGB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  ensureContact();
  Serial.println("Going into loop");
  Serial.setTimeout(TIMEOUT);

  strip.begin();
  strip.setBrightness(64);
  strip.show();
}

void loop() {
  if (Serial.available() > 0) {

    //get three packets from the processing sketch:
    byte input[3][INPUT_SIZE + 1];
    byte size;
    for (byte r = 0; r < 3; r++) {
      // Get next command from Serial (add 1 for final 0)
      size = Serial.readBytes(input[r], INPUT_SIZE + 1);
      // Add the final 0 to end the C string
      input[r][size] = 0;
    }

    //insert code here
    byte n = 0;
    for (byte j = 0; j < 5; j++) {
      for (byte r = 0; r < 3; r++) {
        for (byte i = 0; i < size; i += 3) {
          strip.setPixelColor(n, input[r][i], input[r][i + 1], input[r][i + 2]);
          n++;
        }
      }
    }

    strip.show();
    //    //  insert code before here
    //    for (int i = 0; i < size - 1; i++) {
    //      Serial.print(input[i]);
    //      Serial.print(',');
    //    }
    //    Serial.println(input[size - 1]);

    //    for (byte i = 0; i < input[0]; i++) {
    //      digitalWrite(13, HIGH);
    //      delay(1000);
    //      digitalWrite(13, LOW);
    //      delay(500);
    //    }
    Serial.println(ENQ);
  }

  ensureContact();
}

/***
   Check to make sure that processing is listening and establish contact.
   Nessacary to start the back and forth chain.
*/
void ensureContact() { //wait for a response from client:
  if (!Serial) {

    while (Serial.available() <= 0) { //execute this loop every 300 microseconds with millis() - compare seconde passed
      Serial.write(EOT);
      delay(300); //remove delay
    }

    //eat the byte that was sent as confirmation
    Serial.read();
    Serial.println("done");
    //request new data:
    Serial.println(ENQ);
  }
}

