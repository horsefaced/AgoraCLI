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

	public enum class EnumAudienceLatencyLevelType
	{
		AUDIENCE_LATENCY_LEVEL_LOW_LATENCY = 1,
		AUDIENCE_LATENCY_LEVEL_ULTRA_LOW_LATENCY = 2,
	};

	public
		enum class EnumRenderModeType
	{
		RENDER_MODE_HIDDEN = 1,
		RENDER_MODE_FIT = 2,
		RENDER_MODE_ADAPTIVE = 3,
		RENDER_MODE_FILL = 4,
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
		enum class EnumRemoteVideoStreamType
	{
		REMOTE_VIDEO_STREAM_HIGH = 0,
		REMOTE_VIDEO_STREAM_LOW = 1,
	};

	public enum class EnumMediaDeviceStateType
	{
		/** 0: The device is idle.
		*/
		MEDIA_DEVICE_STATE_IDLE = 0,
		/** 1: The device is active.
		*/
		MEDIA_DEVICE_STATE_ACTIVE = 1,
		/** 2: The device is disabled.
		*/
		MEDIA_DEVICE_STATE_DISABLED = 2,
		/** 4: The device is not present.
		*/
		MEDIA_DEVICE_STATE_NOT_PRESENT = 4,
		/** 8: The device is unplugged.
		*/
		MEDIA_DEVICE_STATE_UNPLUGGED = 8,
		/** 16: The device is not recommended.
		*/
		MEDIA_DEVICE_STATE_UNRECOMMENDED = 16,
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
		AUDIO_CODEC_PROFILE_HE_AAC_V2 = 2,
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
		AUDIO_SCENARIO_MEETING = 8,
		AUDIO_SCENARIO_NUM = 9,
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
		enum class EnumConnectionStateType
	{
		CONNECTION_STATE_DISCONNECTED = 1,
		CONNECTION_STATE_CONNECTING = 2,
		CONNECTION_STATE_CONNECTED = 3,
		CONNECTION_STATE_RECONNECTING = 4,
		CONNECTION_STATE_FAILED = 5,
	};

	public
		enum class EnumConnectionChangedReasonType
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
		VIDEO_BUFFER_PIXEL_BUFFER = 2,
	};

	/** The video pixel format.
		 */
	public
		enum class EnumVideoPixelFormat
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
		VIDEO_PIXEL_NV21 = 3,
		VIDEO_PIXEL_RGBA = 4,
		VIDEO_PIXEL_IMC2 = 5,
		VIDEO_PIXEL_ARGB = 7,
		/** 8: The video pixel format is NV12.
		*/
		VIDEO_PIXEL_NV12 = 8,
		VIDEO_PIXEL_I422 = 16,
	};

	public
		enum class StreamFallbackOptions
	{
		STREAM_FALLBACK_OPTION_DISABLED = 0,
		STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
		STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
	};

	public
		enum class EnumRemoteVideoState
	{
		REMOTE_VIDEO_STATE_STOPPED = 0,
		REMOTE_VIDEO_STATE_STARTING = 1,
		REMOTE_VIDEO_STATE_DECODING = 2,
		REMOTE_VIDEO_STATE_FROZEN = 3,
		REMOTE_VIDEO_STATE_FAILED = 4
	};

	public enum class EnumRemoteVideoStateReason
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
		NETWORK_TYPE_MOBILE_5G = 6,
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
		LOCAL_AUDIO_STREAM_ERROR_ENCODE_FAILURE = 5,
		LOCAL_AUDIO_STREAM_ERROR_NO_RECORDING_DEVICE = 6,
		LOCAL_AUDIO_STREAM_ERROR_NO_PLAYOUT_DEVICE = 7,
		LOCAL_AUDIO_STREAM_ERROR_INTERRUPTED = 8,
		LOCAL_AUDIO_STREAM_ERROR_RECORD_INVALID_ID = 9,
		LOCAL_AUDIO_STREAM_ERROR_PLAYOUT_INVALID_ID = 10,
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
		LOCAL_VIDEO_STREAM_ERROR_ENCODE_FAILURE = 5,
		/** 11: The shared window is minimized when you call \ref IRtcEngine::startScreenCaptureByWindowId "startScreenCaptureByWindowId" to share a window.*/
		LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_WINDOW_MINIMIZED = 11,
		LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_WINDOW_CLOSED = 12,
		LOCAL_VIDEO_STREAM_ERROR_DEVICE_INVALID_ID = 10,
		LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_WINDOW_OCCLUDED = 13,
		LOCAL_VIDEO_STREAM_ERROR_SCREEN_CAPTURE_WINDOW_NOT_SUPPORTED = 20,
	};

	public enum class EnumRemoteAudioState
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

	public enum class EnumRemoteAudioStateReason
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

	public enum class AudioMixingReasonType {
		/** 701: The SDK cannot open the audio mixing file.
		*/
		AUDIO_MIXING_REASON_CAN_NOT_OPEN = 701,
		/** 702: The SDK opens the audio mixing file too frequently.
		*/
		AUDIO_MIXING_REASON_TOO_FREQUENT_CALL = 702,
		/** 703: The audio mixing file playback is interrupted.
		*/
		AUDIO_MIXING_REASON_INTERRUPTED_EOF = 703,
		/** 720: The audio mixing is started by user.
		*/
		AUDIO_MIXING_REASON_STARTED_BY_USER = 720,
		/** 721: The audio mixing file is played once.
		*/
		AUDIO_MIXING_REASON_ONE_LOOP_COMPLETED = 721,
		/** 722: The audio mixing file is playing in a new loop.
		*/
		AUDIO_MIXING_REASON_START_NEW_LOOP = 722,
		/** 723: The audio mixing file is all played out.
		*/
		AUDIO_MIXING_REASON_ALL_LOOPS_COMPLETED = 723,
		/** 724: Playing of audio file is stopped by user.
		*/
		AUDIO_MIXING_REASON_STOPPED_BY_USER = 724,
		/** 725: Playing of audio file is paused by user.
		*/
		AUDIO_MIXING_REASON_PAUSED_BY_USER = 725,
		/** 726: Playing of audio file is resumed by user.
		*/
		AUDIO_MIXING_REASON_RESUMED_BY_USER = 726,
	};

	public enum class VoiceChangerPreset {
		/**
	 * The original voice (no local voice change).
	 */
		VOICE_CHANGER_OFF = 0x00000000, //Turn off the voice changer
		/**
		 * The voice of an old man.
		 */
		 VOICE_CHANGER_OLDMAN = 0x00000001,
		 /**
		  * The voice of a little boy.
		  */
		  VOICE_CHANGER_BABYBOY = 0x00000002,
		  /**
		   * The voice of a little girl.
		   */
		   VOICE_CHANGER_BABYGIRL = 0x00000003,
		   /**
			* The voice of Zhu Bajie, a character in Journey to the West who has a voice like that of a growling bear.
			*/
			VOICE_CHANGER_ZHUBAJIE = 0x00000004,
			/**
			 * The ethereal voice.
			 */
			 VOICE_CHANGER_ETHEREAL = 0x00000005,
			 /**
			  * The voice of Hulk.
			  */
			  VOICE_CHANGER_HULK = 0x00000006,
			  /**
			   * A more vigorous voice.
			   */
			   VOICE_BEAUTY_VIGOROUS = 0x00100001,//7,
			   /**
				* A deeper voice.
				*/
				VOICE_BEAUTY_DEEP = 0x00100002,
				/**
				 * A mellower voice.
				 */
				 VOICE_BEAUTY_MELLOW = 0x00100003,
				 /**
				  * Falsetto.
				  */
				  VOICE_BEAUTY_FALSETTO = 0x00100004,
				  /**
				   * A fuller voice.
				   */
				   VOICE_BEAUTY_FULL = 0x00100005,
				   /**
					* A clearer voice.
					*/
					VOICE_BEAUTY_CLEAR = 0x00100006,
					/**
					 * A more resounding voice.
					 */
					 VOICE_BEAUTY_RESOUNDING = 0x00100007,
					 /**
					  * A more ringing voice.
					  */
					  VOICE_BEAUTY_RINGING = 0x00100008,
					  /**
					   * A more spatially resonant voice.
					   */
					   VOICE_BEAUTY_SPACIAL = 0x00100009,
					   /**
						* (For male only) A more magnetic voice. Do not use it when the speaker is a female; otherwise, voice distortion occurs.
						*/
						GENERAL_BEAUTY_VOICE_MALE_MAGNETIC = 0x00200001,
						/**
						 * (For female only) A fresher voice. Do not use it when the speaker is a male; otherwise, voice distortion occurs.
						 */
						 GENERAL_BEAUTY_VOICE_FEMALE_FRESH = 0x00200002,
						 /**
						  * 	(For female only) A more vital voice. Do not use it when the speaker is a male; otherwise, voice distortion occurs.
						  */
						  GENERAL_BEAUTY_VOICE_FEMALE_VITALITY = 0x00200003

	};

	public enum class EnumAudioReverbPreset {
		/**
	 * Turn off local voice reverberation, that is, to use the original voice.
	 */
		AUDIO_REVERB_OFF = 0x00000000, // Turn off audio reverb
		/**
		 * The reverberation style typical of a KTV venue (enhanced).
		 */
		 AUDIO_REVERB_FX_KTV = 0x00100001,
		 /**
		  * The reverberation style typical of a concert hall (enhanced).
		  */
		  AUDIO_REVERB_FX_VOCAL_CONCERT = 0x00100002,
		  /**
		   * The reverberation style typical of an uncle's voice.
		   */
		   AUDIO_REVERB_FX_UNCLE = 0x00100003,
		   /**
			* The reverberation style typical of a little sister's voice.
			*/
			AUDIO_REVERB_FX_SISTER = 0x00100004,
			/**
			 * The reverberation style typical of a recording studio (enhanced).
			 */
			 AUDIO_REVERB_FX_STUDIO = 0x00100005,
			 /**
			  * The reverberation style typical of popular music (enhanced).
			  */
			  AUDIO_REVERB_FX_POPULAR = 0x00100006,
			  /**
			   * The reverberation style typical of R&B music (enhanced).
			   */
			   AUDIO_REVERB_FX_RNB = 0x00100007,
			   /**
				* The reverberation style typical of the vintage phonograph.
				*/
				AUDIO_REVERB_FX_PHONOGRAPH = 0x00100008,
				/**
				 * The reverberation style typical of popular music.
				 */
				 AUDIO_REVERB_POPULAR = 0x00000001,
				 /**
				  * The reverberation style typical of R&B music.
				  */
				  AUDIO_REVERB_RNB = 0x00000002,
				  /**
				   * The reverberation style typical of rock music.
				   */
				   AUDIO_REVERB_ROCK = 0x00000003,
				   /**
					* The reverberation style typical of hip-hop music.
					*/
					AUDIO_REVERB_HIPHOP = 0x00000004,
					/**
					 * The reverberation style typical of a concert hall.
					 */
					 AUDIO_REVERB_VOCAL_CONCERT = 0x00000005,
					 /**
					  * The reverberation style typical of a KTV venue.
					  */
					  AUDIO_REVERB_KTV = 0x00000006,
					  /**
					   * The reverberation style typical of a recording studio.
					   */
					   AUDIO_REVERB_STUDIO = 0x00000007,
					   /**
						* The reverberation of the virtual stereo. The virtual stereo is an effect that renders the monophonic
						* audio as the stereo audio, so that all users in the channel can hear the stereo voice effect.
						* To achieve better virtual stereo reverberation, Agora recommends setting `profile` in `setAudioProfile`
						* as `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`.
						*/
						AUDIO_VIRTUAL_STEREO = 0x00200001

	};

	public enum class EnumRtmpStreamPublishState {
		RTMP_STREAM_PUBLISH_STATE_IDLE = 0,
		RTMP_STREAM_PUBLISH_STATE_CONNECTING = 1,
		RTMP_STREAM_PUBLISH_STATE_RUNNING = 2,
		RTMP_STREAM_PUBLISH_STATE_RECOVERING = 3,
		RTMP_STREAM_PUBLISH_STATE_FAILURE = 4,
		RTMP_STREAM_PUBLISH_STATE_DISCONNECTING = 5,
	};

	public enum class EnumRtmpStreamPublishError {
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
		RTMP_STREAM_UNPUBLISH_ERROR_OK = 100,
		RTMP_STREAM_PUBLISH_ERROR_NOT_BROADCASTER = 11,
		RTMP_STREAM_PUBLISH_ERROR_TRANSCODING_NO_MIX_STREAM = 13,
		RTMP_STREAM_PUBLISH_ERROR_NET_DOWN = 14,
		RTMP_STREAM_PUBLISH_ERROR_INVALID_APPID = 15,
	};

	public enum class EnumChannelMediaRelayState {
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

	public enum class EnumChannelMediaRelayError {
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

	public enum class EnumChannelMediaRelayEvent {
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
		/** 12: The SDK successfully pauses relaying the media stream to destination channels.
		*
		* @since v3.5.1
		*/
		RELAY_EVENT_PAUSE_SEND_PACKET_TO_DEST_CHANNEL_SUCCESS = 12,
		/** 13: The SDK fails to pause relaying the media stream to destination channels.
		*
		* @since v3.5.1
		*/
		RELAY_EVENT_PAUSE_SEND_PACKET_TO_DEST_CHANNEL_FAILED = 13,
		/** 14: The SDK successfully resumes relaying the media stream to destination channels.
		*
		* @since v3.5.1
		*/
		RELAY_EVENT_RESUME_SEND_PACKET_TO_DEST_CHANNEL_SUCCESS = 14,
		/** 15: The SDK fails to resume relaying the media stream to destination channels.
		*
		* @since v3.5.1
		*/
		RELAY_EVENT_RESUME_SEND_PACKET_TO_DEST_CHANNEL_FAILED = 15,

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

	public enum class EnumLighteningContrastLevel {
		/** Low contrast level. */
		LIGHTENING_CONTRAST_LOW = 0,
		/** (Default) Normal contrast level. */
		LIGHTENING_CONTRAST_NORMAL,
		/** High contrast level. */
		LIGHTENING_CONTRAST_HIGH
	};

	public enum class EnumVideoMirrorModeType {
		/** 0: (Default) The SDK enables the mirror mode.
 */
		VIDEO_MIRROR_MODE_AUTO = 0,//determined by SDK
			/** 1: Enable mirror mode. */
			VIDEO_MIRROR_MODE_ENABLED = 1,//enabled mirror
				/** 2: Disable mirror mode. */
				VIDEO_MIRROR_MODE_DISABLED = 2,//disable mirror
	};

	public enum class EnumClientRoleType
	{
		/** 1: Host */
		CLIENT_ROLE_BROADCASTER = 1,
		/** 2: Audience */
		CLIENT_ROLE_AUDIENCE = 2,
	};

	public enum class EnumUserOfflineReasonType
	{
		/** 0: The user quits the call. */
		USER_OFFLINE_QUIT = 0,
		/** 1: The SDK times out and the user drops offline because no data packet is received within a certain period of time. If the user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user dropped offline. */
		USER_OFFLINE_DROPPED = 1,
		/** 2: (Live broadcast only.) The client role switched from the host to the audience. */
		USER_OFFLINE_BECOME_AUDIENCE = 2,
	};

	/**
  * The frame position of the video observer.
  */
	public enum class EnumVideoObserverPositionType {
		/**
		 * 1: The post-capturer position, which corresponds to the video data in the onCaptureVideoFrame callback.
		 */
		POSITION_POST_CAPTURER = 1 << 0,
		/**
		 * 2: The pre-renderer position, which corresponds to the video data in the onRenderVideoFrame callback.
		 */
		 POSITION_PRE_RENDERER = 1 << 1,
		 /**
		  * 4: The pre-encoder position, which corresponds to the video data in the onPreEncodeVideoFrame callback.
		  */
		  POSITION_PRE_ENCODER = 1 << 2,
	};

	public enum class EnumStreamPublishState {
		/** 0: The initial publishing state after joining the channel.*/
		PUB_STATE_IDLE = 0,
		/** 1: Fails to publish the local stream. Possible reasons:
		 * - The local user calls \ref IRtcEngine::muteLocalAudioStream "muteLocalAudioStream(true)" or \ref IRtcEngine::muteLocalVideoStream "muteLocalVideoStream(true)" to stop sending local streams.
		 * - The local user calls \ref IRtcEngine::disableAudio "disableAudio" or \ref IRtcEngine::disableVideo "disableVideo" to disable the entire audio or video module.
		 * - The local user calls \ref IRtcEngine::enableLocalAudio "enableLocalAudio(false)" or \ref IRtcEngine::enableLocalVideo "enableLocalVideo(false)" to disable the local audio sampling or video capturing.
		 * - The role of the local user is `AUDIENCE`.
		 */
		 PUB_STATE_NO_PUBLISHED = 1,
		 /** 2: Publishing.
		  */
		  PUB_STATE_PUBLISHING = 2,
		  /** 3: Publishes successfully.
		   */
		   PUB_STATE_PUBLISHED = 3
	};

	public enum class EnumStreamSubscribeState {
		/** 0: The initial subscribing state after joining the channel.
		 */
		SUB_STATE_IDLE = 0,
		/** 1: Fails to subscribe to the remote stream. Possible reasons:
		 * - The remote user:
		 *  - Calls \ref IRtcEngine::muteLocalAudioStream "muteLocalAudioStream(true)" or \ref IRtcEngine::muteLocalVideoStream "muteLocalVideoStream(true)" to stop sending local streams.
		 *  - Calls \ref IRtcEngine::disableAudio "disableAudio" or \ref IRtcEngine::disableVideo "disableVideo" to disable the entire audio or video modules.
		 *  - Calls \ref IRtcEngine::enableLocalAudio "enableLocalAudio(false)" or \ref IRtcEngine::enableLocalVideo "enableLocalVideo(false)" to disable the local audio sampling or video capturing.
		 *  - The role of the remote user is `AUDIENCE`.
		 * - The local user calls the following methods to stop receiving remote streams:
		 *  - Calls \ref IRtcEngine::muteRemoteAudioStream "muteRemoteAudioStream(true)", \ref IRtcEngine::muteAllRemoteAudioStreams "muteAllRemoteAudioStreams(true)", or \ref IRtcEngine::setDefaultMuteAllRemoteAudioStreams "setDefaultMuteAllRemoteAudioStreams(true)" to stop receiving remote audio streams.
		 *  - Calls \ref IRtcEngine::muteRemoteVideoStream "muteRemoteVideoStream(true)", \ref IRtcEngine::muteAllRemoteVideoStreams "muteAllRemoteVideoStreams(true)", or \ref IRtcEngine::setDefaultMuteAllRemoteVideoStreams "setDefaultMuteAllRemoteVideoStreams(true)" to stop receiving remote video streams.
		 */
		 SUB_STATE_NO_SUBSCRIBED = 1,
		 /** 2: Subscribing.
		  */
		  SUB_STATE_SUBSCRIBING = 2,
		  /** 3: Subscribes to and receives the remote stream successfully.
		   */
		   SUB_STATE_SUBSCRIBED = 3
	};

	public enum class EnumEncryptionMode
	{
		/** 1: (Default) 128-bit AES encryption, XTS mode.
		*/
		AES_128_XTS = 1,
		/** 2: 128-bit AES encryption, ECB mode.
		*/
		AES_128_ECB = 2,
		/** 3: 256-bit AES encryption, XTS mode.
		*/
		AES_256_XTS = 3,
		/** 4: 128-bit SM4 encryption, ECB mode.
		*/
		SM4_128_ECB = 4,
		AES_128_GCM = 5, //128 位 AES 加密，GCM 模式。
		AES_256_GCM = 6, //256 位 AES 加密，GCM 模式。
		AES_128_GCM2 = 7,
		AES_256_GCM2 = 8,
		/** Enumerator boundary.
		*/
		MODE_END,
	};

	public enum class EnumVideoCaptureType {
		/** Unknown type.
		 */
		VIDEO_CAPTURE_UNKNOWN,
		/** (Default) Video captured by the camera.
		 */
		 VIDEO_CAPTURE_CAMERA,
		 /** Video for screen sharing.
		  */
		  VIDEO_CAPTURE_SCREEN,
	};

	public enum class EnumRtmpStreamingEvent
	{
		/** An error occurs when you add a background image or a watermark image to the RTMP stream.
		 */
		RTMP_STREAMING_EVENT_FAILED_LOAD_IMAGE = 1,
		RTMP_STREAMING_EVENT_URL_ALREADY_IN_USE = 2,
		RTMP_STREAMING_EVENT_ADVANCED_FEATURE_NOT_SUPPORT = 3,
		RTMP_STREAMING_EVENT_REQUEST_TOO_OFTEN = 4,
	};

	public enum class EnumVoiceBeautifierPreset
	{
		/** Turn off voice beautifier effects and use the original voice.
		 */
		VOICE_BEAUTIFIER_OFF = 0x00000000,
		/** A more magnetic voice.
		 *
		 * @note Agora recommends using this enumerator to process a male-sounding voice; otherwise, you may experience vocal distortion.
		 */
		 CHAT_BEAUTIFIER_MAGNETIC = 0x01010100,
		 /** A fresher voice.
		  *
		  * @note Agora recommends using this enumerator to process a female-sounding voice; otherwise, you may experience vocal distortion.
		  */
		  CHAT_BEAUTIFIER_FRESH = 0x01010200,
		  /** A more vital voice.
		   *
		   * @note Agora recommends using this enumerator to process a female-sounding voice; otherwise, you may experience vocal distortion.
		   */
		   CHAT_BEAUTIFIER_VITALITY = 0x01010300,
		   /**
			* @since v3.3.0
			*
			* Singing beautifier effect.
			* - If you call \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset" (SINGING_BEAUTIFIER), you can beautify a male-sounding voice and add a reverberation
			* effect that sounds like singing in a small room. Agora recommends not using \ref IRtcEngine::setVoiceBeautifierPreset "setVoiceBeautifierPreset" (SINGING_BEAUTIFIER)
			* to process a female-sounding voice; otherwise, you may experience vocal distortion.
			* - If you call \ref IRtcEngine::setVoiceBeautifierParameters "setVoiceBeautifierParameters"(SINGING_BEAUTIFIER, param1, param2), you can beautify a male- or
			* female-sounding voice and add a reverberation effect.
			*/
			SINGING_BEAUTIFIER = 0x01020100,
			/** A more vigorous voice.
			 */
			 TIMBRE_TRANSFORMATION_VIGOROUS = 0x01030100,
			 /** A deeper voice.
			  */
			  TIMBRE_TRANSFORMATION_DEEP = 0x01030200,
			  /** A mellower voice.
			   */
			   TIMBRE_TRANSFORMATION_MELLOW = 0x01030300,
			   /** A falsetto voice.
				*/
				TIMBRE_TRANSFORMATION_FALSETTO = 0x01030400,
				/** A fuller voice.
				 */
				 TIMBRE_TRANSFORMATION_FULL = 0x01030500,
				 /** A clearer voice.
				  */
				  TIMBRE_TRANSFORMATION_CLEAR = 0x01030600,
				  /** A more resounding voice.
				   */
				   TIMBRE_TRANSFORMATION_RESOUNDING = 0x01030700,
				   /** A more ringing voice.
					*/
					TIMBRE_TRANSFORMATION_RINGING = 0x01030800
	};

	public enum class EnumAudioEffectPreset
	{
		AUDIO_EFFECT_OFF = 0x00000000,
		/** An audio effect typical of a KTV venue.
		 *
		 * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
		 * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
		 * before setting this enumerator.
		 */
		 ROOM_ACOUSTICS_KTV = 0x02010100,
		 /** An audio effect typical of a concert hall.
		  *
		  * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
		  * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
		  * before setting this enumerator.
		  */
		  ROOM_ACOUSTICS_VOCAL_CONCERT = 0x02010200,
		  /** An audio effect typical of a recording studio.
		   *
		   * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
		   * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
		   * before setting this enumerator.
		   */
		   ROOM_ACOUSTICS_STUDIO = 0x02010300,
		   /** An audio effect typical of a vintage phonograph.
			*
			* @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
			* and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
			* before setting this enumerator.
			*/
			ROOM_ACOUSTICS_PHONOGRAPH = 0x02010400,
			/** A virtual stereo effect that renders monophonic audio as stereo audio.
			 *
			 * @note Call \ref IRtcEngine::setAudioProfile "setAudioProfile" and set the `profile` parameter to
			 * `AUDIO_PROFILE_MUSIC_STANDARD_STEREO(3)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before setting this
			 * enumerator; otherwise, the enumerator setting does not take effect.
			 */
			 ROOM_ACOUSTICS_VIRTUAL_STEREO = 0x02010500,
			 /** A more spatial audio effect.
			  *
			  * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
			  * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
			  * before setting this enumerator.
			  */
			  ROOM_ACOUSTICS_SPACIAL = 0x02010600,
			  /** A more ethereal audio effect.
			   *
			   * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile"
			   * and setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)`
			   * before setting this enumerator.
			   */
			   ROOM_ACOUSTICS_ETHEREAL = 0x02010700,
			   /** A 3D voice effect that makes the voice appear to be moving around the user. The default cycle period of the 3D
				* voice effect is 10 seconds. To change the cycle period, call \ref IRtcEngine::setAudioEffectParameters "setAudioEffectParameters"
				* after this method.
				*
				* @note
				* - Call \ref IRtcEngine::setAudioProfile "setAudioProfile" and set the `profile` parameter to `AUDIO_PROFILE_MUSIC_STANDARD_STEREO(3)`
				* or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before setting this enumerator; otherwise, the enumerator setting does not take effect.
				* - If the 3D voice effect is enabled, users need to use stereo audio playback devices to hear the anticipated voice effect.
				*/
				ROOM_ACOUSTICS_3D_VOICE = 0x02010800,
				/** The voice of an uncle.
				 *
				 * @note
				 * - Agora recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice effect.
				 * - To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
				 * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
				 * setting this enumerator.
				 */
				 VOICE_CHANGER_EFFECT_UNCLE = 0x02020100,
				 /** The voice of an old man.
				  *
				  * @note
				  * - Agora recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice effect.
				  * - To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting
				  * the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before setting
				  * this enumerator.
				  */
				  VOICE_CHANGER_EFFECT_OLDMAN = 0x02020200,
				  /** The voice of a boy.
				   *
				   * @note
				   * - Agora recommends using this enumerator to process a male-sounding voice; otherwise, you may not hear the anticipated voice effect.
				   * - To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting
				   * the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
				   * setting this enumerator.
				   */
				   VOICE_CHANGER_EFFECT_BOY = 0x02020300,
				   /** The voice of a young woman.
					*
					* @note
					* - Agora recommends using this enumerator to process a female-sounding voice; otherwise, you may not hear the anticipated voice effect.
					* - To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting
					* the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
					* setting this enumerator.
					*/
					VOICE_CHANGER_EFFECT_SISTER = 0x02020400,
					/** The voice of a girl.
					 *
					 * @note
					 * - Agora recommends using this enumerator to process a female-sounding voice; otherwise, you may not hear the anticipated voice effect.
					 * - To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and setting
					 * the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
					 * setting this enumerator.
					 */
					 VOICE_CHANGER_EFFECT_GIRL = 0x02020500,
					 /** The voice of Pig King, a character in Journey to the West who has a voice like a growling bear.
					  *
					  * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
					  * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
					  * setting this enumerator.
					  */
					  VOICE_CHANGER_EFFECT_PIGKING = 0x02020600,
					  /** The voice of Hulk.
					   *
					   * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
					   * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
					   * setting this enumerator.
					   */
					   VOICE_CHANGER_EFFECT_HULK = 0x02020700,
					   /** An audio effect typical of R&B music.
						*
						* @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
						* setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
						* setting this enumerator.
						*/
						STYLE_TRANSFORMATION_RNB = 0x02030100,
						/** An audio effect typical of popular music.
						 *
						 * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
						 * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
						 * setting this enumerator.
						 */
						 STYLE_TRANSFORMATION_POPULAR = 0x02030200,
						 /** A pitch correction effect that corrects the user's pitch based on the pitch of the natural C major scale.
						  * To change the basic mode and tonic pitch, call \ref IRtcEngine::setAudioEffectParameters "setAudioEffectParameters" after this method.
						  *
						  * @note To achieve better audio effect quality, Agora recommends calling \ref IRtcEngine::setAudioProfile "setAudioProfile" and
						  * setting the `profile` parameter to `AUDIO_PROFILE_MUSIC_HIGH_QUALITY(4)` or `AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO(5)` before
						  * setting this enumerator.
						  */
						  PITCH_CORRECTION = 0x02040100
	};

	public enum class EnumCloudProxyType {
		/** 0: Do not use the cloud proxy.
		 */
		NONE_PROXY = 0,
		/** 1: The cloud proxy for the UDP protocol.
		 */
		 UDP_PROXY = 1,
		 /// @cond
		 /** 2: The cloud proxy for the TCP (encrypted) protocol.
		  */
		  TCP_PROXY = 2,
		  /// @endcond
	};

	public enum class EnumLogLevel {
		LOG_LEVEL_NONE = 0, //不输出任何日志。
		LOG_LEVEL_INFO = 0x0001, // (默认)输出 FATAL、ERROR、WARN、INFO 级别的日志。我们推荐你将日志级别设为该等级。
		LOG_LEVEL_WARN = 0x0002, //仅输出 FATAL、ERROR、WARN 级别的日志。
		LOG_LEVEL_ERROR = 0x0004, //仅输出 FATAL、ERROR 级别的日志。
		LOG_LEVEL_FATAL = 0x0008, //仅输出 FATAL 级别的日志。
	};

	public enum class EnumAreaCode {
		/**
		 * Mainland China.
		 */
		AREA_CODE_CN = 0x00000001,
		/**
		 * North America.
		 */
		 AREA_CODE_NA = 0x00000002,
		 /**
		  * Europe.
		  */
		  AREA_CODE_EU = 0x00000004,
		  /**
		   * Asia, excluding Mainland China.
		   */
		   AREA_CODE_AS = 0x00000008,
		   /**
			* Japan.
			*/
			AREA_CODE_JP = 0x00000010,
			/**
			 * India.
			 */
			 AREA_CODE_IN = 0x00000020,
			 /**
			  * (Default) Global.
			  */
			  AREA_CODE_GLOB = 0xFFFFFFFF
	};
	public enum class EnumVoiceConversionPreset
	{
		VOICE_CONVERSION_OFF = 0x00000000,
		VOICE_CHANGER_NEUTRAL = 0x03010100,
		VOICE_CHANGER_SWEET = 0x03010200,
		VOICE_CHANGER_SOLID = 0x03010300,
		VOICE_CHANGER_BASS = 0x03010400
	};

	public enum class EnumAudioRecordingPosition {
		/** The SDK will record the voices of all users in the channel. */
		AUDIO_RECORDING_POSITION_MIXED_RECORDING_AND_PLAYBACK = 0,
		/** The SDK will record the voice of the local user. */
		AUDIO_RECORDING_POSITION_RECORDING = 1,
		/** The SDK will record the voices of remote users. */
		AUDIO_RECORDING_POSITION_MIXED_PLAYBACK = 2,
	};

	public enum class EnumAudioMixingDualMonoMode {
		/**
		 * 0: Original mode.
		 */
		AUDIO_MIXING_DUAL_MONO_AUTO = 0,
		/**
		 * 1: Left channel mode. This mode replaces the audio of the right channel
		 * with the audio of the left channel, which means the user can only hear
		 * the audio of the left channel.
		 */
		 AUDIO_MIXING_DUAL_MONO_L = 1,
		 /**
		  * 2: Right channel mode. This mode replaces the audio of the left channel with
		  * the audio of the right channel, which means the user can only hear the audio
		  * of the right channel.
		  */
		  AUDIO_MIXING_DUAL_MONO_R = 2,
		  /**
		   * 3: Mixed channel mode. This mode mixes the audio of the left channel and
		   * the right channel, which means the user can hear the audio of the left
		   * channel and the right channel at the same time.
		   */
		   AUDIO_MIXING_DUAL_MONO_MIX = 3
	};

	public enum class EnumAudioFileInfoError {
		AUDIO_FILE_INFO_ERROR_OK = 0,
		AUDIO_FILE_INFO_ERROR_FAILURE = 1,
	};

	public enum class EnumScreenCaptureSourceType {
		ScreenCaptureSourceType_Unknown = -1,
		ScreenCaptureSourceType_Window = 0,
		ScreenCaptureSourceType_Screen = 1,
		ScreenCaptureSourceType_Custom = 2,
	};
}