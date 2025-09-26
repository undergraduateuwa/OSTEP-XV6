 struct sysinfo{
    int freemem;
    int nproc;
 };

 struct sysinfo;
 int sysinfo(struct sysinfo *);