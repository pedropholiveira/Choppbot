#include <Choppbot.h>
#include <Arduino.h>
#include <WiFi.h>

// // Set your Static IP address
IPAddress local_IP(192, 168, 88, 150);
IPAddress gateway(192, 168, 88, 1);
IPAddress subnet(255, 255, 255, 0);
// // IPAddress primaryDNS(8, 8, 8, 8);   //optional
// // IPAddress secondaryDNS(8, 8, 4, 4); //optional

void initConection()
{
    pinMode(LedStatus, OUTPUT);
    WiFi.mode(WIFI_STA);
    WiFi.begin(Rede, Senha);

    if (!WiFi.config(local_IP, gateway, subnet))
    {
        Serial.println("Configurando Endereço");
    }

    Serial.println("Conectando a Rede...");
    delay(1000);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Conectando a Rede... ");
        delay(1000);
    }
    digitalWrite(LedStatus, HIGH);

    Serial.print("Conectado a rede: ");
    Serial.println(WiFi.localIP());
    Serial.print("Conexão: ");
    Serial.println(WiFi.getAutoConnect());
    Serial.print("Auto conect: ");
    Serial.println(WiFi.getAutoReconnect());
}
void checkConection()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LedStatus, LOW);
        // Serial.println("... wifi disconnected!");
        // delay(500);
        // initConection();
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(LedStatus, !LOW);
    }
}