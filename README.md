# eigar
eiger - Entity Information Gatherer And Reporter - is a library that aims to provide single API 
for access to metrics like:
* resource usage (cpu/memory/disk/etc.)
* hardware specifications (physically installed memory, cpu cache sizes, gpu bus widths, etc.)

Initial target is to support operating systems that currently receive updates per their life cycle. As of 2021.11.27, that would be 
* Windows 10 (end of life: 2025.10.14)
* Windows 11
* various Linux distributions, for Ubuntu that would be:
    * 18.04 LTS (end of life: 2023.04)
    * 20.04 LTS (end of life: 2025.04)
    * 22.04 LTS (planned release date: 2022.04.21, planned end of life: 2027.04)
  
Couple of requirements at start:
* Do not require additional system specific libraries (for Windows, that would be installation of specific versions of vcredist)
* Do not require privileged-user permissions as much as possible
* Support old os/hardware combinations as long as this does not conflict with support for current of future os/hardware
* Core library will be written C
* Provide bindings for higher-level languages, like:
  * C++
  * Java
  * Python
  * Go