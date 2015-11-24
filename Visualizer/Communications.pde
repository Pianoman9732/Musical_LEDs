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

int timesThrough = 0;
int packetSize = 30;
int packetNum = 1;

void setupSerial() {
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600);
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

      for (int i = 0; i < packetSize; i++) {
       p.write(data[i*3]);
       p.write(data[i*3 + 1]);
       p.write(data[i*3 + 2]);
      }

      //for (int i = timesThrough*packetSize; i < (packetSize + timesThrough*packetSize); i += 3) {
      //  p.write(data[i*3]);
      //  p.write(data[i*3 + 1]);
      //  p.write(data[i*3 + 2]);
      //}

      //timesThrough++;
      //if (timesThrough > 2) {
      //  timesThrough = 0;
      //}
    } else {
      //always send input to allow arduino to resent w/out opening and closing current program?
      //System.out.println(inString.split(",").length);
      System.out.println("data = " + inString);
    }
  }
}