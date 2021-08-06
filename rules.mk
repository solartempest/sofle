MCU = atmega32u4
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.

SPLIT_KEYBOARD = yes	# Split keyboard
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
CONSOLE_ENABLE = no		# Console for debug
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
RGBLIGHT_ENABLE = yes	# RGB lighting
ENCODER_ENABLE = yes	# Encoders
COMBO_ENABLE = yes      # Tap combo chording (+952)
LTO_ENABLE = yes		# Save space

OLED_DRIVER_ENABLE = no # Must be disabled if OLEDs are not installed(+3608)
WPM_ENABLE = yes		# For OLED WPM counter
MOUSEKEY_ENABLE = no	# Mouse keys(+1482)
NKRO_ENABLE = no		# Has 6KRO+ already. NKRO did not work.
