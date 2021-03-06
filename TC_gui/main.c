/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "main.h"
#include <system_settings.h>

static void _quit_cb(void *data, Evas_Object* obj, void* event_info)
{
    Evas_Object *win = (Evas_Object *) data;
    elm_win_lower(win);
}

static Evas_Object* create_win(const char *name)
{
    Evas_Object *eo;
    int w, h;

    eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
    if (!eo) return NULL;

    elm_win_title_set(eo, name);
    elm_win_borderless_set(eo, EINA_TRUE);
    elm_win_autodel_set(eo, EINA_TRUE);
    evas_object_smart_callback_add(eo, "delete,request", _quit_cb, NULL);
    ecore_x_window_size_get(ecore_x_window_root_first_get(), &w, &h);
    evas_object_resize(eo, w, h);

    return eo;
}

static Evas_Object* _create_bg(Evas_Object *parent)
{
    Evas_Object *bg;

    bg = elm_bg_add(parent);
    evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(parent, bg);
    evas_object_show(bg);

    return bg;
}

static Evas_Object* _create_layout_main(Evas_Object* parent)
{
    Evas_Object *layout;

    layout = elm_layout_add(parent);

    elm_layout_theme_set(layout, "layout", "application", "default");
    evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(parent, layout);

    evas_object_show(layout);

    return layout;
}

static Evas_Object* _create_naviframe_layout(Evas_Object* parent)
{
    Evas_Object *navi;

    navi = elm_naviframe_add(parent);
    elm_object_part_content_set(parent, "elm.swallow.content", navi);

    evas_object_show(navi);

    return navi;
}


static void _create_view_layout(struct appdata *ad)
{
    Evas_Object *list;
    Evas_Object *btn;

    list = _create_list_winset(ad->win_main, ad);
    btn = elm_button_add(ad->navi);
    elm_object_style_set(btn, "naviframe/end_btn/default");
    evas_object_smart_callback_add(btn, "clicked", _quit_cb, ad->win_main);
    elm_naviframe_item_push(ad->navi, _("Tizen UI"), btn, NULL, list, NULL);
}

void list_item_touch_handler_exit(void* data, Evas_Object* obj, void* event_info)
{
    elm_exit();
}

/**
 * Huge
 */
void list_item_touch_handler1(void* data, Evas_Object* obj, void* event_info)
{
	int ret;
    ret = system_settings_set_value_int(SYSTEM_SETTINGS_KEY_FONT_SIZE, SYSTEM_SETTINGS_FONT_SIZE_HUGE);
    ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, "HelveticaNeue");
}

/**
 * Normal
 */
void list_item_touch_handler2(void* data, Evas_Object* obj, void* event_info)
{
	int ret;

	ret = system_settings_set_value_int(SYSTEM_SETTINGS_KEY_FONT_SIZE, SYSTEM_SETTINGS_FONT_SIZE_NORMAL);
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, "HelveticaNeue");
}

void list_item_touch_handler3(void* data, Evas_Object* obj, void* event_info)
{
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, "HelveticaNeue");
}

void list_item_touch_handler4(void* data, Evas_Object* obj, void* event_info)
{
	int ret;
    ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, "HelveticaNeue");
}

void list_item_touch_handler5(void* data, Evas_Object* obj, void* event_info)
{
	printf(">>>>>>>> motion activation ON \n");
	system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, 1/*ON*/);
}

void list_item_touch_handler6(void* data, Evas_Object* obj, void* event_info)
{
	printf(">>>>>>>> motion activation OFF \n");
	system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, 0/*OFF*/);
}

void system_settings_changed_font_size(system_settings_key_e key, void *user_data)
{
	printf(">>>>>>>> system_settings_changed_font_size key = %d \n", key);
	printf("---------------------------------CALLED BY USER APPLICATION -FONT SIZE \n");
}

void system_settings_changed_font_type(system_settings_key_e key, void *user_data)
{
	printf(">>>>>>>> system_settings_changed_font_type key = %d \n", key);
	printf("---------------------------------CALLED BY USER APPLICATION -FONT TYPE \n");
}

void system_settings_changed_motion_activation(system_settings_key_e key, void *user_data)
{
	printf(">>>>>>>> system_settings_changed_motion_activation key = %d \n", key);
	printf("---------------------------------CALLED BY USER APPLICATION-MOTION ACTIVIATION \n");
}

static Evas_Object* _create_list_winset(Evas_Object* parent, struct appdata* ad)
{
	Evas_Object *li;
	int idx = 0;
	//struct _menu_item *menu_its;
	int ret;
	ret = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_FONT_SIZE, system_settings_changed_font_size, NULL);

	ret = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_FONT_TYPE, system_settings_changed_font_type, NULL);
	if (ret < 0) {
		printf("SYSTEM_SETTINGS_KEY_FONT_TYPE returns negative values = %d \n", ret);
	} else {
		printf("SYSTEM_SETTINGS_KEY_FONT_TYPE returns positive values = %d, means successful return. \n", ret);
	}

	// callback registration
	ret = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, system_settings_changed_motion_activation, NULL);
	if (ret < 0) {
			printf("SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION returns negative values = %d \n", ret);
	} else {
			printf("SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION returns positive values = %d, means successful return. \n", ret);
	}

	li = elm_list_add(parent);
	elm_list_mode_set(li, ELM_LIST_COMPRESS);

	elm_list_item_append( li, "QUIT", NULL, NULL, list_item_touch_handler_exit, ad);
	elm_list_item_append( li, "font size - bigger ", NULL, NULL, list_item_touch_handler1, ad);
	elm_list_item_append( li, "font size - normal ", NULL, NULL, list_item_touch_handler2, ad);
	elm_list_item_append( li, "font type - choose Helvetica 1 ", NULL, NULL, list_item_touch_handler3, ad);
	elm_list_item_append( li, "font type - choose Helvetica 2 ", NULL, NULL, list_item_touch_handler4, ad);
	elm_list_item_append( li, "motion activation ON ", NULL, NULL, list_item_touch_handler5, ad);
	elm_list_item_append( li, "motion activation OFF ", NULL, NULL, list_item_touch_handler6, ad);

	elm_list_go(li);
	return li;
}

static void _mouse_down_cb(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
	//struct appdata *ad = (struct appdata *)data;
    //Evas_Event_Mouse_Down *ev = event_info;

}

static void _mouse_up_cb(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
    //struct appdata *ad = (struct appdata *)data;

}

static void _mouse_move_cb(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
    //struct appdata *ad = (struct appdata *)data;
}

static void _window_resize_cb(void *data, Evas * e, Evas_Object * obj, void *event_info)
{
    struct appdata *ad = (struct appdata *)data;
    evas_object_geometry_get(ad->win_main, NULL, NULL, &ad->root_w, &ad->root_h);
}

static int _rotation_cb(enum appcore_rm mode, void *data)
{
    struct appdata *ad = (struct appdata *)data;
    int angle;

    switch (mode) {
        case APPCORE_RM_LANDSCAPE_NORMAL:
            angle = -90;
            break;

        case APPCORE_RM_LANDSCAPE_REVERSE:
            angle = 90;
            break;

        case APPCORE_RM_PORTRAIT_REVERSE:
            angle = 180;
            break;

        case APPCORE_RM_UNKNOWN:
        case APPCORE_RM_PORTRAIT_NORMAL:
        default:
            angle = 0;
            break;
    }

    elm_win_rotation_with_resize_set(ad->win_main, angle);
    // set_rotation_degree(angle);

    // This is need for customized rotation process.
    // rotate_for_winset(mode);

    return 0;
}

int app_create(void *data)
{
    struct appdata *ad = (struct appdata *) data;

    // Set the engine to opengl_x11
    //elm_config_engine_set("opengl_x11");

    ad->win_main = create_win(PACKAGE);

    evas_object_event_callback_add(ad->win_main, EVAS_CALLBACK_RESIZE, _window_resize_cb, ad);
    evas_object_show(ad->win_main);
    ad->evas = evas_object_evas_get(ad->win_main);
    appcore_set_rotation_cb(_rotation_cb, ad);

    // set_edj_name(NULL);

	ad->bg = _create_bg(ad->win_main);
	ad->layout_main = _create_layout_main(ad->win_main);
	elm_win_indicator_mode_set(ad->win_main, ELM_WIN_INDICATOR_SHOW);

	ad->navi = _create_naviframe_layout(ad->layout_main);

	_create_view_layout(ad);

    evas_object_event_callback_add(ad->navi, EVAS_CALLBACK_MOUSE_DOWN, _mouse_down_cb, ad);
    evas_object_event_callback_add(ad->navi, EVAS_CALLBACK_MOUSE_UP, _mouse_up_cb,  ad);
    evas_object_event_callback_add(ad->navi, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move_cb, ad);

    return 0;
}

int app_terminate(void *data)
{
	//struct appdata *ad = data;

	int ret;
	// unregistration
	ret = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_FONT_SIZE);
	ret = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_FONT_TYPE);
	ret = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION);
	return 0;
}

int app_pause(void *data)
{
	//struct appdata *ad = data;

    return 0;
}

int app_resume(void *data)
{
    //struct appdata *ad = data;

    return 0;
}

int app_reset(bundle* b, void* data)
{
	struct appdata* ad = data;

	if (ad->win_main)
		elm_win_activate(ad->win_main);

	return 0;
}


int main(int argc, char* argv[])
{
	struct appdata ad;

	struct appcore_ops ops = {
		.create = app_create,
		.terminate = app_terminate,
		.pause = app_pause,
		.resume = app_resume,
		.reset = app_reset
	};

	ops.data = &ad;

	return appcore_efl_main(PACKAGE, &argc, &argv, &ops);
}
