#include <WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const char* ssid = "NET_2GF68C53";  //Nome da rede
const char* password = "B3F68C53";  //Senha da red

const uint16_t kIrLed = 4;  // ESP32 GPIO pin : 4 (D2).

IRsend irsend(kIrLed);  // Defina o GPIO a ser usado para enviar a mensagem.

//Liga/Desliga
uint16_t power[71] = {9024, 4456,  620, 530,  592, 528,  590, 532,  594, 1628,  
                        618, 1632,  616, 532,  592, 530,  590, 1634,  618, 1632,
                        618, 1630,  618, 1632,  618, 1630,  618, 530,  592, 1630,
                        620, 1630,  620, 530,  592, 1630,  618, 532,  592, 526,
                        590, 1632,  620, 1630,  616, 532,  592, 528,  592, 530,
                        592, 528,  592, 1630,  614, 1634,  618, 530,  588, 532,
                        594, 1628,  616, 1632,  622, 1628,  618, 42374,  9028,
                        2218,  622};  // NEC 19F69867

//Temp +
uint16_t tempUp[71] = {8994, 4486,  588, 560,  556, 564,  558, 564,  558, 1666,  586,
                        1664,  586, 562,  560, 560,  536, 1688,  582, 1666,  584, 1666,
                        586, 1664,  586, 1664,  582, 564,  562, 1662,  586, 1664,  586,
                        562,  556, 1666,  586, 562,  558, 1664,  562, 588,  560, 560,
                        562, 560,  558, 562,  558, 564,  560, 562,  558, 1668,  588, 558,
                        558, 1664,  584, 1664,  586, 1666,  584, 1664,  584, 1664,  586,
                        42406,  8968, 2280,  584};

//Temp -
uint16_t tempDown[71] = {8990, 4490,  556, 590,  558, 562,  558, 564,  560, 1664,  582, 1670,
                        582, 564,  556, 566,  530, 1660,  590, 1690,  584, 1666,  558, 1692,
                        582, 1668,  580, 564,  558, 1668,  584, 1664,  586, 564,  556, 1666,
                        584, 564,  554, 566,  560, 1666,  584, 562,  558, 564,  556, 566,
                        530, 588,  558, 564,  558, 1664,  584, 1668,  582, 566,  556, 1666,
                        558, 1690,  586, 1666,  582, 1664,  560, 42434,  8994, 2252,  586};

//Fan
uint16_t fan[71] = {9002, 4480,  592, 556,  566, 554,  566, 556,  566, 1656,
                        588, 1660,  590, 560,  590, 532,  566, 1656,  590, 1658,
                        592, 1658,  592, 1658,  592, 1658,  590, 556,  562, 1664,
                        592, 1656,  612, 536,  590, 530,  562, 558,  562, 1660,
                        594, 556,  564, 558,  592, 528,  566, 556,  564, 558,
                        564, 1658,  592, 1656,  592, 558,  564, 1656,  590, 1660,
                        590, 1658,  594, 1658,  590, 1660,  592, 42402,  9026,
                        2222,  592};

//Mode
uint16_t mode[73] = {8990, 4490,  580, 568,  550, 548,  576, 568,  550, 1672,
                        574, 1678,  578, 568,  556, 566,  554, 1668,  554, 1698,
                        604, 1644,  556, 1698,  574, 1672,  578, 568,  554, 1670,
                        580, 1668,  582, 566,  530, 592,  552, 568,  528, 594,
                        554, 1672,  576, 570,  526, 594,  552, 570,  530, 592,
                        528, 1694,  582, 1668,  578, 1670,  582, 564,  554, 1670,
                        584, 1666,  578, 1668,  556, 1698,  576, 42414,  8992, 2256,
                        580, 43920,  100};
                                                                      
WiFiServer wifiServer(80);

void setup() {
  irsend.begin();
  Serial.begin(115200);

  delay(1000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }

  Serial.print("Conectado ao Wi-Fi. IP:");
  Serial.println(WiFi.localIP());

  wifiServer.begin();

}

void loop() {

  WiFiClient client = wifiServer.available();
  String command = "";

  if (client) {

    while (client.connected()) {

      while (client.available()>0) {
        char c = client.read();
        if (c == '\n') {
          break;
        }
        command += c;
        Serial.write(c);
      }
      
      if (command == "POWER") {
        irsend.sendRaw(power, 71, 38);  // Envia o sinal referente ao comando power, que tem o comprimento de 71, na faixa de 38kHz.
        Serial.println("Ativado!");
      }else if (command == "TEMPUP") {
        irsend.sendRaw(tempUp, 71, 38);  // Envia o sinal referente ao comando tempUp, que tem o comprimento de 71, na faixa de 38kHz.
        Serial.println("Ativado!");
      }else if (command == "TEMPDOWN") {
        irsend.sendRaw(tempDown, 71, 38);  // Envia o sinal referente ao comando tempDown, que tem o comprimento de 71, na faixa de 38kHz.
        Serial.println("Ativado!");
      }else if (command == "FAN") {
        irsend.sendRaw(fan, 71, 38);  // Envia o sinal referente ao comando fan, que tem o comprimento de 71, na faixa de 38kHz.
        Serial.println("Ativado!");
      }else if (command == "MODE") {
        irsend.sendRaw(mode, 73, 38);  // Envia o sinal referente ao comando mode, que tem o comprimento de 73, na faixa de 38kHz.
        Serial.println("Ativado!");
      }

      command = "";
      delay(10);
    }

    client.stop();
    Serial.println("Cliente desconectado");
    
  }
}
