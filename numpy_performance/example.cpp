#include <utility>
#include <vector>

#include "pybind11/numpy.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;

class matrix {
 public:
  matrix(std::vector<std::vector<double>> data, std::vector<double> labels)
      : data_{std::move(data)}, labels_{std::move(labels)} {}

  [[nodiscard]] const std::vector<std::vector<double>> &get_data() const noexcept {
    return data_;
  }
  [[nodiscard]] const std::vector<double> &get_labels() const noexcept {
    return labels_;
  }

 private:
  std::vector<std::vector<double>> data_;
  std::vector<double> labels_;
};

void init_numpy_performance(py::module_ &m) {
//  py::class_<matrix>(m, "Matrix")
//      .def(py::init<std::vector<std::vector<double>>, std::vector<double>>())
//      .def("get_data", &matrix::get_data)
//      .def("get_labels", &matrix::get_labels);

  py::class_<matrix>(m, "Matrix")
      .def(py::init([](const py::array_t<double> &data, const py::array_t<double> &labels) {
        if (data.ndim() != 2) {
          throw py::attribute_error{"The data must have exactly two dimensions!"};
        }
        if (labels.ndim() != 1) {
          throw py::attribute_error{"The labels must have exactly one dimension!"};
        }
        if (data.shape(0) != labels.shape(0)) {
          throw py::attribute_error{"The data and labels must have exactly the same number of data points!"};
        }

        std::vector<std::vector<double>> data_vec(data.shape(0));
        for (std::size_t i = 0; i < data_vec.size(); ++i) {
          data_vec[i] = std::vector<double>(data.data(i, 0), data.data(i, 0) + data.shape(1));
        }
        std::vector<double> label_vec(labels.data(0), labels.data(0) + labels.shape(0));

        return matrix{std::move(data_vec), std::move(label_vec)};
      }))
      .def("get_data", [](const matrix &self) {
        const std::vector<std::vector<double>> &data = self.get_data();
        const std::size_t num_data_points = data.size();
        const std::size_t num_features = data.front().size();

        py::array_t<double> py_array({ num_data_points, num_features });
        py::buffer_info buffer = py_array.request();
        auto *ptr = static_cast<double *>(buffer.ptr);
        for (std::size_t i = 0; i < num_data_points; ++i) {
          for (std::size_t j = 0; j < num_features; ++j) {
            ptr[i * num_features + j] = data[i][j];
          }
        }
        return py_array;
      })
      .def("get_labels", [](const matrix &self) {
        const std::vector<double> &labels = self.get_labels();

        py::array_t<double> py_array(labels.size());
        py::buffer_info buffer = py_array.request();
        auto *ptr = static_cast<double *>(buffer.ptr);
        for (std::size_t i = 0; i < labels.size(); ++i) {
          ptr[i] = labels[i];
        }
        return py_array;
      });
}