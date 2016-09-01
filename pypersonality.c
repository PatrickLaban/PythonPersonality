#include <Python.h>
#include <sys/personality.h>
#include <stdint.h>

int Cget_personality(void) {
	unsigned long persona = 0xffffffffUL;
	return personality(persona);
}

static PyObject* get_personality(PyObject* self) {
	return Py_BuildValue("i", Cget_personality());
}

int Cset_personality(unsigned long persona) {
	return personality(persona);
}

static PyObject* set_personality(PyObject* self, PyObject *args) {
	unsigned long persona; // = READ_IMPLIES_EXEC;
	const char * personality;
	
	if (!PyArg_ParseTuple(args, "s", &personality))
		return NULL;
	
	if (strcmp(personality, "READ_IMPLIES_EXEC") == 0) {
		persona = READ_IMPLIES_EXEC;
	} else if (strcmp(personality, "ADDR_LIMIT_32BIT") == 0) {
		persona = ADDR_LIMIT_32BIT;
	} else {
		return Py_BuildValue("i", -1); 
	}
	
	return Py_BuildValue("i", Cset_personality(persona));
}

static PyMethodDef personality_methods[] = {
	{"get_personality", (PyCFunction)get_personality, METH_NOARGS, "Returns the personality value"},
	{"set_personality", (PyCFunction)set_personality, METH_VARARGS, "Sets the personality value"},
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

