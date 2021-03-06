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
		NULL
	}, 

	{
		SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_wallpaper_home_screen,
		system_setting_set_wallpaper_home_screen,
		system_setting_set_changed_callback_wallpaper_home_screen,
		system_setting_unset_changed_callback_wallpaper_home_screen,
		NULL
	},

	{
		SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_wallpaper_lock_screen,
		system_setting_set_wallpaper_lock_screen,
		system_setting_set_changed_callback_wallpaper_lock_screen,
		system_setting_unset_changed_callback_wallpaper_lock_screen,
		NULL
	},

	{
		SYSTEM_SETTINGS_KEY_FONT_SIZE,
		SYSTEM_SETTING_DATA_TYPE_INT,
		system_setting_get_font_size,
		system_setting_set_font_size,
		system_setting_set_changed_callback_font_size,
		system_setting_unset_changed_callback_font_size,
		NULL
	},

	{
		SYSTEM_SETTINGS_KEY_FONT_TYPE,
		SYSTEM_SETTING_DATA_TYPE_STRING,
		system_setting_get_font_type,
		system_setting_set_font_type,
		system_setting_set_changed_callback_font_type,
		system_setting_unset_changed_callback_font_type,
		NULL
	},

	{
		SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION,
		SYSTEM_SETTING_DATA_TYPE_BOOL,
		system_setting_get_motion_activation,
		system_setting_set_motion_activation,
		system_setting_set_changed_callback_motion_activation,
		system_setting_unset_changed_callback_motion_activation,
		NULL
	},
	{
		SYSTEM_SETTINGS_MAX, -1, NULL, NULL, NULL, NULL, NULL
	}
};

int system_settings_get_item(system_settings_key_e key, system_setting_h *item)
{
    int index = 0;

    while (system_setting_table[index].key != SYSTEM_SETTINGS_MAX)
    {   
        if (system_setting_table[index].key == key)
        {   
            *item = &system_setting_table[index];
            return 0;
        }   

        index++;
    }   

    return -1; 
}

int system_settings_get_value(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
    system_setting_h system_setting_item;
	system_setting_get_value_cb	system_setting_getter;

    if (system_settings_get_item(key, &system_setting_item))
    {
        LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
        return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
    }

    if (system_setting_item->data_type != data_type)
    {
        LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid data type", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
        return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
    }

	printf("assigned getter \n");
    system_setting_getter = system_setting_item->get_value_cb;

    if (system_setting_getter == NULL)
    {
        LOGE("[%s] IO_ERROR(0x%08x) : failed to call getter for the system settings", __FUNCTION__, SYSTEM_SETTINGS_ERROR_IO_ERROR);
        return SYSTEM_SETTINGS_ERROR_IO_ERROR;
    }

    return system_setting_getter(key, system_setting_item->data_type, value);
}

int system_settings_set_value(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	system_setting_h system_setting_item;
	system_setting_set_value_cb	system_setting_setter;

    if (system_settings_get_item(key, &system_setting_item))
    {
        LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
        return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
    }

	printf("assigned setter \n");
    system_setting_setter = system_setting_item->set_value_cb;

    if (system_setting_setter == NULL)
    {
        LOGE("[%s] IO_ERROR(0x%08x) : failed to call getter for the system settings", __FUNCTION__, SYSTEM_SETTINGS_ERROR_IO_ERROR);
        return SYSTEM_SETTINGS_ERROR_IO_ERROR;
    }

    return system_setting_setter(key, system_setting_item->data_type, value);
}

// typedef int (*system_setting_set_value_cb) (system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_settings_set_value_int(system_settings_key_e key, int value)
{
	printf("[MOCK] system_settings_set_value_int - value = %d \n", value);

	// TODO: make sure the value is inside of enum.
	int* ptr = &value;
	return system_settings_set_value(key, SYSTEM_SETTING_DATA_TYPE_INT,(void*)ptr);
}

int system_settings_get_value_int(system_settings_key_e key, int *value)
{
	return system_settings_get_value(key, SYSTEM_SETTING_DATA_TYPE_INT, (void**)value);
}

int system_settings_set_value_bool(system_settings_key_e key, bool value)
{
	printf("[MOCK] system_settings_set_value_bool - value = %d \n", value);
	bool* ptr = &value;
	return system_settings_set_value(key, SYSTEM_SETTING_DATA_TYPE_BOOL,(void*)ptr);
}

int system_settings_get_value_bool(system_settings_key_e key, bool *value)
{
	return system_settings_get_value(key, SYSTEM_SETTING_DATA_TYPE_BOOL, (void**)value);
}

int system_settings_set_value_double(system_settings_key_e key, double value)
{
	printf("[MOCK] system_settings_set_value_double - value = %f \n", value);
	double* ptr = &value;
	return system_settings_set_value(key, SYSTEM_SETTING_DATA_TYPE_DOUBLE,(void*)ptr);
}

int system_settings_get_value_double(system_settings_key_e key, double *value)
{
	return system_settings_get_value(key, SYSTEM_SETTING_DATA_TYPE_DOUBLE, (void**)value);
}

int system_settings_set_value_string(system_settings_key_e key, const char *value)
{
	printf("[MOCK] system_settings_set_value_string - input string : %s \n", value);
	return system_settings_set_value(key, SYSTEM_SETTING_DATA_TYPE_STRING,(void*)value);
}

int system_settings_get_value_string(system_settings_key_e key, char **value)
{
	return system_settings_get_value(key, SYSTEM_SETTING_DATA_TYPE_STRING, (void**)value);
}


/*
	- START
		- system_settings_set_changed_cb
			-> int (*system_setting_set_changed_callback_cb)(key, callback, user_data)
*/

/*PUBLIC*/
int system_settings_set_changed_cb(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	printf("system_settings_set_changed_cb \n");

    system_setting_h system_setting_item;
	system_setting_set_changed_callback_cb system_setting_set_changed_cb;

    if (system_settings_get_item(key, &system_setting_item))
    {
        LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
        return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
    }

	system_setting_set_changed_cb = system_setting_item->set_changed_cb;

	// Store the callback function from application side
	if (callback)
		system_setting_item->changed_cb = callback;

    if (system_setting_set_changed_cb == NULL)
    {
        LOGE("[%s] IO_ERROR(0x%08x) : failed to call getter for the system settings", __FUNCTION__, SYSTEM_SETTINGS_ERROR_IO_ERROR);
        return SYSTEM_SETTINGS_ERROR_IO_ERROR;
    }

	return system_setting_set_changed_cb(key, callback, user_data);
}


int system_settings_unset_changed_cb(system_settings_key_e key)
{
	printf("system_settings_unset_changed_cb \n");

    system_setting_h system_setting_item;
	system_setting_unset_changed_callback_cb system_setting_unset_changed_cb;

    if (system_settings_get_item(key, &system_setting_item))
    {
        LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
        return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
    }

	system_setting_unset_changed_cb = system_setting_item->unset_changed_cb;

	// free the callback function from application side
	if (system_setting_item->changed_cb)
		system_setting_item->changed_cb = NULL;
	//-----------------------------------------------------

    if (system_setting_unset_changed_cb == NULL)
    {
        LOGE("[%s] IO_ERROR(0x%08x) : failed to call getter for the system settings", __FUNCTION__, SYSTEM_SETTINGS_ERROR_IO_ERROR);
        return SYSTEM_SETTINGS_ERROR_IO_ERROR;
    }

	return system_setting_unset_changed_cb(key);
}

