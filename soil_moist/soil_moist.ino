const int SOIL_MOIST_PIN = A0;
int soilMoist;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}
//https://lamchucongnghe.com/huong-dan-esp8266-5-cam-bien-do-am-dat-va-ung-dung

void loop() {
  soilMoist = getSoilMoist();
  Serial.print("Do am dat: ");
  Serial.print(soilMoist);
  Serial.println(" %");
}

int getSoilMoist()
{
  int anaValue = 0;
  anaValue = analogRead(SOIL_MOIST_PIN); //Đọc giá trị cảm biến độ ẩm đất
  anaValue = map(anaValue, 1023, 0, 0, 100); //Ít nước:0%  ==> Nhiều nước 100%
  return anaValue;
}
