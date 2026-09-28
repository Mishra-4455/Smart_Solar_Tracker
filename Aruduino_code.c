#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// // ------------------------- RAIN SENSOR ----------------------------
// const int rainAnalogPin = A6;
// const int rainDigitalPin = 7;
// unsigned long rainStartTime = 0;
int HowMuchRaining = 0;
int RainLevel = 0;

// // ------------------------- WIND SPEED ---------------------------
// volatile unsigned long windPulseCount = 0;
// unsigned long windLastTime = 0;
// const float WIND_CALIBRATION = 2.4; // Adjust based on: 2 * PI * arm_radius(m) * 3.6
// const int WIND_INTERVAL = 2000;
float windSpeed = 0.0;

// ------------------------------ OLED & SERVO --------------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
int position = 90;
int servoPin = 9;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo myServo;

// --------------------------------- LDR SENSOR ---------------------------------
int left1 = A0;
int left2 = A1;
int right1 = A2;
int right2 = A3;

// // ----------------------------- WIND INTERRUPT ---------------------------
// void countWindPulse() {
//     windPulseCount++;
// }

// ------------------------------ SETUP -----------------------------------
void setup() {
    // The display setup
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // Servo setup
    myServo.attach(servoPin);
    myServo.write(position);

    // --------------------------------- ACTUAL NEEDED SETUP -----------------------------------
    // // Animo meter setup
    // pinMode(2, INPUT_PULLUP);
    // attachInterrupt(
    //     digitalPinToInterrupt(2),
    //     countWindPulse,
    //     FALLING
    // );
    // windLastTime = millis();

    // // Rain setup
    // pinMode(rainDigitalPin, INPUT);
    // pinMode(rainAnalogPin, INPUT);

    // ----------------------- SETUP FOR SIMULATION PURPOSE TO BE REMOVED LATER -----------------------
    // Rain simulation potentiometer
    pinMode(A4, INPUT);

    // Wind simulation potentiometer
    pinMode(A5, INPUT);
}

// ------------------------------------- OLED DISPLAY FUNC -------------------------------------------
void print_data(int ang, int lumi, float wind, int rain){
    display.clearDisplay();

    display.setTextSize(1);

    // Title of the apparatus
    display.setCursor(30, 0);
    display.println("SOLAR GUARD");

    display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    // TRACKING display
    display.setCursor(0, 14);
    display.print("STATUS: TRACKING");
    
    // Angle
    display.setCursor(0, 24);
    display.print("ANGLE: ");
    display.print(ang);
    display.print(" degree");
    
    // Light
    display.setCursor(0, 34);
    display.print("LIGHT: ");
    display.print(lumi);
    display.print(" persentage");

    // Wind
    display.setCursor(0, 44);
    display.print("WIND: ");
    display.print(wind, 1);
    display.print(" km/h");

    // Rain 
    display.setCursor(0, 54);
    display.print("RAIN: ");
    if(rain == 1)
        display.print("NO ");
    else
        display.print("YES  AMT: ");
    //
    if(rain == 2)
        display.print("LOW");
    else if(rain == 3)
        display.print("MID");
    else if(rain == 4)
        display.print("HIGH");

    display.display();
}

// -------------------------------------- CODE ----------------------------------
void loop() {
    // Light calculation 
    // Read all four LDRs
    int LDR0 = analogRead(left1);
    int LDR1 = analogRead(left2);
    int LDR2 = analogRead(right1);
    int LDR3 = analogRead(right2);
    // Calculate average light on each side
    int leftLight = (LDR0 + LDR1) / 2;
    int rightLight = (LDR2 + LDR3) / 2;
    int diff = leftLight - rightLight;
    int light_per;

    // ------------------------ ACTUAL NEEDED CODE FOR WIND AND RAIN -----------------------------------

    // // wind speed calculations
    // unsigned long currentWindTime = millis();
    // if (currentWindTime - windLastTime >= WIND_INTERVAL) {
    //     noInterrupts();

    //     unsigned long pulses = windPulseCount;
    //     windPulseCount = 0;

    //     interrupts();

    //     float elapsedTime = (currentWindTime - windLastTime) / 1000.0;
    //     windLastTime = currentWindTime;
    //     float rotationsPerSecond = pulses / elapsedTime;
    //     windSpeed = WIND_CALIBRATION * rotationsPerSecond;
    // }

    // // Rain calculation 
    // int rainAnalogValue = analogRead(rainAnalogPin);
    // int rainDigitalValue = digitalRead(rainDigitalPin);

    // // Mapping it to 0-100 
    // HowMuchRaining = map(rainAnalogValue,1023, 0, 0, 100);
    // HowMuchRaining = constrain(HowMuchRaining, 0, 100);

    // ---------------------------- END OF NEEDED CODE ----------------------------

    // ------------------------- SUMULATION TRIAL CODE ----------------------------------
    
    // Wind calculation
    int simulatedWindValue = analogRead(A5);
    windSpeed = (simulatedWindValue / 1023.0) * 30.0;

    // Rain calculation
    int simulatedRainValue = analogRead(A4);
    HowMuchRaining = map(simulatedRainValue, 0, 1023, 0, 100);
    

    if(HowMuchRaining >= 80){
        RainLevel = 4;
    }
    else if(HowMuchRaining >= 50){
        RainLevel = 3;
    }
    else if(HowMuchRaining >= 20){
        RainLevel = 2;
    }
    else{
        RainLevel = 1;
    }
    // --------------------------- END OF SIMULATION TRIAL CODE -----------------------------

    // Printing what to the OLED display using the "print_data"
    if (diff >= 30) {
        position--;
        light_per = map(leftLight, 0, 1016, 100, 0);
        print_data(position, light_per, windSpeed, RainLevel);
    }
    else if (diff <= -30) {
        position++;
        light_per = map(rightLight, 0, 1016, 100, 0);
        print_data(position, light_per, windSpeed, RainLevel);
    }
    else{
        light_per = map((rightLight + leftLight/2), 0, 1023, 100, 0);
        print_data(position, light_per, windSpeed, RainLevel);
    }

    // Positioning Servo according to the data 
    position = constrain(position, 0, 180);
    myServo.write(position);
    delay(50);
}