//#include <SoftwareSerial.h>
//
////SoftwareSerial testSerial(19, 18);
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  Serial1.begin(9600); // for pin 18 and 19
//  while (!Serial1) {
//    Serial.println("Serial1 not connected");
//    delay(1000);
//  }
//
//  Serial.println("Serial connected");
//  delay(1000);
//  
////  testSerial.begin(9600);
////  testSerial("This is test communication");
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  Serial.println(Serial1.print("Hello"));
//  delay(1000);
//}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write("Yep\n"); 
//  if(Serial.available() > 0) {

    // echo
  Serial.write("Hello\n"); 
//  }
}
