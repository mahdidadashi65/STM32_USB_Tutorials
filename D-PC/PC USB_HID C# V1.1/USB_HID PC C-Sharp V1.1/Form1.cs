using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using HIDInterface;
using System.Globalization;


namespace USB_HID_PC_C_Sharp_V1._1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        
        HIDDevice device;
        bool CloseDev = false;
        public void useSynchronousOperation()
        {
            //Get the details of all connected USB HID devices
            HIDDevice.interfaceDetails[] devices = HIDDevice.getConnectedDevices();

            //Arbitrarily select one of the devices which we found in the previous step
            //record the details of this device to be used in the class constructor
            int selectedDeviceIndex = 4;
            ushort VID = devices[selectedDeviceIndex].VID;
            ushort PID = devices[selectedDeviceIndex].PID;
            int SN = devices[selectedDeviceIndex].serialNumber;
            string devicePath = devices[selectedDeviceIndex].devicePath;

            //create a handle to the device by calling the constructor of the HID class
            //This can be done using either the VID/PID/Serialnumber, or the device path (string) 
            //all of these details are available from the HIDDevice.interfaceDetails[] struct array created above
            //The "false" boolean in the constructor tells the class we only want synchronous operation
            device = new HIDDevice(devicePath, false);
            //OR, the normal usage when you know the VID and PID of the device
            //HIDDevice device = new HIDDevice(VID, PID, (ushort)SN, false);

            //Write some data to the device (the write method throws an exception if the data is longer than the report length
            //specified by the device, this length can be found in the HIDDevice.interfaceDetails struct)
            byte[] writeData = { 0x10, 0x11, 0x02, 0x03, 0x04 };
            device.write(writeData);    //Its that easy!!

            //Read some data synchronously from the device. This method blocks the calling thread until the data
            //is returned. This takes 1-20ms for most HID devices
            byte[] readData = device.read();    //again, that easy!

            //close the device to release all handles etc
           // device.close();
        }

        public bool startAsyncOperation(ushort MyDevVID,ushort MyDevPID)
        {
            //Get the details of all connected USB HID devices
           HIDDevice.interfaceDetails[] devices = HIDDevice.getConnectedDevices();
            
        
            //Arbitrarily select one of the devices which we found in the previous step
            //record the details of this device to be used in the class constructor
            int selectedDeviceIndex = -1;
            for (int i = 0; i < devices.Length; i++)
            {
                if ((devices[i].VID==MyDevVID) &&(devices[i].PID==MyDevPID))
                {
                    selectedDeviceIndex = i;
                } 
            }

            if (selectedDeviceIndex == -1) return false;

            ushort VID = devices[selectedDeviceIndex].VID;
            ushort PID = devices[selectedDeviceIndex].PID;
            int SN = devices[selectedDeviceIndex].serialNumber;
            string devicePath = devices[selectedDeviceIndex].devicePath;

            //create a handle to the device by calling the constructor of the HID class
            //This can be done using either the VID/PID/Serialnumber, or the device path (string) 
            //all of these details are available from the HIDDevice.interfaceDetails[] struct array created above
            //The "true" boolean in the constructor tells the class we want asynchronous operation this time
             device = new HIDDevice(devicePath, true);
            
            //OR, the normal usage when you know the VID and PID of the device
            //HIDDevice device = new HIDDevice(VID, PID, (ushort)SN, true);

            //next create the event handler for the incoming reports
            device.dataReceived += new HIDDevice.dataReceivedEvent(device_dataReceived);

            //Write some data to the device (the write method throws an exception if the data is longer than the report length
            //specified by the device, this length can be found in the HIDDevice.interfaceDetails struct)
            //The write method is identical to the synchronous mode of operation
            byte[] writeData = new byte[64];
            for (int i = 0; i < writeData.Length; i++)
            {
                writeData[i] = Convert.ToByte(i + 100);
            }

            device.write(writeData);    //Its that easy!!

            //Send your program off to do other stuff here, wait for UI events etc
            //When a report occurs, the device_dataReceived(byte[] message) method will be called
            //System.Threading.Thread.Sleep(100);

            //close the device to release all handles etc
            //device.close();
            return true;
        }



        public void SetTextBox(string value)
        {
            if (InvokeRequired)
            {
                this.Invoke(new Action<string>(SetTextBox), new object[] { value });
                return;
            }
            txtResp.Text = value;
        }

        public void AppendTextBox(string value)
        {
            if (InvokeRequired)
            {
                this.Invoke(new Action<string>(AppendTextBox), new object[] { value });
                return;
            }
            txtResp.Text += value;
        }

        public void UpdateU8TextVal(string value)
        {
            if (InvokeRequired)
            {
                this.Invoke(new Action<string>(UpdateU8TextVal), new object[] { value });
                return;
            }
            txtU8Val.Text += value;
        }



        void Proccess_HID_Data_MCU_to_PC(byte[] data)
        {
            if(data[0]==0xAA)
            {
                if (data[1] == 0)
                {
                    ckSW1.Checked = false;
                }
                else
                {
                    ckSW1.Checked = true;
                }

                if (data[2] == 0)
                {
                    ckSW2.Checked = false;
                }
                else
                {
                    ckSW2.Checked = true;
                }

                if (data[3] == 0)
                {
                    ckSW3.Checked = false;
                }
                else
                {
                    ckSW3.Checked = true;
                }

                if (data[4] == 0)
                {
                    ckSW4.Checked = false;
                }
                else
                {
                    ckSW4.Checked = true;
                }


                txtU8Val.Text = data[5].ToString();

                Int32 My32bitData = data[6] + (data[7] << 8) + (data[8] << 16) + (data[9] << 24);
                txtU32Val.Text = My32bitData.ToString();

                float Myfloat=System.BitConverter.ToSingle(data,10);
                txtfloatVal.Text = Myfloat.ToString();


            }
        }

        //Whenever a report comes in, this method will be called and the data will be available! Like magic...
        void device_dataReceived(byte[] message)
        {

            byte[] mydata = new byte[64];

            for (int i = 0; i < 64;i++ )
            {
                mydata[i] = message[i + 1];
            }

            if (this.InvokeRequired)
            {

                this.Invoke((Action)(() => { Proccess_HID_Data_MCU_to_PC(mydata); }));

            }

            else
            {
                Proccess_HID_Data_MCU_to_PC(mydata);
            }

                
            


                string NewMsg = "";

                SetTextBox("");

                NewMsg = "";
                int wrap = 0;
                for (int i = 0; i < message.Length; i++)
                {
                    NewMsg += message[i].ToString("X2") + " ";
                    wrap++;
                    if (wrap > 15)
                    {
                        wrap = 0;
                        NewMsg += "\r\n";
                    }
                }
                NewMsg += "\r\n";
                AppendTextBox(NewMsg);
            if(CloseDev)
            {
                if (device.deviceConnected)
                {
                    device.close();
                    
                }
            }
            
        }
        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (startAsyncOperation(0x0483, 0x5750))
            {
                //btnClose.Enabled = true;
                btnOpen.Enabled = false;
            }
            else
            {
                MessageBox.Show("Device Not Found");
            }
            
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            
            CloseDev = true;
            //btnClose.Enabled = false;
            btnOpen.Enabled = true;
        }

        //private void btnClose_Click(object sender, EventArgs e)
        //{

        //    CloseDev = true;
        //    btnClose.Enabled = false;
        //    btnOpen.Enabled = true;
        //}


        private void Form1_Load(object sender, EventArgs e)
        {

        }


        void Send_HID_Data_PC_to_MCU()
        {
            byte[] writeData = new byte[64];
            //for (int i = 0; i < writeData.Length; i++)
            //{
            //    writeData[i] = Convert.ToByte(i + 100);
            //}

            writeData[0] = 0x55;

            if (ckReceiveData.Checked)
            {
                writeData[1] = 1;
            }
            else
            {
                writeData[1] = 0;
            }

            if (ckLED1.Checked)
            {
                writeData[2] = 1;
            }
            else
            {
                writeData[2] = 0;
            }

            if (ckLED2.Checked)
            {
                writeData[3] = 1;
            }
            else
            {
                writeData[3] = 0;
            }


            if (ckLED3.Checked)
            {
                writeData[4] = 1;
            }
            else
            {
                writeData[4] = 0;
            }

            writeData[5] = Convert.ToByte(tBarServo.Value);

            int MyINTVal=0;

            if(txtU32ValOut.Text!="")
            {
                 MyINTVal = Convert.ToInt32(txtU32ValOut.Text);
            }

            

            writeData[6] = (byte)(MyINTVal         & 0xff);
            writeData[7] = (byte)((MyINTVal >>  8) & 0xff);
            writeData[8] = (byte)((MyINTVal >> 16) & 0xff);
            writeData[9] = (byte)((MyINTVal >> 24) & 0xff);

            float MyFloatVal = 0;
            if (txtfloatValOut.Text != "")
            {
                MyFloatVal = float.Parse(txtfloatValOut.Text, CultureInfo.InvariantCulture.NumberFormat);
            }
            byte[] FloatBytes = BitConverter.GetBytes(MyFloatVal);
            writeData[10] = FloatBytes[0];
            writeData[11] = FloatBytes[1];
            writeData[12] = FloatBytes[2];
            writeData[13] = FloatBytes[3];

            device.write(writeData);
        }
        private void ckLED1_CheckedChanged(object sender, EventArgs e)
        {
            Send_HID_Data_PC_to_MCU();
        }

        private void ckReceiveData_CheckedChanged(object sender, EventArgs e)
        {
            Send_HID_Data_PC_to_MCU();
        }

        private void ckLED2_CheckedChanged(object sender, EventArgs e)
        {
            Send_HID_Data_PC_to_MCU();
        }

        private void ckLED3_CheckedChanged(object sender, EventArgs e)
        {
            Send_HID_Data_PC_to_MCU();
        }

        private void tBarServo_Scroll(object sender, EventArgs e)
        {
            Send_HID_Data_PC_to_MCU();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Send_HID_Data_PC_to_MCU();
        }



    }
}
