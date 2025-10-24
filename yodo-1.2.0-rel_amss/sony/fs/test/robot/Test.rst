.. default-role:: code

=====================================
  Robot Framework Fastboot Test
=====================================

.. contents:: Table of contents:
   :local:
   :depth: 2


Test cases
==========

.. code:: robotframework

    *** Settings ***
    Library           OperatingSystem
    Library           FastbootLibrary.py
    Library           TestContentLibrary.py

    Variables         RobotVariables.py
    Variables         SwVariables.py

    *** Test Cases ***

    [Setup]
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe  test
        Setup content  ${inputDutState}    ${inputSwState}

    Authentication
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        # Normal test
        Authenticate challenge    ${CHALLENGE FILE}
        Response should be    OKAY
        Send Challenge To Secs    ${CHALLENGE FILE}    ${RESPONSE FILE}
        Authenticate response    ${RESPONSE FILE}
        Response should be    OKAY
        # Negative test: invalid syntax for challenge
        Bad authenticate challenge    ${CHALLENGE FILE}
        Response should be    FAIL
        # Negative test: invalid syntax for response
        Bad authenticate response    ${RESPONSE FILE}
        Response should be    FAIL

    Authentication level
        [Tags]    tama  nile  ganges  kumano  huaihe
        # Negative test: invalid level
        Authenticate challenge    ${CHALLENGE FILE}    2
        Response should be    FAIL
        # Negative test: invalid response file
        Authenticate challenge    ${CHALLENGE FILE}    0
        Response should be    OKAY
        Authenticate response    ${RESPONSE FILE}
        Response should be    FAIL

    Check flashloader version
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Getvar   Loader-version
        Response should be            OKAY
        Compare range    ${gFastbootResponse.value}    ${ContentId.TC_GETVAR_MIN_XFL_VERSION}    ${ContentId.TC_GETVAR_MAX_XFL_VERSION}    ${VariantId.TCV_VALID}

    Check bootloader version
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Getvar   version-bootloader
        Response should be            OKAY
        Compare version               ${gFastbootResponse.value}    ${ContentId.TC_GETVAR_VERSION_BOOTLOADER}    ${VariantId.TCV_VALID}

    Check fastboot variables
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        [Template]    Fastboot variable
        version                            OKAY    ${ContentId.TC_GETVAR_VERSION}                   ${VariantId.TCV_VALID}
        max-download-size                  OKAY    ${ContentId.TC_GETVAR_MAX_DOWNLOAD_SIZE}         ${VariantId.TCV_VALID}
        Version-sony                       OKAY    ${ContentId.TC_GETVAR_VERSION_SONY}              ${VariantId.TCV_VALID}
        USB-version                        OKAY    ${ContentId.TC_GETVAR_USB_VERSION}               ${VariantId.TCV_VALID}
        serialno                           OKAY    ${ContentId.TC_GETVAR_SERIAL}                    ${VariantId.TCV_VALID}
        version-baseband                   OKAY    ${ContentId.TC_GETVAR_VERSION_BASEBAND}          ${VariantId.TCV_VALID}
        product                            OKAY    ${ContentId.TC_GETVAR_PRODUCT}                   ${VariantId.TCV_VALID}
        Phone-id                           OKAY    ${ContentId.TC_GETVAR_PHONE_ID}                  ${VariantId.TCV_VALID}
        Rooting-status                     OKAY    ${ContentId.TC_GETVAR_ROOTING_STATUS}            ${VariantId.TCV_VALID}
        Device-id                          OKAY    ${ContentId.TC_GETVAR_DEVICE_ID}                 ${VariantId.TCV_VALID}
        Platform-id                        OKAY    ${ContentId.TC_GETVAR_PLATFORM_ID}               ${VariantId.TCV_VALID}
        Frp-partition                      OKAY    ${ContentId.TC_GETVAR_FRP_PARTITION}             ${VariantId.TCV_VALID}
        secure                             OKAY    ${ContentId.TC_GETVAR_SECURE}                    ${VariantId.TCV_VALID}
        Sector-size                        OKAY    ${ContentId.TC_GETVAR_SECTOR_SIZE}               ${VariantId.TCV_VALID}
        Keystore-counter                   OKAY    ${ContentId.TC_GETVAR_KEYSTORE_COUNTER}          ${VariantId.TCV_VALID}
        Sake-root                          OKAY    ${ContentId.TC_GETVAR_SAKE_ROOT}                 ${VariantId.TCV_VALID}
        Default-security                   OKAY    ${ContentId.TC_GETVAR_DEFAULT_SECURITY}          ${VariantId.TCV_VALID}
        S1-root                            OKAY    ${ContentId.TC_GETVAR_S1_ROOT}                   ${VariantId.TCV_VALID}
        Security-state                     OKAY    ${ContentId.TC_GETVAR_SECURITY_STATE}            ${VariantId.TCV_VALID}

    Check fastboot variables A/B support
        [Tags]    tama  nile  ganges  kumano  huaihe
        [Template]    Fastboot variable
        Keystore-xcs                       OKAY    ${ContentId.TC_GETVAR_KEYSTORE_XCS}              ${VariantId.TCV_VALID}
        Stored-security-state              OKAY    ${ContentId.TC_GETVAR_STORED_SECURITY_STATE}     ${VariantId.TCV_VALID}
        Battery                            OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        slot-count                         OKAY    ${ContentId.TC_GETVAR_SLOT_COUNT}                ${VariantId.TCV_VALID}
        current-slot                       OKAY    ${ContentId.TC_GETVAR_CURRENT_SLOT}              ${VariantId.TCV_VALID}
        slot-unbootable:a                  OKAY    ${ContentId.TC_GETVAR_SLOT_UNBOOTABLE}           a
        slot-unbootable:b                  OKAY    ${ContentId.TC_GETVAR_SLOT_UNBOOTABLE}           b
        slot-unbootable:c                  FAIL    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        slot-successful:a                  OKAY    ${ContentId.TC_GETVAR_SLOT_SUCCESSFUL}           a
        slot-successful:b                  OKAY    ${ContentId.TC_GETVAR_SLOT_SUCCESSFUL}           b
        slot-successful:c                  FAIL    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        slot-retry-count:a                 OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        slot-retry-count:b                 OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        slot-retry-count:c                 FAIL    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:system                    OKAY    ${ContentId.TC_GETVAR_HAS_SLOT}                  system
        has-slot:userdata                  OKAY    ${ContentId.TC_GETVAR_HAS_SLOT}                  userdata

    Check fastboot variables A/B support
        [Tags]    yoshino
        [Template]    Fastboot variable
        slot-count                         OKAY    ${ContentId.TC_GETVAR_SLOT_COUNT}                ${VariantId.TCV_VALID}

    Check fastboot variables kumano huaihe
        [Tags]    kumano  huaihe
        [Template]    Fastboot variable
        Has-been-unlocked                  OKAY    ${ContentId.TC_GETVAR_HAS_BEEN_UNLOCKED}         ${VariantId.TCV_VALID}

    Check slots common
        [tags]    nile  ganges  tama  kumano  huaihe
        [Template]    Fastboot variable
        has-slot:toolsfv                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:ssd                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:appslog                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:hyp                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:ddr                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:vendor                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:keymaster                 OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:modemst1                  OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:modem                     OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:cmnlib64                  OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:sec                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:TA                        OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:fsg                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:dsp                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:fsc                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:msadp                     OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:xflkeystore               OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:misc                      OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:rdimage                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:rddata                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:tzxflattest               OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:limits                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:persist                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:frp                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:tz                        OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:tzxfl                     OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:logfs                     OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:devinfo                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:diag                      OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:oem                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:abl                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:cmnlib                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:modemst2                  OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:bluetooth                 OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:devcfg                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:apdp                      OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:LTALabel                  OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:cdt                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:boot                      OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:xfl                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:xflkeystorebak            OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:keystore                  OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:xbl                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots (nile,ganges)
        [tags]    nile  ganges
        [Template]    Fastboot variable
        has-slot:sti                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:splash                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:dpo                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:dip                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:storsec                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:pmic                      OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:rpm                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots (nile)
        [tags]    nile
        [Template]    Fastboot variable
        has-slot:mdtp                      OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:mdtpsecapp                OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots (nile,ganges,tama)
        [tags]    nile  ganges  tama
        [Template]    Fastboot variable
        has-slot:fsmetadata                OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots (nile,tama)
        [tags]    nile  tama
        [Template]    Fastboot variable
        has-slot:Qnovo                     OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots (kumano)
        [tags]    kumano  huaihe
        [Template]    Fastboot variable
        has-slot:bootloader                OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:uefivarstore              OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:uefisecapp                OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:multiimgoem               OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:storsec                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:secdata                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:metadata                  OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots (tama kumano)
        [tags]    tama  kumano  huaihe
        [Template]    Fastboot variable
        has-slot:qupfw                     OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:dtbo                      OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:logdump                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:aop                       OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:spunvm                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:vbmeta                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:xbl_config                OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots (ganges VB2)
        [tags]    ganges-vb2
        [Template]    Fastboot variable
        has-slot:dtbo                      OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:vbmeta                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots softbank
        [tags]    softbank
        [Template]    Fastboot variable
        has-slot:carrier                   OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check slots kumano_plus
        [tags]    kumano_plus
        [Template]    Fastboot variable
        has-slot:mdm1m9kefs1               OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:mdm1m9kefs2               OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:mdm1m9kefs3               OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:mdm1m9kefsc               OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}
        has-slot:mdmddr                    OKAY    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check fastboot variables ufs
        [Tags]    yoshino  tama  kumano
        [Template]    Fastboot variable
        Ufs-info                           OKAY    ${ContentId.TC_GETVAR_UFS_INFO}                  ${VariantId.TCV_VALID}

    Check fastboot variables rollback index count
        [Tags]    nile  ganges  tama  kumano
        [Template]    Fastboot variable
        Rollback-index-count               OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX_COUNT}      ${VariantId.TCV_VALID}

    Check fastboot variables rollback counters
        [Tags]    tama  kumano  ganges-vb2
        [Template]    Fastboot variable
        Rollback-index:0                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            0
        Rollback-index:1                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            1
        Rollback-index:2                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            2
        Rollback-index:3                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            3
        Rollback-index:4                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            4
        Rollback-index:5                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            5
        Rollback-index:6                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            6
        Rollback-index:7                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            7
        Rollback-index:8                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            8
        Rollback-index:9                   OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            9
        Rollback-index:10                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            10
        Rollback-index:11                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            11
        Rollback-index:12                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            12
        Rollback-index:13                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            13
        Rollback-index:14                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            14
        Rollback-index:15                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            15
        Rollback-index:16                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            16
        Rollback-index:17                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            17
        Rollback-index:18                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            18
        Rollback-index:19                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            19
        Rollback-index:20                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            20
        Rollback-index:21                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            21
        Rollback-index:22                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            22
        Rollback-index:23                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            23
        Rollback-index:24                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            24
        Rollback-index:25                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            25
        Rollback-index:26                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            26
        Rollback-index:27                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            27
        Rollback-index:28                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            28
        Rollback-index:29                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            29
        Rollback-index:30                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            30
        Rollback-index:31                  OKAY    ${ContentId.TC_GETVAR_ROLLBACK_INDEX}            31
        Rollback-index:32                  FAIL    ${ContentId.DO_NOT_CARE}                         ${VariantId.TCV_VALID}

    Check partition-info tama
        [Tags]    tama
        Fastboot variable  partition-type:system_a  OKAY  ${ContentId.TC_GETVAR_PARTITION_TYPE}  system_a
        Fastboot variable  partition-size:system_a  OKAY  ${ContentId.TC_GETVAR_PARTITION_SIZE}  system_a

    Check partition-info ganges-vb1
        [Tags]    ganges-vb1
        [Template]    Partition info
        boot
        system
        vendor
        oem

    Check partition-info
        [Tags]    kumano  huaihe  ganges-vb2
        [Template]    Partition info
        boot
        dtbo
        system
        vendor
        oem
        vbmeta

    # need a separate test case for userdata since it is slot-less
    Check partition-info userdata
        [Tags]    tama  kumano  huaihe  ganges
        [Template]    Fastboot variable
        partition-type:userdata            OKAY    ${ContentId.TC_GETVAR_PARTITION_TYPE}            userdata
        partition-size:userdata            OKAY    ${ContentId.TC_GETVAR_PARTITION_SIZE}            userdata

    Check fastboot variables emmc
        [Tags]    nile  ganges
        [Template]    Fastboot variable
        Emmc-info                          OKAY    ${ContentId.TC_GETVAR_UFS_INFO}                  ${VariantId.TCV_VALID}

    Check fastboot variable X-conf
        [Tags]    kumano  huaihe
        [Template]    Fastboot variable
        X-conf                             OKAY    ${ContentId.TC_GETVAR_X_CONF}                    ${VariantId.TCV_VALID}

    Check invalid fastboot variable
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Getvar   invalid    FAIL
        Response should be                 FAIL

    # 'Test getvar all' has to be executed after all other 'getvar' commands
    Test getvar all
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Getvar all
        Check if response from getvar all is okay
        Check if all tested vars are in getvar all
        Check if all vars in getvar all are tested

    Format TA partitions
        [Tags]    yoshino  tama  nile  ganges
        Backup TA
        Format TA    1
        Response should be    OKAY
        Format TA    2
        Response should be    OKAY
        Format TA    3
        Response should be    FAIL
        Format TA
        Response should be    OKAY
        Restore TA

    Format TA partitions
        [Tags]    kumano  huaihe
        Backup TA
        Format TA    1
        Response should be    OKAY
        Format TA    2
        Response should be    OKAY
        Format TA    3
        Response should be    OKAY
        Format TA    10
        Response should be    FAIL
        Format TA    A
        Response should be    FAIL
        Format TA
        Response should be    FAIL
        Restore TA

    Test TA units
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        [Template]    Test TA unit
        2    2473
        2    4130
        1    4

    Read TA partitions
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        [Template]    Read TA partition
        1
        2

    Check partition table
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Get partition list    ${TEMP PARTITIONS FILE}
        Response should be    OKAY
        Compare file list  ${TEMP PARTITIONS FILE}  ${ContentId.TC_PARTITION_TABLE}  ${VariantId.TCV_VALID}

    Erase partitions
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Backup TA
        Erase partition    TA
        Restore TA

    Flash images
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        # Restore TA will test the flash command
        # This should be extended with images in sparse format
        Backup TA
        Restore TA

    Sync command
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Sync
        Response should be    OKAY

    Read partitions
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Get partition list    ${TEMP PARTITIONS FILE}
        Response should be    OKAY
        # Read all partitions, this takes a long time...
        #@{PLIST} =    Create List From CSV    ${TEMP PARTITIONS FILE}
        #:FOR    ${partition}    IN    @{PLIST}
        #\    Read Image     ${partition}    ${TEMPDIR}${/}${partition}.img

    Get log file
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Get log    ${LOADER LOG FILE}
        Response should be    OKAY

    Get security properties
        [Tags]    yoshino  tama  nile  ganges
        Get security    ${TEST FILE}
        Response should be    OKAY

    Get root key
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Get root key hash    ${TEST FILE}
        Response should be    OKAY

    Repartition negative tests
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        # Check invalid LUN
        Repartition   7
        Response should be    FAIL
        Repartition   a
        Response should be    FAIL

    Signature test
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Get file name    ${ContentId.TC_SIGNATURE_FILE}    ${VariantId.TCV_INVALID}
        Signature       ${gTCV.filename}
        Response should be    FAIL
        Get file name    ${ContentId.TC_SIGNATURE_FILE}
        Signature       ${gTCV.filename}
        Response should be    OKAY

        # Signature command when data is downloaded first
        Get file name    ${ContentId.TC_SIGNATURE_FILE}    ${VariantId.TCV_INVALID}
        Download        ${gTCV.filename}
        Response should be    OKAY
        Signature
        Response should be    FAIL
        Get file name    ${ContentId.TC_SIGNATURE_FILE}
        Download        ${gTCV.filename}
        Response should be    OKAY
        Signature
        Response should be    OKAY

    Charge command test
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Charge    20
        Response should be    OKAY
        Charge    40
        Response should be    OKAY
        Charge    80
        Response should be    OKAY
        Charge    120
        Response should be    FAIL
        Charge    60
        Response should be    OKAY

    Get UFS information
        [Tags]    yoshino  tama  kumano
        Get UFS info    ${TEST FILE}
        Response should be    OKAY

    Get EMMC information
        [Tags]    nile  ganges  huaihe
        Get emmc info    ${TEST FILE}
        Response should be    OKAY

    Set active slot
        [Tags]    tama  nile  ganges  kumano  huaihe
        Set active    a
        Response should be    OKAY
        Set active    b
        Response should be    OKAY
        Set active    a
        Response should be    OKAY
        Set active    c
        Response should be    FAIL
        Set active    0
        Response should be    FAIL

    Reset rollback counters
        [Tags]    tama  nile  ganges  kumano  huaihe
        Reset rollback counter
        Response should be    OKAY

    Reset frp
        [Tags]    kumano  huaihe
        Reset frp
        Response should be    OKAY

    Command reboot
        [Tags]    yoshino  tama  nile  ganges
        # Reboot into Xperia Flash Loader, recovery might be entered in between
        Reboot
        Response should be    OKAY
        Wait for fastboot device

    Command reboot
        [Tags]    kumano  huaihe
        # Reboot into Android SW
        Reboot
        Response should be    OKAY
        adb wait for device
        # Now return to Xperia Flash Loader
        adb reboot into xfl
        Wait for fastboot device

    Command reboot bootloader
        [Tags]    kumano  huaihe
        # Reboot into Xperia Flash Loader, recovery might be entered in between
        Reboot bootloader
        Response should be    OKAY
        Wait for fastboot device

    Command Reboot-bootloader
        [Tags]    kumano  huaihe
        # Reboot into vendor fastboot
        Reboot bootloader vendor
        Response should be    OKAY
        Wait for fastboot device
        getvar    product
        Response should be    No d    # No device found
        Vendor getvar    product
        Response should be    OKAY
        # Now return to Xperia Flash Loader
        Vendor continue cmd
        Response should be    OKAY
        adb wait for device
        adb reboot into xfl
        Wait for fastboot device

    Command continue
        [Tags]    yoshino  tama  nile  ganges  kumano  huaihe
        Continue cmd
        Response should be    OKAY
        # Phone should start up with Android SW
        adb wait for device

    *** Keywords ***

    Partition info
        [Arguments]    ${partition}
        Fastboot variable  partition-type:${partition}_a  OKAY  ${ContentId.TC_GETVAR_PARTITION_TYPE}  ${partition}_a
        Fastboot variable  partition-size:${partition}_a  OKAY  ${ContentId.TC_GETVAR_PARTITION_SIZE}  ${partition}_a
        Fastboot variable  partition-type:${partition}_b  OKAY  ${ContentId.TC_GETVAR_PARTITION_TYPE}  ${partition}_b
        Fastboot variable  partition-size:${partition}_b  OKAY  ${ContentId.TC_GETVAR_PARTITION_SIZE}  ${partition}_b

    Fastboot variable
        [Arguments]    ${variable}    ${expected response}    ${content id}    ${variant}
        Getvar   ${variable}    ${expected response}
        Response should be            ${expected response}
        Compare content               ${gFastbootResponse.value}     ${content_id}    ${variant}

    Backup TA
        Read Image    TA    ${TA BACKUP FILE}
        Response should be    OKAY

    Restore TA
        Flash Image    TA    ${TA BACKUP FILE}
        Response should be    OKAY

    Read image
        [Arguments]    ${partition}    ${image_file}
        Read partition    ${partition}    ${image_file}
        Response should be    OKAY

    Flash image
        [Arguments]    ${partition}    ${image}
        Flash    ${partition}    ${image}
        Response should be    OKAY
        Digest    ${partition}    ${TEST FILE}
        Response should be    OKAY
        #Calculate SHA256    ${image}    ${TEST2 FILE}
        #Data should be    ${TEST2 FILE}    ${TEST FILE}

    Test TA unit
        [Arguments]    ${partition}    ${unit}
        # Save old data
        # Create random data in case the unit does not exist
        Create random TA data    ${TEMP FILE}
        Read TA    ${partition}    ${unit}    ${TEMP FILE}
        # The unit might not exist, but we don't care
        Create random TA data    ${RANDOM TA FILE}
        Write TA    ${partition}    ${unit}    ${RANDOM TA FILE}
        Response should be    OKAY
        Read TA    ${partition}    ${unit}    ${TEST FILE}
        Response should be    OKAY
        Data should be    ${RANDOM TA FILE}    ${TEST FILE}
        # Restore old value
        Write TA    ${partition}    ${unit}    ${TEMP FILE}
        Response should be    OKAY
        Read TA    ${partition}    ${unit}    ${TEST FILE}
        Response should be    OKAY

    Read TA partition
        [Arguments]    ${partition}
        Read All TA    ${partition}    ${TEST FILE}
        Response should be    OKAY

    Erase partition
        [Arguments]    ${partition}
        Erase    ${partition}
        Response should be    OKAY

    *** Variables ***

    ${CHALLENGE FILE}        ${TEMPDIR}${/}challenge.bin
    ${RESPONSE FILE}         ${TEMPDIR}${/}response.bin
    ${TEST FILE}             ${TEMPDIR}${/}test.bin
    ${TEMP FILE}             ${TEMPDIR}${/}temp.bin
    ${TA BACKUP FILE}        ${TEMPDIR}${/}TA_backup.img
    ${TEMP PARTITIONS FILE}  ${TEMPDIR}${/}partitions.txt
    ${RANDOM TA FILE}        ${TEMPDIR}${/}random_ta.bin
    ${LOADER LOG FILE}       ${TEMPDIR}${/}log.bin
