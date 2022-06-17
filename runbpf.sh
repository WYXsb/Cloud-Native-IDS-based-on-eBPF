gcc ./wyx/hash1.1.c -o hash1.1
gcc ./wyx/cmp.c -o cmp
{
    bpftrace --unsafe ./wyx/cont_openfiles.bt >  ./log/cont_openfiles.log
}&

{
    bpftrace --unsafe ./wyx/syscalls_seq.bt   >  ./log/syscalls_seq.log
}&

{
    bpftrace ./dhz/container_exec.bt          >  ./log/cont_exec.log
}&

{
    bpftrace ./dhz/container_mount.bt         >  ./log/cont_mount.log
}&

{
    bpftrace ./dhz/container_shell.bt         >  ./log/cont_shell.log
}&

{
    bpftrace ./dhz/rootkit.bt                 >  ./log/rootkit.log
}&

