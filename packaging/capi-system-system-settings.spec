Name:       capi-system-system-settings
Summary:    A System Settings library in Tizen Native API
Version:    0.0.2
Release:    3
Group:      System/System Info
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(ecore)
BuildRequires:  pkgconfig(ecore-x)
BuildRequires:  pkgconfig(ecore-file)
BuildRequires:  pkgconfig(appcore-efl)
BuildRequires:  pkgconfig(capi-appfw-application)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(fontconfig)
BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  pkgconfig(eventsystem)
BuildRequires:  pkgconfig(bundle)

Requires(post): /sbin/ldconfig  
Requires(postun): /sbin/ldconfig

%description
System setting api for get,set configuration

%package devel
Summary:  A System Settings library in Tizen Native API (Development)
Group:    System/System Info
Requires: %{name} = %{version}-%{release}
Requires:  pkgconfig(capi-base-common)

%description devel
System setting api for get,set configuration



%prep
%setup -q

%define tizen_profile_name mobile 

%build

%if "%{?tizen_profile_name}" == "wearable"
export CFLAGS="$CFLAGS -DTIZEN_WEARABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_WEARABLE"
export FFLAGS="$FFLAGS -DTIZEN_WEARABLE"
%else
export CFLAGS="$CFLAGS -DTIZEN_MOBILE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_MOBILE"
export FFLAGS="$FFLAGS -DTIZEN_MOBILE"
%endif

%if 0%{?sec_build_binary_debug_enable}
export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"
%endif

%if 0%{?tizen_build_binary_release_type_eng}
export CFLAGS="$CFLAGS -DTIZEN_ENGINEER_MODE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_ENGINEER_MODE"
export FFLAGS="$FFLAGS -DTIZEN_ENGINEER_MODE"
%endif

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`  
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER} 


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%{_libdir}/lib*.so.*
# /usr/local/bin/test_system_settings
/usr/local/bin/test_system_settings_gui

%files devel
%manifest %{name}.manifest
%{_includedir}/system/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/lib*.so
