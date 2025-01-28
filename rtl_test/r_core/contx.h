
class hcont {
  public:
  unsigned long reg_gen[32];
  char reg_genP[32];
  unsigned long reg_fpA[32];
  unsigned long reg_fpB[32];
  unsigned reg_fpA_X[32];
  unsigned short reg_fpB_X[32];
  unsigned flags;
  hcont() {
  }
};
