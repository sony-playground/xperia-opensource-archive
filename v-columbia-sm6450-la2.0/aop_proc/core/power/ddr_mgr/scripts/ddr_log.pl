
$min_timestamp_addr = 0;
$binary = 0;
$current_freq_seq = undef;
%vote_val = (
  0   => "OFF",
  16  => "RET",
  48  => "MIN_SVS",
  64  => "LOW_SVS",
  80  => "LOW_SVS_L1",
  96  => "LOW_SVS_L2",
  128 => "SVS",
  192 => "SVS_L1",
  224 => "SVS_L2",
  258 => "NOM",
  320 => "NOM_L1",
  336 => "NOM_L2",
  384 => "TUR",
  416 => "TUR_L1"
);

%seq_name = (
# Lahaina values
 "78" => "MC/SHUB Parallel",
 "30" => "SHUB Only",
 "50" => "MC Only",
 "C8" => "Collapse",
 "F2" => "Restore",
);

%wa_mapping = (
# Waipio values
 0 => "WA_DONE",
 1 => "VOLTAGE_WA",
 2 => "PRE_FREQ_WA",
 3 => "POST_FREQ_WA",
 4 => "SW_SEQ_WA",
 5 => "COLLAPSE_WA",
 6 => "RESTORE_WA",
);


%translations = (
  "SwtchIdx" => "local_switch_log_index  ",
  "GetNeeds" => "get_aop_needs           ",
  "SendVote" => "arc_send_vote           ",
  "ERR:TCS2" => "service_fal: TCS2 used  ",
  "RailChng" => "rail_change_handler     ",
  "ERR:VSEQ" => "Invalid CX Voltage Seq  ",
  "ARC CONT" => "ARC_CONTINUE_PROCESSING ",
  "PS_PreWk" => "arc_unblock_ps_prework  ",
  "RM_PreWk" => "arc_unblock_rm_prework  ",
  "VoltDone" => "Voltage Sequence Done   ",
  "Volt Rdy" => "Voltage_Dependency_Ready",
  "Run VSeq" => "Running Voltage Seq     ",
  "Unblk MC" => "UNBLOCK_BCM_MC          ",
  "UnblkSHB" => "UNBLOCK_BCM_SHUB        ",
  "Unblk_PS" => "UNBLOCK_POWERSTATE_ARC  ",
  "Procssed" => "FREQ_FSM PROCESS DONE   ",
  "StrtMemT" => "Starting Memory Test    ",
  "CmdDBTst" => "CMD_DB_MEMORY_TEST      ",
  "DBTstBAD" => "CMD_DB_MEMORY_TEST FAIL ",
  "DBTst OK" => "CMD_DB_MEMORY_TEST PASS ",
  "FreqStrt" => "Starting Frequency Seq  ",
  "Log Stop" => "Freq_exit stopping log  ",
  "FreqDone" => "Frequency Seq complete  ",
  "ERR:TCS0" => "readdata: TCS 0 in use  ",
  "ReadData" => "Flush readdata complete ",
  "ERR:TCS0" => "flush_entry: TCS0 used  ",
  "ERR:TCS1" => "flush_exit: TCS1 used   ",
  "LLC_Evnt" => "Event during LLC Flush  ",
  "MainLoop" => "MAIN LOOP PROCESSING    ",
  "ZeroTemp" => "sig_zero_temp_event     ",
  "DDR ISR " => "DDR_MGR_ISR_FUNC ISR    ",
  "PMIC CB " => "PMIC Callback           ",
  "FreqNeed" => "In Frequency_Need_Met   ",
  "DCCEnter" => "Waiting for Bandwidth   ",
  "DCC Exit" => "Memtest Bandwidth ready ",
  "BusVt On" => "Voting Bandwidth on     ",
  "BusVtOff" => "Voting Bandwidth off    ",
  "DEBUG   " => "Debug Timer Expired     ",
  "XO OFF  " => "XO Voted Off            ",
  "XO start" => "Waiting for XO complete ",
  "XO done." => "XO Vote Completed       ",
  "Block CX" => "CX seq waiting for XO   ",
  "ERRreqid" => "Unexpected Request ID   ",
  "VoltPend" => "Waiting for Volt Req    ",
  "Volt CB " => "Voltage Request Complete",
  "SendVolt" => "Checking Outstand Votes ",
  "VotesOut" => "Voltages Summary        ",
  "DDR Vote" => "DDR Vote Sent to uNPA   ",
  "CXVoteCB" => "CX uNPA Driver Callback ",
  "MXVoteCB" => "MX uNPA Driver Callback ",
  "VAVoteCB" => "VDDA NPA Driver Callback",
  "MXRet CX" => "Block CX:MX at Retention",
  "MXSeqReq" => "Block CX:MX Sequencing  ",
  "MXDepCSC" => "Block CX:MX needs TURBO ",
  "DDRclnCB" => "DDR_MSG Driver Callback ",
  "IsCxRest" => "CX Restore?             ",
  "Int Step" => "Intermediate Frequency  ",
  "No  Step" => "Stopping at Int Freq    ",
  "TCS_CMD " => "Building TCS CMD        ",
  "SMEMVOTE" => "VRM Votes sent          ",
  "PMICRqCB" => "VRM Votes Complete      ",
  "DRV PERF" => "DDR_MGR Vote Performance",
  "Clock WA" => "Clock Workaround        ",
  "DDR_WA  " => "DDR Workaround          ",
  "MC NEEDS" => "MC Voltage Need         ",
  "SHRMFREQ" => "SHRM Frequency          ",
  "NO SHRM " => "ALLOW_SHRM set to FALSE ",
  "PWRCT_HI" => "Hi Workaround Cntrl Bits",
  "PWRCT_LO" => "Lo Workaround Cntrl Bits",
  "AOSSRES0" => "AOSS Sleep Down Start   ",
  "AOSSRES1" => "AOSS Sleep Up End       ",
  "AOSSRES2" => "AOSS Sleep Down End     ",
  "AOSSRES3" => "AOSS Sleep Up Start     ",
  "SIGSDPM1" => "Send SDPM Signal (PRIOR)",
  "SIGSDPM2" => "Send SDPM Signal (AFTER)",
  "PASRDone" => "Exit PASR State         ",
  "PERFStrt" => "Enter Perfmode State    ",
  "PERFDone" => "Exit Perfmode State     ",
  "AUXtoAOP" => "AUX Hardened WA         ",
);

sub relative
{
   $last = shift;
   $first = shift;
   $rel = int(($last - $first) / 19.2);
   #$units = "us";
   $units = "";
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
  #0000000: 90a8 5c49 4152 4320 434f 4e54 0001 0100  ..\IARC CONT..../
  if ($line =~ m/([0-9a-f]+)..([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4}).([0-9a-f]{4})......(.{1,8})/i)
  {
    $log_msgs[$count]{addr}      = $1;
    $log_msgs[$count]{timestamp} = flip($3) . flip($2);
    $log_msgs[$count]{msg1}      = flip($5) . flip($4);
    $log_msgs[$count]{msg2}      = flip($7) . flip($6);
    $log_msgs[$count]{data}      = flip($9) . flip($8);
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
  elsif ($line =~ m/([0-9A-F]{8})..([0-9A-F]{8}).([0-9A-F]{8}).([0-9A-F]{8}).([0-9A-F]{8}).....(.{1,8})/i)
  {
    $log_msgs[$count]{addr}      = $1;
    $log_msgs[$count]{timestamp} = $2;
    $log_msgs[$count]{msg1} =      $3;
    $log_msgs[$count]{msg2} =      $4;
    $log_msgs[$count]{data} =      $5;
    if (defined($translations{$6}))
    {
      $log_msgs[$count]{msg_text} = $translations{$6};
    }
    else
    {
      $log_msgs[$count]{msg_text} = $6 . " " x (24-length($6));
    }
    return 1;
  }
  elsif ($line =~ m/([0-9A-F]{7})..([0-9A-F]{8}).([0-9A-F]{8}).([0-9A-F]{8}).([0-9A-F]{8}).....(.{1,8})/i)
  {
    $log_msgs[$count]{addr}      = $1;
    $log_msgs[$count]{timestamp} = $2;
    $log_msgs[$count]{msg1} =      $3;
    $log_msgs[$count]{msg2} =      $4;
    $log_msgs[$count]{data} =      $5;
    if (defined($translations{$6}))
    {
      $log_msgs[$count]{msg_text} = $translations{$6};
    }
    else
    {
      $log_msgs[$count]{msg_text} = $6 . " " x (24-length($6));
    }
    return 1;
  }
  else
  {
    #print "No: [$line]\n";
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

%clients = (
  "00" => "FREQUENCY",
  "01" => "DEPENDENCY",
  "02" => "TEMP_EVENT",
);
%resources = (
  "00" => "CX",
  "01" => "MX",
  "02" => "VDDA",
  "03" => "PMIC",
  "04" => "DDR",
  "05" => "XO",
  "06" => "LDO",
);
%rm_names = (
  "00" => "CX",
  "01" => "MX",
  "02" => "VDDA",
  "03" => "SSC_CX",
  "04" => "SSC_MX",
  "05" => "GFX",
  "06" => "MSS",
  "07" => "DDR_SS",
  "08" => "XO",
);

%sigs = (
  "000001" => "PASR_PENDING",
  "000002" => "PERFMODE_PENDING",
  "000004" => "UPDATE_FREQUENCY_PLAN",
  "000008" => "BCM_STATUS",
  "000010" => "UPDATE_STARC",
  "000020" => "UPDATE_BCM_INIT_DONE",
  "000040" => "TEST_PROCESS_COLLAPSE",
  "000080" => "TEST_PROCESS_RESTORE",
  "000100" => "DDR_AUX_SEQ0_INT ",
  "000200" => "DDR_AUX_VLT_TCS_INT",
  "000400" => "DDR_AUX_RSI_TCS_INT",
  "000800" => "DDR_AUX_PWR_CTRL_INT",
  "001000" => "DDR_AUX_RSI_GPW_INT",
  "002000" => "DDR_AUX_SEQ_TO_INT",
  "004000" => "DDR_AUX_RSI_TO_INT",
  "008000" => "DDR_AUX_SUMMARY_INT",
  "010000" => "ARC_CX_RM_INTERRUPT",
  "020000" => "ARC_CX_SEQ_PRE_INTERRUPT",
  "040000" => "ARC_CX_SEQ_POST_INTERRUPT",
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
  "40000000" => "Bit 30",
  "80000000" => "Bit 31",
);

%frequency_event = (
  "000001" => "Frequency Change",
  "000002" => "Voltage Requirements Met",
  "000004" => "DCC Complete",
  "000008" => "Frequency Sequence Complete",
  "000010" => "Command Done",
  "000020" => "Process Complete",
  "000040" => "Poll Complete",
  "000080" => "PASR Pending",
  "000100" => "Perfmode Pending",
  "FFFE00" => "Additional/Unknown Events",
);

sub pending_decode_new
{
  $code = $_[0];
  if ($code eq "00") {
    return "Pending None";
  } elsif ($code eq "01") {
    return "Pending Sequence";
  } elsif ($code eq "02") {
    return "Deferred Sequence";
  } else {
    return "$code";
  }
}
sub pending_decode_old
{
  $code = $_[0];
  if ($code eq "00") {
    return "Pending None";
  } elsif ($code eq "01") {
    return "Below MOL Agg";
  } elsif ($code eq "02") {
    return "Pending Agg";
  } elsif ($code eq "03") {
    return "Pending Sequence";
  } elsif ($code eq "04") {
    return "Deferred Agg";
  } else {
    return "$code";
  }
}

%translate_vlvls = (
  hex(10) => "RET",
  hex(30) => "MIN_SVS",
  hex(40) => "LOW_SVS",
  hex(80) => "SVS",
  hex('C0') => "SVS_L1",
  hex(100) => "NOM",
  hex(140) => "NOM_L1",
  hex(150) => "NOM_L2",
  hex(180) => "TUR",
  hex('1A0') => "TUR_L1",
);

sub fsm_events
{
  $data = hex($_[0]);
  $fsm_list = undef;
  foreach $key (sort keys %frequency_event)
  {
    if ((hex($key) & $data) > 0)
    {
      if (defined($fsm_list))
      {
        $fsm_list = $fsm_list . ", " . $frequency_event{$key};
      }
      else
      {
        $fsm_list = $frequency_event{$key};
      }
    }
  }
  return "$fsm_list";
}

$resource_time = 0x100000000;  # Process Done -> Sequencer Start
sub expand_data($$$)
{
  $msg = $_[0];
  $data = $_[1];
  $time = $_[2];
  if ($msg =~ m/ARC_CONTINUE_PROCESSING/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $arc = $1;
      $seq_lvl = $2;
      $in_seqlvl = $3;
      $arc = $resources{$arc} if defined($resources{$arc});
      print "ARC $arc SequenceLvl $seq_lvl  In_sequence $in_seqlvl";
    }
  }
  elsif ($msg =~ m/arc_unblock_rm_prework/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $arc_rm = $1;
      $current = $2;
      $seq_lvl = $3;
      $in_seqlvl = $4;
      $arc_rm = $rm_names{$arc_rm} if defined($rm_names{$arc_rm});
      print "ARC_RM $arc_rm Current $current SequenceLvl $seq_lvl  In_sequence $in_seqlvl";
    }
  }
  elsif ($msg =~ m/arc_unblock_ps_prework/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $arc = $1;
      $arc_lvl = $4;
      $arc = $resources{$arc} if defined($resources{$arc});
      print "ARC $arc ddr_arc_lvl $arc_lvl";
    }
  }
  elsif ($msg =~ m/DDR_MGR_ISR/)
  {
    if ($data =~ m/(..)(......)/)
    {
      $int = $1;
      if (defined $sigs{$2}) {
        $sig = $sigs{$2};
      }
      else
      {
        $sig = "Multiple Signals: 0x$2";
      }

      print "Interrupt 0x$int, Signal $sig";
    }
  }
  elsif ($msg =~ m/arc_send_vote/)
  {
    if ($data =~ m/(..)(..)(....)/)
    {
      $arc = $1;
      $client = $2;
      $value = $3;
      $arc = $resources{$arc} if defined($resources{$arc});
      $client = $clients{$client} if defined($clients{$client});
      print "Resource $arc Client $client Value $value";
    }
  }
  elsif (($msg =~ m/UNBLOCK_BCM_MC/) || ($msg =~ m/UNBLOCK_BCM_SHUB/))
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Current:$1, BCM:$2, Next BCM Lvl:$3";
    }
  }
  elsif ($msg =~ m/UNBLOCK_POWERSTATE_ARC/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Current MC:$1, Ack Lvl:$2, ARC Lvl:$3";
    }
  }
  elsif ($msg =~ m/Running Voltage Seq/)
  {
    if ($data =~ m/(..)(..)(....)/)
    {
      $mask = $2;
      %masks = (
        "01" => "MX Only",
        "02" => "CX Only",
        "03" => "CX/MX",
        "04" => "VDDA Only",
        "05" => "MX & VDDA",
        "06" => "CX & VDDA",
        "07" => "CX/MX/VDDA"
      );
      $mask = $masks{$2} if defined($masks{$2});
      print "Mask $mask";
    }
  }
  elsif ($msg =~ m/Voltage Sequence Done/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $arc = $1;
      $was = $2;
      $now = $3;
      $arc = $resources{$arc} if defined($resources{$arc});
      print "$arc Was $was Became $now";
    }
  }
  elsif ($msg =~ m/Starting Frequency Seq/)
  {
    $res_str = undef;
    if ($time > $resource_time)
    {
      $res_elapsed = int(10 * ($time - $resource_time) / 19.2)/10;
      $res_str = "Overhead:$res_elapsed us";
    }
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $mc = $1;
      $shub = $2;
      $start_addr = $3;
      $current_freq_seq = undef;
      $current_freq_seq = $seq_name{$start_addr};
      print "MC to $mc SHUB to $shub Sequence offset $start_addr";
      print " - $current_freq_seq" if (defined($current_freq_seq));
      print " - $res_str" if (defined($res_str));
    }
    $resource_time = 0x100000000;
  }
  elsif ($msg =~ m/Frequency Seq complete/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $mc = $1;
      $shub = $2;
      print "MC at $mc SHUB at $shub";
      $elapsed = hex($3) * 256 + hex($4);
      if ($elapsed > 0)
      {
        $elapsed_time = int($elapsed/19.2 + 0.5);
        print " Elapsed $elapsed_time";
      }
      print " - $current_freq_seq" if (defined($current_freq_seq));
      $current_freq_seq = undef;
      print " *****************";
    }
  }
  elsif ($msg =~ m/Flush readdata complete/)
  {
    if ($data =~ m/(........)/)
    {
      print "PCB Data $1";
    }
  }
  elsif ($msg =~ m/rail_change_handler/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      %events = (
        "00" => "Agg",
        "01" => "Pre",
        "02" => "Post",
        "06" => "BMPre",
        );

      $arc = $1;
      $event = $2;
      $aop_needs = $3;
      $desired_ol = $4;

      $arc = $resources{$arc} if defined($resources{$arc});
      $event = $events{$event} if defined($events{$event});
      print "$arc Event $event DDR_NEEDS $aop_needs Desired OL $desired_ol";
    }
  }
  elsif ($msg =~ m/Event during LLC Flush/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $event = $1;
      $next_state = $2;
      $flush_status = $3;
      $pcb_mask = $4;
      print "Events:$event\[";
      print fsm_events($event);
      print "], Next_State:" . $next_state;
      print ", Flush_Status:" . $flush_status;
      print ", PCB:" . $pcb_mask;
    }
  }
  elsif ($msg =~ m/MAIN LOOP PROCESSING/)
  {
    $signals = hex($data);
    $list = undef;

    foreach $key (sort keys %sigs)
    {
      if ((hex($key) & $signals) > 0)
      {
        if (defined($list))
        {
          $list = $list . ", " . $sigs{$key};
        }
        else
        {
          $list = $sigs{$key};
        }
      }
    }
    print "$list";
  }
  elsif ($msg =~ m/PSInt/)
  {
    $elapsed = int(hex($data)/19.2);
    print "Time from event to now is $elapsed us";
  }
  elsif ($msg =~ m/Freq_exit stopping log/)
  {
    $elapsed = int(hex($data)/19.2);
    print "Logging stopped, transition took $elapsed us";
  }
  elsif (($msg =~ m/CX Callback/) ||
         ($msg =~ m/MX Callback/) ||
         ($msg =~ m/VDDA Callback/))
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $request_id = $1 . $2;
      $pending = $3;
      $vote = $4;
      print "Request $request_id Pending $pending Vote value $vote";
    }
  }
  elsif ($msg =~ m/PMIC Callback/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      if ($4 cmp "00")
      {
         $request_id = $1 . $2;
         $pending = $3;
         $vote = $4;
         $request_id = "0x" . $request_id . " (" . hex($request_id) . ")";
      }
      else
      {
         $request_id = $1;
         $pending = $2;
         $vote = $3;
      }
      print "Request $request_id Pending $pending Vote value $vote";
    }
  }
  elsif ($msg =~ m/FREQ_FSM PROCESS DONE/)
  {
    $resource_time = $time;
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $mc = $1;
      $shub = $2;
      $next_state = $4;
      $next_state = "IDLE" if ($next_state == 0);
      $next_state = "Voltage" if ($next_state == 2);
      print "MC going to $mc Shub going to $shub Next state $next_state";
    }
  }
  elsif ($msg =~ m/In Frequency_Need_Met/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
       $pmic_pending = $1;
       $cx_min_state = $2;
       $mx_min_state = $3;
       $vdda_min_state = $4;

       print "PMIC Pending $pmic_pending CX at $cx_min_state MX at $mx_min_state VDDA at $vdda_min_state";
    }
  }
  elsif ($msg =~ m/Waiting for Bandwidth/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Bandwidth available: $1"
    }
  }
  elsif ($msg =~ m/Memtest Bandwidth ready/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Bandwidth previously available: $1"
    }
  }
  elsif ($msg =~ m/Voting Bandwidth on/)
  {
    if ($data =~ m/(........)/)
    {
      if ($1 cmp "00000000")
      {
        print "Bandwidth request: $1"
      }
      else
      {
        print "Bandwidth already available $1";
      }
    }
  }
  elsif ($msg =~ m/Voting Bandwidth off/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Bandwidth available: $1"
    }
  }
  elsif ($msg =~ m/Debug Timer Expired/)
  {
    if ($data =~ m/(........)/)
    {
      print "Check DDR Ulogs";
      if ($1 & 1) {
        print ": DDRAUX Sequence Running";
      }
      if ($1 & 2) {
        print ": SHRM Not Responding to commands";
      }
    }
  }
  elsif ($msg =~ m/XO Voted Off/)
  {
     # Nothing to do
  }
  elsif (($msg =~ m/Freq Voting FireForget/) ||
         ($msg =~ m/Freq Voting Resp Req/))
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      printf("Num Commands:%d CX=%X, MX=%X, VDDA=%X",
              $1, hex($2)*16,hex($3)*16,hex($4)*16);
    }
  }
  elsif ($msg =~ m/Checking Outstand Votes/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $cx_pend = $2;
      $mx_pend = $3;
      $vdda_pend = $4;
      print "CX Pending:$cx_pend; MX Pending:$mx_pend; VDDA Pending:$vdda_pend";
    }
  }
  elsif ($msg =~ m/Voltages Summary/)
  {
    #"VotesOut" => "Voltages Summary        ",
    if ($data =~ m/(.)(.)(.)(.)(.)(.)(.)(.)/)
    {
      $votes = hex($1);
      $resp  = hex($2);
      $vdda_was = hex($3);
      $vdda_now = hex($4);
      $mx_was  = hex($5);
      $mx_now  = hex($6);
      $cx_was  = hex($7);
      $cx_now  = hex($8);

      printf("%d votes %d RR. CX %d->%d, MX %d->%d, VDDA %d->%d",
             $votes, $resp, $cx_was, $cx_now, $mx_was,
             $mx_now, $vdda_was, $vdda_now);
    }
  }
  elsif ($msg =~ m/DDR Vote Sent to uNPA/)
  {
    if ($data =~ m/(.)(.)(.)(.....)/)
    {
      $arc = $1;
      $current = $2;
      $vote = $3;
      $req_id = $4;

      $arc = "CX" if ($arc =~ m/0/);
      $arc = "MX" if ($arc =~ m/1/);
      $arc = "VDDA" if ($arc =~ m/2/);

      print "ARC:$arc; At $current Voting $vote; Request ID: $req_id";
    }
  }
  elsif ($msg =~ m/NPA Driver Callback/)
  {
    if ($data =~ m/(....)(..)(..)/)
    {
      $req_id = $1;
      $pending = $2;
      $arc_cl = $3;

      print "Request ID:$1; Was Pending:$pending;  ARC CL:$arc_cl";
    }
  }
  elsif ($msg =~ m/CX Restore/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      # $cx_cl = $1;
      # $cx_state = $2*16;
      # $mx_state = $3*16;
      # $collapsed = $4;
      
      printf("CxLvl:%d, CxState:%X, MxState:%X, Collapsed:%d",
             $1, $2*16, $3*16, $4);
    }
  }
  elsif ($msg =~ m/Intermediate Frequency/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      printf("Step Num:%d, From CP:%d, To CP:%d", $1, hex($2), hex($3));
    }
  }
  elsif ($msg =~ m/Stopping at Int Freq/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      printf("Step Num:%d, From CP:%d, To CP:%d Not Allowed", $1, hex($2), hex($3));
    }
  }
  elsif (($msg =~ m/Waiting for XO complete/) ||
         ($msg =~ m/XO Vote Completed/)       ||
         ($msg =~ m/CX seq waiting for XO/)   ||
         ($msg =~ m/Waiting for Volt Req/)    ||
         ($msg =~ m/Block CX:MX at Retention/)||
         ($msg =~ m/Block CX:MX Sequencing/)  ||
         ($msg =~ m/Voltage Request Complete/))
  {
    if ($data =~ m/(........)/)
    {
       print "Request ID: $1";
    }
  }
  elsif ($msg =~ m/Block CX:MX needs TURBO/)
  {
    #"MXDepCSC" => "Block CX:MX needs TURBO ",
    if ($data =~ m/(........)/)
    {
       print "MX_ARC_LEVEL:$1";
    }
  }
  elsif ($msg =~ m/DDR_MSG Driver Callback/)
  { 
    #"DDRclnCB" => "DDR_MSG Driver Callback ",
    if ($data =~ m/(........)/)
    {
       print "Request ID: $1";
    }
  }
  elsif ($msg =~ m/Starting Memory Test   /)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Next MC:$1, Next Shub:$2, Address:$3, AOP Read DDR only:$4";
    }
  }
  elsif ($msg =~ m/CMD_DB_MEMORY_TEST     /)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Next MC:$1, Next Shub:$2";
    }
  }
  elsif ($msg =~ m/CMD_DB_MEMORY_TEST FAIL/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Next MC:$1, Next Shub:$2";
    }
  }
  elsif ($msg =~ m/CMD_DB_MEMORY_TEST PASS/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      print "Next MC:$1, Next Shub:$2";
    }
  }
  elsif ($msg =~ m/Building TCS CMD/)
  {
    if ($data =~ m/(...)(.)(....)/)
    {
      $type = hex($2);
      $val = hex($3);
      if    ($type == 0) { print "Resource:$1, Voltage:$val"; }
      elsif ($type == 4) { print "Resource:$1, Enable:$val"; }
      elsif ($type == 8) { print "Resource:$1, Mode:$val"; }
      elsif ($type == 12){ print "Resource:$1, Headroom:$val"; }
      else  {print "Resource:$1, Type:$2, Value:$3"; }
    }
  }
  elsif ($msg =~ m/VRM Votes sent/)
  {
    print "Request ID:$data";
  }
  elsif ($msg =~ m/VRM Votes Complete/)
  {
    if ($data =~ m/(....)(..)(..)/)
    {
      print "Req ID:$1, PMIC Pending:$2, PMIC Mode:$3";
    }
  }
  elsif ($msg =~ m/DDR_MGR Vote Performance/)
  {
    if ($data =~ m/(....)(....)/)
    {
      $vrm_time=$1+0 . "us";
      $pmic_time=$2+0 . "us";
      print "VRM Votes:$vrm_time, PMIC Mode:$pmic_time";
    }
  }
  elsif ($msg =~ m/AOSS Sleep/)
  {
    if ($data =~ m/(........)/)
    {
      $time = hex($1) / 19.2;
    }
    if ($msg =~ /Down Start/)
    {
      $aoss_down_start = $time;
    }
    elsif ($msg =~ /Up End/)
    {
      $aoss_up_end = $time;
    }
    elsif ($msg =~ /Down End/)
    {
      $aoss_down_end = $time;
      $elapsed = $time - $aoss_down_start;
      print "Down Sequence: $aoss_down_end -> $aoss_down_start = $elapsed";
    }
    elsif ($msg =~ /Up Start/)
    {
      $aoss_up_start = $time;
      $elapsed = $aoss_up_end - $aoss_up_start;
      print "Up Sequence: $aoss_up_end -> $aoss_up_start = $elapsed";
    }
  }
  elsif ($msg =~ m/Clock Workaround/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $wa_id  = $1;
      $from_cp = hex($2);
      $to_cp  = hex($3);
      $ret_val  = hex($4);
      print "WA ID:$wa_id, FromCP:$from_cp, NextCP:$to_cp, Return:$ret_val";
    }
  }
  elsif ($msg =~ m/MC Voltage Need/)
  {
    if ($data =~ m/(........)/)
    {
      $need = $1;
      $need = $vote_val{hex($1)} if defined($vote_val{hex($1)});
      print $need;
    }
  }
  elsif ($msg =~ m/SHRM Frequency/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $desired_shrm  = hex($1);
      $branch_bits   = hex($2);
      $begin_shrm    = hex($3);
      $end_shrm      = hex($4);
      $delta = "";
      $delta = $delta . "No Change" if ($branch_bits == 0);
      $delta = $delta . "SHRM down" if ($branch_bits & 1);
      $delta = $delta . "SHRM up" if ($branch_bits & 2);
      $delta = $delta . "SHRM power" if ($branch_bits & 4);

      print "SHRM Desired $desired_shrm:$delta Freq at start: $begin_shrm Freq at end: $end_shrm"
    }
  }
  elsif ($msg =~ m/ALLOW_SHRM/)
  {
    if ($data =~ m/(....)(....)/)
    {
      $seq_addr = hex($1);
      $seq_flags = hex($2);
      $current_freq_seq = sprintf("0x%x", $seq_addr);
      $current_freq_seq = $seq_name_lahaina{$current_freq_seq} if defined($seq_name_lahaina{$current_freq_seq});
      printf("Would start sequence %s with flags 0x%X", $current_freq_seq, $seq_flags);
    }
  }
  elsif (($msg =~ m/Workaround Cntrl/) ||
         ($msg =~ m/ALLOW_SHRM/))
  {
    if ($data =~ m/(........)/)
    {
      print "Bits:$1";
    }
  }
  elsif ($msg =~ m/Send SDPM Signal/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $mc_cur = hex($1);
      $shub_cur = hex($2);
      $mc_next = hex($3);
      $shub_next = hex($4);
      if ($msg =~ m/PRIOR/)
      {
        printf("MC:%d->%d, SHUB:%d->%d", $mc_cur, $mc_next, $shub_cur, $shub_next);
      }
      else 
      {
        printf("MC:%d, SHUB:%d", $mc_cur, $shub_cur);
      }
    }
  }
  elsif ($msg =~ m/Perfmode State/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $mc_cur = hex($1);
      $alc_cur = hex($2);
      if ($msg =~ m/Enter/) 
      {
        $alc_next = hex($3);
        printf("MC:%d, Current ALC:%d, Next ALC:%d", $mc_cur, $alc_cur, $alc_next);
      }
      else
      {
        $event = $3;
        $state = hex($4);
        $decoded_event = fsm_events($event);
        $decoded_event = "None" if ($decoded_event =~ m/^$/);
        printf("MC:%d, Current ALC:%d, Event:%s, NextState:%d",
               $mc_cur, $alc_cur, $decoded_event, $state);
      }
    }
  }
  elsif ($msg =~ m/PASR State/)
  {
    if ($data =~ m/(..)(..)(..)(..)/)
    {
      $event = $1;
      $state = hex($2);
      $decoded_event = fsm_events($event);
      printf("Event:%s, NextState:%d", $decoded_event, $state);
    }
  }
  elsif ($msg =~ m/AUX Hardened WA/)
  {
    if ($data =~ m/(........)/)
    {
        $wa = $1&0xF;
        if (defined $wa_mapping{$wa}) {
            $wa = $wa_mapping{$wa};
            print "WA state: $wa";
        }else {
            print "Raw data:$1";
        }
    }
  }
  else
  {
    print "Raw data:$data";
  }
}


if (!defined $data)
{
  $file = shift;
  if (-d $file) {
    @trials = qw(MSGRAM6.BIN aop_msg6_0xc360000--0xc3603ff.lst);
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
      $line = sprintf ("%08.8X: %08.8X %08.8X %08.8X %08.8X     %s    ", $total, $word1, $word2, $word3, $word4, $ascii);
      $total = $total + 16;
      push(@lines, $line);
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
$time_offset = 0;
$last_ts = 0;

foreach $hash_ref (@log_msgs)
{
  %line_hash = %{$hash_ref};
  $time = hex($line_hash{timestamp});
  $delta = $time - $last_ts;
  if ($time_offset <= 0)
  {
    $time_offset = $time;
  }
  if ($delta > 192000)
  {
    printf("-------------------:------------------------------------------------------------------------\n");
    $rel_time = relative($time, $last_ts);
    $time_offset = $time;
  }
  else
  {
    $rel_time = relative($time, $time_offset);
  }
  $last_ts = $time;
  printf("%8s %10s: %s %08s ", $line_hash{timestamp}, $rel_time,
         $line_hash{msg_text}, $line_hash{data});
  expand_data($line_hash{msg_text}, $line_hash{data}, $time);
  print "\n";
}

