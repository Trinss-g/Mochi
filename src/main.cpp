#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "settings.h"
#include "settings_display.h"

// === Include animation frame arrays ===
#include "bigeye_anim.h"
#include "speedometer_anim.h"
#include "torchsearch_anim.h"
#include "tounge_anim.h"
#include "upside_down_anim.h"
#include "hat_xi_anim.h"
#include "text_anim.h"
#include "Ten_anim.h"
#include "next10_anim.h"
#include "rest_anim.h"

// --- Shared objects/variables ---
DISPLAY_TYPE u8g2(DISPLAY_ROTATION, /* reset=*/DISPLAY_RESET_PIN);
int fontHeight, maxCharsPerLine;
const char* message = MAIN_MESSAGE;


struct Animation {
  const unsigned char** frames;
  int frameCount;
  const char* name;
};

// List of all animations
Animation animations[] = {
  #if ENABLE_BIG_EYE_ANIM
  {big_eyeallArray, big_eyeallArray_LEN, "Big Eye"},
  #endif
  #if ENABLE_SPEEDOMETER_ANIM
  {speedometerallArray, speedometerallArray_LEN, "Speedometer"},
  #endif
  #if ENABLE_TORCH_ANIM
  {torch_searchallArray, torch_searchallArray_LEN, "Torch"},
  #endif
  #if ENABLE_TONGUE_ANIM
  {toungeallArray, toungeallArray_LEN, "Tongue"},
  #endif
  #if ENABLE_UPSIDE_DOWN_ANIM
  {epd_bitmap_upside_downallArray, epd_bitmap_upside_downallArray_LEN, "Upside Down"},
  #endif
  #if ENABLE_HAT_XI_ANIM
  {hat_xiallArray, hat_xiallArray_LEN, "Hat Xi"},
  #endif
  #if ENABLE_BEE_ANIM
  {BeeallArray, BeeallArray_LEN, "Bee"},
  #endif
  #if ENABLE_ANGRY_2_ANIM
  {Angry_2allArray, Angry_2allArray_LEN, "Angry 2"},
  #endif
  #if ENABLE_ANGRY_3_ANIM
  {Angry_3allArray, Angry_3allArray_LEN, "Angry 3"},
  #endif
  #if ENABLE_ANGRY_ANIM
  {AngryallArray, AngryallArray_LEN, "Angry"},
  #endif
  #if ENABLE_EYE_GOL_ANIM
  {eyegolallArray, eyegolallArray_LEN, "Eye Gol"},
  #endif
  #if ENABLE_CRY_2_ANIM
  {cry_2allArray, cry_2allArray_LEN, "Cry 2"},
  #endif
  #if ENABLE_CRY_ANIM
  {cryallArray, cryallArray_LEN, "Cry"},
  #endif
  #if ENABLE_LAUGH_ANIM
  {laughallArray, laughallArray_LEN, "Laugh"},
  #endif
  #if ENABLE_LAUGH_2_ANIM
  {laugh_2allArray, laugh_2allArray_LEN, "Laugh 2"},
  #endif
  #if ENABLE_DASAI_ANIM
  {DasaiallArray, DasaiallArray_LEN, "Dasai"},
  #endif
  #if ENABLE_TORCH_NEW_ANIM
  {TorchallArray, TorchallArray_LEN, "Torch New"},
  #endif
  #if ENABLE_EVIL_ANIM
  {evilallArray, evilallArray_LEN, "Evil"},
  #endif
  #if ENABLE_EVIL_2_ANIM
  {evil_2allArray, evil_2allArray_LEN, "Evil 2"},
  #endif
  #if ENABLE_DISTRACTED_ANIM
  {DistractedallArray, DistractedallArray_LEN, "Distracted"},
  #endif
  #if ENABLE_HAPPY_ANIM
  {HappyallArray, HappyallArray_LEN, "Happy"},
  #endif
  #if ENABLE_SNEEZE_ANIM
  {SneezeallArray, SneezeallArray_LEN, "Sneeze"},
  #endif
  #if ENABLE_VISUALIZER_ANIM
  {VisualizerallArray, VisualizerallArray_LEN, "Visualizer"},
  #endif
  #if ENABLE_LOVE_ANIM
  {loveallArray, loveallArray_LEN, "Love"},
  #endif
  #if ENABLE_HEHE_ANIM
  {heheallArray, heheallArray_LEN, "Hehe"},
  #endif
  #if ENABLE_MOCHI_ANIM
  {MochiallArray, MochiallArray_LEN, "Mochi"},
  #endif
  #if ENABLE_NEON_ANIM
  {NeonallArray, NeonallArray_LEN, "Neon"},
  #endif
  #if ENABLE_YAWN_ANIM
  {YawnallArray, YawnallArray_LEN, "Yawn"},
  #endif
  #if ENABLE_FAT_EYE_ANIM
  {Fat_eyeallArray, Fat_eyeallArray_LEN, "Fat Eye"},
  #endif
  #if ENABLE_RIGHT_EYE_ANIM
  {Right_eyeallArray, Right_eyeallArray_LEN, "Right Eye"},
  #endif
  #if ENABLE_LEFT_EYE_ANIM
  {Left_eyeallArray, Left_eyeallArray_LEN, "Left Eye"},
  #endif
  #if ENABLE_UP_EYE_ANIM
  {Up_eyeallArray, Up_eyeallArray_LEN, "Up Eye"},
  #endif
  #if ENABLE_DOWN_EYE_ANIM
  {Down_eyeallArray, Down_eyeallArray_LEN, "Down Eye"},
  #endif
  #if ENABLE_PINGPONG_2_ANIM
  {pingpongallArray, pingpongallArray_LEN, "Ping Pong 2"},
  #endif
  #if ENABLE_SAKURA_ANIM
  {SakuraallArray, SakuraallArray_LEN, "Sakura"},
  #endif
  #if ENABLE_SNEEZE_2_ANIM
  {Sneeze_2allArray, Sneeze_2allArray_LEN, "Sneeze 2"},
  #endif
};

const int totalAnimations = sizeof(animations) / sizeof(animations[0]);

// Track recently played animations (simple circular buffer)
int recentlyPlayed[15];  // Remember last 15 animations
int recentIndex = 0;

void playAnimation(const unsigned char* frames[], int frameCount, int delayMs) {
  for (int i = 0; i < frameCount; i++) {
    u8g2.clearBuffer();
    u8g2.drawXBMP(0, 0, FRAME_WIDTH, FRAME_HEIGHT, frames[i]);
    u8g2.sendBuffer();
    delay(delayMs);
  }
}

bool wasRecentlyPlayed(int index) {
  // Check if this animation was in the last 15 played
  for (int i = 0; i < 15; i++) {
    if (recentlyPlayed[i] == index) {
      return true;
    }
  }
  return false;
}

int getRandomAnimation() {
  int selected;
  int attempts = 0;
  
  // Try to find an animation that wasn't recently played
  do {
    selected = random(0, totalAnimations);
    attempts++;
    
    // After 30 attempts, just pick any random one
    if (attempts > 30) {
      break;
    }
  } while (wasRecentlyPlayed(selected));
  
  // Remember this animation
  recentlyPlayed[recentIndex] = selected;
  recentIndex = (recentIndex + 1) % 15;  // Wrap around
  
  return selected;
}


void playRandomAnimations() {
  // Decide how many animations to play (between min and max from settings)
  int numToPlay = random(RANDOM_ANIM_MIN_COUNT, RANDOM_ANIM_MAX_COUNT + 1);
  
  for (int i = 0; i < numToPlay; i++) {
    // Get a random animation (avoids recent repeats)
    int index = getRandomAnimation();
    
    // Play the animation
    playAnimation(
      animations[index].frames,
      animations[index].frameCount,
      ANIM_DELAY_DEFAULT
    );
    
    // Delay between animations
    delay(RANDOM_ANIM_DELAY_BETWEEN);
  }
}

void setup() {
  // Initialize random seed
  randomSeed(analogRead(0));
  
  // Initialize recently played array with -1 (no animation)
  for (int i = 0; i < 15; i++) {
    recentlyPlayed[i] = -1;
  }

  // Setup display
  Wire.begin(DISPLAY_I2C_SDA, DISPLAY_I2C_SCL);
  u8g2.begin();
  
  // Show welcome message
  u8g2.setFont(WELCOME_FONT);
  drawCenteredText(WELCOME_TEXT_LINE1, WELCOME_Y_LINE1);
  drawCenteredText(WELCOME_TEXT_LINE2, WELCOME_Y_LINE2);
  u8g2.sendBuffer();
  delay(WELCOME_DELAY);
  u8g2.clearBuffer();

  // Display settings page
  displaySettingsPage(totalAnimations);
  delay(3000);
  u8g2.clearBuffer();

  // Run text animation
  u8g2.setFont(TEXT_ANIM_FONT);
  fontHeight = u8g2.getMaxCharHeight();
  int charWidth = u8g2.getMaxCharWidth();
  maxCharsPerLine = DISPLAY_WIDTH / charWidth;
  runTextAnimation(message);
  delay(1000);
}

void loop() {
  // Play random animations with improved algorithm
  playRandomAnimations();
}