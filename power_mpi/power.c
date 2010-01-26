static char help[] = "Solves a standard eigensystem Ax=kx with the matrix loaded from a file.\n"
  "This example works for both real and complex numbers.\n\n"
  "The command line options are:\n"
  "  -file <filename>, where <filename> = matrix file in PETSc binary form.\n\n";

#include "petscmat.h"
#include "petscvec.h"
#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

#define max(a, b)       ((a) > (b) ? (a) : (b))
#define min(a, b)       ((a) < (b) ? (a) : (b))


#undef __FUNCT__
#define __FUNCT__ "fakult"
double fakult(int eingabe)
{
   if(eingabe<=1) return 1.0;   // da fak(0) gleich 1 ist und fak(1) ebenfalls 1 ist
   double ergebnis=1.0;
   do
   {
      ergebnis = ergebnis * eingabe;
      eingabe--;
   }while(eingabe>1);
   return ergebnis;
}

#undef __FUNCT__
#define __FUNCT__ "vec_get_dist"
void vec_get_dist(Vec x,Vec y,PetscReal *max, PetscInt *max_elem) {
  PetscInt x_local_rows, y_local_rows, x_start_row, x_end_row, y_start_row, y_end_row, i;
  VecGetLocalSize(x,&x_local_rows);
  VecGetLocalSize(y,&y_local_rows);
  VecGetOwnershipRange(x, &x_start_row, &x_end_row);
  VecGetOwnershipRange(y, &y_start_row, &y_end_row);
  PetscScalar *xa, *ya;
  if(x_local_rows != y_local_rows || x_start_row != y_start_row || x_start_row != y_start_row) {
    (*PetscErrorPrintf)("Error! Local vectors do not have equal settings: %d %d | %d %d | %d %d\n", x_local_rows, y_local_rows, x_start_row, y_start_row, x_start_row, y_start_row);
  }
  VecGetArray(x,&xa);
  VecGetArray(y,&ya);
  for(i = 0; i < x_local_rows; ++i) {
    __builtin_prefetch(xa+i+1,1);
    __builtin_prefetch(ya+i+1,0);
    if(xa[i] > 0) {
      xa[i] = fabs(ya[i]/xa[i]-1);
    } else {
      xa[i] = 0;
    }
  }
  VecRestoreArray(x, &xa);
  VecRestoreArray(y, &ya);
  VecMax(x, max_elem, max);
  //PetscPrintf(PETSC_COMM_WORLD,"distance: %g %d\n", *max, *max_elem);
}

#undef __FUNCT__
#define __FUNCT__ "vec_to_file"
void vec_to_file(Vec u, PetscInt iteration, PetscReal dist, const char *prefix) {
  PetscInt       lrows, start_row, end_row, nEnergy, i, n, j;
  //PetscInt       rank;
  PetscScalar    *v0a;
  PetscReal      fak, fakln, value;
  FILE *         file;
  char filename[100];

  //MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
  VecGetLocalSize(u,&lrows);
  VecGetOwnershipRange(u, &start_row, &end_row);
  //PetscSynchronizedPrintf(PETSC_COMM_WORLD,"[%d] local row start / end: %d %d\n", rank, start_row, end_row);
  //PetscSynchronizedFlush(PETSC_COMM_WORLD);
  VecGetArray(u,&v0a);
  if(prefix == NULL) {
    PetscSNPrintf(filename, 100, "%s.%06d_%.6g.dat", "pet", iteration, dist);
  } else {
    PetscSNPrintf(filename, 100, "%s.%06d_%.6g.dat", prefix, iteration, dist);
  }
  
  PetscFOpen(PETSC_COMM_WORLD, filename, "w", &file);
  fak = 1.0;
  nEnergy = 500;
  for(i = 0; i < lrows; ++i) {
    n = (start_row+i)/(double)nEnergy+2;
    j = (start_row+i)-((n-2)*nEnergy);
    fakln = 0.0;
    if(n > 0) {
      fak = fakult(n);
      fakln = n*log(125.0)-log(fak);
    }
    value = v0a[i];
    if(value > 0) {
      PetscSynchronizedFPrintf(PETSC_COMM_WORLD, file, "%4d %12g %12g %12g %12g\n", n, (j*(10+700)/(double)(nEnergy)-700.0)+0.71, log(value) + fakln, log(value), value);
    }
  }
  PetscSynchronizedFlush(PETSC_COMM_WORLD);
  PetscFClose(PETSC_COMM_WORLD, file);
  VecRestoreArray(u, &v0a);
}

#undef __FUNCT__
#define __FUNCT__ "read_parq_matrix"
PetscErrorCode read_parq_matrix(const char * filename, Mat *A) {
  gzFile pf;
  int i,j,ni,nj;
  PetscInt m,n;
  uint32_t outer_cols, outer_rows, inner_cols, inner_rows;
  uint32_t minParticles, maxParticles, nParticles, nEnergy;
  double minEnergy, maxEnergy, energyBinWidth, volume;
  double *data;
  PetscErrorCode ierr;
  
  pf = gzopen(filename, "rb");
  
  gzread(pf, (char*)&minParticles,   sizeof(minParticles));
  gzread(pf, (char*)&maxParticles,   sizeof(maxParticles));
  gzread(pf, (char*)&nParticles,     sizeof(nParticles));
  gzread(pf, (char*)&minEnergy,      sizeof(minEnergy));
  gzread(pf, (char*)&maxEnergy,      sizeof(maxEnergy));
  gzread(pf, (char*)&energyBinWidth, sizeof(energyBinWidth));
  gzread(pf, (char*)&nEnergy,        sizeof(nEnergy));
  gzread(pf, (char*)&volume,         sizeof(volume));
  gzread(pf, (char*)&outer_cols,     sizeof(outer_cols));
  gzread(pf, (char*)&outer_rows,     sizeof(outer_rows));
  gzread(pf, (char*)&inner_cols,     sizeof(inner_cols));
  gzread(pf, (char*)&inner_rows,     sizeof(inner_rows));
  // create Matrix
  ierr = MatCreateSeqAIJ(PETSC_COMM_WORLD,outer_rows*inner_rows,outer_cols*inner_cols,1000,0,A);CHKERRQ(ierr);
  data = malloc(sizeof(double)*inner_rows*inner_cols);
  
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Matrix Informationen:\nSize: %d*%d X %d*%d\n", outer_rows, inner_rows, outer_cols, inner_cols);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"System:\n  Particles: %d - %d | %d\n", minParticles, maxParticles, nParticles);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"  Energy   : %f - %f | %d | %f\n", minEnergy, maxEnergy, nEnergy, energyBinWidth);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"  Volume   : %f\n", volume);CHKERRQ(ierr);
  
  for (ni = 0; ni < (int)(outer_cols); ++ni) {
    for (nj = max(ni-1, 0);
         nj < min(ni+2, (int)(outer_rows));
         ++nj)
    {
      gzread(pf, (char*)data, sizeof(double)*inner_rows*inner_cols);
      for(i = 0; i < inner_rows; ++i) {
        for(j = 0; j < inner_cols; ++j)
        {
          if(data[i*inner_rows+j] > 0) {
            m = inner_rows*nj+j;
            n = inner_cols*ni+i;
            ierr = MatSetValues(*A,1,&n,1,&m,&(data[i*inner_rows+j]),INSERT_VALUES);CHKERRQ(ierr);
          }
        }
      }
    }
  }
  ierr = MatAssemblyBegin(*A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  free(data);
  gzclose(pf);
  ierr = MatAssemblyEnd(*A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  ierr = MatCompress(*A);CHKERRQ(ierr);
  
  return 0;
}

#undef __FUNCT__
#define __FUNCT__ "main"
int main( int argc, char **argv )
{
  Vec            x,b,u,d;      /* approx solution, RHS, exact solution */
  Mat            A;            /* linear system matrix */
  PetscErrorCode ierr;
  char        	 filename[256];
  //PetscViewer 	 viewer;
  PetscTruth  	 flg;
  PetscInt       i,/*j,*/cols, rows, /*n, nEnergy, */lcols, lrows, /*start_row, end_row, */plot_every, max_iter,rank, dist_elem;
  PetscReal      norm, /*fak, fakln, value,*/ dist;
  PetscScalar    lambda, residual/*, *v0a*/;
  PetscLogDouble v1,v2;
  MatInfo        info;
  //FILE* file;

  PetscInitialize(&argc,&argv,(char *)0,help);

  //ierr = PetscPrintf(PETSC_COMM_WORLD,"\nEigenproblem stored in file.\n\n");CHKERRQ(ierr);
  ierr = PetscOptionsGetString(PETSC_NULL,"-file",filename,256,&flg);CHKERRQ(ierr);
  if (!flg) {
    SETERRQ(1,"Must indicate a file name with the -file option.");
  }
  ierr = PetscOptionsGetInt(PETSC_NULL,"-every",&plot_every,&flg);CHKERRQ(ierr);
  if(!flg) {
    plot_every = 1000;
  }
  ierr = PetscOptionsGetInt(PETSC_NULL,"-max_iter",&max_iter,&flg);CHKERRQ(ierr);
  if(!flg) {
    max_iter = 200000;
  }
  
  MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
  if(rank == 0) {
    ierr = read_parq_matrix(filename, &A);CHKERRQ(ierr);
  }
  MPI_Barrier(PETSC_COMM_WORLD);
  ierr = MatGetInfo(A, MAT_GLOBAL_SUM, &info);CHKERRQ(ierr);
  //ierr = PetscViewerBinaryOpen(PETSC_COMM_WORLD,filename,FILE_MODE_READ,&viewer);CHKERRQ(ierr);
  //ierr = MatLoad(viewer,MATAIJ,&A);CHKERRQ(ierr);
  //ierr = PetscViewerDestroy(viewer);CHKERRQ(ierr);
  ierr = MatGetVecs(A,&x,PETSC_NULL);CHKERRQ(ierr);
  ierr = MatGetVecs(A,&u,PETSC_NULL);CHKERRQ(ierr);
  ierr = MatGetVecs(A,&b,PETSC_NULL);CHKERRQ(ierr);
  ierr = MatGetVecs(A,&d,PETSC_NULL);CHKERRQ(ierr);
  ierr = MatGetSize(A, &cols, &rows);CHKERRQ(ierr);
  ierr = MatGetLocalSize(A, &lcols, &lrows);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Matrix Size: %d %d nonzero: %.0f fill-ratio: %f\n", cols, rows, info.nz_used, (info.nz_used/cols/rows)*100.0);CHKERRQ(ierr);
  ierr = PetscSynchronizedPrintf(PETSC_COMM_WORLD,"[%d] Matrix Size (local): %d %d\n", rank, lcols, lrows);CHKERRQ(ierr);
  PetscSynchronizedFlush(PETSC_COMM_WORLD);
  ierr = VecSet(u, 1.0/rows);CHKERRQ(ierr);
  ierr = VecSet(b, 0.0);CHKERRQ(ierr);
  ierr = VecSet(x, 0.0);CHKERRQ(ierr);
  ierr = VecSet(d, 0.0);CHKERRQ(ierr);
  
  i=0;
  dist = 1;
  PetscGetTime(&v1);
  //for(i = 0; i < max_iter; ++i) {
  while(dist > 1e-10) {
    i++;
    VecCopy(u, b);
    MatMult(A, u, x);
    if(i % plot_every == 0) {
      VecDot(u, x, &lambda);
      VecAYPX(u, -lambda, x);
      VecNorm(u, NORM_2, &residual);
    }
    VecCopy(x, u);
    VecNorm(u, NORM_1, &norm);
    VecScale(u, 1.0/norm);
    
    //VecMaxPointwiseDivide(b,u,&dist);
    if(i % plot_every == 0) {
      vec_get_dist(b, u, &dist, &dist_elem);
      vec_to_file(u, i, dist, NULL);
      vec_to_file(b, i, dist, "err");
      PetscGetTime(&v2);
      ierr = PetscPrintf(PETSC_COMM_WORLD,"%10d: Norm: %12g r: %12g lambda: %12g dist: %12g (%6d) i/s: %8.4f\n", i, norm, residual, lambda, fabs(dist), dist_elem, plot_every/(v2-v1));CHKERRQ(ierr);
      v1 = v2;
    }
    if(i >= max_iter) {
      break;
    }
  }
  vec_to_file(u, i, dist, NULL);
    
  /* 
     Free work space
  */
  ierr = VecDestroy(u);CHKERRQ(ierr); ierr = VecDestroy(x);CHKERRQ(ierr);
  ierr = VecDestroy(b);CHKERRQ(ierr); ierr = MatDestroy(A);CHKERRQ(ierr);
  ierr = PetscFinalize();CHKERRQ(ierr);
  return 0;
}

