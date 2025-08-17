#include <Arduino.h>

// ---------------------------
// Define a new type called 'Color' using a 'struct'
// ---------------------------
// A struct is a simple way to group related data together.
// Here, 'Color' groups a color's name and its RGB values.
// Think of it like a mini object or record that holds three numbers plus a name.
struct Color {
  const char* name;   // Pointer to a constant character array (string literal) holding the color's name
  uint8_t red;        // Red component intensity (0 to 255)
  uint8_t green;      // Green component intensity (0 to 255)
  uint8_t blue;       // Blue component intensity (0 to 255)
};

const int RED_PIN = 10;
const int GREEN_PIN = 9;
const int BLUE_PIN = 8;

// ---------------------------
// Create an array of 'Color' structs to hold our predefined colors
// ---------------------------
// Here, 'colors' is an array holding many 'Color' structs.
Color colors[] = {
  {"red",     255,   0,   0},
  {"green",     0, 255,   0},
  {"blue",      0,   0, 255},
  {"yellow",  255, 255,   0},
  {"cyan",      0, 255, 255},
  {"magenta", 255,   0, 255},
  {"white",   255, 255, 255},
  {"purple",  128,   0, 255},
  {"orange",  255, 100,   0},
  {"pink",    255, 128, 192},
  {"brown",   139,  69,  19},
  {"aqua",      0, 255, 255},
  {"lime",    191, 255,   0},
  {"teal",      0, 128, 128},
  {"navy",      0,   0, 128},
  {"silver", 192, 192, 192},
  {"gray",   128, 128, 128},
};

// ---------------------------
// Calculate how many colors we have in the 'colors' array
// ---------------------------
// sizeof(colors) gives total bytes used by the entire array
// sizeof(Color) gives bytes used by a single element
// Dividing tells us the number of elements in the array
const int COLOR_COUNT = sizeof(colors) / sizeof(Color);

// ---------------------------
// Helper function: sets the RGB LED to given intensities
// ---------------------------
void setColor(uint8_t red, uint8_t green, uint8_t blue) {
  // analogWrite controls LED brightness using PWM (0=off, 255=full brightness)
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

// ---------------------------
// Find a color in the colors array by name (case-insensitive)
// ---------------------------
// Parameters:
//   - input: the color name to find
//   - result: output parameter to hold the matching Color struct (passed by reference so the function can modify it)
// Returns:
//   - true if a matching color was found
//   - false if no match found
//
// The function loops through the colors array and compares input to each stored name.
// If it finds a match, it copies the color data into 'result' (modifying the caller's variable) and returns true.
// If it gets through the whole array with no match, it returns false.
bool findColor(const String& input, Color& result) {
  for (int i = 0; i < COLOR_COUNT; i++) {
    if (input.equalsIgnoreCase(colors[i].name)) {
      // Copy matching color data into result
      result = colors[i];
      return true;
    }
  }
  // No match found
  return false;
}


void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  Serial.println("Enter a color:");
  while (Serial.available() == 0) {
    // Wait for input from Serial monitor
  }

  String input = Serial.readString(); // Read input line from serial
  input.trim();                       // Remove any trailing whitespace or newlines

  Color chosenColor;                  // Variable to hold the color if found

  // Use our lookup function to find the color by name
  if (findColor(input, chosenColor)) {
    // If found, set the LED to that color
    setColor(chosenColor.red, chosenColor.green, chosenColor.blue);

    Serial.print("Set color: ");
    Serial.println(chosenColor.name);
  } else {
    // Input color name didn't match any predefined color
    Serial.println("Unknown color");
  }
}
