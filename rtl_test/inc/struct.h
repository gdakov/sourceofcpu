

#define except_width 13
#define except_status 0,1
#define except_setsFlags 2,2
#define except_flags 3,8
#define except_fperr 3,8
#define except_fpflags 9,12


#define page_wc 9,9
#define page_global 8,8
#define page_huge 7,7
#define page_dirty 6,6
#define page_accessed 5,5
#define page_nc 4,4
#define page_wt 3,3
#define page_sys 1,1
#define page_wr 2,2
#define page_na 0,0


#define bob_ipOff0_9 0,129
#define bob_ret0_8 130,165
#define bob_jump0Type 166,170
#define bob_jump1Type 171,175
#define bob_jump0Pos 176,179
#define bob_jump1Pos 180,183
#define bob_jump0IP 184,230
#define bob_jump1IP 231,277
#define bob_afterTk 278,287
#define bob_pred 288,289
#define bob_regs 290,349
#define bob_rgen 350,359
#define bob_rvec 360,369
#define bob_magicO 370,399
#define bob_last 400,409
#define bob_Fsimd 410,419
#define bob_freeregs 420,469
#define bob_j0GHT 470,477
#define bob_j1GHT 478,485
#define bob_j0Ind 486,487
#define bob_j1Ind 488,489
#define bob_j0Way 490,492
#define bob_j1Way 493,495
#define bob_j0sc 496,497
#define bob_j1sc 498,499
#define bob_j0BtbOnly 500,500
#define bob_j1BtbOnly 501,501
#define bob_j0Miss 502,502
#define bob_j1Miss 503,503
#define bob_frr 504,512
#define bob_jump0Mask 513,516
#define bob_jump1Mask 517,520
#define bob_width 521


#define bobJmp_satCount 0,1
#define bobJmp_hist 2,7
#define bobJmp_camIndex 8,14
#define bobJmp_freq 15,21
#define bobJmp_width 22

#define pbob_jump0Type 0,4
#define pbob_jump1Type 5,9
#define pbob_jump0Pos 10,13
#define pbob_jump1Pos 14,17
#define pbob_pred 18,19
#define pbob_j0Miss 20,20
#define pbob_j1Miss 21,21
#define pbob_indir 22,68
#define pbob_width 69

#define flags_width 6

#define jump_Z 0
#define jump_nZ 1
#define jump_S 2
#define jump_nS 3
#define jump_uGT 4
#define jump_uLE 5
#define jump_uGE 6
#define jump_uLT 7
#define jump_sGT 8
#define jump_sLE 9
#define jump_sGE 10
#define jump_sLT 11
#define jump_O 12
#define jump_nO 13
#define jump_P 14
#define jump_nP 15

#define btb_src_IP 0,48
#define btb_tgt_IP0 49,95
#define btb_tgt_IP1 96,142
#define btb_tgt_IP2 143,189
#define btb_tgt_IP3 190,236
#define btb_valid 237,237
#define btb_off0 238,241
#define btb_off1 242,245
#define btb_off2 246,249
#define btb_off3 250,253
#define btb_cond 254,257
#define btb_indir 258,261
#define btb_link 262,266
#define btb_lnkpos 267,268
#define btb_lnkoff 269,272
#define btb_tgt_jmask0 273,276
#define btb_tgt_jmask1 277,280
#define btb_tgt_jmask2 281,284
#define btb_tgt_jmask3 285,288
#define btb_other 289,292
#define btb_LRU 293,293
//lru needs to be kept at highest 2 bits

#define btb_width 294


#define btbExtra_satCount0 0,1 
#define btbExtra_satCount1 2,3
#define btbExtra_satCount2 4,5
#define btbExtra_satCount3 6,7
#define btbExtra_freq0 8,14
#define btbExtra_freq1 15,21
#define btbExtra_freq2 22,28
#define btbExtra_freq3 29,35

#define btbExtra_width 36





//dirty & LRU bits in separate module
#define dc1Tag_addr_43_14 0,29
#define dc1Tag_valid 30,30
#define dc1Tag_exclusive 31,31
#define dc1Tag_recent 32,32
#define dc1Tag_parity 33,33

#define dc1Tag_width 34

#define cc1Tag_paddr 0,36
#define cc1Tag_valid 37,37
#define cc1Tag_parity 38,38

#define cc1Tag_width 39

//dirty & lru bits for l1
#define dc1Extra_exclusive 0,0
#define dc1Extra_dirty 1,1
#define dc1Extra_LRU 2,4
#define dc1Extra_valid 5,5 

#define dc1Extra_width 6

#define dc2Tag_addr_43_16 0,27
#define dc2Tag_valid 28,28
#define dc2Tag_exclusive 29,29
#define dc2Tag_ins_dirty 30,30
#define dc2Tag_parity 31,31

#define dc2Tag_width 32

#define iclass_indir 0,0
#define iclass_jump 1,1
#define iclass_ALU 2,2
#define iclass_shift 3,3
#define iclass_mul 4,4
#define iclass_load 5,5
#define iclass_store 6,6
#define iclass_store2 7,7
#define iclass_FPU 8,8
#define iclass_loadFPU 9,9
#define iclass_sys 10,10
#define iclass_flag 11,11
#define iclass_pos0 12,12
#define iclass_width 13

#define instrQ_magic 0,3
#define instrQ_srcIPOff 4,15
#define instrQ_btbMiss 16,16
#define instrQ_taken 17,17
#define instrQ_srcTick 18,18
#define instrQ_class 19,31
#define instrQ_btb_way 32,34
#define instrQ_jmp_ind 35,36
#define instrQ_ght_addr 37,44
#define instrQ_sc 45,46
#define instrQ_btb_only 47,47
#define instrQ_lastInstr 48,48
#define instrQ_width 49


#define instrQ_addr_count 36,36
#define instrQ_addr_width 6

#define instrQExtra_IP 0,46
#define instrQExtra_jmask 47,50
#define instrQExtra_width 51



#define dtlbData_phys 0,31
#define dtlbData_sys 32,32
#define dtlbData_wp 33,33
#define dtlbData_na 34,34
#define dtlbData_ne 35,35
#define dtlbData_glo 36,36
#define dtlbData_type 37,38
#define dtlbData_acc 39,39
#define dtlbData_wrt 40,40
#define dtlbData_subpage 41,41
#define dtlbData_width 42

#define dwtlb_vaddr 0,49
#define dwtlb_valid 50,50
#define dwtlb_data1 51,88
#define dwtlb_data2 89,126
#define dwtlb_lru 127,128
#define dwtlb_width 129

#define dtlb_vaddr 0,51
#define dtlb_valid 52,52
#define dtlb_shr 53,53
#define dtlb_data1 54,95
#define dtlb_data2 96,137
#define dtlb_data3 138,179
#define dtlb_width 180



#define ctlbData_phys 0,31
#define ctlbData_sys 32,32
#define ctlbData_na 33,33
#define ctlbData_ne 34,34
#define ctlbData_global 35,35
#define ctlbData_width 36

#define ctlb_ip 0,63
#define ctlb_valid 64,64
#define ctlb_validN 65,65
#define ctlb_lru 66,67 
#define ctlb_data 68,103
#define ctlb_width 104



#define mOp_addrMain 0,43
#define mOp_sz 44,48
#define mOp_st 49,49
#define mOp_bank0 50,54
#define mOp_split 55,55
#define mOp_reg 56,64
#define mOp_LSQ 65,73
#define mOp_II 74,83
#define mOp_thread 84,84
#define mOp_lsflag 85,85
#define mOp_WQ 86,93
#define mOp_type 94,95
#define mOp_width 96

#define mOpX_addrEven 0,35
#define mOpX_addrOdd 36,71
#define mOpX_sz 72,76
#define mOpX_st 77,77
#define mOpX_split 78,78
#define mOpX_odd 79,79
#define mOpX_low 80,81
#define mOpX_bank0 82,86
#define mOpX_regNo 87,95
#define mOpX_II 96,105
#define mOpX_WQ 106,113
#define mOpX_bread 114,118
#define mOpX_mtype 119,120
#define mOpX_width 121


#define mOpC_addrEven 0,35
#define mOpC_addrOdd 36,71
#define mOpC_banks 72,103
#define mOpC_begin 104,108
#define mOpC_end 109,113
#define mOpC_bben 114,117
#define mOpC_endben 118,121
#define mOpC_req 122,124
#define mOpC_odd 125,125
#define mOpC_split 126,126
#define mOpC_width 127

#define mOp1_addrEven 0,35
#define mOp1_addrOdd 36,71
#define mOp1_sz 72,76
#define mOp1_st 77,77
#define mOp1_split 78,78
#define mOp1_odd 79,79
#define mOp1_low 80,81
#define mOp1_bank0 82,86
#define mOp1_clHit 87,88
#define mOp1_banks 89,120
#define mOp1_regNo 121,129
#define mOp1_LSQ 130,138
#define mOp1_II 139,148
#define mOp1_thr 149,149
#define mOp1_lsf 150,150
#define mOp1_WQ 151,158
#define mOp1_lsfwd 159,159
#define mOp1_type 160,161
#define mOp1_width 162

#define mOp2_addrMain 0,43
#define mOp2_sz 44,48
#define mOp2_bank0 49,53
#define mOp2_split 54,54
#define mOp2_LSQ 55,63
#define mOp2_II 64,73
#define mOp2_thread 74,74
#define mOp2_lsflag 75,75
#define mOp2_WQ 76,83
#define mOp2_banks 84,115
#define mOp2_odd 116,116
#define mOp2_addr_low 117,118
#define mOp2_type 119,120
#define mOp2_width 121

#define lsaddr_addrE 0,35
#define lsaddr_addrO 36,71
#define lsaddr_banks 72,103
#define lsaddr_OH 104,104
#define lsaddr_EH 105,105
#define lsaddr_EL 106,106
#define lsaddr_OL 107,107
#define lsaddr_II 108,117
#define lsaddr_odd_round 118,118 
#define lsaddr_bank0 119,123
#define lsaddr_reg_hi 124,128
#define lsaddr_low 129,130
#define lsaddr_odd 131,131
#define lsaddr_split 132,132
#define lsaddr_st 133,133
#define lsaddr_sz 134,138
#define lsaddr_reg_low 139,142
#define lsaddr_flag 143,143
#define lsaddr_pconfl 144,144
#define lsaddr_except 145,145
#define lsaddr_mtype 146,147
#define lsaddr_WQ 148,155
#define lsaddr_blow 156,159
#define lsaddr_etype 160,163
#define lsaddr_width 164
#define lsaddr_II_low 108,111

#define lsqshare_wrt0 0,2
#define lsqshare_wrt1 3,5
#define lsqshare_wrt2 6,8
#define lsqshare_used 9,14
#define lsqshare_II 15,20
#define lsqshare_wrtII0 21,24
#define lsqshare_wrtII1 25,28
#define lsqshare_wrtII2 29,32
#define lsqshare_usedB 33,38
#define lsqshare_width 39

#define lsqpend_retire 0,5
#define lsqpend_ldconfl 6,11
#define lsqpend_smpconfl 12,17
#define lsqpend_odd_round 18,18
#define lsqpend_odd_rnd_partial 19,19
#define lsqpend_width 20

#define lsqxcept_code 0,5
#define lsqxcept_xcept 6,6
#define lsqxcept_II 7,16
#define lsqxcept_smpdep 17,17
#define lsqxcept_odd_round 18,18

#define lsqxcept_width 19




#define lsfxdata_byBank 0,0
#define lsfxdata_Mexact 1,1
#define lsfxdata_banks 2,5
#define lsfxdata_Mshift 6,10
#define lsfxdata_has 11,11
#define lsfxdata_width 12


#define rbus_used 0,0
#define rbus_second 1,1
#define rbus_bcast 2,2
#define rbus_mreq 3,3
#define rbus_creq 4,4
#define rbus_want_excl 5,5
#define rbus_code 6,6
#define rbus_dupl 7,7
#define rbus_ior 8,8
#define rbus_width 9

#define rbusD_used 0,0
#define rbusD_second 1,1
#define rbusD_bcast 2,2
#define rbusD_mem_reply 3,3
#define rbusD_cc_reply 4,4
#define rbusD_write_back 5,5
#define rbusD_excl 6,6
#define rbusD_dirty 7,7
#define rbusD_iorpl 8,8
#define rbusD_width 9

#define rbusM_data 0,511
#define rbusM_src_req 512,521
#define rbusM_dst_req 522,531
#define rbusM_addr 532,568
#define rbusM_signals 569,576
#define rbusM_width 577

#define ptype_int 0
#define ptype_ext 1
#define ptype_dbl 2
#define ptype_sngl 3


#define ptr_exp 59,63
#define ptr_low 52,58
#define ptr_hi 45,51
#define ptr_on_low 44,44
#define ptr_addr 0,43


