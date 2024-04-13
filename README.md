**Assignment Review System**

__Inheritance:__

Inheritance is employed through the Student and Reviewer classes, both derived from the IMG_Member base class. They inherit common attributes and behaviors such as name and role.

__Polymorphism:__
Polymorphism is achieved through virtual functions in the IMG_Member base class.  give_choices is declared as virtual function and overridden in the derived classes to enable different implementations based on the object's type.
__Encapsulation:__
Member variables name and role are encapsulated within the IMG_Member base class. They are accessible only within the class hierarchy, promoting data hiding and preventing unauthorized access from outside the classes.

__Abstraction:__
Virtual functions view_assignment_status() and give_choices() in the IMG_Member class are abstract, meaning they don't have an implementation in the base class. They are meant to be overridden by derived classes.