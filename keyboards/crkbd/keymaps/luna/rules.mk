OLED_ENABLE = yes
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
# ENCODER_ENABLE = yes
# CONSOLE_ENABLE = yes
# EXTRAKEY_ENABLE = yes

WPM_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes

NO_USB_EXTRA = yes

LTO_ENABLE = yes

OPT_DEFS += -Os
OPT_DEFS += -flto
OPT_DEFS += -fdata-sections
OPT_DEFS += -ffunction-sections
