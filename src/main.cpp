#include "wlr.h"
#include <f3d/context.h>
#include <f3d/engine.h>
#include <f3d/interactor.h>
#include <f3d/scene.h>
#include <iostream>

static void handle_global(void *data, struct wl_registry *registry,
                          uint32_t name, const char *interface,
                          uint32_t version) {
    // TODO: handling
}

static void handle_global_remove(void *data, struct wl_registry *registry,
                                 uint32_t name) {
    // TODO: destroy
}

struct State {
    struct wl_display *display;
    struct wl_compositor *compositor;
    struct wl_list outputs;

    State() {
        wl_list_init(&outputs);
        display = wl_display_connect(NULL);

        struct wl_registry *registry = wl_display_get_registry(display);

        static const struct wl_registry_listener registry_listener = {
            .global = handle_global,
            .global_remove = handle_global_remove,
        };

        wl_registry_add_listener(registry, &registry_listener, this);

        if (wl_display_roundtrip(display) < 0) {
            std::cerr << "Failed to initialize Wayland connection" << std::endl;
            return;
        }
    }
};

struct Output {
    struct wl_list link;
    struct wl_output *wl_output;

    struct wl_surface *surface;
    struct zwlr_layer_surface_v1 *layer_surface;

    uint32_t width, height;
    int32_t scale;
};

int main() {
    f3d::engine::autoloadPlugins();
    f3d::engine engine = f3d::engine::create();
    engine.getScene().add("models/Hatsune Miku/miku_prefab.dae");
    engine.getInteractor().start();

    State *state = new State();
    delete state;

    return 0;
};
