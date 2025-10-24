pushd %~dp0
 python phy_cov.py -i kailua_xbl_usb_dp.txt -o Default_xbl_usb_dp -pr="HWIO_USB3_DP_PHY" -po="ADDR" -s=0 -c=0 -d 0
 python phy_cov.py -i kailua_xbl_usb_dp.txt -o DFT_xbl_usb_dp -pr="HWIO_USB3_DP_PHY" -po="ADDR" -s=0 -c=0 -d 1
popd
pause