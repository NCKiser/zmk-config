/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lvgl.h>
#include <kernel.h>

struct custom_widget_matrix_status {
    sys_snode_t node;
    lv_obj_t *obj;
};

int custom_widget_matrix_status_init(struct custom_widget_matrix_status *widget, lv_obj_t *parent);
lv_obj_t *custom_widget_matrix_status_obj(struct custom_widget_matrix_status *widget);