
    /* Copyright 2021 Dane Evans
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
    // SOFLE RGB
    #include <stdio.h>
    char wpm_str[10];

    #include QMK_KEYBOARD_H

    #define INDICATOR_BRIGHTNESS 30

    #define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
    #define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

    // Light66ations
    #define SET_INDICATORS(hsv) \
        {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
        {35+0, 1, hsv}
    #define SET_UNDERGLOW(hsv) \
        {1, 6, hsv}, \
        {35+1, 6,hsv}
    #define SET_NUMPAD(hsv)     \
        {35+15, 5, hsv},\
        {35+22, 3, hsv},\
        {35+27, 3, hsv}
    #define SET_NUMROW(hsv) \
        {10, 2, hsv}, \
            {20, 2, hsv}, \
            {30, 2, hsv}, \
        {35+ 10, 2, hsv}, \
        {35+ 20, 2, hsv}, \
        {35+ 30, 2, hsv}
    #define SET_INNER_COL(hsv)	\
        {33, 4, hsv}, \
        {35+ 33, 4, hsv}

    #define SET_OUTER_COL(hsv) \
        {7, 4, hsv}, \
        {35+ 7, 4, hsv}
    #define SET_THUMB_CLUSTER(hsv) 	\
        {25, 2, hsv}, \
        {35+ 25, 2, hsv}
    #define SET_LAYER_ID(hsv) 	\
        {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
        {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
            {1, 6, hsv}, \
        {35+1, 6, hsv}, \
            {7, 4, hsv}, \
        {35+ 7, 4, hsv}, \
            {25, 2, hsv}, \
        {35+ 25, 2, hsv}


    enum sofle_layers {
        _DEFAULTS = 0,
        _QWERTY = 0,
        _COLEMAK,
        _COLEMAKDH,
        _LOWER,
        _RAISE,
        _ADJUST,
    };

    enum custom_keycodes {
        KC_LOWER = SAFE_RANGE,
        KC_RAISE,
        KC_ADJUST,
        KC_PRVWD = QK_USER,
        KC_NXTWD,
        KC_LSTRT,
        KC_LEND
    };

    #define KC_QWERTY PDF(_QWERTY)
    #define KC_COLEMAK PDF(_COLEMAK)
    #define KC_COLEMAKDH PDF(_COLEMAKDH)
    uint32_t last_input_activity = 0;

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * QWERTY
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | ESC  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Caps |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------| MUTE  |    |       |------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | RCTR | LGUI | LAlt |LOWER | / Space /       \ Enter\  |RAISE | Bspc | RCTR | RAlt |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_QWERTY] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,     KC_9,   KC_0,   KC_ESC,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,   KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,   KC_BACKSLASH,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,   XXXXXXX,  KC_N,   KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_LSFT,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_LCTL,  KC_LGUI, KC_LALT, KC_LOWER, KC_SPC,      KC_ENT,  KC_RAISE, KC_BSPC, KC_RCTL, KC_RALT
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
    ),


    /*
    * COLEMAK
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | ESC  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Caps |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
    * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  | Shift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | RCTR | LGUI | LAlt |LOWER | / Space /       \ Enter\  |RAISE | Bspc | RCTR | RAlt |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_COLEMAK] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    _______,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    _______,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    _______,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN, _______,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    _______,  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,   KC_E,    KC_I,    KC_O,    _______,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    _______,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  _______,    _______,KC_K,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, _______,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                     _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
    ),


    /*
    * COLEMAK-DH
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | ESC  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Caps |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
    * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  | Shift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | RCTR | LGUI | LAlt |LOWER | / Space /       \ Enter\  |RAISE | Bspc | RCTR | RAlt |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_COLEMAKDH] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    _______,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    _______,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    _______,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,   KC_U,    KC_Y,    KC_SCLN, _______,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    _______,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,   KC_E,    KC_I,    KC_O,    _______,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    _______,  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,  _______,    _______,KC_K,    KC_H,   KC_COMM, KC_DOT,  KC_SLSH, _______,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                    _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
    ),


    /* LOWER
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
    * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
    * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | RCTR | LGUI | LAlt |LOWER | / Space /       \ Enter\  |RAISE | Del  | RCTR | RAlt |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_LOWER] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                    _______, _______, _______, _______, _______,     _______, KC_DEL, _______, _______, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
    ),


    /* RAISE
    * ,----------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Esc  | Ins  | Pscr | Menu |      |      |                    |PageUp| PWrd |  Up  | NWrd | DLine| Bspc |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Tab  | LAt  | LCtl | Shift|      | Caps |-------.    ,-------|PageDn| Left | Down | Rigth|  Del | Bspc |
    * |------+------+------+------+------+------|  MUTE  |   |       |------+------+------+------+------+------|
    * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | RCTR | LGUI | LAlt |LOWER | / Space /       \ Enter\  |RAISE | Del  | RCTR | RAlt |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_RAISE] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    _______, _______ , _______ , _______ , _______ , _______,               _______,  _______  , _______,  _______ ,  _______ ,_______,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                KC_PGUP, KC_PRVWD, KC_UP, KC_NXTWD, C(KC_BSPC), KC_BSPC,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,  _______,       _______,  XXXXXXX, KC_LSTRT, XXXXXXX, KC_LEND,   XXXXXXX, _______,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                    _______, _______, _______, _______, _______,     _______, KC_DEL, _______, _______, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
    ),

    // * SnapW - snap window
    // ! Unforturnately snap window does not work in Mac OS
    /* ADJUST
    * ,-------------------------------------------.                   ,-----------------------------------------.
    * |      |      |      |      |      |        |                   |      |      |      |      |      |      |
    * |--------+------+------+------+------+------|                   |------+------+------+------+------+------|
    * | QK_BOOT|    |      |      |      |        |                   |      |      |SnapWU|      |      |      |
    * |--------+------+------+------+------+------|                   |------+------+------+------+------+------|
    * |      |      |      |      |CLMKDH| CLMK   |-------.   ,-------|      |SnapWL|SnapWD|SnapWR|      |      |
    * |--------+------+------+------+------+------|  MUTE |   |       |------+------+------+------+------+------|
    * |      |      |      |      |      |QWERTY  |-------|   |-------|      | PREV | PLAY | NEXT |      |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LGUI | LAlt | Bspc |LOWER | / Space /       \ Enter\  |RAISE | RCTR | RAlt | RGUI |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [_ADJUST] = LAYOUT(
    //,------------------------------------------------.                    ,---------------------------------------------------.
    EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    QK_BOOT, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, LGUI(KC_LEFT), XXXXXXX, XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
    XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, KC_COLEMAKDH,KC_COLEMAK,            XXXXXXX,LGUI(KC_LEFT), LGUI(KC_LEFT), LGUI(KC_RIGHT), XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
    XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,KC_QWERTY,XXXXXXX,   XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
    //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                    _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
    ),
};

    // TODO create C array image for bongo cat
    // TODO learn how to animate bongo cat
    // * Yoinked bongo cat from https://github.com/nwii/oledbongocat/blob/main/keymap.c

    // #ifdef OLED
    #ifdef OLED_ENABLE

    static void render_logo(void) {
        static const char PROGMEM qmk_logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };
    
        oled_write_P(qmk_logo, false);
    }
    
    static void print_status_narrow(void) {
        // Print current mode
        oled_write_P(PSTR("\n\n"), false);
        oled_write_ln_P(PSTR("Dane\nEvans"), false);
    
        oled_write_ln_P(PSTR(""), false);
    
        //snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state)
    
    
        switch (get_highest_layer(default_layer_state)) {
            case _QWERTY:
                oled_write_ln_P(PSTR("Qwrt"), false);
                break;
            case _COLEMAK:
                oled_write_ln_P(PSTR("Clmk"), false);
                break;
            case _COLEMAKDH:
                oled_write_ln_P(PSTR("CmkDH"), false);
                break;
    
            default:
                oled_write_ln_P(PSTR("Undef"), false);
        }
        oled_write_P(PSTR("\n\n"), false);
        // Print current layer
        oled_write_ln_P(PSTR("LAYER"), false);
        switch (get_highest_layer(layer_state)) {
            case _COLEMAK:
            case _QWERTY:
            case _COLEMAKDH:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("Raise"), false);
                break;
            case _LOWER:
                oled_write_P(PSTR("Lower"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adj\n"), false);
                break;
            default:
                oled_write_ln_P(PSTR("Undef"), false);
        }
    }
    
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        if (is_keyboard_master()) {
            return OLED_ROTATION_270;
        }
        return rotation;
    }
    
    bool oled_task_user(void) {
        if (is_keyboard_master()) {
            print_status_narrow();
        } else {
            render_logo();
        }
        return false;
    }
    
    #endif

    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        if (record->event.pressed) {
            last_input_activity = timer_read32();
        }

        switch (keycode) {
            case KC_LOWER:
                if (record->event.pressed) {
                    layer_on(_LOWER);
                    update_tri_layer(_LOWER, _RAISE, _ADJUST);
                } else {
                    layer_off(_LOWER);
                    update_tri_layer(_LOWER, _RAISE, _ADJUST);
                }
                return false;
            case KC_RAISE:
                if (record->event.pressed) {
                    layer_on(_RAISE);
                    update_tri_layer(_LOWER, _RAISE, _ADJUST);
                } else {
                    layer_off(_RAISE);
                    update_tri_layer(_LOWER, _RAISE, _ADJUST);
                }
                return false;
            case KC_ADJUST:
                if (record->event.pressed) {
                    layer_on(_ADJUST);
                } else {
                    layer_off(_ADJUST);
                }
                return false;
        }
        return true;
    }

    // ! Make sure to return false here because by default all main encoders have volume controls.
    // ! If you return true then the micro controller will still make the main controller act as
    // ! volumne controls along with the functionality in this function.
    #ifdef ENCODER_ENABLE
    bool encoder_update_user(uint8_t index, bool clockwise) {
        // Main encoder has index of 0
        if (index == 0) {
            switch (get_highest_layer(layer_state)) {
                case _COLEMAK:
                case _QWERTY:
                case _COLEMAKDH:
                    tap_code(clockwise ? QK_MOUSE_WHEEL_RIGHT : QK_MOUSE_WHEEL_LEFT);
                    break;
                case _RAISE:
                case _LOWER:
                case _ADJUST:
                    tap_code(clockwise ? KC_AUDIO_VOL_UP : KC_AUDIO_VOL_DOWN);
                    break;
                default:
                    tap_code(clockwise ? QK_MOUSE_WHEEL_RIGHT : QK_MOUSE_WHEEL_LEFT);
                    break;
            }
        } else if (index == 1) {
            tap_code(clockwise ? QK_MOUSE_WHEEL_UP : QK_MOUSE_WHEEL_DOWN);
        }

        return false;
    }
    #endif