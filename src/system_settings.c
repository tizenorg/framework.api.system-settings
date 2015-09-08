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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vconf.h>
#include <dlog.h>

#include <system_settings.h>
#include <system_settings_private.h>

#include <glib.h>


#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_SYSTEM_SETTINGS"

#define SYSTEM_SETTINGS_MAX -1



system_setting_s system_setting_table[] = {

	{
		SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_incoming_call_ringtone,
		system_setting_set_incoming_call_ringtone,
		system_setting_set_changed_callback_incoming_call_ringtone,
		system_setting_unset_changed_callback_incoming_call_ringtone,
		NULL,
		NULL		/* user data */
	},

	{
		SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_wallpaper_home_screen,
		system_setting_set_wallpaper_home_screen,
		system_setting_set_changed_callback_wallpaper_home_screen,
		system_setting_unset_changed_callback_wallpaper_home_screen,
		NULL,
		NULL		/* user data */
	},

	{
		SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_wallpaper_lock_screen,
		system_setting_set_wallpaper_lock_screen,
		system_setting_set_changed_callback_wallpaper_lock_screen,
		system_setting_unset_changed_callback_wallpaper_lock_screen,
		NULL,
		NULL		/* user data */
	},

	{
		SYSTEM_SETTINGS_KEY_FONT_SIZE,
		SYSTEM_SETTING_DATA_TYPE_INT,
		system_setting_get_font_size,
		system_setting_set_font_size,
		system_setting_set_changed_callback_font_size,
		system_setting_unset_changed_callback_font_size,
		NULL,
		NULL		/* user data */
	},

	{
		SYSTEM_SETTINGS_KEY_FONT_TYPE,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_font_type,
		system_setting_set_font_type,
		system_setting_set_changed_callback_font_type,
		system_setting_unset_changed_callback_font_type,
		NULL,
		NULL		/* user data */
	},

#ifdef TIZEN_WEARABLE
	{
		SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_not_supported_now,
		system_setting_set_not_supported_now,
		system_setting_set_changed_callback_not_supported_now,
		system_setting_unset_changed_callback_not_supported_now,
		NULL,
		NULL		/* user data */
	},
#else
	{
		SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_motion_activation,
		system_setting_set_motion_activation,
		system_setting_set_changed_callback_motion_activation,
		system_setting_unset_changed_callback_motion_activation,
		NULL,
		NULL		/* user data */
	},
#endif

	{
		SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_email_alert_ringtone,
		system_setting_set_email_alert_ringtone,
		system_setting_set_changed_callback_email_alert_ringtone,
		system_setting_unset_changed_callback_email_alert_ringtone,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_usb_debugging_option,
		system_setting_set_usb_debugging_option,
		system_setting_set_changed_callback_usb_debugging_option,
		system_setting_unset_changed_callback_usb_debugging_option,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_3g_data_network,
		system_setting_set_3g_data_network,
		system_setting_set_changed_callback_3g_data_network,
		system_setting_unset_changed_callback_3g_data_network,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY,
		SYSTEM_SETTING_DATA_TYPE_INT,
		system_setting_get_tap_and_hold_delay,
		system_setting_set_tap_and_hold_delay,
		system_setting_set_changed_callback_tap_and_hold_delay,
		system_setting_unset_changed_callback_tap_and_hold_delay,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_lockscreen_app,
		system_setting_set_lockscreen_app,
		system_setting_set_changed_callback_lockscreen_app,
		system_setting_unset_changed_callback_lockscreen_app,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_default_font_type,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_locale_country,
		system_setting_set_locale_country,
		system_setting_set_changed_callback_locale_country,
		system_setting_unset_changed_callback_locale_country,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_locale_language,
		system_setting_set_locale_language,
		system_setting_set_changed_callback_locale_language,
		system_setting_unset_changed_callback_locale_language,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_locale_timeformat_24hour,
		system_setting_set_locale_timeformat_24hour,
		system_setting_set_changed_callback_locale_timeformat_24hour,
		system_setting_unset_changed_callback_locale_timeformat_24hour,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_LOCALE_TIMEZONE,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_locale_timezone,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_TIME_CHANGED,
		SYSTEM_SETTING_DATA_TYPE_INT,
		system_setting_get_time_changed,
		NULL,
		system_setting_set_changed_callback_time_changed,
		system_setting_unset_changed_callback_time_changed,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_SOUND_LOCK,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_sound_lock,
		NULL,
		system_setting_set_changed_callback_sound_lock,
		system_setting_unset_changed_callback_sound_lock,
		NULL,
		NULL		/* user data */
	},

#ifdef TIZEN_WEARABLE
	{
		SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_not_supported_now,
		system_setting_set_not_supported_now,
		system_setting_set_changed_callback_not_supported_now,
		system_setting_unset_changed_callback_not_supported_now,
		NULL,
		NULL		/* user data */
	},
#else
	{
		SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_sound_silent_mode,
		system_setting_set_sound_silent_mode,
		system_setting_set_changed_callback_sound_silent_mode,
		system_setting_unset_changed_callback_sound_silent_mode,
		NULL,
		NULL		/* user data */
	},
#endif
	{
		SYSTEM_SETTINGS_KEY_SOUND_TOUCH,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_sound_touch,
		NULL,
		system_setting_set_changed_callback_sound_touch,
		system_setting_unset_changed_callback_sound_touch,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_auto_rotation_mode,
		system_setting_set_auto_rotation_mode,
		system_setting_set_changed_callback_auto_rotation_mode,
		system_setting_unset_changed_callback_auto_rotation_mode,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_SCREEN_BACKLIGHT_TIME,
		SYSTEM_SETTING_DATA_TYPE_INT,
		system_setting_get_screen_backlight_time,
		system_setting_set_screen_backlight_time,
		system_setting_set_changed_callback_screen_backlight_time,
		system_setting_unset_changed_callback_screen_backlight_time,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_sound_notification,
		system_setting_set_sound_notification,
		system_setting_set_changed_callback_sound_notification,
		system_setting_unset_changed_callback_sound_notification,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION_REPETITION_PERIOD,
		SYSTEM_SETTING_DATA_TYPE_INT,
		system_setting_get_notification_repetition_period,
		system_setting_set_notification_repetition_period,
		system_setting_set_changed_callback_notification_repetition_period,
		system_setting_unset_changed_callback_notification_repetition_period,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_KEY_DEVICE_NAME,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_device_name,
		NULL,
		system_setting_set_changed_callback_device_name,
		system_setting_unset_changed_callback_device_name,
		NULL,
		NULL		/* user data */
	},
#ifdef TIZEN_WEARABLE
	{
		SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_not_supported_now,
		system_setting_set_not_supported_now,
		system_setting_set_changed_callback_not_supported_now,
		system_setting_unset_changed_callback_not_supported_now,
		NULL,
		NULL		/* user data */
	},
#else
	{
		SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_network_flight_mode,
		NULL,
		system_setting_set_changed_callback_network_flight_mode,
		system_setting_unset_changed_callback_network_flight_mode,
		NULL,
		NULL		/* user data */
	},
#endif
#ifdef TIZEN_WEARABLE
	{
		SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_not_supported_now,
		system_setting_set_not_supported_now,
		system_setting_set_changed_callback_not_supported_now,
		system_setting_unset_changed_callback_not_supported_now,
		NULL,
		NULL		/* user data */
	},
#else
	{
		SYSTEM_SETTINGS_KEY_NETWORK_WIFI_NOTIFICATION,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_network_wifi_notification,
		NULL,
		system_setting_set_changed_callback_network_wifi_notification,
		system_setting_unset_changed_callback_network_wifi_notification,
		NULL,
		NULL		/* user data */
	},
#endif
	{
		SYSTEM_SETTINGS_KEY_LOCK_STATE,
		SYSTEM_SETTING_DATA_TYPE_INT,
		system_setting_get_lock_state,
		system_setting_set_lock_state,
		system_setting_set_changed_callback_lock_state,
		system_setting_unset_changed_callback_lock_state,
		NULL,
		NULL		/* user data */
	},
	{
		SYSTEM_SETTINGS_MAX, -1, NULL, NULL, NULL, NULL, NULL, NULL
	}
};

static void _dump_context()
{
	int i;
	/*int max = SYSTEM_SETTINGS_MAX; */
	int max = sizeof(system_setting_table)/sizeof(system_setting_s) -1 ;

	for (i=0; i<27; i++) {
		LOGE("[%s] system_setting_table[i].key = %d", __FUNCTION__, system_setting_table[i].key);
		LOGE("[%s] system_setting_table[i].data_type = %d", __FUNCTION__, system_setting_table[i].data_type);
		LOGE("[%s] system_setting_table[i].get_value_cb = %x", __FUNCTION__, system_setting_table[i].get_value_cb);
		LOGE("[%s] system_setting_table[i].set_value_cb = %x", __FUNCTION__, system_setting_table[i].set_value_cb);

		LOGE("[%s] system_setting_table[i].set_changed_cb = %x <---", __FUNCTION__, system_setting_table[i].set_changed_cb);
		LOGE("[%s] system_setting_table[i].unset_changed_cb = %x", __FUNCTION__, system_setting_table[i].unset_changed_cb);
		LOGE("[%s] system_setting_table[i].changed_cb = %x", __FUNCTION__, system_setting_table[i].changed_cb);
	}
}

static int _dump_context_node(int key)
{
	int index = 0;

	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	while (system_setting_table[index].key != SYSTEM_SETTINGS_MAX) {
		if (system_setting_table[index].key == key) {
			int i = index;
			LOGE("[%s] system_setting_table[i].key = %d", __FUNCTION__, system_setting_table[i].key);
			LOGE("[%s] system_setting_table[i].data_type = %d", __FUNCTION__, system_setting_table[i].data_type);
			LOGE("[%s] system_setting_table[i].get_value_cb = %x", __FUNCTION__, system_setting_table[i].get_value_cb);
			LOGE("[%s] system_setting_table[i].set_value_cb = %x", __FUNCTION__, system_setting_table[i].set_value_cb);
			LOGE("[%s] system_setting_table[i].set_changed_cb = %x <---", __FUNCTION__, system_setting_table[i].set_changed_cb);
			LOGE("[%s] system_setting_table[i].unset_changed_cb = %x", __FUNCTION__, system_setting_table[i].unset_changed_cb);
			LOGE("[%s] system_setting_table[i].changed_cb = %x", __FUNCTION__, system_setting_table[i].changed_cb);
			return 0;
		}
		index++;
	}

	return -1;
}

int system_settings_get_item(system_settings_key_e key, system_setting_h *item)
{
	int index = 0;

	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}
#if 0
	_dump_context();
#endif
	while (system_setting_table[index].key != SYSTEM_SETTINGS_MAX) {
		if (system_setting_table[index].key == key) {
			*item = &system_setting_table[index];
			LOGE("Enter [%s], index = %d, key = %d, type = %d", __FUNCTION__, index, key, (*item)->data_type);
			return 0;
		}

		index++;
	}

	return -1;
}

int system_settings_get_value(system_settings_key_e key, system_setting_data_type_e data_type, void **value)
{
	LOGE("Enter [%s]", __FUNCTION__);
	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	system_setting_h system_setting_item;
	system_setting_get_value_cb	system_setting_getter;

	if (0 != system_settings_get_item(key, &system_setting_item)) {
		_dump_context_node(key);
		LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key --- (%d)", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER, key);
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	if (system_setting_item->data_type != data_type) {
		_dump_context_node(key);
		LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid data type --- key : (%d), datatype:(%d)", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER, key, data_type);
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	system_setting_getter = system_setting_item->get_value_cb;

	if (system_setting_getter == NULL) {
		LOGE("[%s] IO_ERROR(0x%08x) : failed to call getter for the system settings", __FUNCTION__, SYSTEM_SETTINGS_ERROR_IO_ERROR);
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return system_setting_getter(key, system_setting_item->data_type, value);
}

int system_settings_set_value(system_settings_key_e key, system_setting_data_type_e data_type, void *value)
{
	LOGE("Enter [%s]", __FUNCTION__);
	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key) || value == NULL) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}


	system_setting_h system_setting_item;
	system_setting_set_value_cb	system_setting_setter;

	int ret = system_settings_get_item(key, &system_setting_item);

	if (0 != ret) {
		LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		return SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED;
	}

	/* type check */
	if (system_setting_item->data_type != data_type) {
		LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid data type", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	system_setting_setter = system_setting_item->set_value_cb;

	if (system_setting_setter == NULL) {
		LOGE("[%s] IO_ERROR(0x%08x) : failed to call setter for the system settings", __FUNCTION__, SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED);
		return SYSTEM_SETTINGS_ERROR_NOT_SUPPORTED;
	}

	return system_setting_setter(key, system_setting_item->data_type, value);
}

int system_settings_set_value_int(system_settings_key_e key, int value)
{
	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	int *ptr = &value;
	return system_settings_set_value(key, SYSTEM_SETTING_DATA_TYPE_INT,(void *)ptr);
}

int system_settings_get_value_int(system_settings_key_e key, int *value)
{
	LOGE("Enter [%s]", __FUNCTION__);
	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	return system_settings_get_value(key, SYSTEM_SETTING_DATA_TYPE_INT, (void **)value);
}

int system_settings_set_value_bool(system_settings_key_e key, bool value)
{
	LOGE("Enter [%s]", __FUNCTION__);
	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	bool *ptr = &value;
	return system_settings_set_value(key, SYSTEM_SETTING_DATA_TYPE_BOOL,(void *)ptr);
}

int system_settings_get_value_bool(system_settings_key_e key, bool *value)
{
	LOGE("Enter [%s]", __FUNCTION__);
	int flag = 0;

	int ret;

	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	ret = system_settings_get_value(key, SYSTEM_SETTING_DATA_TYPE_BOOL, (void **)&flag);
	SETTING_TRACE(" inf (flag) value : %d ", flag);
	if (flag == 0) {
		*value = false;
		SETTING_TRACE(" flag == 0 ");
	} else if (flag == 1) {
		*value = true;
		SETTING_TRACE(" flag == 1 ");
	} else {
		*value = false;
		SETTING_TRACE(" exception here!!! ");
	}

	return ret;
}

int system_settings_set_value_string(system_settings_key_e key, const char *value)
{
	LOGE("Enter [%s]", __FUNCTION__);
	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}


	if (key == SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE)
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;

	return system_settings_set_value(key, SYSTEM_SETTING_DATA_TYPE_STRING,(void *)value);
}

int system_settings_get_value_string(system_settings_key_e key, char **value)
{
	LOGE("Enter [%s]", __FUNCTION__);
	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	return system_settings_get_value(key, SYSTEM_SETTING_DATA_TYPE_STRING, (void **)value);
}


/*
	- START
		- system_settings_set_changed_cb
			-> int (*system_setting_set_changed_callback_cb)(key, callback, user_data)
*/

/*PUBLIC*/
int system_settings_set_changed_cb(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	LOGE("Enter [%s]", __FUNCTION__);
	system_setting_h system_setting_item;
	system_setting_set_changed_callback_cb system_setting_set_changed_cb;

	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	if (key == SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE)
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;

	if (system_settings_get_item(key, &system_setting_item)) {
		LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	system_setting_set_changed_cb = system_setting_item->set_changed_cb;


	/* Store the callback function from application side */
	if (callback)
		system_setting_item->changed_cb = callback;

	if (user_data)
		system_setting_item->user_data = user_data;

	if (system_setting_set_changed_cb == NULL) {
		LOGE("[%s] IO_ERROR(0x%08x) : failed to call getter for the system settings", __FUNCTION__, SYSTEM_SETTINGS_ERROR_IO_ERROR);
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return system_setting_set_changed_cb(key, callback, user_data);
}


int system_settings_unset_changed_cb(system_settings_key_e key)
{
	LOGE("Enter [%s]", __FUNCTION__);
	system_setting_h system_setting_item;
	system_setting_unset_changed_callback_cb system_setting_unset_changed_cb;

	if (!(key >= 0 && SYSTEM_SETTINGS_KEY_MAX > key)) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	if (key == SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE)
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;

	int ret = system_settings_get_item(key, &system_setting_item) ;
	if (ret) {
		LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	system_setting_unset_changed_cb = system_setting_item->unset_changed_cb;

	/* free the callback function from application side */
	if (system_setting_item->changed_cb)
		system_setting_item->changed_cb = NULL;
	/*----------------------------------------------------- */

	if (system_setting_unset_changed_cb == NULL) {
		LOGE("[%s] IO_ERROR(0x%08x) : failed to call getter for the system settings", __FUNCTION__, SYSTEM_SETTINGS_ERROR_IO_ERROR);
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return system_setting_unset_changed_cb(key);
}

