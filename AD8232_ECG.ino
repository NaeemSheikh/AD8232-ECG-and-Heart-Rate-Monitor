/*
  ECG Signal And Heart Rate Acquisition From The AD8232 ECG Module

  In this project, we connect the AD8232 ECG module to an Arduino Uno to acquire ECG and heart
  rate of the person being tested with the module.
  
*/

int pulsePin = 1;
int hr = 0; // Heart Rate (in BPM)
int rawECG = 0; // ECG signal

// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, must be seeded!
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

void setup() {
  Serial.begin(9600); // Default baud rate
  interruptSetup();
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

}

void loop() {
  if (QS == true) {
    hr = getBPM();
    QS = false;
  }
  rawECG = analogRead(A0);
  sendData(rawECG, hr);
}

int getBPM() {
  return BPM;
}

void sendData(float ecg, int hrate) { // Sends data over serial port
  Serial.print(ecg);
  Serial.print(", ");
  Serial.println(hrate);
}
