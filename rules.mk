MCU = atmega32u4
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.

SPLIT_KEYBOARD = yes	# Split keyboard
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = no		# Console for debug(+400)
COMMAND_ENABLE = no     # Commands for debug and configuration
RGBLIGHT_ENABLE = yes	# RGB LEDs
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
AUDIO_ENABLE = no		# No audio
KEY_LOCK_ENABLE = no	# Key lock functionality
ENCODER_ENABLE = yes	# Encoders
OLED_DRIVER_ENABLE = no # Must be disabled if OLEDs are not installed
LTO_ENABLE = yes		# Save space

FAUXCLICKY_ENABLE = no
MIDI_ENABLE = no
BLUETOOTH_ENABLE = no
TERMINAL_ENABLE = no
LEADER_ENABLE = no
