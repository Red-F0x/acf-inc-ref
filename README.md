# C++ Static Reflection Library

There is a [lot of libraries][boost-hana] that provide the reflection for c++ and I know the c++ standard committee is currently working on a [c++ reflection library][std-ref] and I guess what you're thinking now: "Oh no, another one!". But I say: "Yes, this is another one", and this one is my own attempt to implement static reflection in c++.

## The Goals

The Goal is simple, make this thing possible:
```c++
void main()
{
  SomeType st {};
  // do something with st ...

  json_stream js;
  js << st; // this should serialise c++ object to json one

  xml_stream xs;
  xs << st; // and this to xml

  csv_stream cs;
  cs << st; // and this to csv

  // and so one ...
}
```

Of course, it should be possible to convert a stream back to c++ object, like here:
```c++
SomeType st {};

json_stream js;
js >> st;
```

But let's start with simple things first: the output.

## What do we need to make serialisation/reflection possible in c++?

First of all we need a c++ object. From the example above, it is an object of type `SomeType`. In addition, the object should be a **Bean**, more on this later.

The second thing we need is a member function `js << st`  what do the serialisation job for us. I call such a member function: **Service Call**.

### But, what is a Bean?

> From [Wikipedia][java-bean-wiki]: JavaBeans are classes that encapsulate many objects into a single object (the bean). They are serializable, have a zero-argument constructor, and allow access to properties using getter and setter methods.

Well, check whether a datatype _[is a class][std-is-class]_ and _[have a zero-argument constructor][std-is-constructible]_ is simple, but what about _access to properties using getter and setter methods_?

Ok, let us speak in c++ language. The _property_ is a **non-static member object** and _getter and setter methods_ are **non-static member function pointers**.

>**Note:** From now I call the _property_ **class member**, _getter access method_ **read access** and _setter access method_ **write access**.

#### But, how can one access a class member without having information about this?

The answer is simple: you can not do it. It is not possible without any kind of information about the class. To enable the access to an **class member** we need to _register_ them. Let's say we have a class that looks like this:
```c++
class SomeType
{

  bool m_bvalue { false };

public:
  bool getBvalue()              const { return m_bvalue;     }
  void setBvalue(bool t_bvalue)       { m_bvalue = t_bvalue; }

}; // class SomeType
```

This class has one **class member** called `m_bvalue` and two access member functions: first for **read access** `bool getBvalue() const` and second for **write access** `void setBvalue(bool)`.

With help of enumeration/indexing and metaprogramming is it possible to _register_ **class member** for later use in **Service Call**. We extend our example code.
```c++
}; // class SomeType

template <>
struct index<SomeType, 0> { };
```

Now we can say what `index<SomeType, 0>` is an data type representing a key for **class member** `m_bvalue`.

#### But a key does not help us as long as we do not have doors/constraints.

And here is the first konstrain we have to define.
```c++
}; // class SomeType

template <>
struct name_of<SomeType>
{
  static constexpr char value[] { "SomeType" };
};

template <>
struct index<SomeType, 0> { };

template <>
struct name_of<index<SomeType, 0>>
{
  static constexpr char value[] { "bvalue" };
}; // name_of m_bvalue
```

The next step needs a little more tap work, as we need the access to our **class member**.
```c++
}; // name_of m_bvalue

template <>
struct read_access<index<SomeType, 0>>
{
  using value_type = decltype(&SomeType::getBvalue);
  static constexpr value_type value = &SomeType::getBvalue;
};

template <>
struct write_access<index<SomeType, 0>>
{
  using value_type = decltype(&SomeType::setBvalue);
  static constexpr value_type value = &SomeType::setBvalue;
};
```

Now is it possible to write the code similar to:
```c++
template <typename Bean>
constexpr void print(Bean&& t_bean)
{
  std::cout << name_of<Bean>::value << '\n';
  std::cout << '{' << '\n';

  using index_type = index<Bean, 0>;
  std::cout << name_of<index_type>::value << ':' << (t_bean.*read_access<index_type>::value)() << '\n';

  std::cout << '}' << '\n';
}

void main()
{
  SomeType st {};
  print(st); // print's SomeType and bvalue to the standard output
}
```

This pseudocode outputs the following:
```shell
SomeType
{
bvalue:0
}
```

## Conclusion

That's it, all we need is to define a [partial template specialization][std-pts] for following cases:

- for **class**:
 - `name_of` - to make human readable name of given class

- for **class member**
 - `index` - unique key for class member
 - `name_of` - to make human readable name of given class member
 - `read_access` - to provide read access to class member
 - `write_access` - to provide write access to class member

The remaining work should take over this library.
[//]: # (The End)


[//]: # (Used links)
[boost-hana]: <http://www.boost.org/doc/libs/1_63_0/libs/hana/doc/html/index.html>
[std-ref]: <https://meetingcpp.com/index.php/br/items/reflections-on-the-reflection-proposals.html>
[java-bean-wiki]: <https://en.wikipedia.org/wiki/JavaBeans>
[std-is-class]: <http://en.cppreference.com/w/cpp/types/is_class>
[std-is-constructible]: <http://en.cppreference.com/w/cpp/types/is_constructible>
[std-pts]: <http://en.cppreference.com/w/cpp/language/partial_specialization>











