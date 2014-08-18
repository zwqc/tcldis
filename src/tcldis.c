#include <Python.h>
#include <tcl.h>

static PyObject *
tcldis_test(PyObject *self, PyObject *args, PyObject *kwargs)
{
	static char *kwlist[] = {NULL};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "", kwlist))
		return NULL;

	Tcl_Interp *interp = Tcl_CreateInterp();

	Tcl_Obj *tObj = Tcl_NewObj();
	Tcl_AppendStringsToObj(tObj, "puts 1", NULL);

	const Tcl_ObjType *bct = Tcl_GetObjType("bytecode");
	if (Tcl_ConvertToType(interp, tObj, bct) != TCL_OK)
		return PyLong_FromLong(1);

	Tcl_DeleteInterp(interp);

	return PyLong_FromLong(0);
}

static PyMethodDef TclDisMethods[] = {
	{"test",  (PyCFunction)tcldis_test, METH_VARARGS | METH_KEYWORDS, "test"},
	{NULL, NULL, 0, NULL} /* Sentinel */
};

/* Module name is _tcldis */
PyMODINIT_FUNC
init_tcldis(void)
{
	PyObject *m = Py_InitModule("_tcldis", TclDisMethods);
	if (m == NULL)
		return;
}


