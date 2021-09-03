#include <esp_now.h>
#include <Wire.h>
#include <WiFi.h>
#include <M5StickC.h>

#define CHANNEL 1

#define VEHICLE_ADDR    0x5d
#define PIN_SDA         0
#define PIN_SCL         26

uint16_t bgColor;
uint16_t fontColor;

//I2C command
#define MOTOR_STOP              0x00
#define MOTOR_FORWARD           0x01
#define MOTOR_LEFT_FORWARD      0x02
#define MOTOR_RIGHT_FORWARD     0x03
#define MOTOR_LEFT              0x04
#define MOTOR_RIGHT             0x05
#define MOTOR_LEFT_BACKWARD     0x06
#define MOTOR_RIGHT_BACKWARD    0x07
#define MOTOR_BACKWARD          0x08
#define MOTOR_RIGHT_ROTATE      0x10
#define MOTOR_LEFT_ROTATE       0x11

void I2C_Motor_write_speed(uint8_t direction, uint8_t motor_speed) {
    Wire.beginTransmission(VEHICLE_ADDR);
    Wire.write(direction);
    Wire.write(motor_speed);

    M5.Lcd.setRotation(4);
    M5.Lcd.fillScreen(bgColor);
    M5.Lcd.setTextColor(fontColor);
    M5.Lcd.setCursor(20, 60 , 2);
    M5.Lcd.println(direction); 

    Wire.endTransmission();
}

void doCommand( const uint8_t command ) {

    switch (command) {
        case MOTOR_STOP:
            bgColor=BLACK;
            fontColor=WHITE;
            I2C_Motor_write_speed( command, 0 );
            break;
        case MOTOR_FORWARD:
        case MOTOR_LEFT_FORWARD:
        case MOTOR_RIGHT_FORWARD:
            bgColor=BLUE;
            fontColor=WHITE;
            I2C_Motor_write_speed( command, 128 );
            break;
        case MOTOR_LEFT:
        case MOTOR_RIGHT:
            bgColor=GREEN;
            fontColor=BLACK;
            I2C_Motor_write_speed( command, 128 );
            break;
        case MOTOR_LEFT_BACKWARD:
        case MOTOR_RIGHT_BACKWARD:
        case MOTOR_BACKWARD:
            bgColor=RED;
            fontColor=WHITE;
            I2C_Motor_write_speed( command, 128 );
            break;
        case MOTOR_RIGHT_ROTATE:
        case MOTOR_LEFT_ROTATE:
            bgColor=YELLOW;
            fontColor=BLACK;
            I2C_Motor_write_speed( command, 128 );
            break;
        default:
            break;
    }
}

void InitESPNow() {
    WiFi.disconnect();
    if (esp_now_init() == ESP_OK) {
        Serial.println("ESPNow Init Success");
    }
    else {
        Serial.println("ESPNow Init Failed");
        ESP.restart();
    }
}

void configDeviceAP() {
    char* SSID = "Slave_1";
    bool result = WiFi.softAP(SSID, "Slave_1_Password", CHANNEL, 0);
    if (!result) {
        Serial.println("AP Config failed.");
    } else {
        Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
    }
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
    doCommand( *data );
}

void setup() {
    Serial.begin(115200);
    M5.begin();
    Wire.begin(PIN_SDA, PIN_SCL);   //SDA=0, SCL=26
    // Wire.begin(32, 33);

    M5.Lcd.setRotation(3);
    M5.Lcd.setTextSize(2);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("Starting...");

    Serial.println("ESPNow Slave");
    WiFi.mode(WIFI_AP);  //Set device in AP mode to begin with
    configDeviceAP();  // configure device AP mode
    Serial.print("AP MAC: ");
    Serial.println(WiFi.softAPmacAddress());  // This is the mac address of the Slave in AP Mode
    InitESPNow();  // Init ESPNow with a fallback logic
    esp_now_register_recv_cb(OnDataRecv);  // Once ESPNow is successfully Init, we will register for recv CB to get recv packer info.

}

void test() {

    int delaytime = 600;
    int delaytimeL = 1000;

    bgColor=BLUE;

    I2C_Motor_write_speed( MOTOR_STOP, 0 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_FORWARD, 128 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_LEFT_FORWARD, 128 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_LEFT, 128 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_LEFT_BACKWARD, 128 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_BACKWARD, 128 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_RIGHT_BACKWARD, 128 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_RIGHT, 128 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_RIGHT_FORWARD, 128 );
    delay(delaytime);

    bgColor=RED;

    I2C_Motor_write_speed( MOTOR_STOP, 0 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_RIGHT_ROTATE, 128 );
    delay(delaytimeL);
    I2C_Motor_write_speed( MOTOR_STOP, 0 );
    delay(delaytime);
    I2C_Motor_write_speed( MOTOR_LEFT_ROTATE, 128 );
    delay(delaytimeL);
}

void loop() {
    if ( M5.BtnA.wasReleased() ) {
        M5.Axp.PowerOff();
    }
    delay(10);
}
