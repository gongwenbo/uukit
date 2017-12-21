class Foo{}

obj = new Foo() ;
obj1 = new Foo ;
问题是:两种定义有区别吗?

如果Foo的构造函数是Foo::Foo()  二者没有没有问题,
但是Foo的构造是Foo::Foo(int index) obj1 = new Foo 是无法定义的.



