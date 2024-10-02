#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

// Renaming struct to Class
// To make easier the comparison with
// OOP langs
#define Class struct

// struct;
Class Person {
  char name[10];
  uint8_t age;
  uint8_t height;
  // bellow there is a pointer to a function
  // that will be referenced from Person Class
  // instance as show that should return void and
  // receive a pointer to a Person Class
  void(*show)(Class Person *);
};
// constructor
Class Person * newPerson(char name[], uint8_t age, uint8_t height);

// struct
Class Dog {
  char name[10];
  uint8_t age;
  uint8_t weight;
  // Similar to person class but
  // We will move method to work as
  // a callback, on stack, instead of
  // predefining in struct to work by reference
  // But there is a new method as well, as per bellow
  void(*bark)(Class Dog *);
};
// contructor
Class Dog * newDog(char name[10], uint8_t age, void(*printDog) (Class Dog *));
//Callback for dog instantiation
void print_dog(Class Dog *self);



int main() {
  Class Person *joao = (Class Person *) newPerson("João", 28, 170);
  // below, print_dog will be executed as a callback for dog instantiation
  // while above person show is set as method and will run after fluff instance 
  // is constructed.
  Class Dog *fluff = (Class Dog *) newDog("Fluff", 8, &print_dog); 
 
  printf("\n");
  // Using Person Method
  joao->show(joao);
  printf("\n");
  // Using Dog Method
  fluff->bark(fluff);
  printf("\n");
  return 0;
}


void print_person(Class Person *self) {
  printf("[show - Person's method] Pessoa -> Nome: %s | Idade: %d | Altura: %d\n",
    self->name, self->age, self->height);
}

// Person "constructor" function which returns a
// Pointer to a Person Class
Class Person * newPerson(
  char name[],
  uint8_t age,
  uint8_t height
) {

  Class Person *self = (Class Person *) malloc(sizeof(Class Person));
 
  strcpy(self->name, name);
  self->age = age;
  self->height = height;
  
  self->show = &print_person;

  return self;
}

void bark(Class Dog *self) {
  printf("[bark - Dog's method]%s: Wooof! Wooooof!!\n", self->name);
}

Class Dog * newDog(
  char name[10],
  uint8_t age,
  void(*printDog) (Class Dog *)
) {

  Class Dog *self = (Class Dog *) malloc(sizeof(Class Dog));
 
  strcpy(self->name, name);
  self->age = age;

  self->bark = &bark;
  // Bellow is the callback, it will use the stack
  // immediately and execute once this block run, using
  // printDog as reference for print_dog
  (*printDog)(self);

  return self;
}

void print_dog(Class Dog *self) {
  printf("\n[printDog - Dog's creation Callback]: Cachorro -> Nome: %s | Idade: %d\n",
    self->name, self->age);
}
