//
//  ruvi base
//

// includes
#include "core/definitions/handler.hh"
#include "core/interfaces/interfaces.hh"
#include "hooks/hooks.hh"
#include "menu/menu.hh"
#include "sdk/input/input.hh"
#include "sdk/netvars/netvars.hh"
#include "sdk/render/render.hh"
#include <thread>

std::thread main_thread;

// initialize all our stuff here
void constructor() {

  CODE_START

  while (!dlopen(STR("./bin/linux64/serverbrowser_client.so"),
                 RTLD_NOLOAD | RTLD_NOW))
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  interfaces::on_entry_point();
  netvars::on_entry_point();
  draw::on_entry_point();
  input::on_entry_point();
  hooks::on_entry_point();
  menu::on_entry_point();

  CODE_END("error handler - constructor - entry");
}

// entry point
int __attribute__((constructor)) startup() {

  // create a new thread and attach the library
  main_thread = std::thread{constructor};

  return 0;
}
