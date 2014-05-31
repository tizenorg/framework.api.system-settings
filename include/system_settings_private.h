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


#ifndef __TIZEN_SYSTEM_SETTING_PRIVATE_H__
#define __TIZEN_SYSTEM_SETTING_PRIVATE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "SYSTEM-SETTINGS"

#define SYSTEM_SETTINGS_ENABLE_TRACE

#ifdef SYSTEM_SETTINGS_ENABLE_TRACE

	#define SETTING_TRACE_DEBUG(fmt, arg...) \
		do {\
			SECURE_LOGD("\n\033[0;32mDEBUG: " fmt "\033[0m\t%s:%d\n", \
	##arg, (char*)(strrchr(__FILE__, '/')+1), __LINE__);\
		}while(0);

	#define SETTING_TRACE(fmt, arg...) \
		do {\
			SECURE_LOGD("\n\033[0;36m" fmt "\033[0m\t%s:%d\n", \
	##arg, (char*)(strrchr(__FILE__, '/')+1), __LINE__);\
		}while(0);

	#define SETTING_TRACE_BEGIN do {\
		{\
			printf("\n[SETTING]\033[0;35mENTER FUNCTION: %s. \033[0m\t%s:%d\n", \
					__FUNCTION__, (char*)(strrchr(__FILE__, '/')+1), __LINE__);\
		}\
	}while(0);

	#define SETTING_TRACE_END  do {\
		{\
			printf("\n[SETTING]\033[0;35mEXIT FUNCTION: %s. \033[0m\t%s:%d\n", \
					__FUNCTION__, (char*)(strrchr(__FILE__, '/')+1), __LINE__);\
		}\
	}while(0);

#else
	#define SETTING_TRACE_DEBUG(fmt, arg...)
	#define SETTING_TRACE(fmt, arg...)
    #define SETTING_TRACE_BEGIN
    #define SETTING_TRACE_END
#endif


#define VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_NAME  "db/setting/accessibility/font_name"

typedef enum {
	SYSTEM_SETTING_DATA_TYPE_STRING,
	SYSTEM_SETTING_DATA_TYPE_INT,
	SYSTEM_SETTING_DATA_TYPE_DOUBLE,
	SYSTEM_SETTING_DATA_TYPE_BOOL,
	SYSTEM_SETTING_DATA_TYPE_FLOAT,
} system_setting_data_type_e;


typedef int (*system_setting_get_value_cb) (system_settings_key_e key, system_setting_data_type_e data_type, void** value);
typedef int (*system_setting_set_value_cb) (system_settings_key_e key, system_setting_data_type_e data_type, void* value);

typedef int (*system_setting_set_changed_callback_cb)(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
typedef int (*system_setting_unset_changed_callback_cb)(system_settings_key_e key);


typedef struct {
	system_settings_key_e key;										/* key */
	system_setting_data_type_e data_type;
	system_setting_get_value_cb get_value_cb;						/* get value */
	system_setting_set_value_cb set_value_cb;						/* set value */

	system_setting_set_changed_callback_cb set_changed_cb;
	system_setting_unset_changed_callback_cb unset_changed_cb ;

	system_settings_changed_cb changed_cb;							/* registered by user application */
	void* user_data;												/* user_data */

} system_setting_s;

typedef system_setting_s* system_setting_h;


int system_settings_get_item(system_settings_key_e key, system_setting_h *item);


// get

/**
* @brief get vconf of in type value
*
* @param[in] vconf_key string
* @param[out] value get the integer type value
*
* @return 0 on success, -1 on error
*/
int system_setting_vconf_get_value_int(const char *vconf_key, int *value);

/**
* @brief get vconf of in bool value
*
* @param[in] vconf_key string
* @param[out] value get the bool type value
*
* @return 0 on success, -1 on error
*/
int system_setting_vconf_get_value_bool(const char *vconf_key, bool *value);

/**
* @brief get vconf of double type value
*
* @param[in] vconf_key string
* @param[out] value get the double type value
*
* @return 0 on success, -1 on error
*/
int system_setting_vconf_get_value_double(const char *vconf_key, double *value);

/**
* @brief get vconf of string type value
*
* @param[in] vconf_key string
* @param[out] value get the string(char*) type value
*
* @return 0 on success, -1 on error
*/
int system_setting_vconf_get_value_string(const char *vconf_key, char **value);

/**
* @brief set the int type vconf value
*
* @param[in] vconf_key key name
* @param[in] value int type value
*
* @return 0 on success, -1 on error
*/
int system_setting_vconf_set_value_int(const char *vconf_key, int value);

/**
* @brief set the bool type vconf value
*
* @param[in] vconf_key key name
* @param[in] value bool type value
*
* @return 0 on success, -1 on error
*/
int system_setting_vconf_set_value_bool(const char *vconf_key, bool value);

/**
* @brief set the double type vconf value
*
* @param[in] vconf_key key name
* @param[in] value double type value
*
* @return 0 on success, -1 on error
*/
int system_setting_vconf_set_value_double(const char *vconf_key, double value);

/**
* @brief set the string type vconf value
*
* @param[in] vconf_key key name
* @param[in] value string type value
*
* @return 0 on success, -1 on error
*/
int system_setting_vconf_set_value_string(const char *vconf_key, char *value);


int system_setting_vconf_set_changed_cb(const char *vconf_key, system_settings_key_e key, int slot, void* user_data);

int system_setting_vconf_unset_changed_cb(const char *vconf_key, int slot);

int system_setting_get_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_email_alert_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_usb_debugging_option(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_3g_data_network(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_tap_and_hold_delay(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_lockscreen_app(system_settings_key_e key, system_setting_data_type_e data_type, void** value);

int system_setting_get_default_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void** value);

int system_setting_set_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_email_alert_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_usb_debugging_option(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_3g_data_network(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_tap_and_hold_delay(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_lockscreen_app(system_settings_key_e key, system_setting_data_type_e data_type, void* value);

int system_setting_set_changed_callback_incoming_call_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_incoming_call_ringtone(system_settings_key_e key);

int system_setting_set_changed_callback_email_alert_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_email_alert_ringtone(system_settings_key_e key);

int system_setting_set_changed_callback_wallpaper_home_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_wallpaper_home_screen(system_settings_key_e key);

int system_setting_set_changed_callback_wallpaper_lock_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_wallpaper_lock_screen(system_settings_key_e key);

int system_setting_set_changed_callback_font_size(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_font_size(system_settings_key_e key);

int system_setting_set_changed_callback_font_type(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_font_type(system_settings_key_e key);

int system_setting_set_changed_callback_motion_activation(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_motion_activation(system_settings_key_e key);

int system_setting_set_changed_callback_usb_debugging_option(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_usb_debugging_option(system_settings_key_e key);

int system_setting_set_changed_callback_3g_data_network(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_3g_data_network(system_settings_key_e key);

int system_setting_set_changed_callback_tap_and_hold_delay(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_tap_and_hold_delay(system_settings_key_e key);

int system_setting_set_changed_callback_lockscreen_app(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_lockscreen_app(system_settings_key_e key);

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_SETTING_PRIVATE_H__ */



