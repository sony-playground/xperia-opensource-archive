======================
Software Architecture
======================

Software Components
===================

.. graphviz::

   digraph comp {
      color=black;
      XF [label="XFL (userspace)", shape=box, fillcolor=green, style=filled,
          fontname="Arial"];
      C  [label="Charging", shape=box, fillcolor=lightblue, style=filled,
           fontname="Arial"];
      D  [label="Display (optional)", shape=box, fillcolor=lightblue,
          style=filled, fontname="Arial"];
      F  [label="Flash block devices", shape=box, fillcolor=lightblue,
          style=filled, fontname="Arial"];
      U  [label="USB Gadget", shape=box, fillcolor=lightblue, style=filled,
          fontname="Arial"];
      L  [label="Linux kernel", shape=box, fillcolor=lightblue, style=filled,
          fontname="Arial"];
      Q  [label="QSEE (QC) or TEE (MTK)", shape=box, fillcolor=lightblue,
          style=filled, fontname="Arial"];
      X  [label="Xflattest (TZ app)", shape=box, fillcolor=lightblue,
          style=filled, fontname="Arial"];
      LA [label="Loader (TZ app for fusing, only QC)", shape=box,
          fillcolor=lightblue, style=filled, fontname="Arial"];
      XF -> C -> L;
      XF -> D -> L;
      XF -> U -> L;
      XF -> F -> L;
      XF -> Q;
      Q -> X;
      Q -> LA;
   }

\
\

XFL main loop
=============

.. graphviz::

   digraph main_loop {
      color=black;

      I [label="Init", shape=box, fillcolor=green, style="rounded,filled",
         fontname="Arial"];
      C [label="Initialize crypto library (mbedtls or openssl)
         Get storage descriptor for flash
         Setup TA
         Setup transfer protocol (normally USB)
         Start TZ apps\nInitialize graphics (optional)",
         shape=box, fillcolor=yellow, style="rounded,filled", fontname="Arial"];
      W [label="Wait for fastboot command",  shape=box, fillcolor=green,
         style="rounded,filled", fontname="Arial"];
      E [label="Execute fastboot command", shape=box, fillcolor=green,
         style="rounded,filled", fontname="Arial"];
      S [label="Send response", shape=box, fillcolor=green,
         style="rounded,filled", fontname="Arial"];
      I -> W;
      W -> E;
      E -> S;
      S -> W;
      I -> C [dir=none, constraint=false];
   }

\
\

XFL Linux Integration
=====================

.. graphviz::

   digraph linux_integration {
      color=black;
      H  [label="Fastboot command handler (fastboot.c)", shape=box,
          fillcolor=green, style=filled, fontname="Arial"];
      SI [label="Generic storage interface (storage.h)", shape=box,
          fillcolor=green, style=filled, fontname="Arial"];
      TI [label="Generic transport interface (transport.h)", shape=box,
          fillcolor=green, style=filled, fontname="Arial"];
      SM [label="UFS/eMMC/RAM etc
          (integration/linux/smmc.c,ufs.c,ram.c)",
          shape=box, fillcolor=green, style=filled, fontname="Arial"];
      TM [label="USB, file, pipe etc
          (integration/linux/ffs.c, tr_file.c, tr_pipe.c)",
          shape=box, fillcolor=green, style=filled, fontname="Arial"];
      H -> SI [label="Read/Write/Erase"];
      H -> TI [label="Read/Write"];
      SI -> SM;
      TI -> TM;
   }

\
\
