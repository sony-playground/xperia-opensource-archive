
$max_log_addr = "00003A0";
$min_timestamp_addr = 0;
$binary = 0;
$current_freq_seq = undef;
%translations = (
  "SIGNALS"  => "Signals Received        ",
  "SIGNALS "  => "Signals Received        ",
  "  ISR   " => "ISR Received            ",
  " ABORT  " => "signal_abort_isr called ",
  "TIMEOUT!" => "Service Timed Out       ",
  "WDOGBITE" => "NonSecure Watchdog Bite ",
  "Crash!!!" => "Secure Watchdog Bite    ",
  "CNOC_ON " => "BCM CNOC Callback Recvd ",
  " DDR_ON " => "BCM DDR Callback Recvd  ",
  "MMNOC_ON" => "BCM MMNOC Callback Recvd",
  "MMNOC_TO" => "MMNOC Timed Out         ",
  "DDR  OFF" => "BCM Voting DDR Off      ",
  "Enab DDR" => "BCM Voting DDR ON       ",
  "RSC_NEED" => "Vote Resource Needs     ",
  "EnaMMNoC" => "BCM Voting MMNOC On     ",
  "EnabMNOC" => "BCM Voting MMNOC On     ",
  "MMNOCOFF" => "BCM Voting MMNOC Off    ",
  "MMNoCOFF" => "BCM Voting MMNOC Off    ",
  "CNOC OFF" => "BCM Voting CNOC Off     ",
  "EnabCNOC" => "BCM Voting CNOC On      ",
  "SERV_PTR" => "Initialized: PTR value  ",
  "SERV_CNT" => "Initialized: Count Value",
  "QUP/MMNC" => "Service:QUP/MMNC        ",
  "CXC_LOCK" => "Service:CX Collapse Lock",
  "CXC_UNLK" => "Service:CX CollapseUnLk ",
  "DBG_LOCK" => "Service:Dbg Res Lock    ",
  "DBG_UNLK" => "Service:Dbg Res Unlock  ",
  "TEST_CMD" => "Service:Test Command    ",
  "WATCHDOG" => "Service:NonSecure W_DOG ",
  "CrashDMP" => "Service:Secure WatchDog ",
  "BCM_CHNG" => "Service:BCM Change Done ",
  "PDC_WA"   => "Service:PDC Workaround  ",
  "JTAG_ON " => "Service:JTAG Connected  ",
  "JTAG_OFF" => "Service:JTAG Disconnect ",
  "SYS_IDLE" => "Service:System at Idle  ",
  "LCX_PRE " => "Service:LPI_CX Prework  ",
  "LCX_POST" => "Service:LPI_CX Postwork ",
  "DDR_WA  " => "Service:DDR Workaround  ",
  "UPD_SDPM" => "Service:Update SDPM     ",
  "PDC_GLOB" => "Service:PDC Global Chng ",
  "ICBASYNC" => "Service:ICB ASynComplete",
  "DDR_LOG " => "Service:Save DDR Seq    ",
  "PDC_IRQ " => "PDC Change Done         ",
  "CRASH!!!" => "In do_crash_dump        ",
  " WAITING" => "Service pending resource",
  "IDLE_CHK" => "Checking system idleness",
  "AOPABORT" => "AOP Initiated Abort     ",
  "SERVDONE" => "Service:Completed       ",
  "AOP_TIME" => "Service:AOP TimerService",
  "GPO_BIT " => "Debug Bit31 (GPI_BIT)   ",
  "SDPM LVL" => "SDPM Level              ",
  "PMU_WORK" => "Service:PMU Workaround  ",
  "PMUWORK1" => "PMU Workaround Address  ",
  "PMUWORK2" => "PMU Workaround Data     ",
  "PMU_ERR " => "Service:PMU Error       ",
  "CRASHIST" => "force_aop_abort history ",
  "AbortREQ" => "Service Requesting Abort",
  "EnabDDR " => "DDR Resource voted on   ",
  "DDR VOTE" => "About to Enable ICB Rte ",
);


sub relative
{
   $last = shift;
   $first = shift;
   $rel = int(($last - $first) / 19.2);
   $units = " us";
   if ($rel >= 100000)
   {
      $rel = $rel / 1000;
      if ($rel >= 1000) {
         $rel = int($rel+0.5)/1000;
         $units = " sec";
      } else {
         $rel = int($rel+0.5);
         $units = " ms";
      }
   }
   return "$rel" . "$units";
}

sub flip
{
   $str = $_[0];
   if ($str =~ m/(..)(..)/)
   {
     return $2 . $1;
   }
}
sub parse_fields
{
  $count = $_[0];
  $line = $_[1];
  #       8 2   41   41   41   41   41  341123411234121234123456781234
  #00000000: 4fff a205 4d61 696e 4c6f 6f70 0430 0000  O...MainLoop.0..
  #0000000: 90a8 5c49 4152 4320 434f 4e54 0001 0100  ..\IARC CONT....]
  if ($line =~ m/([0-9a-f]+)..([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4})......(........)/i)
  {
    return 0 if ((hex($1) & hex('fff')) > hex($max_log_addr));
    $log_msgs[$count]{addr}      = $1;
    $log_msgs[$count]{timestamp} = flip($3) . flip($2);
    $log_msgs[$count]{msg1}      = flip($5) . flip($4);
    $log_msgs[$count]{msg2}      = flip($7) . flip($6);
    $log_msgs[$count]{data}      = flip($9) . flip($8);
    $6 =~ m/ *([\w \!\/]+) */;
    $str = $1;
    if (defined($translations{$10}))
    {
      $log_msgs[$count]{msg_text} = $translations{$10};
    }
    else
    {
      $log_msgs[$count]{msg_text} = $10 . " " x (24-length($10));
    }
    return 1;
  }
  elsif ($line =~ m/([0-9A-F]{8})..([0-9A-F]{8}).([0-9A-F]{8}).([0-9A-F]{8}).([0-9A-F]{8}).....(........)/i)
  {
    return 0 if ((hex($1) & hex("FFF")) > hex($max_log_addr));
    $log_msgs[$count]{addr}      = $1;
    $log_msgs[$count]{timestamp} = $2;
    $log_msgs[$count]{msg1} =      $3;
    $log_msgs[$count]{msg2} =      $4;
    $log_msgs[$count]{data} =      $5;
    $6 =~ m/([\w \!\/]+)/;
    $str = $1;
    if (defined($translations{$str}))
    {
      $log_msgs[$count]{msg_text} = $translations{$str};
    }
    else
    {
      $log_msgs[$count]{msg_text} = $str . " " x (24-length($6));
    }
    return 1;
  }
  else
  {
    print "No: [$line]\n";
  }
  return 0;
}

sub by_position()
{
  %hash_a = %{$a};
  %hash_b = %{$b};
  $addr1 = hex($hash_a{addr})/16;
  $addr1 += 100 if ($addr1 < $min_timestamp_addr);
  $addr2 = hex($hash_b{addr})/16;
  $addr2 += 100 if ($addr2 < $min_timestamp_addr);
  return $addr1 <=> $addr2;
}

%sigs = (
  "000001" => "BCM Workaround",
  "000002" => "CX Collapse Change",
  "000004" => "DBG Sig Lock",
  "000008" => "DBG Sig UnLock",
  "000010" => "PDC Global Change",
  "000020" => "Log Abort ISR",
  "000040" => "Crash Dump Needed",
  "000080" => "BCM Change Done",
  "000100" => "PDC Workaround",
  "000200" => "AOP Timer Service",
  "000400" => "Sys Power Change",
  "000800" => "System Idle",
  "001000" => "LPI CX Prework",
  "002000" => "PMU ERROR",
  "004000" => "GDS ERROR",
  "008000" => "ICB Async Completion",
  "010000" => "DDR Logging",
  "020000" => "Bit 17",
  "040000" => "Bit 18",
  "080000" => "Bit 19",
  "100000" => "Bit 20",
  "200000" => "Bit 21",
  "400000" => "Bit 22",
  "800000" => "Bit 23",
  "01000000" => "Bit 24",
  "02000000" => "Bit 25",
  "04000000" => "Bit 26",
  "08000000" => "Bit 27",
  "10000000" => "Bit 28",
  "20000000" => "Bit 29",
  "40000000" => "Resource Callback",
  "80000000" => "Timer Service Callback",
);

%subsystems = (
  "000002" => "HLOS",
  "000020" => "Audio",
  "000080" => "Sensors",
  "010000" => "Compute v1/Modem v2",
  "020000" => "Compute v1/Modem v2",
  "040000" => "Modem v1/Compute v2",
  "080000" => "Modem v1/Compute v2",
  "F0FF5D" => "Invalid"
);

sub decode_resource
{
  $code = hex($_[0]);
  if ($code eq 0) {
    return "None";
  }
  else
  {
    $ret=undef;
    if ($code & 1) {
      $ret = "CNOC";
    }
    if ($code & 2) {
      $ret .= ", " if (defined($ret));
      $ret .= "DDR";
    }
    if ($code & 4) {
      $ret .= ", " if (defined($ret));
      $ret .= "DDR (w/Timeout)";
    }
    if ($code & 8) {
      $ret .= ", " if (defined($ret));
      $ret .= "Aborting";
    }
    if ($code & 16) {
      $ret .= ", " if (defined($ret));
      $ret .= "MMNOC";
    }
    if ($code & 32) {
      $ret .= ", " if (defined($ret));
      $ret .= "MMNOC (w/Timeout)";
    }
    $ret = sprintf("%x[%s]", $code, $ret);
  }
  return $ret;
}

sub decode_subsystem
{
  $data = hex($_[0]);
  $subsystem_list = undef;
  foreach $key (sort keys %subsystems)
  {
    if ((hex($key) & $data) > 0)
    {
      $data -= hex($key);
      if (defined($subsystem_list))
      {
        $subsystem_list = $subsystem_list . ", " . $subsystems{$key};
      }
      else
      {
        $subsystem_list = $subsystems{$key};
      }
    }
  }
  if ($data != 0) {
    $subsystem_list = sprintf("!!!ERROR: %X in list: %s", $data, $subsystem_list);
  }
  return $subsystem_list;
}

sub abort_reasons
{
  $reason_mask = $_[0];
  $reason_val = "Reasons";
  $reason_val = $reason_val . ":Sequence Running" if ($reason_mask & 1);
  $reason_val = $reason_val . ":SHRM Timeout" if ($reason_mask & 2);
  $reason_val = $reason_val . ":ARC Timeout" if ($reason_mask & 4);
  $reason_val = $reason_val . ":PMIC Vote Timeout" if ($reason_mask & 8);
  $reason_val = $reason_val . ":SERVICE Requested Abort" if ($reason_mask & 0x10);
  $reason_val = $reason_val . ":BUS Timeout" if ($reason_mask & 0x20);
  $reason_val = sprintf("%s:OTHERS:0x%X", $reason_val, $reason_mask & 0xFFFFFFC0) if ($reason_mask & 0xFFFFFFC0);
  return "$reason_val";
}

sub signal_list
{
  $val = $_[0];

  $int = hex($1);
  $list = "Services";
  foreach $key (sort keys %sigs)
  {
    if ((hex($key) & $int) > 0)
    {
      $delay = undef;
      $list = $list . ":" . $sigs{$key};
    }
  }
  return $list
}

$signals_pending = ();
sub expand_data
{
  $msg = $_[0];
  $data = $_[1];
  $timestamp = $_[2];
  if ($msg =~ m/ISR Received/)
  {
    if ($data =~ m/(..)(......)/)
    {
      $int = $1;
      $signals_pending{$2}=$timestamp;
      if (defined $sigs{$2}) {
        $sig = $sigs{$2};
      }
      else
      {
        $sig = $2;
      }
      print "Interrupt 0x$int Signal $sig";
    }
  }
  elsif ($msg =~ m/MMNOC Timed Out/)
  {
    if ($data =~ m/(....)(..)(..)/)
    {
      $service_pend = decode_resource($2);
      $services_on  = decode_resource($3);
      print "Pending:$service_pend, Already on:$services_on";
    }
  }
  elsif ($msg =~ m/Service Timed Ou/)
  {
    if ($data =~ m/(.)(.......)/)
    {
      $wdog = $1;
      $extra = hex($2);
      print "Watchdog Pending $wdog Timeout $extra ticks past timeout time";
    }
  }
  elsif ($msg =~ m/signal_abort_isr called/)
  {
    if ($data =~ m/(..)(......)/)
    {
      $int = $1;
      if (defined $sigs{$2}) {
        $sig = $sigs{$2};
      }
      else
      {
        $sig = $2;
      }
      print "Interrupt 0x$int Signal $sig";
    }
  }
  elsif ($msg =~ m/NonSecure Watchdog Bite/)
  {
    if ($data =~ m/(........)/)
    {
      $glob_wd_bite = $1;
      print "Glob_wd_bite = $glob_wd_bite";
    }
  }
  elsif ($msg =~ m/Signals Received/)
  {
    if ($data =~ m/(........)/)
    {

      $int = hex($1);
      $list = undef;
      foreach $key (sort keys %sigs)
      {
        if ((hex($key) & $int) > 0)
        {
          $delay = undef;
          if (defined($signals_pending{$key})) {
            $start = hex($signals_pending{$key});
            $done = hex($timestamp);
            $delay = int(($done - $start)/19.2 + 0.5);
          }
          if (defined($list))
          {
            $list = $list . ", " . $sigs{$key};
          }
          else
          {
            $list = $sigs{$key};
          }
          $list = $list."(delay:$delay)" if (defined($delay));
        }
      }

      print "Signals: $list";
    }
  }
  elsif (($msg =~ m/In do_crash_dump/) ||
         ($msg =~ m/Secure Watchdog Bite/))
  {
    if ($data =~ m/(........)/)
    {
      $ddr_complete = hex($1);
      print "DDR_Completed" if ($ddr_complete);
      print "DDR did not complete turning on" if (!$ddr_complete);
    }
  }
  elsif ($msg =~ m/Service pending resource/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $service_number = hex($1);
      $service_needs  = decode_resource($3);
      $services_on    = decode_resource($4);
      print "Service number $service_number, Needs:$service_needs, Already on:$services_on";
    }
  }
  elsif (($msg =~ m/BCM CNOC Callback Recvd/) ||
         ($msg =~ m/BCM DDR Callback Recvd/)  ||
         ($msg =~ m/BCM MMNOC Callback Recvd/))
  {
    if ($data =~ m/(....)(..)(..)/)
    {
      $req_data = $1;
      $pending_resource = decode_resource($2);
      $on_resource = decode_resource($3);
      print "Request $req_data, Pending:$pending_resource, ON:$on_resource";
    }
  }
  elsif (($msg =~ m/BCM Voting DDR Off/) ||
         ($msg =~ m/BCM Voting MMNOC Off/) ||
         ($msg =~ m/BCM Voting CNOC Off/))
  {
    if ($data =~ m/(....)(....)/)
    {
      $pending_resource = decode_resource($1);
      $on_resource = decode_resource($2);
      print "Pending:$pending_resource, ON:$on_resource";
    }
  }
  elsif ($msg =~ m/Vote Resource Needs/)
  {
    if ($data =~ m/(....)(..)(..)/)
    {
      $resource_needs = decode_resource($1);
      $pending_resource = decode_resource($2);
      $on_resource = decode_resource($3);
      print "Needs $resource_needs, Pending:$pending_resource, ON:$on_resource";
    }
  }
  elsif ($msg =~ m/BCM Voting .* On/)
  {
    if ($data =~ m/(........)/)
    {
      $request = $1;
      $signals_pending{'40000000'}=$timestamp;
      print "RequestID $request";
    }
  }
  elsif ($msg =~ m/^Service:/)
  {
    if ($data =~ m/(..)(....)(..)/)
    {
      $service_number = hex($1);
      if (($msg =~ m/System at Idle/) && ($service_number == 0))
      {
	$service_needs  = decode_resource($2 << 8 + $3);
	print "QDSS needs Resources:$service_needs";
      }
      else
      {
	$service_needs  = decode_resource($2);
	$services_on    = decode_resource($3);
	print "Service number $service_number, Needs:$service_needs, Already on:$services_on";
      }
    }
  }
  elsif ($msg =~ m/^PDC Change Done/)
  {
    if ($data =~ m/(........)/)
    {
      $subsystem_list = decode_subsystem($1);
      print "Subsystems: $subsystem_list";
    }
  }
  elsif ($msg =~ m/^BCM Voting DDR ON/)
  {
    if ($data =~ m/(........)/)
    {
      $signals_pending{'40000000'}=$timestamp;
      $debug_request = $1;
      print "Request_ID: $debug_request";
    }
  }
  elsif ($msg =~ m/Checking system idleness/)
  {
    if ($data =~ m/(........)/)
    {
      $idle_mask = hex($1);
      if ($idle_mask == 0) {
	$idle_val = "Idle";
      }
      else
      {
	$idle_val = "Busy:";
	$idle_val = $idle_val . " Signals," if ($idle_mask & 1);
	$idle_val = $idle_val . " Resources," if ($idle_mask & 2);
	$idle_val = $idle_val . " System Active," if ($idle_mask & 4);
      }
      print "$idle_val";
    }
  }
  elsif ($msg =~ m/^AOP Initiated Abort/i)
  {
    if ($data =~ m/(........)/)
    {
      $reason_mask = abort_reasons(hex($1));
      print "$reason_val";
    }
  }
  elsif ($msg =~ m/^Disabling DDR/)
  {
  }
  elsif ($msg =~ m/^SDPM Level/i)
  {
    if ($data =~ m/(..)(..)(....)/)
    {
      $mc = hex($1);
      $shub = hex($2);
      $shub = 300 if ($shub == 0x2c);
      $shub = 466 if ($shub == 0xD2);
      $shub = 600 if ($shub == 0x58);
      $shub = 806 if ($shub == 0x26);
      $shub = 933 if ($shub == 0xA5);
      $shub = 1020 if ($shub == 0xFC);
      $shub = 1066 if ($shub == 0x2a);
      if ($shub == 150) {
        # If SHUB is 150, it didn't affect MC.   Also, MC can only be 200
      }
      elsif (($shub == 300) || ($shub == 466))
      {
	$mc = 200 if ($mc == 0xc9);
	$mc = 451 if ($mc == 0xc3);
	$mc = 547 if ($mc == 0x23);
	$mc = 681 if ($mc == 0xA9);
	$mc = 768 if ($mc == 0x01);
      }
      elsif ($shub == 600)
      {
	$mc = 200 if ($mc == 0xca);
	$mc = 451 if ($mc == 0xc3);
	$mc = 547 if ($mc == 0x23);
	$mc = 681 if ($mc == 0xAB);
	$mc = 768 if ($mc == 0x02);
	$mc =1017 if ($mc == 0xFB);
	$mc =1555 if ($mc == 0x13);
	$mc =1708 if ($mc == 0xAE);
      }
      else 
      {
	$mc = 200 if (($mc == 0xCB) || ($mc == 0xCC));
	$mc = 451 if (($mc == 0xC3) || ($mc == 0xC7));
	$mc = 547 if (($mc == 0x23) || ($mc == 0x27));
	$mc = 681 if (($mc == 0xAB) || ($mc == 0xAD));
	$mc = 768 if (($mc == 0x03) || ($mc == 0x04));
	$mc =1017 if (($mc == 0xFB) || ($mc == 0xFD));
	$mc =1555 if (($mc == 0x13) || ($mc == 0x17));
	$mc =1708 if (($mc == 0xAF) || ($mc == 0xAC));
	$mc =2092 if (($mc == 0x2F) || ($mc == 0x2C));
	$mc =2736 if (($mc == 0xB3) || ($mc == 0xB4));
	$mc =3196 if (($mc == 0x7F) || ($mc == 0x7C));
      }
      $ret = hex($3);
      printf("MC:%d, SHUB:%d, ret:%X", $mc, $shub, $ret);
    }
  }
  elsif ($msg =~ m/^PMU Workaround /i)
  {
    if ($data =~ m/(........)/)
    {
       print "0x$1";
    }
  }
  elsif ($msg =~ m/force_aop_abort history/i)
  {
    $reason_mask = abort_reasons(hex($data));
    print "$reason_val";
  }
  elsif ($msg =~ m/Service Requesting Abort/i)
  {
    $services = signal_list(hex($data));
    print "$services";
  }
  elsif ($msg =~ m/DDR Resource voted on/i)
  {
    if ($data =~ m/(........)/)
    {
      $resource  = decode_resource($1);
      print ("Resource: $resource");
    }
  }
  elsif ($msg =~ m/About to Enable ICB Rte/i)
  {
    if ($data =~ m/(........)/)
    {
      if ($data == 0)
      {
        print "DDR Was voted off";
      }
      elsif ($data == 1)
      {
        print "DDR Was already voted on";
      }
      else
      {
        print "$data:  DDR previous state unknown";
      }
    }
  }
  else
  {
    print "...";
  }
}

if (!defined $data)
{
  $file = shift;
  if (-d $file) {
    @trials = qw(MSGRAM7.BIN aop_msg7_0xc370000--0xc3703ff.lst);
    foreach $trial (@trials) {
      print "Trying $trial\n";
      $try = $file . "/" . $trial;
      if (-f $try)
      {
        $file = $try;
        last;
      }
    }
  }
  print "Trying to open $file\n";
  open LOGFILE, "< $file" || die "Cannot open $file: $!";
  print "Logfile $file opened\n";
  if (($file =~ m/.bin$/i) || ($file =~ m/.lst$/i))
  {
    $total = 0;
    binmode LOGFILE;
    $binary = 1;
    while (read(LOGFILE, $bindata, 16) == 16)
    {
      ($word1, $word2, $word3, $word4) = unpack("I I I I", $bindata);
      $ascii = unpack("x4 a8", $bindata);
      $ascii =~ s/[[:^print:]]/ /g;
      $line = sprintf ("%08.8X: %08.8X %08.8X %08.8X %08.8X     %s    ", $total, $word1, $word2, $word3, $word4, $ascii);
      $total = $total + 16;
      push(@lines, $line);
      last if ($total >= (1024-64));
    }
    print "Total read: $total\n";
  }
  else 
  {
    local $/;
    while (<LOGFILE>) {
      $data = $data . $_;
    }
    @lines = split /\n/, $data;
  }
  close LOGFILE;
}
else
{
  @lines = split /\n/, $data;
}
@log_msgs = ();
$count = 0;
$ts_hi_used = 0;
$ts_lo_used = 0;
foreach $line (@lines)
{
  if (parse_fields($count, $line))
  {
    $hex_ts = hex($log_msgs[$count]{timestamp});
    $ts_hi_used = 1 if (($hex_ts & 0xF0000000) == 0xF0000000);
    $ts_lo_used = 1 if (($hex_ts & 0xF0000000) == 0x00000000);
    $count++;
  }
}

$wrap_ts = 1 if ($ts_hi_used && $ts_lo_used);
$last_timestamp = hex("1FFFFFFFF");
for $index (0 .. $#log_msgs)
{
  $hex_ts = hex($log_msgs[$index]{timestamp});
  $hex_ts += hex(100000000) if ($wrap_ts && (($hex_ts & 0xC0000000) == 0x00000000));

  if ($hex_ts < $last_timestamp)
  {
    $min_timestamp_addr = hex($log_msgs[$index]{addr})/16;
    print "Min Timestamp is $log_msgs[$index]{timestamp} at index $index (last $last_timestamp)\n";
    $last_timestamp = $hex_ts;
  }
}

@log_msgs = sort by_position @log_msgs;
$log_count = 1+$#log_msgs;
print "Log msgs have $log_count\n";

$last_time = 0;

foreach $hash_ref (@log_msgs)
{
  %line_hash = %{$hash_ref};
  $hex_ts = hex($line_hash{timestamp});
  $hex_ts += hex(100000000) if ($wrap_ts && (($hex_ts & 0xC0000000) == 0x00000000));

  $time = int($hex_ts);
  $rel_time = relative($time, $last_time);
  $last_time = $time;
  printf ("%08s %10s: %s %08s ", $line_hash{timestamp}, $rel_time,
          $line_hash{msg_text}, $line_hash{data});
  expand_data($line_hash{msg_text}, $line_hash{data}, $line_hash{timestamp});
  print "\n";
}
