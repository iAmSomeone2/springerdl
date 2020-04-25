Name:       springerdl
Version:    0.1
Release:    0.1%{?dist}
Summary:    Downloads a list of free Springer-published books
URL:        https://github.com/iAmSomeone2/springerdl
License:    GPLv3

Source0:    https://github.com/iAmSomeone2/%{name}/archive/%{version}-alpha.tar.gz  # Fix this to point to a release on GitHub

ExclusiveArch:  x86_64,aarch64
BuildRequires:  libcurl-devel, cmake, ninja, gcc
Requires:       libcurl

%description
Springer DL is a CLI program used for downloading free, Springer-published
books.

%prep
%autosetup

%build
cd %{_builddir}
cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
ninja

%install
cd %{_builddir}
ninja install

%files
%{buildroot}/usr/local/bin/springerdl

%changelog
* Sat Apr 25 2020 Brenden Davidson <davidson.brenden15@gmail.com> 0.1-1fc32-initial alpha release