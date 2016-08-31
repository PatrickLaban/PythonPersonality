#include <Python.h>
#include <sys/personality.h>

int Cget_personality(void) {
	unsigned long int persona = 0xffffffff;
	return personality(persona);
}

static PyObject* get_personality(PyObject* self) {
	return Py_BuildValue("i", Cget_personality);
}

int Cset_personality(void) {
	unsigned long int persona = READ_IMPLIES_EXEC;
	return personality(persona);
}

static PyObject* set_personality(PyObject* self) {
	return Py_BuildValue("i", Cset_personality);
}

static PyMethodDef personality_methods[] = {
	{"get_personality", (PyCFunction)get_personality, METH_NOARGS, "Returns the personality value"},
	{"set_personality", (PyCFunction)set_personality, METH_NOARGS, "Sets the personality value"},
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

