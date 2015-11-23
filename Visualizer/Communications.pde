import processing.serial.*; 
Serial myPort;
String inString;

int repeats = 1;

//Used to receive commands from Arduino
boolean firstContact = false;
final byte EOT = 10;
final byte REQ = 5;
final byte STP = 4; //actually EOT char in ASCII



enum Modes {
  AVERAGE, LOGARITHMIC
}

void setupSerial() {
    printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 19200);
  myPort.bufferUntil(EOT);
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
    p.write(1);
  } else {
    if (inString.equals(Byte.toString(REQ))) { 
      println("cmd = " + inString);
      for (int i = 0; i < 10; i++) {
        p.write(i*20);
        p.write(10);
        p.write(i*15);
      }
      repeats += 10;
      if (repeats > 150) {
        repeats = 0;
      }
    } else {
      //always send input to allow arduino to resent w/out opening and closing current program?
      //System.out.println(inString.split(",").length);
      System.out.println("data = " + inString);
    }
  }
}