package somc_platform_flag_default

import (
    "android/soong/android"
    "android/soong/cc"
)

func globalFlags(ctx android.BaseContext) []string {
        var cflags []string
        flag_prepend := "-DTARGET_PLATFORM="
	somc_platform := "\"" + ctx.Config().Getenv("SOMC_PLATFORM") + "\""
	cflags = append(cflags, flag_prepend + somc_platform)
        return cflags
}

func somcPlatformFlagDefault(ctx android.LoadHookContext) {
        type props struct {
                Cflags []string
        }
        default_props := &props{}
        default_props.Cflags = globalFlags(ctx)

        ctx.AppendProperties(default_props)
}

func init() {
    android.RegisterModuleType("somc_platform_flag_default", somcPlatformFlagDefaultFactory)
}

func somcPlatformFlagDefaultFactory() android.Module {
    module := cc.DefaultsFactory()
    android.AddLoadHook(module, somcPlatformFlagDefault)
    return module
}

