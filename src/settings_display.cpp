#include <Arduino.h>
#include <U8g2lib.h>
#include "settings.h"
#include "settings_display.h"

// Assuming u8g2 is declared in main.cpp, we need to declare it extern here
extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2; // Adjust the type if different

// Function to display the settings page
void displaySettingsPage(int numAnimations) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr); // Use a readable font

  // Title
  u8g2.drawStr(15, 15, "Settings");

  // Enabled animations count
  char animBuf[32];
  sprintf(animBuf, "Enabled: %d", numAnimations);
  u8g2.drawStr(10, 35, animBuf);
  u8g2.sendBuffer();
}