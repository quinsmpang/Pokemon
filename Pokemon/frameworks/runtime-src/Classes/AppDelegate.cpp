#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "ZipUtils.h"

#include "Framework/lua/lua_framework_auto.hpp"
#include "Framework/lua/lua_framework_manual.hpp"
#include "Framework/lua/lua_decryption_loader.h"
#include "Framework/lanes/lanes.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "Framework/win32/KeyboardHelper.h"
#endif

#include "framework.h"
#include "version.h"

#define LANES_SUPPORTED 0
#define LUA_DECIPHER_SUPPORTED 0

using namespace CocosDenshion;
USING_NS_CC;

// The code is to fix Xcode 6 linking duplication issue.
// source: http://forum.openframeworks.cc/t/xcode6-beta-of-0-8-1-for-ios-8-0/16103/6
extern "C"{
    size_t fwrite$UNIX2003(const void *a, size_t b, size_t c, FILE *d)
    {
        return fwrite(a, b, c, d);
    }
    char *strerror$UNIX2003(int errnum)
    {
        return strerror(errnum);
    }
    time_t mktime$UNIX2003(struct tm * a)
    {
        return mktime(a);
    }
    double strtod$UNIX2003(const char * a, char ** b) {
        return strtod(a, b);
    }
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLView::createWithRect("Pokemon Sunrise", Rect(0, 0, 800, 480));
		director->setOpenGLView(glview);
	}

	glview->setDesignResolutionSize(800, 480, ResolutionPolicy::SHOW_ALL);

	FileUtils::getInstance()->addSearchPath("res");

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	bool res = framework::KeyboardHelper::getInstance()->hookOn();
	if (!res)
	{
		DWORD error = GetLastError();
		LPVOID pBuffer = NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&pBuffer, 0, NULL);
		MessageBoxW(NULL, (LPCTSTR)pBuffer, L"Error", MB_OK | MB_ICONINFORMATION);
		ExitProcess(-1);
	}
#endif

	// set pvr.ccz encryption key 33b495bcb090291ccb5aaa689a516406
	ZipUtils::setPvrEncryptionKey(0x33b495bc, 0xb090291c, 0xcb5aaa68, 0x9a516406);

	auto pEngine = LuaEngine::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
	lua_State *L = pEngine->getLuaStack()->getLuaState();
	// bind our framework to lua.
	register_all_psframework(L);
	register_all_psframework_manual(L);
#if LANES_SUPPORTED
	// multithreading lane lib
	lua_register_lanes(L);
#endif
	// version management.
	::printVersion();
	lua_register_psframework_version(L);
#if LUA_DECIPHER_SUPPORTED
    // use lua encryption.
    pEngine->addLuaLoader(framework_decipher_loader);
#endif

	pEngine->executeScriptFile("src/main.lua");

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	bool res = framework::KeyboardHelper::getInstance()->hookOn();
	if (!res)
	{
        DWORD error = GetLastError();
		LPVOID pBuffer = NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&pBuffer, 0, NULL);
		MessageBoxW(NULL, (LPCTSTR)pBuffer, L"Error", MB_OK | MB_ICONINFORMATION);
		ExitProcess(-1);
	}
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	framework::KeyboardHelper::getInstance()->hookOff();
#endif
}
