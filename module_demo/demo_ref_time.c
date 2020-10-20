//
//  demo_ref_time.c
//  lib_demo
//
//  Created by Von on 2020/10/19.
//

#include "demo_ref_time.h"

#include <stdio.h>
#include <uv.h>

uv_loop_t *loop;
uv_timer_t gc_req;
uv_timer_t fake_job_req;
uv_timer_t test_req;

void gc(uv_timer_t *handle) { fprintf(stderr, "Freeing unused objects\n"); }

void fake_job(uv_timer_t *handle) { fprintf(stdout, "Fake job done\n"); }

void test_job(uv_timer_t *handle) { fprintf(stdout, "Test job done\n"); }

/**
 * time task
 */
void demo_ref_time() {
  loop = uv_default_loop();

  // 初始化定时器 gc_req
  uv_timer_init(loop, &gc_req);
  // 如果除了定时器 gc_req, 如果当前没有其他任务的时候，则退出定时器 gc_req
  uv_unref((uv_handle_t *)&gc_req);
  // 启动 gc_req 定时器, 0 毫秒开始，每 2000 毫秒执行一次
  uv_timer_start(&gc_req, gc, 0, 2000);

  // could actually be a TCP download or something
  // 初始化定时器 fake_job_req
  uv_timer_init(loop, &fake_job_req);
  // 启动 fake_job_req 定时器, 9000 毫秒后开始执行, 不需要循环执行
  uv_timer_start(&fake_job_req, fake_job, 9000, 0);

  // could actually be a TCP download or something
  uv_timer_init(loop, &test_req);
  uv_timer_start(&test_req, test_job, 10000, 10000);

  uv_run(loop, UV_RUN_DEFAULT);
}
