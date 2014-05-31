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

#ifndef __TIZEN_SYSTEM_SYSTEM_SETTINGS_H__
#define __TIZEN_SYSTEM_SYSTEM_SETTINGS_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define SUPPORT_ACCESSIBILITY 0
 /**
 * @addtogroup CAPI_SYSTEM_SYSTEM_SETTINGS_MODULE
 * @{
 */


/**
 * @brief Enumeration of error code for system settings
 */
typedef enum
{
	SYSTEM_SETTINGS_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful */
	SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
	SYSTEM_SETTINGS_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY, /**< Out of memory */
	SYSTEM_SETTINGS_ERROR_IO_ERROR =  TIZEN_ERROR_IO_ERROR, /**< Internal I/O error */

	// lock screen app error code
	SYSTEM_SETTINGS_ERROR_LOCKSCREEN_APP_PASSWORD_MODE, /**< current lock screen app set 'password' type */
} system_settings_error_e;


/**
 * @brief Enumeration of key for system settings
 */
typedef enum
{
	SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, /**< The file path of the current ringtone */
	SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, /**< The file path of the current home screen wallpaper */
	SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, /**< The file path of the current lock screen wallpaper */
	SYSTEM_SETTINGS_KEY_FONT_SIZE, /**< The current system font size */
	SYSTEM_SETTINGS_KEY_FONT_TYPE, /**< The current system font type */
	SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, /**< Indicates whether the motion service is activated */
	SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE,  /**< The file path of the current email alert ringtone */
	SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED,  /**< Indicates whether the usb debugging is enabled */
	SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED,  /**< Indicates whether the 3G data network is enabled */
#if SUPPORT_ACCESSIBILITY
	SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY,  /**< Indicates delaying time of 'tab and hold' (sec) */
#endif
	SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP,  /**< Indicates lockscreen app pkg name (string) */
	SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE,/**< The current system default font type (only support Get) */
} system_settings_key_e;

#if SUPPORT_ACCESSIBILITY
/**
 * @brief Enumeration of tab and hold delay
 */
typedef enum
{
	SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_SHORT = 500, /**< 500 msec */
	SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_MEDIUM = 1000, /**< 1000 msec */
	SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_LONG = 1500, /**< 1500 msec */
} system_settings_tap_and_hold_delay_e;
#endif
/**
 * @brief Enumeration of font size
 */
typedef enum
{
	SYSTEM_SETTINGS_FONT_SIZE_SMALL = 0, /**< A small size */
	SYSTEM_SETTINGS_FONT_SIZE_NORMAL, /**< A normal size */
	SYSTEM_SETTINGS_FONT_SIZE_LARGE, /**< A large size */
	SYSTEM_SETTINGS_FONT_SIZE_HUGE, /**< A huge size */
	SYSTEM_SETTINGS_FONT_SIZE_GIANT, /**< A giant size */
} system_settings_font_size_e;


/**
 * @brief Called when the system settings changes
 * @param[in] key The key name of the system settings changed
 * @param[in] user_data The user data passed from the callback registration function
 * @pre system_settings_set_changed_cb() will invoke this callback function.
 * @see system_settings_set_changed_cb()
 * @see system_settings_unset_changed_cb()
 */
typedef void (*system_settings_changed_cb)(system_settings_key_e key, void *user_data);

/**
 * @brief Sets the system settings value associated with the given key as an integer.
 * @param[in] key The key name of the system settings
 * @param[out] value The new system settings value of the given key
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 */
int system_settings_set_value_int(system_settings_key_e key, int value);

/**
 * @brief Gets the system settings value associated with the given key as an integer.
 * @param[in] key The key name of the system settings
 * @param[out] value The current system settings value of the given key
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 */
int system_settings_get_value_int(system_settings_key_e key, int *value);


/**
 * @brief Sets the system settings value associated with the given key as a boolean.
 * @param[in] key The key name of the system settings
 * @param[out] value The new system settings value of the given key
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 */
int system_settings_set_value_bool(system_settings_key_e key, bool value);

/**
 * @brief Gets the system settings value associated with the given key as a boolean.
 * @param[in] key The key name of the system settings
 * @param[out] value The current system settings value of the given key
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 */
int system_settings_get_value_bool(system_settings_key_e key, bool *value);


/**
 * @brief Sets the system settings value associated with the given key as a double.
 * @param[in] key The key name of the system settings
 * @param[out] value The new system settings value of the given key
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 */
int system_settings_set_value_double(system_settings_key_e key, double value);

/**
 * @brief Gets the system settings value associated with the given key as a double.
 * @param[in] key The key name of the system settings
 * @param[out] value The current system settings value of the given key
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 */
int system_settings_get_value_double(system_settings_key_e key, double *value);


/**
 * @brief Sets the system settings value associated with the given key as a string.
 * @param[in] key The key name of the system settings
 * @param[out] value The new system settings value of the given key
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 *
 * @remarks SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE is not available for set
 */
int system_settings_set_value_string(system_settings_key_e key, const char *value);

/**
 * @brief Gets the system settings value associated with the given key as a string.
 * @remarks @a value must be released with @c free() by you.
 * @param[in] key The key name of the system settings
 * @param[out] value The current system settings value of the given key
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 */
int system_settings_get_value_string(system_settings_key_e key, char **value);


/**
 * @brief Registers a change event callback for the given system settings key.
 * @param[in] key The key name of the system settings
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @post system_settings_changed_cb() will be invoked.
 *
 * @see system_settings_unset_changed_cb()
 * @see system_settings_changed_cb()
 *
 * @remarks SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE is not available for set_changed_cb
*/
int system_settings_set_changed_cb(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);


/**
 * @brief Unregisters the callback function.
 * @param[in] key The key name of the system settings
 * @return  0 on success, otherwise a negative error value.
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see system_settings_set_changed_cb()
 *
 * @remarks SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE is not available for set_changed_cb
 */
int system_settings_unset_changed_cb(system_settings_key_e key);


/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_SYSTEM_SETTINGS_H__ */
