#define csr_page 0
#define csr_vmpage 1
#define csr_page0 2
#define csr_vmpage0 3
#define csr_retIP 4
#define csr_excStackSave 5
#define csr_excStack 6
#define csr_PCR 7
#define csr_excIP 8
#define csr_PCR_reg_save 9
#define csr_mflags 10
#define csr_FPU 11
#define csr_syscall 12
#define csr_vmcall 13
#define csr_cpage_mask 14
#define csr_indir_table 15
#define csr_indir_mask 16
#define mflags_cpl 0
#define mflags_vm 2
#define mflags_pg 3
#define mflags_irq 4
//define mflags_main 5
//define mflags_helper 6
#define mflags_dbl_fault 7
#define mflags_excpt_extra 8
#define mflags_transl_en 16



#define csrfpu_inv_excpt 0
#define csrfpu_under_excpt 1
#define csrfpu_under_ieee_excpt 2
#define csrfpu_over_excpt 3
#define csrfpu_over_ieee_excpt 4
#define csrfpu_inexact_excpt 5
#define csrfpu_inexact_ieee_excpt 6
#define csrfpu_denor_excpt 7
#define csrfpu_denor_ieee_excpt 8
#define csrfpu_denor_consume_excpt 9
#define csrfpu_denor_produce_excpt 10
#define csrfpu_inv_flag 11
#define csrfpu_under_flag 12
#define csrfpu_under_ieee_flag 13
#define csrfpu_over_flag 14
#define csrfpu_over_ieee_flag 15
#define csrfpu_inexact_flag 16
#define csrfpu_inexact_ieee_flag 17
#define csrfpu_denor_flag 18
#define csrfpu_denor_ieee_flag 19
#define csrfpu_denor_consume_flag 20
#define csrfpu_denor_produce_flag 21

#define csrfpu_rmode 22,24
#define csrfpu_rmodeE 25,27
#define csrfpu_clip_IEEE 28
#define csrfpu_daz 29

