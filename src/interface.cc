#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "geometry3.hh"
#include "cube.hh"
#include "trajectory.hh"

namespace py = pybind11;

PYBIND11_PLUGIN(libtropicity) {
  py::module m("lalala", "pybind11 ... whatever");

// class coord3d
  py::class_<coord3d>(m, "coord3d") 
    .def(py::init<float, float, float>());

// class cube
  py::class_<Cube>(m, "cube")
    .def(py::init<string>())
    .def("gettropplaneZ", &Cube::gettropplaneZ) // double
    .def("writetropplaneZ", &Cube::writetropplaneZ) // string, vector<vector<int>>
    .def("writecube", &Cube::writecube) // string
    .def("getvector", &Cube::getvector) // coord3d
    .def("outofbounds", &Cube::outofbounds); //coord3d

// class trajectory
  py::class_<trajectory>(m, "trajectory")
    .def(py::init<coord3d, coord3d, float>());



// // class canvas
//   py::class_<canvas>(m, "canvas")
//     .def(py::init<const string , int , int>())
//     .def("bucket_fill", &canvas::bucket_fill) // int, int, int
//     .def("render_scene", &canvas::render_scene) // scene
//     .def("highlight_edges", &canvas::highlight_edges)
//     .def("draw_coast", &canvas::draw_coast) // scene
//     .def("annotate_peaks", &canvas::annotate_peaks) // scene
//     .def("annotate_islands", &canvas::annotate_islands) // scene
//     .def("label_axis", &canvas::label_axis); // scene

    return m.ptr();
}

