/* Copyright
 *   2021 solartempest
 *   2021 QMK
 *   2021 Luna code adapted from HellSingCoder and Jackasaur
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <stdio.h> //This is required for OLED sprintf.
//#include "oled.c" //Skip stock OLED code for Luna
#include "encoder.c"

#ifdef RGBLIGHT_ENABLE
	extern rgblight_config_t rgblight_config; // To pull layer status for RGBLIGHT
#endif


bool is_alt_tab_active = false; // Super Alt Tab Code
uint16_t alt_tab_timer = 0;
bool is_window_move_active = false; // Move Window Code
uint16_t move_window_timer = 0;
#ifdef VIA_ENABLE
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = USER00, //Alt tab forwards
	  ATABR, //Alt tab reverse
	  NMR, //Move window to monitor on right
	  NML //Move window to monitor on left
	};
#else
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = SAFE_RANGE, //Alt tab forwards
	  ATABR, //Alt tab reverse
	  NMR, //Move window to monitor on right
	  NML //Move window to monitor on left
	};
#endif


#ifdef COMBO_ENABLE
	enum combo_events {
	  sbs_delword
	};

	const uint16_t PROGMEM delword_combo[] = {KC_LSFT, KC_BSPC, COMBO_END};

	combo_t key_combos[COMBO_COUNT] = {
	  [sbs_delword] = COMBO_ACTION(delword_combo)
	};

	void process_combo_event(uint16_t combo_index, bool pressed) {
	  switch(combo_index) {
		case sbs_delword:
		  if (pressed) {
			tap_code16(LCTL(KC_BSPC));
		  }
		  break;
	  }
	}
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Enc  |    |  Enc  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[0] = LAYOUT(
  KC_GRV,	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,						KC_6,	KC_7,	KC_8,	KC_9,	KC_0,		KC_MINS,
  KC_ESC,	KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC__VOLUP,	KC_PGUP,KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,		KC_BSPC,
  KC_TAB,	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_MUTE,	KC_NO,	KC_H,	KC_J,	KC_K,	KC_L,	KC_SCLN,	KC_QUOT,
  KC_LSFT,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC__VOLDOWN,KC_PGDN,KC_N,	KC_M,	KC_COMM,KC_DOT,	KC_SLSH,	KC_RSFT,
					KC_LGUI,KC_LALT,KC_LCTRL,MO(2),	KC_ENT,		KC_SPC,	MO(3),	KC_RCTRL,KC_RALT,KC_RGUI
),
[1] = LAYOUT(
  KC_PSCR,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
  KC_TRNS,	KC_T,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_BSPC,
  KC_TRNS,	KC_G,		KC_A,		KC_S,		KC_D,		KC_F,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
  KC_TRNS,	KC_B,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
						KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_PAUS,	KC_SPACE,	KC_TRNS,	MO(3),		KC_TRNS,	KC_TRNS,	KC_TRNS
),
[2] = LAYOUT(
  KC_TRNS,	KC_F1,	KC_F2,	KC_F3,	KC_F4,	KC_F5,							KC_F6,	KC_F7,	KC_F8,	KC_F9,	KC_F10,		KC_F11,
  KC_GRV,	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	KC_TRNS,		KC_TRNS,KC_6,	KC_7,	KC_8,	KC_9,	KC_0,		KC_F12,
  KC_TRNS,	KC_EXLM,KC_AT,	KC_HASH,KC_DLR,	KC_PERC,KC_TRNS,		KC_TRNS,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,	KC_PIPE,
  KC_TRNS,	KC_EQL,	KC_MINS,KC_PLUS,KC_LCBR,KC_LCBR,KC_TRNS,		KC_TRNS,KC_LBRC,KC_RBRC,KC_DOT,	KC_COLN,KC_BSLS,	KC_TRNS,
					KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,		KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
),
[3] = LAYOUT(
  KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
  KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_HOME,	KC_UP,		KC_END,		KC_INS,		KC_DEL,
  KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_TRNS,	KC_TRNS,
  KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_CAPS,	KC_PGUP,	KC_TRNS,	KC_PGDN,	KC_TRNS,	KC_TRNS,
						KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS
)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	switch (id) {
	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (is_window_move_active) {
    if (timer_elapsed(move_window_timer) > 1000) {
      unregister_code(KC_LSFT);
      unregister_code(KC_LWIN);
      is_window_move_active = false;
    }
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) { //For super alt tab keycodes
	case ATABF:	//Alt tab forwards
	  if (record->event.pressed) {
		if (!is_alt_tab_active) {
		  is_alt_tab_active = true;
		  register_code(KC_LALT);
		}
		alt_tab_timer = timer_read();
		register_code(KC_TAB);
	  } else {
		unregister_code(KC_TAB);
	  }
	  break;
	case ATABR:	//Alt tab reverse
	  if (record->event.pressed) {
		if (!is_alt_tab_active) {
		  is_alt_tab_active = true;
		  register_code(KC_LALT);
		}
		alt_tab_timer = timer_read();
		register_code(KC_LSHIFT);
		register_code(KC_TAB);
	  } else {
		unregister_code(KC_LSHIFT);
		unregister_code(KC_TAB);
	  }
	  break;
	  	case NMR:	//Move window to next monitor on right
	  if (record->event.pressed) {
		if (!is_window_move_active) {
		  is_window_move_active = true;
		  register_code(KC_LSFT);
		  register_code(KC_LWIN);
		}
		move_window_timer = timer_read();
		register_code(KC_RIGHT);
	  } else {
		unregister_code(KC_RIGHT);
	  }
	  break;
	case NML:	//Move window to next monitor on left
	  if (record->event.pressed) {
		if (!is_window_move_active) {
		  is_window_move_active = true;
		  register_code(KC_LSFT);
		  register_code(KC_LWIN);
		}
		move_window_timer = timer_read();
		register_code(KC_LSHIFT);
		register_code(KC_LEFT);
	  } else {
		unregister_code(KC_LEFT);
	  }
	  break;
	}
	return true;
}


// RGB Layer Light Settings - Note that this will fix the key switch LED colour and brightness
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 95,255,90}); //Spring green		(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 30,255,120}); //Yellow-orange	(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 128,255,100}); //Cyan			(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 215,255,120}); //Magenta		(Code is extra for static key lighting of layers)
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 3, 43,100,160}); //White-left caps lock indication (No dedicated LED)
const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS({28, 3, 43,100,150}); //White-right num lock indication (No dedicated LED). Since this indicator is inverted, it must be on the master side of the keyboard to shut off properly when the computer is sleeping.
const rgblight_segment_t PROGMEM my_scrollock_layer[] = RGBLIGHT_LAYER_SEGMENTS({55, 3, 43,100,160}); //White-middle-right scroll lock indication (No dedicated LED)


const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST( //Lighting layers
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
	my_capslock_layer,    //Highest status indicators override other layers
	my_numlock_layer,
	my_scrollock_layer
);


void keyboard_post_init_user(void)
{
    rgblight_layers = my_rgb_layers;// Enable the LED layers
	rgblight_enable();
	rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT+8); //Set to static gradient 9
	rgblight_sethsv_noeeprom(50, 255, 80); //Set default brightness when connected
	layer_move(0); //start on layer 0 to get the lighting activated
}


layer_state_t layer_state_set_user(layer_state_t state)
{
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));    // Multiple layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
	
	switch(biton32(state)){ // Change all other LEDs based on layer state as well
		case 0:
			rgblight_enable_noeeprom();
			rgblight_sethsv_noeeprom(50,255,80);
			break;
		case 1:
			rgblight_enable_noeeprom();
			rgblight_sethsv_noeeprom(8,255,80);
			break;
		case 2:
			rgblight_enable_noeeprom();	
			rgblight_sethsv_noeeprom(118,255,80);
			break;
		case 3:
			rgblight_enable_noeeprom();
			rgblight_sethsv_noeeprom(218,255,80);
			break;
		default:
			rgblight_enable_noeeprom();
			rgblight_sethsv_noeeprom(64,255,80);
	  }
    return state;
}


bool led_update_user(led_t led_state)
{
	rgblight_set_layer_state(4, led_state.caps_lock); //Activate capslock lighting layer
	rgblight_set_layer_state(5, !(led_state.num_lock)); //Invert the indication so numlock does not always appear "on".
	rgblight_set_layer_state(6, led_state.scroll_lock); //Activate scrollock lighting layer
    return true;
}



//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE
	/* KEYBOARD PET START */
	 
	/* settings */
	#define MIN_WALK_SPEED 10
	#define MIN_RUN_SPEED 40
	 
	/* advanced settings */
	#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
	#define ANIM_SIZE 96 // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024
	 
	/* timers */
	uint32_t anim_timer = 0;
	uint32_t anim_sleep = 0;
	 
	/* current frame */
	uint8_t current_frame = 0;
	 
	/* status variables */
	int current_wpm = 0;
	led_t led_usb_state;
	 
	bool isSneaking = false;
	bool isJumping = false;
	bool showedJump = true;
	bool isBarking = false;
	 
	 
	/* logic */
	static void render_luna(int LUNA_X, int LUNA_Y) {
	 
		/* Sit */
		static const char PROGMEM sit[2][ANIM_SIZE] = {
			/* 'sit1', 32x22px */
			{
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
				0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
				0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			},
	 
			/* 'sit2', 32x22px */
			{
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
				0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
				0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			}
		};
	 
		/* Walk */
		static const char PROGMEM walk[2][ANIM_SIZE] = {
			/* 'walk1', 32x22px */
			{
				0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80,
				0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
				0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03,
				0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			},
	 
			/* 'walk2', 32x22px */
			{
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
				0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
				0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e,
				0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			}
		};
	 
		/* Run */
		static const char PROGMEM run[2][ANIM_SIZE] = {
			/* 'run1', 32x22px */
			{
				0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
				0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01,
				0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
			},
	 
			/* 'run2', 32x22px */
			{
				0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
				0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37,
				0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			}
		};
	 
		/* Bark */
		static const char PROGMEM bark[2][ANIM_SIZE] = {
			/* 'bark1', 32x22px */
			{
				0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
				0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
				0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			},
	 
			/* 'bark2', 32x22px */
			{
				0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
				0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
				0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			}
		};
	 
		/* Sneak */
		static const char PROGMEM sneak[2][ANIM_SIZE] = {
			/* 'sneak1', 32x22px */
			{
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04,
				0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06,
				0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
			},
	 
			/* 'sneak2', 32x22px */
			{
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04,
				0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04,
				0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
			}
		};
	 
		/* animation */
		void animate_luna(void) {
	 
			/* jump */
			if (isJumping || !showedJump) {
	 
				/* clear */
				oled_set_cursor(LUNA_X,LUNA_Y +2);
				oled_write("     ", false);
	 
				oled_set_cursor(LUNA_X,LUNA_Y -1);
	 
				showedJump = true;
			} else {
	 
				/* clear */
				oled_set_cursor(LUNA_X,LUNA_Y -1);
				oled_write("     ", false);
	 
				oled_set_cursor(LUNA_X,LUNA_Y);
			}
	 
			/* switch frame */
			current_frame = (current_frame + 1) % 2;
	 
			/* current status */
			if(isBarking) {
				oled_write_raw_P(bark[abs(1 - current_frame)], ANIM_SIZE);
	 
			} else if(isSneaking) {
				oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);
	 
			} else if(current_wpm <= MIN_WALK_SPEED) {
				oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);
	 
			} else if(current_wpm <= MIN_RUN_SPEED) {
				oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);
	 
			} else {
				oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
			}
		}
	 
		/* animation timer */
		if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
			anim_timer = timer_read32();
			animate_luna();
		}
	 
		/* this fixes the screen on and off bug */
		if (current_wpm > 0) {
			oled_on();
			anim_sleep = timer_read32();
		} else if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
			oled_off();
		}
	 
	}
	 
	/* KEYBOARD PET END */

	static void print_logo_narrow(void) {
		/* wpm counter */
		char wpm_str[8];
		oled_set_cursor(0,8);
		sprintf(wpm_str, " %03d", current_wpm);
		oled_write(wpm_str, false);
	 
		oled_set_cursor(0,9);
		oled_write(" wpm", false);
	}
	 
	static void print_status_narrow(void) {
		oled_set_cursor(0,3);
	 
		switch (get_highest_layer(default_layer_state)) {
			case 0:
				oled_write("QWRTY", false);
				break;
			case 1:
				oled_write("GAME", false);
				break;
			default:
				oled_write("UNDEF", false);
		}
	 
		oled_set_cursor(0,5);
	 
		/* Print current layer */
		oled_write("LAYER", false);
	 
		oled_set_cursor(0,6);
	 
		switch (get_highest_layer(layer_state)) {
			case 0:
				oled_write("Base ", false);
				break;
			case 1:
				oled_write("Game", false);
				break;
			case 3:
				oled_write("Raise", false);
				break;
			case 2:
				oled_write("Lower", false);
				break;
		}
	 
		/* caps lock */
		oled_set_cursor(0,8);
		oled_write("Doge", led_usb_state.caps_lock);
	 
		/* KEYBOARD PET RENDER START */
		render_luna(0,13);
		/* KEYBOARD PET RENDER END */
	}
	 
	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		return OLED_ROTATION_270;
	}
	 
	void oled_task_user(void) {
		/* KEYBOARD PET VARIABLES START */
		current_wpm = get_current_wpm();
		led_usb_state = host_keyboard_led_state();
	 
		/* KEYBOARD PET VARIABLES END */
		if (is_keyboard_master()) {
			print_status_narrow();
		} else {
			print_logo_narrow();
		}
	}
#endif
