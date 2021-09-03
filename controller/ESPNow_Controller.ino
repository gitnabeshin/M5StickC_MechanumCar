#include <WiFi.h>
#include <esp_now.h>
#include <M5StickCPlus.h>

//M5StickCPlus
int PIN_X = 33; //ADC works with ESP-NOW
int PIN_Y = 32; //ADC works with ESP-NOW
int PIN_A = 0;  //digitalRead works well with ESP-NOW 
int PIN_B = 25; //not work well with ESP-NOW

int MIN_LowKeepCount = 5;
int lowKeepCount = 0;
int button_B_State = HIGH;

esp_now_peer_info_t slave;
#define CHANNEL 3
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

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

#define JOYCON_LOW      1
#define JOYCON_NEUTRAL  2
#define JOYCON_HIGH     3

void InitESPNow() {
    WiFi.disconnect();
    if (esp_now_init() == ESP_OK) {
        Serial.println("ESPNow Init Success");
    } else {
        Serial.println("ESPNow Init Failed");
        ESP.restart();
    }
}

void ScanForSlave() {
    int8_t scanResults = WiFi.scanNetworks();
    bool slaveFound = 0;  // reset on each scan
    memset(&slave, 0, sizeof(slave));
    Serial.println("");
    if (scanResults == 0) {
        Serial.println("No WiFi devices in AP Mode found");
    } else {
        Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
        for (int i = 0; i < scanResults; ++i) {
            String SSID = WiFi.SSID(i);
            int32_t RSSI = WiFi.RSSI(i);
            String BSSIDstr = WiFi.BSSIDstr(i);
            delay(10);
            if (SSID.indexOf("Slave") == 0) {
                Serial.println("Found a Slave.");
                Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
                // Get BSSID => Mac Address of the Slave
                int mac[6];
                if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x%c",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
                    for (int ii = 0; ii < 6; ++ii ) {
                        slave.peer_addr[ii] = (uint8_t) mac[ii];
                    }
                }
                slave.channel = CHANNEL; // pick a channel
                slave.encrypt = 0; // no encryption
                slaveFound = 1;
                break;
            }
        }
    }
    if (slaveFound) {
        Serial.println("Slave Found, processing..");
    } else {
        Serial.println("Slave Not Found, trying again.");
    }
    WiFi.scanDelete();
}

bool manageSlave() {
    if (slave.channel == CHANNEL) {
        if (DELETEBEFOREPAIR) {
            deletePeer();
        }

        Serial.print("Slave Status: ");
        const esp_now_peer_info_t *peer = &slave;
        const uint8_t *peer_addr = slave.peer_addr;
        bool exists = esp_now_is_peer_exist(peer_addr);
        if ( exists) {
            // Slave already paired.
            Serial.println("Already Paired");
            return true;
        } else {
            // Slave not paired, attempt pair
            esp_err_t addStatus = esp_now_add_peer(peer);
            if (addStatus == ESP_OK) {
                // Pair success
                Serial.println("Pair success");
                return true;
            } else {
                Serial.println("Not sure what happened");
                return false;
            }
        }
    } else {
        Serial.println("No Slave found to process"); // No slave found to process
        return false;
    }
}

void deletePeer() {
    const esp_now_peer_info_t *peer = &slave;
    const uint8_t *peer_addr = slave.peer_addr;
    esp_err_t delStatus = esp_now_del_peer(peer_addr);
}

// send data
void sendData( uint8_t command_in ) {

    const uint8_t *peer_addr = slave.peer_addr;
    uint8_t command = command_in;
    esp_err_t result = esp_now_send(peer_addr, &command, 2);
}

void setButtonKeepState(int nowState_B){
    //D25(PULL_UP) data comes with noise LOW. So filter noise.
    if( nowState_B == LOW ){
        lowKeepCount++;
        if( lowKeepCount > MIN_LowKeepCount){
            button_B_State = LOW;
        }
    } else {
        lowKeepCount = 0;
        button_B_State = HIGH;
    }
}

uint8_t getControlState(void) {

    uint8_t command;

    int x_degree = analogRead(PIN_X);
    int y_degree = analogRead(PIN_Y);

    int button_A_State = digitalRead(PIN_A);
    setButtonKeepState( digitalRead(PIN_B) );

    int x_state = JOYCON_NEUTRAL;
    int y_state = JOYCON_NEUTRAL;

    M5.Lcd.fillScreen(BLACK);

    Serial.printf("X:%04d", x_degree );
    Serial.printf(", Y:%04d\n", y_degree );
    Serial.printf("A:%d", button_A_State );
    Serial.printf(",  B:%d \n", button_B_State );

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(10, 10, 1);
    M5.Lcd.print("X: "); M5.Lcd.print(x_degree);
    M5.Lcd.print(",  Y: "); M5.Lcd.println(y_degree);

    M5.Lcd.println();
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.setCursor(30, 40, 2);

    if( x_degree > 1800 ) {
        x_state = JOYCON_HIGH;
        M5.Lcd.setTextColor(BLUE);
        M5.Lcd.println("X: LEFT");
    } else if( x_degree >= 1500 && x_degree <= 1800 ) {
        x_state = JOYCON_NEUTRAL;
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.println("X: STOP");
    } else if( x_degree < 1500 ) {
        x_state = JOYCON_LOW;
        M5.Lcd.setTextColor(RED);
        M5.Lcd.println("X: RIGHT");
    } else {
        x_state = JOYCON_NEUTRAL;
        M5.Lcd.println("X: ERROR");
    }

    M5.Lcd.setCursor(30, 64, 2);

    if( y_degree > 1800 ) {
        y_state = JOYCON_HIGH;
        M5.Lcd.setTextColor(BLUE);
        M5.Lcd.println("Y: FORWARD");
    } else if( y_degree >= 1500 && y_degree <= 1800 ) {
        y_state = JOYCON_NEUTRAL;
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.println("Y: STOP");
    } else if( y_degree < 1500 ) {
        y_state = JOYCON_LOW;
        M5.Lcd.setTextColor(RED);
        M5.Lcd.println("Y: BACKWARD");
    } else {
        M5.Lcd.println("Y: ERROR");
    }

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 96, 1);

    M5.Lcd.print("A: "); M5.Lcd.print(button_A_State);
    M5.Lcd.print(",  B: "); M5.Lcd.println(button_B_State);

    if ( button_B_State == LOW ) {
        command = MOTOR_LEFT_ROTATE;
    } else if( button_A_State == LOW ){
        command = MOTOR_RIGHT_ROTATE;
    } else if( x_state == JOYCON_NEUTRAL ) {
        if( y_state == JOYCON_NEUTRAL ) {
            command = MOTOR_STOP;
        } else if( y_state == JOYCON_LOW ) {
            command = MOTOR_BACKWARD;
        } else {
            command = MOTOR_FORWARD;
        }
    } else if( x_state == JOYCON_LOW ) {
        if( y_state == JOYCON_NEUTRAL ) {
            command = MOTOR_RIGHT;
        } else if( y_state == JOYCON_LOW ) {
            command = MOTOR_RIGHT_BACKWARD;
        } else {
            command = MOTOR_RIGHT_FORWARD;
        }
    } else if( x_state == JOYCON_HIGH ) {
        if( y_state == JOYCON_NEUTRAL ) {
            command = MOTOR_LEFT;
        } else if( y_state == JOYCON_LOW ) {
            command = MOTOR_LEFT_BACKWARD;
        } else {
            command = MOTOR_LEFT_FORWARD;
        }
    } else {
        command = MOTOR_STOP;
    }

    return command;
}

void setup() {
    WiFi.mode(WIFI_STA);
    InitESPNow();
    M5.begin();
//    Serial.begin(115200);

    pinMode(PIN_X, ANALOG);
    pinMode(PIN_Y, ANALOG);

    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);

    M5.Lcd.setRotation(3);
    M5.Lcd.setTextSize(2);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.println("ESP-Now start.");
    delay(1000);
}

void loop() {
    M5.update();

    if (slave.channel == CHANNEL) { 
        bool isPaired = manageSlave();
        if (isPaired) {
            sendData( getControlState() );
        } else {
            Serial.println("Slave pair failed!");
        }
    } else {
        ScanForSlave();
    }
    delay(50);
}
