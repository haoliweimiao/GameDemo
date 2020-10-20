//
//  demo_idle_basic.c
//  lib_demo
//
//  Created by Von on 2020/10/20.
//

#include "demo_idle_basic.h"
#include <stdio.h>
#include <uv.h>

int64_t counter_idle_basic = 0;

void wait_for_a_while(uv_idle_t *handle) {
    counter_idle_basic++;
    
    if (counter_idle_basic >= 1000) {
        printf("wait_for_a_while counter_idle_basic>=1000\n");
        uv_idle_stop(handle);
    }
}

/**
 * idle basic demo
 */
void demo_idle_basic() {
    uv_idle_t idler;
    
    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, wait_for_a_while);
    
    printf("Idling...\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    
    uv_loop_close(uv_default_loop());
}
