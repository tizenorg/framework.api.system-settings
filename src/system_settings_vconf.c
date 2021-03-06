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

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_SYSTEM_SETTINGS"


int system_setting_vconf_get_value_int(const char *vconf_key, int *value)
{
	return vconf_get_int(vconf_key, value);
}

int system_setting_vconf_get_value_bool(const char *vconf_key, bool *value)
{
	return vconf_get_bool(vconf_key, (int*)value);
}

int system_setting_vconf_get_value_double(const char *vconf_key, double *value)
{
	return vconf_get_dbl(vconf_key, value);
}

int system_setting_vconf_get_value_string(const char *vconf_key, char **value)
{
    char *str_value = NULL;

    str_value = vconf_get_str(vconf_key);
        
    if (str_value != NULL)
    {
        *value = str_value;
        return 0;
    }
    else
    {
        return -1;
    }
}

int system_setting_vconf_set_value_int(const char *vconf_key, int value)
{
	return vconf_set_int(vconf_key, value);
}

int system_setting_vconf_set_value_bool(const char *vconf_key, bool value)
{
	return vconf_set_bool(vconf_key, (int)value);
}

int system_setting_vconf_set_value_double(const char *vconf_key, double value)
{
	return vconf_set_dbl(vconf_key, value);
}

int system_setting_vconf_set_value_string(const char *vconf_key, char *value)
{
    return vconf_set_str(vconf_key, value);
}


/////////////////////////////////////////////////////////////////////////////////////////////

typedef void (*system_setting_vconf_event_cb)(keynode_t *node, void *event_data);
    
static void system_setting_vconf_event_cb0(keynode_t *node, void *event_data)
{       
	system_settings_key_e pkey = (system_settings_key_e)event_data;
	printf("*** system_setting_vconf_event_cb0  : %d \n",pkey );

    if (node != NULL)
    {
		system_setting_h system_setting_item;
																														  
		if (system_settings_get_item(pkey, &system_setting_item))
		{
			LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		}
		system_setting_item->changed_cb(pkey, NULL);
    }       
}
    
static void system_setting_vconf_event_cb1(keynode_t *node, void *event_data)
{       
	system_settings_key_e pkey = (system_settings_key_e)event_data;
	printf("*** system_setting_vconf_event_cb1  : %d \n",pkey );

    if (node != NULL)
    {
		system_setting_h system_setting_item;
																														  
		if (system_settings_get_item(pkey, &system_setting_item))
		{
			LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		}
		system_setting_item->changed_cb(pkey, NULL);
    }       
}
    
static void system_setting_vconf_event_cb2(keynode_t *node, void *event_data)
{       
	system_settings_key_e pkey = (system_settings_key_e)event_data;
	printf("*** system_setting_vconf_event_cb2  : %d \n",pkey );

    if (node != NULL)
    {
		system_setting_h system_setting_item;
																														  
		if (system_settings_get_item(pkey, &system_setting_item))
		{
			LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		}
		system_setting_item->changed_cb(pkey, NULL);
    }       
}

static void system_setting_vconf_event_cb3(keynode_t *node, void *event_data)
{
	system_settings_key_e pkey = (system_settings_key_e)event_data;
	printf("*** system_setting_vconf_event_cb3  : %d \n",pkey );

    if (node != NULL)
    {
		system_setting_h system_setting_item;
																														  
		if (system_settings_get_item(pkey, &system_setting_item))
		{
			LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		}
		system_setting_item->changed_cb(pkey, NULL);
    }       
}

static void system_setting_vconf_event_cb4(keynode_t *node, void *event_data)
{
	system_settings_key_e pkey = (system_settings_key_e)event_data;
	printf("*** system_setting_vconf_event_cb4  : %d \n",pkey );

    if (node != NULL)
    {
		system_setting_h system_setting_item;
																														  
		if (system_settings_get_item(pkey, &system_setting_item))
		{
			LOGE("[%s] INVALID_PARAMETER(0x%08x) : invalid key", __FUNCTION__, SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER);
		}
		system_setting_item->changed_cb(pkey, NULL);
    }       
}


static system_setting_vconf_event_cb system_setting_vconf_get_event_cb_slot(int slot)
{
    switch (slot)
    {
    case 0:
        return system_setting_vconf_event_cb0;

    case 1:
        return system_setting_vconf_event_cb1;

    case 2:
        return system_setting_vconf_event_cb2;

    case 3:
        return system_setting_vconf_event_cb3;

    case 4:
        return system_setting_vconf_event_cb4;

    default:
        return NULL;
    }
}

int system_setting_vconf_set_changed_cb(const char *vconf_key, system_settings_key_e key, int slot)
{
    system_setting_vconf_event_cb vconf_event_cb;

    vconf_event_cb = system_setting_vconf_get_event_cb_slot(slot);

    if (vconf_event_cb == NULL)
    {
        return SYSTEM_SETTINGS_ERROR_IO_ERROR;
    }

    if (vconf_notify_key_changed(vconf_key, vconf_event_cb, (void*)key))
    {
        return SYSTEM_SETTINGS_ERROR_IO_ERROR;
    }

    return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_vconf_unset_changed_cb(const char *vconf_key, int slot)
{
    system_setting_vconf_event_cb vconf_event_cb;

    vconf_event_cb = system_setting_vconf_get_event_cb_slot(slot);

    if (vconf_event_cb != NULL)
    {
        vconf_ignore_key_changed(vconf_key, vconf_event_cb);
    }

    return SYSTEM_SETTINGS_ERROR_NONE;
}


