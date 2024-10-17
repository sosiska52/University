using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace omis_4
{
    public partial class SearchResult : Form
    {
        public SearchResult(DataGridView data, string year)
        {
            InitializeComponent();
            this.data = data;
            this.neededYear = year;
        }
        private DataGridView data;
        private string neededYear;
        private void SearchResult_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < this.data.Rows.Count - 1; i++) 
            {
                DataGridViewRow row = this.data.Rows[i];
                string year = row.Cells[0].Value.ToString(); 
                if (neededYear == year)
                {
                    string expenses = row.Cells[1].Value.ToString(); 
                    string income = row.Cells[2].Value.ToString(); 
                    richTextBox1.AppendText(year + "\t" + expenses + "\t" + income + "\n");
                }
            }
        }
    }
}
