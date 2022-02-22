#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// define pins for the red, green and blue LEDs and the neopixel strip
// #define RED_LED 6
// #define BLUE_LED 5
// #define GREEN_LED 9
#define NEOPIXEL 11

// define pins for the controls
#define HUE_PICKER A0
// #define BRIGHTNESS_PICKER A1
// #define BLINK_SPEED_PICKER A2

// Define number of leds of the neopixel strip
#define NUMPIXELS 60

// overall brightness value
// int brightness;
int hue;

// individual brightness values for the red, green and blue LEDs
struct color {
    byte r;
    byte g;
    byte b;
};

// overall blink speed
int blink_speed = 10;

// Setting up Neopixel
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup()
{
    // set up pins to output and input.
    // pinMode(GREEN_LED, OUTPUT);
    // pinMode(RED_LED, OUTPUT);
    // pinMode(BLUE_LED, OUTPUT);
    pinMode(NEOPIXEL, OUTPUT);
    pinMode(HUE_PICKER, INPUT);
    // pinMode(BRIGHTNESS_PICKER, INPUT);
    // pinMode(BLINK_SPEED_PICKER, INPUT);

    // Initialize NeoPixel
    pixels.begin();
    Serial.begin(9600);
}

void loop()
{
    // brightness = analogRead(BRIGHTNESS_PICKER);
    // brightness = map(brightness, 0, 1023, 0, 1000);

    // blink_speed = analogRead(BLINK_SPEED_PICKER);
    // blink_speed = map(blink_speed, 0, 1023, 0, 1500);

    hue = analogRead(HUE_PICKER);
    hue = map(hue, 0, 1023, 0, 360);
    color rgb = HSVtoRGB(hue, 100);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(rgb.r, rgb.g, rgb.b));


        // delay(DELAYVAL); // Pause before next pass through loop
    }
    pixels.show();   // Send the updated pixel colors to the hardware.
    //delay(1500);
}

struct color HSVtoRGB(int H, int S){
    struct color rgb; 
    float s = S/100;
    float v = 0.5;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    int R = (r+m)*255;
    int G = (g+m)*255;
    int B = (b+m)*255;
    rgb.r = R;
    rgb.g = G;
    rgb.b = B;
    return rgb;
}
