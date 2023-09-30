#include "../hex_viewer.h"
#include "../helpers/hex_viewer_custom_event.h"
#include "../views/hex_viewer_scene_1.h"

void hex_viewer_scene_1_callback(BoilerplateCustomEvent event, void* context) {
    furi_assert(context);
    Boilerplate* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, event);
}

void hex_viewer_scene_scene_1_on_enter(void* context) {
    furi_assert(context);
    Boilerplate* app = context;
    hex_viewer_scene_1_set_callback(app->hex_viewer_scene_1, hex_viewer_scene_1_callback, app);
    view_dispatcher_switch_to_view(app->view_dispatcher, BoilerplateViewIdScene1);
}

bool hex_viewer_scene_scene_1_on_event(void* context, SceneManagerEvent event) {
    Boilerplate* app = context;
    bool consumed = false;
    
    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
            case BoilerplateCustomEventScene1Left:
            case BoilerplateCustomEventScene1Right:
                break;
            case BoilerplateCustomEventScene1Up:
            case BoilerplateCustomEventScene1Down:
                break;
            case BoilerplateCustomEventScene1Back:
                notification_message(app->notification, &sequence_reset_red);
                notification_message(app->notification, &sequence_reset_green);
                notification_message(app->notification, &sequence_reset_blue);
                if(!scene_manager_search_and_switch_to_previous_scene(
                    app->scene_manager, BoilerplateSceneMenu)) {
                        scene_manager_stop(app->scene_manager);
                        view_dispatcher_stop(app->view_dispatcher);
                    }
                consumed = true;
                break;
        }
    }
    
    return consumed;
}

void hex_viewer_scene_scene_1_on_exit(void* context) {
    Boilerplate* app = context;
    UNUSED(app);
}