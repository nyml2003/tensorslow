class Animal:
    def speak(self):
        print("Animal speaks")


class Dog(Animal):
    def speak(self):
        print("Dog barks")


class Cat(Animal):
    def speak(self):
        print("Cat meows")


animal = Animal()
animal.speak()

dog = Dog()
dog.speak()

cat = Cat()
cat.speak()
