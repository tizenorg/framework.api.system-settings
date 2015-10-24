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

#include <tet_api.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>


#include <system_settings.h>

/* test loop code */
#include <glib.h>
#include <glib-object.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;


#define API_NAME_SETTINGS_SET_VALUE_STRING 	"system_settings_set_value_string"
#define API_NAME_SETTINGS_GET_VALUE_STRING 	"system_settings_get_value_string"
#define API_NAME_SETTINGS_SET_VALUE_INT 	"system_settings_set_value_int"
#define API_NAME_SETTINGS_GET_VALUE_INT 	"system_settings_get_value_int"
#define API_NAME_SETTINGS_SET_VALUE_BOOL 	"system_settings_set_value_bool"
#define API_NAME_SETTINGS_GET_VALUE_BOOL 	"system_settings_get_value_bool"
#define API_NAME_SETTINGS_SET_CHANGED_CB 	"system_settings_set_changed_cb"
#define API_NAME_SETTINGS_UNSET_CHANGED_CB 	"system_settings_unset_changed_cb"

static void utc_system_settings_set_string_p(void);
static void utc_system_settings_get_string_p(void);

static void utc_system_settings_set_bool_p(void);
static void utc_system_settings_get_bool_p(void);

static void utc_system_settings_get_int_p(void);
static void utc_system_settings_set_int_p(void);

static void utc_system_settings_set_changed_cb(void);
static void utc_system_settings_unset_changed_cb(void);


struct tet_testlist tet_testlist[] = {
	{utc_system_settings_set_string_p, 1},
	{utc_system_settings_set_bool_p, 1},
	{utc_system_settings_get_string_p, 1},
	{utc_system_settings_get_int_p, 1},
	{utc_system_settings_get_bool_p, 1},
	{utc_system_settings_set_int_p, 1},
	{utc_system_settings_set_changed_cb, 1},
	{utc_system_settings_unset_changed_cb, 1},
	{NULL, 0},
};

static GMainLoop *main_loop;
static int timeout = 5;

static void startup(void)
{
	main_loop = g_main_loop_new(NULL, FALSE);
}

static void cleanup(void)
{
	/* end of TC */
}

static gboolean callback(gpointer data)
{
	/*int ret =*/ system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, 1);

	static int i = 0;

	i++;
	if (timeout == i) {
		g_main_loop_quit((GMainLoop *)data);
		return FALSE;
	}

	return TRUE;
}

static void utc_system_settings_changed_motion_activation(system_settings_key_e key, void *user_data)
{

}

static void utc_system_settings_set_string_p(void)
{
	int retcode = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, "/opt/share/settings/Ringtones/General_Over the horizon.mp3");

	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		dts_pass(API_NAME_SETTINGS_SET_VALUE_STRING, "passed");
	} else {
		dts_fail(API_NAME_SETTINGS_SET_VALUE_STRING, "failed");
	}
}

static void utc_system_settings_set_bool_p(void)
{
	int retcode = system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, true);

	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		dts_pass(API_NAME_SETTINGS_SET_VALUE_BOOL, "passed");
	} else {
		dts_fail(API_NAME_SETTINGS_SET_VALUE_BOOL, "failed");
	}
}

static void utc_system_settings_get_string_p(void)
{
	char *value = NULL;
	int retcode = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, &value);

	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		dts_pass(API_NAME_SETTINGS_GET_VALUE_STRING, "passed");
	} else {
		dts_fail(API_NAME_SETTINGS_GET_VALUE_STRING, "failed");
	}
}

static void utc_system_settings_get_int_p(void)
{
	int value = -1;
	int retcode = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_FONT_SIZE, &value);

	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		dts_pass(API_NAME_SETTINGS_GET_VALUE_INT, "passed");
	} else {
		dts_fail(API_NAME_SETTINGS_GET_VALUE_INT, "failed");
	}
}

static void utc_system_settings_get_bool_p(void)
{
	bool value = false;
	int retcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, &value);

	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		dts_pass(API_NAME_SETTINGS_GET_VALUE_BOOL, "passed");
	} else {
		dts_fail(API_NAME_SETTINGS_GET_VALUE_BOOL, "failed");
	}
}

static void utc_system_settings_set_int_p(void)
{
	int retcode = system_settings_set_value_int(SYSTEM_SETTINGS_KEY_FONT_SIZE, SYSTEM_SETTINGS_FONT_SIZE_NORMAL);

	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		dts_pass(API_NAME_SETTINGS_SET_VALUE_INT, "passed");
	} else {
		dts_fail(API_NAME_SETTINGS_SET_VALUE_INT, "failed");
	}
}


static void utc_system_settings_set_changed_cb(void)
{
	int retcode = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, utc_system_settings_changed_motion_activation, NULL);

	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		dts_pass(API_NAME_SETTINGS_SET_CHANGED_CB, "passed");
	} else {
		dts_fail(API_NAME_SETTINGS_SET_CHANGED_CB, "failed");
	}

	g_timeout_add_seconds(5, callback, main_loop);
	g_main_loop_run(main_loop);
	g_main_loop_unref(main_loop);
}

static void utc_system_settings_unset_changed_cb(void)
{
	int retcode = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION);

	if (retcode == SYSTEM_SETTINGS_ERROR_NONE) {
		dts_pass(API_NAME_SETTINGS_UNSET_CHANGED_CB, "passed");
	} else {
		dts_fail(API_NAME_SETTINGS_UNSET_CHANGED_CB, "failed");
	}
}
