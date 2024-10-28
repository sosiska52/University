using omis_task2;

Console.WriteLine("Примеры возможных объектов класса B:\n");
//B objB = new B();     нельзя создать объект абстрактного класса
B objB = new C1();
objB.baseMethod();
objB = new C2();
objB.baseMethod();

Console.WriteLine("\nПримеры возможных объектов класса C1:\n");
C1 objC1 = new C1();
objC1.baseMethod();
objC1 = new C2();
objC1.baseMethod();

Console.WriteLine("\nПримеры возможных объектов класса C2:\n");
C2 objC2 = new C2();
objC2.baseMethod();
objC2.interfaceMethod1();
objC2.interfaceMethod2();
objC2.interfaceMethod3();

Console.WriteLine("\nПримеры возможных объектов классов IB1, IB2, I1:\n");
/*IB1 objIB1 = new IB1();   
IB2 objIB2 = new IB2();     нельзя создавать объекты-интерфейсы
I1 objI1 = new I1();*/

IB1 objIB1 = new C2();
objIB1.interfaceMethod1();

IB2 objIB2 = new C2();
objIB2.interfaceMethod2();  /*все эти объекты могут реализовывать только
                                          методы своих интерфейсов, не смотря на то что
                                          класс C2 имеет и другие методы*/
I1 objI1 = new C2();
objI1.interfaceMethod1();
objI1.interfaceMethod2();
objI1.interfaceMethod3();