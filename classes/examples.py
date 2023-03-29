import showcase

#
# simple
#
print("\nsmiple:")

s = showcase.student(12345, "Max Mustermann", 14.50)
print(s.id)
# s.id = 00000
print(s.get_name())
print(s.get_salary())
s.raise_salary(0.5)
print(s.get_salary())

#
# templates
#
print("\ntemplates:")

w = showcase.WrapperDouble(3.1415)
print(w.value)
w.value = 2.7182
print(w.value)

w = showcase.WrapperInt(42)
print(w.value)

w = showcase.Wrapper(100)
print(w.value)

#
# inheritance
#
print("\ninheritance:")

# a = showcase.Animal()

a = showcase.Cat()
a.what_does_the_animal_say()

a = showcase.Dog()
a.what_does_the_animal_say()

