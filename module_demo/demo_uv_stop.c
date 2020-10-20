//
//  demo_uv_stop.c
//  lib_demo
//
//  Created by Von on 2020/10/19.
//

#include "demo_uv_stop.h"

#include <stdio.h>
#include <uv.h>

int64_t counter_uv_stop = 0;

void idle_cb(uv_idle_t *handle) {
  printf("Idle callback\n");
  counter_uv_stop++;

  if (counter_uv_stop >= 5) {
    uv_stop(uv_default_loop());
    printf("uv_stop() called\n");
  }
}

void prep_cb(uv_prepare_t *handle) { printf("Prep callback\n"); }

/**
 * demo: uv stop
 */
void demo_uv_stop() {
  uv_idle_t idler;
  uv_prepare_t prep;

  uv_idle_init(uv_default_loop(), &idler);
  uv_idle_start(&idler, idle_cb);

  uv_prepare_init(uv_default_loop(), &prep);
  uv_prepare_start(&prep, prep_cb);

  uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
