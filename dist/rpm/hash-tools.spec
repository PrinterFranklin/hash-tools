Name:          hash-tools
Version:       1.0
Release:       2
Summary:       A hash calculate tool based on OpenSSL
License:       BSD
URL:           https://github.com/euleros/hash-tools
Source0:       https://github.com/euleros/hash-tools/releases/download/%{version}/%{name}-%{version}.tar.bz2

BuildRequires: gcc make openssl-devel

%description
The hash-tools can be used to calculate hash values with SHA1, SHA256 and SM3.

%prep
%autosetup -n %{name}-%{version} -p1 -Sgit

%build
gcc -Wall -g -c hash_calculate.c -o hash_calculate.o
gcc -Wall -g -lcrypto hash_calculate.o -o hash_calculate
rm -f hash_calculate.o

%install
install -D -m 0755 hash_calculate $RPM_BUILD_ROOT/usr/bin/hash_calculate

%check

%pre

%preun

%post

%postun

%files
%defattr(-,root,root)
%{_bindir}/*

%changelog
* Wed Dec 1 2021 openEuler Buildteam <buildteam@openeuler.org> - 1.0-2
- Support SM3 digest calculation

* Mon Aug 2 2021 openEuler Buildteam <buildteam@openeuler.org> - 1.0-1
- Package init
