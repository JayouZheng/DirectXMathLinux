#if defined(__ARM_ARCH) || defined(_M_ARM) || defined(_M_ARM64)
#   define BUILD_ARCH_ARM 1
#elif defined(_MSC_VER)
#   if defined(_M_X86) || defined(_M_X64)
#       define BUILD_ARCH_X86 1
#   endif
#elif defined(__GNUC__) || defined(__clang__)
#   if defined(__i386__) || defined(__x86_64__)
#       define BUILD_ARCH_X86 1
#   endif
#endif

#if defined(_WIN32)
#   define BUILD_PLATFORM_WIN 1
#elif defined(__APPLE__)
#   include "TargetConditionals.h"
#   if defined(TARGET_OS_IPHONE)
#       define BUILD_PLATFORM_IOS 1
#   else
#       define BUILD_PLATFORM_OSX 1
#   endif
#elif defined(__linux__) || defined(__gnu_linux__) || defined(linux)
#   define BUILD_PLATFORM_LINUX 1
#elif defined(__unix__)
#   define BUILD_PLATFORM_UNIX 1
#elif defined(__ANDROID__)
#   define BUILD_PLATFORM_ANDROID 1
#endif

/*
 * BUILD_INTRINSICS_LEVEL 0..3. Try setting different levels and see what compiles/runs/doesn't crash.
 * 0 _XM_NO_INTRINSICS_
 * 1 Some
 * 2 More
 * 3 All
 */
#if defined(BUILD_PLATFORM_WIN)
#   if !defined(BUILD_INTRINSICS_LEVEL)
#       define BUILD_INTRINSICS_LEVEL 3
#   endif
#else
#   if !defined(BUILD_INTRINSICS_LEVEL)
#       define BUILD_INTRINSICS_LEVEL 1
#   endif
#endif

#if defined(BUILD_ARCH_ARM)
#   if defined(__ARM_NEON) && BUILD_INTRINSICS_LEVEL > 0
#       define _XM_ARM_NEON_INTRINSICS_
#   else
#       define _XM_NO_INTRINSICS_
#   endif
#else
#   if BUILD_INTRINSICS_LEVEL > 0
#       define _XM_SSE_INTRINSICS_
#   endif
#   if BUILD_INTRINSICS_LEVEL > 1
#       define _XM_SSE3_INTRINSICS_
#       define _XM_SSE4_INTRINSICS_
#       define _XM_AVX_INTRINSICS_
#   endif
#   if BUILD_INTRINSICS_LEVEL > 2
#       define _XM_F16C_INTRINSICS_
#   endif
#endif
#if defined(__GNUC__) || defined(BUILD_PLATFORM_IOS)
#   define _XM_NO_CALL_CONVENTION_
#endif
#if defined(BUILD_PLATFORM_IOS) || defined(BUILD_PLATFORM_ANDROID)
#   define _XM_ARM_NEON_NO_ALIGN_
#endif

// We need this first
#include <initializer_list>
// then we can include these
#include "DirectXMath.h"
#include "DirectXCollision.h"
#include <iostream>

using namespace DirectX;

int main()
{
	std::cout << "Testing AABB vs OBB 45 deg" << std::endl;
    // Works as expected. Maybe I shouldn't have negative orientation?
    BoundingBox abb({ -3.5f, 0.0f, -3.5f }, { 0.5f, 0.5f, 0.5f });
    // 45Deg Y
    XMFLOAT4 orientation = { 0.000000000f, 0.382683456f, 0.000000000f, 0.923879504f };

    BoundingOrientedBox obb({ 0.0f, 0.0f, 0.0f }, { 4.0f, 0.5f, 2.0f }, orientation);
    while (!abb.Intersects(obb))
    {
        abb.Center.x += 0.5f;
        abb.Center.z += 0.5f;
    }
    // Must intersect @ x = -1.5, z = -1.5
    if (!abb.Intersects(obb))
    	std::cout << "Fail!" << std::endl;
    else
    	std::cout << "Success!" << std::endl;
    if (abb.Center.x != -1.5f)
    	std::cout << "Fail!" << std::endl;
    else
    	std::cout << "Success!" << std::endl;
    if (abb.Center.z != -1.5f)
    	std::cout << "Fail!" << std::endl;
    else
    	std::cout << "Success!" << std::endl;

    BoundingBox abb2({ -2.5f, 0.0f, 2.5f }, { 0.5f, 0.5f, 0.5f });
    if (!abb2.Intersects(obb))
    	std::cout << "Fail!" << std::endl;
    else
    	std::cout << "Success!" << std::endl;

    while (abb2.Intersects(obb))
    {
        abb2.Center.x -= 0.5f;
        abb2.Center.z += 0.5f;
    }
    // Must intersect @ x = -2.0, z = 1.5
    if (abb2.Intersects(obb))
    	std::cout << "Fail!" << std::endl;
    else
    	std::cout << "Success!" << std::endl;

    if (abb2.Center.x != -3.5f)
    	std::cout << "Fail!" << std::endl;
    else
    	std::cout << "Success!" << std::endl;

    if (abb2.Center.z != 3.5f)
    	std::cout << "Fail!" << std::endl;
    else
    	std::cout << "Success!" << std::endl;

    return 0;
}
