using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PCSerialController
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            string strPortName = txtPortName.Text;

            serialPort1.PortName = strPortName;
            serialPort1.Open();
        }

        private void btnReadKeys_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write("SW?\r\n");
            }
        }


        public void AppendTextBox(string value)
        {
            if (InvokeRequired)
            {
                this.Invoke(new Action<string>(AppendTextBox), new object[] { value });
                return;
            }
            txtResponse.Text += value;
        }


        public static void InvokeCheckBoxChecked(CheckBox checkbox, bool isChecked)
        {
            if (checkbox.InvokeRequired)
            {
                checkbox.Invoke(new MethodInvoker(delegate() { InvokeCheckBoxChecked(checkbox, isChecked); }));
            }
            else
            {
                checkbox.Checked = isChecked;
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string strNewData = serialPort1.ReadLine();
            AppendTextBox(strNewData);
            AppendTextBox("\r\n");
            if(strNewData.Contains("SW1:0"))
            {
                InvokeCheckBoxChecked(cBoxSW1, true);
            }
            if (strNewData.Contains("SW1:1"))
            {
                InvokeCheckBoxChecked(cBoxSW1, false);
            }

            if (strNewData.Contains("SW2:0"))
            {
                InvokeCheckBoxChecked(cBoxSW2, true);
            }
            if (strNewData.Contains("SW2:1"))
            {
                InvokeCheckBoxChecked(cBoxSW2, false);
            }


            if (strNewData.Contains("SW3:0"))
            {
                InvokeCheckBoxChecked(cBoxSW3, true);
            }
            if (strNewData.Contains("SW3:1"))
            {
                InvokeCheckBoxChecked(cBoxSW3, false);
            }

            if (strNewData.Contains("SW4:0"))
            {
                InvokeCheckBoxChecked(cBoxSW4, true);
            }
            if (strNewData.Contains("SW4:1"))
            {
                InvokeCheckBoxChecked(cBoxSW4, false);
            }


        }

        private void cBoxLED1_CheckedChanged(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (cBoxLED1.Checked)
                {
                    serialPort1.Write("LED1:1\r\n");
                }
                else
                {
                    serialPort1.Write("LED1:0\r\n");
                }
            }
        }

        private void cBoxLED2_CheckedChanged(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (cBoxLED2.Checked)
                {
                    serialPort1.Write("LED2:1\r\n");
                }
                else
                {
                    serialPort1.Write("LED2:0\r\n");
                }
            }
        }

        private void cBoxLED3_CheckedChanged(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (cBoxLED3.Checked)
                {
                    serialPort1.Write("LED3:1\r\n");
                }
                else
                {
                    serialPort1.Write("LED3:0\r\n");
                }
            }
        }

        private void cBoxLED4_CheckedChanged(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (cBoxLED4.Checked)
                {
                    serialPort1.Write("LED4:1\r\n");
                }
                else
                {
                    serialPort1.Write("LED4:0\r\n");
                }
            }
        }

        private void txtResponse_DoubleClick(object sender, EventArgs e)
        {
            txtResponse.Text = "";
        }
    }
}
