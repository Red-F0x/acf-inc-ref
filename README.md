# C++ Static Reflection Library

There is a lot of libraries that provide the reflection for c++ and i guess what you're thinking now: "Oh no, another one!". And I say: "Yes, i need another one", and this one is my own attempt to implement static reflection in c++.

## The Goals

The Goal is simple, make this thing possible:
```c++
int main()
{
  SomeType st {};
  // make something with st ...

  json_stream js;
  js << st; // this should serialise c++ object to json one

  xml_stream xs;
  xs << st; // and this to xml

  csv_stream cs;
  cs << st; // and this to csv

  // and so one ...

  return 0;
}
```

Of course, it should be possible to convert a stream back to c++ object, like here:
```c++
SomeType st {};

json_stream js;
js >> st;
```

But let's start with simple things first: output.

## What do we need to make serialisation/reflection possible in c++?

First of all we need a c++ object. From the example above, it is an object of type `SomeType`. In addition, the object should be a **Bean**, more on this later.

The second thing we need is a member function `js << st`  what do the serialisation job for us. I call such a member function: **Service Call**.














