using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace omis_4
{
    public partial class SearchTask : Form
    {
        public SearchTask(DataGridView data)
        {
            InitializeComponent();
            this.data = data;
        }
        private DataGridView data;
        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(textBox1.Text))
                MessageBox.Show("Empty");
            else
            {
                SearchResult searchResult = new SearchResult(data, textBox1.Text);
                searchResult.ShowDialog();
            }
        }
    }
}
