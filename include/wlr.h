#pragma once

#include <wayland-client.h>

#define class class_
#define namespace namespace_
#define delete delete_
#define static

extern "C" {

#include "wlr-layer-shell-unstable-v1-client-protocol.h"
}

#undef class
#undef namespace
#undef delete
#undef static
