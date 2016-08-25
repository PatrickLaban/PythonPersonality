#include <Python.h>
#include <sys/personality.h>
#include <stdint.h>

int32_t Cget_personality(void) {
	unsigned long persona = 0xffffffff;
	return personality(persona);
}

static PyObject* get_personality(PyObject* self) {
	return Py_BuildValue("i", Cget_personality);
}

static PyMethodDef personality_methods[] = {
	{"get_personality", (PyCFunction)get_personality, METH_NOARGS, "Returns the personality value"},
	/*	{"version", (PyCFunction)version, METH_NOARGS, "Returns the version number"}, */
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
	return PyModule_Create(&pypersonality);
}

