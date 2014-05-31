Name:       capi-system-system-settings
Summary:    A System Settings library in Tizen Native API
Version:    0.0.2
Release:    3
VCS:        framework/api/system-settings#submit/master/20130123.062629-31-g2aad2056688f241103f7e9400587a89c9e24cf05
Group:      TO_BE/FILLED_IN
License:    TO BE FILLED IN
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
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(fontconfig)
BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  pkgconfig(pkgmgr)
BuildRequires:  pkgconfig(pkgmgr-info)

Requires(post): /sbin/ldconfig  
Requires(postun): /sbin/ldconfig

%description


%package devel
Summary:  A System Settings library in Tizen Native API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}
Requires:  pkgconfig(capi-base-common)

%description devel



%prep
%setup -q


%build
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
