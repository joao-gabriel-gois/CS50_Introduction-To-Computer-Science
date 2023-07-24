# Overall Data Structures Review

### Structs (built-in)
* Custom multiple types data type
* Fields with different types can be created with it
* Allows create custom data sructures once the minimun unit is able to store different type of data and metadata (supporting custom structure access/navigation details)
___
### Arrays (built-in)
* __insertion__ is _costly_
  * insertion demands shift O(n) elements to fit a new one
* __deletion__ is _costly_
  * deletion demands shift O(n) elements after removing old one
* __lookup__ is _super easy_
  * random access, constant time O(1)
* __sort__ is relatively _easy_
  * ordered by indexes, where you can apply binary search
* __fixed size__, no flexibility. Also small __size-wise__.
 
___
### Linked lists
* __insertion__ is _easy_
  * just stack add it in the beggining of the list
* __deletion__ is _easy_
  * once you find the element (linear)
* __lookup__ is _costly_
  * relies on linear search
* __sort__ is relatively _costly_
  * unless you are adding its cost to insertion by already sorting when doing it, so it will become O(0).

___

REVER DAQUI PRA BAIXO
* __There is to types of linked lists:__
  * __Singly Linked lists__:
    * only move torwards one direction 
  * __Doubly Linked lists__:
    * can move backwards and forwards

___
### Hash table
* __insertion__ is _two-step process_
  * hash, then add
* __deletion__ is _easy_
  * once you find the element
* __lookup__ is relatively _easy_
  * it is better in average than linked lists, cause you have a real world constant factor (less processing, more memory)
* __sort__ is real _costly_
  * not the proper data structure if sorting is a main goal
* Can run the gamut of size
  * It acutally tends to run faster because it uses more memory in order to access a singly linked list after removing a bunch of initial likely events on a table (REVER!)

___
### Tries
* __insertion__ is _costly_
  * insertion demands shift O(n) elements to fit a new one
* __deletion__ is _costly_
  * deletion demands shift O(n) elements after removing old one
* __lookup__ is _super easy_
  * random access, constant time O(1)
* __sort__ is relatively _easy_
  * ordered by indexes, where you can apply binary search
* __fixed size__, no flexibility. Also small __size-wise__.