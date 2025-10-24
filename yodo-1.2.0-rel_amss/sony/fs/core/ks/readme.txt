This uses the asn1c in a "hybrid mode", generate
files from keystore asn schema, patch generated files (if necessary), check in.
> sudo apt-get install asn1c
> cd generated
> asn1c ../keystore.asn
> edit generated makefile (see commit)
> Check in generated files (when compiling successfully)
