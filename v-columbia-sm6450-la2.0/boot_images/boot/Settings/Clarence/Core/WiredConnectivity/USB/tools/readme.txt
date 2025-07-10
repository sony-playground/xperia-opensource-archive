PLEASE MAKE SURE fix all the exception at the end of log before copy to code


Instruction:
optional arguments:
  -h, --help            show this help message and exit
  -pr PREFIX, --prefix PREFIX
                        prefix for addr
  -po POSTFIX, --postfix POSTFIX
                        postfix for addr
  -t TABLE_NAME, --table_name TABLE_NAME
                        phy table name
  -o OUTPUT_TAG, --output_tag OUTPUT_TAG
                        output tag
  -i INPUT, --input INPUT    //if not provide, use usb_phy.txt in the same folder
                        input_name
  -n INDEX_FLAG, --index_flag INDEX_FLAG
                        attach index at the end
  -c COMMENT_FLAG, --comment_flag COMMENT_FLAG
                        attach comment
  -s SEPARATE_FLAG, --separate_flag SEPARATE_FLAG
                        separate address and data

Output contain PBL (sepereate every 4 line) or HLOS version 


sample output:
2019-04-30_kona_DP_SS_table_v4_phy_tune.out
2019-04-30_kona_uni_table_phy_tune.out

Sample cmd:
python phy_cov.py -i kona_USB_SS_DP_v4.txt -o kona_DP_SS_table_v4 -pr="HWIO_USB3_DP_PHY_USB3" -po="ADDR"
python phy_cov.py -i kona_uni_usb_ss.txt -o kona_uni_table -pr="HWIO_USB3_UNI_PHY" -po="ADDR"

The old version (address_table & value_table):
python phy_cov.py -i kona_USB_SS_DP_v4.txt -o kona_DP_SS_table_v4_sep -pr="HWIO_USB3_DP_PHY_USB3" -po="ADDR" -s=1
python phy_cov.py -i kona_uni_usb_ss.txt -o kona_uni_table_sep -pr="HWIO_USB3_UNI_PHY" -po="ADDR" -s=1