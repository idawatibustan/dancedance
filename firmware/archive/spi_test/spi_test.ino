#import <SPI.h>

const int N = 2;
const int MPU_addr[N]={0x68, 0x69};  // I2C address of the first MPU-6050
//const int MPU_addr2=0x69;  // I2C address of the second MPU-6050
int16_t AcX[N], AcY[N], AcZ[N], Tmp[N], GyX[N], GyY[N], GyZ[N];
int i;

const int MOSI = 51; // MASTER OUT, SLAVE IN
const int MISO = 50; // MASTER IN, SLAVE OUT
const int SCK = 52; // CLOCK
const int SS = 53; // SLAVE SELECT

void setup(){
  /*
   * SET UP FOR SENSOR DATA COLLECTION
   */
  Wire.begin();

  // this is just a sample
  for (i = 0; i < N; i++){
    Wire.beginTransmission(MPU_addr[i]);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
  }

  /*
   * SET UP FOR SPI AND SERIAL
   */
  Serial.begin(9600);
  SPI.begin();

  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);

  delay(100);
}

void loop(){
  /*
   * COLLECTING SENSOR DATA
   * 
   * Ac = accelerometer
   * Tmp = temperature
   * Gy = gyroscope
   */
  for (i = 0; i < N; i++){
    Wire.beginTransmission(MPU_addr[i]);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr[i],14,true);  // request a total of 14 registers
    AcX[i]= Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
    AcY[i]= Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ[i]= Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp[i]= Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX[i]= Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY[i]= Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ[i]= Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    Serial.print("I2C Address ");Serial.print(MPU_addr[i]);Serial.print(":\n");
    Serial.print("AcX = "); Serial.print(AcX[i]);
    Serial.print(" | AcY = "); Serial.print(AcY[i]);
    Serial.print(" | AcZ = "); Serial.print(AcZ[i]);
    Serial.print(" | Tmp = "); Serial.print(Tmp[i]/340.00+36.53);  //equation for temperature in degrees C from datasheet
    Serial.print(" | GyX = "); Serial.print(GyX[i]);
    Serial.print(" | GyY = "); Serial.print(GyY[i]);
    Serial.print(" | GyZ = "); Serial.println(GyZ[i]);
  }

  
}
