#include <Python.h>

#include <hap.h>

#include "engine.h"


static struct PyModuleDef hapModule = {
    PyModuleDef_HEAD_INIT,
    "hap",
    NULL,
    -1,
    NULL
};


PyMODINIT_FUNC PyInit_hap(void) {
    return PyModule_Create(&hapModule);
}
