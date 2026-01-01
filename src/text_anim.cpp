#include "text_anim.h"
#include "settings.h"

// ------------------ STATE ------------------
int charIndex = 0;
bool cursorVisible = true;
unsigned long lastBlinkTime = 0;
const int blinkInterval = CURSOR_BLINK_INTERVAL;

// ------------------ INTERNAL HELPERS ------------------
String wrapText(const String& text) {
  String wrapped = "";
  int lineStart = 0;
  int count = 0;

  for (int i = 0; i < text.length(); ++i) {
    if (text[i] == ' ' || i == text.length() - 1) {
      int wordEnd = (text[i] == ' ') ? i : i + 1;
      int wordLength = wordEnd - lineStart;
      if (count + wordLength > maxCharsPerLine) {
        wrapped += '\n';
        wrapped += text.substring(lineStart, wordEnd);
        count = wordLength;
      } else {
        wrapped += text.substring(lineStart, wordEnd);
        count += wordLength;
      }
      lineStart = wordEnd;
    }
  }
  return wrapped;
}

std::vector<String> splitLines(const String& wrapped) {
  std::vector<String> lines;
  int start = 0;
  for (int i = 0; i <= wrapped.length(); ++i) {
    if (i == wrapped.length() || wrapped[i] == '\n') {
      lines.push_back(wrapped.substring(start, i));
      start = i + 1;
    }
  }
  return lines;
}

void drawCursor(const std::vector<String>& lines, int startLine) {
  if (millis() - lastBlinkTime >= blinkInterval) {
    cursorVisible = !cursorVisible;
    lastBlinkTime = millis();
  }

  if (cursorVisible && !lines.empty()) {
    const String& lastLine = lines.back();
    int cursorX = u8g2.getStrWidth(lastLine.c_str());
    int cursorY = fontHeight * (lines.size() - startLine);
    u8g2.drawStr(cursorX, cursorY, "_");
  }
}

void drawTextBox(const std::vector<String>& lines, int startLine) {
  const int paddingX = TEXT_PADDING_X;
  const int paddingY = TEXT_PADDING_Y;

  int maxWidth = 0;
  for (const auto& line : lines) {
    int w = u8g2.getStrWidth(line.c_str());
    maxWidth = max(maxWidth, w);
  }

  int boxWidth = min(maxWidth + 2 * paddingX, DISPLAY_WIDTH);
  int visibleLines = min((int)lines.size(), DISPLAY_HEIGHT / fontHeight);
  int boxHeight = visibleLines * fontHeight + 2 * paddingY;

  u8g2.drawFrame(0, 0, boxWidth, boxHeight);
}

int drawTextWithScroll(const std::vector<String>& lines) {
  int maxVisibleLines = DISPLAY_HEIGHT / fontHeight;
  int startLine = max(0, (int)lines.size() - maxVisibleLines);

  int y = fontHeight + 2;
  for (int i = startLine; i < (int)lines.size(); ++i) {
    u8g2.drawStr(TEXT_PADDING_X, y, lines[i].c_str());
    y += fontHeight;
  }
  return startLine;
}

void runTextAnimation(const char* message) {
  int msgLen = strlen(message);
  charIndex = 0;

  while (charIndex < msgLen) {
    u8g2.clearBuffer();

    String partial = String(message).substring(0, charIndex);
    String wrapped = wrapText(partial);
    std::vector<String> lines = splitLines(wrapped);

    int startLine = drawTextWithScroll(lines);
    drawTextBox(lines, startLine);
    drawCursor(lines, startLine);

    u8g2.sendBuffer();
    delay(TEXT_TYPE_DELAY);
    ++charIndex;
  }

  // Final display with blinking cursor
  String wrapped = wrapText(String(message));
  std::vector<String> lines = splitLines(wrapped);
  for (int i = 0; i < 50; ++i) {
    u8g2.clearBuffer();
    int startLine = drawTextWithScroll(lines);
    drawTextBox(lines, startLine);
    drawCursor(lines, startLine);
    u8g2.sendBuffer();
    delay(TEXT_FINAL_DELAY);
  }
}

void drawCenteredText(const char* message, int y) {
  int textWidth = u8g2.getStrWidth(message);
  int x = (DISPLAY_WIDTH - textWidth) / 2;
  u8g2.drawStr(x, y, message);
}