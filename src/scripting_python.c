#include <Python.h>


// Because some people think Windows is a good idea
#ifdef OS_Windows
#include <Windows.h>
#endif


#include <hap.h>
#include "engine.h"


HAP_MODULE_EXPORT void* create(HAPEngine *engine, HAPConfigurationSection *configuration) {
    wchar_t *program = Py_DecodeLocale((*engine).name, NULL);

    if (program == NULL)
        (*engine).log_fatal_error(
            engine,
            30,
            "Can not initialize locale for %s.\n",
            (*engine).name
        );

    PyImport_AppendInittab((*engine).name, PyInit_hap);

    Py_SetProgramName(((wchar_t**) (*engine).argvp)[0]);
    Py_Initialize();

    return program;
}


HAP_MODULE_EXPORT void load(HAPEngine *engine, void *state, char *identifier) {
    (void)engine;
    (void)identifier;
    (void)state;

    // TODO: Add engine APIs to Python so that we can log_debug via Python
	(*engine).log_debug(engine, "Loaded Python scripting plugin");
}


HAP_MODULE_EXPORT HAPTime update(HAPEngine *engine, void *state) {
    (void)engine;
    (void)state;

    return 0;
}


HAP_MODULE_EXPORT void unload(HAPEngine *engine, void *state) {
    (void)engine;
    (void)state;
}


HAP_MODULE_EXPORT void destroy(HAPEngine *engine, void *state) {
    (void)engine;

    Py_Finalize();
    PyMem_RawFree(state);
}
