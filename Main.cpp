#include "mbed.h"
#include <math.h>
#include <iostream>

// buzzer note definitions
#define NOTE_C4  262    
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523


// pins for buttons
DigitalIn startButton(PC_10);
DigitalIn modeButton(PC_11);

// pins for leds
DigitalOut led1(PC_1);
DigitalOut led2(PB_0);
DigitalOut led3(PC_0);
DigitalOut led4(PA_4);

// buzzer pwm output pin
PwmOut buzzer(PA_15);

// sensor input pins
AnalogIn TMP(PC_3);
AnalogIn sensorPin(PA_1); //LDR CLOSED_THRESHOLD = 32000 OPEN_THRESHOLD = 35000
AnalogIn fsrPin(PC_2);


// 7-seg output pins and hex codes
BusOut SegDis(PA_11, PA_12, PB_1, PB_14, PB_15, PB_12, PB_11);
DigitalOut decimal_point(PB_2);
int hexDis[] = {0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D}; // Hex values for digits 1-6


// Enum representing different washing modes
enum WashingMode {
    MODE_OFF,           // Washing machine is turned off
    MODE_STANDARD,      // Standard washing mode
    MODE_DELICATE,      // Delicate washing mode for sensitive fabrics
    MODE_INTENSIVE,     // Intensive washing mode for heavily soiled clothes
    MODE_ECO,           // Eco-friendly washing mode for energy efficiency
    MODE_WOOL,          // Wool washing mode for woolen garments
    MODE_RAPID,         // Rapid washing mode for quick wash cycles
    MODE_COUNT          // Number of washing modes 
};
// set current washing mode to off when the washing machine starts
WashingMode currentMode = MODE_OFF;


// function to play a single note with specified frequency and duration
void playNote(double frequency, int duration_ms) {
    buzzer.period(1.0 / frequency); // Set the period of the buzzer waveform
    buzzer.write(0.5); // Set the duty cycle to 50% to generate the note
    ThisThread::sleep_for(std::chrono::milliseconds(duration_ms)); // Wait for the duration
    buzzer.write(0.0); // Turn off the buzzer
}
// function to play a note twice with a delay 
void playNoteTwiceWithDelay(double frequency, int duration_ms, int delay_ms) {
    playNote(frequency, duration_ms); // Play the note first
    ThisThread::sleep_for(std::chrono::milliseconds(delay_ms)); // Delay
    playNote(frequency, duration_ms); // Play the note again
}

// function to set the washing mode based on user input
void setMode() {
    // Check if the mode button is pressed
    if (modeButton == 1) {
        // increment the current mode using modulo operation
        currentMode = static_cast<WashingMode>((currentMode + 1) % MODE_COUNT);
        
        // add debounce delay to prevent rapid mode changes
        ThisThread::sleep_for(300ms);
        
        // print the name of the current washing mode and play a note to indicate mode change
        switch (currentMode) {
            case WashingMode::MODE_STANDARD:
                printf("Current Mode: Standard\n");
                playNote(NOTE_A4, 100);
                break;
            case WashingMode::MODE_DELICATE:
                printf("Current Mode: Delicate\n");
                playNote(NOTE_A4, 100);
                break;
            case WashingMode::MODE_INTENSIVE:
                printf("Current Mode: Intensive\n");
                playNote(NOTE_A4, 100);
                break;
            case WashingMode::MODE_ECO:
                printf("Current Mode: Eco\n");
                playNote(NOTE_A4, 100);
                break;
            case WashingMode::MODE_WOOL:
                printf("Current Mode: Wool\n");
                playNote(NOTE_A4, 100);
                break;
            case WashingMode::MODE_RAPID:
                printf("Current Mode: Rapid\n");
                playNote(NOTE_A4, 100);
                break;
        }
    }
}

// function to display the corresponding number on a 7 segment display
void seven_seg_disp(int cycleNumber) {
    // set the value of the 7 segment display based on the cycle number
    SegDis = hexDis[cycleNumber - 1];
}

// function to update LEDs based on the current washing mode
void updateLEDs() {
    // check the current washing mode and update 7 seg
    if (currentMode == MODE_STANDARD) {
        // display the corresponding cycle number for Standard mode
        seven_seg_disp(1);
    } else if (currentMode == MODE_DELICATE) {
        // display the corresponding cycle number for Delicate mode
        seven_seg_disp(2);
    } else if (currentMode == MODE_INTENSIVE) {
        // display the corresponding cycle number for Intensive mode
        seven_seg_disp(3);
    } else if (currentMode == MODE_ECO) {
        // display the corresponding cycle number for Eco mode
        seven_seg_disp(4);
    } else if (currentMode == MODE_WOOL) {
        // display the corresponding cycle number for Wool mode
        seven_seg_disp(5);
    } else if (currentMode == MODE_RAPID) {
        // display the corresponding cycle number for Rapid mode
        seven_seg_disp(6);
    }
}




void standardMode() { // function for standard washing mode which runs for 10s
    playNoteTwiceWithDelay(NOTE_C5, 50, 50);
    for (int i = 0; i <25; i++) {
        led3.write(1);
        ThisThread::sleep_for(200ms);
        led3.write(0);
    }
}

void standardModecountdown() { //function to show the the countdown until cycle finishes
    int countdown = 10;

    while (countdown >= 0) {
        printf("Time remaining: %d seconds\r\n", countdown);
        countdown--;
        ThisThread::sleep_for(1000ms);
    }
    printf("Cycle completed.\n");
}




void delicateMode() { // function for delicate washing mode which runs for 25s
     playNoteTwiceWithDelay(NOTE_C5, 50, 50);
    for (int i = 0; i < 25; i++) {
        led3.write(1);
        ThisThread::sleep_for(500ms);
        led3.write(0);
        ThisThread::sleep_for(500ms);
    }
}

void delicateModecountdown() { //function to show the the countdown until cycle finishes
    int countdown = 25;

    while (countdown >= 0) {
        printf("Time remaining: %d seconds\r\n", countdown);
        countdown--;
        ThisThread::sleep_for(1000ms);
    }
    printf("Cycle completed.\n");
}




void intensiveMode() { // function for intensive washing mode which runs for 5s
    playNoteTwiceWithDelay(NOTE_C5, 50, 50);
    for (int i = 0; i <25; i++) {
        led3.write(1);
        ThisThread::sleep_for(100ms);
        led3.write(0);
        ThisThread::sleep_for(100ms);
    }
}   

void intensiveModecountdown() { //function to show the the countdown until cycle finishes
    int countdown = 5;

    while (countdown >= 0) {
        printf("Time remaining: %d seconds\r\n", countdown);
        countdown--;
        ThisThread::sleep_for(1000ms);
    }
    printf("Cycle completed.\n");
}




void ecoMode() { // function for eco washing mode which runs for 12s
    playNoteTwiceWithDelay(NOTE_C5, 50, 50);
    for (int i = 0; i <25; i++) { 
        led3.write(1);
        ThisThread::sleep_for(240ms);
        led3.write(0);
        ThisThread::sleep_for(240ms);
    }
}   

void ecoModecountdown() { //function to show the the countdown until cycle finishes
    int countdown = 12;

    while (countdown >= 0) {
        printf("Time remaining: %d seconds\r\n", countdown);
        countdown--;
        ThisThread::sleep_for(1000ms);
    }
    printf("Cycle completed.\n");
}




void woolMode() {   // function for eco washing mode which runs for 14s
    playNoteTwiceWithDelay(NOTE_C5, 50, 50);
    for (int i = 0; i <25; i++) { 
        led3.write(1);
        ThisThread::sleep_for(280ms);
        led3.write(0);
        ThisThread::sleep_for(280ms);
    }
}   

void woolModecountdown() { //function to show the the countdown until cycle finishes
    int countdown = 14;

    while (countdown >= 0) {
        printf("Time remaining: %d seconds\r\n", countdown);
        countdown--;
        ThisThread::sleep_for(1000ms);
    }
    printf("Cycle completed.\n");
}




void rapidMode() {  // function for rapid washing mode which runs for 2s
    playNoteTwiceWithDelay(NOTE_C5, 50, 50);
    for (int i = 0; i <25; i++) { //run for 2s
        led3.write(1);
        ThisThread::sleep_for(80ms);
        led3.write(0);
        ThisThread::sleep_for(80ms);
    }
}   

void rapidModecountdown() { //function to show the the countdown until cycle finishes
    int countdown = 14;

    while (countdown >= 0) {
        printf("Time remaining: %d seconds\r\n", countdown);
        countdown--;
        ThisThread::sleep_for(1000ms);
    }
    printf("Cycle completed.\n");
}




//f unction to indicate the completion of a washing cycle
void finish(int frequency, int duration) {
    // set the period of the buzzer waveform based on the frequency
    buzzer.period_us((float)1000000.0f / (float)frequency);
    
    // set the pulse width of the buzzer to produce sound
    buzzer.pulsewidth_us(buzzer.read_period_us() / 2);
    
    // wait for delay
    ThisThread::sleep_for(1000ms);
    
    // turn off the buzzer
    buzzer.pulsewidth_us(0);
    
    // set the washing mode to off
    currentMode = MODE_OFF;
    
    // flash the LEDs to show cycle completion
    led1 = 1;
    led2 = 1;
    led4 = 1;
    ThisThread::sleep_for(20ms);
    led1 = 0;
    led2 = 0;
    led4 = 0;
    ThisThread::sleep_for(20ms);
    led1 = 1;
    led2 = 1;
    led4 = 1;
    ThisThread::sleep_for(20ms);
    led1 = 0;
    led2 = 0;
    led4 = 0;
    ThisThread::sleep_for(20ms);
    led1 = 1;
    led2 = 1;
    led4 = 1;
    ThisThread::sleep_for(20ms);
    led1 = 0;
    led2 = 0;
    led4 = 0;
    ThisThread::sleep_for(20ms);
}






// function to read temperature from a temperature sensor
float readTemperature() {
    // read the analog pin of the temperature sensor and convert the value to millivolts
    float temp_mv = TMP.read_u16() * 0.48828125;
    
    // convert millivolts to Celsius using the conversion factor
    float temp_celsius = temp_mv / 100;
    
    // round the temperature to the nearest integer
    int rounded_temp = round(temp_celsius);
    
    // return the rounded temperature value
    return rounded_temp;
}

// function to monitor the status of the door sensor
void doorShut() {
    int sensorValue; // variable to store the value coming from the door sensor
    
    // continuously monitor the door sensor
    while(1) {
        // read the value from the sensor and scale it to the range 0-65535
        sensorValue = int(sensorPin.read() * 65535);
        
        // wait for a short duration before reading again
        ThisThread::sleep_for(100ms);
    }
}

// function to check the weight from a weight sensor
void weight_check() {
    int sensorValue; // variable to store the value coming from the weight sensor
    
    // continuously check the weight sensor
    while(1) {
        // read the value from the sensor and scale it to the range 0-65535
        sensorValue = int(fsrPin.read() * 65535);
        
        // wait for a short duration before reading again
        ThisThread::sleep_for(100ms);
    }
}


int main() {
        while (1) {
            setMode(); // check for mode change
        updateLEDs(); // update LEDs on current mode
        int temperature = readTemperature(); // Read the temperature
        int sensorValue = int(sensorPin.read() * 65535); // read the value from the sensor (scale)
        int weightValue = int(fsrPin.read() * 65535); // read the value from the sensor (scale)
       
       //printf("Temperature: %dC\n", temperature); // comment these out
       //printf("Sensor value: %d\n", sensorValue);
       //printf("FSR value: %d\n", weightValue);

        if (startButton == 1 && currentMode != MODE_OFF) {
            if (currentMode == MODE_STANDARD) {
                if (temperature < 20.0f || sensorValue > 35000 || weightValue > 10000) {
                    printf("Temperature is too low, the door is open or washing machine is overweight. Cannot start the machine.\n");
                } else if (sensorValue < 32000 && weightValue < 9500) {
                    printf("Door Closed. Standard mode starting.\n");

                Thread thread1;
                Thread thread2;

                thread1.start(callback(standardMode));
                thread2.start(callback(standardModecountdown));

                thread1.join();
                thread2.join();
                //standardMode();
                //standardModecountdown();
                finish(NOTE_C4, 50);
                finish(NOTE_E4, 50);
                finish(NOTE_G4, 200);
                }
            } else if (currentMode == MODE_DELICATE) {
                if (temperature < 18.0f || sensorValue > 35000 || weightValue > 10000) {
                printf("Temperature is too low or the door is open. Cannot start the machine.\n");
                } else if (sensorValue < 32000 && weightValue < 9500) {
                    printf("Door Closed. Delicate mode starting.\n");

                Thread thread3;
                Thread thread4;

                thread3.start(callback(delicateMode));
                thread4.start(callback(delicateModecountdown));

                thread3.join();
                thread4.join();
                //delicateMode();
                //delicateModecountdown();
                finish(NOTE_C4, 50);
                finish(NOTE_E4, 50);
                finish(NOTE_G4, 200);

                }
            } else if (currentMode == MODE_INTENSIVE) {
                if (temperature < 30.0f || sensorValue > 35000 || weightValue > 10000) { //30 degrees
                    printf("Temperature is too low or the door is open. Cannot start the machine.\n");
                } else if(sensorValue < 32000 && weightValue < 9500) {
                     printf("Door Closed. Intensive mode starting.\n");
                
                Thread thread5;
                Thread thread6;

                thread5.start(callback(intensiveMode));
                thread6.start(callback(intensiveModecountdown));

                thread5.join();
                thread6.join();
                //intensiveMode();
                finish(NOTE_C4, 50);
                finish(NOTE_E4, 50);
                finish(NOTE_G4, 200);
                }
            }
            else if (currentMode == MODE_ECO) {
                if (temperature < 24.0f || sensorValue > 35000 || weightValue > 10000) {
                    printf("Temperature is too low or the door is open. Cannot start the machine.\n");
                } else if(sensorValue < 32000 && weightValue < 9500) {
                     printf("Door Closed. Eco mode starting.\n");
                
                Thread thread7;
                Thread thread8;

                thread7.start(callback(ecoMode));
                thread8.start(callback(ecoModecountdown));

                thread7.join();
                thread8.join();
                //ecoMode();
                finish(NOTE_C4, 50);
                finish(NOTE_E4, 50);
                finish(NOTE_G4, 200);
                }
            }
             else if (currentMode == MODE_WOOL) {
                if (temperature < 16.0f || sensorValue > 35000 || weightValue > 10000) {
                    printf("Temperature is too low or the door is open. Cannot start the machine.\n");
                } else if(sensorValue < 32000 && weightValue < 9500) {
                     printf("Door Closed. Wool mode starting.\n");
                
                Thread thread9;
                Thread thread10;

                thread9.start(callback(ecoMode));
                thread10.start(callback(ecoModecountdown));

                thread9.join();
                thread10.join();
                finish(NOTE_C4, 50);
                finish(NOTE_E4, 50);
                finish(NOTE_G4, 200);
                }
            }
             else if (currentMode == MODE_RAPID) {
                if (temperature < 14.0f || sensorValue > 35000 || weightValue > 10000) {
                    printf("Temperature is too low or the door is open. Cannot start the machine.\n");
                } else if(sensorValue < 32000 && weightValue < 9500) {
                     printf("Door Closed. Rapid mode starting.\n");
                
                Thread thread11;
                Thread thread12;

                thread11.start(callback(ecoMode));
                thread12.start(callback(ecoModecountdown));

                thread11.join();
                thread12.join();
                finish(NOTE_C4, 50);
                finish(NOTE_E4, 50);
                finish(NOTE_G4, 200);
                }
            }
        }
        ThisThread::sleep_for(500ms);
    }
}

