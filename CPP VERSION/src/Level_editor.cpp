#include "Level_editor.hpp"

void level_editor() {
    /* Calls the python level_editor.py, which is an independent Tkinter program */

    setenv("PYTHONPATH",".",1);
    Py_Initialize();

    PyObject *pName, *pModule, *pDict, *pFunc;

    // Build the name object
    pName = PyString_FromString((char*)"editor");

    // Load the module object
    pModule = PyImport_Import(pName);
    if (pModule == 0) {
        PyErr_Print();
    }

    // pDict is a borrowed reference
    pDict = PyModule_GetDict(pModule);

    // pFunc is also a borrowed reference
    pFunc = PyDict_GetItemString(pDict, (char*)"level_editor");

    if (PyCallable_Check(pFunc))
    {
        PyObject_CallObject(pFunc,NULL); // Call the main function in the .py
        PyErr_Print();
    } else {
        PyErr_Print();
    }

    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);

    Py_Finalize();

}
