class Base:
    def say(self):
        print("Calling Base class method say()")


class Derived(Base):
    def say(self):
        print("Calling Derived class method say()")


d = Derived()
d.say()
