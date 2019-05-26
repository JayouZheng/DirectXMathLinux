# DirectXMathLinux

DirectXMath (https://github.com/microsoft/DirectXMath) version that compiles on Linux.
Tested with Clang 8.0.0

Oh, btw. it still compiles with MSVC and can be used on Windows.

## What I did

* Initializer list `{ { { ... } } }` -> `{ ... }`
* Replaced `__declspec(align(16))` with `alignas(16)`
* Added many `#idfef _MSC_VER #pragma ... #endif`
* Some other minor stuff
* `XMVerifyCPUSupport()` always returns `true`
