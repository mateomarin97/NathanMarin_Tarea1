#PBS -q batch                                                                  
#PBS -N out                                                                    
#PBS -l nodes=1:ppn=4                                                          
#PBS -M mneira011@gmail.com                                                    
#PBS -m abe                                                                    


cd $PBS_O_WORKDIR
NPROCS=`wc -l < $PBS_NODEFILE`
./cuerda.x 

