// Basic Config
#include "globals.h"
#include "gsm.h"

static const char TAG[] = "GSM";

TaskHandle_t gsmLoopTask;

#define TINY_GSM_MODEM_SIM800   // Modem is SIM800
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#include <TinyGsmClient.h>

#define SerialAT Serial1
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

#define MODEM_RST 5
#define MODEM_PWKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26

const char apn[] = "";      // Your APN
const char gprsUser[] = ""; // User
const char gprsPass[] = ""; // Password
const char simPIN[] = "";   // SIM card PIN code, if any

void gsmLoop(void *parameter) {
  while (1) {
    if (!modem.isNetworkConnected()) {
      if (!modem.waitForNetwork(1800L)) {
      ESP_LOGI(TAG, "Waiting GSM for network...");
      }

    }  else {
      if (!modem.isGprsConnected()) {
        if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
        ESP_LOGI(TAG, "Waiting GSM APN ...");
          return;
        }
      }
    }
    if (modem.isGprsConnected() && modem.isNetworkConnected()) {
      ESP_LOGI(TAG, "GSM connected...");
          delay(1000);
      }

    delay(2);

  }
}

int gsm_init(void) {
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);

  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  // Set GSM module baud rate and UART pins
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);
  modem.restart();
  ESP_LOGI(TAG, "Initializing modem...");
  String modemInfo = modem.getModemInfo();
  ESP_LOGI(TAG, "modem %s", modemInfo.c_str());
  return 1;
}
