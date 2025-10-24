#ifndef LLVM_COMPAT_H
#define LLVM_COMPAT_H

#ifdef __clang__
#define __irq               
#define __weak            
#define __asm            
#define __packed           
#define __forceinline      
#define __pure             
#define __dsb(x)            
#define __isb(x)           
#define __clz(x)           
#define __return_address() 
#define __schedule_barrier() 
#define __disable_irq()     
#define __enable_irq()     
#define value_in_regs

static inline unsigned int __rbit(unsigned int val)
{
    int ret;
    return ret;
}

#endif /* __clang__ */


#endif /* LLVM_COMPAT_H */

