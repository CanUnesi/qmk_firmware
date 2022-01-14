/*
Copyright 2020 Dimitris Mantzouranis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _LALT,
    _LCTL,
};

enum custom_keycodes {
    MY_LALT = SAFE_RANGE,
    MY_LCTL,
};

bool ctrl_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_LALT:
            if (ctrl_active) {
                if (record->event.pressed) {
                    register_code(KC_LALT);
                } else {
                    unregister_code(KC_LALT);
                }
            } else {
                if (record->event.pressed) {
                    layer_on(_LALT);
                    register_code(KC_LALT);
                } else {
                    layer_off(_LALT);
                    unregister_code(KC_LALT);
                }
            }
            break;

        case MY_LCTL:
            if (record->event.pressed) {
                ctrl_active = true;
                layer_on(_LCTL);
                register_code(KC_LCTL);
            } else {
                ctrl_active = false;
                layer_clear();
                unregister_code(KC_LCTL);
            }
            break;
    }

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /*      Row:         0                    1          2          3          4          5          6         7          8           9          10          11         12          13           14         15         */
      [_BASE] = { {   KC_GESC,             KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,     KC_7,      KC_8,       KC_9,      KC_0,       KC_MINS,   KC_EQL,     KC_BSPC,     KC_NO,     KC_PGUP     },
                  {   KC_TAB,              KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,     KC_U,      KC_I,       KC_O,      KC_P,       KC_LBRC,   KC_RBRC,    KC_BSLASH,   KC_NO,     KC_PGDN     },
                  {   LT(_FN1, KC_CAPS),   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,     KC_J,      KC_K,       KC_L,      KC_SCLN,    KC_QUOT,   KC_NO,      KC_ENT,      KC_NO,     KC_DEL      },
                  {   KC_LSFT,             KC_NO,     KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,     KC_N,      KC_M,       KC_COMM,   KC_DOT,     KC_SLSH,   KC_NO,      KC_NUBS,     KC_UP,     KC_END      },
                  {   MY_LCTL,             KC_LGUI,   MY_LALT,   KC_NO,     KC_NO,     KC_NO,     KC_SPC,   KC_NO,     KC_NO,      KC_NO,     KC_RCTL,    KC_RGUI,   MO(_FN2),   KC_LEFT,     KC_DOWN,   KC_RGHT     }
                },
      [_FN1] = {  {   KC_ESC,              KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,     KC_F11,    KC_F12,     _______,     _______,   _______     },
                  {   _______,             _______,   KC_UP,     _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             KC_LEFT,   KC_DOWN,   KC_RGHT,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     }
               },
      [_FN2] = {  {   RESET,               _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   KC_SLCK     },
                  {   _______,             RGB_HUI,   RGB_SAI,   RGB_VAI,   RGB_MOD,   RGB_SPI,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   KC_PAUS      },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    KC_MPLY,     _______,   KC_INS      },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     KC_VOLU,   KC_HOME     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   KC_MPLY,   _______,   _______,   _______,   KC_PSCR,    RGB_TOG,   _______,    KC_MPRV,     KC_VOLD,   KC_MNXT,    }
               },
     [_LALT] = {  {   _______,             _______,   _______,   _______,   KC_F4,     _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     }
               },
     [_LCTL] = {  {   KC_ESC,              _______,   _______,   _______,   KC_4,      _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     },
                  {   _______,             _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,    _______,     _______,   _______     }
               }
};

void dip_switch_update_user(uint8_t index, bool active){
    switch(index){
        case 0: // macos/windows togggle
            if(active){ //macos
                // layer_off(_WINDOWS);
                // layer_on(_MAC);
            }
            else{ //windows
                // layer_on(_WINDOWS);
                // layer_off(_MAC);
            }
        break;
    }
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
