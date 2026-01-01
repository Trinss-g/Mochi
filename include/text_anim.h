#ifndef TEXT_ANIM_H
#define TEXT_ANIM_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <vector>

// Shared from .ino
extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;
extern int fontHeight;
extern int maxCharsPerLine;

// Exposed function
void runTextAnimation(const char* message);
void drawCenteredText(const char* message, int y);

#endif
