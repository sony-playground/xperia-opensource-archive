========================
Xflattest TZ Application
========================

Xflattest is a TrustZone application used primary by the Xboot for publishing
security information. The information published varies on whether the image
started by the Xboot is XFL [#xfl_sec_data]_ or application SW [#sec_data]_.

Xflattest should store this information in RPMB, or in a local allocated buffer,
depending on the platform and the command being used. If RPMB is not provisioned
the app can keep this info in a local allocated buffer. The app should be able to retain
the info until the next reboot, when the Xboot will publish the data again.
The format and content of the data is not known or parsed by xflattest. The
calling client should parse and handle the data.

By design on QCM platforms xflattest is loaded and started by the Xboot and
it should not be unloaded from TrustZone when the HLOS is started, for example
see [#xflattest_kernel_patch]_

Xflattest creates an RPMB partition with size of 4 sectors. The size of the sector
is platform dependent, QCM has 512 bytes per sector.

  Sector 0
    Reserved for XFLATTEST_CMD_SET_RPMB_SECTOR and XFLATTEST_CMD_GET_RPMB_SECTOR commands.
  Sector 1
    Reserved for xfl_sec_data. If more than 512 bytes are needed the storage for the
    xfl_sec_data should be increased with sector 2 and 3.
  Sector 2 and 3
    Reserved for future use.

Source code for the app is located in platform/vendor/sony/tzapp-xflattest git:
http://review.sonyericsson.net/plugins/gitiles/platform/vendor/sony/tzapp-xflattest

Command reference
-----------------
The application supports several commands for storing and reading data. The
commands are defined in xflattest.h [#xflattest_commands]_

  XFLATTEST_CMD_SET_SEC_DATA
    Used for storing the sec_data structure. The data is stored in a local buffer.
    This command should be called from Xboot and can be called only once per restart.
    It will blow a SW fuse (QSEE_SONYTZAPPXFL_LOADED_FUSE) on the first run and any
    subsequent calls to the command will fail. This is done to protect the data from
    modification from HLOS.

  XFLATTEST_CMD_GET_SEC_DATA
    Should be called from another TZ app to get the security information stored by the
    Xboot. Used for getting the data stored by XFLATTEST_CMD_SET_SEC_DATA. It will fail if
    QSEE_SONYTZAPPXFL_LOADED_FUSE fuse is not blown, which indicated that there is
    no data stored.

  XFLATTEST_CMD_SET_XFL_SEC_DATA
    Used for storing the xfl_sec_data. If RPMB is provisioned the data will be written in
    sector 1 from the xflattest RPMB partition. It will return an error if
    the QSEE_SONYTZAPPXFL_RPMB_FUSE SW fuse is blown.

  XFLATTEST_CMD_GET_RAW_SEC_DATA
    Should be called from HLOS to get the security information stored by the Xboot. It
    can be called to get the sec_data or xfl_sec_data, depending on the input parameter
    provided (0 for sec_data, 1 for xfl_sec_data)

  XFLATTEST_CMD_LOCK_RPMB
    Will blow the SW fuse QSEE_SONYTZAPPXFL_RPMB_FUSE. This fuse is used to restrict
    write access to RPMB by other commands.

  XFLATTEST_CMD_SET_RPMB_SECTOR
    Currently not used by any client. Can be used to write data to sector 0 in the
    xflattest RPMB partition. It will return an error if the QSEE_SONYTZAPPXFL_RPMB_FUSE
    SW fuse is blown.

  XFLATTEST_CMD_GET_RPMB_SECTOR
    Currently not used by any client. Can be used to read data from sector 0 from
    xflattest RPMB partition.

  XFLATTEST_CMD_CLR_RPMB_SECTOR
    Can be used to clear the data from any sector in the xflattest RPMB partition.
    It will return an error if the QSEE_SONYTZAPPXFL_RPMB_FUSE SW fuse is blown.

Usage example sequence diagrams
-------------------------------

Android and XFL usage examples:

.. uml::
  :caption: sec_data Android example

  @startuml
  activate Xboot
  Xboot -> xflattest: Load and start xflattest app
  return done
  activate xflattest
  Xboot -> xflattest: XFLATTEST_CMD_SET_SEC_DATA
  xflattest -> xflattest: store data in local buffer
  xflattest -> xflattest: blow QSEE_SONYTZAPPXFL_LOADED_FUSE
  xflattest --> Xboot: OK
  Xboot -> xflattest: XFLATTEST_CMD_LOCK_RPMB
  xflattest -> xflattest: blow QSEE_SONYTZAPPXFL_RPMB_FUSE
  xflattest --> Xboot: OK
  Xboot -> Android: Load and start HLOS (Android)
  activate Android
  deactivate Xboot
  Android -> xflattest: XFLATTEST_CMD_GET_RAW_SEC_DATA
  xflattest --> Android: return stored data
  deactivate Android
  deactivate xflattest
  @enduml

.. uml::
  :caption: xfl_sec_data XFL example

  @startuml
  activate Xboot
  Xboot -> xflattest: Load and start xflattest app
  return done
  activate xflattest
  Xboot -> xflattest: XFLATTEST_CMD_SET_XFL_SEC_DATA
  xflattest -> xflattest: store data in RPMB or local buffer
  xflattest --> Xboot: OK
  Xboot -> xflattest: XFLATTEST_CMD_LOCK_RPMB
  xflattest -> xflattest: blow QSEE_SONYTZAPPXFL_RPMB_FUSE
  xflattest --> Xboot: OK
  Xboot -> XFL: Load and start HLOS (XFL)
  activate XFL
  deactivate Xboot
  XFL -> xflattest: XFLATTEST_CMD_GET_RAW_SEC_DATA
  xflattest --> XFL: return stored data
  deactivate XFL
  deactivate xflattest
  @enduml

Data Flow Diagram
=================

.. graphviz::

	digraph dfd_qc_sec_data {
		label="Data Flow Diagram for security data, Qualcomm"
		node[shape=record]
		subgraph level0 {
			Host [label="Host", shape=box,
			 style=filled,  fillcolor=green, fontname="Arial"];
		}
	subgraph cluster_device {
		label="Device";
		graph[style=dashed];
		XFL	[label="Flash Loader\nXFL", shape=ellipse,
			 style=filled,  fillcolor=yellow, fontname="Arial"];
		XBoot	[label="Bootloader\nXBoot", shape=ellipse,
			 style=filled,  fillcolor=yellow, fontname="Arial"];
		AND	[label="Android", shape=ellipse,
			 style=filled,  fillcolor=yellow, fontname="Arial"];
		TzXfl	[label="TzXflAttest", shape=ellipse,
			 style=filled,  fillcolor=yellow, fontname="Arial"];
		RPMB	[label="RPMB", shape=box,
			 style=filled,  fillcolor=lightblue, fontname="Arial"];
		MiscTA	[label="MiscTA (2335)\n(unfused device)", shape=box,
			 style=filled,  fillcolor=lightblue, fontname="Arial"];
	}
	Host -> XFL [dir=both, label="Fastboot command"]
	XFL -> TzXfl [dir=both]
	XBoot -> TzXfl [dir=both]
	TzXfl -> AND
	TzXfl -> RPMB [dir=both]
	XFL -> MiscTA [dir=both]
	XBoot -> MiscTA [dir=both]
	}


.. graphviz::

	digraph dfd_mtk_sec_data {
		label="Data Flow Diagram for security data, MediaTek"
		node[shape=record]
		subgraph level0 {
			Host [label="Host", shape=box,
			 style=filled,  fillcolor=green, fontname="Arial"];
		}
	subgraph cluster_device {
		label="Device";
		graph[style=dashed];
		XFL	[label="Flash Loader\nXFL", shape=ellipse,
			 style=filled,  fillcolor=yellow, fontname="Arial"];
		XBoot	[label="Bootloader\nXBoot", shape=ellipse,
			 style=filled,  fillcolor=yellow, fontname="Arial"];
		AND	[label="Android", shape=ellipse,
			 style=filled,  fillcolor=yellow, fontname="Arial"];
		TzXfl	[label="TzXflAttest", shape=ellipse,
			 style=filled,  fillcolor=yellow, fontname="Arial"];
		RPMB	[label="RPMB", shape=box,
			 style=filled,  fillcolor=lightblue, fontname="Arial"];
	}
	Host -> XFL [dir=both, label="Fastboot command"]
	XFL -> TzXfl [dir=both]
	XBoot -> RPMB [dir=both]
	TzXfl -> AND
	TzXfl -> RPMB [dir=both]
	}


.. rubric:: Footnotes

.. [#sec_data] sec_data struct: http://review.sonyericsson.net/plugins/gitiles/platform/vendor/semc/fs/main/+/master/integration/common/include/xflattest.h#114
.. [#xfl_sec_data] xfl_sec_data struct: http://review.sonyericsson.net/plugins/gitiles/platform/vendor/semc/fs/main/+/master/integration/common/include/xflattest.h#146
.. [#xflattest_kernel_patch] xflattest kernel patch: http://review.sonyericsson.net/#/c/1840058/
.. [#xflattest_commands] xflattest commands http://review.sonyericsson.net/plugins/gitiles/platform/vendor/semc/fs/main/+/master/integration/common/include/xflattest.h#8
