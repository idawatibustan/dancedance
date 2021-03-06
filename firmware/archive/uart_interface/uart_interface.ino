const int N = 2;
int16_t AcX[N],AcY[N],AcZ[N],Tmp[N],GyX[N],GyY[N],GyZ[N];
const int MPU_addr[N]={0x68, 0x69};  // I2C address of the first MPU-6050

int handshake_flag;
int send_sensor_data;
String incoming;

struct Dataframe {
    int16_t AcX[N], AcY[N], AcZ[N], Tmp[N], GyX[N], GyY[N], GyZ[N];
} dataframe;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  handshake_flag = 0;
  send_sensor_data = 0;
}


void loop() {
  if (handshake_flag == 0) {    
    while (Serial1.available() > 0) {
      char received = Serial1.read();
      incoming += received;
      if (incoming == "ACK1") {
        Serial1.println("ACK2");
        Serial.println("ACK2");
        incoming = "";
      } else if (incoming == "ACK3") {
        handshake_flag = 1;
        send_sensor_data = 1;
        incoming = "";
      }
    }
  }
  if (send_sensor_data == 1) {
    compileData();
    while (Serial1.available() > 0) {
      char received = Serial1.read();
      incoming += received;
      Serial1.println(incoming);
      Serial.println(incoming);
      if (incoming == "scriptend") {
        handshake_flag = 0;
        send_sensor_data = 0;
        incoming = "";
      }
    }
  }
}

void compileData() {
  // dummy values
  dataframe.AcX[0] = 100;
  dataframe.AcY[0] = 200;
  dataframe.AcZ[0] = 300;
  dataframe.Tmp[0] = 50;
  dataframe.GyX[0] = 400;
  dataframe.GyY[0] = 500;
  dataframe.GyZ[0] = 600;

  dataframe.AcX[1] = 1000;
  dataframe.AcY[1] = 2000;
  dataframe.AcZ[1] = 3000;
  dataframe.Tmp[1] = 100;
  dataframe.GyX[1] = 4000;
  dataframe.GyY[1] = 5000;
  dataframe.GyZ[1] = 6000;

  char sensor_one[100];
  char sensor_two[100];
//  sprintf(sensor_one, "%d AcX:%d AcY:%d AcZ:%d GyX:%d GyY:%d GyZ:%d", MPU_addr[0], dataframe.AcX[0], dataframe.AcY[0], dataframe.AcZ[0], dataframe.GyX[0], dataframe.GyY[0], dataframe.GyZ[0]);
//  sprintf(sensor_two, "%d AcX:%d AcY:%d AcZ:%d GyX:%d GyY:%d GyZ:%d", MPU_addr[1], dataframe.AcX[1], dataframe.AcY[1], dataframe.AcZ[1], dataframe.GyX[1], dataframe.GyY[1], dataframe.GyZ[1]);

  // format: <SENSOR_ID> <ACC_X> <ACC_Y> <ACC_Z> <GYRO_X> <GYRO_Y> <GYRO_Z>
  sprintf(sensor_one, "%d %d %d %d %d %d %d", MPU_addr[0], dataframe.AcX[0], dataframe.AcY[0], dataframe.AcZ[0], dataframe.GyX[0], dataframe.GyY[0], dataframe.GyZ[0]);
  sprintf(sensor_two, "%d %d %d %d %d %d %d", MPU_addr[1], dataframe.AcX[1], dataframe.AcY[1], dataframe.AcZ[1], dataframe.GyX[1], dataframe.GyY[1], dataframe.GyZ[1]);

  Serial.println(sensor_one);
  Serial1.println(sensor_one);
  delay(500);
  Serial.println(sensor_two);
  Serial1.println(sensor_two);
  delay(500);
}
