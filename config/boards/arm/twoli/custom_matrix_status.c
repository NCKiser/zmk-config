/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <kernel.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include "custom_matrix_status.h"
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

int custom_widget_matrix_status_init(struct custom_widget_matrix_status *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent, NULL);

    lv_obj_set_size(widget->obj, 48, 64); 

    lv_obj_align(widget->obj, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    lv_obj_set_style_local_border_color(widget->obj, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_SECONDARY);
    lv_obj_set_style_local_border_width(widget->obj, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_radius(widget->obj, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 005);

    lv_obj_t* top_half = lv_obj_create(widget->obj, NULL);
    lv_obj_set_size(top_half, 48, 32); 
    lv_obj_align(top_half, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_style_local_border_color(top_half, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_SECONDARY);
    lv_obj_set_style_local_border_width(top_half, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 0);
    if (CONFIG_MATRIX_LAYOUT_ISO) {
        lv_obj_t* btn1 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn1, 24, 16); 
        lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
        lv_obj_set_style_local_border_color(btn1, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY); 
        lv_obj_set_style_local_border_width(btn1, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);

        lv_obj_t* btn5 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn5, 28, 16);
        lv_obj_align(btn5, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
        lv_obj_set_style_local_border_color(btn5, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);
        lv_obj_set_style_local_border_width(btn5, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);

        lv_obj_t* btn7 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn7, 20, 32); 
        lv_obj_align(btn7, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
        lv_obj_set_style_local_border_color(btn7, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);
        lv_obj_set_style_local_border_width(btn7, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);
    } else {
        lv_obj_t* btn1 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn1, 16, 16); 
        lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
        lv_obj_set_style_local_border_color(btn1, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY); 
        lv_obj_set_style_local_border_width(btn1, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);
        
        lv_obj_t* btn2 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn2, 16, 16); 
        lv_obj_align(btn2, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
        lv_obj_set_style_local_border_color(btn2, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);
        lv_obj_set_style_local_border_width(btn2, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);
        
        lv_obj_t* btn3 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn3, 16, 16); 
        lv_obj_align(btn3, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
        lv_obj_set_style_local_border_color(btn3, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);
        lv_obj_set_style_local_border_width(btn3, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);
        lv_obj_set_style_local_bg_color(btn3, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);
        
        lv_obj_t* btn5 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn5, 16, 16);
        lv_obj_align(btn5, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
        lv_obj_set_style_local_border_color(btn5, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);
        lv_obj_set_style_local_border_width(btn5, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);
        
        lv_obj_t* btn6 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn6, 16, 16); 
        lv_obj_align(btn6, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
        lv_obj_set_style_local_border_color(btn6, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);
        lv_obj_set_style_local_border_width(btn6, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);
        
        lv_obj_t* btn7 = lv_obj_create(top_half, NULL);
        lv_obj_set_size(btn7, 16, 16); 
        lv_obj_align(btn7, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
        lv_obj_set_style_local_border_color(btn7, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);
        lv_obj_set_style_local_border_width(btn7, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 002);
    }
    lv_obj_t* bottom_half = lv_obj_create(widget->obj, NULL);
    lv_obj_set_size(bottom_half, 48, 32); 
    lv_obj_align(bottom_half, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_local_border_color(bottom_half, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_SECONDARY);
    lv_obj_set_style_local_border_width(bottom_half, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 0);

    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *custom_widget_matrix_status_obj(struct custom_widget_matrix_status *widget) {
    return widget->obj;
}