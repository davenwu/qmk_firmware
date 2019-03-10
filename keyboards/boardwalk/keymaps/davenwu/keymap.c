#include QMK_KEYBOARD_H

void update_gaming_layer(void);

// Layer shorthand
enum layer {
  _BASE,
  _FN,
  _GN,
  _GAMING
};

enum custom_keycodes {
  FN = SAFE_RANGE,
  GN
};

#define TASK LCTL(LSFT(KC_ESC))
#define QUIT LALT(KC_F4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_hhkb(
  KC_MINS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,  KC_CAPS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,  \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PSCR, KC_BSLS, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_PGDN, KC_PGUP, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
           GN,      KC_LGUI, KC_LALT, KC_LCTL,      KC_SPC,           KC_LSFT,     FN,      KC_RGUI, KC_RALT, KC_RCTL
  ),

  [_FN] = LAYOUT_ortho_hhkb(
  KC_F11 , KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
  _______, QUIT,    KC_UP,   _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_DEL,  \
  TASK,    KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_END,  KC_HOME, _______, _______, _______, _______, _______, KC_INS,  \
           _______, _______, _______, _______,       _______,       _______,       _______, _______, _______, _______
  ),

  [_GN] = LAYOUT_ortho_hhkb(
  _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, RGB_SAI, RGB_HUI, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, \
           _______, _______, _______, _______,       _______,       _______,       _______, _______, _______, _______
  ),

  [_GAMING] = LAYOUT_ortho_hhkb(
  KC_GRV,  _______, _______, _______, _______, _______, KC_MINS, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
           _______, _______, _______, KC_SPC,        _______,       KC_ESC,        _______, _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
      } else {
        layer_off(_FN);
      }
      update_gaming_layer();
      return false;
      break;
    case GN:
      if (record->event.pressed) {
        layer_on(_GN);
      } else {
        layer_off(_GN);
      }
      update_gaming_layer();
      return false;
      break;
    default:
      return true;
  }
}

void update_gaming_layer() {
  if (IS_LAYER_ON(_FN) && IS_LAYER_ON(_GN)) {
    layer_invert(_GAMING);
  }
}
