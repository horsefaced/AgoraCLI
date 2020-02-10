#pragma once

namespace AgoraClrLibrary {

	public
		enum class VideoProfile
	{										   // res       fps  kbps
		VIDEO_PROFILE_LANDSCAPE_120P = 0,	  // 160x120   15
		VIDEO_PROFILE_LANDSCAPE_120P_3 = 2,	// 120x120   15
		VIDEO_PROFILE_LANDSCAPE_180P = 10,	 // 320x180   15
		VIDEO_PROFILE_LANDSCAPE_180P_3 = 12,   // 180x180   15
		VIDEO_PROFILE_LANDSCAPE_180P_4 = 13,   // 240x180   15
		VIDEO_PROFILE_LANDSCAPE_240P = 20,	 // 320x240   15
		VIDEO_PROFILE_LANDSCAPE_240P_3 = 22,   // 240x240   15
		VIDEO_PROFILE_LANDSCAPE_240P_4 = 23,   // 424x240   15
		VIDEO_PROFILE_LANDSCAPE_360P = 30,	 // 640x360   15
		VIDEO_PROFILE_LANDSCAPE_360P_3 = 32,   // 360x360   15
		VIDEO_PROFILE_LANDSCAPE_360P_4 = 33,   // 640x360   30
		VIDEO_PROFILE_LANDSCAPE_360P_6 = 35,   // 360x360   30
		VIDEO_PROFILE_LANDSCAPE_360P_7 = 36,   // 480x360   15
		VIDEO_PROFILE_LANDSCAPE_360P_8 = 37,   // 480x360   30
		VIDEO_PROFILE_LANDSCAPE_360P_9 = 38,   // 640x360   15
		VIDEO_PROFILE_LANDSCAPE_360P_10 = 39,  // 640x360   24
		VIDEO_PROFILE_LANDSCAPE_360P_11 = 100, // 640x360   24
		VIDEO_PROFILE_LANDSCAPE_480P = 40,	 // 640x480   15
		VIDEO_PROFILE_LANDSCAPE_480P_3 = 42,   // 480x480   15
		VIDEO_PROFILE_LANDSCAPE_480P_4 = 43,   // 640x480   30
		VIDEO_PROFILE_LANDSCAPE_480P_6 = 45,   // 480x480   30
		VIDEO_PROFILE_LANDSCAPE_480P_8 = 47,   // 848x480   15
		VIDEO_PROFILE_LANDSCAPE_480P_9 = 48,   // 848x480   30
		VIDEO_PROFILE_LANDSCAPE_480P_10 = 49,  // 640x480   10
		VIDEO_PROFILE_LANDSCAPE_720P = 50,	 // 1280x720  15
		VIDEO_PROFILE_LANDSCAPE_720P_3 = 52,   // 1280x720  30
		VIDEO_PROFILE_LANDSCAPE_720P_5 = 54,   // 960x720   15
		VIDEO_PROFILE_LANDSCAPE_720P_6 = 55,   // 960x720   30
		VIDEO_PROFILE_LANDSCAPE_1080P = 60,	// 1920x1080 15
		VIDEO_PROFILE_LANDSCAPE_1080P_3 = 62,  // 1920x1080 30
		VIDEO_PROFILE_LANDSCAPE_1080P_5 = 64,  // 1920x1080 60
		VIDEO_PROFILE_LANDSCAPE_1440P = 66,	// 2560x1440 30
		VIDEO_PROFILE_LANDSCAPE_1440P_2 = 67,  // 2560x1440 60
		VIDEO_PROFILE_LANDSCAPE_4K = 70,	   // 3840x2160 30
		VIDEO_PROFILE_LANDSCAPE_4K_3 = 72,	 // 3840x2160 60

		VIDEO_PROFILE_PORTRAIT_120P = 1000,	// 120x160   15
		VIDEO_PROFILE_PORTRAIT_120P_3 = 1002,  // 120x120   15
		VIDEO_PROFILE_PORTRAIT_180P = 1010,	// 180x320   15
		VIDEO_PROFILE_PORTRAIT_180P_3 = 1012,  // 180x180   15
		VIDEO_PROFILE_PORTRAIT_180P_4 = 1013,  // 180x240   15
		VIDEO_PROFILE_PORTRAIT_240P = 1020,	// 240x320   15
		VIDEO_PROFILE_PORTRAIT_240P_3 = 1022,  // 240x240   15
		VIDEO_PROFILE_PORTRAIT_240P_4 = 1023,  // 240x424   15
		VIDEO_PROFILE_PORTRAIT_360P = 1030,	// 360x640   15
		VIDEO_PROFILE_PORTRAIT_360P_3 = 1032,  // 360x360   15
		VIDEO_PROFILE_PORTRAIT_360P_4 = 1033,  // 360x640   30
		VIDEO_PROFILE_PORTRAIT_360P_6 = 1035,  // 360x360   30
		VIDEO_PROFILE_PORTRAIT_360P_7 = 1036,  // 360x480   15
		VIDEO_PROFILE_PORTRAIT_360P_8 = 1037,  // 360x480   30
		VIDEO_PROFILE_PORTRAIT_360P_9 = 1038,  // 360x640   15
		VIDEO_PROFILE_PORTRAIT_360P_10 = 1039, // 360x640   24
		VIDEO_PROFILE_PORTRAIT_360P_11 = 1100, // 360x640   24
		VIDEO_PROFILE_PORTRAIT_480P = 1040,	// 480x640   15
		VIDEO_PROFILE_PORTRAIT_480P_3 = 1042,  // 480x480   15
		VIDEO_PROFILE_PORTRAIT_480P_4 = 1043,  // 480x640   30
		VIDEO_PROFILE_PORTRAIT_480P_6 = 1045,  // 480x480   30
		VIDEO_PROFILE_PORTRAIT_480P_8 = 1047,  // 480x848   15
		VIDEO_PROFILE_PORTRAIT_480P_9 = 1048,  // 480x848   30
		VIDEO_PROFILE_PORTRAIT_480P_10 = 1049, // 480x640   10
		VIDEO_PROFILE_PORTRAIT_720P = 1050,	// 720x1280  15
		VIDEO_PROFILE_PORTRAIT_720P_3 = 1052,  // 720x1280  30
		VIDEO_PROFILE_PORTRAIT_720P_5 = 1054,  // 720x960   15
		VIDEO_PROFILE_PORTRAIT_720P_6 = 1055,  // 720x960   30
		VIDEO_PROFILE_PORTRAIT_1080P = 1060,   // 1080x1920 15
		VIDEO_PROFILE_PORTRAIT_1080P_3 = 1062, // 1080x1920 30
		VIDEO_PROFILE_PORTRAIT_1080P_5 = 1064, // 1080x1920 60
		VIDEO_PROFILE_PORTRAIT_1440P = 1066,   // 1440x2560 30
		VIDEO_PROFILE_PORTRAIT_1440P_2 = 1067, // 1440x2560 60
		VIDEO_PROFILE_PORTRAIT_4K = 1070,	  // 2160x3840 30
		VIDEO_PROFILE_PORTRAIT_4K_3 = 1072,	// 2160x3840 60
		VIDEO_PROFILE_DEFAULT = VIDEO_PROFILE_LANDSCAPE_360P,
	};

	public
		enum class ChannelProfile
	{
		CHANNEL_PROFILE_COMMUNICATION = 0,
		CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
		CHANNEL_PROFILE_GAME = 2,
	};

	public
		enum class ClientRoleType
	{
		CLIENT_ROLE_BROADCASTER = 1,
		CLIENT_ROLE_AUDIENCE = 2,
	};

	public
		enum class RenderMode
	{
		RENDER_MODE_HIDDEN = 1,
		RENDER_MODE_FIT = 2,
		RENDER_MODE_ADAPTIVE = 3,
	};

	public
		enum class UserOfflineType
	{
		USER_OFFLINE_QUIT = 0,
		USER_OFFLINE_DROPPED = 1,
		USER_OFFLINE_BECOME_AUDIENCE = 2,
	};

	public
		enum class RawAudioFrameOPModeType
	{
		RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
		RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = 1,
		RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
	};
	public
		enum class AudioRecordingQualityType
	{
		AUDIO_RECORDING_QUALITY_LOW = 0,
		AUDIO_RECORDING_QUALITY_MEDIUM = 1,
		AUDIO_RECORDING_QUALITY_HIGH = 2,
	};

	public enum class QualityAdaptIndication
	{
		/** The quality of the local video stays the same. */
		ADAPT_NONE = 0,
		/** The quality improves because the network bandwidth increases. */
		ADAPT_UP_BANDWIDTH = 1,
		/** The quality worsens because the network bandwidth decreases. */
		ADAPT_DOWN_BANDWIDTH = 2,
	};

	public enum class VideoCodecType
	{
		/** Standard VP8 */
		VIDEO_CODEC_VP8 = 1,
		/** Standard H264 */
		VIDEO_CODEC_H264 = 2,
		/** Enhanced VP8 */
		VIDEO_CODEC_EVP = 3,
		/** Enhanced H264 */
		VIDEO_CODEC_E264 = 4,
	};

	public
		enum class RemoteVideoStreamType
	{
		REMOTE_VIDEO_STREAM_HIGH = 0,
		REMOTE_VIDEO_STREAM_LOW = 1,
	};

	public
		enum class MediaDeviceType
	{
		UNKNOWN_AUDIO_DEVICE = -1,
		AUDIO_PLAYOUT_DEVICE = 0,
		AUDIO_RECORDING_DEVICE = 1,
		VIDEO_RENDER_DEVICE = 2,
		VIDEO_CAPTURE_DEVICE = 3,
		AUDIO_APPLICATION_PLAYOUT_DEVICE = 4,
	};

	public
		enum class EnumAudioFrameType
	{
		FRAME_TYPE_PCM16 = 0, //PCM 16bit little endian
	};

	public
		enum class EnumVideoFrameType
	{
		FRAME_TYPE_YUV420 = 0, //YUV 420 format
	};

	public
		enum class RtmpStreamLifeCycleType
	{
		RTMP_STREAM_LIFE_CYCLE_BIND2CHANNEL = 1,
		RTMP_STREAM_LIFE_CYCLE_BIND2OWNER = 2,
	};

	public enum class EnumVideoContentHint {
		CONTENT_HINT_NONE,
		CONTENT_HINT_MOTION,
		CONTENT_HINT_DETAILS,
	};

	public
		enum class VideoCodecProfileType
	{
		VIDEO_CODEC_PROFILE_BASELINE = 66,
		VIDEO_CODEC_PROFILE_MAIN = 77,
		VIDEO_CODEC_PROFILE_HIGH = 100,
	};

	public
		enum class AudioSampleRateType
	{
		AUDIO_SAMPLE_RATE_32000 = 32000,
		AUDIO_SAMPLE_RATE_44100 = 44100,
		AUDIO_SAMPLE_RATE_48000 = 48000,
	};

	public enum class AudioCodecProfileType
	{
		AUDIO_CODEC_PROFILE_LC_AAC = 0,
		AUDIO_CODEC_PROFILE_HE_AAC = 1,
	};

	public
		enum class AudioProfileType // sample rate, bit rate, mono/stereo, speech/music codec
	{
		AUDIO_PROFILE_DEFAULT = 0,					 // use default settings
		AUDIO_PROFILE_SPEECH_STANDARD = 1,			 // 32Khz, 18kbps, mono, speech
		AUDIO_PROFILE_MUSIC_STANDARD = 2,			 // 48Khz, 50kbps, mono, music
		AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3,	 // 48Khz, 50kbps, stereo, music
		AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4,		 // 48Khz, 128kbps, mono, music
		AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5, // 48Khz, 128kbps, stereo, music
		AUDIO_PROFILE_IOT = 6,
		AUDIO_PROFILE_NUM = 7,
	};

	public
		enum class AudioScenarioType // set a suitable scenario for your app type
	{
		AUDIO_SCENARIO_DEFAULT = 0,
		AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT = 1,
		AUDIO_SCENARIO_EDUCATION = 2,
		AUDIO_SCENARIO_GAME_STREAMING = 3,
		AUDIO_SCENARIO_SHOWROOM = 4,
		AUDIO_SCENARIO_CHATROOM_GAMING = 5,
		AUDIO_SCENARIO_IOT = 6,
		AUDIO_SCENARIO_NUM = 7,
	};

	public
		enum class AudioEqualizationBandFrequency
	{
		AUDIO_EQUALIZATION_BAND_31 = 0,
		AUDIO_EQUALIZATION_BAND_62 = 1,
		AUDIO_EQUALIZATION_BAND_125 = 2,
		AUDIO_EQUALIZATION_BAND_250 = 3,
		AUDIO_EQUALIZATION_BAND_500 = 4,
		AUDIO_EQUALIZATION_BAND_1K = 5,
		AUDIO_EQUALIZATION_BAND_2K = 6,
		AUDIO_EQUALIZATION_BAND_4K = 7,
		AUDIO_EQUALIZATION_BAND_8K = 8,
		AUDIO_EQUALIZATION_BAND_16K = 9,
	};

	public
		enum class AudioReverbType
	{
		AUDIO_REVERB_DRY_LEVEL = 0, // (dB, [-20,10]), the level of the dry signal
		AUDIO_REVERB_WET_LEVEL = 1, // (dB, [-20,10]), the level of the early reflection signal (wet signal)
		AUDIO_REVERB_ROOM_SIZE = 2, // ([0, 100]), the room size of the reflection
		AUDIO_REVERB_WET_DELAY = 3, // (ms, [0, 200]), the length of the initial delay of the wet signal in ms
		AUDIO_REVERB_STRENGTH = 4,  // ([0, 100]), the strength of the late reverberation
	};

	public
		enum class VideoMirrorModeType
	{
		VIDEO_MIRROR_MODE_AUTO = 0,		//determined by SDK
		VIDEO_MIRROR_MODE_ENABLED = 1,  //enabled mirror
		VIDEO_MIRROR_MODE_DISABLED = 2, //disable mirror
	};

	public
		enum class ConnectionStateType
	{
		CONNECTION_STATE_DISCONNECTED = 1,
		CONNECTION_STATE_CONNECTING = 2,
		CONNECTION_STATE_CONNECTED = 3,
		CONNECTION_STATE_RECONNECTING = 4,
		CONNECTION_STATE_FAILED = 5,
	};

	public
		enum class ConnectionChangedReasonType
	{
		/** 0: The SDK is connecting to Agora's edge server. */
		CONNECTION_CHANGED_CONNECTING = 0,
		/** 1: The SDK has joined the channel successfully. */
		CONNECTION_CHANGED_JOIN_SUCCESS = 1,
		/** 2: The connection between the SDK and Agora's edge server is interrupted. */
		CONNECTION_CHANGED_INTERRUPTED = 2,
		/** 3: The connection between the SDK and Agora's edge server is banned by Agora's edge server. */
		CONNECTION_CHANGED_BANNED_BY_SERVER = 3,
		/** 4: The SDK fails to join the channel for more than 20 minutes and stops reconnecting to the channel. */
		CONNECTION_CHANGED_JOIN_FAILED = 4,
		/** 5: The SDK has left the channel. */
		CONNECTION_CHANGED_LEAVE_CHANNEL = 5,
		/** 6: The connection failed since Appid is not valid. */
		CONNECTION_CHANGED_INVALID_APP_ID = 6,
		/** 7: The connection failed since channel name is not valid. */
		CONNECTION_CHANGED_INVALID_CHANNEL_NAME = 7,
		/** 8: The connection failed since token is not valid, possibly because:

	   - The App Certificate for the project is enabled in Dashboard, but you do not use Token when joining the channel. If you enable the App Certificate, you must use a token to join the channel.
	   - The uid that you specify in the \ref agora::rtc::IRtcEngine::joinChannel "joinChannel" method is different from the uid that you pass for generating the token.
	   */
	   CONNECTION_CHANGED_INVALID_TOKEN = 8,
	   /** 9: The connection failed since token is expired. */
	   CONNECTION_CHANGED_TOKEN_EXPIRED = 9,
	   /** 10: The connection is rejected by server. */
	   CONNECTION_CHANGED_REJECTED_BY_SERVER = 10,
	   /** 11: The connection changed to reconnecting since SDK has set a proxy server. */
	   CONNECTION_CHANGED_SETTING_PROXY_SERVER = 11,
	   /** 12: When SDK is in connection failed, the renew token operation will make it connecting. */
	   CONNECTION_CHANGED_RENEW_TOKEN = 12,
	   /** 13: The IP Address of SDK client has changed. i.e., Network type or IP/Port changed by network operator might change client IP address. */
	   CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED = 13,
	   /** 14: Timeout for the keep-alive of the connection between the SDK and Agora's edge server. The connection state changes to CONNECTION_STATE_RECONNECTING(4). */
	   CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT = 14,
	};

	public
		enum class FrameRate
	{
		FRAME_RATE_FPS_1 = 1,
		FRAME_RATE_FPS_7 = 7,
		FRAME_RATE_FPS_10 = 10,
		FRAME_RATE_FPS_15 = 15,
		FRAME_RATE_FPS_24 = 24,
		FRAME_RATE_FPS_30 = 30,
		FRAME_RATE_FPS_60 = 60,
	};

	public
		enum class OrientationMode
	{
		ORIENTATION_MODE_ADAPTIVE = 0,
		ORIENTATION_MODE_FIXED_LANDSCAPE = 1,
		ORIENTATION_MODE_FIXED_PORTRAIT = 2,
	};

	public
		enum class DegradationPreference
	{
		/** 0: (Default) Degrade the frame rate in order to maintain the video quality. */
		MAINTAIN_QUALITY = 0,
		/** 1: Degrade the video quality in order to maintain the frame rate. */
		MAINTAIN_FRAMERATE = 1,
		/** 2: (For future use) Maintain a balance between the frame rate and video quality. */
		MAINTAIN_BALANCED = 2,
	};

	public
		enum class VideoBufferType
	{
		/** 1: The video buffer in the format of raw data.
			 */
		VIDEO_BUFFER_RAW_DATA = 1,
	};

	/** The video pixel format.
		 */
	public
		enum class VideoPixelFormate
	{
		/** 0: The video pixel format is unknown.
			 */
		VIDEO_PIXEL_UNKNOWN = 0,
		/** 1: The video pixel format is I420.
			 */
			 VIDEO_PIXEL_I420 = 1,
			 /** 2: The video pixel format is BGRA.
				  */
				  VIDEO_PIXEL_BGRA = 2,
				  /** 8: The video pixel format is NV12.
					   */
					   VIDEO_PIXEL_NV12 = 8,
	};

	public
		enum class StreamFallbackOptions
	{
		STREAM_FALLBACK_OPTION_DISABLED = 0,
		STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
		STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
	};

	public
		enum class RemoteVideoState
	{
		REMOTE_VIDEO_STATE_STOPPED = 0,
		REMOTE_VIDEO_STATE_STARTING = 1,
		REMOTE_VIDEO_STATE_DECODING = 2,
		REMOTE_VIDEO_STATE_FROZEN = 3,
		REMOTE_VIDEO_STATE_FAILED = 4
	};

	public enum class RemoteVideoStateReason
	{
		REMOTE_VIDEO_STATE_REASON_INTERNAL = 0,
		REMOTE_VIDEO_STATE_REASON_NETWORK_CONGESTION = 1,
		REMOTE_VIDEO_STATE_REASON_NETWORK_RECOVERY = 2,
		REMOTE_VIDEO_STATE_REASON_LOCAL_MUTED = 3,
		REMOTE_VIDEO_STATE_REASON_LOCAL_UNMUTED = 4,
		REMOTE_VIDEO_STATE_REASON_REMOTE_MUTED = 5,
		REMOTE_VIDEO_STATE_REASON_REMOTE_UNMUTED = 6,
		REMOTE_VIDEO_STATE_REASON_REMOTE_OFFLINE = 7,
		REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK = 8,
		REMOTE_VIDEO_STATE_REASON_AUDIO_FALLBACK_RECOVERY = 9

	};

	public
		enum class NetworkType
	{
		/** -1: The network type is unknown. */
		NETWORK_TYPE_UNKNOWN = -1,
		/** 0: The SDK disconnects from the network. */
		NETWORK_TYPE_DISCONNECTED = 0,
		/** 1: The network type is LAN. */
		NETWORK_TYPE_LAN = 1,
		/** 2: The network type is Wi-Fi(including hotspots). */
		NETWORK_TYPE_WIFI = 2,
		/** 3: The network type is mobile 2G. */
		NETWORK_TYPE_MOBILE_2G = 3,
		/** 4: The network type is mobile 3G. */
		NETWORK_TYPE_MOBILE_3G = 4,
		/** 5: The network type is mobile 4G. */
		NETWORK_TYPE_MOBILE_4G = 5,
	};

	public
		enum class LocalAudioStreamState
	{
		LOCAL_AUDIO_STREAM_STATE_STOPPED = 0,
		LOCAL_AUDIO_STREAM_STATE_RECORDING = 1,
		LOCAL_AUDIO_STREAM_STATE_ENCODING = 2,
		LOCAL_AUDIO_STREAM_STATE_FAILED = 3
	};

	public
		enum class LocalAudioStreamError
	{
		LOCAL_AUDIO_STREAM_ERROR_OK = 0,
		LOCAL_AUDIO_STREAM_ERROR_FAILURE = 1,
		LOCAL_AUDIO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
		LOCAL_AUDIO_STREAM_ERROR_DEVICE_BUSY = 3,
		LOCAL_AUDIO_STREAM_ERROR_RECORD_FAILURE = 4,
		LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 5
	};

	public
		enum class LocalVideoStreamState
	{
		/** Initial state */
		LOCAL_VIDEO_STREAM_STATE_STOPPED = 0,
		/** The capturer starts successfully. */
		LOCAL_VIDEO_STREAM_STATE_CAPTURING = 1,
		/** The first video frame is successfully encoded. */
		LOCAL_VIDEO_STREAM_STATE_ENCODING = 2,
		/** The local video fails to start. */
		LOCAL_VIDEO_STREAM_STATE_FAILED = 3
	};

	public
		enum class LocalVideoStreamError
	{
		/** The local video is normal. */
		LOCAL_VIDEO_STREAM_ERROR_OK = 0,
		/** No specified reason for the local video failure. */
		LOCAL_VIDEO_STREAM_ERROR_FAILURE = 1,
		/** No permission to use the local video device. */
		LOCAL_VIDEO_STREAM_ERROR_DEVICE_NO_PERMISSION = 2,
		/** The local video capturer is in use. */
		LOCAL_VIDEO_STREAM_ERROR_DEVICE_BUSY = 3,
		/** The local video capture fails. Check whether the capturer is working properly. */
		LOCAL_VIDEO_STREAM_ERROR_CAPTURE_FAILURE = 4,
		/** The local video encoding fails. */
		LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5
	};

	public enum class RemoteAudioState
	{
		/** 0: The remote audio is in the default state, probably due to
	 * #REMOTE_AUDIO_REASON_LOCAL_MUTED (3),
	 * #REMOTE_AUDIO_REASON_REMOTE_MUTED (5), or
	 * #REMOTE_AUDIO_REASON_REMOTE_OFFLINE (7).
	 */
		REMOTE_AUDIO_STATE_STOPPED = 0,  // Default state, audio is started or remote user disabled/muted audio stream
		/** 1: The first remote audio packet is received.
		 */
		 REMOTE_AUDIO_STATE_STARTING = 1,  // The first audio frame packet has been received
		 /** 2: The remote audio stream is decoded and plays normally, probably
		  * due to #REMOTE_AUDIO_REASON_NETWORK_RECOVERY (2),
		  * #REMOTE_AUDIO_REASON_LOCAL_UNMUTED (4), or
		  * #REMOTE_AUDIO_REASON_REMOTE_UNMUTED (6).
		  */
		  REMOTE_AUDIO_STATE_DECODING = 2,  // The first remote audio frame has been decoded or fronzen state ends
		  /** 3: The remote audio is frozen, probably due to
		   * #REMOTE_AUDIO_REASON_NETWORK_CONGESTION (1).
		   */
		   REMOTE_AUDIO_STATE_FROZEN = 3,    // Remote audio is frozen, probably due to network issue
		   /** 4: The remote audio fails to start, probably due to
			* #REMOTE_AUDIO_REASON_INTERNAL (0).
			*/
			REMOTE_AUDIO_STATE_FAILED = 4,    // Remote audio play failed
	};

	public enum class RemoteAudioStateReason
	{
		/** 0: Internal reasons.
	 */
		REMOTE_AUDIO_REASON_INTERNAL = 0,
		/** 1: Network congestion.
		 */
		 REMOTE_AUDIO_REASON_NETWORK_CONGESTION = 1,
		 /** 2: Network recovery.
		  */
		  REMOTE_AUDIO_REASON_NETWORK_RECOVERY = 2,
		  /** 3: The local user stops receiving the remote audio stream or
		   * disables the audio module.
		   */
		   REMOTE_AUDIO_REASON_LOCAL_MUTED = 3,
		   /** 4: The local user resumes receiving the remote audio stream or
			* enables the audio module.
			*/
			REMOTE_AUDIO_REASON_LOCAL_UNMUTED = 4,
			/** 5: The remote user stops sending the audio stream or disables the
			 * audio module.
			 */
			 REMOTE_AUDIO_REASON_REMOTE_MUTED = 5,
			 /** 6: The remote user resumes sending the audio stream or enables the
			  * audio module.
			  */
			  REMOTE_AUDIO_REASON_REMOTE_UNMUTED = 6,
			  /** 7: The remote user leaves the channel.
			   */
			   REMOTE_AUDIO_REASON_REMOTE_OFFLINE = 7,
	};

	public enum class AudioMixingStateType {
		/** 710: The audio mixing file is playing.*/
		AUDIO_MIXING_STATE_PLAYING = 710,
		/** 711: The audio mixing file pauses playing.
		*/
		AUDIO_MIXING_STATE_PAUSED = 711,
		/** 713: The audio mixing file stops playing.
		*/
		AUDIO_MIXING_STATE_STOPPED = 713,
		/** 714: An exception occurs when playing the audio mixing file. See #AUDIO_MIXING_ERROR_TYPE.
		*/
		AUDIO_MIXING_STATE_FAILED = 714,
	};

	public enum class AudioMixingErrorType {
		/** 701: The SDK cannot open the audio mixing file.
*/
		AUDIO_MIXING_ERROR_CAN_NOT_OPEN = 701,
		/** 702: The SDK opens the audio mixing file too frequently.
		*/
		AUDIO_MIXING_ERROR_TOO_FREQUENT_CALL = 702,
		/** 703: The audio mixing file playback is interrupted.
		 */
		 AUDIO_MIXING_ERROR_INTERRUPTED_EOF = 703,
		 /** 0: The SDK can open the audio mixing file.
		 */
		 AUDIO_MIXING_ERROR_OK = 0,
	};

	public enum class VoiceChangerPreset {
		/** 0: The original voice (no local voice change).
*/
		VOICE_CHANGER_OFF = 0, //Turn off the voice changer
		/** 1: An old man's voice.
		*/
		VOICE_CHANGER_OLDMAN = 1,
		/** 2: A little boy's voice.
		*/
		VOICE_CHANGER_BABYBOY = 2,
		/** 3: A little girl's voice.
		*/
		VOICE_CHANGER_BABYGIRL = 3,
		/** 4: The voice of a growling bear.
		*/
		VOICE_CHANGER_ZHUBAJIE = 4,
		/** 5: Ethereal vocal effects.
		*/
		VOICE_CHANGER_ETHEREAL = 5,
		/** 6: Hulk's voice.
		*/
		VOICE_CHANGER_HULK = 6

	};

	public enum class EnumAudioReverbPreset {
		/** 0: The original voice (no local voice reverberation).
*/
		AUDIO_REVERB_OFF = 0, // Turn off audio reverb
		/** 1: Pop music.
		*/
		AUDIO_REVERB_POPULAR = 1,
		/** 2: R&B.
		*/
		AUDIO_REVERB_RNB = 2,
		/** 3: Rock music.
		*/
		AUDIO_REVERB_ROCK = 3,
		/** 4: Hip-hop.
		*/
		AUDIO_REVERB_HIPHOP = 4,
		/** 5: Pop concert.
		*/
		AUDIO_REVERB_VOCAL_CONCERT = 5,
		/** 6: Karaoke.
		*/
		AUDIO_REVERB_KTV = 6,
		/** 7: Recording studio.
		*/
		AUDIO_REVERB_STUDIO = 7

	};

	public enum class RtmpStreamPublishState {
		RTMP_STREAM_PUBLISH_STATE_IDLE = 0,
		RTMP_STREAM_PUBLISH_STATE_CONNECTING = 1,
		RTMP_STREAM_PUBLISH_STATE_RUNNING = 2,
		RTMP_STREAM_PUBLISH_STATE_RECOVERING = 3,
		RTMP_STREAM_PUBLISH_STATE_FAILURE = 4,
	};

	public enum class RtmpStreamPublishError {
		/** The RTMP streaming publishes successfully. */
		RTMP_STREAM_PUBLISH_ERROR_OK = 0,
		/** Invalid argument used. If, for example, you do not call the \ref IRtcEngine::setLiveTranscoding "setLiveTranscoding" method to configure the LiveTranscoding parameters before calling the addPublishStreamUrl method, the SDK returns this error. Check whether you set the parameters in the *setLiveTranscoding* method properly. */
		RTMP_STREAM_PUBLISH_ERROR_INVALID_ARGUMENT = 1,
		/** The RTMP streaming is encrypted and cannot be published. */
		RTMP_STREAM_PUBLISH_ERROR_ENCRYPTED_STREAM_NOT_ALLOWED = 2,
		/** Timeout for the RTMP streaming. Call the \ref IRtcEngine::addPublishStreamUrl "addPublishStreamUrl" method to publish the streaming again. */
		RTMP_STREAM_PUBLISH_ERROR_CONNECTION_TIMEOUT = 3,
		/** An error occurs in Agora's streaming server. Call the addPublishStreamUrl method to publish the streaming again. */
		RTMP_STREAM_PUBLISH_ERROR_INTERNAL_SERVER_ERROR = 4,
		/** An error occurs in the RTMP server. */
		RTMP_STREAM_PUBLISH_ERROR_RTMP_SERVER_ERROR = 5,
		/** The RTMP streaming publishes too frequently. */
		RTMP_STREAM_PUBLISH_ERROR_TOO_OFTEN = 6,
		/** The host publishes more than 10 URLs. Delete the unnecessary URLs before adding new ones. */
		RTMP_STREAM_PUBLISH_ERROR_REACH_LIMIT = 7,
		/** The host manipulates other hosts' URLs. Check your app logic. */
		RTMP_STREAM_PUBLISH_ERROR_NOT_AUTHORIZED = 8,
		/** Agora's server fails to find the RTMP streaming. */
		RTMP_STREAM_PUBLISH_ERROR_STREAM_NOT_FOUND = 9,
		/** The format of the RTMP streaming URL is not supported. Check whether the URL format is correct. */
		RTMP_STREAM_PUBLISH_ERROR_FORMAT_NOT_SUPPORTED = 10,
	};

	public enum class ChannelMediaRelayState {
		/** 0: The SDK is initializing.
 */
		RELAY_STATE_IDLE = 0,
		/** 1: The SDK tries to relay the media stream to the destination channel.
		 */
		 RELAY_STATE_CONNECTING = 1,
		 /** 2: The SDK successfully relays the media stream to the destination
		  * channel.
		  */
		  RELAY_STATE_RUNNING = 2,
		  /** 3: A failure occurs. See the details in code.
		   */
		   RELAY_STATE_FAILURE = 3,

	};

	public enum class ChannelMediaRelayError {
		/** 0: The state is normal.
 */
		RELAY_OK = 0,
		/** 1: An error occurs in the server response.
		 */
		 RELAY_ERROR_SERVER_ERROR_RESPONSE = 1,
		 /** 2: No server response. You can call the
		  * \ref agora::rtc::IRtcEngine::leaveChannel "leaveChannel" method to
		  * leave the channel.
		  */
		  RELAY_ERROR_SERVER_NO_RESPONSE = 2,
		  /** 3: The SDK fails to access the service, probably due to limited
		   * resources of the server.
		   */
		   RELAY_ERROR_NO_RESOURCE_AVAILABLE = 3,
		   /** 4: The server fails to join the source channel.
			*/
			RELAY_ERROR_FAILED_JOIN_SRC = 4,
			/** 5: The server fails to join the destination channel.
			 */
			 RELAY_ERROR_FAILED_JOIN_DEST = 5,
			 /** 6: The server fails to receive the data from the source channel.
			  */
			  RELAY_ERROR_FAILED_PACKET_RECEIVED_FROM_SRC = 6,
			  /** 7: The source channel fails to transmit data.
			   */
			   RELAY_ERROR_FAILED_PACKET_SENT_TO_DEST = 7,
			   /** 8: The SDK disconnects from the server due to poor network
				* connections. You can call the \ref agora::rtc::IRtcEngine::leaveChannel
				* "leaveChannel" method to leave the channel.
				*/
				RELAY_ERROR_SERVER_CONNECTION_LOST = 8,
				/** 9: An internal error occurs in the server.
				 */
				 RELAY_ERROR_INTERNAL_ERROR = 9,
				 /** 10: The token of the source channel has expired.
				  */
				  RELAY_ERROR_SRC_TOKEN_EXPIRED = 10,
				  /** 11: The token of the destination channel has expired.
				   */
				   RELAY_ERROR_DEST_TOKEN_EXPIRED = 11,

	};

	public enum class ChannelMediaRelayEvent {
		/** 0: The user disconnects from the server due to poor network
	 * connections.
	 */
		RELAY_EVENT_NETWORK_DISCONNECTED = 0,
		/** 1: The network reconnects.
		 */
		 RELAY_EVENT_NETWORK_CONNECTED = 1,
		 /** 2: The user joins the source channel.
		  */
		  RELAY_EVENT_PACKET_JOINED_SRC_CHANNEL = 2,
		  /** 3: The user joins the destination channel.
		   */
		   RELAY_EVENT_PACKET_JOINED_DEST_CHANNEL = 3,
		   /** 4: The SDK starts relaying the media stream to the destination channel.
			*/
			RELAY_EVENT_PACKET_SENT_TO_DEST_CHANNEL = 4,
			/** 5: The server receives the video stream from the source channel.
			 */
			 RELAY_EVENT_PACKET_RECEIVED_VIDEO_FROM_SRC = 5,
			 /** 6: The server receives the audio stream from the source channel.
			  */
			  RELAY_EVENT_PACKET_RECEIVED_AUDIO_FROM_SRC = 6,
			  /** 7: The destination channel is updated.
			   */
			   RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL = 7,
			   /** 8: The destination channel update fails due to internal reasons.
				*/
				RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_REFUSED = 8,
				/** 9: The destination channel does not change, which means that the
				 * destination channel fails to be updated.
				 */
				 RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_NOT_CHANGE = 9,
				 /** 10: The destination channel name is NULL.
				  */
				  RELAY_EVENT_PACKET_UPDATE_DEST_CHANNEL_IS_NULL = 10,
				  /** 11: The video profile is sent to the server.
				   */
				   RELAY_EVENT_VIDEO_PROFILE_UPDATE = 11,
	};

	public enum class PriorityType {
		/** 50: The user's priority is high.
 */
		PRIORITY_HIGH = 50,
		/** 100: (Default) The user's priority is normal.
		*/
		PRIORITY_NORMAL = 100,
	};

	public enum class LastmileProbeResultState {
		/** 1: The last-mile network probe test is complete. */
		LASTMILE_PROBE_RESULT_COMPLETE = 1,
		/** 2: The last-mile network probe test is incomplete and the bandwidth estimation is not available, probably due to limited test resources. */
		LASTMILE_PROBE_RESULT_INCOMPLETE_NO_BWE = 2,
		/** 3: The last-mile network probe test is not carried out, probably due to poor network conditions. */
		LASTMILE_PROBE_RESULT_UNAVAILABLE = 3
	};

	public enum class VideoFrameType {
		/**
 * 0: YUV420
 */
		FRAME_TYPE_YUV420 = 0,  // YUV 420 format
		/**
		 * 1: YUV422
		 */
		 FRAME_TYPE_YUV422 = 1,  // YUV 422 format
		 /**
		  * 2: RGBA
		  */
		  FRAME_TYPE_RGBA = 2,    // RGBA format
	};

	public enum class EnumCapturerOutputPreference {
		/** 0: (Default) self-adapts the camera output parameters to the system performance and network conditions to balance CPU consumption and video preview quality.
*/
		CAPTURER_OUTPUT_PREFERENCE_AUTO = 0,
		/** 2: Prioritizes the system performance. The SDK chooses the dimension and frame rate of the local camera capture closest to those set by \ref IRtcEngine::setVideoEncoderConfiguration "setVideoEncoderConfiguration".
		*/
		CAPTURER_OUTPUT_PREFERENCE_PERFORMANCE = 1,
		/** 2: Prioritizes the local preview quality. The SDK chooses higher camera output parameters to improve the local video preview quality. This option requires extra CPU and RAM usage for video pre-processing.
		*/
		CAPTURER_OUTPUT_PREFERENCE_PREVIEW = 2,
	};
}