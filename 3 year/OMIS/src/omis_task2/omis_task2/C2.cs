namespace omis_task2
{
    internal sealed class C2: C1, I1
    {
        public override void baseMethod()
        {
            Console.WriteLine("Overridden base method in C2");
        }

        public void interfaceMethod1()
        {
            Console.WriteLine("Interface method 1");
        }

        public void interfaceMethod2()
        {
            Console.WriteLine("Interface method 2");
        }

        public void interfaceMethod3()
        {
            Console.WriteLine("Interface method 3");
        }
    }
}
