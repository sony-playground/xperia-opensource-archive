2020-11-23:  SCons 3.1.2 Installation Procedure:

* Download SCons 3.1.2 from https://scons.org/tag/releases.html
* Unzip the file into a local directory.
* Run
** python setup.py install --no-version-script --no-install-bat --no-install-man
* This creates a folder called 'build'.  Copy the contents of this file into the SCons directory of the scons.qc.3.0 component.
* Also copy the following files from the unzipped scons.3.1.2 folder into the root of the SCons directory in the scons.qc.3.0 component:
** LICENSE.txt
** README.txt
** RELEASE.txt
* Modify !# in python scripts in the scripts directory.
* Apply reentrancy fix to lib/SCons/Node/FS.py (CL#s 24332379, 24416465 and 24497061)
* Set PICKLE_PROTOCOL to 2 in lib/SCons/compat/__init__.py (CL# 21715019)
* Enable case sensitify for Windows in lib/SCons/Util.py
* Create this file.
* Modify the following to call os.chmod() before calling os.unlink() (CL# 29732929, CR# 2908586)
