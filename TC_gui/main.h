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
#ifndef __APPCORE_MINI_
#define __APPCORE_MINI_

#include <stdio.h>
#include <Elementary.h>
#include <appcore-efl.h>
#include <Ecore_X.h>


#define PACKAGE "com.samsung.appcore-mini"

struct appdata
{
	Evas* evas;
	Evas_Object *win_main;
	Evas_Object *bg;
	Evas_Object *layout_main;
	Evas_Object *navi;


	Evas_Coord root_w;
	Evas_Coord root_h;

	char* pkgname;
};


// appcore & EFL initialization code
static void _quit_cb(void *data, Evas_Object* obj, void* event_info);
static Evas_Object* _create_list_winset(Evas_Object* parent, struct appdata* ad);

/**
 * return a pointer, calling elm_win_add(); -> win_main
 */
static Evas_Object* create_win(const char *name);
static void _window_resize_cb(void *data, Evas * e, Evas_Object * obj, void *event_info);

/**
 * return a pointer, calling elm_bg_add(); -> bg
 */
static Evas_Object* _create_bg(Evas_Object *parent);

/**
 * return a pointer, calling elm_layout_add( win_main ) -> layout_main
 */
static Evas_Object* _create_layout_main(Evas_Object* parent);


#endif /* __APPCORE_MINI_ */
