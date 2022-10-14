#include <Arduino.h>

const uint16_t BLINKING_WINDOW = 4500; // 4.5 seconds
const float BLINKING_INTERVAL = 0.25; // 0.25s blinking
const float ACCELERATION_THRESHOLD = 0.5 * 9.81; // m/s^2

enum breaking {
    NORMAL_BRAKING,
    HARD_BRAKING,
};

breaking state;
uint16_t hard_braking_start;

void setup() {
    // Setup Accelerometer
    // Init state machine
    state = NORMAL_BRAKING;

    Serial.begin(9600);
}

// Define helper functions
float readAcceleration();
void turnOnBrakeLight();
void toggleBrakeLight();
void turnOffBrakeLight();

// If the acceleration is greater than 1.5g, then we are braking hard
// If we are breaking hard, make the LED blink at 4Hz for 4.5 seconds then go back to normal
void loop() {
    float acceleration = readAcceleration();
    Serial.println(acceleration);
    switch (state) {
        
        case NORMAL_BRAKING:
            Serial.println("Normal braking");
            turnOnBrakeLight();
            if (acceleration < ACCELERATION_THRESHOLD) break; // or return
            
            state = HARD_BRAKING;
            hard_braking_start = millis();

            break;

        case HARD_BRAKING:
            Serial.println("Hard braking");
            if (millis() - hard_braking_start > BLINKING_WINDOW && acceleration < ACCELERATION_THRESHOLD) {
                state = NORMAL_BRAKING;
                break; // or return
            }

            // Blinking
            if (millis() % int (BLINKING_INTERVAL * 1000) < BLINKING_INTERVAL * 500) {
                // Turn on LED
                turnOnBrakeLight();
            } else {
                // Turn off LED
                turnOffBrakeLight();
            }
            break;
    }
}

float readAcceleration() {
    float x = random(1, 5);
    float y = random(1, 5);
    float z = random(1, 5);
    float vec = sqrt(x * x + y * y + z * z);
    return x;
}

void turnOnBrakeLight() {
    Serial.println("ON");
}
void turnOffBrakeLight() {
    Serial.println("OFF");
}
void toggleBrakeLight() {}