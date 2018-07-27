/** Modifies the linker so that it uses proper symbol names in MSVC. **/
#ifdef OS_Windows
#pragma comment(linker, "/EXPORT:create=create")
#pragma comment(linker, "/EXPORT:load=load")
#pragma comment(linker, "/EXPORT:update=update")
#pragma comment(linker, "/EXPORT:unload=unload")
#pragma comment(linker, "/EXPORT:destroy=destroy")
#endif


// Because some people thing Windows is a good idea
#ifdef OS_Windows
#include <Windows.h>
#endif


#include <Python.h>

#include <hap.h>
#include "engine.h"


PyObject *wat;


void* create(HAPEngine *engine) {
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


void load(HAPEngine *engine, void *state, char *identifier) {
    (void)engine;
    (void)identifier;
    (void)state;

    // TODO: Add engine APIs to Python so that we can log_debug via Python
    PyRun_SimpleString("print('Python scripting enabled')");
}


HAPTime update(HAPEngine *engine, void *state) {
    (void)engine;
    (void)state;

    return 0;
}


void unload(HAPEngine *engine, void *state) {
    (void)engine;
    (void)state;
}


void destroy(HAPEngine *engine, void *state) {
    (void)engine;

    Py_Finalize();
    PyMem_RawFree(state);
}
