.section ".text"

.global get_tc
get_tc:
    mrs x0, cntpct_el0
    ret

.global get_tf
get_tf:
    mrs x0, cntfrq_el0
    ret

.global svc1
svc1:
    svc #1
    ret

.global brk1
brk1:
    brk #1
    ret

