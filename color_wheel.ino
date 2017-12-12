#include <math.h>

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 15; // analog pin connected to X output
const int Y_pin = 14; // analog pin connected to Y output
const int R_pin = 11; // analog pin connected to Red value
const int G_pin = 10; // analog pin connected to Green value
const int B_pin = 9;  // analog pin connected to Blue value

// For Serial statements
const bool debug = false;

void setup() {
  pinMode(SW_pin, INPUT);
  pinMode(R_pin,OUTPUT);
  pinMode(G_pin,OUTPUT);
  pinMode(B_pin,OUTPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
}

void loop() {

  if (debug) {
    Serial.print("Switch:  ");
    Serial.print(digitalRead(SW_pin));
    Serial.print("\n");
    Serial.print("X-axis: ");
    Serial.print(analogRead(X_pin));
    Serial.print("\n");
    Serial.print("Y-axis: ");
    Serial.println(analogRead(Y_pin));
    Serial.print("\n\n");
  }

  // Get x & y "coordinate" values from joystick
  int x = analogRead(X_pin);
  int y = analogRead(Y_pin);

  // If joystick is centered, just make the color white
  // Add 20 units of leighway for both directions for each axis
  if ( x > 490 && x < 534 && y > 490 && y < 534) {
    changeColor(255,255,255);

  // Otherwise, calculate hue angle & convert to RGB vals
  // It is assumed/hardcoded for S & V == 1 (in HSV mode)
  } else {

    // Floor round x and y values by the 10's place
    // Eliminates weird arithmetic issues caused by imperfect
    // analog feedback (e.g. max val for each is 1024; only gets to 1018)
    float x_val = x/10-51; 
    float y_val = y/10-51;

    if (debug) {
      Serial.print("x_val: ");
      Serial.print(x_val);
      Serial.print("\n");
      Serial.print("y_val: ");
      Serial.print(y_val);
      Serial.print("\n");
    }

    // Use arctan for the hue angle in radians from [-pi,pi]
    double hue = atan2(y_val,x_val);

    // Adjust the hue to be in range [0,2pi]
    // then convert the hue from rad to degrees
    hue = hue < 0 ? hue + 2 * 3.14 : hue;
    hue = hue/6.28 * 360;

    if (debug) {
      Serial.print("hue: ");
      Serial.print(hue);
      Serial.print("\n\n");
      delay(200);
    } 

    // Get the RGB vals, change the color accordingly
    int* rgb = (int*) malloc (3 * sizeof(int));
    getRGBVals(hue, rgb);
    changeColor(rgb[0],rgb[1],rgb[2]);
    free(rgb);
  }
}

// Gets the RGB value of corresponding color to hue
// saturation & value will be hardcoded to be 1
// equations found here: https://www.rapidtables.com/convert/color/hsv-to-rgb.html
void getRGBVals(double hue, int* rgb) {
  int c = 1;
  int x = c * (1-fabs(int(hue/60)%2-1));
  int m = 0;

  int r_prime, g_prime, b_prime;
  if (hue >= 300) {
    r_prime = c;
    g_prime = 0;
    b_prime = x;
    
  } else if (hue >= 240) {
    r_prime = x;
    g_prime = 0;
    b_prime = c;
    
  } else if (hue >= 180) {
    r_prime = 0;
    g_prime = x;
    b_prime = c;
    
  } else if (hue >= 120) {
    r_prime = 0;
    g_prime = c;
    b_prime = x;
    
  } else if (hue >= 60) {
    r_prime = x;
    g_prime = c;
    b_prime = 0;

  } else { // hue >= 0
    r_prime = c;
    g_prime = x;
    b_prime = 0;
  }

  rgb[0] = (r_prime + m) * 255;
  rgb[1] = (g_prime + m) * 255;
  rgb[2] = (b_prime + m) * 255;
  
  if (debug) {
    Serial.print("r_prime: ");
    Serial.print(r_prime);
    Serial.print("\n");
    Serial.print("g_prime: ");
    Serial.print(g_prime);
    Serial.print("\n");
    Serial.print("b_prime: ");
    Serial.print(b_prime);
    Serial.print("\n");
    
    Serial.print("R: ");
    Serial.print(rgb[0]);
    Serial.print("\n");
    Serial.print("G: ");
    Serial.print(rgb[1]);
    Serial.print("\n");
    Serial.print("B: ");
    Serial.print(rgb[2]);
    Serial.print("\n\n");
  }
}

// Just makes changing the LED color cleaner/easier
void changeColor(int R, int G, int B) {
      analogWrite(R_pin,R);
      analogWrite(G_pin,G);
      analogWrite(B_pin,B);
}


