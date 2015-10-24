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
		SECURE_LOGD("\033[0;32mDEBUG: " fmt "\033[0m\n", ##arg);\
	}while(0);

#define SETTING_TRACE(fmt, arg...) \
	do {\
		SECURE_LOGI("\033[0;36m" fmt "\033[0m\n", ##arg);\
	}while(0);

#define SETTING_TRACE_BEGIN do {\
		SECURE_LOGD("\033[0;35mENTER FUNCTION: %s. \033[0m\n", __FUNCTION__);\
	}while(0);

#define SETTING_TRACE_END  do {\
		SECURE_LOGD("\033[0;35mEXIT FUNCTION: %s. \033[0m\n", __FUNCTION__);\
	}while(0);
#else
#define SETTING_TRACE_DEBUG(fmt, arg...)
#define SETTING_TRACE(fmt, arg...)
#define SETTING_TRACE_BEGIN
#define SETTING_TRACE_END
#endif



/**
 * @internal
 * @since_tizen 2.3
 * Enumeration for data type of internal getter/setter.
 */
typedef enum {
	SYSTEM_SETTING_DATA_TYPE_STRING,	/**< string */
	SYSTEM_SETTING_DATA_TYPE_INT,		/**< integer */
	SYSTEM_SETTING_DATA_TYPE_BOOL,		/**< boolean */
#if 0
	/*SYSTEM_SETTING_DATA_TYPE_FLOAT, */
	/*SYSTEM_SETTING_DATA_TYPE_DOULBE, */
#endif
}
system_setting_data_type_e;


/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
typedef int (*system_setting_get_value_cb)(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
typedef int (*system_setting_set_value_cb)(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
typedef int (*system_setting_set_changed_callback_cb)(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
typedef int (*system_setting_unset_changed_callback_cb)(system_settings_key_e key);


/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 */
typedef struct {
	system_settings_key_e key;										/**< key */
	system_setting_data_type_e data_type;							/**< data type */
	system_setting_get_value_cb get_value_cb;						/**< function pointer for getter */
	system_setting_set_value_cb set_value_cb;						/**< function pointer for setter */

	system_setting_set_changed_callback_cb set_changed_cb;			/**< function pointer to register for notification callback */
	system_setting_unset_changed_callback_cb unset_changed_cb ;		/**< function pointer to un-register for notification callback */

	system_settings_changed_cb changed_cb;							/* registered by user application */
	void *user_data;												/* user_data */

} system_setting_s;

typedef system_setting_s *system_setting_h;


/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_settings_get_item(system_settings_key_e key, system_setting_h *item);


/* get */

/**
 * @internal
 * @brief get vconf of in type value
 * @since_tizen 2.3
 *
 * @param[in] vconf_key string
 * @param[out] value get the integer type value
 *
 * @return 0 on success, -1 on error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_vconf_get_value_int(const char *vconf_key, int *value);

/**
 * @internal
 * @brief get vconf of in bool value
 * @since_tizen 2.3
 *
 * @param[in] vconf_key string
 * @param[out] value get the bool type value
 *
 * @return 0 on success, -1 on error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_vconf_get_value_bool(const char *vconf_key, bool *value);

/**
 * @internal
 * @brief get vconf of string type value
 * @since_tizen 2.3
 *
 * @param[in] vconf_key string
 * @param[out] value get the string(char*) type value
 *
 * @return 0 on success, -1 on error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_vconf_get_value_string(const char *vconf_key, char **value);

/**
 * @internal
 * @brief set the int type vconf value
 * @since_tizen 2.3
 *
 * @param[in] vconf_key key name
 * @param[in] value int type value
 *
 * @return 0 on success, -1 on error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_vconf_set_value_int(const char *vconf_key, int value);

/**
 * @internal
 * @brief set the bool type vconf value
 * @since_tizen 2.3
 *
 * @param[in] vconf_key key name
 * @param[in] value bool type value
 *
 * @return 0 on success, -1 on error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_vconf_set_value_bool(const char *vconf_key, bool value);

/**
 * @internal
 * @brief set the string type vconf value
 * @since_tizen 2.3
 *
 * @param[in] vconf_key key name
 * @param[in] value string type value
 *
 * @return 0 on success, -1 on error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_vconf_set_value_string(const char *vconf_key, char *value);

/**
 * @internal
 * @brief Set the system settings notification callback
 * @since_tizen 2.3
 * @param[in] vconf_key
 * @param[in] key
 * @param[in] slot internal slot to set the key (0~4)
 * @param[in] user_data user data
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_vconf_set_changed_cb(const char *vconf_key, system_settings_key_e key, int slot, void *user_data);

/**
 * @internal
 * @brief Unset the system settings notification callback
 * @since_tizen 2.3
 * @param[in] vconf_key vconf key name used in the code
 * @param[in] slot internal slot to set the key (0~4)
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_vconf_unset_changed_cb(const char *vconf_key, int slot);

/**
 * @internal
 * @brief get current font size
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_FONT_SIZE
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_INT
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set current font size
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_FONT_SIZE
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_INT
 * @param[out] value the font size
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_font_size(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_font_size(system_settings_key_e key);



/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set current path of the ringtone
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_STRING
 * @param[out] value the ringtone
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_incoming_call_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_incoming_call_ringtone(system_settings_key_e key);


/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_email_alert_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set current path of the email-alert
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_STRING
 * @param[out] value the alert ringtone
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_email_alert_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_email_alert_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_email_alert_ringtone(system_settings_key_e key);



/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set current path of the wallpaper
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_STRING
 * @param[out] value the wallpaper
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_wallpaper_home_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_wallpaper_home_screen(system_settings_key_e key);



/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set current path of the bg image of the lock screen
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_STRING
 * @param[out] value the lock screen
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_wallpaper_lock_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_wallpaper_lock_screen(system_settings_key_e key);


/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_default_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void **value);


/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set name of the font name
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_FONT_TYPE
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_STRING
 * @param[out] value the font type
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_font_type(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_font_type(system_settings_key_e key);


/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set on/off of the motion activation
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_BOOL
 * @param[out] value the motion activation
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_motion_activation(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_motion_activation(system_settings_key_e key);


/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_usb_debugging_option(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set on/off of the debugging options
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_BOOL
 * @param[out] value the usb debug option
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_usb_debugging_option(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_usb_debugging_option(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_usb_debugging_option(system_settings_key_e key);


/**
 * @internal
 * @since_tizen 2.3
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_3g_data_network(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @brief set on/off of the 3G data network option
 * @since_tizen 2.3
 * @param[in] key key name should be SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED
 * @param[in] datatype should be SYSTEM_SETTING_DATA_TYPE_BOOL
 * @param[out] value the 3G data network option
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_3g_data_network(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_3g_data_network(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_3g_data_network(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_tap_and_hold_delay(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_tap_and_hold_delay(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_tap_and_hold_delay(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_tap_and_hold_delay(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_lockscreen_app(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_lockscreen_app(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_lockscreen_app(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_lockscreen_app(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_locale_country(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_locale_country(system_settings_key_e key, system_setting_data_type_e data_type, void *value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_locale_country(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_locale_country(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_locale_language(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_locale_language(system_settings_key_e key, system_setting_data_type_e data_type, void *value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_locale_language(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_locale_language(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_locale_timeformat_24hour(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_locale_timeformat_24hour(system_settings_key_e key, system_setting_data_type_e data_type, void *value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_locale_timeformat_24hour(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_locale_timeformat_24hour(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_locale_timezone(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_locale_timezone_changed(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_locale_timezone_changed(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_time_changed(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_time_changed(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_time_changed(system_settings_key_e key);


/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_sound_lock(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_sound_lock(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_sound_lock(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_sound_silent_mode(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_sound_silent_mode(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_sound_silent_mode(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_sound_silent_mode(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_sound_touch(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_sound_touch(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_sound_touch(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_auto_rotation_mode(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_auto_rotation_mode(system_settings_key_e key, system_setting_data_type_e data_type, void *value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_auto_rotation_mode(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_auto_rotation_mode(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_screen_backlight_time(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_screen_backlight_time(system_settings_key_e key, system_setting_data_type_e data_type, void *value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_screen_backlight_time(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_screen_backlight_time(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_sound_notification(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_sound_notification(system_settings_key_e key, system_setting_data_type_e data_type, void *value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_sound_notification(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_sound_notification(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_notification_repetition_period(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_notification_repetition_period(system_settings_key_e key, system_setting_data_type_e data_type, void *value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_notification_repetition_period(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_notification_repetition_period(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_device_name(system_settings_key_e key, system_setting_data_type_e data_type, void **value);
/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_device_name(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_device_name(system_settings_key_e key);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_network_flight_mode(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_network_flight_mode(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_network_flight_mode(system_settings_key_e key);



/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_network_wifi_notification(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_network_wifi_notification(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_network_wifi_notification(system_settings_key_e key);


/**
 * @internal
 * @brief get current Idle Lock State
 * @since_tizen 2.3.1
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_get_lock_state(system_settings_key_e key, system_setting_data_type_e data_type, void **value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_lock_state(system_settings_key_e key, system_setting_data_type_e data_type, void *value);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_set_changed_callback_lock_state(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @internal
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_setting_unset_changed_callback_lock_state(system_settings_key_e key);


/*// */


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_SETTING_PRIVATE_H__ */



