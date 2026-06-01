#include "ResultMgr.hpp"
#include <QCoreApplication>
#include <QDir>
#include <ResultChecker/ResultChecker.hpp>
#include <filesystem>
#ifndef _WIN32
    #include <dlfcn.h>
#endif
#ifdef __APPLE__
    #include <CoreFoundation/CFBundle.h>
    #include "../ParseMach.hpp"
#endif
#ifdef __ANDROID__
    #include <android/native_activity.h>
    #include "../ParseElf.hpp"
#endif


#ifdef __APPLE__
static std::string GetBundleFrameworksDir() {
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef url = CFBundleCopyPrivateFrameworksURL(mainBundle);
    char path[PATH_MAX] {};
    if (CFURLGetFileSystemRepresentation(url, true, (UInt8*)path, sizeof(path))) {
        CFRelease(url);
        return path;
    }
    CFRelease(url);
    abort();
}

/** Get path to dylib inside framework */
static std::string DylibPath(std::filesystem::path frameworkPath, bool fullPath) {
    std::string path = fullPath ? frameworkPath : frameworkPath.filename();
    path += "/";
    path += frameworkPath.stem(); // filename without extension
    return path;
}
#endif

#ifdef __ANDROID__
static std::string GetNativeLibraryDir(ANativeActivity& activity) {
    JNIEnv* env = nullptr;
    activity.vm->AttachCurrentThread(&env, nullptr);
    std::string result;
    {
        // get ApplicationInfo object
        // DOC: https://developer.android.com/reference/android/content/pm/ApplicationInfo
        jclass actCls = env->GetObjectClass(activity.clazz);
        jmethodID getAppInfo = env->GetMethodID(actCls, "getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;");
        jobject appInfo = env->CallObjectMethod(activity.clazz, getAppInfo);

        // access nativeLibraryDir field
        jclass aiCls = env->GetObjectClass(appInfo);
        jfieldID fid = env->GetFieldID(aiCls, "nativeLibraryDir", "Ljava/lang/String;");
        auto jstr = (jstring)env->GetObjectField(appInfo, fid);

        const char* buffer = env->GetStringUTFChars(jstr, nullptr);
        result = buffer;
        env->ReleaseStringUTFChars(jstr, buffer);
    }
    activity.vm->DetachCurrentThread();
    return result;
}
#endif

static QString GetSharedLibFolder() {
    QString exePath = QCoreApplication::applicationDirPath();
#ifdef __APPLE__
  #if TARGET_OS_IPHONE
    // iOS: @executable_path/Frameworks)
    QDir libDir(exePath);
    libDir.cd("Frameworks");
    return libDir.absolutePath();
  #else
    // macOS: @executable_path/../Frameworks
    QDir libDir(exePath);
    libDir.cd("..");
    libDir.cd("Frameworks");
    return libDir.absolutePath();
  #endif
#else
    // Linux, Android, Windows: @executable_path
    return exePath;
#endif
}


ResultMgr::ResultMgr() : m_mask(9, '\0') {
    printf("ResultChecker loaded.\n");

    // load ResultChecker library
#ifdef _WIN32
    m_lib = LoadLibraryW(L"ResultChecker.dll");
    m_func_ptr = (decltype(&CheckForWin))GetProcAddress(m_lib, "CheckForWin");
#else
  #ifdef __APPLE__
    m_lib = dlopen("ResultChecker.framework/ResultChecker", RTLD_LAZY); // macOS, iOS
  #else
    m_lib = dlopen("libResultChecker.so", RTLD_LAZY); // Linux, Android
  #endif
    m_func_ptr = (decltype(&CheckForWin))dlsym(m_lib, "CheckForWin");
#endif
}

ResultMgr::~ResultMgr() {
    printf("ResultChecker unloaded.\n");

    // unload ResultChecker library
#ifdef _WIN32
    FreeLibrary(m_lib);
    m_lib = nullptr;
#else
    dlclose(m_lib);
    m_lib = nullptr;
#endif
    m_func_ptr = nullptr;
}

ResultMgr::State ResultMgr::check(const QByteArray& cells) {
    assert(cells.size() == 9);

    m_mask.fill('\0');
    GameState val = m_func_ptr(cells, /*out*/m_mask);

    return (State)val;
}

QByteArray ResultMgr::mask() {
    return m_mask;
}
