using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using IronPython.Hosting;
using Microsoft.Scripting;
using Microsoft.Scripting.Hosting;

namespace HelloKinect
{
    /// <summary>
    /// Interaction logic for Interpreter.xaml
    /// </summary>
    public partial class Interpreter : Window
    {
        private ScriptEngine m_engine = Python.CreateEngine();
        private ScriptScope m_scope = null;
        private TextWriter _writer = null;
        private MemoryStream m_ms = new MemoryStream();

        public Interpreter()
        {
            InitializeComponent();

            // Instantiate the writer
            //_writer = new TextBoxStreamWriter(txtConsole);
            // Redirect the out Console stream
            //Console.SetOut(_writer);
            //Console.WriteLine("Now redirecting output to the text box");
        }

        private void TextBox_TextChanged_1(object sender, TextChangedEventArgs e)
        {

        }

        private void OnExecution(object sender, RoutedEventArgs e)
        {
            m_ms = new MemoryStream();
            m_engine.Runtime.IO.SetOutput(m_ms, new StreamWriter(m_ms));
            string printable = "Printable";

            m_scope = m_engine.CreateScope();
            m_scope.SetVariable("result", printable);
            string input = InterpreterInput.Text;

            string code = input;
            /*"def HelloWorld():\n" +
                        "\t" + "return 'Hello World'\n" + "print(HelloWorld())";*/
            ScriptSource source = m_engine.CreateScriptSourceFromString(code, SourceCodeKind.Statements);
            object result = source.Execute(m_scope);

            string str = ReadFromStream(m_ms);
            txtConsole.Text = str;
            m_ms.Close(); 
        }

        private void txtConsole_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private string ReadFromStream(MemoryStream ms)
        {
            int length = (int)ms.Length;
            Byte[] bytes = new Byte[length];

            ms.Seek(0, SeekOrigin.Begin);
            ms.Read(bytes, 0, (int)ms.Length);

            return Encoding.GetEncoding("utf-8").GetString(bytes, 0, (int)ms.Length);
        }
    }
}
