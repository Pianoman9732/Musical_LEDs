/******************
 * This is the test code for sending the visualization data to the arduino sketch. No newline
 * chars are needed to end input---the arduino takes a set number of values in a set amount of
 * time and reads it as one packet. See the Arduino code for more details.
 * <b>Need to run as root in Linux to use the serial library</b>.
 *
 * @author: Stuart Dilts
 *
 ******************/


import processing.serial.*; 
Serial myPort;
String inString;

int repeats = 1;

//Used to receive commands from Arduino
boolean firstContact = false;
final byte EOT = 10;
final byte REQ = 5;
final byte STP = 4; //actually EOT char in ASCII


void setup() {
  size(400, 200);
  // List all the available serial ports:
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 19200);
  myPort.bufferUntil(EOT);
}

void draw() {
  background(0);
  text("received: " + inString, 10, 50);
}

void serialEvent(Serial p) {
  //could change this to readBytes(), but that might break it
  inString = p.readString().trim();
  inString.trim();
  if (!firstContact) {
    println("established");
    println("contact = " + inString);
    p.clear();
    firstContact = true;
    p.write('1');
  } else {
    if (inString.equals(Byte.toString(REQ))) { 
      println("cmd = " + inString);
      for (int i = 0; i < 4; i++) {
        p.write(repeats);
      }
      repeats++;
      if (repeats > 5 ) {
        repeats = 0;
      }
    } else {
      //always send input to allow arduino to resent w/out opening and closing current program?
      //System.out.println(inString.split(",").length);
      System.out.println("data = " + inString);
    }
  }
}