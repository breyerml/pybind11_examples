#include <iostream>

#include "pybind11/pybind11.h"

namespace py = pybind11;

enum class animal_type {
  cat,
  dog
};

void what_does_the_animal_say(const animal_type a) {
  switch (a) {
    case animal_type::cat:
      std::cout << "miau" << std::endl;
      break;
    case animal_type::dog:
      std::cout << "woof" << std::endl;
      break;
  }
}

void init_enums(py::module_ &m) {
  py::enum_<animal_type>(m, "AnimalType")
      .value("CAT", animal_type::cat)
      .value("DOG", animal_type::dog);

  m.def("what_does_the_animal_say", &what_does_the_animal_say);
}