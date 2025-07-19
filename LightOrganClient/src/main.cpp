#include "ColorParser.h"
#include "Configuration.h"
#include "FastLED.h"
#include "SocketManager.h"
#include "WifiManager.h"
#include "LedManager.h"
#include "Color.h"

// State
LedManager ledManager;
WifiManager wifiManager;
SocketManager socketManager;
ColorParser colorParser;
bool isNewConnection = true;
unsigned long lastConnectAttempt = 0;       // Tracks the last time connectToWifi was called
const unsigned long connectInterval = 1000; // Interval in milliseconds (1 second)

// Setup
void configureSerialOutput()
{
  Serial.begin(115200);
}

void warmUpWifi()
{
  // NOTE: Connecting to wifi immediately resulted in messages not being received.
  uint32_t tenMs = 10;
  delay(tenMs);
}

void setup()
{
  configureSerialOutput();
  ledManager.setup();
  warmUpWifi();
}

// Loop
void connectToWifi()
{
  wifiManager.connect(ssid, password);
}

void updateLedsUsingFallback()
{
  static uint8_t tickOffset = 0;

  for (int segment = 0; segment < segments; ++segment)
  {
    // Calculate the color offset for the segment
    uint8_t hueOffset = (segment * 25 + tickOffset) % 256;

    for (int i = 0; i < segmentSize; ++i)
    {
      // Calculate the LED index within the array
      int ledIndex = segment * segmentSize + i;

      // Set the LED color with the hue offset
      CHSV hsvColor = CHSV(hueOffset, 255, 255); // Full saturation and brightness
      CRGB rgbColor;
      hsv2rgb_rainbow(hsvColor, rgbColor);

      Color color = Color(rgbColor.red, rgbColor.green, rgbColor.blue);

      ledManager.setLed(ledIndex, color);
    }
  }

  FastLED.show();

  delay(10);

  tickOffset = (tickOffset + 1) % 256;
  Serial.println("Tick offset: ");
  Serial.println(tickOffset);

  // for (int colorStep = 0; colorStep < 256; colorStep++)
  // {
  //   Color color;
  //   color.red = sin(colorStep * 0.024) * 127 + 128;
  //   color.green = sin(colorStep * 0.024 + 2 * PI / 3) * 127 + 128;
  //   color.blue = sin(colorStep * 0.024 + 4 * PI / 3) * 127 + 128;

  //   ledManager.setAllTo(color);

  //   delay(10); // delay for visual effect, adjust as needed
  // }
}

void handleInitialConnectionIfNeeded()
{
  wifiManager.printConnectionInformation();
  socketManager.openPort(port);
  // TODO: new connection false?
}

void setLedsToNextColor()
{
  std::string colorString = socketManager.getNextString();
  Color color = colorParser.getColor(colorString);
  ledManager.setAllTo(color);
}

void loop()
{
  if (wifiManager.isDisconnected())
  {
    unsigned long currentMillis = millis();

    if (currentMillis - lastConnectAttempt >= connectInterval)
    {
      lastConnectAttempt = currentMillis; // Update the last attempt time
      connectToWifi();                    // Call the function
    }

    updateLedsUsingFallback();
    isNewConnection = true;
  }
  else if (wifiManager.isConnected())
  {
    handleInitialConnectionIfNeeded();
    setLedsToNextColor();
    isNewConnection = false;
  }
}