#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SDHCI.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
SDClass mySD;

File dataFile;

void setup() {
  Serial.begin(9600);
  mlx.begin();

  

  // SDカードにデータを追記モードで開く
  dataFile = mySD.open("temperature_data.txt", FILE_WRITE);
  if (dataFile) {
    Serial.println("データファイルが正常に開かれました");
  } else {
    Serial.println("データファイルの開くのに失敗しました");
  }
}

void loop() {
  float ambientTemp = mlx.readAmbientTempC();
  float objectTemp = mlx.readObjectTempC();
  
  Serial.print("Ambient = "); Serial.print(ambientTemp); 
  Serial.print("*C\tObject = "); Serial.print(objectTemp); Serial.println("*C");

  // SDカードにデータを記録
  if (dataFile) {
    dataFile.print("Ambient = "); dataFile.print(ambientTemp); 
    dataFile.print("*C\tObject = "); dataFile.print(objectTemp); dataFile.println("*C");
    dataFile.flush(); // フラッシュしてデータをSDカードに保存
  } else {
    Serial.println("データファイルが開かれていません");
  }

  delay(1000);
}
