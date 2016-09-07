#include <Python.h>
#include <sys/personality.h>
#include <stdint.h>
#include <stdbool.h>

static int Cget_personality(void) {
    unsigned long persona = 0xffffffffUL;
    return personality(persona);
}

static PyObject* get_personality(PyObject* self) {
    return Py_BuildValue("i", Cget_personality());
}

static int Cset_personality(unsigned long persona) {
    return personality(persona);
}

static PyObject* set_personality(PyObject* self, PyObject *args) {
    unsigned long persona;
    
    if (!PyArg_ParseTuple(args, "i", &persona))
        return NULL;

    Cset_personality(persona);
    if (Cget_personality() == persona) {
        return Py_BuildValue("b", true);
    } else {
        return Py_BuildValue("b", false);
    }
}

static PyObject* version(PyObject* self) {
    return Py_BuildValue("s", "Version 1.0");
}

static PyMethodDef personality_methods[] = {
    {"get_personality", (PyCFunction)get_personality, METH_NOARGS, "Returns the personality value"},
    {"set_personality", (PyCFunction)set_personality, METH_VARARGS, "Sets the personality value"},
    {"version", (PyCFunction)version, METH_NOARGS, "Returns the version number"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pypersonality = {
    PyModuleDef_HEAD_INIT,
    "personality",
    "Module to manipulate process execution domain",
    -1,
    personality_methods
};


PyMODINIT_FUNC PyInit_pypersonality(void) {
    PyObject *module;
    module = PyModule_Create(&pypersonality);
    
    PyModule_AddIntMacro(module, UNAME26);
    PyModule_AddIntMacro(module, ADDR_NO_RANDOMIZE);
    PyModule_AddIntMacro(module, FDPIC_FUNCPTRS);
    PyModule_AddIntMacro(module, MMAP_PAGE_ZERO);
    PyModule_AddIntMacro(module, ADDR_COMPAT_LAYOUT);
    PyModule_AddIntMacro(module, READ_IMPLIES_EXEC);
    PyModule_AddIntMacro(module, ADDR_LIMIT_32BIT);
    PyModule_AddIntMacro(module, SHORT_INODE);
    PyModule_AddIntMacro(module, WHOLE_SECONDS);
    PyModule_AddIntMacro(module, STICKY_TIMEOUTS);
    PyModule_AddIntMacro(module, ADDR_LIMIT_3GB);
    PyModule_AddIntMacro(module, PER_LINUX);
    PyModule_AddIntMacro(module, PER_LINUX_32BIT);
    PyModule_AddIntMacro(module, PER_LINUX_FDPIC);
    PyModule_AddIntMacro(module, PER_SVR4);
    PyModule_AddIntMacro(module, PER_SVR3);
    PyModule_AddIntMacro(module, PER_SCOSVR3);
    PyModule_AddIntMacro(module, PER_OSR5);
    PyModule_AddIntMacro(module, PER_WYSEV386);
    PyModule_AddIntMacro(module, PER_ISCR4);
    PyModule_AddIntMacro(module, PER_BSD);
    PyModule_AddIntMacro(module, PER_SUNOS);
    PyModule_AddIntMacro(module, PER_XENIX);
    PyModule_AddIntMacro(module, PER_LINUX32);
    PyModule_AddIntMacro(module, PER_LINUX32_3GB);
    PyModule_AddIntMacro(module, PER_IRIX32);
    PyModule_AddIntMacro(module, PER_IRIXN32);
    PyModule_AddIntMacro(module, PER_IRIX64);
    PyModule_AddIntMacro(module, PER_RISCOS);
    PyModule_AddIntMacro(module, PER_SOLARIS);
    PyModule_AddIntMacro(module, PER_UW7);
    PyModule_AddIntMacro(module, PER_OSF4);
    PyModule_AddIntMacro(module, PER_HPUX);
    PyModule_AddIntMacro(module, PER_MASK);
    
    return module;

}

