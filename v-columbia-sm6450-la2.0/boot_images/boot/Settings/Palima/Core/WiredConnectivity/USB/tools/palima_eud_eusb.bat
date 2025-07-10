pushd %~dp0
 python phy_cov.py -i palima_eud_eusb.txt -o eud_eusb -pr="HWIO_USB2PHY" -po="ADDR" -s=1 -c=0 -d=0 -e=1
popd
pause