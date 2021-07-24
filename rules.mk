MCU = atmega32u4
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.

SPLIT_KEYBOARD = yes	# Split keyboard
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
CONSOLE_ENABLE = no		# Console for debug
MOUSEKEY_ENABLE = yes	# Mouse keys(+1482)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
RGBLIGHT_ENABLE = yes	# RGB lighting
NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
ENCODER_ENABLE = yes	# Encoders
OLED_DRIVER_ENABLE = no # Must be disabled if OLEDs are not installed(+3608)
TAP_DANCE_ENABLE = no	# Tap dance(+1060)
LTO_ENABLE = yes		# Save space
