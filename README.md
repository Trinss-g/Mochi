# Mochi OLED Display

A lightweight animation and text display engine for the **Seeed Studio XIAO ESP32C3** using a 128x64 SH1106 OLED.

## 🛠 Hardware Setup

- **Microcontroller**: Seeed Studio XIAO ESP32C3
- **Display**: 128x64 SH1106 OLED (I2C)

| OLED Pin | XIAO Pin | Function |
| :--- | :--- | :--- |
| VCC | 3V3 | Power |
| GND | GND | Ground |
| SDA | GPIO 8 | I2C Data |
| SCL | GPIO 9 | I2C Clock |

## 🚀 Quick Start

1.  **Install PlatformIO**: Ensure you have the PlatformIO extension installed in VS Code.
2.  **Clone the Project**:
    ```bash
    git clone <repository-url>
    ```
3.  **Build & Upload**:
    - Connect your XIAO ESP32C3 via USB.
    - Click the **PlatformIO: Upload** button (arrow icon) in the status bar.

## ⚙️ Configuration

Most settings are centralized in `include/settings.h`.

### Change the Message
Update the `MAIN_MESSAGE` macro:
```cpp
#define MAIN_MESSAGE "Hello Mochi!"
```

### Toggle Animations
Enable or disable specific animations to save memory:
```cpp
#define ENABLE_BIG_EYE_ANIM 1  // 1 = On, 0 = Off
```

### Adjust Speed
Change the global animation frame delay:
```cpp
#define ANIM_DELAY_DEFAULT 70 // ms
```

## 📂 Project Structure

```
Mochi_test/
├── include/                 # Animation header files and settings
│   ├── settings.h          # Configuration file for all display and animation settings
│   ├── settings_display.h  # Display hardware settings
│   ├── bigeye_anim.h       # Big eye animation frames
│   ├── hat_xi_anim.h       # Hat animation frames
│   ├── speedometer_anim.h  # Speedometer animation frames
│   ├── Ten_anim.h          # "Ten" animation frames
│   ├── next10_anim.h       # "Next 10" animation frames
│   ├── rest_anim.h         # "Rest" animation frames
│   ├── text_anim.h         # Text animation functions
│   ├── torchsearch_anim.h  # Torch search animation frames
│   ├── tounge_anim.h       # Tongue animation frames
│   └── upside_down_anim.h  # Upside down animation frames
├── lib/                    # Local libraries (empty)
├── src/                    # Source code
│   ├── main.cpp           # Main application logic
│   ├── settings_display.cpp # Display settings implementation
│   └── text_anim.cpp      # Text animation implementation
├── test/                   # Test files (empty)
├── partitions.csv         # Custom partition table for full flash
├── platformio.ini         # PlatformIO configuration
└── README.md              # This file
```

## 🎨 Customization

### Settings Configuration

All display and animation settings are centralized in `include/settings.h`. This file contains:

- **Display Settings**: I2C pins, resolution, fonts, rotation
- **Animation Settings**: Single default timing delay for all animations
- **Text Animation**: Cursor blink rate, typing speed, layout padding
- **Welcome Screen**: Greeting text and positioning
- **Animation Control**: Enable/disable individual animations

### Modifying Settings

Edit `include/settings.h` to customize:

```cpp
// Change display pins
#define DISPLAY_I2C_SDA        8
#define DISPLAY_I2C_SCL        9

// Adjust animation speed (affects all animations)
#define ANIM_DELAY_DEFAULT     70  // milliseconds

// Enable/disable animations
#define ENABLE_BIG_EYE_ANIM    1   // 1 = enabled, 0 = disabled
#define ENABLE_PING_PONG_ANIM  1   // 1 = enabled, 0 = disabled
#define ENABLE_SPEEDOMETER_ANIM 1  // 1 = enabled, 0 = disabled
#define ENABLE_BEE_ANIM        1   // 1 = enabled, 0 = disabled

// Change text message
#define MAIN_MESSAGE           "Your custom message here"
```

### Adding New Animations

1. Create animation frames as XBM bitmaps
2. Add them to a new header file in `include/`
3. Include the header in `main.cpp`
4. Add an `ENABLE_...` macro in `settings.h`
5. Add the animation entry to the `animations[]` array in `main.cpp`

Example:
```cpp
// In main.cpp
Animation animations[] = {
  // ... existing entries
  #if ENABLE_MY_ANIM
  {my_anim_frames, my_anim_LEN, "My New Anim"},
  #endif
};
```

## 🔧 Technical Details

### Memory Optimization
- Custom partition table maximizes available flash (4MB)
- Optimized string handling reduces heap fragmentation
- Efficient bitmap rendering for smooth animations

### Display Configuration
- Resolution: 128x64 pixels
- Controller: SH1106
- Interface: I2C
- Font: u8g2_font_8x13_tf for text, various for UI

### Performance
- Frame rate: Optimized for smooth 60-120ms animations
- Memory usage: ~5% RAM, ~80% Flash
- Power efficient for battery-powered applications

## 🤝 Contributing

Feel free to contribute by:
- Adding new animation sequences
- Improving text animation effects
- Optimizing memory usage
- Adding new display effects

## 📄 License

This project is licensed under the MIT License.

## 🙏 Acknowledgments

- **U8G2 Library**: Excellent OLED display library by Oliver Kraus
- **PlatformIO**: Making embedded development easier
- **Seeed Studio**: For the awesome XIAO ESP32C3 board

## 📞 Support

If you encounter any issues or have questions:
1. Check the PlatformIO console for error messages
2. Verify hardware connections
3. Ensure the correct board is selected in `platformio.ini`

---

**Made with ❤️ for creative OLED projects**