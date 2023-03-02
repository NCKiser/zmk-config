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

static lv_style_t button_style;

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

int custom_widget_matrix_status_init(struct custom_widget_matrix_status *widget, lv_obj_t *parent) {
    widget->obj = lv_btn_create(parent, NULL);

    lv_style_set_bg_color(&button_style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&button_style, LV_STATE_PRESSED, 1);
    lv_style_set_border_color(&button_style, LV_STATE_DEFAULT, 1);
    lv_style_set_border_width(&button_style, LV_STATE_DEFAULT, 2);
    lv_style_set_border_color(&button_style, LV_STATE_PRESSED, 0);
    lv_style_set_border_width(&button_style, LV_STATE_PRESSED, 2);

    lv_obj_set_size(widget->obj, 48, 64);
    lv_obj_add_style(widget->obj, LV_OBJ_PART_MAIN, &button_style);

    lv_btn_set_checkable(widget->obj, true);
    lv_btn_set_state(widget->obj, LV_BTN_STATE_PRESSED);

    lv_label_set_text(lv_label_create(widget->obj, NULL), "btn");
    lv_obj_align(widget->obj, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *custom_widget_matrix_status_obj(struct custom_widget_matrix_status *widget) {
    return widget->obj;
}