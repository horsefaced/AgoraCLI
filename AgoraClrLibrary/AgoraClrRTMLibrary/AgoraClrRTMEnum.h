#pragma once

namespace AgoraClrLibrary {
	public enum class EnumLoginErrCode {
        /**
         0: The method call succeeds, or login succeeds.
         */
        LOGIN_ERR_OK = 0,

        /**
         1: Login fails. The reason is unknown.
         */
         LOGIN_ERR_UNKNOWN = 1,

         /**
          2: Login is rejected by the server.
          */
          LOGIN_ERR_REJECTED = 2, // Occurs when not initialized or server reject

          /**
           3: Invalid login argument.
           */
           LOGIN_ERR_INVALID_ARGUMENT = 3,

           /**
            4: The App ID is invalid.
            */
            LOGIN_ERR_INVALID_APP_ID = 4,

            /**
             5: The token is invalid.
             */
             LOGIN_ERR_INVALID_TOKEN = 5,

             /**
              6: The token has expired, and hence login is rejected.
              */
              LOGIN_ERR_TOKEN_EXPIRED = 6,

              /**
               7: Unauthorized login.
               */
               LOGIN_ERR_NOT_AUTHORIZED = 7,

               /**
                8: The user has already logged in or is logging in the Agora RTM system, or the user has not called the \ref agora::rtm::IRtmService::logout "logout" method to leave the \ref agora::rtm::CONNECTION_STATE_ABORTED "CONNECTION_STATE_ABORTED" state.
                */
                LOGIN_ERR_ALREADY_LOGGED_IN = 8,

                /**
                 9: The login times out. The current timeout is set as six seconds.
                 */
                 LOGIN_ERR_TIMEOUT = 9,

                 /**
                  10: The call frequency of the \ref agora::rtm::IRtmService::login "login" method exceeds the limit of two queries per second.
                  */
                  LOGIN_ERR_TOO_OFTEN = 10,

                  /**
                   101: \ref agora::rtm::IRtmService "IRtmService" is not initialized.
                  */
                  LOGIN_ERR_NOT_INITIALIZED = 101,
	};

    public enum class EnumLogoutErrCode {
        /**
 0: The method call succeeds, or logout succeeds.
 */
        LOGOUT_ERR_OK = 0,

        /**
         1: Logout fails.
         */
         LOGOUT_ERR_REJECTED = 1,

         /**
          101: \ref agora::rtm::IRtmService "IRtmService" is not initialized.
          */
          LOGOUT_ERR_NOT_INITIALIZED = 101,

          /**
           102: The user does not call the \ref agora::rtm::IRtmService::login "login" method, or the method call of \ref agora::rtm::IRtmService::login "login" does not succeed before the user logs out of the Agora RTM system.
           */
           LOGOUT_ERR_USER_NOT_LOGGED_IN = 102,
    };

    public enum class EnumConnectionState {
        /**
 1: The initial state. The SDK is disconnected from the Agora RTM system.

 When the user calls the \ref agora::rtm::IRtmService::login "login" method, the SDK starts to log in the Agora RTM system, triggers the \ref agora::rtm::IRtmServiceEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback, and switches to the \ref agora::rtm::CONNECTION_STATE_CONNECTING "CONNECTION_STATE_CONNECTING" state.
 */
        CONNECTION_STATE_DISCONNECTED = 1,

        /**
         2: The SDK is logging in the Agora RTM system.

         - If the user successfully logs in the Agora RTM system and receives the \ref agora::rtm::IRtmServiceEventHandler::onLoginSuccess "onLoginSuccess" callback, the SDK triggers the \ref agora::rtm::IRtmServiceEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the \ref agora::rtm::CONNECTION_STATE_CONNECTED "CONNECTION_STATE_CONNECTED" state.
         - If the user fails to login the Agora RTM system and receives the \ref agora::rtm::IRtmServiceEventHandler::onLoginFailure "onLoginFailure" callback, the SDK triggers the \ref agora::rtm::IRtmServiceEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the \ref agora::rtm::CONNECTION_STATE_DISCONNECTED "CONNECTION_STATE_DISCONNECTED" state.
         */
         CONNECTION_STATE_CONNECTING = 2,

         /**
          3: The SDK has logged in the Agora RTM system.

          - If the connection state between the SDK and the Agora RTM system is interrupted because of network issues, the SDK triggers the \ref agora::rtm::IRtmServiceEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the \ref agora::rtm::CONNECTION_STATE_RECONNECTING "CONNECTION_STATE_RECONNECTING" state.
          - If the login is banned by the server because, for example, another instance logs in the Agora RTM system with the same user ID, the \ref agora::rtm::IRtmServiceEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback is triggered, and the SDK is switched to the \ref agora::rtm::CONNECTION_STATE_ABORTED "CONNECTION_STATE_ABORTED" state.
          - If the user calls the \ref agora::rtm::IRtmService::logout "logout" method to log out of the Agora RTM system and receives the \ref agora::rtm::IRtmServiceEventHandler::onLogout "onLogout" callback (error code = `LOGOUT_ERR_OK`), the SDK triggers the \ref agora::rtm::IRtmServiceEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the \ref agora::rtm::CONNECTION_STATE_DISCONNECTED "CONNECTION_STATE_DISCONNECTED" state.
          */
          CONNECTION_STATE_CONNECTED = 3,

          /**
           4: The connection state between the SDK and the Agora RTM system is interrupted due to network issues, and the SDK keeps re-logging in the Agora RTM system.

           - If the SDK successfully re-logs in the Agora RTM system, the SDK triggers the \ref agora::rtm::IRtmServiceEventHandler::onConnectionStateChanged "onConnectionStateChanged" callback and switches to the \ref agora::rtm::CONNECTION_STATE_CONNECTED "CONNECTION_STATE_CONNECTED" state. The SDK automatically adds the user back to the channel(s) he or she was in when the connection was interrupted, and synchronizes the local user's attributes with the server.
           - If the SDK cannot re-log in the Agora RTM system, it stays in the \ref agora::rtm::CONNECTION_STATE_RECONNECTING "CONNECTION_STATE_RECONNECTING" state and keeps re-logging in the system.
           */
           CONNECTION_STATE_RECONNECTING = 4,

           /**
            5: The SDK gives up logging in the Agora RTM system, mainly because another instance has logged in the Agora RTM system with the same user ID.

            You must call the \ref agora::rtm::IRtmService::logout "logout" method to leave this state before calling the \ref agora::rtm::IRtmService::login "login" method again.
            */
            CONNECTION_STATE_ABORTED = 5,

    };

    public enum class EnumConnectionChangeReason {
        /**
         1: The SDK is logging in the Agora RTM system.
         */
        CONNECTION_CHANGE_REASON_LOGIN = 1,

        /**
         2: The SDK has logged in the Agora RTM system.
         */
         CONNECTION_CHANGE_REASON_LOGIN_SUCCESS = 2,

         /**
          3: The SDK fails to log in the Agora RTM system.
          */
          CONNECTION_CHANGE_REASON_LOGIN_FAILURE = 3,

          /**
           4: The SDK fails to log in the Agora RTM system within six seconds and gives up.
           */
           CONNECTION_CHANGE_REASON_LOGIN_TIMEOUT = 4,

           /**
            5: The connection between the SDK and the Agora RTM system is interrupted. The system defines an interruption when the SDK loses connection with the Agora RTM system for network reasons and cannot recover in four seconds.
            */
            CONNECTION_CHANGE_REASON_INTERRUPTED = 5,

            /**
             6: The user has called the \ref agora::rtm::IRtmService::logout "logout" method to log out of the Agora RTM system.
             */
             CONNECTION_CHANGE_REASON_LOGOUT = 6,

             /**
              7: The SDK login to the Agora RTM system is banned by Agora.
              */
              CONNECTION_CHANGE_REASON_BANNED_BY_SERVER = 7,

              /**
               8: Another user is logging in the Agora RTM system with the same User ID.
               */
               CONNECTION_CHANGE_REASON_REMOTE_LOGIN = 8,

    };

    public enum class EnumMessageType {
        /**
 0: The message type is undefined.
 */
        MESSAGE_TYPE_UNDEFINED = 0,

        /**
         1: A text message.
         */
         MESSAGE_TYPE_TEXT = 1,
         /**
          2: A raw message.
          */
          MESSAGE_TYPE_RAW = 2,

    };

    public enum class EnumPeerMessageErrCode {
        /**
         0: The method call succeeds, or the specified user receives the peer-to-peer message.
         */
        PEER_MESSAGE_ERR_OK = 0,

        /**
         1: The sender fails to send the peer-to-peer message.
         */
         PEER_MESSAGE_ERR_FAILURE = 1,

         /**
          2: A timeout occurs when sending the peer-to-peer message. The current timeout is set as 10 seconds. Possible reasons: The user is in the \ref agora::rtm::CONNECTION_STATE_ABORTED "CONNECTION_STATE_ABORTED" or \ref agora::rtm::CONNECTION_STATE_RECONNECTING "CONNECTION_STATE_RECONNECTING" state.
          */
          PEER_MESSAGE_ERR_SENT_TIMEOUT = 2,

          /**
           3: The specified user is offline and does not receive this peer-to-peer message.
           */
           PEER_MESSAGE_ERR_PEER_UNREACHABLE = 3,

           /**
            4: The receiver is offline and does not receive this offline peer-to-peer message, but the server has cached it and will re-send it once he/she is back online.
            */
            PEER_MESSAGE_ERR_CACHED_BY_SERVER = 4,

            /**
             5: The method call frequency exceeds the limit of 60 queries per second (channel and peer messages taken together).
             */
             PEER_MESSAGE_ERR_TOO_OFTEN = 5,

             /**
              6: The user ID is invalid.
              */
              PEER_MESSAGE_ERR_INVALID_USERID = 6,

              /**
               7: The message is null or exceeds 32 KB in length.
               */
               PEER_MESSAGE_ERR_INVALID_MESSAGE = 7,

               /**
                101: \ref agora::rtm::IRtmService "IRtmService" is not initialized.
                */
                PEER_MESSAGE_ERR_NOT_INITIALIZED = 101,

                /**
                 102: The sender does not call the \ref agora::rtm::IRtmService::login "login" method, or the method call of \ref agora::rtm::IRtmService::login "login" does not succeed before sending the peer-to-peer message.
                 */
                 PEER_MESSAGE_ERR_USER_NOT_LOGGED_IN = 102,
    };


}