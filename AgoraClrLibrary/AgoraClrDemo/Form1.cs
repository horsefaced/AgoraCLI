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
        private AgoraClrRTM agoraRTM = new AgoraClrRTM();
        private AgoraClrLibrary.onCameraReady cameraReadyEvent;
        private System.Timers.Timer m_timer;
        private bool m_start;
        private bool m_pulling;

        public Form1()
        {
            InitializeComponent();
            log("initialize", agora.initialize(txtVendorkey.Text));
            //log("initialize rtm", agoraRTM.initialize(txtVendorkey.Text));
            agora.onCameraReady += onCameraReady;
            agora.onJoinChannelSuccess += onJoinChannelSuccess;
            agora.onFirstRemoteVideoDecoded += onFirstRemoteVideoDecoded;
            agora.onFirstLocalVideoFrame += onFirstLocalVideoFrame;
            agora.onCaptureVideoFrame += onCaptureVideoFrame;
            agora.onPreEncodeVideoFrame += onPreEncodeVideoFrame;

            /*AgoraClrRTMChannel channel = agoraRTM.createChannel("1234");
            channel.onMemberJoined += onMemberJoined;*/

        }

        private void onMemberJoined(ClrChannelMember member)
        {

        }

        bool onPreEncodeVideoFrame(ClrVideoFrame frame)
        {
            //log("onPreEncodeVideoFrame", (int)frame.type);
            return true;
        }

        private void onFirstLocalVideoFrame(int width, int height, int elapsed)
        {
            log("on first local video frame with " + width + "," + height + "," + elapsed, 0);
        }

        private bool onCaptureVideoFrame(AgoraClrLibrary.ClrVideoFrame frame)
        {
            return true;
        }

        private void onFirstRemoteVideoDecoded(uint uid, int width, int height, int elapsed)
        {
            log("remote video decoded in " + uid, elapsed);
            setupRemoteVideo(uid);
        }

        delegate void setupRemoteVideoDelegate(uint uid);
        private void setupRemoteVideo(uint uid)
        {
            if (remoteVideo.InvokeRequired)
            {
                setupRemoteVideoDelegate d = new setupRemoteVideoDelegate(setupRemoteVideo);
                this.Invoke(d, uid);
            } else
            {
                agora.setupRemoteVideo(remoteVideo.Handle, (int)EnumRenderModeType.RENDER_MODE_ADAPTIVE, uid);
            }
        }

        private void onCameraReady()
        {
            log("Camera Ready Event", 0);
        }

        private void onJoinChannelSuccess(String channel, uint uid, int elapsed)
        {
            log("join channel success in " + channel + " by " + uid, elapsed);
            m_start = true;
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
                txtResult.AppendText(String.Format("agora {0} result is {1}", operation, result));
                txtResult.AppendText(Environment.NewLine);
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
            log("setChannelProfile", agora.setChannelProfile(ChannelProfile.CHANNEL_PROFILE_LIVE_BROADCASTING));
            log("setClientRole", agora.setClientRole(ClientRoleType.CLIENT_ROLE_BROADCASTER));
            log("enableVideo", agora.enableVideo());
            log("setuplocalVideo", agora.setupLocalVideo(localVideo.Handle, (int)EnumRenderModeType.RENDER_MODE_ADAPTIVE, 0));
            log("setExternalAudioSink", agora.setExternalAudioSink(true, 44100, 1));
            log("startPreview", agora.startPreview());

            m_timer = new System.Timers.Timer(10);
            m_timer.Elapsed += pullAudioFrameTimer;
            m_timer.Enabled = true;
        }

        private void pullAudioFrameTimer(object sender, System.Timers.ElapsedEventArgs e)
        {
            if (!m_start) return;
            if (m_pulling) return;

            m_pulling = true;
            ClrAudioFrame frame = null;
            var result = agora.pullAudioFrame(out frame);
            m_pulling = false;
        }

        private void btnJoinChannel_Click(object sender, EventArgs e)
        {
            log("join channel", agora.joinChannel(txtToken.Text, txtChannelName.Text, null, 0));
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            //log(" convert -1 to unit result is " + Convert.ToUInt32(-1), 0);
            //log("start audio recording", agora.startAudioRecording("recording.mp4", AudioRecordingQualityType.AUDIO_RECORDING_QUALITY_HIGH));
            agora.release();
        }
    }
}
