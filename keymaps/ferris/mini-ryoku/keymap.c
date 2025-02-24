#include QMK_KEYBOARD_H

// Remarks
// RALT is not the right-handed ALT it is the ALT-GR

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;



/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state);
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

//td_SingleTapFunction_SingleHoldFunction_DoubleTapFunction_DoubleHoldAction_TripleTap_TripleHold
enum {
    td_SPC_L1_na_L2_na_na,
    td_na_L3_na_L4_na_na,
    td_L3_L3,
    td_L4_L4,
    td_L0_RGUI,
    td_L1_RGUI,
    td_L2_RGUI,
    td_L3_RGUI,
    td_BracketLeft_RSHFT,
    td_BracketRight_RCTRL,
    };

// Functions that control what our tap dance key does
void td_SPC_L1_na_L2_na_na_finished(tap_dance_state_t *state, void *user_data);
void td_SPC_L1_na_L2_na_na_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(1);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_on(2);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default:
            break;
    }
}
void td_SPC_L1_na_L2_na_na_reset(tap_dance_state_t *state, void *user_data);
void td_SPC_L1_na_L2_na_na_reset(tap_dance_state_t *state, void *user_data) {
    
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_off(1);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_off(2);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_na_L3_na_L4_na_na_finished(tap_dance_state_t *state, void *user_data);
void td_na_L3_na_L4_na_na_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            layer_on(3);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_on(4);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default:
            break;
    }
}
void td_na_L3_na_L4_na_na_reset(tap_dance_state_t *state, void *user_data);
void td_na_L3_na_L4_na_na_reset(tap_dance_state_t *state, void *user_data) {
    
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            layer_off(3);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_off(4);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_L3_L3_finished(tap_dance_state_t *state, void *user_data);
void td_L3_L3_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_on(3);
            break;
        case TD_SINGLE_HOLD:
            layer_on(3);
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
}
void td_L3_L3_reset(tap_dance_state_t *state, void *user_data);
void td_L3_L3_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:            
            break;
        case TD_SINGLE_HOLD:
          layer_off(3);
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_L4_L4_finished(tap_dance_state_t *state, void *user_data);
void td_L4_L4_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_on(1);
            break;
        case TD_SINGLE_HOLD:
            layer_on(1);
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
}
void td_L4_L4_reset(tap_dance_state_t *state, void *user_data);
void td_L4_L4_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:            
            break;
        case TD_SINGLE_HOLD:
          layer_off(4);
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_L0_RGUI_finished(tap_dance_state_t *state, void *user_data);
void td_L0_RGUI_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_clear();
            layer_on(0);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RIGHT_GUI));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
}
void td_L0_RGUI_reset(tap_dance_state_t *state, void *user_data);
void td_L0_RGUI_reset(tap_dance_state_t *state, void *user_data) {
        switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:            
            break;
        case TD_SINGLE_HOLD:
          unregister_mods(MOD_BIT(KC_RIGHT_GUI));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_L1_RGUI_finished(tap_dance_state_t *state, void *user_data);
void td_L1_RGUI_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_clear();
            layer_on(1);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RIGHT_GUI));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
}
void td_L1_RGUI_reset(tap_dance_state_t *state, void *user_data);
void td_L1_RGUI_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:            
            break;
        case TD_SINGLE_HOLD:
          unregister_mods(MOD_BIT(KC_RIGHT_GUI));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_L2_RGUI_finished(tap_dance_state_t *state, void *user_data);
void td_L2_RGUI_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_clear();
            layer_on(2);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RIGHT_GUI));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
}
void td_L2_RGUI_reset(tap_dance_state_t *state, void *user_data);
void td_L2_RGUI_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:            
            break;
        case TD_SINGLE_HOLD:
          unregister_mods(MOD_BIT(KC_RIGHT_GUI));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_L3_RGUI_finished(tap_dance_state_t *state, void *user_data);
void td_L3_RGUI_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_clear();
            layer_on(3);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RIGHT_GUI));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
}
void td_L3_RGUI_reset(tap_dance_state_t *state, void *user_data);
void td_L3_RGUI_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:            
            break;
        case TD_SINGLE_HOLD:
          unregister_mods(MOD_BIT(KC_RIGHT_GUI));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_BracketLeft_RSHFT_finished(tap_dance_state_t *state, void *user_data);
void td_BracketLeft_RSHFT_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_9));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RIGHT_SHIFT));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
}
void td_BracketLeft_RSHFT_reset(tap_dance_state_t *state, void *user_data);
void td_BracketLeft_RSHFT_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
  switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_9));
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RIGHT_SHIFT));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

void td_BracketRight_RCTRL_finished(tap_dance_state_t *state, void *user_data);
void td_BracketRight_RCTRL_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(LSFT(KC_0));
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RIGHT_CTRL));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
}
void td_BracketRight_RCTRL_reset(tap_dance_state_t *state, void *user_data);
void td_BracketRight_RCTRL_reset(tap_dance_state_t *state, void *user_data) {
   // If the key was held down and now is released then switch off the layer
  switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_0));
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RIGHT_CTRL));
            break;
        case TD_DOUBLE_TAP:            
        default:
            break;
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [td_SPC_L1_na_L2_na_na] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_SPC_L1_na_L2_na_na_finished, td_SPC_L1_na_L2_na_na_reset),
    [td_na_L3_na_L4_na_na] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_na_L3_na_L4_na_na_finished, td_na_L3_na_L4_na_na_reset),
    [td_L3_L3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,td_L3_L3_finished, td_L3_L3_reset),
    [td_L4_L4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,td_L4_L4_finished, td_L4_L4_reset),
    [td_L0_RGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_L0_RGUI_finished,td_L0_RGUI_reset),
    [td_L1_RGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_L1_RGUI_finished,td_L1_RGUI_reset),
    [td_L2_RGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,td_L2_RGUI_finished,td_L2_RGUI_reset),
    [td_L3_RGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,td_L3_RGUI_finished,td_L3_RGUI_reset),
    [td_BracketLeft_RSHFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_BracketLeft_RSHFT_finished, td_BracketLeft_RSHFT_reset),
    [td_BracketRight_RCTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_BracketRight_RCTRL_finished, td_BracketRight_RCTRL_reset),
};

// ##################################################
// Keymap
// ##################################################
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Colemak-dh
    [0] = LAYOUT_split_3x5_2(   KC_Q, KC_W, KC_F, KC_P, KC_B,                                               KC_J, KC_L, KC_U, KC_Y, KC_QUOT, 
                                LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,               KC_M, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O), 
                                KC_Z, KC_X, KC_C, KC_D, KC_V,                                               KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, 
                                LT(1,KC_TAB), LT(2,KC_SPC),                                                 LT(2,KC_BSPC), LT(1,KC_ENT)),
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

