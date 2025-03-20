#include QMK_KEYBOARD_H

const uint16_t PROGMEM combo_LPRN[] = {LALT_T(KC_R), LCTL_T(KC_S), COMBO_END};
const uint16_t PROGMEM combo_RPRN[] = {LCTL_T(KC_S), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM combo_LCBR[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_RCBR[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_LBRC[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_RBRC[] = {KC_C, KC_D, COMBO_END};

const uint16_t PROGMEM combo_BSLS[] = {KC_Y, KC_QUOT, COMBO_END};
const uint16_t PROGMEM combo_SCLN[] = {RALT_T(KC_I), RGUI_T(KC_O), COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_LPRN, KC_LPRN), // (
    COMBO(combo_RPRN, KC_RPRN), // )
    COMBO(combo_LCBR, KC_LCBR), // {
    COMBO(combo_RCBR, KC_RCBR), // }
    COMBO(combo_LBRC, KC_LBRC), // [
    COMBO(combo_RBRC, KC_RBRC), // ]
    
    COMBO(combo_BSLS, KC_BSLS), // "\"
    COMBO(combo_SCLN, KC_SCLN), // :
    
};

// ##################################################
// Keymap
// ##################################################
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Colemak-dh
    [0] = LAYOUT_split_3x5_2(   KC_Q, KC_W, KC_F, KC_P, KC_B,                                               KC_J, KC_L, KC_U, KC_Y, KC_QUOT, 
                                LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,               KC_M, LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), 
                                KC_Z, KC_X, KC_C, KC_D, KC_V,                                               KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, 
                                LT(1,KC_TAB), LT(2,KC_SPC),                                                 LT(2,KC_ENT), LT(1,KC_BSPC)),
    // Navigation
    [1] = LAYOUT_split_3x5_2(   KC_ESC, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO,                          KC_INS, KC_HOME, KC_UP, KC_END, KC_PGUP, 
                                LGUI_T(KC_NO), LALT_T(KC_NO), LCTL_T(KC_NO), LSFT_T(KC_NO), KC_NO,          KC_DEL, RSFT_T(KC_LEFT), RCTL_T(KC_DOWN), RALT_T(KC_RGHT), RGUI_T(KC_PGDN), 
                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                          KC_APP, LCA(KC_LEFT), KC_NO, LCA(KC_RGHT), KC_PSCR, 
                                KC_NO, KC_NO,                                                               KC_NO, KC_NO),
    // Numbers
    [2] = LAYOUT_split_3x5_2(   KC_1, KC_2, KC_3, KC_4, KC_5,                                               KC_6, KC_7, KC_8, KC_9, KC_0, 
                                LGUI_T(KC_NO), LALT_T(KC_NO), LCTL_T(KC_NO), LSFT_T(KC_NO), KC_LPRN,        KC_RPRN, RSFT_T(KC_MINS), RCTL_T(KC_EQL), RALT_T(KC_BSLS), RGUI_T(KC_SCLN),
                                KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_TILD,                                    KC_GRV, KC_LBRC, KC_RBRC, KC_COMM, KC_DOT,
                                KC_NO, KC_NO,                                                               KC_NO, OSL(3)),
    // Functions
    [3] = LAYOUT_split_3x5_2(   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                          KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 
                                LGUI_T(KC_F11), LALT_T(KC_F12), LCTL_T(KC_NO), LSFT_T(KC_NO), KC_NO,        KC_NO, RSFT_T(KC_NO), RCTL_T(KC_NO), RALT_T(KC_NO), RGUI_T(KC_NO),
                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                KC_NO, KC_NO,                                                               KC_NO, KC_NO),
                                                      
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

