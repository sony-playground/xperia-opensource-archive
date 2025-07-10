pushd %~dp0
 python phy_cov.py -i fillmore_xbl_usb_dp.txt -o fillmore_xbl_usb_dp -pr="HWIO_USB3_DP_PHY" -po="ADDR" -s=0 -c=0 
popd
pause