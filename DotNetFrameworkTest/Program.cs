using System;
using Interop.RegFreeCpp;

namespace DotNetFrameworkTest
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("RegFreeCpp C# Test");

            var debugOutput = new MyDebugOutput();

            try
            {
                debugOutput.WriteLine("Debug message from MyDebugOuput");

                Console.WriteLine("MyDebugOutput succeeded");
            }
            catch(Exception ex) 
            { 
                Console.WriteLine("MyDebugOutput failed: " + ex.ToString());
            }
        }
    }
}
