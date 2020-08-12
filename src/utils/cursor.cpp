#include "utils/cursor.hpp"
#include "controller.h"

namespace Utilities {
    void move_cursor(Cursor &cursor, int max_cursor_y_value, int max_cursor_x_value) {
        if (!can_move_cursor) {
            return;
        }
        if (button_is_pressed(Controller::DPAD_UP)) {
            // reset so other lines aren't affected
            cursor.x = 0;
            if (cursor.y > 0) {
                cursor.y -= 1;
            } else {
                cursor.y = max_cursor_y_value - 1;
            }
        }
        if (button_is_pressed(Controller::DPAD_DOWN)) {
            // reset so other lines aren't affected
            cursor.x = 0;
            if (cursor.y < max_cursor_y_value - 1) {
                cursor.y += 1;
            } else {
                cursor.y = 0;
            }
        }
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            if (cursor.x < max_cursor_x_value - 1) {
                cursor.x += 1;
            } else {
                cursor.x = 0;
            }
        }
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            if (cursor.x > 0) {
                cursor.x -= 1;
            } else {
                cursor.x = max_cursor_x_value - 1;
            }
        }
    }
} 