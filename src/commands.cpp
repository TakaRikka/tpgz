#include "commands.h"
#include "menus/practice_menu.h"
#include "menus/settings_menu.h"
#include "save_injector.h"
#include "timer.h"
#include "gorge.h"
#include "fs.h"
#include "free_cam.h"
#include "movelink.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "utils/loading.hpp"

using namespace Controller;

#define GORGE_VOID_BUTTONS (Pad::L | Pad::Z)
#define STORE_POSITION_BUTTONS (Pad::DPAD_UP | Pad::R)
#define LOAD_POSITION_BUTTONS (Pad::DPAD_DOWN | Pad::R)
#define MOON_JUMP_BUTTONS (Pad::R | Pad::A)
#define RELOAD_AREA_BUTTONS (Pad::L | Pad::R | Pad::A | Pad::START)
#define TIMER_TOGGLE_BUTTONS (Pad::Z | Pad::A)
#define TIMER_RESET_BUTTONS (Pad::Z | Pad::B)
#define FREE_CAM_BUTTONS (Pad::Z | Pad::B | Pad::A)
#define MOVE_LINK_BUTTONS (Pad::L | Pad::R | Pad::Y )

bool reload_area_flag = false;
bool timer_started = false;
bool reset_timer = false;

bool commands_states[COMMANDS_AMNT];

namespace Commands {
    static float saved_x = 0.0f;
    static float saved_y = 0.0f;
    static float saved_z = 0.0f;
    static uint16_t saved_angle = 0;
    static Vec3 saved_pos = {0.0f, 0.0f, 0.0f};
    static Vec3 saved_target = {0.0f, 0.0f, 0.0f};
    static int button_last_frame;
    static int button_this_frame;

    void store_position() {
        saved_x = tp_zelAudio.link_debug_ptr->position.x;
        saved_y = tp_zelAudio.link_debug_ptr->position.y;
        saved_z = tp_zelAudio.link_debug_ptr->position.z;
        saved_angle = tp_zelAudio.link_debug_ptr->facing;
        saved_pos = tp_matrixInfo.matrix_info->pos;
        saved_target = tp_matrixInfo.matrix_info->target;
    }

    void load_position() {
        tp_zelAudio.link_debug_ptr->position.x = saved_x;
        tp_zelAudio.link_debug_ptr->position.y = saved_y;
        tp_zelAudio.link_debug_ptr->position.z = saved_z;
        tp_zelAudio.link_debug_ptr->facing = saved_angle;
        tp_matrixInfo.matrix_info->pos = saved_pos;
        tp_matrixInfo.matrix_info->target = saved_target;
    }

    void moon_jump() {
        if (tp_gameInfo.momentum_ptr) {
            tp_gameInfo.momentum_ptr->link_momentum.y = 56.0f;
        };
    };

    void toggle_timer() {
        if (button_this_frame == TIMER_TOGGLE_BUTTONS && button_last_frame != TIMER_TOGGLE_BUTTONS) {
            timer_started = !timer_started;
        };
    }

    void hit_reset() {
        reset_timer = true;
    }

    void reload_area() {
        inject_save_flag = true;
        if (g_area_reload_behavior == LOAD_AREA) {
            tp_gameInfo.spawn_speed = 0.0f;
            tp_gameInfo.loading_animation = 13;  // instant load
            tp_gameInfo.respawn_animation = 0;
            tp_gameInfo.warp.entrance.void_flag = 0;
            practice_file.inject_options_before_load = nullptr;
            practice_file.inject_options_during_load = nullptr;
            practice_file.inject_options_after_load = nullptr;
        }
    }  // namespace Commands

    void gorge_void() {
        if (button_this_frame == GORGE_VOID_BUTTONS && button_last_frame != GORGE_VOID_BUTTONS) {
            Utilities::load_save_file("tpgz/save_files/any/gorge_void.bin");
            practice_file.inject_options_before_load = SaveInjector::inject_default_before;
            practice_file.inject_options_during_load = GorgeVoidIndicator::warp_to_gorge;
            practice_file.inject_options_after_load = GorgeVoidIndicator::prep_rupee_roll;
            inject_save_flag = true;
        }
    }

    void toggle_free_cam() {
        if (button_this_frame == FREE_CAM_BUTTONS && button_last_frame != FREE_CAM_BUTTONS) {
            free_cam_active = !free_cam_active;
        }
    }

    void toggle_move_link() {
        if (button_this_frame == 0x0860 && button_last_frame != 0x0860) {
            move_link_active = !move_link_active;
        }
    }

    struct Command {
        bool& active;
        uint16_t buttons;
        void (*command)();
    };

    static Command Commands[COMMANDS_AMNT] = {
        {commands_states[CMD_STORE_POSITION], STORE_POSITION_BUTTONS, store_position},
        {commands_states[CMD_LOAD_POSITION], LOAD_POSITION_BUTTONS, load_position},
        {commands_states[CMD_MOON_JUMP], MOON_JUMP_BUTTONS, moon_jump},
        {commands_states[CMD_RELOAD_AREA], RELOAD_AREA_BUTTONS, reload_area},
        {commands_states[CMD_TIMER_TOGGLE], TIMER_TOGGLE_BUTTONS, toggle_timer},
        {commands_states[CMD_TIMER_RESET], TIMER_RESET_BUTTONS, hit_reset},
        {commands_states[CMD_GORGE_VOID], GORGE_VOID_BUTTONS, gorge_void},
        {commands_states[CMD_FREE_CAM], FREE_CAM_BUTTONS, toggle_free_cam},
        {commands_states[CMD_MOVE_LINK], 0x0860, toggle_move_link}};

    void process_inputs() {
        button_this_frame = tp_mPadStatus.sval;
        for (auto c : Commands) {
            if (c.active == true && tp_mPadStatus.sval == c.buttons) {
                c.command();
                set_buttons_down(0x0);
                set_buttons_pressed(0x0);
                tp_mPadButton.sval = 0x0;
                tp_mPadStatus.sval = 0x0;
            };
        };
        button_last_frame = button_this_frame;
    };

    void enable_command(int idx) {
        Commands[idx].active = true;
    }

    void disable_command(int idx) {
        Commands[idx].active = false;
    }

}  // namespace Commands