MASTERCHEF MANAGEMENT SOFTWARE
==============================

# Table of Contents

1. [Synopsis](#i-synopsis)
2. [General Features](#ii-general-features)
3. [User Manual](#iii-user-manual)
4. [Technical Details](#iv-technical-details)

# I. Synopsis

**Masterchef Management Software** is a simple but functional program
(_hopefully_) to manage a list of _masterchefs_. Despite the culinary-themed
branding, at its core, Masterchef Management Software is a simple employee
management program that can be readily adapted to any use cases.

# II. General Features

* Add, edit and delete _masterchefs_
* Load and save managed _masterchefs_ to a specified location
* Display _masterchefs_ in a nicely-formatted table.
* Search for particular _masterchefs_ either by name or by a salary range.
* Calculate the total salary of managed _masterchefs_

# III. User Manual

## 1. Startup

_This is possibly the most confusing part of the program. Please do excuse the
verbosity of this section._

Whenever you launch the program, you will have the option to load an existing
file. Should you choose to do so, you must enter the path to the file **relative
to where you launched the program**. Please note that this is different from
entering a path _relative to the program itself_.

For example, suppose that we have to work with the following directory structure:

```
Documents
|  my_file.txt
|  my_other_file.txt
|
|--Masterchef_Manager
|  |  MasterchefManager.bin
|  |  test.chefs
|  |
|  |--save_files
|     |  demo.chefs
|     |  master.chefs
|
|--My Directory
|  |  something.txt
|  |  nothing.txt
```

If we launch `MasterchefManager.bin` directly in _its own directory_, to load
either `test.chefs` or `demo.chefs`, we can simply enter the relative path to
the respective file:

```
> test.chefs
```

or alternatively:

```
> save_files/demo.chefs
```

Please note that the path separator differs across operating systems. On
Windows, to load `demo.chefs`, we would have to enter the following path
instead:

```
> save_files\demo.chefs
```

In the case that we launch `MasterchefManager.bin` _from outside of its
directory_, for instance:

``` shell
~/Documents $ ./Masterchef_Manager/MasterchefManager.bin
```

or alternatively on Windows:

```
PS D:\Documents> .\Masterchef_Manger\MasterchefManager.exe
```

Now, in order to load `test.chefs` or `demo.chefs`, we must enter the respective
path to these files, _relative to the current directory_. For example:

```
> Masterchef_Manager/test.chefs
```

```
> Masterchef_Manager/save_files/demo.chefs
```

or alternative on Windows:

```
> Masterchef_Manager\test.chefs
```

```
> Masterchef_Manager\save_files\demo.chefs
```

This quirk results from the implementation of `fopen()`, which could probably be
remedied if it weren't for the time constraints of the project.

# IV. Technical Details

## 1. Data Structure

### 1.1 Representing a Single Chef

Each _masterchef_ is stored within a `struct chefObj` containing the following
fields, referred to internally as _properties_:

* `name`: string, sentence capitalization & proper spacing.
* `role`: string, one of the following values (MASTER CHEF > SEASONED CHEF > JUNIOR CHEF > APPRENTICE COOK).
* `dateOfBirth`: string, "YYYY-MM-DD" format.
* `salary`: long integer.

In retrospect, it would have been more flexible to store `dateOfBirth` as its
own `struct` within `struct chefObj`. In fact, whenever the `dateOfBirth`
property is accessed, the program must first convert its string representation
to its `struct` form. This is unnecessarily time-consuming and it's also quite
_inelegant_, to say the least.

### 1.2 Representing Multiple Chefs

A list of _masterchefs_, hereby simply referred to as a _chef list_, is
represented with an _array of pointers to struct_ (yes). Although it would have
been (_arguably_) simpler to represent a _chef list_ with a simple _array of
structs_, this method can be rather inflexible at times.

One of the primary concerns is the modification of each `struct chefObj`.
Suppose that we have a function `setName()` which changes the name of a single
`struct chefObj`. If we were to store the _chef list_ using a regular array of
structs, we would have to pass the _pointer_ of the struct into the function
every time we would like to modify it:

``` c
setName(&chefList[i], newName);
```

Whereas if we take the extra step to store the _chef list_ in an array of
pointers, we can simply call the function like so, which is arguably much more
intuitive for the user:

``` c
setName(chefList[i], newName);
```

Another concern is with the initialization of the _chef list_. Using a regular
array of structs, one must first set all properties within `struct chefObj` to
some sort of _sentinel values_. This is to help the program differentiate
between _occupied_ and _unoccupied_ slots within the list. In other words, **we
don't want the program to accidentally modify an existing chef in the list**.

Using _sentinel values_ is rather undesirable due to the extra work needed to
deal with these values when we interact with the _chef list_. This could, of
course, be streamlined with the help of _wrapper functions_. However, depending
on their specific implementation, using them may also prove to be rather
_unwieldy_.

In the case of using an array of pointers to structs, to check whether a spot
in the list is _occupied_ or vice versa, one could simply perform a check like
so:

``` c
if (chefList[i] != NULL) {
    // Do something
}
```

Nevertheless, it must be admitted that this method of representing a _chef list_
is not entirely without flaws. In fact, one may very well argue that this
representation only adds extra complexity to program without any real benefits.
Perhaps it have been wiser to implement a combination of these two methods.

## 2. File Format

Managed _masterchefs_ should preferably be saved in a `.chefs` file to avoid
any potential confusion, although the program is perfectly capable of reading
from any types of file, as long as it is formatted correctly.

Each line in the file represents a single `struct chefObj` and must be formatted
like so:

```
NAME:Chef Name,ROLE:Chef Role,DOB:YYYY-MM-DD,SAL:1234567890\n
```

For example:

```
NAME:John Doe,ROLE: MASTER CHEF,DOB:1980-01-01,SAL:1234567890\n
```

It is crucial that each line in the list (including the last one) must be
terminated with a _newline_ character (`\n'). Otherwise, the program won't be
able to parse the saved file properly.

## 3. Software Components

Masterchef Management Software is subdivided into several smaller components,
each of which is responsible for implementing a different aspect of the
program as a whole.

```
Masterchef Manager
|- Chef List
|- Chef Object
|- Database
|- Date Parser
|- String Format
|- User Interface
```

### 3.1 Masterchef Manager

This is the driver code for the program. It is responsible for linking all
components together in order to form the final product.

### 3.2 Chef List

This component is responsible for creating and modifying a given _chef list_.
This includes operations such as extending, sorting and/or running a search
query on a _chef list_.

### 3.3 Chef Object

This component defines the internal data structure of a single chef and
provides methods to modify or retrieve certain from a particular chef. The
program only interacts indirectly with each _chef object_ using the provided
methods and never directly with the _chef object_ itself.

### 3.4 Database

This component is responsible for loading and saving _chef lists_ to disk,
ensuring that the data is properly formatted.

### 3.5 Date Parser

This component is responsible for parsing and interpreting date strings and then
translating them into the appropriate format for internal use.

### 3.6 String Format

Like its name implies, this component provides methods to transform strings into
the appropriate format, either for internal use or for the user interface.

### 3.7 User Interface

This component defines the user interface of the program (_obviously_) and
handles all interactions between the user and the program itself.
