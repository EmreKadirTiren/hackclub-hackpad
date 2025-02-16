#include QMK_KEYBOARD_H

enum custom_keycodes {
    KC_PTT = SAFE_RANGE,
    KC_DEAF,
    KC_PTT_PRIO
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_PTT:
            if (record->event.pressed) {
                // When keycode KC_PTT is pressed
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_M); // Example: Ctrl+Shift+M for Push-to-Talk
            } else {
                // When keycode KC_PTT is released
                unregister_code(KC_M);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            break;
        case KC_DEAF:
            if (record->event.pressed) {
                // When keycode KC_DEAF is pressed
                SEND_STRING(SS_LCTL(SS_LSFT("d"))); // Example: Ctrl+Shift+D for Deafen
            } else {
                // When keycode KC_DEAF is released
            }
            break;
        case KC_PTT_PRIO:
            if (record->event.pressed) {
                // When keycode KC_PTT_PRIO is pressed
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_P); // Example: Ctrl+Shift+P for Push-to-Talk Priority
            } else {
                // When keycode KC_PTT_PRIO is released
                unregister_code(KC_P);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Layer 0: Default Layer
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Tg │ + │ <- Tg = TG(1)
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, TG(1),   KC_PPLS
    ),
    /*
     * Layer 1: Fun Layer
     * This layer is designed to provide quick access to various fun and utility functions.
     * 
     * ┌────────┬────────┬────────┬────────┐
     * │ Next   │ Prev   │ Play   │ Stop   │
     * ├────────┼────────┼────────┼────────┤
     * │ Vol Up │ Vol Dn │ Mute   │ Power  │
     * ├────────┼────────┼────────┼────────┤
     * │ My Comp│ Mail   │ Search │ Browser│
     * ├────────┼────────┼────────┼────────┤
     * │ PTT    │ Mute   │ TO(0)  │PTT Prio│
     * └────────┴────────┴────────┴────────┘
     * 
     * Keymap:
     * - KC_MNXT: Next track
     * - KC_MPRV: Previous track
     * - KC_MPLY: Play/Pause
     * - KC_MSTP: Stop
     * - KC_VOLU: Volume up
     * - KC_VOLD: Volume down
     * - KC_MUTE: Mute
     * - KC_CALC: Open calculator
     * - KC_MYCM: Open "My Computer"
     * - KC_MAIL: Open mail client
     * - KC_WSCH: Open web search
     * - KC_WBAK: Open web browser
     * - KC_PWR: Power off
     * - KC_PTT: Push-to-Talk (custom keycode)
     * - KC_MUTE: Mute/Unmute Microphone
     * - KC_DEAF: Deafen/Undeafen
     * - TO(0): Switch to Layer 0
     * - KC_PTT_PRIO: Push-to-Talk Priority (custom keycode)
     * - _______: No function (transparent)
     */
    [1] = LAYOUT(
        KC_MNXT, KC_MPRV, KC_MPLY, KC_MSTP,
        KC_VOLU, KC_VOLD, KC_MUTE, KC_PWR,
        KC_MYCM, KC_MAIL, KC_WSCH, KC_WBAK,
        KC_PTT,  KC_MUTE, TO(0), KC_PTT_PRIO
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Assuming you have only one encoder
        switch (biton32(layer_state)) {
            case 0:
                if (clockwise) {
                    tap_code(KC_VOLU); // Volume Up
                } else {
                    tap_code(KC_VOLD); // Volume Down
                }
                break;
            case 1:
                if (clockwise) {
                    tap_code(KC_MNXT); // Next Track
                } else {
                    tap_code(KC_MPRV); // Previous Track
                }
                break;
            default:
                break;
        }
    }
    return true;
}