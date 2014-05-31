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
#include <unistd.h>
#include <errno.h>

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <regex.h>

#include <dlog.h>
#include <vconf.h>

#include <glib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include <fontconfig/fontconfig.h>

#include <pkgmgr-info.h>
#include <ail.h>

#include <Ecore_X.h>
#include <Elementary.h>
#include <Evas.h>
#include <Ecore_Evas.h>

#include <system_settings.h>
#include <system_settings_private.h>

#define SMALL_FONT_DPI                      (-80)
#define MIDDLE_FONT_DPI                     (-100)
#define LARGE_FONT_DPI                      (-120)
#define HUGE_FONT_DPI                       (-190)
#define GIANT_FONT_DPI                      (-250)

#define SETTING_FONT_PRELOAD_FONT_PATH "/usr/share/fonts"
#define SETTING_FONT_DOWNLOADED_FONT_PATH "/opt/share/fonts"

#define SETTING_FONT_CONF_FILE "/opt/etc/fonts/conf.avail/99-slp.conf"
#define SETTING_DEFAULT_FONT_CONF_FILE "/usr/opt/etc/fonts/conf.avail/99-slp.conf"

#define SETTING_STR_SLP_LEN  256

static char* _get_cur_font();
static void __font_size_set();
static int __font_size_get();
static char* _get_default_font();

static bool font_config_set(char *font_name);
static void font_config_set_notification();

/**
 * VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR has a path of the ringtone file which user choose
 * @return the ringtone file path specified by user in normal case
 *         if it's not accessable, return the default ringtone path
 */
int system_setting_get_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* vconf_value;
	if (system_setting_vconf_get_value_string(VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	// check to see if it's accessable -> OK
	// no --> default ringtone path VCONFKEY_SETAPPL_CALL_RINGTONE_DEFAULT_PATH_STR
	int is_load = _is_file_accessible(vconf_value);
	if (is_load == 0) {
		*value = vconf_value;
	} else { // not zero on errro
		*value = vconf_get_str(VCONFKEY_SETAPPL_CALL_RINGTONE_DEFAULT_PATH_STR);
	}

	//*value = vconf_value;
	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_get_email_alert_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* vconf_value;
	if (system_setting_vconf_get_value_string(VCONFKEY_SETAPPL_NOTI_MSG_RINGTONE_PATH_STR, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	// check to see if it's accessable -> OK
	// no --> default ringtone path VCONFKEY_SETAPPL_NOTI_RINGTONE_DEFAULT_PATH_STR
	int is_load = _is_file_accessible(vconf_value);
	if (is_load == 0) {
		*value = vconf_value;
	} else { // not zero on errro
		*value = vconf_get_str(VCONFKEY_SETAPPL_NOTI_RINGTONE_DEFAULT_PATH_STR);
	}

	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_get_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* vconf_value;
	if (system_setting_vconf_get_value_string(VCONFKEY_BGSET, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = vconf_value;
	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_get_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* vconf_value;

	if (system_setting_vconf_get_value_string(VCONFKEY_IDLE_LOCK_BGSET, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = vconf_value;

	return SYSTEM_SETTINGS_ERROR_NONE;
}


// [int] vconf GET
int system_setting_get_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	int vconf_value;

	if (system_setting_vconf_get_value_int(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = (void*)vconf_value;

	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_get_default_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* font_name = _get_default_font();
	if (font_name)
	{
		*value = (void*)font_name;
		return SYSTEM_SETTINGS_ERROR_NONE;
	} else {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
}

// [int] vconf GET
int system_setting_get_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* font_name = _get_cur_font();
	*value = (void*)font_name;

	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_get_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	bool vconf_value;

	if (system_setting_vconf_get_value_bool(VCONFKEY_SETAPPL_MOTION_ACTIVATION, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = (void*)vconf_value;

	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_get_usb_debugging_option(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	bool vconf_value;

	if (system_setting_vconf_get_value_bool(VCONFKEY_SETAPPL_USB_DEBUG_MODE_BOOL, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = (void*)vconf_value;

	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_get_3g_data_network(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	bool vconf_value;

	if (system_setting_vconf_get_value_bool(VCONFKEY_3G_ENABLE, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = (void*)vconf_value;

	return SYSTEM_SETTINGS_ERROR_NONE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

#if SUPPORT_ACCESSIBILITY
int system_setting_get_tap_and_hold_delay(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* vconf_value = NULL;
	if (system_setting_vconf_get_value_string(VCONFKEY_SETAPPL_ACCESSIBILITY_TAP_HOLD_DELAY_STR, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	int val = SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_MEDIUM;
	if (vconf_value && strcmp(vconf_value, "IDS_COM_POP_SHORT") == 0)
	{
		val = SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_SHORT;
	} else if (vconf_value && strcmp(vconf_value, "IDS_ST_BODY_MEDIUM") == 0)
	{
		val = SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_MEDIUM;
	} else if (vconf_value && strcmp(vconf_value, "IDS_COM_POP_LONG") == 0)
	{
		val = SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_LONG;
	}

	*value = (void*)val;		// float
	return SYSTEM_SETTINGS_ERROR_NONE;
}
#endif
/**
 * get current lock scren app package name (string)
 *
 * @return SYSTEM_SETTINGS_ERROR_LOCKSCREEN_APP_PASSWORD_MODE raise exception if current lock type is 'password'
 */
int system_setting_get_lockscreen_app(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* pkg_name = NULL;
	int locktype = -1;
	system_setting_vconf_get_value_int(VCONFKEY_SETAPPL_SCREEN_LOCK_TYPE_INT, &locktype);

	if (system_setting_vconf_get_value_string(VCONFKEY_SETAPPL_3RD_LOCK_PKG_NAME_STR, &pkg_name)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	if (pkg_name && strcmp(pkg_name, "com.samsung.lockscreen") == 0 && locktype == SETTING_SCREEN_LOCK_TYPE_PASSWORD)
	{
		return SYSTEM_SETTINGS_ERROR_LOCKSCREEN_APP_PASSWORD_MODE;
	}

	*value = pkg_name;
	return SYSTEM_SETTINGS_ERROR_NONE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

int _is_file_accessible(const char * path)
{
    int ret = access(path ,R_OK);
    if (ret == 0)
	{
		SETTING_TRACE("found the file  %s", path);
        return 0;
	}
    else
	{
		SETTING_TRACE("found the file  %s --- error code : %d ", path, errno);
        return errno;
	}
}

int system_setting_set_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	char* vconf_value;
	vconf_value = (char*)value;

	int is_load = _is_file_accessible(vconf_value);
	if (is_load == 0)
	{
		if (system_setting_vconf_set_value_string(VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR, vconf_value)) {
			return SYSTEM_SETTINGS_ERROR_IO_ERROR;
		}
	} else {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_set_email_alert_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	char* vconf_value;
	vconf_value = (char*)value;

	int is_load = _is_file_accessible(vconf_value);
	if (is_load == 0)
	{
		if (system_setting_vconf_set_value_string(VCONFKEY_SETAPPL_NOTI_MSG_RINGTONE_PATH_STR, vconf_value)) {
			return SYSTEM_SETTINGS_ERROR_IO_ERROR;
		}
	} else {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return SYSTEM_SETTINGS_ERROR_NONE;
}


bool __is_supported_image_type_load(char* path)
{
	evas_init();
	Ecore_Evas  *ee;
	Evas        *evas;

	ee = ecore_evas_new(NULL, 0, 0, 100, 100, NULL);
	evas = ecore_evas_get(ee);

	Evas_Object* img = evas_object_image_add(evas);
	evas_object_image_file_set(img, path, NULL);
	Evas_Load_Error ret = evas_object_image_load_error_get(img);

	bool result = false;
	if (ret == EVAS_LOAD_ERROR_NONE)
	{
		SETTING_TRACE("%s - OK", path);
		result = true;
	} else
	{
		SETTING_TRACE("%s - NO", path);
		result = false;
	}
	ecore_evas_free(ee);
	evas_shutdown();
	return result;
}

bool __is_supported_image_type(char* path)
{
	bool ret = false;

	evas_init();
	if (evas_object_image_extension_can_load_get(path))
		ret = true;
	else
		ret = false;

	evas_shutdown();

	return ret;
}

#define PATH_EXT_CHECK_REG ".(jpe?g|jpg|png|gif)$"
bool __is_supported_image_type_by_ext(char* file_path)
{
    regex_t fsm;
    regmatch_t str[2048+1];

	if (!file_path) return false;

    int ret = false;
    if( ret = regcomp( &fsm, PATH_EXT_CHECK_REG, REG_ICASE | REG_EXTENDED) )
    {
        SETTING_TRACE("regular expresstion fail");
        return 1;
    }

	/* code */
	if( regexec( &fsm, file_path, strlen(file_path) + 1, str, 0 ) == REG_NOMATCH )
	{
		//SETTING_TRACE("FAILED - %s", file_path[i]);
		ret = 0;
	} else {
		//SETTING_TRACE("MATCHED - %s", file_path[i]);
		ret = 1;
	}
    return ret;
}

int system_setting_set_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	char* vconf_value;
	vconf_value = (char*)value;

	bool isok  = __is_supported_image_type_load(vconf_value);
	if (!isok)
	{
		// not supported
		SETTING_TRACE("path : %s is not supported file format", vconf_value);
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	} else
	{
		SETTING_TRACE("path : %s is SUPPORT file format", vconf_value);
	}

	// error handling here
	if (_is_file_accessible(vconf_value) != 0)
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;

	if (system_setting_vconf_set_value_string(VCONFKEY_BGSET, vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	char* vconf_value;
	vconf_value = (char*)value;

	bool isok  = __is_supported_image_type_load(vconf_value);
	if (!isok)
	{
		// not supported
		SETTING_TRACE("path : %s is not supported file format", vconf_value);
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	} else
	{
		SETTING_TRACE("path : %s is SUPPORT file format", vconf_value);
	}

	// error handling here
	if (_is_file_accessible(vconf_value) != 0)
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;

	if (system_setting_vconf_set_value_string(VCONFKEY_IDLE_LOCK_BGSET, vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	SETTING_TRACE_BEGIN;
	int* vconf_value;
	vconf_value = (int*)value;

	if (*vconf_value < 0 || *vconf_value > SYSTEM_SETTINGS_FONT_SIZE_GIANT) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	if (system_setting_vconf_set_value_int(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, *vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	__font_size_set();
	SETTING_TRACE_END;
	return SYSTEM_SETTINGS_ERROR_NONE;
}
/**
 * [internal API]
 */
void *font_conf_doc_parse(char *doc_name, char *font_name)
{
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    xmlNodePtr cur2 = NULL;
    xmlNodePtr cur3 = NULL;
    xmlChar *key = NULL;

    doc = xmlParseFile(doc_name);

    cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }

    if(xmlStrcmp(cur->name, (const xmlChar *)"fontconfig")) {
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }

    cur = cur->xmlChildrenNode;

    Eina_Bool is_changed = EINA_FALSE;
    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar *)"match")))
        {
            cur2 = cur->xmlChildrenNode;
            while(cur2 != NULL)
            {
                if((!xmlStrcmp(cur2->name, (const xmlChar *)"edit")))
                {
                    xmlChar *name = xmlGetProp(cur2, (const xmlChar *)"name");
                    /* if name is not 'family', break */
                    if (xmlStrcmp(name, (const xmlChar *)"family"))
                    {
                        xmlFree(name);
                        name = NULL;
                        break;
                    }
                    xmlFree(name);
                    name = NULL;

                    cur3 = cur2->xmlChildrenNode;
                   while(cur3 != NULL)
                    {
                        if((!xmlStrcmp(cur3->name, (const xmlChar *)"string")))
                        {
                            xmlNodeSetContent(cur3->xmlChildrenNode, (const xmlChar *)font_name);
                            key = xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);
                            xmlFree(key);
                            key = NULL;
                            is_changed = EINA_TRUE;
                        }
                        cur3 = cur3->next;
                    }
                }
                cur2 = cur2->next;
            }
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *)"alias")))
        {
            cur2 = cur->xmlChildrenNode;
            while (cur2 != NULL)
            {
                if ((!xmlStrcmp(cur2->name, (const xmlChar *)"family")))
                {
                    xmlNodeSetContent(cur2->xmlChildrenNode, (const xmlChar *)font_name);
                    key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
                    xmlFree(key);
                    key = NULL;
                    is_changed = EINA_TRUE;
                } else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"prefer")))
                {
                    cur3 = cur2->xmlChildrenNode;
                    while (cur3 != NULL)
                    {
                        if((!xmlStrcmp(cur3->name, (const xmlChar *)"family")))
                        {
                            xmlNodeSetContent(cur3->xmlChildrenNode, (const xmlChar *)font_name);
                            key = xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);
                            xmlFree(key);
                            key = NULL;
                            is_changed = EINA_TRUE;
                            cur3 = cur3->next;
			    return doc;
                        }
                        cur3 = cur3->next;
                    }
                }
                cur2 = cur2->next;
            }
        }
        cur = cur->next;
    }

    if (is_changed) {
        return doc;
    } else {
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }
}

int system_setting_set_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	char* font_name = NULL;
	font_name = (char*)value;

	/* get current font list */
	int is_found = __is_available_font(font_name);

	if (is_found)
	{
		SETTING_TRACE("found font : %s ", font_name);
	} else {
		SETTING_TRACE(" NOT found font : %s ", font_name);
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	bool bsave = font_config_set(font_name);

	if (! bsave)
	{
		SETTING_TRACE(" font type save error by font_config_set() ");
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	} else {
		SETTING_TRACE(" save OK - font_config_set() ");
	}

    xmlDocPtr doc = (xmlDocPtr)font_conf_doc_parse(SETTING_FONT_CONF_FILE, font_name);
    if(doc != NULL) {
        xmlSaveFormatFile(SETTING_FONT_CONF_FILE, doc, 0);
        xmlFreeDoc(doc);
        doc = NULL;
    }

	font_config_set_notification();

	char* vconf_value;
	vconf_value = (char*)value;
	if (system_setting_vconf_set_value_string(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_NAME, vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	bool* vconf_value;
	vconf_value = (bool*)value;
	if (system_setting_vconf_set_value_bool(VCONFKEY_SETAPPL_MOTION_ACTIVATION, *vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_usb_debugging_option(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	bool* vconf_value;
	vconf_value = (bool*)value;
	if (system_setting_vconf_set_value_bool(VCONFKEY_SETAPPL_USB_DEBUG_MODE_BOOL, *vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	return SYSTEM_SETTINGS_ERROR_NONE;

}

int system_setting_set_3g_data_network(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	bool* vconf_value;
	vconf_value = (bool*)value;
	if (system_setting_vconf_set_value_bool(VCONFKEY_3G_ENABLE, *vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	return SYSTEM_SETTINGS_ERROR_NONE;
}

#if SUPPORT_ACCESSIBILITY
/*
	"IDS_COM_POP_SHORT"		0.5
	"IDS_ST_BODY_MEDIUM"	1.0
	"IDS_COM_POP_LONG"		1.5
*/
int system_setting_set_tap_and_hold_delay(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	int* vconf_value;
	vconf_value = (int*)value;

	char* result = "IDS_ST_BODY_MEDIUM";		// default as 'medium'
	if (*vconf_value == SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_SHORT)
	{
		result = "IDS_COM_POP_SHORT";
	}
	else if (*vconf_value == SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_MEDIUM)
	{
		result = "IDS_ST_BODY_MEDIUM";
	}
	else if (*vconf_value == SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_LONG)
	{
		result = "IDS_COM_POP_LONG";
	} else {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	if (system_setting_vconf_set_value_string(VCONFKEY_SETAPPL_ACCESSIBILITY_TAP_HOLD_DELAY_STR, result)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	return SYSTEM_SETTINGS_ERROR_NONE;
}
#endif

static int category_func(const char *name, void *user_data)
{
	SETTING_TRACE_BEGIN;
	static char* category = "lock-screen";
	if ( name && !strcmp(name, category) )
	{
		SETTING_TRACE(" SAME ");
		return -1;
	}
	else
	{
		SETTING_TRACE(" DIFFERENT -- %s, category -- %s ", name, category);
		return 0;
	}

	return 0;
}

/**
 *
 * set 'swipe type' if current lockscreen app is 'com.samsung.lockscreen'
 *
 */
int system_setting_set_lockscreen_app(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	char* vconf_value;
	vconf_value = (char*)value;		// ex) com.samsung.lockscreen

	int r = 0;
	pkgmgrinfo_appinfo_h handle;
	char *apptype = NULL;
	r = pkgmgrinfo_appinfo_get_appinfo(vconf_value, &handle);
	if (r != PMINFO_R_OK) {
		SETTING_TRACE("*** pkginfo failed ");
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	} else {
		SETTING_TRACE("%x", handle);
	}

	int ret = pkgmgrinfo_appinfo_foreach_category(handle, category_func, (void*)"lock-screen");
	if (ret != PMINFO_R_OK) {
		pkgmgrinfo_appinfo_destroy_appinfo(handle);
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	pkgmgrinfo_appinfo_destroy_appinfo(handle);
	//-----------------------------------------------------------------------------------
	int locktype = -1;
	if (system_setting_vconf_get_value_int(VCONFKEY_SETAPPL_SCREEN_LOCK_TYPE_INT, &locktype)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	if (locktype == SETTING_SCREEN_LOCK_TYPE_PASSWORD)
		return SYSTEM_SETTINGS_ERROR_LOCKSCREEN_APP_PASSWORD_MODE;

	if (system_setting_vconf_set_value_string(VCONFKEY_SETAPPL_3RD_LOCK_PKG_NAME_STR, vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	if (vconf_value && strcmp(vconf_value, "com.samsung.lockscreen") == 0)
	{
		if (system_setting_vconf_set_value_int(VCONFKEY_SETAPPL_SCREEN_LOCK_TYPE_INT, SETTING_SCREEN_LOCK_TYPE_SWIPE)) {
			return SYSTEM_SETTINGS_ERROR_IO_ERROR;
		}
	}
	return SYSTEM_SETTINGS_ERROR_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//

int system_setting_set_changed_callback_incoming_call_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR, SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, 0, user_data);
}

int system_setting_unset_changed_callback_incoming_call_ringtone(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR, 0);
}

int system_setting_set_changed_callback_email_alert_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_NOTI_MSG_RINGTONE_PATH_STR, SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, 0, user_data);
}

int system_setting_unset_changed_callback_email_alert_ringtone(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_NOTI_MSG_RINGTONE_PATH_STR, 0);
}

int system_setting_set_changed_callback_wallpaper_home_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_BGSET, SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, 0, user_data);
}

int system_setting_unset_changed_callback_wallpaper_home_screen(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_BGSET, 0);
}

int system_setting_set_changed_callback_wallpaper_lock_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_IDLE_LOCK_BGSET,SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, 0, user_data);
}

int system_setting_unset_changed_callback_wallpaper_lock_screen(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_IDLE_LOCK_BGSET, 0);
}

int system_setting_set_changed_callback_font_size(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE,SYSTEM_SETTINGS_KEY_FONT_SIZE, 1, user_data);
}

int system_setting_unset_changed_callback_font_size(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, 1);
}

int system_setting_set_changed_callback_usb_debugging_option(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_USB_DEBUG_MODE_BOOL,SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED, 1, user_data);
}

int system_setting_unset_changed_callback_usb_debugging_option(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_USB_DEBUG_MODE_BOOL, 1);
}

int system_setting_set_changed_callback_3g_data_network(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_3G_ENABLE,SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED, 1,user_data);
}

int system_setting_unset_changed_callback_3g_data_network(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_3G_ENABLE, 1);
}
#if SUPPORT_ACCESSIBILITY
int system_setting_set_changed_callback_tap_and_hold_delay(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_TAP_HOLD_DELAY_STR, SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, 1,user_data);
}

int system_setting_unset_changed_callback_tap_and_hold_delay(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_TAP_HOLD_DELAY_STR, 1);
}
#endif
int system_setting_set_changed_callback_lockscreen_app(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_3RD_LOCK_PKG_NAME_STR, SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP, 1,user_data);
}

int system_setting_unset_changed_callback_lockscreen_app(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_3RD_LOCK_PKG_NAME_STR, 1);
}


/**
 * @todo need to add custom event notification method
 */
int system_setting_set_changed_callback_font_type(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_NAME,SYSTEM_SETTINGS_KEY_FONT_TYPE, 2, user_data);
}

int system_setting_unset_changed_callback_font_type(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_NAME,2);
}

// TODO : 2th argument, callback, is not in use.
int system_setting_set_changed_callback_motion_activation(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_MOTION_ACTIVATION, SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, 3, user_data );
}

int system_setting_unset_changed_callback_motion_activation(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_MOTION_ACTIVATION, 3);
}

static char* _get_cur_font()
{
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    xmlNodePtr cur2 = NULL;
    xmlNodePtr cur3 = NULL;
    xmlChar *key = NULL;

    char *font_name = NULL;

    doc = xmlParseFile(SETTING_FONT_CONF_FILE);

    cur = xmlDocGetRootElement(doc);

    if(cur == NULL) {
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }

    if(xmlStrcmp(cur->name, (const xmlChar *)"fontconfig")) {
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }

    cur = cur->xmlChildrenNode;

    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar *)"match")))
        {
            cur2 = cur->xmlChildrenNode;
            while(cur2 != NULL)
            {
                if((!xmlStrcmp(cur2->name, (const xmlChar *)"edit")))
                {
                    cur3 = cur2->xmlChildrenNode;
                    while(cur3 != NULL)
                    {
                        if((!xmlStrcmp(cur3->name, (const xmlChar *)"string")))
                        {
                            key = xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);

                            font_name = g_strdup((char *)key);
                            xmlFree(key);
                            key = NULL;
                            xmlFreeDoc(doc);
                            doc = NULL;
                            return font_name;
                        }
                       cur3 = cur3->next;
                    }
                }
                cur2 = cur2->next;
            }
        }
        cur = cur->next;
    }

    xmlFreeDoc(doc);
    doc = NULL;
    return NULL;
}

static void font_config_set_notification()
{
    /* notification */
	Ecore_X_Window ecore_win = ecore_x_window_root_first_get();
	Ecore_X_Atom atom = ecore_x_atom_get("FONT_TYPE_change");
	ecore_x_window_prop_string_set(ecore_win, atom, "tizen");
}

int __is_available_font(char* font_name)
{
	SETTING_TRACE_BEGIN;
	FcObjectSet *os = NULL;
	FcFontSet *fs = NULL;
	FcPattern *pat = NULL;
	Eina_List *list = NULL;
	FcConfig *font_config = NULL;

	int ret = 0;

	if(font_name == NULL)
		return -1;

	font_config = FcInitLoadConfigAndFonts();

	//setting_retvm_if(font_config == NULL, NULL, "Failed: FcInitLoadConfigAndFonts");

	pat = FcPatternCreate();

	os = FcObjectSetBuild(FC_FAMILY, FC_FILE, (char *) 0);

	if (os) {
		fs = FcFontList(font_config, pat, os);
		FcObjectSetDestroy(os);
		os = NULL;
	}

	if (pat) {
		FcPatternDestroy(pat);
		pat = NULL;
	}

	if (fs)	{
		int j;
		SETTING_TRACE("fs->nfont = %d", fs->nfont);

		for (j = 0; j < fs->nfont; j++)	{
			FcChar8 *family = NULL;
			FcChar8 *file = NULL;

			if (FcPatternGetString(fs->fonts[j], FC_FILE, 0, &file) == FcResultMatch) {
				int preload_path_len = strlen(SETTING_FONT_PRELOAD_FONT_PATH);
				int download_path_len = strlen(SETTING_FONT_DOWNLOADED_FONT_PATH);

				if ( file && (!strncmp((const char*)file, SETTING_FONT_PRELOAD_FONT_PATH, preload_path_len)
							|| !strncmp((const char*)file, SETTING_FONT_DOWNLOADED_FONT_PATH, download_path_len))) {
					if (FcPatternGetString(fs->fonts[j], FC_FAMILY, 0, &family) != FcResultMatch) {
						SETTING_TRACE("Family name is invalid");
						continue;
					}

					if (family)
					{
						SETTING_TRACE("-------- FONT - family = %s", (char *)family);
						if (strcmp(family, font_name) == 0)
						{
							ret = 1;
							break;
						}
					}
				}
			}
		}
		FcFontSetDestroy(fs);
		fs = NULL;
	}
	FcConfigDestroy(font_config);
	font_config = NULL;
	return ret;
}


static char* _get_default_font()
{
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    xmlNodePtr cur2 = NULL;
    xmlNodePtr cur3 = NULL;
    xmlChar *key = NULL;
	struct _xmlAttr *properties = NULL;
    char *default_font_name = NULL;

    doc = xmlParseFile(SETTING_DEFAULT_FONT_CONF_FILE);

    cur = xmlDocGetRootElement(doc);

    if(cur == NULL) {
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }

    if(xmlStrcmp(cur->name, (const xmlChar *)"fontconfig")) {
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }

    cur = cur->xmlChildrenNode;

    while(cur != NULL){
		if((!xmlStrcmp(cur->name, (const xmlChar *)"match"))){
			cur2 = cur->xmlChildrenNode;
			while(cur2 != NULL){
				if((!xmlStrcmp(cur2->name, (const xmlChar *)"edit"))){
					properties = cur2->properties;
					/*find the "name" property*/
					while(NULL != properties){
						if(!xmlStrcmp(properties->name, (const xmlChar *)"name")){
							break;
						}
						properties = properties->next;
					}

					/*If the value of "name" property is "family", then get the child node string,
					it shall be the default font type*/
					if(NULL != properties &&!xmlStrcmp(properties->children->content, (const xmlChar *)"family")){
						cur3 = cur2->xmlChildrenNode;
						while(cur3 != NULL){
							if((!xmlStrcmp(cur3->name, (const xmlChar *)"string"))){
								key = xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);
								default_font_name = g_strdup((char *)key);
								xmlFree(key);
								key = NULL;
								xmlFreeDoc(doc);
								doc = NULL;
								return default_font_name;
							}
							cur3 = cur3->next;
						}
					}
				}
                cur2 = cur2->next;
            }
        }
        cur = cur->next;
    }

    xmlFreeDoc(doc);
    doc = NULL;
    return NULL;
}

static bool font_config_set(char *font_name)
{
    Eina_List *text_classes = NULL;
    Elm_Text_Class *etc = NULL;
    const Eina_List *l = NULL;
    Eina_List *fo_list = NULL;
    Elm_Font_Overlay *efo = NULL;

    int font_size = __font_size_get();
    int size = 0;

    text_classes = elm_config_text_classes_list_get();

    fo_list = (Eina_List *)elm_config_font_overlay_list_get();

    Eina_List *ll = NULL;
    Eina_List *l_next = NULL;

    Eina_Bool slp_medium_exist = EINA_FALSE;
    Eina_Bool slp_roman_exist = EINA_FALSE;
    Eina_Bool slp_bold_exist = EINA_FALSE;
    Eina_Bool slp_regular_exist = EINA_FALSE;

    // Tizen
    Eina_Bool tizen_exist = EINA_FALSE;

    EINA_LIST_FOREACH_SAFE(fo_list, ll, l_next, efo)
    {
        if (!strcmp(efo->text_class, "tizen_medium")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            slp_medium_exist = EINA_TRUE;
        } else if (!strcmp(efo->text_class, "tizen_roman")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            slp_roman_exist = EINA_TRUE;
        } else if (!strcmp(efo->text_class, "tizen_bold")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            slp_bold_exist = EINA_TRUE;
        } else if (!strcmp(efo->text_class, "tizen_regular")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            slp_regular_exist = EINA_TRUE;
        }

        // Tizen
        if (!strcmp(efo->text_class, "tizen")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            tizen_exist = EINA_TRUE;
        }

    }

    /* if slp_XX do not exist, need to set them, font size is -100(100%) */
    if (slp_medium_exist == EINA_FALSE) {
        elm_config_font_overlay_set("tizen_medium", (const char*)font_name,  MIDDLE_FONT_DPI);
    }
    if (slp_roman_exist == EINA_FALSE) {
        elm_config_font_overlay_set("tizen_roman", (const char*)font_name,  MIDDLE_FONT_DPI);
    }
    if (slp_bold_exist == EINA_FALSE) {
        elm_config_font_overlay_set("tizen_bold", (const char*)font_name,  MIDDLE_FONT_DPI);
    }
    if (slp_regular_exist == EINA_FALSE) {
        elm_config_font_overlay_set("tizen_regular", (const char*)font_name,  MIDDLE_FONT_DPI);
    }

    // Tizen
    if (tizen_exist == EINA_FALSE) {
        elm_config_font_overlay_set("tizen", (const char*)font_name,  MIDDLE_FONT_DPI);
    }

    elm_config_font_overlay_set("tizen", (const char*)font_name,  MIDDLE_FONT_DPI);

    // Tizen
    elm_config_font_overlay_set("tizen", (const char*)font_name,  MIDDLE_FONT_DPI);

    EINA_LIST_FOREACH(text_classes, l, etc)
    {
        ll = NULL;

        size = font_size;
        EINA_LIST_FOREACH(fo_list, ll, efo)
        {
            if (!strcmp(etc->name, efo->text_class)) {
                size = efo->size;
            }
        }
        elm_config_font_overlay_set(etc->name, (const char*)font_name, size);
    }

    //elm_config_font_overlay_apply();
    elm_config_all_flush();

	EAPI Eina_Bool save_ok = EINA_FALSE;
    save_ok = elm_config_save();
    elm_config_text_classes_list_free(text_classes);
    text_classes = NULL;
	bool ok = (save_ok) ? true : false;
	return save_ok;
}

static void __font_size_set()
{
    Eina_List *text_classes = NULL;
    Elm_Text_Class *etc = NULL;
    const Eina_List *l = NULL;
    int font_size = __font_size_get();
    char *font_name = _get_cur_font();

    if (font_size == -1) {
        return;
    }

    text_classes = elm_config_text_classes_list_get();

    EINA_LIST_FOREACH(text_classes, l, etc)
    {
        elm_config_font_overlay_set(etc->name, font_name, font_size);
    }

	elm_config_font_overlay_apply();
    elm_config_all_flush();
    elm_config_save();
    elm_config_text_classes_list_free(text_classes);
    text_classes = NULL;
    g_free(font_name);
}

static int __font_size_get()
{
    int font_size = -1;
    int err = -1;

	int vconf_value = -1;
	if (system_setting_vconf_get_value_int(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, &vconf_value)) {
		return -1;
	}

    switch(vconf_value) {
    case SYSTEM_SETTINGS_FONT_SIZE_SMALL:
        font_size = SMALL_FONT_DPI;
        break;
    case SYSTEM_SETTINGS_FONT_SIZE_NORMAL:
        font_size = MIDDLE_FONT_DPI;
        break;
    case SYSTEM_SETTINGS_FONT_SIZE_LARGE:
        font_size = LARGE_FONT_DPI;
        break;
    case SYSTEM_SETTINGS_FONT_SIZE_HUGE:
        font_size = HUGE_FONT_DPI;
        break;
    case SYSTEM_SETTINGS_FONT_SIZE_GIANT:
        font_size = GIANT_FONT_DPI;
        break;
    default:
        font_size = MIDDLE_FONT_DPI;
        break;
    }
    return font_size;
}
