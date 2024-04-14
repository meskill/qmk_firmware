SRC += features/lang_word.c
SRC += features/process_lang_word.c
SRC += features/lang_switch.c
SRC += macro.c
SRC += mod_tap.c
SRC += mod_hold.c
SRC += tap_dance.c
SRC += rgb.c

CONVERT_TO=liatris

OLED_ENABLE = false
ENCODER_ENABLE = false     # Enables the use of one or more encoders
RGB_MATRIX_ENABLE = no     # Disable keyboard RGB matrix, as it is enabled by default on rev3
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
WS2812_DRIVER = vendor 		 # Use the RP2040's PIO interface

KEY_OVERRIDE_ENABLE = yes
COMBO_ENABLE = yes
SWAP_HANDS_ENABLE = yes
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes

CONSOLE_ENABLE = yes