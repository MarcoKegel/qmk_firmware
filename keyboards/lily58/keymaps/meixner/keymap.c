#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


 [_QWERTY] = LAYOUT(
  KC_ESC,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                         KC_6,         KC_7,           KC_8,         KC_9,         KC_0,             KC_MINS,
  KC_TAB,       KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                         KC_Y,         KC_U,           KC_I,         KC_O,         KC_P,             KC_EQL,
  KC_NO,        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,                                         KC_H,         RSFT_T(KC_J),   RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN),  KC_NUHS,
  KC_NO,        KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,           KC_LBRC,        KC_RBRC,      KC_N,         KC_M,           KC_COMM,      KC_DOT,       KC_SLSH,          KC_RSFT,
                                            KC_NO,        KC_NO,        LT(1,KC_SPC),   KC_BSPC,        KC_ENT,       LT(1,KC_SPC), KC_NO,          KC_NO
),

[_LOWER] = LAYOUT(
  KC_ESC,       KC_F1,          KC_F2,          KC_F3,         KC_F4,         KC_F5,                                    KC_F6,        KC_F7,             KC_F8,            KC_F9,            KC_F10,           KC_F11,
  KC_TAB,       LCTL(KC_X),     LCTL(KC_C),     LCTL(KC_V),    KC_NO,         KC_NO,                                    KC_NO,        KC_HOME,           KC_UP,            KC_END,           KC_PGUP,          KC_F12,
  KC_NO,        LGUI_T(KC_NO),  LALT_T(KC_NO),  LCTL_T(KC_NO), LSFT_T(KC_NO), KC_NO,                                    KC_NO,        RSFT_T(KC_LEFT),   RCTL_T(KC_DOWN),  RALT_T(KC_RIGHT), RGUI_T(KC_PGDN),  KC_NO,
  KC_NO,        KC_NO,          KC_NO,          KC_NO,         KC_NO,         KC_NO,      KC_NO,         KC_NO,         KC_NO,        KC_NO,             KC_NO,            KC_NO,            KC_NO,            KC_NO,
                                                KC_NO,         KC_NO,         KC_SPC,     KC_BSPC,       KC_ENT,        KC_SPC,       KC_NO,             KC_NO
),


[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),

  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
