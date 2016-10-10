using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AgoraClrLibrary;


namespace AgoraClrDemo
{
    public partial class Form1 : Form
    {
        private AgoraClr agora = new AgoraClr();
        private AgoraClrLibrary.onCameraReady cameraReadyEvent;

        public Form1()
        {
            InitializeComponent();
            log("initialize", agora.initialize(txtVendorkey.Text));
            agora.onCameraReady += new AgoraClrLibrary.onCameraReady(onCameraReady);
            agora.onJoinChannelSuccess += new AgoraClrLibrary.onJoinChannelSuccess(onJoinChannelSuccess);
            agora.onFirstRemoteVideoDecoded += new AgoraClrLibrary.onFirstRemoteVideoDecoded(onFirstRemoteVideoDecoded);
        }

        private void onFirstRemoteVideoDecoded(int uid, int width, int height, int elapsed)
        {
            log("remote video decoded in " + uid, elapsed);
            setupRemoteVideo(uid);
        }

        delegate void setupRemoteVideoDelegate(int uid);
        private void setupRemoteVideo(int uid)
        {
            if (remoteVideo.InvokeRequired)
            {
                setupRemoteVideoDelegate d = new setupRemoteVideoDelegate(setupRemoteVideo);
                this.Invoke(d, uid);
            } else
            {
                agora.setupRemoteVideo(remoteVideo.Handle, (int)RenderMode.RENDER_MODE_ADAPTIVE, uid);
            }
        }

        private void onCameraReady()
        {
            log("Camera Ready Event", 0);
        }

        private void onJoinChannelSuccess(String channel, int uid, int elapsed)
        {
            log("join channel success in " + channel + " by " + uid, elapsed);
        }

        delegate void LogDelegate(String operation, int result);

        private void log(String operation, int result)
        {
            if (txtResult.InvokeRequired)
            {
                LogDelegate d = new LogDelegate(log);
                this.Invoke(d, new object[] { operation, result });
            } else
            {
                txtResult.AppendText(String.Format("agora {0} result is {1}\n", operation, result));
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
           
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void txtResult_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnStartPreview_Click(object sender, EventArgs e)
        {
            log("setuplocalVideo", agora.setupLocalVideo(localVideo.Handle, (int)RenderMode.RENDER_MODE_ADAPTIVE, 0));
            log("enableVideo", agora.enableVideo());
            log("startPreview", agora.startPreview());
        }

        private void btnJoinChannel_Click(object sender, EventArgs e)
        {
            log("join channel", agora.joinChannel("", txtChannelName.Text, 0));
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            log(" convert -1 to unit result is " + Convert.ToUInt32(-1), 0);
        }
    }
}
