#include "string.h"
//#include "SMMUTypes.h"
//#include "SMMUUtils.h"
//#include "HALIOMMULib.h"
#include "HALIOMMUv3Reg.h"
#include "HALIOMMUv3Queue.h"
//#include "IORT.h"

//TODO
void SMMU_Handle_Event(uint64 smmu_base, HAL_IOMMUv3_EVT_t event)
{
    return;
}
void SMMU_memory_barrier(void)
{
    __asm("DSB sy");
}

/* ========================================================================================================================
        Command Queue Functions.  Enqueues and command processing expected to be done under mutual exclusion
   ======================================================================================================================== */
uint32 g_cmdq_err_code = 0;

void HAL_IOMMUv3_LOG_CMDQ_ERROR(uint32 cons) {
    g_cmdq_err_code = (cons >> 24) & 0x7F;
    while(1); // TODO ERR FATAL
}

/* Enqueues a single command into the command queue, unless it is full.  Updates prod_session to indicate the increment/wrap
   upon successful enqueue.  On first usage, a value of HALIOMMUv3_PROD_INVALID (-1) must be used for prod_session.  
   This prod_session must be used to process the commands using HAL_IOMMUv3_Process_CMDs(). */
static HAL_IOMMUResult_t HAL_IOMMUv3_Enqueue_CMD(uint64 smmu_base, int ns, HAL_IOMMUv3_CMD_t *cmd, uint32 *prod_session)
{
    uint32  prod, cons, size = 0, max_idx = 0, prod_idx, cons_idx, wrap_prod, wrap_cons;
    HAL_IOMMUv3_CMD_t *cmdq = NULL;
    
    HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_CMDQ_BASE_OFFSET, (uint32 *)&cmdq);
    
    size = (uint64)cmdq & 0x1F;
    max_idx = (2 << size) - 1;
    
    cmdq = (HAL_IOMMUv3_CMD_t *)((uint64)cmdq & ~0x1F);
    
    if(!cmdq || !prod_session) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
    // Get CMDQ_PROD and CMDQ_CONS, and relevant fields
    prod = *prod_session;
    if(prod == HALIOMMUv3_PROD_INVALID) {
        // First Enqueue
        HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_CMDQ_PROD_OFFSET, &prod);
    }
    HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_CMDQ_CONS_OFFSET, &cons);

    wrap_prod = (prod >> size) & 0x1;
    wrap_cons = (cons >> size) & 0x1;
    
    prod_idx = prod & max_idx;
    cons_idx = cons & max_idx;
    
    if((prod_idx == cons_idx) && (wrap_prod != wrap_cons)) {
        // Queue full
        return HAL_IOMMU_ERR_QUEUE_FULL;
    }
    
    // Enqueue CMD
    memscpy(&cmdq[prod_idx], sizeof(HAL_IOMMUv3_CMD_t), cmd, sizeof(HAL_IOMMUv3_CMD_t));
    
    // CMO? Barrier? TODO
    
    // Check for wrap    
    if(prod_idx == max_idx) {
        // Need to wrap
        prod_idx = 0;
        if(wrap_prod) {
            // clear wrap
            prod &= ~(1 << size);
        }
        else {
            // set wrap
            prod |= (1 << size);
        }
    }
    else {
        prod_idx++;
    }
    
    prod = (prod & ~max_idx) | prod_idx;
    
    // Update PROD for this session of enqueues
    *prod_session = prod;
    
    return HAL_IOMMU_ERR_OK;
}

/* Processes all of the commands associated with prod_session and polls for completion.
   In the event of an error, will log the result and terminate processing */
HAL_IOMMUResult_t HAL_IOMMUv3_Process_CMDs(uint64 smmu_base, int ns, uint32 *prod_session)
{
    uint32  prod, cons, size = 0, max_idx = 0, prod_idx, cons_idx, wrap_prod, wrap_cons, gerror = 0;
    HAL_IOMMUv3_CMD_t *cmdq = NULL;
    
    HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_CMDQ_BASE_OFFSET, (uint32 *)&cmdq);
    
    size = (uint64)cmdq & 0x1F;
    max_idx = (2 << size) - 1;
    
    cmdq = (HAL_IOMMUv3_CMD_t *)((uint64)cmdq & ~0x1F);
    
    if(!cmdq || !prod_session) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
    // Get CMDQ_PROD and CMDQ_CONS, and relevant fields
    prod = *prod_session;
    if(prod == HALIOMMUv3_PROD_INVALID) {
        // Invalid PROD
        return HAL_IOMMU_ERR_INVALID_PARAM;
    }

    wrap_prod = (prod >> size) & 0x1;    
    prod_idx = prod & max_idx;
    
    // Ensure SMMU can see commands
    SMMU_memory_barrier();
    
    // Write prod_session to HW to process commands
    HAL_IOMMUv3_REG_WRITE32(smmu_base, ns, HAL_IOMMUv3_CMDQ_PROD_OFFSET, prod);
    
    // Poll on CONS to wait for commands to complete
    do {
        // Read CMDQ_CONS
        HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_CMDQ_CONS_OFFSET, &cons);
        // Read GERROR.CMDQ_ERR
        HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_GERROR_OFFSET, &gerror);
        if(gerror & GERROR_CMDQ_ERR_MASK) {
            // Log CMDQ error 
            HAL_IOMMUv3_LOG_CMDQ_ERROR(cons);
            return HAL_IOMMU_ERR_GENERIC_ERROR; // maybe different behavior later
        }
        
        cons_idx = cons & max_idx;
        wrap_cons = (cons >> size) & 0x1;
        
    }while((prod_idx != cons_idx) || (wrap_prod != wrap_cons)); // not 'empty'
    
    return HAL_IOMMU_ERR_OK;
}


HAL_IOMMUResult_t HAL_IOMMUv3_CMD_PREFETCH_CONFIG(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 ssid, boolean ssv)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    // setup command
    cmd[0] = CMD_PREFETCH_CONFIG | ((ssec ? 1 : 0) << 10) | ((ssv ? 1 : 0) << 11) | (ssid << 12);
    cmd[1] = sid;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_PREFETCH_ADDR(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 ssid, boolean ssv, uint64 addr, uint32 size, uint32 stride)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    // setup command
    cmd[0] = CMD_PREFETCH_ADDR | ((ssec ? 1 : 0) << 10) | ((ssv ? 1 : 0) << 11) | (ssid << 12);
    cmd[1] = sid;
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (stride << 5) | size;
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_STE(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_CFGI_STE | ((ssec ? 1 : 0) << 10);
    cmd[1] = sid;
    cmd[2] = leaf ? 1 : 0;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_STE_RANGE(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 range)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_CFGI_STE_RANGE | ((ssec ? 1 : 0) << 10);
    cmd[1] = sid;
    cmd[2] = range;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_ALL(uint64 smmu_base, int ns, uint32 *prod_session, boolean ssec)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_CFGI_ALL | ((ssec ? 1 : 0) << 10);
    cmd[2] = 31; // max
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_CD(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 ssid, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_CFGI_CD | ((ssec ? 1 : 0) << 10) | (ssid << 12);
    cmd[1] = sid;
    cmd[2] = leaf ? 1 : 0;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_CD_ALL(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_CFGI_CD_ALL | ((ssec ? 1 : 0) << 10);
    cmd[1] = sid;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_CFGI_VMS_PIDM(uint64 smmu_base, int ns, uint32 *prod_session, boolean ssec, uint32 vmid)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_CFGI_VMS_PIDM | ((ssec ? 1 : 0) << 10);
    cmd[1] = vmid;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NH_ALL(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_NH_ALL;
    cmd[1] = vmid;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NH_ASID(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid, uint32 asid)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_NH_ASID;
    cmd[1] = vmid | (asid << 16);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NH_VA(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid, uint32 asid, uint64 addr, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_NH_VA; // NUM / SCALE ignored because we will use TG = 0
    cmd[1] = vmid | (asid << 16);
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0);
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NH_VAA(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid, uint64 addr, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_NH_VAA;
    cmd[1] = vmid;
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0);
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL3_ALL(uint64 smmu_base, int ns, uint32 *prod_session)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_EL3_ALL;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL3_VA(uint64 smmu_base, int ns, uint32 *prod_session, uint64 addr, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_EL3_VA;
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0);
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL2_ALL(uint64 smmu_base, int ns, uint32 *prod_session)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_EL2_ALL;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL2_ASID(uint64 smmu_base, int ns, uint32 *prod_session, uint32 asid)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_EL2_ASID;
    cmd[1] = (asid << 16);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL2_VA(uint64 smmu_base, int ns, uint32 *prod_session, uint32 asid, uint64 addr, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_EL2_VA;
    cmd[1] = (asid << 16);
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0);
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_EL2_VAA(uint64 smmu_base, int ns, uint32 *prod_session, uint64 addr, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_EL2_VAA;
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0);
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S12_VMALL(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_S12_VMALL;
    cmd[1] = vmid;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S2_IPA(uint64 smmu_base, int ns, uint32 *prod_session, uint32 vmid, uint64 addr, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_S2_IPA;
    cmd[1] = vmid;
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0);
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_NSNH_ALL(uint64 smmu_base, int ns, uint32 *prod_session)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_NSNH_ALL;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_ATC_INV(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, uint32 ssid, boolean ssv, boolean global, uint64 addr, uint32 size)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_ATC_INV | ((global ? 1 : 0) << 9) | ((ssv ? 1 : 0) << 11) | (ssid << 12);
    cmd[1] = sid;
    cmd[2] = (uint32)(addr & 0xFFFFF000) | size;
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_PRI_RESP(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, uint32 ssid, boolean ssv, uint32 prgidx, uint32 rsp)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_PRI_RESP | ((ssv ? 1 : 0) << 11) | (ssid << 12);
    cmd[1] = sid;
    cmd[2] = prgidx | (rsp << 12);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_RESUME(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec, uint32 stag, boolean action, boolean abort)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_RESUME | ((ssec ? 1 : 0) << 10) | ((action ? 1 : 0) << 12) | ((abort ? 1 : 0) << 13);
    cmd[1] = sid;
    cmd[2] = stag;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_STALL_TERM(uint64 smmu_base, int ns, uint32 *prod_session, uint32 sid, boolean ssec)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_STALL_TERM | ((ssec ? 1 : 0) << 10);
    cmd[1] = sid;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, ns, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_SYNC(uint64 smmu_base, int ns, uint32 *prod_session, uint32 compsig, uint64 msi_addr, uint32 msi_data, uint32 msi_attr)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_SYNC;
    // MSI not supported
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, 0, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_EL2_ALL(uint64 smmu_base, uint32 *prod_session)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_S_EL2_ALL;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, 0, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_EL2_ASID(uint64 smmu_base, uint32 *prod_session, uint32 asid)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_S_EL2_ASID;
    cmd[1] = (asid << 16);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, 0, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_EL2_VA(uint64 smmu_base, uint32 *prod_session, uint32 asid, uint64 addr, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_S_EL2_VA;
    cmd[1] = (asid << 16);
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0);
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, 0, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_EL2_VAA(uint64 smmu_base, uint32 *prod_session, uint64 addr, boolean leaf)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_S_EL2_VAA;
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0);
    cmd[3] = (uint32)(addr >> 32);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, 0, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_S12_VMALL(uint64 smmu_base, uint32 *prod_session, uint32 vmid)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_S_S12_VMALL;
    cmd[1] = vmid;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, 0, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_S_S2_IPA(uint64 smmu_base, uint32 *prod_session, uint32 vmid, uint64 addr, boolean leaf, boolean ns)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_S_S2_IPA;
    cmd[1] = vmid;
    cmd[2] = (uint32)(addr & 0xFFFFF000) | (leaf ? 1 : 0) | ((ns ? 1 : 0) << 1);
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, 0, &cmd, prod_session);
}
HAL_IOMMUResult_t HAL_IOMMUv3_CMD_TLBI_SNH_ALL(uint64 smmu_base, uint32 *prod_session)
{
    HAL_IOMMUv3_CMD_t cmd = {0};
    
    cmd[0] = CMD_TLBI_SNH_ALL;
    
    return HAL_IOMMUv3_Enqueue_CMD(smmu_base, 0, &cmd, prod_session);
}


/* ========================================================================================================================
        Event Queue Functions.  Event Dequeuing and Processing is expected to be done under mutual exclusion
   ======================================================================================================================== */


HAL_IOMMUResult_t HAL_IOMMUv3_Dequeue_EVT(uint64 smmu_base, int ns, HAL_IOMMUv3_EVT_t *event, uint32 *cons_session)
{
    uint32  prod, cons, size = 0, max_idx = 0, prod_idx, cons_idx, wrap_prod, wrap_cons;
    HAL_IOMMUv3_EVT_t *evtq = NULL;
    
    HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_CMDQ_BASE_OFFSET, (uint32 *)&evtq);
    
    size = (uint64)evtq & 0x1F;
    max_idx = (2 << size) - 1;
    
    evtq = (HAL_IOMMUv3_EVT_t *)((uint64)evtq & ~0x1F);
    
    if(!evtq || !cons_session) {
        return HAL_IOMMU_ERR_NULL_POINTER;
    }
    
    // Get CMDQ_PROD and CMDQ_CONS, and relevant fields
    cons = *cons_session;
    if(cons == HALIOMMUv3_CONS_INVALID) {
        // First Dequeue
        HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_CMDQ_CONS_OFFSET, &cons);
    }
    HAL_IOMMUv3_REG_READ32(smmu_base, ns, HAL_IOMMUv3_CMDQ_PROD_OFFSET, &prod);
    

    wrap_prod = (prod >> size) & 0x1;
    wrap_cons = (cons >> size) & 0x1;
    
    prod_idx = prod & max_idx;
    cons_idx = cons & max_idx;
    
    if((prod_idx == cons_idx) && (wrap_prod == wrap_cons)) {
        // Queue Empty
        return HAL_IOMMU_ERR_QUEUE_EMPTY;
    }
    
    // CMO? TODO
    
    // Dequeue CMD
    memscpy(event, sizeof(HAL_IOMMUv3_EVT_t), &evtq[cons_idx], sizeof(HAL_IOMMUv3_EVT_t));
    
    // Check for wrap    
    if(cons_idx == max_idx) {
        // Need to wrap
        cons_idx = 0;
        if(wrap_cons) {
            // clear wrap
            cons &= ~(1 << size);
        }
        else {
            // set wrap
            cons |= (1 << size);
        }
    }
    else {
        cons_idx++;
    }
    
    cons = (cons & ~max_idx) | cons_idx;
    
    // Update CONS for this session of dequeues
    *cons_session = cons;
    
    return HAL_IOMMU_ERR_OK;
}

HAL_IOMMUResult_t HAL_IOMMUv3_Process_EVTs(uint64 smmu_base, int ns)
{
    uint32  cons_session = HALIOMMUv3_CONS_INVALID; // initialize CONS for first dequeue
    HAL_IOMMUv3_EVT_t event = {0};

    // Loop through dequeueing events and processing them until the queue is empty
    while(HAL_IOMMU_ERR_QUEUE_EMPTY != HAL_IOMMUv3_Dequeue_EVT(smmu_base, ns, &event, &cons_session)) {
        // Process Event
        SMMU_Handle_Event(smmu_base, event); // Security Level specific implementation
        // Write cons_session to HW to indicate this event has been processed
        HAL_IOMMUv3_REG_WRITE32(smmu_base, ns, HAL_IOMMUv3_EVENTQ_CONS_OFFSET, cons_session);
    }
    
    return HAL_IOMMU_ERR_OK;
}

