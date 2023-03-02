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

static lv_style_t style_btn;000000

int custom_widget_matrix_status_init(struct custom_widget_matrix_status *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent, NULL);

    lv_obj_set_size(widget->obj, 48, 64); 

    lv_obj_align(widget->obj, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    lv_obj_t* btn1 = lv_btn_create(widget->obj, NULL);
    lv_obj_set_size(btn1, 16, 16); 
    lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    lv_obj_t* btn2 = lv_btn_create(widget->obj, NULL);
    lv_obj_set_size(btn2, 16, 16); 
    lv_obj_align(btn2, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *custom_widget_matrix_status_obj(struct custom_widget_matrix_status *widget) {
    return widget->obj;
}