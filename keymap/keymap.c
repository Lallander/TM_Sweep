#include QMK_KEYBOARD_H

#define LAYOUT LAYOUT_split_3x5_2

// Left-hand home row mods Gallium
#define GUI_N LGUI_T(KC_N)
#define ALT_R LALT_T(KC_R)
//#define CTL_T LCTL_T(KC_T)
#define SHFT_S LSFT_T(KC_S)

// Right-hand home row mods Gallium 
#define SFT_H RSFT_T(KC_H)
#define CTL_A RCTL_T(KC_A)
#define ALT_E RALT_T(KC_E)
#define GUI_I RGUI_T(KC_I)

 enum layer_number {
  _GALLIUM = 0, 
  _NAV,
  _SYM,
  _FUNC,
  _MOUSE,
  _GAMES,
  _QWERTY, 
};   

#include "g/keymap_combo.h"

enum custom_keycodes{
  _SCREEN = SAFE_RANGE,
  _MAIL,
  _Scope,
  _Arrow,
  _NCount,
  _DollarBracks
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Base layer
  [_GALLIUM] = LAYOUT(
    KC_B,    KC_L,    KC_D,    KC_C,    KC_V,                      KC_J,    KC_F,    KC_O,    KC_U,    KC_QUOT,  
    GUI_N,   ALT_R,    LCTL_T(KC_T),    SHFT_S,    KC_G,           KC_Y,    SFT_H,    CTL_A,    ALT_E,   GUI_I,  
    KC_X,    KC_Q,    KC_M,    KC_W,    KC_Z,  					   KC_K,    KC_P,    KC_COMMA,  KC_DOT, KC_SLSH,  
                      			LT(_NAV, KC_DEL), QK_REP,        KC_SPC,  LT(_SYM, KC_BSPC)
),

//Nav layer
  [_NAV] = LAYOUT(
	KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY,        XXXXXXX, KC_PGUP, KC_UP, KC_PGDN, XXXXXXX,  
	KC_1,  KC_2, LALT_T(KC_3), LSFT_T(KC_4), KC_5,      XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT,KC_ENT, 
	KC_0, KC_9, KC_8,  KC_7, KC_6,             			XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, TG(_MOUSE), 
							_______, _______, 		     _______, _______
),

  // Symbols layer
  [_SYM] = LAYOUT( 
    KC_GRV,  KC_LPRN, KC_RPRN, _Arrow, KC_PERC,                 _Scope, KC_AMPR, KC_QUOT, LSFT(KC_QUOT), KC_AT,
    KC_CIRC, KC_LCBR,  KC_RCBR, KC_DLR , _DollarBracks,         KC_HASH, KC_EQL, KC_MINS, KC_PLUS, KC_EXLM, 
    KC_LT,  KC_LBRC, KC_RBRC,  KC_GT, KC_PIPE,            		KC_TILD, KC_UNDS, KC_ASTR, KC_BSLS, KC_SLSH, 
                             _______, _______, 				_______,  _______  
),

  // Function layer
  [_FUNC] = LAYOUT(
	KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                 KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
	KC_F1, KC_BRID,KC_BRIU,KC_CAPS,XXXXXXX,           _MAIL,_SCREEN,XXXXXXX,XXXXXXX,KC_F12,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP, KC_PWR,  
								            	XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
),

// Mouse Layer
[_MOUSE] = LAYOUT(
	XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX,              XXXXXXX, XXXXXXX, KC_WH_U, XXXXXXX, XXXXXXX, 
	XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,              XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_R, XXXXXXX, 
	XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,    			 XXXXXXX, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX,   
								          TG(_GAMES), KC_BTN2,           KC_BTN1, TO(_GALLIUM)
),

// Games Layer
[_GAMES] = LAYOUT(
	KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,   
	KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
	KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  
									KC_TAB, KC_SPC,      		XXXXXXX,  TO(_GALLIUM)
),

// QWERTY layer
  [_QWERTY] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  					  KC_N,    KC_M,    KC_COMMA,  KC_DOT, KC_SLSH,  
                      LT(_NAV, KC_DEL), KC_ENT,        KC_SPC,  LT(_SYM, KC_BSPC)
)};



//triple layer state definitions
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NAV, _SYM, _FUNC);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 
  const uint8_t mods = get_mods();
  const uint8_t oneshot_mods = get_oneshot_mods();

  switch(keycode){
    case _Arrow:
      if(record -> event.pressed){
        if((mods | oneshot_mods) & MOD_MASK_SHIFT){
         del_oneshot_mods(MOD_MASK_SHIFT);
         unregister_mods(MOD_MASK_SHIFT);
         SEND_STRING("=>");
         register_mods(mods);
        }else{
         SEND_STRING("->");
        }
      }
      break;

    case _DollarBracks:
      if(record -> event.pressed){
         SEND_STRING("${}" SS_TAP(X_LEFT)); 

      }
      break;

    case _Scope:
      if(record -> event.pressed){
         SEND_STRING(":=");
      }
      break;
      
    case _SCREEN:
      if(record -> event.pressed){
        SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LGUI) SS_DOWN(X_S));
        }else{
          clear_keyboard();
        }
        break;

    case _MAIL: 
      if (record->event.pressed) {
        SEND_STRING("@gmail.com");
      }
    break;      
    }
  return true;
}


