#include <Arduino.h>

const uint16_t BLINKING_WINDOW = 4500; // 4.5 seconds
const float BLINKING_INTERVAL = 0.25; // 0.25s blinking
const float ACCELERATION_THRESHOLD = 0.5 * 9.81; // m/s^2

enum breaking_state {
    NORMAL_BRAKING,
    HARD_BRAKING,
};

breaking_state state;
uint16_t hard_braking_start;

void setup() {
    // Setup Accelerometer
    // Init state machine
    state = NORMAL_BRAKING;

    Serial.begin(9600);
}

// Define helper functions
float read_acceleration();
void turn_on_brake_light();
void turn_off_brake_light();
void toggle_brake_light();

// If the acceleration is greater than 1.5g, then we are braking hard
// If we are breaking hard, make the LED blink at 4Hz for 4.5 seconds then go back to normal
void loop() {
    float acceleration = read_acceleration();
    Serial.println(acceleration);
    switch (state) {
        
        case NORMAL_BRAKING:
            Serial.println("Normal braking");
            turn_on_brake_light();
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
                turn_on_brake_light();
            } else {
                // Turn off LED
                turn_off_brake_light();
            }
            break;
    }
}

float read_acceleration() {
    float x = random(1, 6);
    float y = random(1, 6);
    float z = random(1, 6);
    float vec = sqrt(x * x + y * y + z * z);
    return x;
}

void turn_on_brake_light() {
    Serial.println("ON");
}
void turn_off_brake_light() {
    Serial.println("OFF");
}
void toggle_brake_light() {}