gcc ./mining/hash1.1.c -o ./mining/hash1.1
gcc ./mining/cmp.c -o ./mining/cmp
{
    bpftrace --unsafe ./mining/cont_openfiles.bt      >  ./log/cont_openfiles.log
}&

{
    bpftrace --unsafe ./mining/syscalls_seq.bt        >  ./log/syscalls_seq.log
}&

{
    bpftrace ./container/container_monitor.bt               >  ./log/cont_exec.log
}&

# {
#     bpftrace ./container/container_shell.bt              >  ./log/cont_shell.log
# }&

{
    ./hids   >  ./log/hids.log  2>&1
}&

{
    bpftrace --unsafe ./network/sliver-implant-dect.bt  >  ./log/sliver.log
}&

