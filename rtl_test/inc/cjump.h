

bool cjump(unsigned type,unsigned flags) {
    bool C=(flags>>5)&1;
    bool O=(flags>>4)&1;
    bool A=(flags>>3)&1;
    bool S=(flags>>2)&1;
    bool Z=(flags>>1)&1;
    bool P=(flags)&1;
    switch(type) {
	case jump_Z: return Z;
	case jump_nZ: return !Z;
	case jump_S: return S;
	case jump_nS: return !S;
        case jump_uGT: return !(C | Z);
        case jump_uLE:  return C | Z;
        case jump_uGE:  return !C;
        case jump_uLT:  return C;
        case jump_sGT:  return !((S^O)|Z);
        case jump_sLE:  return (S^O)|Z;
        case jump_sGE:  return !S^O;
        case jump_sLT:  return S^O;
        case jump_O:    return O;
        case jump_nO:   return !O;
        case jump_P:    return P;
        case jump_nP:   return !P;
        case 0x19:   return 0;//wr csrss
        default:    return 1;
//mngwana una no get rich
    }
}

char *COND(int index) {
    index=((index>>7)&0xe)|(index&1);
    switch(index) {
	case jump_Z: return "e";
	case jump_nZ: return "ne";
	case jump_S: return "s";
	case jump_nS: return "ns";
        case jump_uGT: return "a";
        case jump_uLE:  return "be";
        case jump_uGE:  return "ae";
        case jump_uLT:  return "b";
        case jump_sGT:  return "g";
        case jump_sLE:  return "le";
        case jump_sGE:  return "ge";
        case jump_sLT:  return "l";
        case jump_O:    return "o";
        case jump_nO:   return "no";
        case jump_P:    return "p";
        case jump_nP:   return "np";
    }
    return "<err>";
}
