/*
 * BLEAdvertising.h
 *
 *  Created on: Jun 21, 2017
 *      Author: kolban
 */

#ifndef COMPONENTS_CPP_UTILS_BLEADVERTISING_H_
#define COMPONENTS_CPP_UTILS_BLEADVERTISING_H_
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)
#include <esp_gap_ble_api.h>
#include "BLEUUID.h"
#include <vector>
#include "FreeRTOS.h"

/* relate to BTM_BLE_AD_TYPE_xxx in stack/btm_ble_api.h */
/// The type of advertising data(not adv_type)
typedef enum {
    ESP_BLE_AD_TYPE_FLAG                     = 0x01,    /* relate to BTM_BLE_AD_TYPE_FLAG in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_16SRV_PART               = 0x02,    /* relate to BTM_BLE_AD_TYPE_16SRV_PART in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_16SRV_CMPL               = 0x03,    /* relate to BTM_BLE_AD_TYPE_16SRV_CMPL in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_32SRV_PART               = 0x04,    /* relate to BTM_BLE_AD_TYPE_32SRV_PART in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_32SRV_CMPL               = 0x05,    /* relate to BTM_BLE_AD_TYPE_32SRV_CMPL in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_128SRV_PART              = 0x06,    /* relate to BTM_BLE_AD_TYPE_128SRV_PART in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_128SRV_CMPL              = 0x07,    /* relate to BTM_BLE_AD_TYPE_128SRV_CMPL in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_NAME_SHORT               = 0x08,    /* relate to BTM_BLE_AD_TYPE_NAME_SHORT in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_NAME_CMPL                = 0x09,    /* relate to BTM_BLE_AD_TYPE_NAME_CMPL in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_TX_PWR                   = 0x0A,    /* relate to BTM_BLE_AD_TYPE_TX_PWR in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_DEV_CLASS                = 0x0D,    /* relate to BTM_BLE_AD_TYPE_DEV_CLASS in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_SM_TK                    = 0x10,    /* relate to BTM_BLE_AD_TYPE_SM_TK in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_SM_OOB_FLAG              = 0x11,    /* relate to BTM_BLE_AD_TYPE_SM_OOB_FLAG in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_INT_RANGE                = 0x12,    /* relate to BTM_BLE_AD_TYPE_INT_RANGE in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_SOL_SRV_UUID             = 0x14,    /* relate to BTM_BLE_AD_TYPE_SOL_SRV_UUID in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_128SOL_SRV_UUID          = 0x15,    /* relate to BTM_BLE_AD_TYPE_128SOL_SRV_UUID in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_SERVICE_DATA             = 0x16,    /* relate to BTM_BLE_AD_TYPE_SERVICE_DATA in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_PUBLIC_TARGET            = 0x17,    /* relate to BTM_BLE_AD_TYPE_PUBLIC_TARGET in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_RANDOM_TARGET            = 0x18,    /* relate to BTM_BLE_AD_TYPE_RANDOM_TARGET in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_APPEARANCE               = 0x19,    /* relate to BTM_BLE_AD_TYPE_APPEARANCE in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_ADV_INT                  = 0x1A,    /* relate to BTM_BLE_AD_TYPE_ADV_INT in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_LE_DEV_ADDR              = 0x1b,    /* relate to BTM_BLE_AD_TYPE_LE_DEV_ADDR in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_LE_ROLE                  = 0x1c,    /* relate to BTM_BLE_AD_TYPE_LE_ROLE in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_SPAIR_C256               = 0x1d,    /* relate to BTM_BLE_AD_TYPE_SPAIR_C256 in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_SPAIR_R256               = 0x1e,    /* relate to BTM_BLE_AD_TYPE_SPAIR_R256 in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_32SOL_SRV_UUID           = 0x1f,    /* relate to BTM_BLE_AD_TYPE_32SOL_SRV_UUID in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_32SERVICE_DATA           = 0x20,    /* relate to BTM_BLE_AD_TYPE_32SERVICE_DATA in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_128SERVICE_DATA          = 0x21,    /* relate to BTM_BLE_AD_TYPE_128SERVICE_DATA in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_LE_SECURE_CONFIRM        = 0x22,    /* relate to BTM_BLE_AD_TYPE_LE_SECURE_CONFIRM in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_LE_SECURE_RANDOM         = 0x23,    /* relate to BTM_BLE_AD_TYPE_LE_SECURE_RANDOM in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_URI                      = 0x24,    /* relate to BTM_BLE_AD_TYPE_URI in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_INDOOR_POSITION          = 0x25,    /* relate to BTM_BLE_AD_TYPE_INDOOR_POSITION in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_TRANS_DISC_DATA          = 0x26,    /* relate to BTM_BLE_AD_TYPE_TRANS_DISC_DATA in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_LE_SUPPORT_FEATURE       = 0x27,    /* relate to BTM_BLE_AD_TYPE_LE_SUPPORT_FEATURE in stack/btm_ble_api.h */
    ESP_BLE_AD_TYPE_CHAN_MAP_UPDATE          = 0x28,    /* relate to BTM_BLE_AD_TYPE_CHAN_MAP_UPDATE in stack/btm_ble_api.h */
    ESP_BLE_AD_MANUFACTURER_SPECIFIC_TYPE    = 0xFF,    /* relate to BTM_BLE_AD_MANUFACTURER_SPECIFIC_TYPE in stack/btm_ble_api.h */
} esp_ble_adv_data_type;

/// Advertising mode
typedef enum {
    ADV_TYPE_IND                = 0x00,
    ADV_TYPE_DIRECT_IND_HIGH    = 0x01,
    ADV_TYPE_SCAN_IND           = 0x02,
    ADV_TYPE_NONCONN_IND        = 0x03,
    ADV_TYPE_DIRECT_IND_LOW     = 0x04,
} esp_ble_adv_type_t;

/// Advertising channel mask
typedef enum {
    ADV_CHNL_37     = 0x01,
    ADV_CHNL_38     = 0x02,
    ADV_CHNL_39     = 0x04,
    ADV_CHNL_ALL    = 0x07,
} esp_ble_adv_channel_t;

typedef enum {
    ///Allow both scan and connection requests from anyone
    ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY  = 0x00,
    ///Allow both scan req from White List devices only and connection req from anyone
    ADV_FILTER_ALLOW_SCAN_WLST_CON_ANY,
    ///Allow both scan req from anyone and connection req from White List devices only
    ADV_FILTER_ALLOW_SCAN_ANY_CON_WLST,
    ///Allow scan and connection requests from White List devices only
    ADV_FILTER_ALLOW_SCAN_WLST_CON_WLST,
    ///Enumeration end value for advertising filter policy value check
} esp_ble_adv_filter_t;


/* relate to BTA_DM_BLE_SEC_xxx in bta/bta_api.h */
typedef enum {
    ESP_BLE_SEC_ENCRYPT = 1,            /* relate to BTA_DM_BLE_SEC_ENCRYPT in bta/bta_api.h. If the device has already
                                           bonded, the stack will used LTK to encrypt with the remote device directly.
                                           Else if the device hasn't bonded, the stack will used the default authentication request
                                           used the esp_ble_gap_set_security_param function set by the user. */
    ESP_BLE_SEC_ENCRYPT_NO_MITM,        /* relate to BTA_DM_BLE_SEC_ENCRYPT_NO_MITM in bta/bta_api.h. If the device has already
                                           bonded, the stack will check the LTK Whether the authentication request has been met, if met, used the LTK
                                           to encrypt with the remote device directly, else Re-pair with the remote device.
                                           Else if the device hasn't bonded, the stack will used NO MITM authentication request in the current link instead of
                                           used the authreq in the esp_ble_gap_set_security_param function set by the user. */
    ESP_BLE_SEC_ENCRYPT_MITM,           /* relate to BTA_DM_BLE_SEC_ENCRYPT_MITM in bta/bta_api.h. If the device has already
                                           bonded, the stack will check the LTK Whether the authentication request has been met, if met, used the LTK
                                           to encrypt with the remote device directly, else Re-pair with the remote device.
                                           Else if the device hasn't bonded, the stack will used MITM authentication request in the current link instead of
                                           used the authreq in the esp_ble_gap_set_security_param function set by the user. */
}esp_ble_sec_act_t;

typedef enum {
    ESP_BLE_SM_PASSKEY = 0,
    /* Authentication requirements of local device */
    ESP_BLE_SM_AUTHEN_REQ_MODE,
    /* The IO capability of local device */
    ESP_BLE_SM_IOCAP_MODE,
    /* Initiator Key Distribution/Generation */
    ESP_BLE_SM_SET_INIT_KEY,
    /* Responder Key Distribution/Generation */
    ESP_BLE_SM_SET_RSP_KEY,
    /* Maximum Encryption key size to support */
    ESP_BLE_SM_MAX_KEY_SIZE,
    /* Minimum Encryption key size requirement from Peer */
    ESP_BLE_SM_MIN_KEY_SIZE,
    /* Set static Passkey */
    ESP_BLE_SM_SET_STATIC_PASSKEY,
    /* Reset static Passkey */
    ESP_BLE_SM_CLEAR_STATIC_PASSKEY,
    /* Accept only specified SMP Authentication requirement */
    ESP_BLE_SM_ONLY_ACCEPT_SPECIFIED_SEC_AUTH,
    /* Enable/Disable OOB support */
    ESP_BLE_SM_OOB_SUPPORT,
    /* Appl encryption key size */
    ESP_BLE_APP_ENC_KEY_SIZE,
    ESP_BLE_SM_MAX_PARAM,
} esp_ble_sm_param_t;

#if (BLE_42_FEATURE_SUPPORT == TRUE)
/// Advertising parameters
typedef struct {
    uint16_t                adv_int_min;        /*!< Minimum advertising interval for
                                                  undirected and low duty cycle directed advertising.
                                                  Range: 0x0020 to 0x4000 Default: N = 0x0800 (1.28 second)
                                                  Time = N * 0.625 msec Time Range: 20 ms to 10.24 sec */
    uint16_t                adv_int_max;        /*!< Maximum advertising interval for
                                                  undirected and low duty cycle directed advertising.
                                                  Range: 0x0020 to 0x4000 Default: N = 0x0800 (1.28 second)
                                                  Time = N * 0.625 msec Time Range: 20 ms to 10.24 sec Advertising max interval */
    esp_ble_adv_type_t      adv_type;           /*!< Advertising type */
    esp_ble_addr_type_t     own_addr_type;      /*!< Owner bluetooth device address type */
    esp_bd_addr_t           peer_addr;          /*!< Peer device bluetooth device address */
    esp_ble_addr_type_t     peer_addr_type;     /*!< Peer device bluetooth device address type, only support public address type and random address type */
    esp_ble_adv_channel_t   channel_map;        /*!< Advertising channel map */
    esp_ble_adv_filter_t    adv_filter_policy;  /*!< Advertising filter policy */
} esp_ble_adv_params_t;

/// Advertising data content, according to "Supplement to the Bluetooth Core Specification"
typedef struct {
    bool                    set_scan_rsp;           /*!< Set this advertising data as scan response or not*/
    bool                    include_name;           /*!< Advertising data include device name or not */
    bool                    include_txpower;        /*!< Advertising data include TX power */
    int                     min_interval;           /*!< Advertising data show slave preferred connection min interval.
                                                    The connection interval in the following manner:
                                                    connIntervalmin = Conn_Interval_Min * 1.25 ms
                                                    Conn_Interval_Min range: 0x0006 to 0x0C80
                                                    Value of 0xFFFF indicates no specific minimum.
                                                    Values not defined above are reserved for future use.*/

    int                     max_interval;           /*!< Advertising data show slave preferred connection max interval.
                                                    The connection interval in the following manner:
                                                    connIntervalmax = Conn_Interval_Max * 1.25 ms
                                                    Conn_Interval_Max range: 0x0006 to 0x0C80
                                                    Conn_Interval_Max shall be equal to or greater than the Conn_Interval_Min.
                                                    Value of 0xFFFF indicates no specific maximum.
                                                    Values not defined above are reserved for future use.*/

    int                     appearance;             /*!< External appearance of device */
    uint16_t                manufacturer_len;       /*!< Manufacturer data length */
    uint8_t                 *p_manufacturer_data;   /*!< Manufacturer data point */
    uint16_t                service_data_len;       /*!< Service data length */
    uint8_t                 *p_service_data;        /*!< Service data point */
    uint16_t                service_uuid_len;       /*!< Service uuid length */
    uint8_t                 *p_service_uuid;        /*!< Service uuid array point */
    uint8_t                 flag;                   /*!< Advertising flag of discovery mode, see BLE_ADV_DATA_FLAG detail */
} esp_ble_adv_data_t;

/**
 * @brief Advertisement data set by the programmer to be published by the %BLE server.
 */
class BLEAdvertisementData {
	// Only a subset of the possible BLE architected advertisement fields are currently exposed.  Others will
	// be exposed on demand/request or as time permits.
	//
public:
	void setAppearance(uint16_t appearance);
	void setCompleteServices(BLEUUID uuid);
	void setFlags(uint8_t);
	void setManufacturerData(std::string data);
	void setName(std::string name);
	void setPartialServices(BLEUUID uuid);
	void setServiceData(BLEUUID uuid, std::string data);
	void setShortName(std::string name);
	void addData(std::string data);         // Add data to the payload.
	std::string getPayload();               // Retrieve the current advert payload.

private:
	friend class BLEAdvertising;
	std::string m_payload;   // The payload of the advertisement.
};   // BLEAdvertisementData


/**
 * @brief Perform and manage %BLE advertising.
 *
 * A %BLE server will want to perform advertising in order to make itself known to %BLE clients.
 */
class BLEAdvertising {
public:
	BLEAdvertising();
	void addServiceUUID(BLEUUID serviceUUID);
	void addServiceUUID(const char* serviceUUID);
	void start();
	void stop();
	void setAppearance(uint16_t appearance);
	void setAdvertisementType(esp_ble_adv_type_t adv_type);
	void setMaxInterval(uint16_t maxinterval);
	void setMinInterval(uint16_t mininterval);
	void setAdvertisementData(BLEAdvertisementData& advertisementData);
	void setScanFilter(bool scanRequertWhitelistOnly, bool connectWhitelistOnly);
	void setScanResponseData(BLEAdvertisementData& advertisementData);
	void setPrivateAddress(esp_ble_addr_type_t type = BLE_ADDR_TYPE_RANDOM);
	void setDeviceAddress(esp_bd_addr_t addr, esp_ble_addr_type_t type = BLE_ADDR_TYPE_RANDOM);

	void handleGAPEvent(esp_gap_ble_cb_event_t  event, esp_ble_gap_cb_param_t* param);
	void setMinPreferred(uint16_t);
	void setMaxPreferred(uint16_t);
	void setScanResponse(bool);

private:
	esp_ble_adv_data_t   m_advData;
	esp_ble_adv_data_t   m_scanRespData; // Used for configuration of scan response data when m_scanResp is true
	esp_ble_adv_params_t m_advParams;
	std::vector<BLEUUID> m_serviceUUIDs;
	bool                 m_customAdvData = false;  // Are we using custom advertising data?
	bool                 m_customScanResponseData = false;  // Are we using custom scan response data?
	FreeRTOS::Semaphore  m_semaphoreSetAdv = FreeRTOS::Semaphore("startAdvert");
	bool                 m_scanResp = true;

};
#endif /* CONFIG_BT_ENABLED */
#endif /* COMPONENTS_CPP_UTILS_BLEADVERTISING_H_ */
