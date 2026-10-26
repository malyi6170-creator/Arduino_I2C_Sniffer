#include <Wire.h>

#define MY_I2C_ADDRESS 0x3F // Фиксированный адрес, на который настроена эта Arduino (Slave)

void setup() {
  Serial.begin(9600);
  while (!Serial); // Ожидание инициализации Serial-порта
  
  Serial.println(F("========================================="));
  Serial.println(F("   ATtiny13 Stable I2C Sniffer Ready     "));
  Serial.println(F("========================================="));

  // Запуск аппаратного интерфейса TWI/I2C в режиме ведомого (Slave)
  Wire.begin(MY_I2C_ADDRESS);
  
  // Регистрация прерывания: эта функция вызывается аппаратно «на лету» 
  // в момент успешного приема пакета по шине I2C.
  Wire.onReceive(receiveEvent);
}

void loop() {
  // Главный цикл полностью свободен от блокирующих задач
}

// Обработчик аппаратного прерывания приема данных
void receiveEvent(int bytesCount) {
  byte targetData = 0;
  
  // Вычитываем все байты, поступившие во внутренний аппаратный буфер
  while (Wire.available()) {
    targetData = Wire.read();
  }

  // Фильтруем данные: выводим в порт только печатные цифры от '0' до '9',
  // отсекая служебные байты адреса и возможные случайные наводки.
  if (targetData >= '0' && targetData <= '9') {
    Serial.print(F("[I2C OK] Digit: "));
    Serial.print((char)targetData);
    Serial.println(F(" -> [ACK Sent]"));
  }
}
