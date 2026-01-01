#ifndef SETTINGS_H
#define SETTINGS_H

// ==================== DISPLAY SETTINGS ====================

// Display Hardware Configuration
#define DISPLAY_WIDTH          128
#define DISPLAY_HEIGHT         64
#define DISPLAY_I2C_SDA        8
#define DISPLAY_I2C_SCL        9
#define DISPLAY_RESET_PIN      U8X8_PIN_NONE
#define DISPLAY_ROTATION       U8G2_R0

// Display Type
#define DISPLAY_TYPE           U8G2_SH1106_128X64_NONAME_F_HW_I2C

// ==================== FONT SETTINGS ====================

// Welcome Screen Font
#define WELCOME_FONT           u8g2_font_ncenB14_tr

// Text Animation Font
#define TEXT_ANIM_FONT         u8g2_font_8x13_tf

// ==================== ANIMATION SETTINGS ====================

// Animation Frame Dimensions
#define FRAME_WIDTH            DISPLAY_WIDTH
#define FRAME_HEIGHT           DISPLAY_HEIGHT

// Animation Delay (milliseconds) - Default for all animations
#define ANIM_DELAY_DEFAULT     70

// ==================== RANDOM ANIMATION SETTINGS ====================

// Random animation settings
#define RANDOM_ANIM_MIN_COUNT  5   // Minimum number of random animations to play
#define RANDOM_ANIM_MAX_COUNT  12  // Maximum number of random animations to play
#define RANDOM_ANIM_DELAY_BETWEEN 5000  // Delay between different animations (milliseconds)

// ==================== TEXT ANIMATION SETTINGS ====================

// Cursor Settings
#define CURSOR_BLINK_INTERVAL  400  // milliseconds

// Text Animation Timing
#define TEXT_TYPE_DELAY        120  // milliseconds between characters
#define TEXT_FINAL_DELAY       50   // milliseconds between cursor blinks

// Text Layout
#define TEXT_PADDING_X         4
#define TEXT_PADDING_Y         4

// ==================== WELCOME SCREEN SETTINGS ====================

// Welcome Screen Timing
#define WELCOME_DELAY          1000  // milliseconds

// Welcome Text
#define WELCOME_TEXT_LINE1     "Hello!"
#define WELCOME_TEXT_LINE2     "@Trinss"

// Welcome Text Positions
#define WELCOME_Y_LINE1        32
#define WELCOME_Y_LINE2        48


// ==================== MAIN MESSAGE ====================

// Main animated text message
#define MAIN_MESSAGE    "Sample animated message goes here. Customize this message as needed for your display animation project."

// ==================== DEBUG SETTINGS ====================

// Serial Debug (uncomment to enable)
// #define ENABLE_SERIAL_DEBUG
// #define SERIAL_BAUD_RATE       115200

// ==================== ANIMATION SEQUENCES ====================

// Enable/disable specific animations (1 = enabled, 0 = disabled)
#define ENABLE_BIG_EYE_ANIM    1
#define ENABLE_PING_PONG_ANIM  1
#define ENABLE_SPEEDOMETER_ANIM 1
#define ENABLE_TORCH_ANIM      1
#define ENABLE_TONGUE_ANIM     1
#define ENABLE_UPSIDE_DOWN_ANIM 1
#define ENABLE_HAT_XI_ANIM     1
#define ENABLE_BEE_ANIM        1
#define ENABLE_ANGRY_2_ANIM    1
#define ENABLE_ANGRY_3_ANIM    1
#define ENABLE_ANGRY_ANIM      1
#define ENABLE_EYE_GOL_ANIM    1
#define ENABLE_CRY_2_ANIM      1
#define ENABLE_CRY_ANIM        1
#define ENABLE_LAUGH_ANIM      1
#define ENABLE_LAUGH_2_ANIM    1
#define ENABLE_DASAI_ANIM      1
#define ENABLE_TORCH_NEW_ANIM  1
#define ENABLE_EVIL_ANIM       1
#define ENABLE_EVIL_2_ANIM     1
#define ENABLE_DISTRACTED_ANIM 1
#define ENABLE_HAPPY_ANIM      1
#define ENABLE_SNEEZE_ANIM     1
#define ENABLE_VISUALIZER_ANIM 1
#define ENABLE_LOVE_ANIM       1
#define ENABLE_HEHE_ANIM       1
#define ENABLE_MOCHI_ANIM      1
#define ENABLE_NEON_ANIM       1
#define ENABLE_YAWN_ANIM       1
#define ENABLE_FAT_EYE_ANIM    1
#define ENABLE_RIGHT_EYE_ANIM  1
#define ENABLE_LEFT_EYE_ANIM   1
#define ENABLE_UP_EYE_ANIM     1
#define ENABLE_DOWN_EYE_ANIM   1
#define ENABLE_PINGPONG_2_ANIM 1
#define ENABLE_SAKURA_ANIM     1
#define ENABLE_SNEEZE_2_ANIM   1

#endif // SETTINGS_H