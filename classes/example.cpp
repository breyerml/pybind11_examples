#include <iostream>
#include <string>
#include <utility>

#include "pybind11/pybind11.h"

namespace py = pybind11;

class student {
 public:
  student(const int id, std::string name)
      : id_{id}, name_{std::move(name)} {}
  student(const int id, std::string name, const double salary)
      : id_{id}, name_{std::move(name)}, salary_{salary} {}

  [[nodiscard]] const std::string &get_name() const noexcept {
    return name_;
  }
  [[nodiscard]] double get_salary() const noexcept {
    return salary_;
  }
  void raise_salary(double factor) noexcept {
    salary_ *= 1.0 + factor;
  }

  int id_{};

 private:
  std::string name_{};
  double salary_{};
};

void init_classes_simple(py::module_ &m) {
  py::class_<student>(m, "student")
      .def(py::init<int, std::string>())
      .def(py::init<int, std::string, double>())
      .def_readonly("id", &student::id_)
      .def("get_name", &student::get_name)
      .def("get_salary", &student::get_salary)
      .def("raise_salary", &student::raise_salary);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class wrapper {
 public:
  explicit wrapper(T value) : value_{value} {}

  void set(T value) {
    value_ = value;
  }
  [[nodiscard]] T get() const noexcept {
    return value_;
  }

 private:
  T value_{};
};

template<typename T>
void create_wrapper_bindings(py::module_ &m, const std::string &name) {
  py::class_<wrapper<T>>(m, name.c_str())
      .def(py::init<T>())
      .def_property("value", &wrapper<T>::get, &wrapper<T>::set);
}

void init_classes_templates(py::module_ &m) {
//    py::class_<wrapper<double>>(m, "Wrapper")
//        .def(py::init<double>())
//        .def_property("value", &wrapper<double>::get, &wrapper<double>::set);
//
//    py::class_<wrapper<int>>(m, "Wrapper")
//        .def(py::init<int>())
//        .def_property("value", &wrapper<int>::get, &wrapper<int>::set);

  create_wrapper_bindings<double>(m, "WrapperDouble");
  create_wrapper_bindings<int>(m, "WrapperInt");

  m.attr("Wrapper") = m.attr("WrapperDouble");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class animal {
 public:
  void what_does_the_animal_say() const {
    this->say();
  }
  virtual ~animal() = default;

 protected:
  virtual void say() const = 0;
};

class cat : public animal {
 private:
  void say() const override {
    std::cout << "miau" << std::endl;
  }
};

class dog : public animal {
 private:
  void say() const override {
    std::cout << "woof" << std::endl;
  }
};

void init_classes_inheritance(py::module_ &m) {
  py::class_<animal>(m, "Animal")
      .def("what_does_the_animal_say", &animal::what_does_the_animal_say);

  py::class_<cat, animal>(m, "Cat")
      .def(py::init<>());
  py::class_<dog, animal>(m, "Dog")
      .def(py::init<>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_classes(py::module_ &m) {
  init_classes_simple(m);
  init_classes_templates(m);
  init_classes_inheritance(m);
}