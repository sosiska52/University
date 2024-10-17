using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace omis_4
{
    public partial class SignIn : Form
    {
        public SignIn()
        {
            InitializeComponent();
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
        }

        private const string loginPath = "D:\\GitHubRepo\\University\\3 year\\OMIS\\src\\omis_4\\omis_4\\logins.txt";
        private const string dataPath = "D:\\GitHubRepo\\University\\3 year\\OMIS\\src\\omis_4\\omis_4\\UsersData\\";

        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(textBox1.Text) || string.IsNullOrEmpty(textBox2.Text)) {
                MessageBox.Show("Empty");
            }
            else
            {
                int ind = findLogin(textBox1.Text);
                if(ind == -1)
                {
                    string newPair = textBox1.Text.Trim() + "\t" + textBox2.Text.Trim() + "\n";
                    File.AppendAllText(loginPath, newPair);

                    string path = dataPath + textBox1.Text + ".txt";
                    File.WriteAllText(path, ""); 
                    this.Close();
                }
                else
                {
                    MessageBox.Show("Login already exists");
                    textBox1.Clear();
                }
            }
        }

        private int findLogin(string newLogin)
        {
            int ind = 0;
            foreach (string line in File.ReadLines(loginPath))
            {
                string[] pair = line.Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
                if (pair[0] == newLogin)
                    return ind;
                ind++;
            }
            return -1;
        }
    }
}
