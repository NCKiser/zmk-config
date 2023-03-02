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
    widget->obj = lv_btn_create(parent, NULL);

    // set the size of the button
    lv_obj_set_size(widget->obj, 30, 12); 

    // set the text for the button label
    lv_obj_t* label = lv_label_create(widget->obj, NULL);
    lv_label_set_text(label, "->");

    lv_obj_align(widget->obj, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *custom_widget_matrix_status_obj(struct custom_widget_matrix_status *widget) {
    return widget->obj;
}